#include <stdlib.h>
#include "player.h"
#include "raylib.h"
#include "main.h"
#include "obstacle.h"

/** player display type list */
enum playerDisplayType {
    PLAYER_ALIVE,
    PLAYER_ALIVE_LAY,
    PLAYER_DEAD
};

/** flag and global variable */
static Texture texture;                                      // 사용할 텍스쳐
const int INTERVAL = TARGET_FPS / 8;                         // 플레이어 애니메이션 변수
extern bool isGameOver;                                      // 게임 오버 플래그
extern bool game_debug;                                      // 게임 디버그 온/오프
const Rectangle textruePlayerData[][2] = {                   // T-Rex 상태 별 스트라이트 위치
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

/** protected functions */
/**
 * @brief T-Rex 이동 함수
 * 
 * @param player 
 */
static void movePlayer(Player *player);
/**
 * @brief T-Rex 출력 함수
 * 
 * @param player 
 */
static void drawPlayer(Player *player);
/**
 * @brief T-Rex 중력 적용 함수
 * 
 * @param player 
 */
static void applyGravity(Player *player);

/** player preferences */
Player * createPlayer(){
    Player * p = (Player*)malloc(sizeof(Player));
    p->isJump      = false;
    p->isLaydown   = false;
    p->aabb.x      = IDLE_X * SCREEN_WIDTH;
    p->aabb.y      = SCREEN_HEIGHT * IDLE_Y - PLAYER_HEIGHT;
    p->aabb.width  = PLAYER_WIDTH;
    p->aabb.height = PLAYER_HEIGHT;
    p->idlePos.y   = p->aabb.y;
    p->show = drawPlayer;
    return p;
}
void resetPlayer(Player *p) {
    p->isJump      = false;
    p->isLaydown   = false;
    p->aabb.x      = IDLE_X * SCREEN_WIDTH;
    p->aabb.y      = SCREEN_HEIGHT * IDLE_Y - PLAYER_HEIGHT;
    p->aabb.width  = PLAYER_WIDTH;
    p->aabb.height = PLAYER_HEIGHT;
    p->velocity    = (Vector2){0,0};
    p->idlePos.y   = p->aabb.y;
}
void setPlayerTexture(Texture text){
    texture = text;
}
void deletePlayer(Player * p){
    free(p);
}

/** protected functions */
static void drawPlayer(Player *player) {

    static int frameCounter;
    int playerDisplayType = PLAYER_DEAD;
    player->aabb.width    = PLAYER_WIDTH;
    player->aabb.height   = PLAYER_HEIGHT;
    if(!isGameOver){
        applyGravity(player);
        movePlayer(player);
        if(!player->isLaydown){
            player->aabb.width  = PLAYER_WIDTH;
            player->aabb.height = PLAYER_HEIGHT;
            playerDisplayType   = PLAYER_ALIVE;
        }
        else{
            player->aabb.width  = PLAYER_WIDTH_LAY;
            player->aabb.height = PLAYER_HEIGHT_LAY;
            playerDisplayType   = PLAYER_ALIVE_LAY;
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
static void movePlayer(Player *player) {
    if (player->aabb.y    >= player->idlePos.y + player->isLaydown * (PLAYER_HEIGHT - PLAYER_HEIGHT_LAY)) {
        player->aabb.y     = player->idlePos.y;
        player->isJump     = false; 
        player->velocity.y = 0;
        player->isLaydown  = false;
    }
    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && !player->isJump) {
        player->velocity.y -= PLAYER_JUMP_SPEED;
        player->isJump      = true;
    }
    if (IsKeyDown(KEY_DOWN) && !player->isLaydown){
        player->isLaydown = true;
        player->aabb.y   += (PLAYER_HEIGHT - PLAYER_HEIGHT_LAY); //엎드렸을 경우 위치 조정값
    }
}
