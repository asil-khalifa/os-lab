#include <bits/stdc++.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

const int n = 6;
int cnt = 1;
mutex mu;
queue<int> q;
sem_t empty_slots, full;

void consumer(int i) {
    while(1) {
        sem_wait(&full);

        mu.lock();
        cout<<"Consumer "<<i<<" used "<<q.front()<<endl;
        q.pop();
        mu.unlock();

        sem_post(&empty_slots);

        sleep(3);
    }
}

void producer(int i) {
    while(1) {
        sem_wait(&empty_slots);
        
        mu.lock();
        cout<<"Producer "<<i<<" made "<<++cnt<<endl;
        q.push(cnt);
        mu.unlock();

        sem_post(&full);

        sleep(3);
    }
}

int main() {
    sem_init(&empty_slots, 0, n);
    sem_init(&full, 0, 0);

    vector<thread> prods, cons;

    for (int i=0; i<n; i++) {
        prods.push_back(thread(producer, i));
        cons.push_back(thread(consumer, i));
    }

    for (auto &th : prods)
        th.join();

    for (auto &con: cons)
        con.join();
}