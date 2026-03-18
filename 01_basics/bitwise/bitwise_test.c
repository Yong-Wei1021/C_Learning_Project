#include <stdio.h>
 // intial = 0x00 = 0000 0000
 // (1<<X):將1這個數字往左推X格，(1<<0) = 0000 0001
 // (1>>X):右移X格，同上

 /* 定義在檔案最上方, include下 */
#define SET_BIT(VAR, POS)   ((VAR) |=  (1 << (POS)))
#define CLR_BIT(VAR, POS)   ((VAR) &= ~(1 << (POS)))
#define TGL_BIT(VAR, POS)   ((VAR) ^=  (1 << (POS)))
#define CHK_BIT(VAR, POS)   (((VAR) >> (POS)) & 1) //右移
/* 使用起來就像 Function */

int main() {
    unsigned char header = 0x00; // 0000 0000 (二進位), char: 8bits (1 byte)
    // unsigned 8bits (0~255), 0x代表16進制，一個16進位數字可代表4bits
    // 0x0 = 二進制的 0000, 0x00 = 0000 0000
    unsigned char stack = 0x10;
    printf("測試格式化字串 (16進位): 0x%02X\n", stack); // 預期 0x10 = 0001 0000
    // OR運算
    //stack |= (1 << 3); //預期 0x18 = 0001 1000, stack = stack | (1 << 3)
    SET_BIT(stack,3);
    printf("測試移位格式化字串 (16進位): 0x%02X\n", stack); // 預期 0x18
    stack |=(1 << 0); // 預期 = 0001 1001 
    printf("測試二次移位格式化字串 (16進位): 0x%02X\n", stack); // 預期 0x19
    // toggle 反相運算
    stack = stack ^ (1 << 0); //預期 = 0001 1000, stack^= (1<<0)
    printf("測試反相格式化字串 (16進位): 0x%02X\n", stack);
    // Extract 取出某個bit=>假設取出第4個bit
    int bit_val = (stack >> 4) & 1; // >> index:想看的bit推至最右邊, &1 (0000 0001):其他位清0只留最後一位
    printf("第 4 位元的數值是: %d\n", bit_val);

    // Clear 清0運算
    stack &= ~(1<<3); //預期 = 0001 0000
    printf("測試清除格式化字串 (16進位): 0x%02X\n", stack);

    // 迴圈印出二進位
    // 從最高位 (7) 往最低位 (0) 檢查
    for (int i = 7; i >= 0; i--) {
        // 1. 把資料右移 i 位，讓目標 bit 跑到第 0 位
        // 2. 使用 & 1 濾掉其他位元
        int bit = (stack >> i) & 1;
        printf("%d", bit);
        
        // 每 4 位印一個空格，方便閱讀
        if (i == 4) printf(" ");
    }
    printf("\n");



    // header (將第 7 位元設為 1)
    header |= (1 << 7); // header = header | (1 << 7): OR運算
    printf("開啟加密後 (16進位): 0x%02X\n", header); // 預期 0x80
    // %:格式化字串, X:16進位格式
    // header (將第 7 位元清為 0)
    header &= ~(1 << 7); // header = header & ~(1 << 7): AND運算
    printf("關閉加密後 (16進位): 0x%02X\n", header); // 預期 0x00

    return 0;
} 