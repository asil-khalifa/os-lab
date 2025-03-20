#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id, arrival, burst, completion, turnaround, waiting;
};

bool comp(Process &p1, Process &p2) {
    return p1.arrival < p2.arrival;
}

void fcfs(vector<Process> &procs) {
    sort(procs.begin(), procs.end(), comp);
    int time = 0;

    for (Process proc : procs) {
        if (proc.arrival > time)
            time = proc.arrival;
        
        time += proc.burst;
        proc.completion = time;
        proc.turnaround = time - proc.arrival;
        proc.waiting = proc.turnaround - proc.burst;
    }
}

void display(vector<Process>& processes) {
    int total_tat = 0, total_wt = 0;
    
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (const auto& process : processes) {
        total_tat += process.turnaround;
        total_wt += process.waiting;
        cout << process.id << "\t" << process.arrival << "\t" << process.burst << "\t" << process.completion << "\t" 
             << process.turnaround << "\t" << process.waiting << endl;
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
        // cout << "Process " << (i + 1) << " Arrival Time: ";
        cin >> processes[i].arrival;
        // cout << "Process " << (i + 1) << " Burst Time: ";
        cin >> processes[i].burst;
    }
}