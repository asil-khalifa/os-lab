#include <bits/stdc++.h>
#include <semaphore.h>

#include <sys/mman.h>
#include <fcntl.h>

#define SM_size 128

#define SM_NAME "JoeMamaff"
#define SEM_EMPTY "bobdd"
#define SEM_FULL "catgg"
#define SEM_MUTEX "ddwd"

using namespace std;

struct SM {
    int in, out, buffer[SM_size];
};

void producer() {
    int shm_fd = shm_open(SM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SM));

    SM* shm = (SM*)mmap(0, sizeof(SM), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    shm->in = 0;
    shm->out = 0;

    sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, SM_size);
    sem_t *full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    for (int i=1; i<=10; i++) {
        sem_wait(empty);
        sem_wait(mutex);

        shm->buffer[shm->in] = i;
        cout<<"Produced: "<<i<<" at "<<shm->in<<endl;
        shm->in++;
        shm->in %= SM_size;

        sem_post(full);
        sem_post(mutex);
        sleep(1);
    }

    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    munmap(shm, sizeof(SM));
    close(shm_fd);
}   

void consumer() {
    int shm_fd = shm_open(SM_NAME, O_RDWR, 0666);
    SM* shm = (SM*)mmap(0, sizeof(SM), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    sem_t* empty = sem_open(SEM_EMPTY, 0);
    sem_t *full = sem_open(SEM_FULL, 0);
    sem_t *mutex = sem_open(SEM_MUTEX, 0);

    for (int i=1; i<10; i++) {
        sem_wait(full);
        sem_wait(mutex);

        int item = shm->buffer[shm->out];
        cout<<"Received "<<item<<" at "<<shm->out<<endl;

        shm->out++;
        shm->out %= SM_size;

        sem_post(mutex);
        sem_post(empty);
        sleep(2);
    }

    sem_close(empty);
    sem_close(full);
    sem_close(mutex);

    munmap(shm, sizeof(SM));
    close(shm_fd);
}

int main() {
    string choice;
    cout<<"Enter consumer or producer: ";
    cin>>choice;

    if (choice == "consumer")
        consumer();
    else if (choice == "producer")
        producer();
    else
        cout<<"Invalid!\n";
    
    return 0;
}