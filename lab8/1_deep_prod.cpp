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
    // Cleanup previous instances
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_EMPTY);
    sem_unlink(SEM_FULL);
    sem_unlink(SEM_MUTEX);

    // Create and set up shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        return EXIT_FAILURE;
    }

    if (ftruncate(shm_fd, sizeof(SharedData)) == -1) {
        perror("ftruncate failed");
        return EXIT_FAILURE;
    }

    SharedData* shared_data = static_cast<SharedData*>(
        mmap(nullptr, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
    if (shared_data == MAP_FAILED) {
        perror("mmap failed");
        return EXIT_FAILURE;
    }

    shared_data->head = 0;
    shared_data->tail = 0;

    // Create semaphores
    sem_t* empty = sem_open(SEM_EMPTY, O_CREAT | O_EXCL, 0666, BUFFER_SIZE);
    if (empty == SEM_FAILED) {
        perror("sem_open empty failed");
        return EXIT_FAILURE;
    }

    sem_t* full = sem_open(SEM_FULL, O_CREAT | O_EXCL, 0666, 0);
    if (full == SEM_FAILED) {
        perror("sem_open full failed");
        return EXIT_FAILURE;
    }

    sem_t* mutex = sem_open(SEM_MUTEX, O_CREAT | O_EXCL, 0666, 1);
    if (mutex == SEM_FAILED) {
        perror("sem_open mutex failed");
        return EXIT_FAILURE;
    }

    // Produce items
    for (int i = 0; i < 5; ++i) {
        std::cout << "Producer: Producing " << i << std::endl;
        sem_wait(empty);
        sem_wait(mutex);

        shared_data->buffer[shared_data->head] = i;
        shared_data->head = (shared_data->head + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(full);
        sleep(1); // Simulate production time
    }

    // Send termination signal
    int termination_signal = -1;
    sem_wait(empty);
    sem_wait(mutex);

    shared_data->buffer[shared_data->head] = termination_signal;
    shared_data->head = (shared_data->head + 1) % BUFFER_SIZE;

    sem_post(mutex);
    sem_post(full);
    std::cout << "Producer: Sent termination signal." << std::endl;

    // Wait for user input to allow consumer time to finish
    std::cout << "Press Enter to clean up and exit..." << std::endl;
    std::cin.get();

    // Cleanup
    munmap(shared_data, sizeof(SharedData));
    close(shm_fd);
    shm_unlink(SHM_NAME);

    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    sem_unlink(SEM_EMPTY);
    sem_unlink(SEM_FULL);
    sem_unlink(SEM_MUTEX);

    return EXIT_SUCCESS;
}