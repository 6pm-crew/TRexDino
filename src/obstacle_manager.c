#include "obstacle_manager.h"

#define QUEUETYPE_IMPLEMENTATION
#include "queuetype.h"
#include "raylib.h"
#include <stdlib.h>

static float time_ms;
static int spawn_delay = 30;
static int type_odd = 2;

static void ObManager_show(ObstacleManager * ob);
static void update_time(ObstacleManager * ob);
static void create_obstacle(ObstacleManager * ob);
static void update_obstacle(ObstacleManager * ob);



int getGap(ObstacleManager * ob, float speed);


const ObstacleData obstacleData[] = {
    {{446,0,34,72},12,0,SMALL_CATUS},
    {{480,0,68,72},12,0,SMALL_CATUS},
    {{548,0,102,72},12,0,SMALL_CATUS},
    {{652,0,50,102},12,0,BIG_CATUS},
    {{702,0,100,102},12,0,BIG_CATUS},
    {{802,0,150,102},12,0,BIG_CATUS},
    {{260,0,92,82},15,8.5,PTERODACTYL}//352
};



static Texture texture;
ObstacleManager * ObManagerCreate(int x_size,int y_size){
    ObstacleManager * ob = (ObstacleManager *)malloc(sizeof(ObstacleManager));
    ob->size.width = x_size;
    ob->size.height = y_size;
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