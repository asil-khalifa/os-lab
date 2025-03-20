#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define SHM_NAME "shared_memory"
#define SEM_EMPTY "sem_empty"
#define SEM_FULL "sem_full"
#define SEM_MUTEX "sem_mutex"
#define BUFFER_SIZE 5

struct SharedMemory {
    int buffer[BUFFER_SIZE];
    int in, out;
};

void producer() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedMemory));
    SharedMemory* shm = (SharedMemory*)mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    shm->in = shm->out = 0;
    
    sem_t* empty = sem_open(SEM_EMPTY, O_CREAT, 0666, BUFFER_SIZE);
    sem_t* full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    sem_t* mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);
    
    for (int i = 1; i <= 10; i++) {
        sem_wait(empty);
        sem_wait(mutex);
        
        shm->buffer[shm->in] = i;
        std::cout << "Produced: " << i << " at index " << shm->in << std::endl;
        shm->in = (shm->in + 1) % BUFFER_SIZE;
        
        sem_post(mutex);
        sem_post(full);
        sleep(1);
    }
    
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    munmap(shm, sizeof(SharedMemory));
    close(shm_fd);
}

void consumer() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    SharedMemory* shm = (SharedMemory*)mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    sem_t* empty = sem_open(SEM_EMPTY, 0);
    sem_t* full = sem_open(SEM_FULL, 0);
    sem_t* mutex = sem_open(SEM_MUTEX, 0);
    
    for (int i = 1; i <= 10; i++) {
        sem_wait(full);
        sem_wait(mutex);
        
        int item = shm->buffer[shm->out];
        std::cout << "Consumed: " << item << " from index " << shm->out << std::endl;
        shm->out = (shm->out + 1) % BUFFER_SIZE;
        
        sem_post(mutex);
        sem_post(empty);
        sleep(2);
    }
    
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    munmap(shm, sizeof(SharedMemory));
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
