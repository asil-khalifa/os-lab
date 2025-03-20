#include <bits/stdc++.h>
#include <semaphore.h>
#include <mutex>
#include <thread>

using namespace std;

int NUM_CONS = 2;
int NUM_PRODS = 5;
int NUM_SLOTS = 5;
int item=0;
queue<int> buffer;
sem_t full_slots;
sem_t empty_slots;
mutex mut;

void producer(int id) {
    while (true) {
        sleep(2);
        sem_wait(&empty_slots);
        
        mut.lock();
        buffer.push(item);
        cout<<"producer "<<id<<" made "<<item++<<endl;
        mut.unlock();

        sem_post(&full_slots);

    }
}

void consumer(int id) {
    while (true) {
        sem_wait(&full_slots);

        mut.lock();
        cout<<"Consumer "<<id<<" ate "<<buffer.front()<<endl;
        buffer.pop();
        mut.unlock();

        sem_post(&empty_slots);
        sleep(1);
    }
}

int main() {
    // cout<<"HI";
    vector<thread> cons, prods;
    int i;
    sem_init(&full_slots, 0, 0);
    sem_init(&empty_slots, 0, NUM_SLOTS);

    for (i=0; i<NUM_CONS;i++)
        cons.push_back(thread(consumer, i));
    
    for (i=0; i<NUM_PRODS; i++)
        prods.push_back(thread(producer, i));
    

    for (auto &th : prods)
        th.join();

    for (auto &cn : cons)
        cn.join();

    return 0;
}