#include <stdio.h>
#include <pthread.h>


void* helloMamma(void* thread)
{
    long tId = (long)thread;
    printf("| Game over! It's me, thred #%ld\n", tId);
    pthread_exit(nullptr);
}


int main()
{
    constexpr int Num_Threads {2};
    pthread_t threads[Num_Threads];

    int rc;

    for (long t = 0; t < Num_Threads; ++t)
    {
        printf("| In main: creating thread %ld\n", t);

        rc = pthread_create(&threads[t], NULL, helloMamma, (void*)t);
        if (rc) {
            printf("| Failed to create thread #%ld\n", t);
            exit(-1);
        }
    }

    pthread_exit(nullptr);
    return 0;
}
