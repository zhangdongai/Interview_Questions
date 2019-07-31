// 不借助第三个变量交换值
void swap(int* const a, int* const b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
/*
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
*/
}

// 辗转求余法
int divide_recursive(int a, int b) {
// a和b求余，如果余数为0，则b是最大公约数
// 否则，领a=b，b=余数，继续求余判断
    int mod = a % b;
    while (mod != 0) {
        a = b;
        b = mod;
        mod = a % b;
    }
    return b;
}

// 相减法
int substraction(int a, int b) {
// 如果a=b，则a或b就是最小公倍数
// 如果a>b，领a=a-b
// 如果a<b，领b=b-a
    while (a != b) {
        if (a > b)
            a -= b;
        else if (a < b)
            b -= a;
    }
    return a;
}
