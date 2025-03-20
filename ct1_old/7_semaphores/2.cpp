#include <bits/stdc++.h>
#include <mutex>
#include <semaphore.h>

using namespace std;

mutex mu;
const int NUM_CONS = 5;
const int NUM_PRODS = 5;
sem_t full_slots;
sem_t empty_slots;
queue<int> buffer;
int item = 1;

void print_action(string text, int id)
{
    mu.lock();
    printf("%s %d\n", text, id);
    mu.unlock();
}

void producer(int id) {
    while (true) {
        sleep(2);
        sem_wait(&empty_slots);
        mu.lock();
        buffer.push(item);
        cout<<"Producer "<<id<<" made "<<item++<<endl;
        mu.unlock();

        sem_post(&full_slots);
    }
}
void consumer(int id) {
    while(true) {
        sem_wait(&full_slots);
        mu.lock();
        cout<<"Consumer "<<id<<" ate "<<buffer.front()<<endl;
        buffer.pop();
        mu.unlock();

        sem_post(&empty_slots);
        sleep(1.5);
    }
}

int main()
{
    int i;
    sem_init(&empty_slots, 0, 5);
    sem_init(&full_slots, 0, 0);

    vector<thread> cons, prods;
    for (i = 0; i < NUM_CONS; i++)
        cons.push_back(thread(consumer, i));

    for (i = 0; i < NUM_PRODS; i++)
        cons.push_back(thread(producer, i));

    for (auto &th : cons)
        th.join();

    for (auto &th : prods)
        th.join();

    return 0;
}