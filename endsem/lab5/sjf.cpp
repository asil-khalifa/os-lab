#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id, arrival, burst, completion, turnaround, waiting;
};

bool comp(Process &p1, Process &p2) {
    return p1.burst < p2.burst;
}

void sjf(vector<Process> &procs) {
    sort(procs.begin(), procs.end(), comp);
    int t = 0, cnt = 0, n = procs.size();
    vector<bool> done(n, false);

    while(cnt < n) {
        int ind = -1, min_val = INT_MAX;

        for (int i=0; i<n; i++) {
            if (!done[i] && procs[i].arrival <= t && procs[i].burst < min_val) {
                min_val = procs[i].burst;
                ind = i;
            }
        }

        if (ind == -1) {
            t++;
            continue;
        }

        cout<<"Doing: "<<ind<<endl;
        procs[ind].waiting = t - procs[ind].arrival;
        t += procs[ind].burst;
        procs[ind].completion = t;
        procs[ind].turnaround = t - procs[ind].arrival;
        done[ind] = true;
        cnt++;
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
    // cout<<"how many: ";
    cin>>n;

    vector<Process> procs(n);
    // cout<<"Arrival Burst: ";
    for (int i=0; i<n; i++) {
        procs[i].id = i+1;
        cin>>procs[i].arrival>>procs[i].burst;
    }

    sjf(procs);
    display(procs);

}