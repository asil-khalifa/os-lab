#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 1000  // Maximum size of the array

int numbers[MAX];
int n;  // Number of elements in the array
float mean;
float median;
int mode;

// Function to compare two integers for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to calculate mean
void* calculate_mean(void* arg) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += numbers[i];
    }
    mean = (float)sum / n;
    return NULL;
}

// Function to calculate median
void* calculate_median(void* arg) {
    qsort(numbers, n, sizeof(int), compare);  // Sort the array
    if (n % 2 == 0) {
        median = (numbers[n / 2 - 1] + numbers[n / 2]) / 2.0;
    } else {
        median = numbers[n / 2];
    }
    return NULL;
}

// Function to calculate mode
void* calculate_mode(void* arg) {
    int max_count = 0;
    int current_count = 1;
    mode = numbers[0];

    for (int i = 1; i < n; i++) {
        if (numbers[i] == numbers[i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                mode = numbers[i - 1];
            }
            current_count = 1;
        }
    }
    if (current_count > max_count) {
        mode = numbers[n - 1];
    }
    return NULL;
}

// Sequential calculation of statistics
void calculate_sequential() {
    // Mean
    long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += numbers[i];
    }
    mean = (float)sum / n;

    // Median
    qsort(numbers, n, sizeof(int), compare);
    if (n % 2 == 0) {
        median = (numbers[n / 2 - 1] + numbers[n / 2]) / 2.0;
    } else {
        median = numbers[n / 2];
    }

    // Mode
    int max_count = 0;
    int current_count = 1;
    mode = numbers[0];
    for (int i = 1; i < n; i++) {
        if (numbers[i] == numbers[i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                mode = numbers[i - 1];
            }
            current_count = 1;
        }
    }
    if (current_count > max_count) {
        mode = numbers[n - 1];
    }
}

int main() {
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    // Measure sequential execution time
    clock_t start_seq = clock();
    calculate_sequential();
    clock_t end_seq = clock();
    double seq_time = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;

    // Measure parallel execution time
    pthread_t threads[3];

    clock_t start_par = clock();
    pthread_create(&threads[0], NULL, calculate_mean, NULL);
    pthread_create(&threads[1], NULL, calculate_median, NULL);
    pthread_create(&threads[2], NULL, calculate_mode, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end_par = clock();
    double par_time = (double)(end_par - start_par) / CLOCKS_PER_SEC;

    // Print results
    printf("\nSequential Execution:\n");
    printf("Mean: %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Mode: %d\n", mode);
    printf("Execution Time: %.6f seconds\n", seq_time);

    printf("\nParallel Execution:\n");
    printf("Mean: %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Mode: %d\n", mode);
    printf("Execution Time: %.6f seconds\n", par_time);

    return 0;
}