#include <bits/stdc++.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

const int PHILS = 5;
mutex mut;
sem_t chops[PHILS];

void think(int id) {
    mut.lock();
    cout<<"Philosopher "<<id<<" is thinking..\n";
    mut.unlock();

    sleep(2);
}

void eat(int id) {
    sem_wait(chops + id);
    sem_wait(chops + (id+1)%PHILS);
    
    mut.lock();
    cout<<"Philospoher "<<id<<" is eating...\n";
    mut.unlock();
    
    sleep(3);
    
    sem_post(chops + id);
    sem_post(chops + (id+1)%PHILS);

}

void philosopher(int id) {
    while (true) {
        think(id);

        mut.lock();
        cout<<"Philosopher "<<id<<" is hungry!\n";
        mut.unlock();

        eat(id);
    }
}

int main() {
    for (int i=0; i<PHILS; i++)
        sem_init(chops + i, 0, 1);
    
    vector<thread> philosophers;
    for (int i=0; i<PHILS; i++) {
        philosophers.push_back(thread(philosopher, i));
    }

    for (auto &th : philosophers)
        th.join();
}