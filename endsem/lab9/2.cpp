#include <bits/stdc++.h>

using namespace std;
const int mem_size = 256;

void paging() {
    int page_size = 16, log_add;
    int page_table_size = mem_size/page_size;
    int page_table[page_table_size];

    int val = 1;
    for (int i=0; i<page_table_size; i++) {
        val += rand() % 4;
        page_table[i] = val * page_size;
    }

    cout<<"Logical: ";
    cin>>log_add;

    int pageNo = log_add/page_size, offset = log_add % page_size;

    int phy_add = page_table[pageNo]+ offset;

    cout<<"Physical Address: "<<phy_add<<endl;
    
}

struct Segment {
    int base, limit;
};

void segmentation() {
    cout<<" How mnay: ";
    int n;
    cin>>n;
    Segment segs[n];

    for (int i=0; i<n; i++) {
        int base, limit;
        cout<<"Base, limit: ";
        cin>>base>>limit;

        segs[i].base = base;
        segs[i].limit = limit;

    }

    cout<<"Enter seg no., offset: ";
    int seg_no, offset;
    cin>>seg_no>>offset;

    // cout<<segs[seg_no] + offset;
}

int main() {
    srand(time(NULL));

}