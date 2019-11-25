#include <iostream>
#include <memory>
#include <mutex>

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
        cout<<"lock_guard "<<__FUNCTION__<<endl;
    }

    {
        std::lock_guard<std::mutex> locker(m_mutex);
        cout<<"lock_guard "<<__FUNCTION__<<endl;
    }

    std::unique_lock<std::mutex> locker(m_mutex);
    cout<<"lock_guard "<<__FUNCTION__<<endl;
}

int main () {
    RAII raii;
    raii.mutexTest();

    return 0;
}