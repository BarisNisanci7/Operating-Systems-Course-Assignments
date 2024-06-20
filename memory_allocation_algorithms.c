#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCK_SIZE 11
#define PROCESS_SIZE_RANGE 501 // 600 - 100 + 1

// Structure to represent a memory block
typedef struct {
    int size;
    int isAllocated;
	int allocatedProcessId;
} MemoryBlock;

// Structure to represent a process
typedef struct {
    int size;
} Process;

void printAllocationTable(MemoryBlock blocks[], int numBlocks) {
    printf("-------------------------------------------------\n");
    printf("| Block ID\t| Block Size\t| Process ID\t|\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("| B%-7d\t", i + 1); // Block ID
        printf("| %-12d\t", blocks[i].size); // Block Size
        if (blocks[i].isAllocated) {
            printf("| P%-9d\t|\n", blocks[i].allocatedProcessId + 1); // Process ID
        } else {
            printf("| %-12s\t|\n", "-"); // No Process ID
        }
    }
    printf("-------------------------------------------------\n");
}


void printProcessTable(Process processes[], int numProcesses) {
    printf("-------------------------------\n");
    printf("| Process ID\t| Process Size\t|\n");
    printf("-------------------------------\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("| P%-9d\t", i + 1); // Process ID
        printf("| %-12d\t|\n", processes[i].size); // Process Size
    }
    printf("-------------------------------\n");
}

void firstFit(MemoryBlock blocks[], int numBlocks, Process processes[], int numProcesses) {
    for(int i = 0; i < numProcesses; i++) {
        for(int j = 0; j < numBlocks; j++) {
            if(!blocks[j].isAllocated && blocks[j].size >= processes[i].size) {
                blocks[j].isAllocated = 1;
                blocks[j].allocatedProcessId = i;
                break;
            }
        }
    }
}

// Baris Nisanci 20070001019

void worstFit(MemoryBlock blocks[], int numBlocks, Process processes[], int numProcesses) {

    for(int i = 0; i < numProcesses; i++) {
        int worstFitIndex = -1;
        for(int j = 0; j < numBlocks; j++) {
            if (worstFitIndex == -1) {
                if(!blocks[j].isAllocated && blocks[j].size >= processes[i].size) {
                    worstFitIndex = j;
                    blocks[j].allocatedProcessId = i;
                    blocks[j].isAllocated = 1;
                }
            } else if(blocks[worstFitIndex].size < blocks[j].size && !blocks[j].isAllocated && processes[i].size <= blocks[j].size){
                    blocks[worstFitIndex].allocatedProcessId = NULL;
                    blocks[worstFitIndex].isAllocated = 0;
                    worstFitIndex = j;
                    blocks[j].allocatedProcessId = i;
                    blocks[j].isAllocated = 1;

            } 
        }
    }
}



void generateMemoryBlocks(MemoryBlock blocks[], int blockSizes[], int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        blocks[i].size = blockSizes[rand() % MAX_BLOCK_SIZE];
        blocks[i].isAllocated = 0; // Initially, no block is allocated
    }
}

void generateProcesses(Process processes[], int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        processes[i].size = (rand() % PROCESS_SIZE_RANGE) + 100; // Process size between 100KB and 600KB
    }
}


// Allocation algorithms will go here

int main() {
    srand(time(0)); // Seed for random number generation
    
    int blockSizes[MAX_BLOCK_SIZE] = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600};
    int numBlocks = rand() % 4 + 5; // 5-8 blocks
    MemoryBlock blocks[numBlocks];

    int numProcesses = rand() % 5 + 4; // 4-8 processes
    Process processes[numProcesses];

    generateMemoryBlocks(blocks, blockSizes, numBlocks);
    generateProcesses(processes, numProcesses);

    printf("Output 1\n");
    printf("\nFirst Fit Allocation:\n");
    printf("Process Table:\n");
    printProcessTable(processes, numProcesses);
    printf("\nMemory Block Allocation Table:\n");
    generateMemoryBlocks(blocks, blockSizes, numBlocks);
    firstFit(blocks, numBlocks, processes, numProcesses);
    printAllocationTable(blocks, numBlocks);

    printf("\n\nOutput 2\n\n");
    generateMemoryBlocks(blocks, blockSizes, numBlocks); // I reseted the table
    printf("Worst Fit Allocation:\n");
    printf("Process Table:\n");
    printProcessTable(processes, numProcesses);
    printf("\nMemory Block Allocation Table:\n");
    worstFit(blocks, numBlocks, processes, numProcesses);
    printAllocationTable(blocks, numBlocks);

    printf("\n\nOutput 3\n\n");
    generateMemoryBlocks(blocks, blockSizes, numBlocks); // I reseted the table
    printf("Worst Fit Allocation:\n");
    printf("Process Table:\n");
    printProcessTable(processes, numProcesses);
    printf("\nMemory Block Allocation Table:\n");
    worstFit(blocks, numBlocks, processes, numProcesses);
    printAllocationTable(blocks, numBlocks);

  return 0;
}
