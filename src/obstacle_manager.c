#include <stdlib.h>
#include "obstacle_type.h"
#include "obstacle_manager.h"
#include "obstacle.h"

#include "raylib.h"
#include "main.h"

#define QUEUETYPE_IMPLEMENTATION
#include "queuetype.h"


/** 지나간 ms의 총 크기(0 - 1000ms)*/
static float time_ms;
/** 장애물 생성 지연 시간*/
static int spawn_delay = 30;

/**
 * @brief 장애물 관리자 화면에 표시
 * 
 * @param ob 장애물 관리자
 */
static void ObManager_show(ObstacleManager * ob);

/**
 * @brief 화면 생성에 걸린 시간으로 부터 지난 시간과 속도를 담당하는 함수
 * 
 * @param ob 장애물 관리자
 */
static void update_time(ObstacleManager * ob);

/**
 * @brief 장애물 생성 함수
 * 
 * @param ob 장애물 관리자
 */
static void create_obstacle(ObstacleManager * ob);

/**
 * @brief 장애물을 업데이트하여 그려주는 함수 
 * 
 * @param ob 장애물 관리자
 */
static void update_obstacle(ObstacleManager * ob);

/**
 * @brief 속도의 크기와 장애물의 크기에 따라 지연 시간을 반환하는 함수
 * 
 * @param ob 장애물 관리자
 * @param speed 장애물 이동 속돈
 * @return int 지연시간 
 */
int getGap(ObstacleManager * ob, float speed);

/**
 * @brief 기본 지정된 스프라이트 이미지 위치 와 기본 데이터
 * 
 */
const ObstacleData obstacleData[] = {
    {{446,0,34,72},12,0,SMALL_CATUS},
    {{480,0,68,72},12,0,SMALL_CATUS},
    {{548,0,102,72},12,0,SMALL_CATUS},
    {{652,0,50,102},12,0,BIG_CATUS},
    {{702,0,100,102},12,0,BIG_CATUS},
    {{802,0,150,102},12,0,BIG_CATUS},
    {{260,0,92,82},15,8.5,PTERODACTYL}//352
};

/** 텍스쳐 저장 변수*/
static Texture texture;


ObstacleManager * ObManagerCreate(){
    ObstacleManager * ob = (ObstacleManager *)malloc(sizeof(ObstacleManager));
    ob->obstacles = create_queue(10);
    ob->show = ObManager_show;
    ob->timePass = 0;
    ob->moveSpeed = OBSTACLE_MOVE_SPEED;
    return ob;
}

void Delete_ObManager(ObstacleManager * ob){
    free(ob);
    destroy_queue(ob->obstacles);
}

int getGap(ObstacleManager * ob, float speed) {
    int minGap;
    if(queue_is_empty(ob->obstacles))
        minGap = 0;
    else{
        Obstacle obstacle = ob->obstacles->data[ob->obstacles->front];
        minGap = obstacle.aabb.width * 0.03 * speed + getObstacle()[obstacle.index].minGap;
    }
    int maxGap = minGap * 0.4;
    TraceLog(LOG_DEBUG,"minGap : %d, maxGap: %d",minGap,maxGap);
    return GetRandomValue(maxGap,minGap);
}

void setObstacleTexture(Texture text){
    texture = text;
}

ObstacleData * getObstacle(){
    return obstacleData;
}

/** 은닉 함수*/


static void ObManager_show(ObstacleManager * ob){
    update_time(ob);
    create_obstacle(ob);
    update_obstacle(ob);
}


static void update_time(ObstacleManager * ob){
    float temp = GetFrameTime();
    if(ob->moveSpeed < 13)
        ob->moveSpeed += temp * OBSTACLE_MOVE_SPEED_MUL;
    time_ms += temp;
    if(time_ms > 0.1) {
        ob->timePass++;
        time_ms = 0;
    }
}



static void create_obstacle(ObstacleManager * ob){
    
    if(spawn_delay == 0){
        spawn_delay = getGap(ob,ob->moveSpeed) + ob->timePass;
        printf("%d\n",spawn_delay);
    }
    if(spawn_delay <= ob->timePass){
        Obstacle temp = obstacle_make(ob,ob->moveSpeed);
        queue_enque(ob->obstacles,temp);
        spawn_delay = 0;
    }

}


static void update_obstacle(ObstacleManager * ob){
    int n = (ob->obstacles->rear + ob->obstacles->total - ob->obstacles->front) % ob->obstacles->total;
    int tfront = ob->obstacles->front,trear = ob->obstacles->rear;
    int i = 0;
    while(i != n){
        ob->obstacles->data[tfront].aabb.x -= ob->moveSpeed;
        DrawRectangleRec(ob->obstacles->data[tfront].aabb, Fade(BLUE,0.2f));
        DrawTexturePro(texture,\
            obstacleData[ob->obstacles->data[tfront].index].data,\
            ob->obstacles->data[tfront].aabb,\
            (Vector2){0,0},0,WHITE);
        i++;
        tfront = (tfront + 1) % ob->obstacles->total;

    }
    if(ob->obstacles->data[ob->obstacles->front].aabb.x + ob->obstacles->data[ob->obstacles->front].aabb.width < 0){
        queue_deque(ob->obstacles,NULL);
    }
}

Obstacle * obstacleClosest(ObstacleManager * ob,Player * p){
    Obstacle * arr;
    int length = toArray(ob->obstacles,&arr);
    if(arr == NULL) return NULL;
    for(int i = 0;i < length;i++){
        if(arr[i].aabb.x + arr[i].aabb.width > SCREEN_WIDTH * IDLE_X ){
            free(arr);
            return &(ob->obstacles->data[i + ob->obstacles->front]);
        }
    }
    free(arr);

}
