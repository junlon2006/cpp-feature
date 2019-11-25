#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class RAII {
private:
    std::mutex m_mutex;
public:
    RAII();
    ~RAII();
    void mutexTest();
};

RAII::RAII() {
    cout<<"RAII"<<endl;
}

RAII::~RAII() {
    cout<<"~RAII"<<endl;
}

void RAII::mutexTest() {
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        cout<<"lock_guard "<<__FUNCTION__<<__LINE__<<endl;
    }

    {
        std::lock_guard<std::mutex> locker(m_mutex);
        cout<<"lock_guard "<<__FUNCTION__<<__LINE__<<endl;
    }

    /* 初始状态不上锁 */
    std::unique_lock<std::mutex> locker(m_mutex, std::defer_lock);
    cout<<"unique_lock "<<__FUNCTION__<<__LINE__<<endl;
    locker.lock(); /* 锁会随着析构自动解除 */
    cout<<"unique_lock "<<__FUNCTION__<<__LINE__<<endl;
}

static void __raii_test(RAII* raii) {
    if (NULL != raii) {
        raii->mutexTest();
    }
}

int main () {
    RAII raii;

    std::thread t1(__raii_test, &raii);
    std::thread t2(__raii_test, &raii);

    t1.join();
    t2.join();
    cout<<"both thread destroy"<<endl;

    return 0;
}