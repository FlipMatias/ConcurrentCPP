#include <iostream>
#include <thread>
using namespace std;


void sayHello()
{
    cout << "| Game over, multithreaded world.\n";
    cout << "| Omae wa mou shindeiru.\n\n";
}


int main()
{
    thread t{sayHello};
    t.join();
    return 0;
}
