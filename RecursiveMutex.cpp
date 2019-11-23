#include <mutex>
#include <iostream>

using namespace std;

class square {
    public:
    square() {}

    void setWidth(int width) {
        std::lock_guard<std::recursive_mutex>(this->mutex);
        this->width = width;
    }   

    void setHeigh(int heigh) {
        std::lock_guard<std::recursive_mutex>(this->mutex);
        this->heigh = heigh;
    } 

    int calcArea(int width, int heigh) {
        std::lock_guard<std::recursive_mutex>(this->mutex);
        this->setHeigh(heigh);
        this->setWidth(width);
        return this->heigh * this->width;
    }

    private:
    std::recursive_mutex mutex;
    int width;
    int heigh;
};

int main() {
    square s;
    int area = s.calcArea(2, 3);
    cout<<"area="<<area<<endl;
    return 0;
}