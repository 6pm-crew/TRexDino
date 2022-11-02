#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include "raylib.h"
#include "player.h"
#include "obstacle_type.h"

/** 큐 데이터 타입 Obstacle로 설정*/


/** 장애물 이동 속도*/
#define OBSTACLE_MOVE_SPEED 6
/** 장애물 이동 계수*/
#define OBSTACLE_MOVE_SPEED_MUL 0.1

/** 장애물 기본 x축 위치 비율*/
#define OBSTACLE_IDLE_X_MULT 0.98f
/** 장애물 기본 y축 위치 비율*/
#define OBSTACLE_IDLE_Y_MULT 0.7f

/** 장애물 총 종류 */
#define OBSTACLE_TOTAL_COUNT 3 


/**
 * @brief 장애물 관리자 생성 함수
 * 
 * @return ObstacleManager* 장애물 변수
 */
ObstacleManager * ObManagerCreate();

/**
 * @brief 장애물 관리자 동적할당 해제 함수
 * 
 * @param ob 장애물 관리자
 */
void Delete_ObManager(ObstacleManager * ob);

/**
 * @brief 가장 가까운 장애물을 반환해주는 함수
 * 
 * @param ob 장애물 관리자
 * @param p 기준으로 삼을 플레이어 변수
 * @return Obstacle 가장 가까운 장애물
 */
Obstacle obstacleClosest(ObstacleManager * ob,Player * p);

/**
 * @brief 장애물의 텍스쳐를 설정해준다.
 * 
 * @param text texture 구조체를 넣어준다.
 */
void setObstacleTexture(Texture text);

/**
 * @brief 설정해둔 ObstacleData 반환한다.
 * 
 * @return ObstacleData* 관련 배열 상수 반환
 */
ObstacleData * getObstacle();



#endif

