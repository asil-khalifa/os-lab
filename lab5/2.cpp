#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Process {
    int id, burst_time, arrival_time, completion_time, turnaround_time, waiting_time;
};

void sjf(vector<Process>& processes) {
    int n = processes.size(), current_time = 0, completed = 0;

    vector<bool> is_done(n, false);
    while (completed < n) {
        int idx = -1, min_burst_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!is_done[i] && processes[i].arrival_time <= current_time &&
                processes[i].burst_time < min_burst_time) {
                min_burst_time = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        current_time += processes[idx].burst_time;
        processes[idx].completion_time = current_time;
        processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
        processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        is_done[idx] = true;
        completed++;
    }
}

void display(const vector<Process>& processes) {
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        cout << p.id << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << "\n";
    }
}

int main() {
    vector<Process> processes = {
        {1, 6, 1}, {2, 8, 1}, {3, 7, 2}, {4, 3, 3}
    };

    sjf(processes);
    display(processes);
    return 0;
}
