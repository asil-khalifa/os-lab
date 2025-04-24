#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id, arrival, burst, completion, turnaround, waiting, remaining;
};

// bool comp(Process &p1, Process &p2) {
//     return p1.burst < p2.burst;
// }

void srtf(vector<Process> &procs) {
    // sort(procs.begin(), procs.end(), comp);
    int t = 0, cnt = 0, n = procs.size();
    vector<bool> done(n, false);

    while(cnt < n) {
        int ind = -1, min_val = INT_MAX;

        for (int i=0; i<n; i++) {
            if (!done[i] && procs[i].arrival <= t && procs[i].remaining < min_val) {
                min_val = procs[i].remaining;
                ind = i;
            }
        }

        if (ind == -1) {
            t++;
            continue;
        }

        t++;
        cout<<"Doing: "<<ind<<endl;

        Process &cur = procs[ind];
        if (cur.remaining == 1) {
            cur.remaining = 0;
            cur.completion = t;
            cur.turnaround = t - cur.arrival;
            cur.waiting = cur.turnaround - cur.burst;

            done[ind] = true;
            cnt++;
        }
        else{
            cur.remaining--;
        }
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
        procs[i].remaining = procs[i].burst;
    }

    srtf(procs);
    display(procs);

}