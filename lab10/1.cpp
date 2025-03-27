#include <bits/stdc++.h>
using namespace std;

// FIFO Page Replacement
int fifoPageReplacement(vector<int>& pages, int frames) {
    queue<int> pageQueue;
    set<int> pageSet;
    int pageFaults = 0;

    for (int page : pages) {
        if (pageSet.find(page) == pageSet.end()) {
            if (pageQueue.size() == frames) {
                int removedPage = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(removedPage);
            }
            pageQueue.push(page);
            pageSet.insert(page);
            pageFaults++;
        }
    }
    return pageFaults;
}

// LRU Page Replacement
int lruPageReplacement(vector<int>& pages, int frames) {
    unordered_map<int, int> pageMap;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (pageMap.find(page) == pageMap.end()) {
            if (pageMap.size() == frames) {
                int lruPage = -1, lruIndex = INT_MAX;
                for (auto& entry : pageMap) {
                    if (entry.second < lruIndex) {
                        lruIndex = entry.second;
                        lruPage = entry.first;
                    }
                }
                pageMap.erase(lruPage);
            }
            pageFaults++;
        }
        pageMap[page] = i;
    }
    return pageFaults;
}

// LFU Page Replacement
int lfuPageReplacement(vector<int>& pages, int frames) {
    unordered_map<int, int> freq, indices;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (freq.find(page) == freq.end()) {
            if (freq.size() == frames) {
                int lfuPage = -1, minFreq = INT_MAX, lruIndex = INT_MAX;
                for (auto& entry : freq) {
                    if (entry.second < minFreq || (entry.second == minFreq && indices[entry.first] < lruIndex)) {
                        minFreq = entry.second;
                        lruIndex = indices[entry.first];
                        lfuPage = entry.first;
                    }
                }
                freq.erase(lfuPage);
                indices.erase(lfuPage);
            }
            pageFaults++;
        }
        freq[page]++;
        indices[page] = i;
    }
    return pageFaults;
}

// Optimal Page Replacement
int optimalPageReplacement(vector<int>& pages, int frames) {
    set<int> pageSet;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (pageSet.find(page) == pageSet.end()) {
            if (pageSet.size() == frames) {
                int farthest = -1, replacePage = -1;
                for (int p : pageSet) {
                    int nextUse = INT_MAX;
                    for (int j = i + 1; j < pages.size(); j++) {
                        if (pages[j] == p) {
                            nextUse = j;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replacePage = p;
                    }
                }
                pageSet.erase(replacePage);
            }
            pageSet.insert(page);
            pageFaults++;
        }
    }
    return pageFaults;
}

int main() {
    int frames, n;
    cout << "Enter number of frames: ";
    cin >> frames;
    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference sequence: ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    
    cout << "FIFO Page Faults: " << fifoPageReplacement(pages, frames) << endl;
    cout << "LRU Page Faults: " << lruPageReplacement(pages, frames) << endl;
    cout << "LFU Page Faults: " << lfuPageReplacement(pages, frames) << endl;
    cout << "Optimal Page Faults: " << optimalPageReplacement(pages, frames) << endl;
    
    return 0;
}