#include <stdio.h>
#include <stdlib.h>

// 指標的指標 pointers of pointers + malloc：需要在執行中動態決定矩陣的大小
int main() {
    int row = 2, col = 3;

    // --- 【淺到深的核心】 ---
    // 1. matrix 是一個指標的指標，它指向 Heap 裡的一個「地址陣列」
    int **matrix = (int **)malloc(row * sizeof(int *));

    // 2. 幫每一列租空間
    for (int i = 0; i < row; i++) {
        matrix[i] = (int *)malloc(col * sizeof(int));
    }

    // 3. 填資料 (跟一般 2D 陣列用法一樣)
    matrix[0][0] = 10;
    matrix[1][2] = 20;

    printf("值: %d, %d\n", matrix[0][0], matrix[1][2]);

    // 4. 釋放 (由內而外)
    for (int i = 0; i < row; i++) free(matrix[i]);
    free(matrix);

    return 0;
}