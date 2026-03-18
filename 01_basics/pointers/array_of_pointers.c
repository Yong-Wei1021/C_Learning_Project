#include <stdio.h>
#include <stdlib.h>

// 指標陣列：當有長短不一或分散在Heap的東西要管理

struct Sensor {
    int id;
    int value;
};

int main() {
    // 宣告一個「存放指標的陣列」，大小為 3
    // 這就像是你有 3 個遙控器位置，但還沒對準任何機器
    struct Sensor *sensors[3]; 

    // 用迴圈幫每個遙控器「租」一台機器 (Heap)
    for (int i = 0; i < 3; i++) {
        sensors[i] = (struct Sensor *)malloc(sizeof(struct Sensor)); //每個遙控器的空間大小:0x555...
        
        // 初始化內容
        sensors[i]->id = i + 1;    // 設定 ID 為 1, 2, 3
        sensors[i]->value = 100 * (i + 1); // 設 value為100, 200, 300
    }

    // 列印結果
    for (int i = 0; i < 3; i++) {
        printf("感測器清單索引 [%d] -> ID: %d, 數值: %d\n", 
                i, sensors[i]->id, sensors[i]->value);
    }

    // 記得！租幾台就要還幾台
    for (int i = 0; i < 3; i++) {
        free(sensors[i]);
    }

    return 0;
}