#include <thread>
#include <iostream>
#include <semaphore.h>
#include <mutex>

#define MSG_COUNT 5

using namespace std;

sem_t sem;
mutex mtx;

int cant_a = 0;

void f1_a() {
    for (int i = 0; i < MSG_COUNT; i++) {
        cout << "Ejecutando F1 (A)\n";
        this_thread::sleep_for(100ms);
    }
}

void f1_b() {
    for (int i = 0; i < MSG_COUNT; i++) {
        cout << "Ejecutando F1 (B)\n";
        this_thread::sleep_for(200ms);
    }
}

void f2_a() {
    for (int i = 0; i < MSG_COUNT; i++) {
        cout << "Ejecutando F2 (A)\n";
        this_thread::sleep_for(500ms);
    }
}

void f2_b() {
    for (int i = 0; i < MSG_COUNT; i++) {
        cout << "Ejecutando F2 (B)\n";
        this_thread::sleep_for(10ms);
    }
}

void f1() {
    f1_a();
    mtx.lock();
    cant_a++;
    if (cant_a == 2) {
        sem_post(&sem);
        sem_post(&sem);
    }
    mtx.unlock();
    sem_wait(&sem);
    f1_b();
}

void f2() {
    f2_a();
    mtx.lock();
    cant_a++;
    if (cant_a == 2) {
        sem_post(&sem);
        sem_post(&sem);
    }
    mtx.unlock();
    sem_wait(&sem);
    f2_b();
}

int main() {
    sem_init(&sem, 1, 0);

    thread thread1 = thread(f1);
    thread thread2 = thread(f2);

    thread1.join();
    thread2.join();

    return 0;
}
