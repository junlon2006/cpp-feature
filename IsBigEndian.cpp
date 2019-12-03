#include <iostream>

using namespace std;

static bool __is_big_endian() {
    uint16_t s = 0x1234;
    uint8_t c = *((uint8_t*)&s);

    std::printf("s=%x\n", s);
    std::printf("c=%x\n", c);

    /* 低地址放高位 */
    return 0x12 == c;
}

int main() {
    /* Intel cpu little endian */
    cout<<__is_big_endian()<<endl;
    return 0;
}