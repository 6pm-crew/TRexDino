#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "raylib.h"

static const char * shmem_name = "trexDino";
static const size_t shm_size = 4096;
void * addr;
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
    // printf("Please enter some text to write to shared memory segment\n");

    // char test[] = "jiral";
    // strncpy((char *)addr, test, shm_size);
    // unsigned 
    memcpy((Image *)addr,&image,sizeof(image));
    // printf("Unlinking shared memory segment.\n");
}

void closeSharedMemory(){
    free(addr);
    shm_unlink(shmem_name) ;
}