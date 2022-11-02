#ifndef OBSTABLE_TYPE_H
#define OBSTABLE_TYPE_H
#include "raylib.h"

typedef struct Obstacle{
    /** 장애물 종류 */
    int type;
    /** 장애물 종류 인덱스 */
    int index;
    /** bounding box */
    Rectangle aabb;
}Obstacle;

#define QUEUEELEMENT Obstacle
#include "queuetype.h"

/** 장애물 높이 위치*/
enum Obstacle_pos{
    OBSTACLE_GROUND,
    OBSTACLE_MIDDLE,
    OBSTACLE_SKY 
};

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

#endif