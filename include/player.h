#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

/** 중력 크기 */
#define GRAVITY 50

/** 점프 상승 관련 계수*/
#define FALL_LONG_MULT 0.85f //현재 사용하지 않음
#define FALL_SHORT_MULT 1.55f

/** 플레이어 점프 속도 관련 상수*/
#define PLAYER_JUMP_SPEED 1400

/** 플레이어 기존 위치 비율*/
#define IDLE_X 0.1f
#define IDLE_Y 0.7f

/** 플레이어 크기 설정 상수 */
#define PLAYER_WIDTH 88.0f
#define PLAYER_HEIGHT 96.0f

#define PLAYER_WIDTH_LAY 118
#define PLAYER_HEIGHT_LAY 56


/**
 * @brief 플레이어 관련 구조체
 * 
 */
typedef struct Player{
    /** 정렬된 bounding Box의 위치와 크기*/
    Rectangle aabb;
    /** 플레이어의 초기 설정 좌표*/
    Vector2 idle_pos;
    /** 플레이어의 힘의 크기*/
    Vector2 velocity;
    /** 플레이어의 점프 여부*/
    bool isJump;
    /** 플레이어가 누워있는지에 대한 여부*/
    bool isLaydown;
    /** 플레이어 이동 포인터 함수*/
    void (*move)(struct Player * p);
    /** 플레이어 표시 포인터 함수*/
    void (*show)(struct Player * p);
}Player;

/**
 * @brief 플레이어를 생성한다.
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
void DeletePlayer(Player * p);

/**
 * @brief 플레이어에 사용할 이미지를 불러온다.
 * 
 * @param tex 
 */
void setPlayerTexture(Texture tex);
#endif