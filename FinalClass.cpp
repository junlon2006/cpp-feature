#include <iostream>

using namespace std;

template <typename T>
class BasePrivate {
    friend T;

    private:
    BasePrivate() {
        cout<<"BasePrivate construct"<<endl;
    }

    BasePrivate(const BasePrivate &other) {
        cout<<"BasePrivate copy construct"<<endl;
    }

    ~BasePrivate() {
        cout<<"BasePrivate destruct"<<endl;
    }
};

/*必须是虚继承*/
class FinalClass : public virtual BasePrivate<FinalClass> {
    public:
    FinalClass() {
        cout<<"FinalClass construct"<<endl;
    }

    FinalClass(const FinalClass &other) {
        cout<<"FinalClass copy construct"<<endl;
    }

    ~FinalClass() {
        cout<<"FinalClass destruct"<<endl;
    }
};

/*
class ClassA : public FinalClass {
    public:
    ClassA() {
        cout<<"ClassA construct"<<endl;
    }

    ClassA(const ClassA &other) {
        cout<<"ClassA copy construct"<<endl;
    }

    ~ClassA() {
        cout<<"ClassA destruct"<<endl;
    }
};
*/

int main(int argc, const char *argv[]) {
    FinalClass f;
    return 0;
}