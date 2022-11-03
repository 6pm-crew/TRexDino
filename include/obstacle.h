#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "obstacle_type.h"


/**
 * @brief 장애물을 변수를 초기화후 반환하는 함수.
 * 
 * @return Obstacle 
 */
Obstacle Obstacle_create();

/**
 * @brief 장애물을 생성한다.
 * 
 * @param ob 장애물 관리자 변수
 * @param score 현재 얻은 점수
 * @return Obstacle 
 */
Obstacle obstacle_make(ObstacleManager * ob, int score);



#endif