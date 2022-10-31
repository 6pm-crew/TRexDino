
#include "player.h"
#include "raylib.h"
#include <stdlib.h>
void player_move(Player *player);
void DrawPlayer(Player *player);
// static const Vector2 idle_pos;
static double startJump;

Player * create(float x_size, float y_size){
    Player * p = (Player*)malloc(sizeof(Player));
    p->isJump = false;

    p->aabb.x = IDLE_X * x_size;
    p->aabb.width = PLAYER_WIDTH;
    p->aabb.height = PLAYER_HEIGHT;

    p->aabb.y = y_size * IDLE_Y;
    p->idle_pos.y = p->aabb.y;

    p->show = DrawPlayer;
    return p;
}

void ApplyGravity(Player *player) {
    if (player->aabb.y < player->idle_pos.y) //점프 상태
        player->velocity.y += GRAVITY; //중력 가속도 넣어준다.

    const double deltaTime = GetFrameTime();

    player->aabb.y += player->velocity.y * deltaTime; //넓이 값 구한다.
}

void DrawPlayer(Player *player) {
    player_move(player);
    ApplyGravity(player);
    DrawRectangleRec(player->aabb, RED);
}



// 가속도 속도 그래프 넓이 = 이동한 거리

void player_move(Player *player) {
    if (IsKeyDown(KEY_SPACE) && !player->isJump) {
        player->isJump = true;

        player->velocity.y -= PLAYER_JUMP_SPEED;
    }

    if (player->aabb.y >= player->idle_pos.y) {
        player->aabb.y = player->idle_pos.y;
        player->isJump = false; 
    }
}

void DeletePlayer(Player * p){
    free(p);
}