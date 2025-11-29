#ifndef GRAPH_MODULE_H
#define GRAPH_MODULE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
    char location[100];
} Hospital;

typedef struct {
    int **adjacencyMatrix;
    Hospital *hospitalList;
    int numHospitals;
    int maxHospitals;
    int maxNodes;
} HospitalGraph;

HospitalGraph* createGraph(int maxHospitals, int maxNodes);
void destroyGraph(HospitalGraph *graph);
int addHospital(HospitalGraph *graph, Hospital hospital);
void setDistance(HospitalGraph *graph, int from, int to, int distance);
void findNearestHospital(HospitalGraph *graph, int patientNode, Hospital *nearest, int *distance);
void displayHospitals(const HospitalGraph *graph);
void displayDistanceMatrix(const HospitalGraph *graph);

#endif
