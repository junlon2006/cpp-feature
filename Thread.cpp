#include <thread>
#include <vector>
#include <memory>
#include <iostream>
#include <mutex>

using namespace std;

static std::vector<std::shared_ptr<std::thread>> g_thread_list;

static void __sync_print(int idx) {
    static int32_t count = 0;
    static std::mutex lock;
    std::lock_guard<std::mutex> locker(lock);
    cout<<"["<<idx<<"]"<<" count="<<++count<<endl;
}

static void __task(int idx) {
    auto count = 0;
    while (count++ < 10000) { 
        __sync_print(idx);
        //std::this_thread::sleep_for(chrono::seconds(1));
    }
}

static int __get_cpu_count() {
    auto cpuCount = std::thread::hardware_concurrency();
    if (0 == cpuCount) {
        cout<<"get hardware cpu count failed, use default value 1"<<endl;
        cpuCount = 1;
    }
    cout<<"current cpu count="<<cpuCount<<endl;
    return cpuCount;
}

int main() {
    int cpuCount = __get_cpu_count();
    for (int i = 0; i < cpuCount; i++) {
        g_thread_list.push_back(std::make_shared<std::thread>(__task, i));
    }

    for (auto& thread : g_thread_list) {
        thread->join();
    }
 
    return 0;
}