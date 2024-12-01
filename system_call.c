#include <stdio.h>
#include <unistd.h>
#include <time.h>


int main() {
    FILE *file = fopen("results_Config1_system_call_times.txt", "w");

    struct timespec start,
            end;

    for (int i = 0; i < 1000000; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        getuid();

        clock_gettime(CLOCK_MONOTONIC, &end);

        long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);

        fprintf(file, "%ld\n", elapsed_ns);
    }

    fclose(file);

    return 0;
}
