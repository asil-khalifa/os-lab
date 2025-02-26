#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int id, arrival_time, burst_time, remaining_time, completion_time, waiting_time, turnaround_time;
};

bool compareArrival(Process a, Process b) {
    return a.arrival_time < b.arrival_time;
}

void roundRobinScheduling(vector<Process>& processes, int time_quantum) {
    int time = 0;
    queue<int> readyQueue;
    vector<bool> inQueue(processes.size(), false);
    int completed = 0;

    sort(processes.begin(), processes.end(), compareArrival);
    readyQueue.push(0);
    inQueue[0] = true;

    while (completed < processes.size()) {
        int i = readyQueue.front();
        readyQueue.pop();
        
        if (processes[i].remaining_time > time_quantum) {
            time += time_quantum;
            processes[i].remaining_time -= time_quantum;
        } else {
            time += processes[i].remaining_time;
            processes[i].completion_time = time;
            processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
            processes[i].remaining_time = 0;
            completed++;
        }
        
        for (int j = 0; j < processes.size(); j++) {
            if (!inQueue[j] && processes[j].arrival_time <= time && processes[j].remaining_time > 0) {
                readyQueue.push(j);
                inQueue[j] = true;
            }
        }
        if (processes[i].remaining_time > 0) {
            readyQueue.push(i);
        }
    }
}

void calculateAverages(vector<Process>& processes) {
    int total_tat = 0, total_wt = 0;
    
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (const auto& process : processes) {
        total_tat += process.turnaround_time;
        total_wt += process.waiting_time;
        cout << process.id << "\t" << process.arrival_time << "\t" << process.burst_time << "\t" << process.completion_time << "\t" 
             << process.turnaround_time << "\t" << process.waiting_time << endl;
    }
    
    cout << "\nAverage Turnaround Time: " << (float)total_tat / processes.size() << endl;
    cout << "Average Waiting Time: " << (float)total_wt / processes.size() << endl;
}

int main() {
    int n, time_quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Process " << (i + 1) << " Arrival Time: ";
        cin >> processes[i].arrival_time;
        cout << "Process " << (i + 1) << " Burst Time: ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    cout << "Enter time quantum: ";
    cin >> time_quantum;
    
    roundRobinScheduling(processes, time_quantum);
    calculateAverages(processes);
    
    return 0;
}
