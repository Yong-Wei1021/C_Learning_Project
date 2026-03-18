#include <stdio.h>
#include "math_utils.h"
int main() {
    int money = 500;
    int *p;

    p = &money;  // 步驟 A
    printf("money 的值: %d\n", money);
    printf("money 的地址 (&money): %p\n", (void*)&money);
    printf("紙條 p 紀錄的內容 (p): %p\n", (void*)p);
    printf("紙條 p 本身的地址 (&p): %p\n", (void*)&p);

    *p = 1000;   // 步驟 B
    printf("修改後 money 的值: %d\n", money);

    return 0;
}