#ifndef QUEUETYPE_H
#define QUEUETYPE_H
#include <stdlib.h>

#ifndef QUEUEELEMENT
typedef struct Queue_node{
    int num;
}QueueNode;
#define QUEUEELEMENT int
#endif

typedef struct queue_type{
    int front;
    int rear;
    int total;
    QUEUEELEMENT * data;
}QueueType;

QueueType * create_queue(int n);

void destroy_queue(QueueType * q);

int queue_is_full(QueueType * queue);

int queue_is_empty(QueueType * queue);

QueueType * create_AQueue();

int queue_enque(QueueType * queue,QUEUEELEMENT data);

int queue_deque(QueueType * queue,QUEUEELEMENT * resultValue);

int toArray(QueueType * queue,Obstacle ** ob);

#endif

#ifdef QUEUETYPE_IMPLEMENTATION
QueueType * create_queue(int n){
    QueueType * result = (QueueType *)malloc(sizeof(QueueType));
    result->data = (QUEUEELEMENT *)malloc(sizeof(QUEUEELEMENT) * n);
    result->total = n;
    result->front = 0;
    result->rear = 0;
    return result;
}

void destroy_queue(QueueType * q){
    free(q->data);
    free(q);
}

int queue_is_full(QueueType * queue){
    return (queue->rear + 1 % queue->total ) == queue->front;
}

int queue_is_empty(QueueType * queue){
    return queue->front == queue->rear;
}

QueueType * create_AQueue(){
    QueueType * result = (QueueType *)malloc(sizeof(QueueType));
    result->rear = 0;
    result->front = 0;
    return result;
}
int queue_enque(QueueType * queue,QUEUEELEMENT data){
    if(queue_is_full(queue)){
        return 0;
    }
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear+1)%queue->total;
    return 1;
}

int queue_deque(QueueType * queue,QUEUEELEMENT * resultValue){
    if(queue_is_empty(queue)) return 0;
    if(resultValue != NULL)
        *resultValue = queue->data[queue->front];
    queue->front = (queue->front+1)%queue->total;
    return 1;
}

int toArray(QueueType * queue,Obstacle ** ob){
    int n = (queue->rear + queue->total - queue->front) % queue->total;
    int tfront = queue->front; int trear = queue->rear;
    if(n == 0) {
        *ob = NULL;
        return 0;
    }
    Obstacle * result = (Obstacle *)malloc(sizeof(Obstacle) * n);
    int i = 0;

    while(i != n){
        result[i++] = queue->data[tfront]; 
        tfront = (tfront + 1) % queue->total;

    }
    *ob = result;
    return n; 
}
#endif