#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include "raylib.h"
#include "obstacle.h"

#define QUEUEELEMENT Obstacle
#include "queuetype.h"


#define OBSTACLE_MOVE_SPEED 10
typedef struct ObstacleManager{
    int timePass;
    Vector2 size;
    QueueType *obstacles;
    void (*show)(struct ObstacleManager * ob);
}ObstacleManager;


ObstacleManager * ObManagerCreate();

void Delete_ObManager(ObstacleManager * ob);

#endif

