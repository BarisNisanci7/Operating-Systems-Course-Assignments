#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
 
#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num + 4)%N  // LEFT == 2+4 = 6 mod 5 = 1 
#define RIGHT (ph_num + 1)%N // 2+1 = 3 mod 5 = 3 
 
sem_t mutex;
sem_t S[N];
 
void * philospher(void *num);
void take_fork(int);
void put_fork(int);
void test(int);
 
int state[N];
int phil_num[N]={0, 1, 2, 3, 4};
 
// Baris Nisanci 20070001019

int main()
{
   int i;
    pthread_t threads[N];
    sem_init(&mutex, 0, 1);
 
    for (i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);
    }
 
    for (i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philospher, &phil_num[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
 
    for (i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
}
 
void *philospher(void *num)
{
    while(1)
    {
      sleep(1);
      take_fork(*(int*)num);
      sleep(0);                    // Delete this code makes philosophers eat sequential
      put_fork(*(int*)num); 
    }
}
 
void take_fork(int ph_num)
{
   sem_wait(&mutex);
   state[ph_num] = HUNGRY;
   printf("Philosopher %d is Hungry\n", ph_num + 1);
   test(ph_num);
   sem_post(&mutex);
   sem_wait(&S[ph_num]);
}
 
void test(int ph_num)
{
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[ph_num] = EATING;
        printf("Philosopher %d takes fork %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1); // print codes tooken from internet and I asked to Giray Hoca  
        printf("Philosopher %d is Eating\n", ph_num + 1);
        sem_post(&S[ph_num]);
    }
}
 
void put_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", ph_num + 1, LEFT + 1, ph_num + 1);
    printf("Philosopher %d is Thinking\n", ph_num + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}