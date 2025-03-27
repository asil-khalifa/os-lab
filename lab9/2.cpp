#include <bits/stdc++.h>
using namespace std;

#define PAGE_SIZE 4  
#define MEMORY_SIZE 32 

void paging() {
    cout << "\nPaging Simulation: " << endl;
    
    int logicalAddress, pageTable[MEMORY_SIZE / PAGE_SIZE];

    int val = 0;
    cout<<"Page Table generated: ";
    for (int i = 0; i < MEMORY_SIZE / PAGE_SIZE; i++) {
        val += rand()%4 + 1;
        pageTable[i] = val * PAGE_SIZE; 
        cout<<pageTable[i]<<" ";
    }
    cout<<endl;
    
    cout << "Enter a logical address (0 - " << MEMORY_SIZE - 1 << "): ";
    cin >> logicalAddress;
    
    if (logicalAddress >= MEMORY_SIZE) {
        cout << "Invalid logical address!" << endl;
        return;
    }
    
    int pageNumber = logicalAddress / PAGE_SIZE;
    int offset = logicalAddress % PAGE_SIZE;
    int physicalAddress = pageTable[pageNumber] + offset;
    
    cout<<"Offset: "<<offset<<" pageNumber: "<<pageNumber<<endl;
    cout << "Logical Address: " << logicalAddress << " => Physical Address: " << physicalAddress << endl;
}


struct Segment {
    int base;
    int limit;
};

void segmentation() {
    int n, logicalAddress, segmentNumber, offset;
    
    cout << "\nSegmentation Simulation: " << endl;
    cout << "Enter the number of segments: ";
    cin >> n;
    
    vector<Segment> segmentTable(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter base and limit for segment " << i << ": ";
        cin >> segmentTable[i].base >> segmentTable[i].limit;
    }
    
    cout << "Enter segment number and offset: ";
    cin >> segmentNumber >> offset;
    
    if (segmentNumber >= n || offset >= segmentTable[segmentNumber].limit) {
        cout << "Invalid segment or offset!" << endl;
        return;
    }
    
    int physicalAddress = segmentTable[segmentNumber].base + offset;
    cout << "Segment: " << segmentNumber << " Offset: " << offset << " => Physical Address: " << physicalAddress << endl;
}

int main() {
    srand(time(NULL));

    int choice;
    do {
        cout << "\nMemory Management Techniques" << endl;
        cout << "1. Paging" << endl;
        cout << "2. Segmentation" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                paging();
                break;
            case 2:
                segmentation();
                break;
            case 3:
                cout << "Exiting" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 3);
    
    return 0;
}
