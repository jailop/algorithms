#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
int32_t number = 0;

void increment() {
    mtx.lock();
    for (int32_t i = 0; i < 100000; i++)
        number++;
    mtx.unlock();
}

int main() {
    thread t1(increment);
    thread t2(increment);
    t1.join();
    t2.join();
    cout << number << endl;
    return 0;
}
