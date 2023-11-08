#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 9
#define FOOD 2
sem_t forks[N];
sem_t foodPlates;

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", id);
        usleep(10000);

        // Pick up forks
        sem_wait(&foodPlates); // Acquire one food plate
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        // Eating
        printf("Philosopher %d is eating\n", id);
        usleep(10000);

        // Release forks
        sem_post(&forks[right]);
        sem_post(&forks[left]);
        sem_post(&foodPlates); // Release food plate
    }
    return NULL;
}

int main() {
    int i;
    int philosopher_ids[N];

    // Initialize semaphores (forks)
    for (i = 0; i < N; ++i) {
        sem_init(&forks[i], 0, 1);
    }

    // Initialize semaphore for food plates (limit to 2)
    sem_init(&foodPlates, 0, FOOD);

    // Create philosopher threads
    pthread_t philosophers[N];
    for (i = 0; i < N; ++i) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads
    for (i = 0; i < N; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

