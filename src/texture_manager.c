#include "raylib.h"
#include "player.h"
#include "main.h"
#include "obstacle_manager.h"
#include "texture_manager.h"

/** 땅이 이동한 총 거리 */
static float temp;

extern bool isGameOver;

void drawBackground(Texture2D texture,float speed){
    if(!isGameOver) temp += speed;
    
    DrawTexturePro(\
        texture,
        (Rectangle) {.x = temp,.y = 102,.width = SCREEN_WIDTH,.height = 28},\
        (Rectangle) {.x = 0,.y = SCREEN_HEIGHT * IDLE_Y - 25,.width = SCREEN_WIDTH,.height = 28},\
        (Vector2){0,0},0,WHITE);
    DrawTexturePro(\
        texture,
        (Rectangle) {.x = texture.width + temp,.y = 102,.width = SCREEN_WIDTH,.height = 28},\
        (Rectangle) {.x = 0,.y = SCREEN_HEIGHT * IDLE_Y  - 25,.width = SCREEN_WIDTH,.height = 28},\
        (Vector2){0,0},0,WHITE);
}


void gameOverBackround(Texture2D texture){
    const Rectangle bounds = { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT };
    Rectangle textureSource = {.x = 954,.y = 29,.width = 381,.height = 21};
    DrawTexturePro(\
        texture,
        textureSource,\
        (Rectangle) {.x = SCREEN_WIDTH * 0.5f - textureSource.width/2,.y = SCREEN_HEIGHT * 0.5f - textureSource.height / 2,.width = 381,.height = 21},\
        (Vector2){0,0},0,WHITE);
}