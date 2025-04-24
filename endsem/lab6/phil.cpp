#include <bits/stdc++.h>
#include <semaphore.h>
// #include <mutex>

using namespace std;

mutex mu;
sem_t sems[6];

void eat(int i) {
    mu.lock();
    cout<<"Phil "<<i<<" is hungry\n";
    mu.unlock();   

    sem_wait(sems+i);
    sem_wait(sems+(i+1)%6);
    mu.lock();
    cout<<"Phil "<<i<<" is eating\n";
    mu.unlock();   
    sleep(3);
    sem_post(sems+i);
    sem_post(sems+(i+1)%6);
}

void philosopher(int i) {
    while(1) {
        mu.lock();
        cout<<"Phil "<<i<<" is thinking...\n";
        mu.unlock();

        sleep(2);

        eat(i);
    }
}

int main() {
    for (int i=0; i<6; i++)
        sem_init(sems+i, 0, 1);

    vector<thread> phils;
    for (int i=0; i<6; i++)
        phils.push_back(thread(philosopher, i));

    for (auto &th : phils)
        th.join();
}