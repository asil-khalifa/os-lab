#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <unistd.h>
#include <mutex>

using namespace std;

const int NUM_PHILOSOPHERS = 5;
sem_t chopsticks[NUM_PHILOSOPHERS];
mutex printMutex; // To prevent mixed console output

void think(int id) {
    printMutex.lock();
    cout << "Philosopher " << id << " is thinking...\n";
    printMutex.unlock();
    sleep(1);
}

void eat(int id) {
    printMutex.lock();
    cout << "Philosopher " << id << " is eating...\n";
    printMutex.unlock();
    sleep(2);
}

void philosopher(int id) {
    while (true) {
        think(id);
        
        // Pick up chopsticks
        sem_wait(&chopsticks[id]);
        sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);

        eat(id);

        // Put down chopsticks
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
    }
}

int main() {
    vector<thread> philosophers;

    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers.emplace_back(philosopher, i);
    }

    // Join threads (though they will run indefinitely)
    for (auto& ph : philosophers) {
        ph.join();
    }

    return 0;
}
