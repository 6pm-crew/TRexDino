#include <stdlib.h>
#include "player.h"
#include "raylib.h"
#include "main.h"
#include "obstacle.h"

enum playerDisplayType {                                                        // 플레이어 상태 플래그
    PLAYER_ALIVE,
    PLAYER_ALIVE_LAY,
    PLAYER_DEAD
};
static Texture texture;                                                         // 사용할 텍스쳐
const int INTERVAL = TARGET_FPS / 8;                                            // 플레이어 애니메이션 변수
extern bool isGameOver;                                                         // 게임 오버 플래그
extern bool game_debug;                                                         // 게임 디버그 온/오프

/**
 * @brief 플레이어 상태 별 스트라이트 위치
 */
const Rectangle textruePlayerData[][2] = {
    {   // PLAYER_ALIVE
        {.x =       1514, .y =  0, .width =  88, .height = 96},
        {.x =  1514 + 88, .y =  0, .width =  88, .height = 96}
    },
    {   // PLAYER_ALIVE_LAY
        {.x =       1866, .y = 40, .width = 118, .height = 56},
        {.x = 1866 + 118, .y = 40, .width = 118, .height = 56}
    },
    {   // PLAYER_DEAD
        {.x =       1689, .y =  0, .width =  88, .height = 96},
        {.x =       1689, .y =  0, .width =  88, .height = 96}
    }
};

/**
 * @brief 플레이어 이동 함수
 * 
 * @param player 
 */
static void player_move(Player *player);

/**
 * @brief 플레이어 출력 함수
 * 
 * @param player 
 */
static void drawPlayer(Player *player);

/**
 * @brief 플레이어 중력 적용 함수
 * 
 * @param player 
 */
static void applyGravity(Player *player);

Player * createPlayer(){
    Player * p = (Player*)malloc(sizeof(Player));
    p->isJump = false;                                   // 점프 플래그
    p->isLaydown = false;                                // 슬라이드 플래그
    p->aabb.x = IDLE_X * SCREEN_WIDTH;                   // T-Rex 히트박스 x값
    p->aabb.y = SCREEN_HEIGHT * IDLE_Y - PLAYER_HEIGHT;  // T-Rex 히트박스 y값
    p->aabb.width = PLAYER_WIDTH;                        // T-Rex 히트박스 너비 
    p->aabb.height = PLAYER_HEIGHT;                      // T-Rex 히트박스 높이
    p->idlePos.y = p->aabb.y;                            // T-Rex 생성 y값

    p->show = drawPlayer;                                // T-Rex 출력
    return p;
}

void resetPlayer(Player *p) {
    p->isJump = false;                                   // 점프 플래그
    p->isLaydown = false;                                // 슬라이드 플래그
    p->aabb.x = IDLE_X * SCREEN_WIDTH;                   // T-Rex 히트박스 x값
    p->aabb.width = PLAYER_WIDTH;                        // T-Rex 히트박스 너비
    p->aabb.height = PLAYER_HEIGHT;                      // T-Rex 히트박스 높이
    p->velocity = (Vector2){0,0};                        // T-Rex 중력 세기
    p->aabb.y = SCREEN_HEIGHT * IDLE_Y  - PLAYER_HEIGHT; // T-Rex 히트박스 y값
    p->idlePos.y = p->aabb.y;                            // T-Rex 생성 y값
}

void setPlayerTexture(Texture text){
    texture = text;
}

void deletePlayer(Player * p){
    free(p);
}

/** 은닉 함수 */
static void drawPlayer(Player *player) {

    static int frameCounter;
    int playerDisplayType = PLAYER_DEAD;
    player->aabb.width = PLAYER_WIDTH;
    player->aabb.height = PLAYER_HEIGHT;
    if(!isGameOver){
        applyGravity(player);
        player_move(player);
        if(!player->isLaydown){
            player->aabb.width = PLAYER_WIDTH;
            player->aabb.height = PLAYER_HEIGHT;
            playerDisplayType = PLAYER_ALIVE;
        }
        else{
            player->aabb.width = PLAYER_WIDTH_LAY;
            player->aabb.height = PLAYER_HEIGHT_LAY;
            playerDisplayType = PLAYER_ALIVE_LAY;
        }
    }

    DrawTexturePro(texture,\
        textruePlayerData[playerDisplayType][frameCounter > INTERVAL],\
        player->aabb,\
        (Vector2){0,0},0,WHITE);
    if(game_debug)
        DrawRectangleRec(player->aabb, Fade(BLUE,0.25f));
    frameCounter++;
    if(frameCounter > INTERVAL *2) frameCounter = 0;
}

static void applyGravity(Player *player) {
    float fallingSpeed = GRAVITY * 3.0f;

    if (player->aabb.y < player->idlePos.y){
        if(!player->isLaydown) player->velocity.y += GRAVITY; //중력 가속도 넣어준다.
        else player->velocity.y += fallingSpeed;
    }
        
    
    const double deltaTime = GetFrameTime();

    player->aabb.y += player->velocity.y * deltaTime; //넓이 값 구한다.

}

static void player_move(Player *player) {
    if (player->aabb.y >= player->idlePos.y + player->isLaydown * (PLAYER_HEIGHT - PLAYER_HEIGHT_LAY)) {
        player->aabb.y = player->idlePos.y;
        player->isJump = false; 
        player->velocity.y = 0;
        player->isLaydown = false;
    }

    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && !player->isJump) {
        player->velocity.y -= PLAYER_JUMP_SPEED;
        player->isJump = true;
    }

    if (IsKeyDown(KEY_DOWN) && !player->isLaydown){
        player->isLaydown = true;
        player->aabb.y += (PLAYER_HEIGHT - PLAYER_HEIGHT_LAY); //엎드렸을 경우 위치 조정값
    }
}
