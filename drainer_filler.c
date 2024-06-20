#include <stdio.h>
#include <pthread.h>

#define MAX_WATER_LEVEL 100
#define MIN_WATER_LEVEL 0
#define FILL_INCREMENT 10

int water_level = MIN_WATER_LEVEL;
pthread_mutex_t water_level_mutex = PTHREAD_MUTEX_INITIALIZER;

// Baris Nisanci 20070001019

void *filler() {

    if(water_level <= 20) {
        while(water_level < MAX_WATER_LEVEL) {
            pthread_mutex_lock(&water_level_mutex);
            water_level += FILL_INCREMENT;
            printf("Filling: Water Level = %d\n", water_level);
            pthread_mutex_unlock(&water_level_mutex);
        }
        pthread_exit(NULL);
    }
}

void *drainer() {
    
    pthread_mutex_lock(&water_level_mutex);
    if (water_level > MIN_WATER_LEVEL) {
        water_level -= FILL_INCREMENT;
        printf("Draining: Water Level = %d\n", water_level);
    }
    pthread_mutex_unlock(&water_level_mutex);
    pthread_exit(NULL);
}

int main() {

    pthread_t filler_thread, drainer_thread;

    for(int i = 0; i < 100; i++) {
        pthread_create(&filler_thread, NULL, filler, NULL);
        pthread_create(&drainer_thread, NULL, drainer, NULL);
        pthread_join(filler_thread, NULL);
        pthread_join(drainer_thread, NULL);
        
    }

    return 0;
}