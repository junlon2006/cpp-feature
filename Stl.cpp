#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <list>
#include <algorithm>
#include <forward_list>

using namespace std;

class Test {
public:
    Test(int count): m_count(count) {
        cout<<"Test "<<m_count<<endl;
    }

    ~Test() {
        cout<<"~Test "<<m_count<<endl;
    }

    int getCount() {
        return m_count;
    }

private:
    int m_count;
};

/**
 * array容器，即内存连续的定长数组，整个生命周期内存都不会重新分配，性能极佳
 * 随机访问O(1）
 */
static void __stl_array() {
    cout<<"---------- STL array ----------"<<endl;
    /**
     * 显示初始化，否则是undefined值
     */
    std::array<std::shared_ptr<Test>, 5> a = {};
    for (int i = 0; i < a.size(); i++) {
        a[i] = std::make_shared<Test>(i + 1);
    }

    /**
     * 清除所有元素
     */
    a = {};

    /**
     * O(1)随机访问
     */
    a.at(2) = std::make_shared<Test>(777);
    a[2] = std::make_shared<Test>(666);
    std::sort(a.begin(), a.end());
    std::weak_ptr<Test> wp;
    for (const auto &t : a) {
        wp = t;
        if (!wp.expired()) {
            cout<<"count="<<t->getCount()<<endl;
        }
    }

    /**
     * c string，当成c的数组用
     */
    std::array<char, 64> str;
    //std::strcpy(&str[0], "hello world");
    std::strcpy(str.data(), "hello world");
    cout<<str.data()<<endl;
}

/**
 * vector容器，即内存可变得数组，2倍扩容，类似Java ArrayList，JDK1.8是1.5倍扩容
 * 随机访问O(1）
 */
static void __stl_vector() {
    cout<<"---------- STL vector ----------"<<endl;
    std::vector<u_int32_t> v;
    for (int i = 0; i < 9; i++) {
        v.push_back(i + 1);
        cout<<"vector size="<<v.capacity()<<endl;
    }

    for (auto & a : v) {
        cout<<a<<"\t";
    }
    cout<<endl;
}

/**
 * list容器，双向链表
 */
static void __stl_list() {
    cout<<"---------- STL list ----------"<<endl;
    std::list<int> l = {1, 2, 3, 4};
    l.push_front(0);
    l.push_back(5);

    /**
     * 在3前面插入666
     */
    auto it = std::find(l.begin(), l.end(), 3);
    if (it != l.end()) {
        l.insert(it, 666);
    }

    for (auto & n : l) {
        cout<<n<<"\t";
    }

    cout<<endl;
}

/**
 * list容器，单向链表
 */
static void __stl_forward_list() {
    cout<<"---------- STL forward_list ----------"<<endl;
    std::forward_list<uint32_t> l = {1, 2, 3, 4};
    auto beginIt = l.begin();
    l.insert_after(beginIt, 0);

    for (auto &n : l) {
        cout<<n<<"\t";
    }

    cout<<endl;
}

int main() {
    __stl_array();
    __stl_vector();
    __stl_list();
    __stl_forward_list();

    return 0;
}