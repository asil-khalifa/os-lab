#include <iostream>
using namespace std;

const int P = 5; // Number of processes
const int R = 3; // Number of resources

// Function to check if system is in a safe state
bool isSafe(int available[], int max[][R], int allocation[][R], int need[][R]) {
    int work[R];
    bool finish[P] = {false};
    for (int i = 0; i < R; i++)
        work[i] = available[i];
    
    int safeSeq[P];
    int count = 0;
    
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];
                    
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is in an unsafe state!" << endl;
            return false;
        }
    }
    
    cout << "System is in a safe state. Safe sequence: ";
    for (int i = 0; i < P; i++)
        cout << safeSeq[i] << " ";
    cout << endl;
    return true;
}

int main() {
    int available[R] = {3, 3, 2};
    int max[P][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int allocation[P][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int need[P][R];
    
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    
    isSafe(available, max, allocation, need);
    return 0;
}
