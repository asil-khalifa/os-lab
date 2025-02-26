#include <bits/stdc++.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

const int num_phils = 5;
sem_t chops[num_phils];
mutex mommyMutex;

void think(int id)
{
    mommyMutex.lock();
    cout << "Philosopher " << id << " is thinking...\n";
    mommyMutex.unlock();

    sleep(1);
}

void eat(int id)
{
    mommyMutex.lock();
    cout << "Philosopher " << id << " is eating...\n";
    mommyMutex.unlock();
    sleep(2);
}

void philosopher(int id)
{
    while (true)
    {
        think(id);

        mommyMutex.lock();
        cout << "Philosopher " << id << " is hungry...\n";
        mommyMutex.unlock();

        sem_wait(chops + id);
        sem_wait(chops + (id + 1) % num_phils);

        eat(id);

        sem_post(chops + id);
        sem_post(chops + (id + 1) % num_phils);
    }
}

int main()
{
    vector<thread> phils;
    for (int i = 0; i < num_phils; i++)
    {
        phils.emplace_back(philosopher, i);
    }

    for (int i = 0; i < num_phils; i++)
    {
        sem_init(chops + i, 0, 1);
    }

    for (auto &ph : phils)
        ph.join();

    return 0;
}