#include "raylib.h"
#include "obstacle_manager.h"
#include "main.h"
#include <stdlib.h>


#include <math.h>

double sigmoid(double x) {
     double result;
     result = 1 / (1 + exp(-x));
     return result;
}


//TODO: 저거 지우자
Obstacle Obstacle_create(int x_size,int y_size){
    Obstacle p = {
        .x_size = SCREEN_WIDTH,
        .y_size = SCREEN_HEIGHT,
        .make = obstacle_make,
        .aabb = {
            .x = SCREEN_WIDTH * OBSTACLE_IDLE_X_MULT,
            .y = SCREEN_HEIGHT * OBSTACLE_IDLE_Y_MULT - getObstacle().height,
            .height = getObstacle().height,
            .width = getObstacle().width
        }
    };

    return p;
}



// 새 400 이상 -> 
// 큰거 3개 200 이상
// 작 2, 큰 1, 작 1, 작 3 0 이상
void obstacle_make(Obstacle *p, int score){
    // p->Ob_type = OBSTACLE_CATUS;

    // if(score >= 400){
    //     int temp = GetRandomValue(0,10);
    //     if(temp > type_odd + (score * SCORE_MULTIPLIER));
    // }
        
}