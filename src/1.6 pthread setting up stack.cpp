#include <stdio.h>
#include <pthread.h>


constexpr int Num_Threads { 4 };
constexpr int N { 1000 };
constexpr int Mega { 1000000 };

pthread_attr_t attribute;


static void* doWork(void* thread)
{
    double a[N][N];
    long tId = (long)thread;
    size_t stacksize;

    pthread_attr_getstacksize(&attribute, &stacksize);
    printf("| Thread #%ld. Stack size: %li bytes\n", tId, stacksize);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i][j] = ((i*j)/3.452) + (N-i);
        }
    }

    pthread_exit(nullptr);
}


int main()
{
    pthread_t threads[Num_Threads];
    size_t stacksize;
    int rc;

    pthread_attr_init(&attribute);
    pthread_attr_getstacksize(&attribute, &stacksize);

    printf("| Amount of stack needed per thread: %li\n", stacksize);
    stacksize = sizeof(double) * N * N + Mega;

    pthread_attr_setstacksize(&attribute, stacksize);
    printf("| Creating threads with stack size: %li\n", stacksize);


    long t = 0;
    for (; t < Num_Threads; ++t) {
        rc = pthread_create(&threads[t], &attribute, doWork, (void*)t);
        if (rc) {
            printf("| Error: returning error on create: %d\n", rc);
            exit(-1);
        }
    }

    printf("| Created %ld threads\n", t);
    //pthread_attr_destroy(&attribute);
    pthread_exit(nullptr);
    return 0;
}
