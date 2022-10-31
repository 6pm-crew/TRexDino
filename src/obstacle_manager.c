#include "obstacle_manager.h"

#define QUEUETYPE_IMPLEMENTATION
#include "queuetype.h"

#include <stdlib.h>

static float time_ms;
static int spawn_delay = 30;
static int type_odd = 2;

void _ObManager_show(ObstacleManager * ob);
void _update_time(ObstacleManager * ob);
void _create_obstacle(ObstacleManager * ob);
void _update_obstacle(ObstacleManager * ob);

ObstacleManager * ObManagerCreate(int x_size,int y_size){
    ObstacleManager * ob = (ObstacleManager *)malloc(sizeof(ObstacleManager));
    ob->obstacles = create_queue(100);
    ob->show = _ObManager_show;
    ob->timePass = 0;
    ob->size.x = x_size;
    ob->size.y = y_size;
    return ob;
}

void Delete_ObManager(ObstacleManager * ob){
    free(ob);
    destroy_queue(ob->obstacles);
}

void _ObManager_show(ObstacleManager * ob){
    _update_time(ob);
    _create_obstacle(ob);
    _update_obstacle(ob);
}

void _update_time(ObstacleManager * ob){
    time_ms += GetFrameTime();
    if(time_ms > 0.1) {
        ob->timePass++;
        time_ms = 0;
    }
}

void _create_obstacle(ObstacleManager * ob){

    if(spawn_delay == 0){
        spawn_delay = GetRandomValue(5,20) + ob->timePass;
        
    }
    if(spawn_delay <= ob->timePass){
        queue_enque(ob->obstacles,Obstacle_create(ob->size.x,ob->size.y));
        TraceLog(LOG_DEBUG,"%d",spawn_delay);
        spawn_delay = 0;
    }

}

void _update_obstacle(ObstacleManager * ob){
    int i = ob->obstacles->front;

    for(i; i < ob->obstacles->rear; i++){
        ob->obstacles->data[i].aabb.x -= OBSTACLE_MOVE_SPEED;
        DrawRectangleRec(ob->obstacles->data[i].aabb, BLUE);
    }

    if(ob->obstacles->data[ob->obstacles->front].aabb.x < 0){
        queue_deque(ob->obstacles,NULL);
    }
}