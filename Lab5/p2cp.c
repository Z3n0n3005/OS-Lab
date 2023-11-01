#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define MAX_ITEMS 5

// Global variables
int buffer[BUFFER_SIZE];
int read_index = 0;
int write_index = 0;
int produced_count = 0;
int consumed_count = 0;
sem_t empty;
sem_t full;

// Producer function
void *producer(void *arg) {
    while (produced_count < MAX_ITEMS) {
        // Wait for the buffer to have empty slots
        sem_wait(&empty);

        // Produce an integer and place it in the buffer
        int item = rand();
        buffer[write_index] = item;
        write_index = (write_index + 1) % BUFFER_SIZE;
        produced_count++;
        // Signal that the buffer has a full slot
        sem_post(&full);

        printf("Produced: %d\n", item);
    }
}

// Consumer function
void *consumer(void *arg) {
    while (consumed_count < MAX_ITEMS) {
        // Wait for the buffer to have full slots
        sem_wait(&full);

        // Consume an integer from the buffer
        int item = buffer[read_index];
        read_index = (read_index + 1) % BUFFER_SIZE;

        consumed_count++;
        // Signal that the buffer has an empty slot
        sem_post(&empty);

        // Consume the integer
        printf("Consumed: %d\n", item);
    }
}

int main() {
    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create the producer and consumer threads
    pthread_t producer_thread;
    pthread_t consumer_thread1;
    pthread_t consumer_thread2;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread1, NULL, consumer, NULL);
    pthread_create(&consumer_thread2, NULL, consumer, NULL);

    // Join the threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread1, NULL);
    pthread_join(consumer_thread2, NULL);

    return 0;
}
