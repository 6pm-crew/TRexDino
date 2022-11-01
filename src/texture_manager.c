#include "raylib.h"
#include "player.h"
#include "main.h"
#include "obstacle_manager.h"

//0,113 땅 시작
static float temp;
void drawBackground(Texture2D texture,float speed){
    temp += speed;
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

// void unloadTexture(){
//     UnloadTexture(texture);
// }