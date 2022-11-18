#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "raylib.h"

/**
 * @brief 배경을 그리는 함수
 * 
 * @param texture   사용할 이미지 
 * @param speed     이동하는 속도
 */
void drawBackground(Texture2D texture,float speed);

/**
 * @brief 게임이 종료될 경우 사용하는 함수
 * 
 * @param texture  사용할 이미지 
 */
void gameOverBackround(Texture2D texture);

/**
 * @brief 점수 출력 함수
 * 
 * @param texture  사용할 텍스쳐
 * @param position 출력 위치
 * @param n        출력할 숫자
*/
void drawNumberAt(Texture2D texture, Vector2 position, int n);

/**
 * @brief 텍스트 출력 함수
 * 
 * @param texture  사용할 텍스쳐
 * @param source   사용될 텍스트의 위치
 */
void drawResourceAt(Texture2D texture, Rectangle source);

#endif