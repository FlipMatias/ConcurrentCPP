#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

#ifdef WIN32
    #include <windows.h>
#endif


static bool isRunning = true;


void chapolin()
{
    printf("| Chapolin thread's id is: %d\n", std::this_thread::get_id());

    while (isRunning) {
        printf("| Não contavam com a minha astúcia!! :)\n");
        std::this_thread::sleep_for(2s);
    }
}


void chaves()
{
    printf("| Chaves thread's id is: %d\n", std::this_thread::get_id());

    while (isRunning) {
        printf("| Foi sem querer querendo... :(\n");
        std::this_thread::sleep_for(2s);
    }
}


int main()
{
    #ifdef WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    std::thread chapolinThread {chapolin};
    std::thread chavesThread {chaves};

    getchar();
    isRunning = false;

    chapolinThread.join();
    chavesThread.join();

    return 0;
}
