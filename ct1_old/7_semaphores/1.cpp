#include <bits/stdc++.h>
#include <mutex>
#include <semaphore.h>

using namespace std;

mutex mu;
const int NUM_PHILS = 5;
sem_t chops[NUM_PHILS];

void print_action(int id, string action) {
    mu.lock();
    cout<<"Philosopher "<<id<<" is "<<action<<" \n";
    mu.unlock();
}

void think(int id) {
    print_action(id, "thinking...");
    sleep(2);
}

void philosopher(int id) {
    while (true) {
        think(id);

        print_action(id, "hungry");

        sem_wait(chops+id);
        sem_wait(chops + (id+1)%NUM_PHILS);
        
        print_action(id, "eating...");
        
        sleep(3);

        sem_post(chops+id);
        sem_post(chops + (id+1)%NUM_PHILS);
        
    }
}

int main() {
    int i;
    for (i=0; i<NUM_PHILS; i++)
        sem_init(chops+i, 0, 1);
    
    vector<thread> phils;
    for (i=0; i<NUM_PHILS; i++)
        phils.push_back(thread(philosopher, i));
    
    for (auto &th : phils)
        th.join();

    return 0;
}