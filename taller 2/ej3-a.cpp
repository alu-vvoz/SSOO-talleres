#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <cassert>

#define N 100
#define THREAD_COUNT 5

using namespace std;


void verify(vector<int> v1, vector<int> v2, vector<int> v3) {
    cout << "v1 = [" << v1[0] << ", " << v1[1] << ", " << ", ..., " << v1[N - 2] << ", " << v1[N - 1] << "]" << endl;
    cout << "v2 = [" << v2[0] << ", " << v2[1] << ", " << ", ..., " << v2[N - 2] << ", " << v2[N - 1] << "]" << endl;
    cout << "v3 = [" << v3[0] << ", " << v3[1] << ", " << ", ..., " << v3[N - 2] << ", " << v3[N - 1] << "]" << endl;

    for (int i = 0; i < N; ++i) {
        assert(v3[i] == v1[i] * v2[i]);
    }
}

void producto_interno(vector<int>::iterator v1_desde, vector<int>::iterator v1_hasta, vector<int>::iterator v2_desde, vector<int>::iterator v2_hasta, vector<int>::iterator v3_desde, vector<int>::iterator v3_hasta) {
    while (v1_desde != v1_hasta && v2_desde != v2_hasta && v3_desde != v3_hasta) {
        *v3_desde = *v1_desde * *v2_desde;
        v1_desde++;
        v2_desde++;
        v3_desde++;
    }
}

int main() {
    vector<int> v1(N);
    vector<int> v2(N);
    iota(v1.begin(), v1.end(), 1);
    iota(v2.begin(), v2.end(), N + 1);

    vector<int> v3(N);
    
    vector<thread> threads;
    for (int i = 0; i < THREAD_COUNT; i ++) {
        int desde = i * (N / THREAD_COUNT);
        int hasta = desde + N / THREAD_COUNT;
        threads.emplace_back(
                producto_interno,
                v1.begin() + desde, v1.begin() + hasta,
                v2.begin() + desde, v2.begin() + hasta,
                v3.begin() + desde, v3.begin() + hasta);
    }

    // TO-DO 
    
    for (int i = 0; i < THREAD_COUNT; i++) {
        threads[i].join();
    }


    verify(v1, v2, v3);

    return 0;
}
