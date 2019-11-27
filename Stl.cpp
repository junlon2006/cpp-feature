#include <array>
#include <iostream>
#include <memory>

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
    a[2] = std::make_shared<Test>(666);
    std::weak_ptr<Test> wp;
    for (auto t : a) {
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



int main() {
    __stl_array();


    return 0;
}