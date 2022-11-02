#include "raylib.h"
#include "player.h"
#include "main.h"
#include "obstacle_manager.h"

/** 땅이 이동한 총 거리 */
static float temp;

/**
 * @brief 배경화면를 그린다.
 * 
 * @param texture 사용할 텍스쳐
 * @param speed 이동 속도
 */
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
