#include "obstacle.h"
#include "raylib.h"
#include <stdlib.h>


#include <math.h>

double sigmoid(double x) {
     double result;
     result = 1 / (1 + exp(-x));
     return result;
}



Obstacle Obstacle_create(int x_size,int y_size){
    Obstacle p = {
        .x_size = x_size,
        .y_size = y_size,
        .make = obstacle_make,
        .aabb = {
            .x = (float)x_size * OBSTACLE_IDLE_X_MULT,
            .y = (float)y_size * OBSTACLE_IDLE_Y_MULT,
            .height = OBSTACLE_SIZE_Y,
            .width = OBSTACLE_SIZE_X
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