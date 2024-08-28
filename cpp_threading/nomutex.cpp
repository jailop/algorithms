#include <iostream>
#include <thread>

using namespace std;

int32_t number = 0;

void increment() {
    for (int32_t i = 0; i < 100000; i++)
        number++;
}

int main() {
    thread t1(increment);
    thread t2(increment);
    t1.join();
    t2.join();
    cout << number << endl;
    return 0;
}
