
#include "player.h"
#include "raylib.h"
#include "main.h"

#include <stdlib.h>
void player_move(Player *player);
void DrawPlayer(Player *player);
// static const Vector2 idle_pos;
static double startJump;
static Texture texture;

const int INTERVAL = TARGET_FPS / 8;
Player * create(float x_size, float y_size){
    Player * p = (Player*)malloc(sizeof(Player));
    p->isJump = false;

    p->aabb.x = IDLE_X * x_size;
    p->aabb.width = PLAYER_WIDTH;
    p->aabb.height = PLAYER_HEIGHT;

    p->aabb.y = y_size * IDLE_Y  - PLAYER_HEIGHT;
    p->idle_pos.y = p->aabb.y;

    p->show = DrawPlayer;
    return p;
}

void ApplyGravity(Player *player) {
    TraceLog(LOG_DEBUG,"%f",player->aabb.y);
    if (player->aabb.y < player->idle_pos.y) //점프 상태
        player->velocity.y += GRAVITY; //중력 가속도 넣어준다.

    const double deltaTime = GetFrameTime();

    player->aabb.y += player->velocity.y * deltaTime; //넓이 값 구한다.
}


//좌측 1514 높이 시작 96

// 너비 88

void DrawPlayer(Player *player) {
    static int frameCounter;
    ApplyGravity(player);
    player_move(player);
    DrawTexturePro(texture,\
        (Rectangle){.x = 1514 + (frameCounter > INTERVAL) * 88,.y = 0,.width = 88,.height = 96},\
        player->aabb,\
        (Vector2){0,0},0,WHITE);
    frameCounter++;
    if(frameCounter > INTERVAL *2) frameCounter = 0;
    // DrawRectangleRec(player->aabb, Fade(RED,0.25f));
}



// 가속도 속도 그래프 넓이 = 이동한 거리

void player_move(Player *player) {
    // printf("%f\n",player->velocity.y);
    if (IsKeyDown(KEY_SPACE) && !player->isJump) {
        player->velocity.y -= PLAYER_JUMP_SPEED;
        player->isJump = true;
    }

    if (player->aabb.y >= player->idle_pos.y) {
        player->aabb.y = player->idle_pos.y;
        player->isJump = false; 
    }
}

void setPlayerTexture(Texture text){
    texture = text;
}

void DeletePlayer(Player * p){
    free(p);
}