#include <stdbool.h>

#include "raylib.h"

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