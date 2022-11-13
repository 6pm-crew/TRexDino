#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "raylib.h"

static const char * shmem_name = "trexDino";
static const size_t shm_size = 4 * 600 * 800;
unsigned char * addr;
void openSharedMemory(){
    int shmem_fd = shm_open(shmem_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    if (shmem_fd == -1) {
        return;
    }
    printf("Shared Memory segment created with fd %d",shmem_fd);
    if (ftruncate(shmem_fd, shm_size) == -1) {
        return;
    }
    printf("Shared Memory segment resized to %d",shm_size);
    addr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (addr == MAP_FAILED) {
        return;
    }
}

int sendData(Image image){
    unsigned char * temp = (unsigned char *)image.data;
    memcpy(addr, temp, 4 * 600 * 800 * sizeof(unsigned char));
}

void closeSharedMemory(){
    shm_unlink(shmem_name) ;
}