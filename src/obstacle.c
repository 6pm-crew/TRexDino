#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "main.h"
#include "math.h"
#include "obstacle_manager.h"

const int obstacleHeightData[] = {  // 지면 높이 정보
    0,                  //ground
    56,                 //middle
    100                 //height
};

/**
 * @brief 출력중인 장애물 개수 확인
 * 
 * @param ob   장애물 관리자
 * @param type 확인하고자 하는 타입 정보
 * @return int 
 */
static int duplicateObstacleCheck(ObstacleManager * ob,int type);

Obstacle Obstacle_create(int index,int type){
    int height_pos = 0;
    if(type == SMALL_CATUS || type == BIG_CATUS) index += GetRandomValue(0,2);
    if(type == PTERODACTYL) height_pos = GetRandomValue(0,2); 
    ObstacleData * asdf = getObstacle();
    
    Obstacle p = {
        .type = type,
        .index = index,
        .aabb = {
            .x = SCREEN_WIDTH * OBSTACLE_IDLE_X_MULT,
            .y = SCREEN_HEIGHT * OBSTACLE_IDLE_Y_MULT - getObstacle()[index].data.height - obstacleHeightData[height_pos],
            .height = getObstacle()[index].data.height,
            .width = getObstacle()[index].data.width
        }
    };

    return p;
}


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

static int duplicateObstacleCheck(ObstacleManager * ob,int type){
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

// 700  밤 -> 낮
// 900  낮 -> 밤
// 1400 밤 -> 낮
// 1600 낮 -> 밤

// 2100
// 2300 남 -> 밤
// 2800 밤 -> 낮
// 3000 낮 -> 밤