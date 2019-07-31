#include <stdio.h>
#include "digit_math.h"

int main(int argc, char** argv) {
    int digit_a = 0;
    int digit_b = 0;
    scanf("%d %d", &digit_a, &digit_b);
    // 确保digit_a是大值
    if (digit_a < digit_b)
        swap(&digit_a, &digit_b);

//    int g_divisor = divide_recursive(digit_a, digit_b);
    int g_divisor = substraction(digit_a, digit_b);
    printf("greatest divisor = %d\n", g_divisor);
    return 0;
}
