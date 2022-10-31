#include "obstacle.h"
#include "raylib.h"
#include <stdlib.h>

static int type_odd = 2;


Obstacle * Obstacle_create(int x_size,int y_size){
    Obstacle * p = (Obstacle *)malloc(sizeof(Obstacle));
    p->x_size = x_size;
    p->y_size = y_size;
    p->make = obstacle_make;
    return p;
}



// 새 400 이상 -> 
// 큰거 3개 200 이상
// 작 2, 큰 1, 작 1, 작 3 0 이상
void obstacle_make(Obstacle *p, int score){
    p->Ob_type = OBSTACLE_CATUS;

    if(score >= 400){
        int temp = GetRandomValue(0,10);
        if(temp > type_odd + (score * SCORE_MULTIPLIER));
    }
        
}