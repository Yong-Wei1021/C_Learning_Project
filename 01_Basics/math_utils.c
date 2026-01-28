#include "math_utils.h"

//實作: like工程師本人操作 => 會與公告欄相同
int add(int a, int b) {
    return a + b;
}

void set_zero(int *x) {
    *x = 0;
}

// 交換
void swap(int*a, int*b) {
    int temp =*a; //temp放a的位址
    *a = *b; // a位址更改為b的位址
    *b=temp; // b為temp內的位址(a)
}

// 這個函式不拿「值」，它拿「地址」
void update(unsigned char *p) { 
    // p 裡面現在存的是 main 裡面 data 的地址 (比如 0x1000)
    // *p = 0xFF 意思就是：去 0x1000 那個櫃子，把裡面的東西換成 0xFF
    *p = 0xFF; 
}