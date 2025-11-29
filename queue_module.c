#include "queue_module.h"
#include <stdlib.h>
#include <stdio.h>

HealthQueue* createQueue(int capacity) {
    if (capacity <= 0) {
        printf("Error: Queue capacity must be positive\n");
        return NULL;
    }
    
    HealthQueue *queue = (HealthQueue*)malloc(sizeof(HealthQueue));
    if (queue == NULL) {
        printf("Error: Memory allocation failed for queue\n");
        return NULL;
    }
    
    queue->data = (HealthReading*)malloc(capacity * sizeof(HealthReading));
    if (queue->data == NULL) {
        printf("Error: Memory allocation failed for queue data\n");
        free(queue);
        return NULL;
    }
    
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    
    printf("[Queue] Initialized with capacity: %d\n", capacity);
    return queue;
}

void destroyQueue(HealthQueue *queue) {
    if (queue == NULL) return;
    free(queue->data);
    free(queue);
    printf("[Queue] Destroyed\n");
}

int isQueueEmpty(const HealthQueue *queue) {
    if (queue == NULL) return 1;
    return (queue->size == 0);
}

int isQueueFull(const HealthQueue *queue) {
    if (queue == NULL) return 1;
    return (queue->size == queue->capacity);
}

int enqueue(HealthQueue *queue, HealthReading reading) {
    if (queue == NULL) {
        printf("Error: Queue is NULL\n");
        return 0;
    }
    
    if (isQueueFull(queue)) {
        printf("[Queue] Error: Queue is full (capacity: %d)\n", queue->capacity);
        return 0;
    }
    
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = reading;
    queue->size++;
    
    return 1;
}

int dequeue(HealthQueue *queue, HealthReading *reading) {
    if (queue == NULL || reading == NULL) {
        printf("Error: Invalid queue or reading pointer\n");
        return 0;
    }
    
    if (isQueueEmpty(queue)) {
        printf("[Queue] Error: Queue is empty\n");
        return 0;
    }
    
    *reading = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    
    return 1;
}

void displayQueue(const HealthQueue *queue) {
    if (queue == NULL || isQueueEmpty(queue)) {
        printf("[Queue] Empty\n");
        return;
    }
    
    printf("[Queue] Size: %d/%d\n", queue->size, queue->capacity);
    
    int current = queue->front;
    for (int i = 0; i < queue->size; i++) {
        printf("  [%d] ", i + 1);
        displayHealthReading(queue->data[current]);
        printf("\n");
        current = (current + 1) % queue->capacity;
    }
}

int getQueueSize(const HealthQueue *queue) {
    if (queue == NULL) return 0;
    return queue->size;
}

int getQueueCapacity(const HealthQueue *queue) {
    if (queue == NULL) return 0;
    return queue->capacity;
}
