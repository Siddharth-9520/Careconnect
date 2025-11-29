#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_module.h"
#include "queue_module.h"
#include "heap_module.h"
#include "graph_module.h"

#define INPUT_FILE "health_data.txt"
#define QUEUE_CAPACITY 50
#define HEAP_CAPACITY 50
#define MAX_HOSPITALS 10

void setupHospitals(HospitalGraph *graph) {
    Hospital h1 = {0, "Max Hospital", "Dehradun"};
    Hospital h2 = {0, "Apollo Hospital", "New Delhi"};
    Hospital h3 = {0, "AIIMS", "Rishikesh"};
    
    addHospital(graph, h1);
    addHospital(graph, h2);
    addHospital(graph, h3);
    
    setDistance(graph, 0, 1, 250);
    setDistance(graph, 0, 2, 50);
    setDistance(graph, 1, 2, 280);
}

int main(void) {
    printf("\n========================================\n");
    printf("💙 CARECONNECT - ELDER HEALTH MONITORING\n");
    printf("========================================\n\n");
    
    FILE *inputFile = fopen(INPUT_FILE, "r");
    if (inputFile == NULL) {
        printf("❌ Error: Could not open %s\n", INPUT_FILE);
        printf("Please create health_data.txt with format:\n");
        printf("heartRate,bloodPressure,spo2\n");
        printf("Example:\n120,165,88\n95,142,97\n");
        return 1;
    }
    
    HealthQueue *queue = createQueue(QUEUE_CAPACITY);
    PriorityHeap *heap = createHeap(HEAP_CAPACITY);
    HospitalGraph *graph = createGraph(MAX_HOSPITALS, MAX_HOSPITALS);
    
    if (queue == NULL || heap == NULL || graph == NULL) {
        printf("❌ Error: Failed to initialize data structures\n");
        return 1;
    }
    
    setupHospitals(graph);
    
    printf("\n📊 STEP 1: READING HEALTH DATA FROM FILE...\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    HealthReading reading;
    int readCount = 0;
    
    while (readHealthData(inputFile, &reading)) {
        if (enqueue(queue, reading)) {
            printf("✅ Reading %d: HR=%3d | BP=%3d | SpO2=%3d%%\n", 
                   readCount + 1, reading.heartRate, reading.bloodPressure, reading.spo2);
            readCount++;
        } else {
            printf("⚠️  Queue full! Stopping input.\n");
            break;
        }
    }
    
    fclose(inputFile);
    printf("\n📈 Total readings loaded: %d\n\n", readCount);
    
    printf("🔄 STEP 2: TRANSFERRING QUEUE → PRIORITY HEAP...\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int emergencyCount = 0;
    while (!isQueueEmpty(queue)) {
        HealthReading qReading;
        if (dequeue(queue, &qReading)) {
            if (insertReading(heap, qReading)) {
                PriorityLevel priority = calculatePriority(qReading);
                if (priority == CRITICAL) {
                    emergencyCount++;
                    printf("🚨 CRITICAL: HR=%3d | BP=%3d | SpO2=%3d%% [EMERGENCY!]\n", 
                           qReading.heartRate, qReading.bloodPressure, qReading.spo2);
                } else if (priority == WARNING) {
                    printf("⚠️  WARNING: HR=%3d | BP=%3d | SpO2=%3d%%\n", 
                           qReading.heartRate, qReading.bloodPressure, qReading.spo2);
                } else {
                    printf("✅ NORMAL : HR=%3d | BP=%3d | SpO2=%3d%%\n", 
                           qReading.heartRate, qReading.bloodPressure, qReading.spo2);
                }
            }
        }
    }
    
    printf("\n📋 STEP 3: PRIORITY HEAP ANALYSIS...\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Heap Size: %d\n\n", getHeapSize(heap));
    displayHeap(heap);
    
    printf("\n🏥 STEP 4: HOSPITAL ROUTING...\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    displayHospitals(graph);
    printf("\n");
    displayDistanceMatrix(graph);
    
    if (emergencyCount > 0 && graph->numHospitals > 0) {
        Hospital nearest;
        int distance;
        findNearestHospital(graph, 0, &nearest, &distance);
        printf("\n🚑 NEAREST HOSPITAL FOR EMERGENCY:\n");
        printf("   Name: %s\n", nearest.name);
        printf("   Location: %s\n", nearest.location);
        printf("   Distance: %.1f km\n", distance / 10.0);
    }
    
    printf("\n📊 FINAL SUMMARY\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Total Readings: %d\n", readCount);
    printf("Emergencies Detected: %d\n", emergencyCount);
    printf("Heap Capacity: %d/%d\n", getHeapSize(heap), getHeapCapacity(heap));
    printf("\n✅ CARECONNECT SYSTEM RUNNING SUCCESSFULLY!\n\n");
    
    destroyQueue(queue);
    destroyHeap(heap);
    destroyGraph(graph);
    
    return 0;
}
