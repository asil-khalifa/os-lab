#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

using Matrix = vector<vector<int>>;

Matrix A, B, C;
int rows, cols, com;

void seq_multiply() {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            C[i][j] = 0;
            for (int k=0; k<com; k++) 
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

void row_mult(int r) {
    for (int j=0; j<cols; j++) {
        C[r][j] = 0;

        for (int k=0; k<com; k++)
            C[r][j] += A[r][k] * B[k][j];
    }
}

int main() {
    srand(time(NULL));

    cout<<"Rows common cols: ";
    cin>>rows>>com>>cols;

    A.resize(rows, vector<int>(com, 0));
    B.resize(com, vector<int>(cols, 0));
    C.resize(rows, vector<int>(cols, 0));

    for (int i=0; i<rows; i++) {
        for (int j=0; j<com; j++)
            A[i][j] = rand()%25;
    }

    for (int i=0; i<com; i++) {
        for (int j=0; j<cols; j++) 
            B[i][j] = rand()%25;
    }

    auto start = high_resolution_clock::now();
    seq_multiply();
    auto end = high_resolution_clock::now();
    auto dur = duration_cast<nanoseconds>(end-start);
    
    cout<<"Sequential Time: "<<dur.count()<<endl;
    
    vector<thread> funcs;
    for (int i=0; i<rows; i++) 
        funcs.push_back(thread(row_mult, i));
    
    start = high_resolution_clock::now();
    for (auto &th : funcs)
        th.join();
    end = high_resolution_clock::now();
    dur = duration_cast<nanoseconds>(end-start);

    cout<<"Parallel Time: "<<dur.count()<<endl;
    
}

