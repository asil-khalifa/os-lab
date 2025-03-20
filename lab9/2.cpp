#include <iostream>
#include <vector>
using namespace std;

#define PAGE_SIZE 4  // Define the size of a page (4 KB assumed for simplicity)
#define MEMORY_SIZE 32 // Define total memory size (32 KB assumed)

// Paging Simulation
void pagingSimulation() {
    int logicalAddress, pageTable[MEMORY_SIZE / PAGE_SIZE];
    for (int i = 0; i < MEMORY_SIZE / PAGE_SIZE; i++) {
        pageTable[i] = i * PAGE_SIZE; // Mapping logical pages to physical frames
    }
    
    cout << "\nPaging Simulation: " << endl;
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

// Segmentation Simulation
struct Segment {
    int base;
    int limit;
};

void segmentationSimulation() {
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
                pagingSimulation();
                break;
            case 2:
                segmentationSimulation();
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 3);
    
    return 0;
}
