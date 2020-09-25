#include <stdio.h>
#include <math.h>
#include <pthread.h>


void* myTask(void* thread)
{
    long threadId = (long)thread;

    double result = 0;
    for (int i = 0; i < 1000000; ++i)
        result += sin(i) + tan(i);

    printf("| Thread #%ld done. Result: %e\n", threadId, result);
    pthread_exit((void*)thread);
}


int main()
{
    constexpr int Num_Threads {4};

    pthread_t threads[Num_Threads];
    pthread_attr_t attribute;
    int rc;
    void* status;

    pthread_attr_init(&attribute);
    pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_JOINABLE); //could be DETACH for not waiting

    for (long t = 0; t < Num_Threads; ++t)
    {
        printf("| Main: creating thread #%ld\n", t);

        rc = pthread_create(&threads[t], &attribute, myTask, (void*)t);
        if (rc) {
            printf("| Error: returning error on create: %d\n", rc);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attribute);
    for (long t = 0; t < Num_Threads; ++t)
    {
        rc = pthread_join(threads[t], &status);
        if (rc) {
            printf("| Error: returning error on joinning: %d\n", rc);
            exit(-1);
        }

        printf("| Completed joinning thread #%ld with code: %ld\n", t, (long)status);
    }

    printf("| Ending main thread...\n\n");
    pthread_exit(nullptr);
    return 0;
}
