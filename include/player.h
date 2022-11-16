#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

/** gravity size constants */
#define GRAVITY 50

/** jump function related constants */
#define FALL_LONG_MULT 0.85f // dummy
#define FALL_SHORT_MULT 1.55f

/** player jump speed constants */
#define PLAYER_JUMP_SPEED 1400

/** player basic position constants */
#define IDLE_X 0.1f
#define IDLE_Y 0.7f

/** player size constants */
#define PLAYER_WIDTH 88.0f
#define PLAYER_HEIGHT 96.0f
#define PLAYER_WIDTH_LAY 118
#define PLAYER_HEIGHT_LAY 56


/**
 * @brief player related struct
 */
typedef struct Player{
    Rectangle aabb;                     // 정렬된 bounding box의 위치 & 크기
    Vector2 idlePos;                    // 플레이어 초기 설정 좌표
    Vector2 velocity;                   // 플레이어 힘 크기값
    bool isJump;                        // 플레이어 점프 상태
    bool isLaydown;                     // 플레이어 업드리기 상태
    void (*move)(struct Player * p);    // 플레이어 이동 포인터 함수
    void (*show)(struct Player * p);    // 플레이어 표시 포인터 함수
}Player;

/**
 * @brief Generate T-Rex | reset target ->
 * @brief  isJump, isLaydown,
 * @brief  aabb.x, aabb.y, 
 * @brief  aabb.width, aabb.height,
 * @brief  idlePos.y, show
 * 
 * @return Player* 
 */
Player * createPlayer();

/**
 * @brief 플레이어를 초기화.
 * 
 * @return Player* 
 */
void resetPlayer(Player *p);

/**
 * @brief 플레이어를 동적할당 해제한다.
 * 
 * @param p 
 */
void deletePlayer(Player * p);

/**
 * @brief 플레이어에 사용할 이미지를 불러온다.
 * 
 * @param text 
 */
void setPlayerTexture(Texture text);
#endif