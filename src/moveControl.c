#include <string.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "main.h"
#include "moveControl.h"

#ifdef DQN_ENABLE
/**
 * @brief 공유 메모리 객체의 이름
 */
static const char *SHMEM_NAME = "trexDino";

/**
 * @brief 공유 메모리 데이터.
 */
static SharedData shmem_data;

/**
 * @brief 공유 메모리의 주소.
 */
static void *shmem_ptr = NULL;

/**
 * @brief 공유 메모리를 생성한다.
 * 
 * @return 메모리 생성 가능 여부
 */
bool OpenSharedMemory(void) {
    // 공유 메모리 객체를 생성한다.
    int fd = shm_open(
        SHMEM_NAME,
        O_CREAT | O_RDWR, 
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP
    );

    if (fd == -1) return false;

    TraceLog(LOG_INFO, "GAME: 공유 메모리 객체 생성 완료");

    // 공유 메모리의 크기를 설정한다.
    if (ftruncate(fd, SHMEM_TOTAL_SIZE) == -1) return false;

    // 공유 메모리를 실제로 할당한다.
    shmem_ptr = mmap(
        NULL, 
        SHMEM_TOTAL_SIZE, 
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0L
    );

    if (shmem_ptr == MAP_FAILED) return false;

    TraceLog(
        LOG_INFO, 
        "GAME: 공유 메모리 할당 완료 (%.1f MB)", 
        SHMEM_TOTAL_SIZE / 1000000.0
    );

    return true;
}

/**
 * @brief 공유 메모리를 해제한다.
 */
void CloseSharedMemory(void) {
    if (munmap(shmem_ptr, SHMEM_TOTAL_SIZE) != -1)
        TraceLog(
            LOG_INFO, 
            "GAME: 공유 메모리 해제 완료 (~%.1f MB)", 
            SHMEM_TOTAL_SIZE / 1000000.0
        );

    if (shm_unlink(SHMEM_NAME) != -1)
        TraceLog(LOG_INFO, "GAME: 공유 메모리 객체 삭제 완료");
}

/**
 * @brief 공유 메모리 데이터를 업데이트한다.
 * 
 * @param image 게임 화면 정보.
 */
void WriteToSharedMemory(void) {
    const Image image = LoadImageFromScreen();

    {   
        memcpy(
            shmem_data.screenData, 
            (unsigned char *) image.data, 
            SHMEM_TOTAL_SIZE
        );

        /* TODO: 나머지 정보 업데이트 */

        shmem_data.nextState = -1;
        shmem_data.reward = -1;
        shmem_data.done = -1;
        shmem_data.info = -1;
    }

    memcpy(shmem_ptr, &shmem_data, SHMEM_TOTAL_SIZE);

    TraceLog(LOG_DEBUG, "GAME: 공유 메모리에 게임 데이터 작성 완료");

    // 공유 메모리의 변경 사항을 즉시 기록한다.
    if (msync(shmem_ptr, SHMEM_TOTAL_SIZE, MS_SYNC) != -1)
        TraceLog(LOG_DEBUG, "GAME: 공유 메모리에 변경 사항 기록 완료");

    RL_FREE(image.data);
}

#endif