#include "raylib.h"
#include "main.h"
#include "obstacle_manager.h"
#include "math.h"
#include <stdlib.h>


#include <math.h>
int duplicateObstacleCheck(ObstacleManager * ob,int type);

double sigmoid(double x) {
     double result;
     result = 1 / (1 + exp(-x));
     return result;
}


Obstacle Obstacle_create(int index,int type){
    if(type == SMALL_CATUS || type == BIG_CATUS) index += GetRandomValue(0,2);
    ObstacleData * asdf = getObstacle();

    Obstacle p = {
        .x_size = SCREEN_WIDTH,
        .y_size = SCREEN_HEIGHT,
        .type = type,
        .index = index,
        .aabb = {
            .x = SCREEN_WIDTH * OBSTACLE_IDLE_X_MULT,
            .y = SCREEN_HEIGHT * OBSTACLE_IDLE_Y_MULT - getObstacle()[index].data.height,
            .height = getObstacle()[index].data.height,
            .width = getObstacle()[index].data.width
        }
    };

    return p;
}



// 새 400 이상 -> 
// 큰거 3개 200 이상
// 작 2, 큰 1, 작 1, 작 3 0 이상
Obstacle obstacle_make(ObstacleManager * ob, int score){
    ObstacleData * obstacleData = getObstacle(); 
    int obstacleTypeIndex = GetRandomValue(0,OBSTACLE_TOTAL_COUNT - 1) * 3;

    ObstacleData obsatcleRef = obstacleData[obstacleTypeIndex];
    if(duplicateObstacleCheck(ob,obsatcleRef.type) || ob->moveSpeed < obsatcleRef.minSpeed){
        return obstacle_make(ob,score);
    }
    else{
        return Obstacle_create(obstacleTypeIndex,obsatcleRef.type);
    }
}


int duplicateObstacleCheck(ObstacleManager * ob,int type){
    Obstacle * obstacleArray;
    int count = 0;
    int length = toArray(ob->obstacles,&obstacleArray);
    for(int i = 0; i < length; i++){
        if(obstacleArray[i].type == type) count++;
        if(count >= 2) return 1;
    }
    free(obstacleArray);
    return 0;
}

Obstacle obstacleClosest(ObstacleManager * ob,Player * p){
    Obstacle * arr;
    int length = toArray(ob->obstacles,&arr);
    for(int i = 0;i < length;i++){
        if(arr[i].aabb.x + arr[i].aabb.width > ob->size.width * IDLE_X ){
            return arr[5];
        }
    }
    free(arr);
}



// type: "CACTUS_SMALL"
// height: 35
// minGap: 120
// minSpeed: 0
// multipleSpeed: 4

// type: "CACTUS_LARGE"
// minGap: 120
// minSpeed: 0
// multipleSpeed: 7

// type: "PTERODACTYL"
// minGap: 150
// minSpeed: 8.5
// multipleSpeed: 999
// numFrames: 2
// speedOffset: 0.8




// 700 밤 -> 낮
// 900 낮 -> 밤
// 1400 밤 -> 낮
// 1600 낮 -> 밤


// 2100
// 2300 남 -> 밤
// 2800 밤 -> 낮
// 3000 낮 -> 밤
