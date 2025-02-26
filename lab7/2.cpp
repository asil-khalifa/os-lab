#include <iostream>
#include <thread>
#include <queue>
#include <semaphore.h>
#include <unistd.h>
#include <mutex>

using namespace std;

const int BUFFER_SIZE = 5;
queue<int> buffer;
sem_t emptySlots;
sem_t fullSlots;
mutex bufferMutex;

void producer(int id) {
    int item = 0;
    while (true) {
        sleep(1); // Simulating production time
        sem_wait(&emptySlots); // Wait if buffer is full

        bufferMutex.lock();
        buffer.push(item);
        cout << "Producer " << id << " produced item " << item++ << "\n";
        bufferMutex.unlock();

        sem_post(&fullSlots); // Increase filled slots
    }
}

void consumer(int id) {
    while (true) {
        sem_wait(&fullSlots); // Wait if buffer is empty

        bufferMutex.lock();
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed item " << item << "\n";
        bufferMutex.unlock();

        sem_post(&emptySlots); // Increase available slots
        sleep(2); // Simulating consumption time
    }
}

int main() {
    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);

    thread producers[] = { thread(producer, 1), thread(producer, 2) };
    thread consumers[] = { thread(consumer, 1), thread(consumer, 2) };

    for (auto& p : producers) p.join();
    for (auto& c : consumers) c.join();

    return 0;
}
