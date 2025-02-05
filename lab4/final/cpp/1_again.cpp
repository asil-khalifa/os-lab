#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

vector<vector<int>> A, B, C;
int rows, cols, common;

void compute_row(int row) {
    for (int col = 0; col < cols; col++) {
        C[row][col] = 0;
        for (int k = 0; k < common; k++) {
            C[row][col] += A[row][k] * B[k][col];
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
    srand(time(NULL));
    int maxval = 5000, test;
    cout << "Enter dimensions of matrix A (rows x common): ";
    cin >> rows >> common;
    cout << "Enter dimensions of matrix B (common x cols): ";
    cin >> test >> cols;

    if (test != common) {
        cout<<"Invalid entry\n";
        return 1;
    }

    A.resize(rows, vector<int>(common));
    B.resize(common, vector<int>(cols));
    C.resize(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < common; j++) {
            A[i][j] = rand()%maxval;
        }
    }

    for (int i = 0; i < common; i++) {
        for (int j = 0; j < cols; j++) {
            B[i][j] = rand()%maxval;
        }
    }

    auto start_seq = high_resolution_clock::now();
    sequential_multiply();
    auto end_seq = high_resolution_clock::now();
    duration<double> seq_time = end_seq - start_seq;

    vector<thread> threads;
    for (int i = 0; i < rows; i++) {
        threads.emplace_back(compute_row, i);
    }

    auto start_par = high_resolution_clock::now();

    for (auto& th : threads) {
        th.join();
    }

    auto end_par = high_resolution_clock::now();
    duration<double> par_time = end_par - start_par;

    cout << "Sequential execution time: " << seq_time.count() << " seconds\n";
    cout << "Parallel execution time: " << par_time.count() << " seconds\n";

    return 0;
}
