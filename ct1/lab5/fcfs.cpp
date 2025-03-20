#include<bits/stdc++.h>

using namespace std;

struct Process {
    int id, arrival, burst, completion, turnaround, waiting;
};

bool compare(Process &a, Process &b) {
    return a.arrival < b.arrival;
}

void fcfs(vector<Process> &procs) {
    sort(procs.begin(), procs.end(), compare);
    int time = 0;

    for (int i=0; i<procs.size(); i++) {

        if (procs[i].arrival > time)
            time = procs[i].arrival;
        
        time += procs[i].burst;
        procs[i].completion = time;
        procs[i].turnaround = time - procs[i].arrival;
        procs[i].waiting = procs[i].turnaround - procs[i].burst;
    }
}

void display(const vector<Process>& processes) {
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t\t" << p.turnaround << "\t\t" << p.waiting << "\n";
    }
}

int main() {
    int n;
    cout<<"how many: ";
    cin>>n;

    vector<Process> procs(n);
    cout<<"Arrival Burst: ";
    for (int i=0; i<n; i++) {
        procs[i].id = i+1;
        cin>>procs[i].arrival>>procs[i].burst;
    }

    fcfs(procs);
    display(procs);

}