#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;   
sem_t mutex;      
int read_count = 0;
int shared_data = 0;

void *reader(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 5; i++) {  
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        printf("Reader %d reads data: %d\n", id, shared_data);
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        sleep(1);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 5; i++) {  
        sem_wait(&rw_mutex);

        shared_data++;
        printf("Writer %d updates data to: %d\n", id, shared_data);
        sleep(1);

        sem_post(&rw_mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t r1, r2, w1;
    int id1 = 1, id2 = 2, id3 = 3;

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&w1, NULL, writer, &id3);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
