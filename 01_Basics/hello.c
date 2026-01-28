#include <stdio.h>

int main() {
    printf("Hello, Coder from Linux C on WSL!\n");
    printf("You are a handsome boy!\n");
    int a = 10;
    int *p = &a;
    printf("a = %d\n", a);
    printf("p (address) = %p\n", p);
    printf("*p (value) = %d\n", *p);
    return 0;
}