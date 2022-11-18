#ifndef OBSTABLE_TYPE_H
#define OBSTABLE_TYPE_H
#include "raylib.h"

typedef struct Obstacle{
    int type;                                  // 장애물 종류
    int index;                                 // 장애물 종류 인덱스
    Rectangle aabb;                            // 히트박스
}Obstacle;

#define QUEUEELEMENT Obstacle
#include "queuetype.h"

enum Obstacle_pos{                             // 장애물 높이 정보
    OBSTACLE_GROUND,
    OBSTACLE_MIDDLE,
    OBSTACLE_SKY 
};
enum ObstacleDataType{                         // `ObstacleData` 종류
    SMALL_CATUS,
    BIG_CATUS,
    PTERODACTYL
};

/**
 * @brief 장애물 매니저 관련 클래스(구조체)
 * 
 */
typedef struct ObstacleManager{
    int timePass;                              // 누적 시간 (점수)
    QueueType *obstacles;                      // 장애물 저장 큐
    float moveSpeed;                           // 장애물 이동 속도
    void (*show)(struct ObstacleManager * ob); // 장애물 출력 포인터 함수
}ObstacleManager;

/**
 * @brief 스프라이트 장애물 구역 저장 관련 구조체
 * 
 */
typedef struct ObstacleData{
    Rectangle data;                            // 장애물 장애물 위치
    float minGap;                              // 장애물 생성 딜레이
    float minSpeed;                            // 장애물 생성 최소 속도
    int type;                                  // 장애물 타입 -> `ObstacleDataType` 참조
}ObstacleData;
#endif