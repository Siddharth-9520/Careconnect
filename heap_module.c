#include "heap_module.h"
#include <stdlib.h>
#include <stdio.h>

PriorityHeap* createHeap(int capacity) {
    if (capacity <= 0) {
        printf("Error: Heap capacity must be positive\n");
        return NULL;
    }
    
    PriorityHeap *heap = (PriorityHeap*)malloc(sizeof(PriorityHeap));
    if (heap == NULL) {
        printf("Error: Memory allocation failed for heap\n");
        return NULL;
    }
    
    heap->heap = (PriorityNode*)malloc(capacity * sizeof(PriorityNode));
    if (heap->heap == NULL) {
        printf("Error: Memory allocation failed for heap data\n");
        free(heap);
        return NULL;
    }
    
    heap->capacity = capacity;
    heap->size = 0;
    heap->counter = 0;
    
    printf("[Heap] Initialized with capacity: %d\n", capacity);
    return heap;
}

void destroyHeap(PriorityHeap *heap) {
    if (heap == NULL) return;
    free(heap->heap);
    free(heap);
    printf("[Heap] Destroyed\n");
}

void initializeHeap(PriorityHeap *heap) {
    if (heap == NULL) return;
    heap->size = 0;
    heap->counter = 0;
    printf("[Heap] Re-initialized\n");
}

PriorityLevel calculatePriority(HealthReading reading) {
    if (reading.heartRate > 120 || reading.bloodPressure > 160 || reading.spo2 < 90) {
        return CRITICAL;
    }
    else if (reading.heartRate > 100 || reading.bloodPressure > 140 || reading.spo2 < 95) {
        return WARNING;
    }
    else {
        return NORMAL;
    }
}

int isHeapEmpty(const PriorityHeap *heap) {
    if (heap == NULL) return 1;
    return (heap->size == 0);
}

int isHeapFull(const PriorityHeap *heap) {
    if (heap == NULL) return 1;
    return (heap->size == heap->capacity);
}

int insertReading(PriorityHeap *heap, HealthReading reading) {
    if (heap == NULL) {
        printf("[Heap] Error: Heap is NULL\n");
        return 0;
    }
    
    if (isHeapFull(heap)) {
        printf("[Heap] Error: Heap is full (capacity: %d)\n", heap->capacity);
        return 0;
    }
    
    PriorityNode newNode;
    newNode.reading = reading;
    newNode.priority = calculatePriority(reading);
    newNode.timestamp = heap->counter++;
    
    heap->heap[heap->size] = newNode;
    heapifyUp(heap, heap->size);
    heap->size++;
    
    return 1;
}

int extractMaxPriority(PriorityHeap *heap, PriorityNode *node) {
    if (heap == NULL || node == NULL) {
        printf("[Heap] Error: Invalid heap or node pointer\n");
        return 0;
    }
    
    if (isHeapEmpty(heap)) {
        printf("[Heap] Error: Heap is empty\n");
        return 0;
    }
    
    *node = heap->heap[0];
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    
    if (heap->size > 0) {
        heapifyDown(heap, 0);
    }
    
    return 1;
}

void heapifyUp(PriorityHeap *heap, int index) {
    if (heap == NULL || index <= 0) return;
    
    int parent = (index - 1) / 2;
    
    int shouldSwap = (heap->heap[index].priority > heap->heap[parent].priority) ||
                    (heap->heap[index].priority == heap->heap[parent].priority && 
                     heap->heap[index].timestamp < heap->heap[parent].timestamp);
    
    if (shouldSwap) {
        PriorityNode temp = heap->heap[index];
        heap->heap[index] = heap->heap[parent];
        heap->heap[parent] = temp;
        heapifyUp(heap, parent);
    }
}

void heapifyDown(PriorityHeap *heap, int index) {
    if (heap == NULL || index >= heap->size) return;
    
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;
    
    if (leftChild < heap->size) {
        int leftLarger = (heap->heap[leftChild].priority > heap->heap[largest].priority) ||
                        (heap->heap[leftChild].priority == heap->heap[largest].priority && 
                         heap->heap[leftChild].timestamp < heap->heap[largest].timestamp);
        if (leftLarger) largest = leftChild;
    }
    
    if (rightChild < heap->size) {
        int rightLarger = (heap->heap[rightChild].priority > heap->heap[largest].priority) ||
                         (heap->heap[rightChild].priority == heap->heap[largest].priority && 
                          heap->heap[rightChild].timestamp < heap->heap[largest].timestamp);
        if (rightLarger) largest = rightChild;
    }
    
    if (largest != index) {
        PriorityNode temp = heap->heap[index];
        heap->heap[index] = heap->heap[largest];
        heap->heap[largest] = temp;
        heapifyDown(heap, largest);
    }
}

void displayHeap(const PriorityHeap *heap) {
    if (heap == NULL || isHeapEmpty(heap)) {
        printf("[Heap] Empty\n");
        return;
    }
    
    printf("[Heap] Size: %d/%d\n", heap->size, heap->capacity);
    
    for (int i = 0; i < heap->size; i++) {
        const char* priorityStr = (heap->heap[i].priority == CRITICAL) ? "CRITICAL" : 
                                 (heap->heap[i].priority == WARNING) ? "WARNING" : "NORMAL";
        
        printf("  [%d] [%s] ", i + 1, priorityStr);
        displayHealthReading(heap->heap[i].reading);
        printf("\n");
    }
}

int getHeapSize(const PriorityHeap *heap) {
    if (heap == NULL) return 0;
    return heap->size;
}

int getHeapCapacity(const PriorityHeap *heap) {
    if (heap == NULL) return 0;
    return heap->capacity;
}
