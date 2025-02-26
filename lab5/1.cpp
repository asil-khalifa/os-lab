#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int id, burst_time, arrival_time, completion_time, turnaround_time, waiting_time;
};

void fcfs(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time)
            current_time = processes[i].arrival_time;

        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        current_time = processes[i].completion_time;
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

    fcfs(processes);
    display(processes);
    return 0;
}
