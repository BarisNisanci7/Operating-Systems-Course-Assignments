#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int find_index(int arr[], int head) {
    int i, pos = 0;
    for (i = 0; i < SIZE; i++) {
        if (arr[i] <= head && arr[i + 1] >= head) {
            pos = i;
        }
    }
    return pos;
}

// Barış NİŞANCI 20070001019

// total_seek_count is total distance traveled in disk during the operation. It has the same function in all functions

void FCFS(int temp[], int head) {
    int total_seek_count = 0;

    // Printing the array
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", temp[i]);
    }

    // Traversing the disk requests sequentially
    for (int i = 0; i < SIZE; i++) { // We start at first index to last index
        int seek_count = abs(head - temp[i]);   // Calculate seek distance
        printf("\nhead=%d-->%d  seek_count=%d", head, temp[i], seek_count);
        total_seek_count +=  seek_count; // Accumulate total seek count
        head = temp[i]; // Move head to the current track
    }

    // Output the total seek count
    printf("\n\nTotal number of seek operations: %d\n\n", total_seek_count);
}


void SSTF(int temp[], int head) {
    int total_seek_count = 0;
    int visited[SIZE] = {0}; // We should keep the visited indexes

    // Traverse all disk requests
    for (int i = 0; i < SIZE; i++) {
        int min_distance = INT_MAX; // I have to find min distance, I used INT_MAX because disk range may change
        int min_index = -1; // This keeps index of minimum distance between head

        for (int j = 0; j < SIZE; j++) {
            if (abs(head - temp[j]) < min_distance && visited[j] == 0) { // If next distance of index is smaller than previous and unvisited
                min_distance = abs(head - temp[j]);
                min_index = j; // Change minimum index
            }
        }

        printf("\nhead=%d-->%d    seek_count=%d", head, temp[min_index], min_distance);

        total_seek_count += abs(head - temp[min_index]); // Update seek count
        head = temp[min_index];  // Move head to the nearest track
        visited[min_index] = 1;
    }

    printf("\n\nTotal number of seek operations: %d\n\n", total_seek_count);
}


void Scan(int temp[], int head, int rotation) {
    sort(temp, SIZE); // Sorting the disk
    int pos = find_index(temp, head); // Keeps smaller but biggest index than head
    int total_seek_count = 0;

    for (int i = 0; i < SIZE; i++) {
        printf("%d  ", temp[i]);
    }
    printf("\n\n");

    switch (rotation) { // Choice for left or right
        case 1: // Left
            for (int i = pos; i >= 0; i--) { // Indexes goes through zero
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i]; // Move head to the current track
            }

            // I used translate for this sentence because my english is broken.
            if (pos != SIZE - 1) { // If the start position is not at the position of the last element of the array, the header is moved to the beginning of the array.
                total_seek_count += head;
                printf("head=%d-->0    seek_count=%d\n", head, head);
                head = 0; // Move head to the start of the disk
            }

            for (int i = pos + 1; i < SIZE; i++) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            break;

        case 2: // Right
            for (int i = pos + 1; i < SIZE; i++) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }

            if (pos != -1) { // If the pos is greater than -1
                total_seek_count += (199 - head);
                printf("head=%d-->199    seek_count=%d\n", head, abs(199 - head));
                head = 199; // Move head to the end of the disk
            }

            for (int i = pos; i >= 0; i--) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            break;

        default:
            printf("Incorrect Rotation Value, please enter (1 for Left & 2 for Right)");
    }

    printf("\nTotal seek count: %d\n\n", total_seek_count);
}


void Cscan(int temp[], int head, int rotation) {
    sort(temp, SIZE);
    int pos = find_index(temp, head);
    int total_seek_count = 0;

    for (int i = 0; i < SIZE; i++) {
        printf("%d  ", temp[i]);
    }
    printf("\n\n");

    switch (rotation) {
        case 1: // Left
            for (int i = pos; i >= 0 ; i--) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }

            printf("head=%d-->0     seek_count=%d\n", head, head);
            total_seek_count += head;
            head = 199;
            printf("head=0-->199     Jump!\n");

            for (int i = SIZE - 1; i > pos; i--) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            break;

        case 2: // Right
            for (int i = pos + 1; i < SIZE; i++) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }

            printf("head=%d-->199    seek_count=%d\n", head, abs(199 - head));
            total_seek_count += abs(199 - head);
            head = 0;
            printf("head=199-->0     Jump!\n");

            for (int i = 0; i <= pos; i++) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            break;

        default:
            printf("Incorrect Rotation Value, please enter (1 for Left & 2 for Right)");
    }

    printf("\nTotal seek count: %d\n\n", total_seek_count);
}


void Look(int temp[], int head, int rotation) {
    sort(temp, SIZE);
    int pos = find_index(temp, head);
    int total_seek_count = 0;

    for (int i = 0; i < SIZE; i++) {
        printf("%d  ", temp[i]);
    }
    printf("\n\n");

    switch (rotation) {
        case 1:
            for (int i = pos; i >= 0 ; i--) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }

            for (int i = pos + 1; i < SIZE; i++) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            break;

        case 2:
            for (int i = pos + 1; i < SIZE; i++) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }

            for (int i = pos; i >= 0; i--) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            break;

        default:
            printf("Incorrect Rotation Value, please enter (1 for Left & 2 for Right)");
    }

    printf("\nTotal seek count: %d\n\n", total_seek_count);
}


void Clook(int temp[], int head, int rotation) {
    sort(temp, SIZE);
    int pos = find_index(temp, head);
    int total_seek_count = 0;

    for (int i = 0; i < SIZE; i++) {
        printf("%d  ", temp[i]);
    }
    printf("\n\n");

    switch (rotation) {
        case 1:
            for (int i = pos; i >= 0 ; i--) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            printf("head=%d-->%d     Jump!\n",head, temp[SIZE - 1]);
            head = temp[SIZE - 1];
            for (int i = SIZE - 2; i > pos; i--) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            break;

        case 2:
            for (int i = pos + 1; i < SIZE; i++) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            printf("head=%d-->%d     Jump!\n",head, temp[0]);
            head = temp[0];
            for (int i = 1; i <= pos; i++) {
                printf("head=%d-->%d    seek_count=%d\n", head, temp[i], abs(head - temp[i]));
                total_seek_count += abs(head - temp[i]);
                head = temp[i];
            }
            break;

        default:
            printf("Incorrect Rotation Value, please enter (1 for Left & 2 for Right)");
    }

    printf("\nTotal seek count: %d\n", total_seek_count);
}

int main() {
    //int arr[SIZE] = {176, 79, 34, 60, 92, 11, 41, 114};
    int arr[SIZE] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    //int head = 53;
    int direction;
    int choice;
    int i = 1;
    
    printf("----Disk Management Algorithms----\n");
    while (i != 0) {
        printf("\n\nSelect The Disk Management Algorithms You Want To Use: \n\n");
        printf("First Come First Serve--1 \n");
        printf("Shortest Seek Time First--2 \n");
        printf("Scan(Elevator)--3 \n");
        printf("C-Scan(Circular Scan)--4 \n");
        printf("Look--5 \n");
        printf("C-Look(Circular Look)--6 \n");
        printf("Exit--0\n");

        printf("Choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1: FCFS(arr, head); break;
            case 2: SSTF(arr, head); break;
            case 3: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Scan(arr, head, direction);
                    break;
            case 4: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Cscan(arr, head, direction); break;
            case 5: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Look(arr, head, direction); break;
            case 6: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Clook(arr, head, direction); break;
            case 0: i = 0; break;
            default: printf("\n Error--\n");
        }
    }
    return 0;
}
