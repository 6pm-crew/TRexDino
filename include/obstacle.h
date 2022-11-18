#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "obstacle_type.h"

/**
 * @brief 장애물 변수 초기화 후 반환
 * 
 * @return Obstacle 
 */
Obstacle Obstacle_create();

/**
 * @brief 장애물 생성
 * 
 * @param ob    장애물 관리자 변수
 * @param score 현재 점수
 * @return Obstacle 
 */
Obstacle obstacle_make(ObstacleManager * ob, int score);
#endif