#include "graph_module.h"

HospitalGraph* createGraph(int maxHospitals, int maxNodes) {
    if (maxHospitals <= 0 || maxNodes <= 0) {
        printf("Error: Graph parameters must be positive\n");
        return NULL;
    }
    
    HospitalGraph *graph = (HospitalGraph*)malloc(sizeof(HospitalGraph));
    if (graph == NULL) {
        printf("Error: Memory allocation failed for graph\n");
        return NULL;
    }
    
    graph->adjacencyMatrix = (int**)malloc(maxNodes * sizeof(int*));
    if (graph->adjacencyMatrix == NULL) {
        printf("Error: Memory allocation failed for adjacency matrix rows\n");
        free(graph);
        return NULL;
    }
    
    for (int i = 0; i < maxNodes; i++) {
        graph->adjacencyMatrix[i] = (int*)malloc(maxNodes * sizeof(int));
        if (graph->adjacencyMatrix[i] == NULL) {
            printf("Error: Memory allocation failed for adjacency matrix columns\n");
            for (int j = 0; j < i; j++) {
                free(graph->adjacencyMatrix[j]);
            }
            free(graph->adjacencyMatrix);
            free(graph);
            return NULL;
        }
        
        for (int j = 0; j < maxNodes; j++) {
            graph->adjacencyMatrix[i][j] = 999999;
        }
        graph->adjacencyMatrix[i][i] = 0;
    }
    
    graph->hospitalList = (Hospital*)malloc(maxHospitals * sizeof(Hospital));
    if (graph->hospitalList == NULL) {
        printf("Error: Memory allocation failed for hospital list\n");
        for (int i = 0; i < maxNodes; i++) {
            free(graph->adjacencyMatrix[i]);
        }
        free(graph->adjacencyMatrix);
        free(graph);
        return NULL;
    }
    
    graph->maxHospitals = maxHospitals;
    graph->maxNodes = maxNodes;
    graph->numHospitals = 0;
    
    printf("[Graph] Initialized with %d hospitals, %d nodes\n", maxHospitals, maxNodes);
    return graph;
}

void destroyGraph(HospitalGraph *graph) {
    if (graph == NULL) return;
    
    if (graph->adjacencyMatrix != NULL) {
        for (int i = 0; i < graph->maxNodes; i++) {
            free(graph->adjacencyMatrix[i]);
        }
        free(graph->adjacencyMatrix);
    }
    
    free(graph->hospitalList);
    free(graph);
    printf("[Graph] Destroyed\n");
}

int addHospital(HospitalGraph *graph, Hospital hospital) {
    if (graph == NULL) {
        printf("[Graph] Error: Graph is NULL\n");
        return 0;
    }
    
    if (graph->numHospitals >= graph->maxHospitals) {
        printf("[Graph] Error: Hospital limit reached (%d)\n", graph->maxHospitals);
        return 0;
    }
    
    hospital.id = graph->numHospitals;
    graph->hospitalList[graph->numHospitals] = hospital;
    graph->numHospitals++;
    
    printf("[Graph] Added hospital: %s at %s\n", hospital.name, hospital.location);
    return 1;
}

void setDistance(HospitalGraph *graph, int from, int to, int distance) {
    if (graph == NULL) {
        printf("[Graph] Error: Graph is NULL\n");
        return;
    }
    
    if (from < 0 || from >= graph->maxNodes || to < 0 || to >= graph->maxNodes) {
        printf("[Graph] Error: Invalid node indices\n");
        return;
    }
    
    graph->adjacencyMatrix[from][to] = distance;
    graph->adjacencyMatrix[to][from] = distance;
}

void findNearestHospital(HospitalGraph *graph, int patientNode, Hospital *nearest, int *distance) {
    if (graph == NULL || nearest == NULL || distance == NULL) {
        printf("[Graph] Error: Invalid parameters\n");
        return;
    }
    
    if (graph->numHospitals == 0) {
        printf("[Graph] Error: No hospitals in graph\n");
        return;
    }
    
    int minDistance = 999999;
    int nearestIdx = 0;
    
    for (int i = 0; i < graph->numHospitals; i++) {
        if (i != patientNode) {
            int dist = graph->adjacencyMatrix[patientNode][i];
            if (dist < minDistance) {
                minDistance = dist;
                nearestIdx = i;
            }
        }
    }
    
    *nearest = graph->hospitalList[nearestIdx];
    *distance = minDistance;
}

void displayHospitals(const HospitalGraph *graph) {
    if (graph == NULL || graph->numHospitals == 0) {
        printf("[Graph] No hospitals\n");
        return;
    }
    
    printf("[Graph] Hospitals (%d):\n", graph->numHospitals);
    for (int i = 0; i < graph->numHospitals; i++) {
        printf("  [%d] %s - %s\n", 
               graph->hospitalList[i].id,
               graph->hospitalList[i].name,
               graph->hospitalList[i].location);
    }
}

void displayDistanceMatrix(const HospitalGraph *graph) {
    if (graph == NULL) {
        printf("[Graph] Error: Graph is NULL\n");
        return;
    }
    
    printf("[Graph] Distance Matrix (x10 km):\n");
    printf("     ");
    for (int i = 0; i < graph->numHospitals; i++) {
        printf("%6d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->numHospitals; i++) {
        printf("  %d: ", i);
        for (int j = 0; j < graph->numHospitals; j++) {
            if (graph->adjacencyMatrix[i][j] == 999999) {
                printf("   INF ");
            } else {
                printf("%6d ", graph->adjacencyMatrix[i][j]);
            }
        }
        printf("\n");
    }
}
