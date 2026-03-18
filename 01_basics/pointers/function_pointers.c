#include <stdio.h>

// 函式指標：讓我的程式可以抽換動作 (driver) 

// 1. 先寫好兩個真正的動作 (Function)
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int main() {
    // 2. 宣告一個函式指標，取名叫 operation
    // 它能指向「收兩個 int，傳回一個 int」的函式
    int (*operation)(int, int);

    // 3. 指向加法
    operation = add;
    printf("加法結果: %d\n", operation(10, 5)); // 輸出 15

    // 4. 指向乘法 (動作被抽換了！)
    operation = mul;
    printf("乘法結果: %d\n", operation(10, 5)); // 輸出 50

    return 0;
}