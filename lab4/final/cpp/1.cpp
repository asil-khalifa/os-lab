// Question 1: Matrix Multiplication using Threads (C++)
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

vector<vector<int>> A, B, C;
int rows, cols, common;

void compute_element(int row, int col) {
    C[row][col] = 0;
    for (int k = 0; k < common; k++) {
        C[row][col] += A[row][k] * B[k][col];
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
    cout << "Enter dimensions of matrix A (rows x common): ";
    cin >> rows >> common;
    cout << "Enter dimensions of matrix B (common x cols): ";
    cin >> common >> cols;

    A.resize(rows, vector<int>(common));
    B.resize(common, vector<int>(cols));
    C.resize(rows, vector<int>(cols));

    cout << "Enter elements of matrix A:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < common; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter elements of matrix B:\n";
    for (int i = 0; i < common; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> B[i][j];
        }
    }

    // Sequential execution time
    auto start_seq = chrono::high_resolution_clock::now();
    sequential_multiply();
    auto end_seq = chrono::high_resolution_clock::now();
    chrono::duration<double> seq_time = end_seq - start_seq;

    // Parallel execution time
    vector<thread> threads;
    auto start_par = chrono::high_resolution_clock::now();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            threads.emplace_back(compute_element, i, j);
        }
    }

    for (auto& th : threads) {
        th.join();
    }

    auto end_par = chrono::high_resolution_clock::now();
    chrono::duration<double> par_time = end_par - start_par;

    // Print results
    cout << "Sequential execution time: " << seq_time.count() << " seconds\n";
    cout << "Parallel execution time: " << par_time.count() << " seconds\n";

    return 0;
}

