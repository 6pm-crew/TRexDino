
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

const Rectangle textureAABBData[] = {
    {
        .y = 0,.width = 88,.height = 96
    },
    {
        .y = 40,.width = 118,.height = 56
    }
};

Player * PlayerCreate(){
    Player * p = (Player*)malloc(sizeof(Player));
    p->isJump = false;

    p->aabb.x = IDLE_X * SCREEN_WIDTH;
    p->aabb.width = PLAYER_WIDTH;
    p->aabb.height = PLAYER_HEIGHT;

    p->aabb.y = SCREEN_HEIGHT * IDLE_Y  - PLAYER_HEIGHT;
    p->idle_pos.y = p->aabb.y;

    p->show = DrawPlayer;
    return p;
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
    ApplyGravity(player);
    player_move(player);
    // 출력 구현
    if(!player->isLaydown){
        player->aabb.width = PLAYER_WIDTH;
        player->aabb.height = PLAYER_HEIGHT;
        DrawTexturePro(texture,\
            (Rectangle){.x = 1514 + (frameCounter > INTERVAL) * 88,.y = 0,.width = 88,.height = 96},\
            player->aabb,\
            (Vector2){0,0},0,WHITE);
    }
    else{
        player->aabb.width = PLAYER_WIDTH_LAY;
        player->aabb.height = PLAYER_HEIGHT_LAY;
        player->aabb.y = player->aabb.y + PLAYER_HEIGHT - PLAYER_HEIGHT_LAY;
        DrawTexturePro(texture,\
            (Rectangle){.x = 1866 + (frameCounter > INTERVAL) * 118,.y = 40,.width = 118,.height = 56},\
            player->aabb,\
            (Vector2){0,0},0,WHITE);
    }

    frameCounter++;
    if(frameCounter > INTERVAL *2) frameCounter = 0;
    DrawRectangleRec(player->aabb, Fade(RED,0.25f));
}

static void ApplyGravity(Player *player) {
    float testing = 1.0f;
    if(player->isLaydown) testing = 0.2f; // 떨어지는 속도 조절

    // printf("%d %f\n",player->isLaydown,testing);
    if (player->aabb.y < player->idle_pos.y) //점프 상태
        player->velocity.y += GRAVITY; //중력 가속도 넣어준다.

    const double deltaTime = GetFrameTime();

    player->aabb.y += player->velocity.y * testing * deltaTime; //넓이 값 구한다.
    printf("%f\n",player->velocity.y * testing * deltaTime);
}


static void player_move(Player *player) {

    if (player->aabb.y >= player->idle_pos.y) {
        player->aabb.y = player->idle_pos.y;
        if(player->isJump) player->velocity.y = 0;
        player->isJump = false; 
    }

    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && !player->isJump) {
        player->velocity.y -= PLAYER_JUMP_SPEED;
        player->isJump = true;
    }
    player->isLaydown = IsKeyDown(KEY_DOWN);
}
