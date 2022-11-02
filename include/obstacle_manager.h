#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include "raylib.h"
#include "player.h"

/**
 * @brief 장애물 구조체
 * 
 * 
 */
typedef struct Obstacle{
    /** */
    int x_size, y_size;
    /** */
    int type;
    /** */
    int index;
    /** */
    Rectangle aabb;
    void (*move)();
}Obstacle;

/** 큐 데이터 타입 Obstacle로 설정*/
#define QUEUEELEMENT Obstacle
#include "queuetype.h"

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
 * @brief 장애물 매니저 관련 클래스(구조체)
 * 
 */
typedef struct ObstacleManager{
    /** 지난 시간*/
    int timePass;
    /** 장애물을 저장하고 있는 큐*/
    QueueType *obstacles;
    /** 장애물 이동 속도*/
    float moveSpeed;
    /** 장애물 출력 포인터 함수 */
    void (*show)(struct ObstacleManager * ob);
}ObstacleManager;

/**
 * @brief 스프라이트에서의 장애물 구역 저장 관련 구조체
 * 
 */
typedef struct ObstacleData{
    /** 장애물 장애물 위치*/
    Rectangle data;
    /** 이 장애물의 등장 딜레이*/
    float minGap;
    /** 장애물 등장 최소 속도*/
    float minSpeed;
    /** 장애물 타입 자세한 내용은 `ObstacleDataType` 참조*/
    int type;
}ObstacleData;

/**
 * @brief `ObstacleData` 종류
 * 
 */
enum ObstacleDataType{
    SMALL_CATUS,
    BIG_CATUS,
    PTERODACTYL
};

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

/** 장애물 높이 위치*/
enum Obstacle_pos{
    OBSTACLE_GROUND,
    OBSTACLE_MIDDLE,
    OBSTACLE_SKY 
};

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


/**
 * @brief 가장 가까운 장애물을 반환해주는 함수
 * 
 * @param ob 장애물 관리자
 * @param p 기준으로 삼을 플레이어 변수
 * @return Obstacle 가장 가까운 장애물
 */
Obstacle obstacleClosest(ObstacleManager * ob,Player * p);

#endif

