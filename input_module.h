#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
int heartRate;
int bloodPressure;
int spo2;
} HealthReading;

int readHealthData(FILE *file, HealthReading *reading);
void displayHealthReading(HealthReading reading);
int validateHealthReading(HealthReading reading);

#endif