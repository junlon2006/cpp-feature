#include <list>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <string>
#include <memory>
#include <thread>

using namespace std;

template<typename T>
class SimpleSyncQueue {
public:
    SimpleSyncQueue() {
    }

    void Put(const T& x) {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    void Take(T& x) {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] {return !m_queue.empty();});
        x = m_queue.front();
        m_queue.pop_front();
    }

    bool Empty() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    size_t Size() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
};

class Food {
public:
    Food(string name): m_name(name) {
        cout<<"Food"<<m_name<<" ["<<this<<"]"<<endl;
    }

    string getName() {
        return m_name;
    }

    ~Food() {
        cout<<"~Food"<<m_name<<" ["<<this<<"]"<<endl;
    }
private:
    Food(const Food & other) {

    }
    string m_name;
};

static void __producer(std::shared_ptr<SimpleSyncQueue<std::shared_ptr<Food>>> foodQueue) {
    static int idx = 0;
    char name[64];
    snprintf(name, sizeof(name), "food%d", ++idx);
    std::shared_ptr<Food> food = std::make_shared<Food>(name);
    cout<<"produce food "<<name<<" ["<<food<<"]"<<endl;
    foodQueue->Put(food);
}

static void __cook_task(std::shared_ptr<SimpleSyncQueue<std::shared_ptr<Food>>> foodQueue) {
    while (true) {
        __producer(foodQueue);
        std::this_thread::sleep_for(std::chrono::microseconds(1000 * 1000));
    }
}

static void __consumer(std::shared_ptr<SimpleSyncQueue<std::shared_ptr<Food>>> foodQueue) {
    std::shared_ptr<Food> food;
    foodQueue->Take(food);
    cout<<"eat food "<<food->getName()<<" ["<<food<<"]"<<endl;
}

static void __foodie_task(std::shared_ptr<SimpleSyncQueue<std::shared_ptr<Food>>> foodQueue) {
    while (true) {
        __consumer(foodQueue);
    }
}

int main() {
    std::shared_ptr<SimpleSyncQueue<std::shared_ptr<Food>>> foodQueue = std::make_shared<SimpleSyncQueue<shared_ptr<Food>>>();
    std::shared_ptr<std::thread> foodieThread = std::make_shared<std::thread>(__foodie_task, foodQueue);
    std::shared_ptr<std::thread> cookThread = std::make_shared<std::thread>(__cook_task, foodQueue);
    cookThread->join();
    foodieThread->join();

    return 0;
}