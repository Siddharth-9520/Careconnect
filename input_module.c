#include "input_module.h"

int readHealthData(FILE *file, HealthReading *reading) {
    if (file == NULL || reading == NULL) {
        printf("Error: Invalid file or reading pointer\n");
        return 0;
    }
    
    int result = fscanf(file, "%d,%d,%d", 
                       &reading->heartRate, 
                       &reading->bloodPressure, 
                       &reading->spo2);
    
    if (result == 3) {
        if (validateHealthReading(*reading)) {
            return 1;
        } else {
            printf("Warning: Invalid health reading (HR:%d BP:%d SpO2:%d)\n",
                   reading->heartRate, reading->bloodPressure, reading->spo2);
            return 0;
        }
    }
    
    return 0;
}

void displayHealthReading(HealthReading reading) {
    printf("HR: %d bpm | BP: %d mmHg | SpO2: %d%%", 
           reading.heartRate, reading.bloodPressure, reading.spo2);
}

int validateHealthReading(HealthReading reading) {
    if (reading.heartRate < 30 || reading.heartRate > 200) return 0;
    if (reading.bloodPressure < 60 || reading.bloodPressure > 250) return 0;
    if (reading.spo2 < 70 || reading.spo2 > 100) return 0;
    return 1;
}
