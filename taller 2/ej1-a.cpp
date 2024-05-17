#include <thread>
#include <vector>
#include <iostream>
#include <unistd.h>

#define CANT_THREADS 10

using namespace std;

void f(int i) {
    this_thread::sleep_for(i * 1000ms);
    cout << "Soy el proceso " << i << endl;
}


int main() {
    vector<thread> threads;
    
    for (int i = 0; i < CANT_THREADS; i++) {
        threads.emplace_back(f, i);
    }
    
    for (int i = 0; i < CANT_THREADS; i++) {
        threads[i].join();
    }
    return 0;
}
