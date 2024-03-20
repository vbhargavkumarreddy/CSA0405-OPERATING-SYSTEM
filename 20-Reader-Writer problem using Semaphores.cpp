#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_READERS 3
#define NUM_WRITERS 2
int sharedData = 0;
int readersCount = 0;
sem_t mutex, rw_mutex, readersCount_mutex;
void* reader(void* threadID) {
    int tid = *((int*)threadID);
    while (1) {
        sem_wait(&readersCount_mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&readersCount_mutex);
        printf("Reader %d is reading: %d\n", tid, sharedData);
        usleep(100000);
        sem_wait(&readersCount_mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&readersCount_mutex);
        usleep(500000);
    }
    pthread_exit(NULL);
}
void* writer(void* threadID) {
    int tid = *((int*)threadID);
    while (1) {
        sem_wait(&rw_mutex);
        sharedData++;
        printf("Writer %d is writing: %d\n", tid, sharedData);
        usleep(200000);
        sem_post(&rw_mutex);
        usleep(800000);
    pthread_exit(NULL);
}
int main() {
    pthread_t readerThreads[NUM_READERS];
    pthread_t writerThreads[NUM_WRITERS];
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    sem_init(&readersCount_mutex, 0, 1);
    int readerIDs[NUM_READERS];
    int writerIDs[NUM_WRITERS];
    for (int i = 0; i < NUM_READERS; ++i) {
        readerIDs[i] = i;
        pthread_create(&readerThreads[i], NULL, reader, (void*)&readerIDs[i]);
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writerIDs[i] = i;
        pthread_create(&writerThreads[i], NULL, writer, (void*)&writerIDs[i]);
    }
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readerThreads[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writerThreads[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    sem_destroy(&readersCount_mutex);

    return 0;
}
