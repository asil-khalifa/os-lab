#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void fcfs(const vector<int>& req, int head) {
    int total = 0;
    cout << "FCFS Order: " << head;
    for (int r : req) {
        total += abs(r - head);
        head = r;
        cout << " -> " << head;
    }
    cout << "\nTotal Seek Time: " << total << "\n";
}

void sstf(const vector<int>& req, int head) {
    vector<int> local = req;
    vector<bool> visited(local.size(), false);
    int total = 0;

    cout << "SSTF Order: " << head;

    for (size_t i = 0; i < local.size(); ++i) {
        int minDist = 1e9, index = -1;
        for (size_t j = 0; j < local.size(); ++j) {
            if (!visited[j] && abs(local[j] - head) < minDist) {
                minDist = abs(local[j] - head);
                index = j;
            }
        }
        visited[index] = true;
        total += abs(local[index] - head);
        head = local[index];
        cout << " -> " << head;
    }
    cout << "\nTotal Seek Time: " << total << "\n";
}

void scan(const vector<int>& req, int head, int size, int dir) {
    vector<int> local = req;
    local.push_back(head);
    local.push_back(dir == 1 ? size - 1 : 0);

    sort(local.begin(), local.end());
    int i = find(local.begin(), local.end(), head) - local.begin();

    cout << "SCAN Order: ";
    if (dir == 1) {
        for (size_t j = i; j < local.size(); ++j) cout << local[j] << " -> ";
        for (int j = i - 1; j >= 0; --j) cout << local[j] << " -> ";
    } else {
        for (int j = i; j >= 0; --j) cout << local[j] << " -> ";
        for (size_t j = i + 1; j < local.size(); ++j) cout << local[j] << " -> ";
    }

    int total = abs(head - (dir == 1 ? size - 1 : 0)) + abs(local[0] - local[local.size() - 2]);
    cout << "\b\b  \nTotal Seek Time: " << total << "\n";
}

void cscan(const vector<int>& req, int head, int size, int dir) {
    vector<int> local = req;
    local.push_back(head);
    local.push_back(0);
    local.push_back(size - 1);

    sort(local.begin(), local.end());
    int i = find(local.begin(), local.end(), head) - local.begin();

    cout << "C-SCAN Order: ";
    if (dir == 1) {
        for (size_t j = i; j < local.size(); ++j) cout << local[j] << " -> ";
        for (size_t j = 0; j < i; ++j) cout << local[j] << " -> ";
    } else {
        for (int j = i; j >= 0; --j) cout << local[j] << " -> ";
        for (int j = local.size() - 1; j > i; --j) cout << local[j] << " -> ";
    }

    int total = (dir == 1) ? (size - 1 - head + size - 1) : (head + size - 1);
    cout << "\b\b  \nTotal Seek Time: " << total << "\n";
}

void look(const vector<int>& req, int head, int dir) {
    vector<int> local = req;
    local.push_back(head);

    sort(local.begin(), local.end());
    int i = find(local.begin(), local.end(), head) - local.begin();

    cout << "LOOK Order: ";
    int total;
    if (dir == 1) {
        for (size_t j = i; j < local.size(); ++j) cout << local[j] << " -> ";
        for (int j = i - 1; j >= 0; --j) cout << local[j] << " -> ";
        total = local.back() - head + local.back() - local.front();
    } else {
        for (int j = i; j >= 0; --j) cout << local[j] << " -> ";
        for (size_t j = i + 1; j < local.size(); ++j) cout << local[j] << " -> ";
        total = head - local.front() + local.back() - local.front();
    }

    cout << "\b\b  \nTotal Seek Time: " << total << "\n";
}

void clook(const vector<int>& req, int head, int dir) {
    vector<int> local = req;
    local.push_back(head);

    sort(local.begin(), local.end());
    int i = find(local.begin(), local.end(), head) - local.begin();

    cout << "C-LOOK Order: ";
    int total;
    if (dir == 1) {
        for (size_t j = i; j < local.size(); ++j) cout << local[j] << " -> ";
        for (size_t j = 0; j < i; ++j) cout << local[j] << " -> ";
        total = local.back() - head + local.back() - local.front();
    } else {
        for (int j = i; j >= 0; --j) cout << local[j] << " -> ";
        for (int j = local.size() - 1; j > i; --j) cout << local[j] << " -> ";
        total = head - local.front() + local.back() - local.front();
    }

    cout << "\b\b  \nTotal Seek Time: " << total << "\n";
}

int main() {
    vector<int> req;
    int n, head, choice, dir;
    const int size = 200;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter request sequence: ";
    req.resize(n);
    for (int i = 0; i < n; i++) cin >> req[i];

    cout << "Enter initial head position: ";
    cin >> head;

    do {
        cout << "\nDisk Scheduling Algorithms\n";
        cout << "1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice >= 3 && choice <= 6) {
            cout << "Enter direction (0 = left, 1 = right): ";
            cin >> dir;
        }

        switch (choice) {
            case 1: fcfs(req, head); break;
            case 2: sstf(req, head); break;
            case 3: scan(req, head, size, dir); break;
            case 4: cscan(req, head, size, dir); break;
            case 5: look(req, head, dir); break;
            case 6: clook(req, head, dir); break;
        }

    } while (choice != 0);

    return 0;
}
