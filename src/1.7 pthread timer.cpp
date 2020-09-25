#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void* helloMamma(void* thread)
{
    long tId = (long)thread;

    while (true) {
        printf("| Game over! It's me, thraed #%ld\n", tId);
        sleep(3);
    }
    pthread_exit(nullptr);
}


int main()
{
    constexpr int Num_Threads {2};
    pthread_t thread;
    long id = 999;

    int rc = pthread_create(thread, NULL, helloMamma, (void*)id);
    if (rc) {
        printf("| Failed to create thread #%ld\n", id);
        exit(-1);
    }

    pthread_exit(nullptr);
    return 0;
}
