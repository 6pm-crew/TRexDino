#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include "raylib.h"
#include "obstacle.h"
#include "player.h"

#define QUEUEELEMENT Obstacle
#include "queuetype.h"


#define OBSTACLE_MOVE_SPEED 10
#define OBSTACLE_MOVE_SPEED_MUL 0.1
typedef struct ObstacleManager{
    int timePass;
    struct size
    {
        int width;
        int height;
    }size;
    QueueType *obstacles;
    void (*show)(struct ObstacleManager * ob);
    Obstacle (*closest)();
    float moveSpeed;
}ObstacleManager;


ObstacleManager * ObManagerCreate(int x_size,int y_size);

void Delete_ObManager(ObstacleManager * ob);

Obstacle obstacleClosest(ObstacleManager * ob,Player * p);

#endif

