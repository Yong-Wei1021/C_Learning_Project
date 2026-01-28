#include <stdio.h>
#include <stdlib.h> // 為了 malloc 和 free
#include <stdint.h> // 為了 uint32_t 等標準型態

// 2. 結構體定義在 main 外面，通常會存成.h檔再去include它
struct Sensor {
    uint8_t id;     // 8位元 (1 byte)
    uint32_t value; // 32位元 (4 bytes)
};

int main() {
    // 3. 一般變數在 Stack
    int normal_var = 10; 

    // 在 Stack 宣告一個指標變數 p (它只是個存地址的盒子)
    // 用 malloc 在 Heap 租一塊 8 bytes 的空間 (1 + padding 3 + 4)

    // 4. p 本身在 Stack，它指向的地方在 Heap
    struct Sensor *p = (struct Sensor *)malloc(sizeof(struct Sensor)); // malloc寫法

    if (p == NULL) {
        printf("記憶體租借失敗！\n");
        return 1; // 結束程式
    }

    // 4. p->value:結構體的指標用法，代表透過地址去改內容
    p->id = 0xFF;        // 將id 填入 8 位元的最大值
    p->value = 123456;   // 將value 填入 32 位元的數值

    printf("ID 位址: %p\n", (void*)&p->id);
    printf("Value 位址: %p\n", (void*)&p->value);
    
    // 你會發現位址差了 4，代表 1(id) + 3(偷偷塞的 Padding)

    free(p); // 歸還 Heap 空間
    return 0;
}