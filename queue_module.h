#ifndef QUEUE_MODULE_H
#define QUEUE_MODULE_H

#include "input_module.h"

typedef struct {
    HealthReading *data;
    int front;
    int rear;
    int size;
    int capacity;
} HealthQueue;

HealthQueue* createQueue(int capacity);
void destroyQueue(HealthQueue *queue);
int enqueue(HealthQueue *queue, HealthReading reading);
int dequeue(HealthQueue *queue, HealthReading *reading);
int isQueueEmpty(const HealthQueue *queue);
int isQueueFull(const HealthQueue *queue);
void displayQueue(const HealthQueue *queue);
int getQueueSize(const HealthQueue *queue);
int getQueueCapacity(const HealthQueue *queue);

#endif
