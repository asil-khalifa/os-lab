#include <bits/stdc++.h>
#include <semaphore.h>

#include <sys/mman.h>
#include <fcntl.h>

#define BUFF_SIZE 32

#define SM_NAME "fdfasf"
#define SEM_EMPTY "fdafadfdsfsa"
#define SEM_FULL "fda"
#define SEM_MUTEX "fdatwtw"

using namespace std;

struct SM {
    int in, out, buffer[BUFF_SIZE];
};

void producer() {
    int shm_fd = shm_open(SM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SM));
    SM* shm = (SM*)mmap(0, sizeof(SM), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    shm->in = 0;
    shm->out = 0;

    sem_t *full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, BUFF_SIZE);
    sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    for (int i=0; i<10; i++) {
        sem_wait(empty);
        sem_wait(mutex);

        cout<<"Produced "<<i<<" at "<<shm->in;
        shm->buffer[shm->in] = i;

        shm->in = (shm->in+1)%BUFF_SIZE;

        sem_post(full);
        sem_post(mutex);
        sleep(2);
    }

    sem_close(full);
    sem_close(empty);
    sem_close(mutex);

    munmap(shm, sizeof(SM));
    close(shm_fd);
}   

void consumer() {
  int shm_fd = shm_open(SM_NAME, O_RDWR, 0666);
  SM* shm = (SM*)mmap(0, sizeof(SM), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  sem_t *full = sem_open(SEM_FULL, 0);
  sem_t *empty = sem_open(SEM_EMPTY, 0);
  sem_t *mutex = sem_open(SEM_MUTEX, 0);

  for (int i=0; i<10; i++) {
    sem_wait(full);
    sem_wait(mutex);

    cout<<"Consumed "<<shm->buffer[shm->out]<<" at "<<shm->out<<endl;
    shm->out = (shm->out + 1) % BUFF_SIZE;

    sem_post(empty);
    sem_post(mutex);

    sleep(1);
  }

  sem_close(full);
  sem_close(mutex);
  sem_close(empty);

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