#include <iostream>

using namespace std;

class StackOnly {
    public:
    StackOnly() {
        cout<<"construct"<<endl;
        m_number = 1;
    }
    StackOnly(const StackOnly &other) {
        cout<<"cope construct"<<endl;
        this->m_number = other.m_number;
    }
    ~StackOnly() {
        cout<<"destruct"<<endl;
    }
    int getNumber() {
        return this->m_number;
    }

    /* 核心代码，重载new和delete，然后设置成private属性，外面就不能new了，也就不能在堆上开辟对象 */
    private:
    void* operator new(size_t size) {
        /* do nothing */
        return NULL;
    }
    void operator delete(void *ptr) {
        /*do nothing*/
    }
    int m_number;

};

int main(int argc, const char* argv[]) {
    StackOnly s, *ps;
    cout<<s.getNumber()<<endl;
    ps = new StackOnly; /*编译错误*/
    cout<<ps->getNumber();
    delete ps;
    StackOnly s1 = s;
    cout<<s1.getNumber()<<endl;
    return 0;
}