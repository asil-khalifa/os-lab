#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cerrno>

const char* SHM_NAME = "/prodcons_shm";
const char* SEM_EMPTY = "/prodcons_empty";
const char* SEM_FULL = "/prodcons_full";
const char* SEM_MUTEX = "/prodcons_mutex";
const int BUFFER_SIZE = 5;

struct SharedData {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
};

int main() {
    // Open existing shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        return EXIT_FAILURE;
    }

    SharedData* shared_data = static_cast<SharedData*>(
        mmap(nullptr, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
    if (shared_data == MAP_FAILED) {
        perror("mmap failed");
        return EXIT_FAILURE;
    }

    // Open existing semaphores
    sem_t* empty = sem_open(SEM_EMPTY, 0);
    if (empty == SEM_FAILED) {
        perror("sem_open empty failed");
        return EXIT_FAILURE;
    }

    sem_t* full = sem_open(SEM_FULL, 0);
    if (full == SEM_FAILED) {
        perror("sem_open full failed");
        return EXIT_FAILURE;
    }

    sem_t* mutex = sem_open(SEM_MUTEX, 0);
    if (mutex == SEM_FAILED) {
        perror("sem_open mutex failed");
        return EXIT_FAILURE;
    }

    // Consume items
    while (true) {
        sem_wait(full);
        sem_wait(mutex);

        int item = shared_data->buffer[shared_data->tail];
        shared_data->tail = (shared_data->tail + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(empty);

        if (item == -1) {
            std::cout << "Consumer: Received termination signal. Exiting..." << std::endl;
            break;
        }

        std::cout << "Consumer: Consumed " << item << std::endl;
        sleep(2); // Simulate consumption time
    }

    // Cleanup
    munmap(shared_data, sizeof(SharedData));
    close(shm_fd);

    sem_close(empty);
    sem_close(full);
    sem_close(mutex);

    return EXIT_SUCCESS;
}