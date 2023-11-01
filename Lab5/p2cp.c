#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define CONSUME_ITEM 3
#define PRODUCE_ITEM 6
// Global variables
int buffer[BUFFER_SIZE];
int read_index = 0;
int write_index = 0;
int produced_count = 0;
int consumer_id = 0;
sem_t mutex;
sem_t empty;
sem_t full;

// Producer function
void *producer(void *arg) {
    while (produced_count < PRODUCE_ITEM) {
        // Wait for the buffer to have empty slots
        sem_wait(&empty);
        sem_wait(&mutex);
	
        // Produce an integer and place it in the buffer
        int item = rand() % 100 + 1;
        buffer[write_index] = item;
        write_index = (write_index + 1) % BUFFER_SIZE;
	sleep(rand() % 5 + 1);
        produced_count++;
        // Signal that the buffer has a full slot
        sem_post(&mutex);
        sem_post(&full);


        printf("Producer add number: %d\n", item);
    }
    pthread_exit(NULL);
}

// Consumer function
void *consumer(void *arg) {
    int consumer = consumer_id;
    int consumed_count = 0;
    consumer_id++;
    while (consumed_count < CONSUME_ITEM) {
        // Wait for the buffer to have full slots
        sem_wait(&full);
        sem_wait(&mutex);

        // Consume an integer from the buffer
        int item = buffer[read_index];
        read_index = (read_index + 1) % BUFFER_SIZE;
	sleep(rand() % 5 +1 );

        consumed_count++;
        // Signal that the buffer has an empty slot
        sem_post(&mutex);
        sem_post(&empty);

        // Consume the integer
        printf("Consumer %d get: %d\n", consumer, item);
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

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

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
