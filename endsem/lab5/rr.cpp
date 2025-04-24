#include <bits/stdc++.h>

using namespace std;

int quantum;
struct Process {
    int id, arrival, burst, completion, turnaround, waiting, remaining;
};

bool comp(Process &p1, Process &p2) {
    return p1.arrival < p2.arrival;
}

void rr_diff(vector<Process> &procs) {
    sort(procs.begin(), procs.end(), comp);
    int n = procs.size(), t = procs[0].arrival, cnt = 0;
    vector<bool> done(n, false), inQ(n, false);
    queue<int> q;

    inQ[0] = true;
    q.push(0);

    while(cnt < n) {

        int i = q.front();
        q.pop();

        Process &cur = procs[i];

        if (cur.remaining <= quantum) {
            t += cur.remaining;
            cur.remaining = 0;
            cur.completion = t;
            cur.turnaround = t - cur.arrival;
            cur.waiting = cur.turnaround - cur.burst;

            done[i] = true;
            cnt++;
        }
        else {
            t += quantum;
            cur.remaining -= quantum;
        }

        for (int j=0; j<n; j++) {
            if (!done[j] && procs[j].arrival <= t && !inQ[j] && procs[j].remaining > 0) {
                q.push(j);
                inQ[j] = true;
            }
        }

        if (cur.remaining > 0) {
            q.push(i);
        }

        if (q.size() == 0) {
            t++;
        }

    }
}

void rr_diff_arrival(vector<Process> &procs) {
    sort(procs.begin(), procs.end(), comp);
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

void rr_same_arrival(vector<Process> &procs) {
    int t = 0, cnt = 0, n = procs.size();
    vector<bool> done(n, false);

    while(cnt < n) {
        bool found = false;

        for (int i=0; i<n; i++) {
            if (done[i] || procs[i].arrival > t)
                continue;
            found = true;

            cout<<"Doing: "<<i<<endl;
    
            Process &cur = procs[i];

            if (cur.remaining <= quantum) {
                t += cur.remaining;

                cur.remaining = 0;
                cur.completion = t;
                cur.turnaround = t - cur.arrival;
                cur.waiting = cur.turnaround - cur.burst;
    
                done[i] = true;
                cnt++;
            }
            else{
                cur.remaining -= quantum;
                t += quantum;
            }
        }

        cout<<"Nope";
        if (!found)
            t++;

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
    cin>>quantum;
    vector<Process> procs(n);
    // cout<<"Arrival Burst: ";
    for (int i=0; i<n; i++) {
        procs[i].id = i+1;
        cin>>procs[i].arrival>>procs[i].burst;
        procs[i].remaining = procs[i].burst;
    }

    rr_diff_arrival(procs);
    display(procs);

}