#include <iostream>

int reverse(int raw_i) {
    int ret_i = 0;
    int mod = raw_i % 10;
    int div = raw_i / 10;
    // 判断条件是余数是否为0，这个需要注意
    while (mod != 0) {
        // 结果乘以10
        ret_i *= 10;
        // 乘以10后加上余数
        ret_i += mod;
        // 对除继续求余
        mod = div % 10;
        // 对除继续求除
        div = div / 10;
    }
 
    // 小cookie，符号并不需要特殊处理，因为如果是负数，则余和除恒为负数
    // 所有的加乘除操作都是直接操作了负数。所以符号位得到保留
    return ret_i;
}

int main(int argc, char** argv) {
    int raw_i;
    std::cin >> raw_i;
    std::cout << reverse(raw_i) << std::endl;
    return 0;
}
