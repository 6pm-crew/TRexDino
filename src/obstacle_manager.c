#include "obstacle_manager.h"

#define QUEUETYPE_IMPLEMENTATION
#include "queuetype.h"

#include <stdlib.h>

static float time_ms;
static int spawn_delay = 30;
static int type_odd = 2;

static void ObManager_show(ObstacleManager * ob);
static void update_time(ObstacleManager * ob);
static void create_obstacle(ObstacleManager * ob);
static void update_obstacle(ObstacleManager * ob);

const Rectangle catusData[] = {
    {446,0,34,72}
};


static Texture texture;
ObstacleManager * ObManagerCreate(int x_size,int y_size){
    ObstacleManager * ob = (ObstacleManager *)malloc(sizeof(ObstacleManager));
    ob->size.width = x_size;
    ob->size.height = y_size;
    ob->obstacles = create_queue(10);
    ob->show = ObManager_show;
    ob->closest = obstacleClosest;
    ob->timePass = 0;
    ob->moveSpeed = 5.0f;
    return ob;
}

void Delete_ObManager(ObstacleManager * ob){
    free(ob);
    destroy_queue(ob->obstacles);
}

static void ObManager_show(ObstacleManager * ob){
    update_time(ob);
    create_obstacle(ob);
    update_obstacle(ob);
}

static void update_time(ObstacleManager * ob){
    float temp = GetFrameTime();
    ob->moveSpeed += temp * OBSTACLE_MOVE_SPEED_MUL;
    TraceLog(LOG_DEBUG,"%f",ob->moveSpeed);
    time_ms += temp;
    if(time_ms > 0.1) {
        ob->timePass++;
        time_ms = 0;
    }
}

static void create_obstacle(ObstacleManager * ob){

    if(spawn_delay == 0){
        spawn_delay = GetRandomValue(3,15) + ob->timePass;
    }
    if(spawn_delay <= ob->timePass){
        queue_enque(ob->obstacles,Obstacle_create(ob->size.width,ob->size.height));
        spawn_delay = 0;
    }

}
// 선인장 왼쪽 시작 446, 선인장 상단 시작 0
// 높이 72 너비 34
static void update_obstacle(ObstacleManager * ob){
    int n = (ob->obstacles->rear + ob->obstacles->total - ob->obstacles->front) % ob->obstacles->total;
    int tfront = ob->obstacles->front,trear = ob->obstacles->rear;
    int i = 0;
    while(i != n){
        ob->obstacles->data[tfront].aabb.x -= ob->moveSpeed;
        DrawRectangleRec(ob->obstacles->data[tfront].aabb, Fade(BLUE,0.2f));
        DrawTexturePro(texture,\
            catusData[0],\
            ob->obstacles->data[tfront].aabb,\
            (Vector2){0,0},0,WHITE);
        i++;
        tfront = (tfront + 1) % ob->obstacles->total;

    }
    if(ob->obstacles->data[ob->obstacles->front].aabb.x < 0){
        queue_deque(ob->obstacles,NULL);
    }
}

Obstacle obstacleClosest(ObstacleManager * ob,Player * p){
    Obstacle * arr;
    int length = toArray(ob->obstacles,&arr);
    for(int i = 0;i < length;i++){
        if(arr[i].aabb.x + arr[i].aabb.width > ob->size.width * IDLE_X ){
            // TraceLog(LOG_DEBUG,"tracking %d",i);
            return arr[i];
        }
    }
    free(arr);
}


void setObstacleTexture(Texture text){
    texture = text;
}

Rectangle getObstacle(){
    return catusData[0];
}