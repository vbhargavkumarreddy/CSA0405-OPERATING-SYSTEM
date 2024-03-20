#include <stdio.h>
#include <pthread.h>

int shared_variable = 0;
pthread_mutex_t mutex;

void *increment_thread(void *arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        shared_variable++;
        printf("Incremented: %d\n", shared_variable);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *decrement_thread(void *arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        shared_variable--;
        printf("Decremented: %d\n", shared_variable);
        pthread_mutex_unlock(&mutex); 
    }
    return NULL;
}

int main() {
    pthread_t inc_thread, dec_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&inc_thread, NULL, increment_thread, NULL);
    pthread_create(&dec_thread, NULL, decrement_thread, NULL);
    pthread_join(inc_thread, NULL);
    pthread_join(dec_thread, NULL);

    pthread_mutex_destroy(&mutex); // Destroy mutex

    return 0;
}

