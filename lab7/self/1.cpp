#include <bits/stdc++.h>
#include <semaphore.h>
#include <mutex>
#include <thread>

using namespace std;

int NUM_PHILS = 5;
sem_t chops[5];
mutex mut;

void think (int id) {
    mut.lock();
    cout<<"Philosopher "<<id<<" is thinking...\n";
    mut.unlock();
    sleep(1);
}

void eat (int id) {
    mut.lock();
    cout<<"Philosopher "<<id<<" is eating...\n";
    mut.unlock();
    sleep(2);
}

void philosopher(int id) {
    while (true) {
        think(id);
        
        mut.lock();
        cout<<"Philosopher "<<id<<" is hungry\n";
        mut.unlock();

        sem_wait(chops+id);
        sem_wait(chops + (id+1)%NUM_PHILS);
        
        eat(id);
        
        sem_post(chops+id);
        sem_post(chops + (id+1)%NUM_PHILS);
        
    }
}

int main() {
    vector<thread> phils;
    int i;
    for (i=0;i<NUM_PHILS;i++)
        phils.push_back(thread(philosopher, i));
    
    for (i=0;i<NUM_PHILS; i++)
        sem_init(chops+i, 0, 1);
    
    for (auto &ph : phils)
        ph.join();
    
    return 0;
}