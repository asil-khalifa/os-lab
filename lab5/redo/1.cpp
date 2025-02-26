#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int id, burst_time, arrival_time, completion_time, turnaround_time, waiting_time;
};

void fcfs(vector<Process>& processes) {
    int cur_time = 0, n =processes.size();

    for (int i=0; i<n; i++) {
        if (processes[i].arrival_time > cur_time)
            cur_time = processes[i].arrival_time;
        processes[i].completion_time = cur_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        cur_time = processes[i].completion_time;
    }
}

int main() {
    vector<Process> processes = {
        {1, 6, 1}, {2, 8, 1}, {3, 7, 2}, {4, 3, 3}
    };

    fcfs(processes);
    return 0;
}
