#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "raylib.h"

/**
 * @brief 배경을 그리는 함수
 * 
 * @param texture 사용할 이미지 
 * @param speed 이동하는 속도
 */
void drawBackground(Texture2D texture,float speed);

/**
 * @brief 게임이 종료될 경우 사용하는 함수
 * 
 * @param texture 사용할 이미지 
 */
void gameOverBackround(Texture2D texture);
#endif