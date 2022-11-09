#include "raylib.h"
#include "player.h"
#include "main.h"
#include "obstacle_manager.h"
#include "texture_manager.h"

/** 땅이 이동한 총 거리 */
static float temp;

extern bool isGameOver;

const Rectangle number[10] = {
    {.x =  954, .y = 2, .width = 18, .height = 23},     // 0
    {.x =  976, .y = 2, .width = 18, .height = 23},     // 1
    {.x =  994, .y = 2, .width = 18, .height = 23},     // 2
    {.x = 1014, .y = 2, .width = 18, .height = 23},     // 3
    {.x = 1034, .y = 2, .width = 18, .height = 23},     // 4
    {.x = 1054, .y = 2, .width = 18, .height = 23},     // 5
    {.x = 1074, .y = 2, .width = 18, .height = 23},     // 6
    {.x = 1094, .y = 2, .width = 18, .height = 23},     // 7
    {.x = 1114, .y = 2, .width = 18, .height = 23},     // 8
    {.x = 1134, .y = 2, .width = 18, .height = 23},     // 9
};

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
    Rectangle textureSource = {.x = 954,.y = 29,.width = 382,.height = 22};
    DrawTexturePro(\
        texture,
        textureSource,\
        (Rectangle) {.x = SCREEN_WIDTH * 0.5f - textureSource.width/2,.y = SCREEN_HEIGHT * 0.5f - textureSource.height / 2,.width = 382,.height = 22},\
        (Vector2){0,0},0,WHITE);
}

void DrawNumber(Texture2D texture, Vector2 position, int n) {
    DrawTexturePro(\
        texture,
        number[n],\
        (Rectangle) {.x = position.x, .y = position.y, .width = 18, .height = 23},\
        (Vector2){0,0},0, WHITE);
}