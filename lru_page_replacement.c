#include <stdio.h>

void initialize(int frames[], int pageLastReferenced[], int numberOfFrames) {
    for (int i = 0; i < numberOfFrames; ++i) {
        if (frames != NULL) {
            frames[i] = -1;
        }
        if (pageLastReferenced != NULL) {
            pageLastReferenced[i] = 0;
        }
    }
}


int findLRU(const int pageLastReferenced[], int numberOfFrames) {
    int minimum = pageLastReferenced[0], minIndex = 0;
    for(int i = 1; i < numberOfFrames; ++i) {
        if(pageLastReferenced[i] < minimum) {
            minimum = pageLastReferenced[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Barış Nişancı 20070001019

void processPageReference(const int pages[], int frames[], int pageLastReferenced[], int numberOfFrames, int numberOfPages) {
    int counter = 0, faults = 0;
    for (int i = 0; i < numberOfPages; ++i) {
        int page = pages[i];
        int j;
        for (j = 0; j < numberOfFrames; ++j) {
            if (frames[j] == page) {
                counter++;
                pageLastReferenced[j] = counter;
                break;
            }
        }

        // If no page in frames
        if (j == numberOfFrames) {
            faults++;
            int minIndex = findLRU(pageLastReferenced, numberOfFrames);
            frames[minIndex] = page;
            pageLastReferenced[minIndex] = ++counter;
        }

        printf("\n");
        for (int k = 0; k < numberOfFrames; ++k) {
            printf("%d\t", frames[k]);
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}


int main() {
    int numberOfFrames, numberOfPages;
    printf("Enter number of frames: ");
    scanf("%d", &numberOfFrames);
    int frames[numberOfFrames];

    printf("Enter number of pages: ");
    scanf("%d", &numberOfPages);
    int pages[numberOfPages];

    printf("Enter reference string: ");
    for(int i = 0; i < numberOfPages; ++i) {
        scanf("%d", &pages[i]);
    }

    initialize(frames, NULL, numberOfFrames);
    int pageLastReferenced[numberOfFrames];
    initialize(NULL, pageLastReferenced, numberOfFrames);

    processPageReference(pages, frames, pageLastReferenced, numberOfFrames, numberOfPages);

    return 0;
}