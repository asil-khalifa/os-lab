#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 500  // Maximum size of the matrix

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];  // Matrices
int rows, cols, common;  // Dimensions of matrices

// Structure to hold data for each thread
typedef struct {
    int row;
    int col;
} ThreadData;

// Function to compute one element of the result matrix
void* compute_element(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;
    int col = data->col;

    C[row][col] = 0;
    for (int k = 0; k < common; k++) {
        C[row][col] += A[row][k] * B[k][col];
    }

    free(data);  // Free memory allocated for thread data
    return NULL;
}

void fill_matrices() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < common; j++) {
            A[i][j] = rand() % 10;  // Fill A with random values
        }
    }
    for (int i = 0; i < common; i++) {
        for (int j = 0; j < cols; j++) {
            B[i][j] = rand() % 10;  // Fill B with random values
        }
    }
}

void sequential_multiply() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = 0;
            for (int k = 0; k < common; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    printf("Enter dimensions of matrix A (rows x common): ");
    scanf("%d %d", &rows, &common);
    printf("Enter dimensions of matrix B (common x cols): ");
    scanf("%d %d", &common, &cols);

    fill_matrices();

    // Measure sequential execution time
    clock_t start_seq = clock();
    sequential_multiply();
    clock_t end_seq = clock();
    double seq_time = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;

    // Measure parallel execution time
    pthread_t threads[rows * cols];
    int thread_count = 0;
    clock_t start_par = clock();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));
            data->row = i;
            data->col = j;

            pthread_create(&threads[thread_count++], NULL, compute_element, data);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_par = clock();
    double par_time = (double)(end_par - start_par) / CLOCKS_PER_SEC;

    // Print results
    printf("Sequential execution time: %.6f seconds\n", seq_time);
    printf("Parallel execution time: %.6f seconds\n", par_time);

    return 0;
}