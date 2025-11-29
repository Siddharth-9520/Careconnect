#ifndef HEAP_MODULE_H
#define HEAP_MODULE_H

#include "input_module.h"

typedef enum {
    NORMAL = 1,
    WARNING = 2,
    CRITICAL = 3
} PriorityLevel;

typedef struct {
    HealthReading reading;
    PriorityLevel priority;
    int timestamp;
} PriorityNode;

typedef struct {
    PriorityNode *heap;
    int size;
    int capacity;
    int counter;
} PriorityHeap;

PriorityHeap* createHeap(int capacity);
void destroyHeap(PriorityHeap *heap);
void initializeHeap(PriorityHeap *heap);
PriorityLevel calculatePriority(HealthReading reading);
int insertReading(PriorityHeap *heap, HealthReading reading);
int extractMaxPriority(PriorityHeap *heap, PriorityNode *node);
void displayHeap(const PriorityHeap *heap);
int isHeapEmpty(const PriorityHeap *heap);
int isHeapFull(const PriorityHeap *heap);
void heapifyUp(PriorityHeap *heap, int index);
void heapifyDown(PriorityHeap *heap, int index);
int getHeapSize(const PriorityHeap *heap);
int getHeapCapacity(const PriorityHeap *heap);

#endif
