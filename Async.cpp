#include <iostream>
#include <future>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

static int __task(int& x) {
    while (x < 10) {
        x += 2;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return x;
}

static int __try_get_future_result_with_timeout(std::future<int>& fut) {
    std::future_status status;
    do {
        status = fut.wait_for(std::chrono::seconds(1));
        if (std::future_status::deferred == status) {
            cout<<"deferred"<<endl;
        } else if (std::future_status::timeout == status) {
            cout<<"timeout"<<endl;
        } else if (std::future_status::ready == status) {
            cout<<"ready"<<endl;
        } else {
            cout<<"invalid"<<endl;
        }
    } while (std::future_status::ready != status);

    if (std::future_status::ready == status) {
        int ret = fut.get();
        cout<<"get async result="<<ret<<endl;
        return ret;
    }

    return -1;
}

int main() {
    int x = 1;
    std::future<int> f1 = std::async(std::launch::async, __task, std::ref(x));
    int ret;
    
    /* 接口get阻塞等待，直到异步操作结果返回 */
    //ret = f1.get();

    /* 带超时等待的接口wait_for */
    ret = __try_get_future_result_with_timeout(f1);

    cout<<ret<<endl;
    cout<<x<<endl;
    return 0;
}