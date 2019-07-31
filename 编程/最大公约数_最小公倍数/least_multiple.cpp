#include <stdio.h>
#include "digit_math.h"

int main(int, char**) {
    int digit_a = 0;
    int digit_b = 0;
    scanf("%d %d", &digit_a, &digit_b);
    // 确保digit_a是大值
    if (digit_a > digit_b)
        swap(&digit_a, &digit_b);

    int g_divisor = substraction(digit_a, digit_b);
    // digit_a和digit_b的乘积处于它们的最大公约数就是最大公倍数
    int l_multiple = (digit_a * digit_b) / g_divisor;
    printf("least multiple = %d\n", l_multiple);
    return 0;
}
