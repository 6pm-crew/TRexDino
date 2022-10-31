#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

#define GRAVITY 50

#define FALL_LONG_MULT 0.85f
#define FALL_SHORT_MULT 1.55f


#define IDLE_X 0.1f
#define IDLE_Y 0.7f

#define PLAYER_WIDTH 15.0f
#define PLAYER_HEIGHT 15.0f
#define PLAYER_JUMP_SPEED 300

typedef struct Player{
    Rectangle aabb;
    Vector2 idle_pos;
    Vector2 velocity;
    bool isJump;
    void (*move)(struct Player * p);
    void (*show)(struct Player * p);
}Player;

Player * create(float x_size, float y_size);

void DeletePlayer(Player * p);
#endif