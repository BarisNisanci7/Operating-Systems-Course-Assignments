#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TRUE 1
#define N 10

sem_t mutex;
sem_t empty;
sem_t full;

int buffer[N] = {0};
int in = 0;
int out = 0;

// Baris Nisanci 20070001019

void print_buffer() {
    for (int i = 0; i < N; i++) {
        printf("%d\t",buffer[i]);
    }
    printf("\n\n");
}

void *producer() {
    while(TRUE) {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = 1;
        printf("Producer produced item ,placed on %d.shelf\n", in+1);
        in = (in + 1) % N;

        print_buffer();

        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer() {
    while(TRUE) {
        sem_wait(&full);
        sem_wait(&mutex);

        buffer[out] = 0;
        printf("Consumer consumed item from %d.shelf\n", out+1);
        out = (out + 1) % N;

        print_buffer();

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {

    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    pthread_t threads[N];

    for(int i = 0; i < N; i++) {
         pthread_create(&threads[i], NULL, producer, NULL);
         
    }

    for(int i = 0; i < N; i++) {
         pthread_create(&threads[i], NULL, consumer, NULL);
    }

    
    for(int i = 0; i < N; i++) {
        pthread_join(threads[i],NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}