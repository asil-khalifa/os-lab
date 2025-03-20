#include<bits/stdc++.h>

using namespace std;

struct Process {
    int id, arrival, burst, completion, turnaround, waiting;
};

bool compare(Process &a, Process &b) {
    if (a.burst < b.burst)
        return true;
    // if (a.burst > b.burst)
    //     return false;
    // if (a.arrival < b.arrival)
    //     return true;
    return false;
}

void sjf(vector<Process> &procs) {
    int n = procs.size();
    sort(procs.begin(), procs.end(), compare);
    int time = 0, cnt=0;
    vector<int> done(n, 0);

    while (cnt < n) {
        // int val = INT_MAX, ind=-1;
        int ind = -1;
        for (int i=0; i<n; i++) {
            if (!done[i] && procs[i].arrival <= time) {
                ind = i;
                break;
            }
        }
        cout<<"ind: "<<ind<<" time: "<<time<<endl;
        if (ind == -1) {
            time++;
            continue;
        }

        time += procs[ind].burst;
        procs[ind].completion = time;
        procs[ind].turnaround = time - procs[ind].arrival;
        procs[ind].waiting = procs[ind].turnaround - procs[ind].burst;
        done[ind] = 1;
        cnt++;
        // cout<<cnt;
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
        // cout<<i<<endl;
    }

    sjf(procs);
    display(procs);

}