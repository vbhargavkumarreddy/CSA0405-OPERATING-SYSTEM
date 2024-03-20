#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Hello from the thread!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // (i) Create Threads
    if (pthread_create(&thread1, NULL, thread_function, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1.\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, thread_function, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2.\n");
        return 1;
    }

    // (iii) Equal Threads
    if (pthread_equal(thread1, thread2)) {
        printf("Threads are equal.\n");
    } else {
        printf("Threads are not equal.\n");
    }

    // (ii) Join Threads
    if (pthread_join(thread1, NULL) != 0) {
        fprintf(stderr, "Error joining thread 1.\n");
        return 2;
    }

    if (pthread_join(thread2, NULL) != 0) {
        fprintf(stderr, "Error joining thread 2.\n");
        return 2;
    }

    printf("Threads joined successfully.\n");

    // (iv) Exit Threads
    pthread_exit(NULL); 

    return 0;
}

