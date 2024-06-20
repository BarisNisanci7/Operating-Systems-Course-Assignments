#include <stdio.h>
#include <stdbool.h>

#define P 8   // Number of processes (job types)
#define R 5   // Number of resources (Computers, Desks, Printers, Conference Rooms, Projectors)

// Function prototypes
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]);
bool isSafe(int processes[], char ** jobTypes, const int avail[], int max[][R], int allot[][R]);
void printResult(int safeSeq[P], char** jobTypes);

int main() {
    int process_ids[] = {0, 1, 2, 3, 4, 5, 6, 7};  // Job types IDs
    char** jobTypes = (char*[]){"Software Developer", "Graphic Designer", "Sales Representative", "HR Manager", "Accountant", "Marketing Analyst", "Customer Support Specialist", "Project Manager"};

    // Available instances of resources. Find minimum resources required for each job type.
    int availableResources[R] = {5, 0, 5, 0, 2};

    int allot[P][R] = {
            {0, 2, 0, 0, 0},   // Software Developer
            {1, 0, 1, 0, 0},   // Graphic Designer
            {1, 1, 0, 1, 0},   // Sales Representative
            {0, 1, 1, 0, 0},   // HR Manager
            {1, 1, 0, 0, 0},   // Accountant
            {1, 2, 0, 1, 1},   // Marketing Analyst
            {1, 2, 1, 0, 0},   // Customer Support Specialist
            {0, 1, 0, 1, 0}    // Project Manager
    };

    int max[P][R] = {
            {10, 4, 1, 0, 0},  // Software Developer
            {5, 1, 8, 0, 1},   // Graphic Designer
            {1, 1, 2, 1, 2},   // Sales Representative
            {2, 2, 1, 0, 1},   // HR Manager
            {2, 1, 1, 1, 0},   // Accountant
            {2, 2, 3, 3, 2},   // Marketing Analyst
            {5, 8, 1, 0, 0},   // Customer Support Specialist
            {1, 2, 1, 2, 2}    // Project Manager
    };

    // Check system state
    if (!isSafe(process_ids, jobTypes, availableResources, max, allot)) {
        printf("System is not in a safe state.\n");
    }

    return 0;
}

// Barış Nişancı 20070001019

// Function to calculate need matrix
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

// Print result
void printResult(int safeSeq[P], char** jobTypes) {
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    
    printf("\n\nOrder of job types: ");
    for (int i = 0; i < P; i++)
        printf("\n%d. %s", i + 1, jobTypes[safeSeq[i]]);
    printf("\n");
}

// Function to find the system is in a safe state or not
bool isSafe(int process_ids[], char** jobTypes, const int availableResources[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculateNeed(need, max, allot);

    bool finish[P] = {false};
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = availableResources[i];

    int safeSeq[P];
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int j = 0; j < R; j++)
                        work[j] += allot[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    printResult(process_ids, jobTypes);
    return true;
}

