#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

/** gravity size constants */
#define GRAVITY             50

/** jump function related constants */
#define FALL_LONG_MULT      0.85f // dummy
#define FALL_SHORT_MULT     1.55f

/** player jump speed constants */
#define PLAYER_JUMP_SPEED   1400

/** player basic position constants */
#define IDLE_X              0.1f
#define IDLE_Y              0.7f

/** player size constants */
#define PLAYER_WIDTH        88.0f
#define PLAYER_HEIGHT       96.0f
#define PLAYER_WIDTH_LAY    118
#define PLAYER_HEIGHT_LAY   56


/**
 * @brief player related struct
 */
typedef struct Player{
    Rectangle aabb;                     // 정렬된 bounding box의 위치 & 크기
    Vector2 idlePos;                    // 초기 설정 좌표
    Vector2 velocity;                   // 힘의 크기값
    bool isJump;                        // 점프 플래그
    bool isLaydown;                     // 업드리기 플래그
    void (*move)(struct Player * p);    // 이동 포인터 함수
    void (*show)(struct Player * p);    // 표시 포인터 함수
}Player;

/**
 * @brief T-Rex 생성 | 작업 타켓 ->
 * isJump, isLaydown, aabb.x, aabb.y, aabb.witdh, aabb.height, idlePos.y, show
 * 
 * @return Player* 
 */
Player * createPlayer();

/**
 * @brief T-Rex 초기화 | 초기화 타켓 ->
 * isJump, isLayDown, aabb.x. aabb.y, aabb.witdh, aabb.height, velocity, idlePos.y
 * 
 * @return Player* 
 */
void resetPlayer(Player *p);

/**
 * @brief T-Rex 동적 메모리 해제
 * 
 * @param p 
 */
void deletePlayer(Player * p);

/**
 * @brief T-Rex 텍스쳐 로드
 * 
 * @param text 
 */
void setPlayerTexture(Texture text);
#endif