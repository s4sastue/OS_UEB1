#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

#define ITERATIONS 1000000

sem_t sem1;
sem_t sem2;

void *thread_func(void *arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        sem_wait(&sem1);
        sem_post(&sem2);
    }
    return NULL;
}

int main() {

    FILE *file = fopen("results_Config1_context_switch_times.txt", "w");

    struct timespec start,
            total_start,
            end,
            total_end;

    pthread_t thread;

    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);

    pthread_create(&thread, NULL, thread_func, NULL);

    clock_gettime(CLOCK_MONOTONIC, &total_start);
    for (int i = 0; i < ITERATIONS; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        sem_wait(&sem2);
        sem_post(&sem1);
        clock_gettime(CLOCK_MONOTONIC, &end);

        long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);

        fprintf(file, "%ld\n", elapsed_ns);
    }

    clock_gettime(CLOCK_MONOTONIC, &total_end);
    long elapsed_ns = (total_end.tv_sec - total_start.tv_sec) * 1000000000L + (total_end.tv_nsec - total_start.tv_nsec);
    printf("Durchschnittliche Kontextwechselzeit: %.2f ns\n", elapsed_ns/(double)(2 * ITERATIONS));


    pthread_join(thread, NULL);
    fclose(file);
    return 0;
}