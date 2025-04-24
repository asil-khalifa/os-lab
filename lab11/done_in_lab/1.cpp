#include <bits/stdc++.h>

using namespace std;

void fcfs(vector<int> &reqs, int head) {
	cout<<"\nFCFS: ";
	int tot = 0;

	cout<<head;
	for (int req : reqs) {
		
		cout<<"->"<<req;
		tot += abs(head - req);
		head = req;
	}

	cout<<"\nFCFS Time: "<<tot<<endl;
}

void sstf(vector<int> &reqs, int head) {
	int n = reqs.size(), tot = 0;

	vector<bool> done(n, false);
	
	cout<<"SSTF: "<<head;
	for (int i=0; i<n; i++) {
		int mini=INT_MAX, ind=-1;

		for (int j=0; j<n; j++) {
			if (done[j])
				continue;

			int val = abs(head - reqs[j]);
			if (val < mini) {
				mini = val;
				ind = j;
			}
		}

		cout<<"->"<<reqs[ind];
		tot += abs(head-reqs[ind]);
		done[ind] = true;
		head = reqs[ind];
	}
	cout<<"\nSSTF Time: "<<tot<<endl;
}

void scan(int size, vector<int> &reqs_in, int head, bool circ) {
	vector<int> reqs = reqs_in;

	bool head_in = false;
	for (int req : reqs) {
		if (req == head) {
			head_in = true;
			break;
		}
	}

	if (!head_in)
		reqs.push_back(head);
	
	reqs.push_back(0);
	if (circ)
		reqs.push_back(size-1);

	sort(reqs.begin(), reqs.end());
	
	int n = reqs.size(), h_ind;
	for (int i=0; i<n; i++) {
		if (reqs[i] == head) {
			h_ind = i;
			break;
		}
	}
	
	cout<<endl;
	if (circ)
		cout<<"C-";
	cout<<"SCAN: "<<head;

	int tot=0;
	for (int i=h_ind-1; i>=0; i--) {
		cout<<"->"<<reqs[i];
		tot+= abs(head-reqs[i]);
		head = reqs[i];
	}
	
	if (circ) {
		for (int i=n-1; i>h_ind; i--) {
			cout<<"->"<<reqs[i];
			tot += abs(head-reqs[i]);
			head = reqs[i];
		}
	}
	else{

		for (int i=h_ind+1; i<n; i++) {
			cout<<"->"<<reqs[i];
			tot += abs(head-reqs[i]);
			head = reqs[i];
		}
	}

	cout<<endl;
	if (circ)
		cout<<"C-";
	cout<<"SCAN Total Seek Time: "<<tot<<endl;
}

void look(int size, vector<int> &reqs_in, int head, bool circ) {
	vector<int> reqs = reqs_in;

	bool head_in = false;
	for (int req : reqs) {
		if (req == head) {
			head_in = true;
			break;
		}
	}

	if (!head_in)
		reqs.push_back(head);
	

	sort(reqs.begin(), reqs.end());
	
	int n = reqs.size(), h_ind;
	for (int i=0; i<n; i++) {
		if (reqs[i] == head) {
			h_ind = i;
			break;
		}
	}
	
	cout<<endl;
	if (circ)
		cout<<"C-";
	cout<<"LOOK: "<<head;

	int tot=0;
	for (int i=h_ind-1; i>=0; i--) {
		cout<<"->"<<reqs[i];
		tot+= abs(head-reqs[i]);
		head = reqs[i];
	}
	
	if (circ) {
		for (int i=n-1; i>h_ind; i--) {
			cout<<"->"<<reqs[i];
			tot += abs(head-reqs[i]);
			head = reqs[i];
		}
	}
	else{

		for (int i=h_ind+1; i<n; i++) {
			cout<<"->"<<reqs[i];
			tot += abs(head-reqs[i]);
			head = reqs[i];
		}
	}
	
	

	cout<<endl;
	if (circ)
		cout<<"C-";
	cout<<"LOOK Total Seek Time: "<<tot<<endl;
}

int main() {
	int size, n, head;
	cout<<"Enter size of disk: ";
	cin>>size;

	cout<<"Enter no. of requests: ";
	cin>>n;
	vector<int> reqs(n, -1);
	
	cout<<"Requests: ";
	for (int i=0; i<n; i++) {
		cin>>reqs[i];
	}

	cout<<"Head: ";
	cin>>head;

	fcfs(reqs, head);
	sstf(reqs, head);
	scan(size, reqs, head, false);
	scan(size, reqs, head, true);
	look(size, reqs, head, false);
	look(size, reqs, head, true);
}

