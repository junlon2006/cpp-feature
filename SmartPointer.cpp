#include <memory>
#include <iostream>

using namespace std;

class SmartPointer : public std::enable_shared_from_this<SmartPointer> {
public:
    SmartPointer(int data): m_data(data) {
        cout<<"SmartPointer"<<endl;
    }

    ~SmartPointer() {
        cout<<"~SmartPointer"<<endl;
    }

    int getData() {
        return m_data;
    }

    std::shared_ptr<SmartPointer> getMySelfSmartPointer() {
        return shared_from_this();
    }

private:
    int m_data;
};

int main() {
    cout<<"--------------------------------------"<<endl;
    /* 构造函数赋值 */
    std::shared_ptr<SmartPointer> smartPointer1(new SmartPointer(1));
    cout<<smartPointer1->getData()<<endl;
    cout<<"smartPointer1="<<smartPointer1<<endl;
    cout<<"smartPointer1.get()="<<smartPointer1.get()<<endl;

    cout<<"--------------------------------------"<<endl;
    /* 使用make_shared方法 */
    std::shared_ptr<SmartPointer> smartPointer2 = std::make_shared<SmartPointer>(2);
    cout<<smartPointer2->getData()<<endl;

    cout<<"--------------------------------------"<<endl;
    /* 用一个已存在的智能指针赋值 */
    std::shared_ptr<SmartPointer> smartPointer3 = smartPointer2;
    cout<<smartPointer3->getData()<<endl;
    cout<<smartPointer3<<endl;
    cout<<smartPointer3->getMySelfSmartPointer()<<endl;
    cout<<smartPointer3->shared_from_this()<<endl;

    return 0;
}