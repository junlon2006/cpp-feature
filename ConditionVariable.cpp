#include <mutex>
#include <thread>
#include <condition_variable>
#include <list>
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class SyncQueue {
public:
    SyncQueue(int maxSize): m_maxSize(maxSize) {
    }

    void Put(const T& x) {
        std::lock_guard<std::mutex> locker(m_mutex);
        while (IsFull()) {
            cout<<"queue full"<<endl;
            m_notFull.wait(m_mutex);
        }
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    void Take(T& x) {
        std::lock_guard<std::mutex> locker(m_mutex);
        while (IsEmpty()) {
            m_notEmpty.wait(m_mutex);
        }

        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

    bool Empty() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    bool Full() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size() == m_maxSize;
    }

    size_t Size() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

    int Count() {
        return m_queue.size();
    }

private:
    SyncQueue(const SyncQueue & other) {
    }

    bool IsFull() const {
        return m_queue.size() == m_maxSize;
    }

    bool IsEmpty() const {
        return m_queue.empty();
    }

    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable_any m_notEmpty;
    std::condition_variable_any m_notFull;
    int m_maxSize;
};

static void __consumer_task(SyncQueue<int> *queue) {
    int frameId = 0;
    while (true) {
        queue->Take(frameId);
        cout<<"take data "<<frameId<<endl;
    }
}

static void __producer_task(SyncQueue<int> *queue) {
    int frameId = 0;
    while (true) {
        cout<<"producer data "<<++frameId<<endl;
        queue->Put(frameId);
        std:this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    int maxSize = 8;
    SyncQueue<int> queue(maxSize);
    std::thread consumer(__consumer_task, &queue);
    std::thread producer(__producer_task, &queue);

    producer.join();
    consumer.join();

    return 0;
}