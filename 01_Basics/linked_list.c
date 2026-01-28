#include <stdio.h>
#include <stdlib.h>

// 定義節點：現在每個感測器都要知道「下一個在哪」
struct Sensor {
    int id;
    int value;
    struct Sensor *next; // 指向下一個感測器的指標 (Linked List 的靈魂)
};

int main() {
    struct Sensor *head = NULL;   // 鏈結串列的開頭 (火車頭)
    struct Sensor *current = NULL; // 用來移動、處理目前節點的輔助指標

    // --- 建立串列 (用迴圈產生 3 個節點) ---
    for (int i = 0; i < 3; i++) {
        // 1. 租一台機器 (配置記憶體)
        struct Sensor *newNode = (struct Sensor *)malloc(sizeof(struct Sensor));
        
        // 2. 初始化資料
        newNode->id = i + 1; // id=1,2,3
        newNode->value = 100 * (i + 1);
        newNode->next = NULL; // 新產生的節點暫時沒有下一個

        // 3. 連接邏輯
        if (head == NULL) {
            head = newNode;    // 如果火車還沒頭，它就是火車頭
        } else {
            current->next = newNode; // 讓「目前的最後一個」牽起「新節點」的手
        }
        current = newNode; // 移動「目前的最後一個」到最新的節點上
    }

    // --- 列印結果 (走訪 Traversal) ---
    printf("===== Linked List 走訪結果 =====\n");
    current = head; // 從火車頭開始走
    while (current != NULL) {
        printf("感測器 ID: %d, 數值: %d\n", current->id, current->value);
        current = current->next; // 往下一站前進
    }

    // --- 釋放記憶體 (非常重要！) ---
    // 釋放也要一站一站走，但要注意：一旦 free(current)，你就找不到 next 了
    // 所以我們需要一個臨時指標暫存下一站
    current = head;
    struct Sensor *temp;
    while (current != NULL) {
        temp = current->next; // 先記住下一站在哪
        printf("釋放感測器 ID: %d\n", current->id);
        free(current);        // 放心拆掉這一站
        current = temp;       // 移到下一站
    }

    return 0;
}