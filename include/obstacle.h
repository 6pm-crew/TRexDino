#ifndef OBSTACLE_H
#define OBSTACLE_H

#define SCORE_MULTIPLIER 0.001
typedef struct Obstacle
{
    int x_size, y_size;
    int Ob_size, Ob_pos, Ob_count, Ob_type;
    void (*make)(int x_size,int y_size);
    void (*update)();

}Obstacle;

/*
    개수: 0 -3 
    위치: 0 - 3
    크기: big or small
*/

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

Obstacle * Obstacle_create(int x_size,int y_size);

void obstacle_make();
void obsatcle_update();

#endif