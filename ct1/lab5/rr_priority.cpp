#include<bits/stdc++.h>

using namespace std;
int quantum;

struct Process {
    int id, arrival, burst, completion, turnaround, waiting, remaining;
};

bool compare(Process &a, Process &b) {
    return a.arrival < b.arrival;
}

void rr_diff_arrival(vector<Process> &procs) {
    sort(procs.begin(), procs.end(), compare);
    int time = procs[0].arrival, cnt = 0,n = procs.size();

    vector<bool> done(n, false);

    vector<bool> inQ(n, false);
    queue<int> readyQ;

    readyQ.push(0);
    inQ[0] = true;

    while (cnt < n) {
        int i = readyQ.front();
        readyQ.pop();

        if (procs[i].remaining <= quantum) {
            time += procs[i].remaining;

            procs[i].completion = time;
            procs[i].turnaround = time - procs[i].arrival;
            procs[i].waiting = procs[i].turnaround - procs[i].burst;
            procs[i].remaining = 0;
            
            cnt++;
            done[i] = true;

        }

        else {
            time += quantum;
            procs[i].remaining -= quantum;
        }

        for (int i=0; i<n; i++) {
            if (!done[i] && !inQ[i] &&
            procs[i].arrival <= time && procs[i].remaining > 0) {
                readyQ.push(i);
                inQ[i] = true;
            }
        }

        if (procs[i].remaining > 0) {
            readyQ.push(i);
        }

        if (readyQ.size() == 0)
            time++;
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
        procs[i].remaining = procs[i].burst;
    }

    cout<<"Quantum: ";
    cin>>quantum;

    rr_diff_arrival(procs);
    // rr_same_arrival(procs);
    display(procs);

}