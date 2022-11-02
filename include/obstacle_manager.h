#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include "raylib.h"
#include "player.h"

typedef struct Obstacle
{
    int x_size, y_size;
    int Ob_size, Ob_pos, Ob_count, Ob_type;
    int type;
    int index;
    // void (*make)(int x_size,int y_size);
    void (*move)();
    Rectangle aabb;
}Obstacle;

#define QUEUEELEMENT Obstacle
#include "queuetype.h"


#define OBSTACLE_MOVE_SPEED 6
#define OBSTACLE_MOVE_SPEED_MUL 0.1

#define SCORE_MULTIPLIER 0.001

#define OBSTACLE_IDLE_X_MULT 0.98f
#define OBSTACLE_IDLE_Y_MULT 0.7f

#define OBSTACLE_SIZE_X 20.0f
#define OBSTACLE_SIZE_Y 20.0f

/** 장애물 총 종류 */
#define OBSTACLE_TOTAL_COUNT 3 


typedef struct ObstacleManager{
    int timePass;
    struct size{
        int width;
        int height;
    }size;
    QueueType *obstacles;
    void (*show)(struct ObstacleManager * ob);
    Obstacle (*closest)();
    float moveSpeed;
}ObstacleManager;

typedef struct ObstacleData{
    Rectangle data;
    float minGap;
    float minSpeed;
    int type;
}ObstacleData;


enum ObstacleDataType{
    SMALL_CATUS,
    BIG_CATUS,
    PTERODACTYL
};
enum ObstacleDataIndex{
    SMALL_CATUS_1,
    SMALL_CATUS_2,
    SMALL_CATUS_3,
    BIG_CATUS_1,
    BIG_CATUS_2,
    BIG_CATUS_3,
    BIRD
};

ObstacleManager * ObManagerCreate(int x_size,int y_size);

void Delete_ObManager(ObstacleManager * ob);

Obstacle obstacleClosest(ObstacleManager * ob,Player * p);

void setObstacleTexture(Texture text);

ObstacleData * getObstacle();


enum Obstacle_size{
    OBSTACLE_SMALL,
    OBSTACLE_BIG
};

enum Obstacle_pos{
    OBSTACLE_GROUND,
    OBSTACLE_MIDDLE,
    OBSTACLE_SKY 
};

enum Obstacle_type{
    OBSTACLE_CATUS,
    OBSTACLE_BIRD
};


Obstacle Obstacle_create();

Obstacle obstacle_make(ObstacleManager * ob, int score);

Obstacle obstacleClosest(ObstacleManager * ob,Player * p);

void obsatcle_update();


#endif

