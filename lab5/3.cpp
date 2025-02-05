#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int id, burst_time, arrival_time, completion_time, turnaround_time, waiting_time, remaining_time;
};

void srtf(vector<Process>& processes) {
    int n = processes.size(), completed = 0, current_time = 0;
    int min_remaining_time = INT_MAX, idx = -1;

    for (auto& p : processes) {
        p.remaining_time = p.burst_time;
    }

    while (completed < n) {
        idx = -1;
        min_remaining_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        processes[idx].remaining_time--;
        current_time++;

        if (processes[idx].remaining_time == 0) {
            completed++;
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        }
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

    srtf(processes);
    display(processes);
    return 0;
}
