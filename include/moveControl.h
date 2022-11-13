#include <stdbool.h>
#include <stdint.h>

#include "raylib.h"

#define SHMEM_SCREEN_DATA_SIZE  ((SCREEN_WIDTH * SCREEN_HEIGHT) \
                                * sizeof(uint32_t))

#define SHMEM_TOTAL_SIZE        sizeof(SharedData)

#define SHMEM_WRITE_THRESHOLD   0.08f

/**
 * @brief 공유 메모리 데이터를 나타내는 구조체.
 */
typedef struct SharedData {
    uint8_t screenData[SHMEM_SCREEN_DATA_SIZE];
    int nextState;
    int reward;
    int done;
    int info;
} SharedData;

/**
 * @brief 공유 메모리를 생성한다.
 */
bool OpenSharedMemory(void);

/**
 * @brief 공유 메모리를 해제한다.
 */
void CloseSharedMemory(void);

/**
 * @brief 공유 메모리 데이터를 업데이트한다.
 * 
 * @param image 게임 화면 정보.
 */
void WriteToSharedMemory(void);