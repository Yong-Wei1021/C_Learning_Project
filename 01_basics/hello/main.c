#include <stdio.h>
// function
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
// 這個函式不拿「值」，它拿「地址」，透過地址去改值。
void update(int *p) { 
    // p 裡面現在存的是 main 裡面 data 的地址 (比如 0x1000)
    // *p = 0xFF 意思就是：去 0x1000 那個櫃子，把裡面的東西換成 0xFF
    *p = 0xFF; 
}
// 傳入 int **ptr_ptr，代表「指標的地址」
void change_address(int **ptr_ptr, int *target) {
    // *ptr_ptr 代表「那張紙條本身」
    // 我們把 target (新地址) 寫到紙條上
    *ptr_ptr = target; 
}


//重點: 使用者，看看公告有哪些function可以用
int main() {
    int a = 10;
    int b = 20;
    int c = 999;
    int money = 500;    
    // 相加
    int sum = add(a, b);
    printf("sum = %d\n", sum);
    // 將a清0 (輸入a的位址)
    set_zero(&a);
    printf("a after set_zero = %d\n", a);
    // x和y互換
    int x=10, y=20;
    swap(&x,&y);
    printf("x=%d,y=%d\n",x,y);

    // Pointers
     int *p = &money; // p指向money
    // 看money的位址
    printf("原本p指向的位址: %p\n", (void*)p); // p = &money
    printf("原本p指向的值: %d\n", *p);
    // 將money改為0xFF = 255
    update(&money);
    printf("修改後的money: %d\n", money);
    // 變數位址不得修改，只能改指向(指標的指標)

    change_address(&p,&c); // 想讓p指向c，傳入p的位址
    printf("現在p指向的位址: %p\n", (void*)p);

    printf("現在p指向的值:%d\n", *p);


    return 0; //程式結束
}
