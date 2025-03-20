#include <bits/stdc++.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

mutex reader_mu, cout_mu;
int read_count = 0;
sem_t writing;

const int NUM_READERS = 3;
const int NUM_WRITERS = 2;

void read_func(int id) {
    while (true) {
        reader_mu.lock();
        if (read_count == 0)
            sem_wait(&writing);
        read_count++;
        reader_mu.unlock();
        cout_mu.lock();
        cout<<"Reader "<<id<<" is reading...\n";
        cout_mu.unlock();

        sleep(1);

        reader_mu.lock();
        read_count--;
        cout<<"debug rC: "<<read_count<<endl;
        if (read_count == 0)
            sem_post(&writing);
        reader_mu.unlock();

        cout_mu.lock();
        cout<<"Reader "<<id<<" finished reading\n";
        cout_mu.unlock();

        sleep(2);
    }
}

void write_func(int id) {    while(true) {
        sem_wait(&writing);
        cout_mu.lock();
        cout<<"Writer "<<id<<" is writing\n";
        cout_mu.unlock();

        sleep(1.5);
        
        cout_mu.lock();
        cout<<"Writer "<<id<<" finished writing\n";
        cout_mu.unlock();
        sem_post(&writing);
        sleep(4);
    }
}

int main() {
    int i;
    sem_init(&writing, 0, 1);

    vector<thread> readers, writers;
    for (i=0; i<NUM_READERS; i++)
        readers.push_back(thread(read_func, i));

    for (i=0; i<NUM_WRITERS; i++)
        writers.push_back(thread(write_func, i));

    for (auto &th:readers)
        th.join();
    for (auto &th: writers)
        th.join();
    
    return 0;
}