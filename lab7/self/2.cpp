#include <bits/stdc++.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

const int num_slots = 5;
int item=0;
queue<int> buffer;
sem_t empty_slots;
sem_t full_slots;
mutex daddyMutex;

void producer(int id) {
    // int item = 0;
    while (true) {
        sleep(2);
        sem_wait(&empty_slots);
        daddyMutex.lock();
        buffer.push(item);
        cout<<"Producer "<<id<<" made "<<item++<<endl;
        daddyMutex.unlock();

        sem_post(&full_slots);
    }
}

void consumer (int id) {
    while (true) {
        sem_wait(&full_slots);
        daddyMutex.lock();
        cout<<"Consumer "<<id<<" ate "<<buffer.front()<<endl;
        buffer.pop();
        daddyMutex.unlock();
        sem_post(&empty_slots);
        sleep(1);
    }
}

int main() {
    sem_init(&empty_slots, 0, num_slots);
    sem_init(&full_slots, 0, 0);

    thread prods[] = {thread(producer, 0), thread(producer, 1)};
    thread cons[] = {thread(consumer, 0), thread(consumer, 1)};

    for (auto &pr : prods)
        pr.join();

    for (auto &cn : cons)
        cn.join();
    
    return 0;
    
}