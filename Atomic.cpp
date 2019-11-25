#include <thread>
#include <iostream>

using namespace std;

static void __inc(std::atomic<int32_t>& a) {
    int incTime = 10000;
    while (incTime--) a++;
}

#define PID_CNT (8)
int main() {
    std::atomic<int32_t> a(0);
    std::thread pids[PID_CNT];

    for (int i = 0; i < PID_CNT; i++) {
        pids[i] = std::thread(__inc, std::ref(a));
    }

    for (int i = 0; i < PID_CNT; i++) {
        pids[i].join();
    }

    cout<<a<<endl;

    return 0;
}
