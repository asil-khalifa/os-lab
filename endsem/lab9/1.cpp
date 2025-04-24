#include <bits/stdc++.h>

using namespace std;
using vvi = vector<vector<int>>;

void isSafe(vvi &need, vvi &max, vvi &allocation, vector<int> &available) {
    int cnt = 0;
    int n = need.size(), m = need[0].size();
    vector<bool> done(n, false);

    while (cnt < n) {
        bool atleast = false;

        for (int i=0; i<n; i++) {
            if (done[i])
                continue;

            bool found = true;
            for (int j=0; j<m; j++) {
                if (need[i][j] > available[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                cnt++;
                atleast = true;

                cout<<i<<"\t";
                done[i] = true;
                for (int j=0; j<m; j++)
                    available[j] += allocation[i][j];
            }
        }

        if (!atleast) {
            cout<<"Not safe!\n";
            break;
        }
    }


}

int main() {    
    int n = 5, m = 3;
    vvi max = {{3, 2, 2}, {2, 2, 2}, {9, 0, 2}, {7, 5, 3}, {4, 3, 3}},
    allocation = {{2, 0, 0}, {2, 1, 1}, {3, 0, 2}, {0, 1, 0}, {0, 0, 2}};
    vector<int> available = {3, 3, 2};

    vvi need(n, vector<int>(m, 0));

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    isSafe(need, max, allocation, available);
    cout<<endl;
}