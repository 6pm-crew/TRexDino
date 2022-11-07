
#include "player.h"
#include "raylib.h"
#include "main.h"
#include "obstacle.h"

#include <stdlib.h>

/**
 * @brief 플레이어 이동 함수
 * 
 * @param player 
 */
static void player_move(Player *player);

/**
 * @brief 플레이어 표시 함수
 * 
 * @param player 
 */
static void DrawPlayer(Player *player);

/**
 * @brief 플레이어에게 중력을 가하는 함수
 * 
 * @param player 
 */
static void ApplyGravity(Player *player);

/** 사용할 텍스쳐*/
static Texture texture;

/** 플레이어 애니메이션에 사용할 변수*/
const int INTERVAL = TARGET_FPS / 8;

/**
 * @brief 플레이어의 스트라이트 위치
 * 
 */
const Rectangle textruePlayerData[][2] = {
    {
        {.x = 1514,.y = 0,.width = 88,.height = 96},
        {.x = 1514 + 88,.y = 0,.width = 88,.height = 96}
    },
    {
        {.x = 1866,.y = 40,.width = 118,.height = 56},
        {.x = 1866 + 118,.y = 40,.width = 118,.height = 56},
    },
    {
        {.x = 1689,.y = 0,.width = 88,.height = 96},
        {.x = 1689,.y = 0,.width = 88,.height = 96}
    }
};

enum PlayerDisplayType {
    PLAYER_ALIVE,
    PLAYER_ALIVE_LAY,
    PLAYER_DEAD
};

extern bool isGameOver;
extern bool game_debug;

Player * createPlayer(){
    Player * p = (Player*)malloc(sizeof(Player));
    p->isJump = false;
    p->isLaydown = false;
    p->aabb.x = IDLE_X * SCREEN_WIDTH;
    p->aabb.width = PLAYER_WIDTH;
    p->aabb.height = PLAYER_HEIGHT;

    p->aabb.y = SCREEN_HEIGHT * IDLE_Y  - PLAYER_HEIGHT;
    p->idle_pos.y = p->aabb.y;

    p->show = DrawPlayer;
    return p;
}

void resetPlayer(Player *p) {
    p->isJump = false;
    p->isLaydown = false;
    p->aabb.x = IDLE_X * SCREEN_WIDTH;
    p->aabb.width = PLAYER_WIDTH;
    p->aabb.height = PLAYER_HEIGHT;
    p->velocity = (Vector2){0,0};
    p->aabb.y = SCREEN_HEIGHT * IDLE_Y  - PLAYER_HEIGHT;
    p->idle_pos.y = p->aabb.y;
}

void setPlayerTexture(Texture text){
    texture = text;
}

void DeletePlayer(Player * p){
    free(p);
}

/** 은닉 함수*/
static void DrawPlayer(Player *player) {

    static int frameCounter;
    int playerDisplayType = PLAYER_DEAD;
    if(!isGameOver){
        ApplyGravity(player);
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
    };

    DrawTexturePro(texture,\
        textruePlayerData[playerDisplayType][frameCounter > INTERVAL],\
        player->aabb,\
        (Vector2){0,0},0,WHITE);
    if(game_debug)
        DrawRectangleRec(player->aabb, Fade(BLUE,0.25f));
    frameCounter++;
    if(frameCounter > INTERVAL *2) frameCounter = 0;
}

static void ApplyGravity(Player *player) {
    float fallingSpeed = GRAVITY * 3.0f;

    if (player->aabb.y < player->idle_pos.y){
        if(!player->isLaydown) player->velocity.y += GRAVITY; //중력 가속도 넣어준다.
        else player->velocity.y += fallingSpeed;
    }
        
    
    const double deltaTime = GetFrameTime();

    player->aabb.y += player->velocity.y * deltaTime; //넓이 값 구한다.

}


static void player_move(Player *player) {
    if (player->aabb.y >= player->idle_pos.y + player->isLaydown * (PLAYER_HEIGHT - PLAYER_HEIGHT_LAY)) {
        player->aabb.y = player->idle_pos.y;
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
