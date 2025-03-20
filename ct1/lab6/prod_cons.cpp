#include <bits/stdc++.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

const int PRODS = 5;
const int CONS = 5;
queue<int> buffer;
mutex mut;
sem_t empty_slots;
sem_t full;
int item = 0;

void prod(int id) {
    while(true) {
        sem_wait(&empty_slots);
        mut.lock();
        cout<<"Producer "<<id<<" produced "<<item++<<endl;
        buffer.push(item);
        mut.unlock();

        sem_post(&full);
        sleep(2);
    }

}

void cons(int id) {
    while (true) {
        sem_wait(&full);

        mut.lock();
        cout<<"Consumer "<<id<<" consumed "<<buffer.front()<<endl;
        buffer.pop();
        mut.unlock();

        sem_post(&empty_slots);
        sleep(1);
    }
}

int main() {
    sem_init(&empty_slots, 0, 5);
    sem_init(&full, 0, 0);
    
    vector<thread> producers, consumers;
    for (int i=0; i<PRODS; i++) {
        producers.push_back(thread(prod, i));
    }
    for (int i=0; i<CONS; i++) {
        consumers.push_back(thread(cons, i));
    }

    for (auto &th : producers)
        th.join();

    for (auto &th : consumers)
        th.join();
}