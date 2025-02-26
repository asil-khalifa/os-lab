#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Process {
    int id, arrival_time, burst_time, remaining_time, completion_time, waiting_time, turnaround_time;
};

bool compareArrival(Process a, Process b) {
    return a.arrival_time < b.arrival_time;
}

void shortestRemainingTimeFirst(vector<Process>& processes) {
    int time = 0, completed = 0, n = processes.size();
    int shortest_index = -1, min_remaining_time = INT_MAX;
    
    sort(processes.begin(), processes.end(), compareArrival);
    
    while (completed < n) {
        shortest_index = -1;
        min_remaining_time = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < min_remaining_time) {
                    min_remaining_time = processes[i].remaining_time;
                    shortest_index = i;
                }
            }
        }
        
        if (shortest_index == -1) {
            time++;
            continue;
        }
        
        processes[shortest_index].remaining_time--;
        time++;
        
        if (processes[shortest_index].remaining_time == 0) {
            completed++;
            processes[shortest_index].completion_time = time;
            processes[shortest_index].turnaround_time = processes[shortest_index].completion_time - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
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
    int n;
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
    
    shortestRemainingTimeFirst(processes);
    calculateAverages(processes);
    
    return 0;
}
