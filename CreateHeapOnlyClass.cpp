#include <iostream>

using namespace std;

class HeapOnly {
    public:
    /* 提供一个静态的方法获取对象 */
    static HeapOnly* getHeapInstance() {
        return new HeapOnly;
    }

    ~HeapOnly() {
        cout<<"destruct"<<endl;
    }

    /*将普通构造函数、拷贝构造函数都设置成private*/
    private:
    HeapOnly() {
        cout<<"construct"<<endl;
    }

    HeapOnly(const HeapOnly& other) {
        cout<<"cope construct"<<endl;
    }
};

int main(int argc, const char *argv[]) {
    HeapOnly *h = HeapOnly::getHeapInstance();
    cout<<h<<endl;
    delete h;
    //HeapOnly heap = *h; /*打开注释，则编译错误*/
    return 0;
}