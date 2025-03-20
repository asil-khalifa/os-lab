#include<bits/stdc++.h>

using namespace std;

struct Process {
    int id, arrival, burst, completion, turnaround, waiting, remaining;
};

// bool compare(Process &a, Process &b) {
//     if (a.burst < b.burst)
//         return true;
//     return false;
// }

void srtf(vector<Process> &procs) {
    int n = procs.size(), time = 0, cnt=0;
    vector<int> done(n, 0);

    while (cnt < n) {
        int ind = -1, val = INT_MAX;
        for (int i=0; i<n; i++) {
            if (!done[i] && procs[i].arrival <= time && procs[i].remaining < val) {
                ind = i;
                val = procs[i].remaining;
            }
        }
        cout<<"ind: "<<ind<<" time: "<<time<<endl;
        if (ind != -1) {
            if (procs[ind].remaining <= 1) {
                time += procs[ind].remaining;
                procs[ind].remaining = 0;

                procs[ind].completion = time;
                procs[ind].turnaround = time - procs[ind].arrival;
                procs[ind].waiting = procs[ind].turnaround - procs[ind].burst;

                done[ind] = 1;
                cnt++;
            }
            else {
                procs[ind].remaining--;
                time++;
            }
        }
        else {
            time++;
        }
        
        // time++;
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
        procs[i].remaining = procs[i].burst;
        // cout<<i<<endl;
    }

    srtf(procs);
    display(procs);

}