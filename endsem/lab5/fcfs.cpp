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
    int t = 0;

    for (auto &proc:procs) {
        if (proc.arrival > t)
            t = proc.arrival;

        t += proc.burst;
        proc.completion = t;
        proc.turnaround = t - proc.arrival;
        proc.waiting = proc.turnaround - proc.burst;
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