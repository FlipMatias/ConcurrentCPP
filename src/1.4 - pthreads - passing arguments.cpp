#include <string>
#include <stdio.h>
#include <pthread.h>


struct ThreadInfo
{
    int threadId;
    int val;
    std::string name;
};


void* helloMamma(void* thread)
{
    auto info = *(ThreadInfo*)thread;
    printf("| Thread id: %d\n", info.threadId);
    printf("| Thread name: %s\n", info.name.c_str());
    printf("| Thread val: %d\n", info.val);
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

        ThreadInfo ti { t, (t*999), "Something"};

        rc = pthread_create(&threads[t], NULL, helloMamma, &ti);
        if (rc) {
            printf("| Failed to create thread #%ld\n", t);
            exit(-1);
        }
    }

    pthread_exit(nullptr);
    return 0;
}
