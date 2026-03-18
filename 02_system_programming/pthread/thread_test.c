#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // 包含 pthread 函式庫的標頭檔
#include <unistd.h>

// 定義一個結構體，用來傳遞多個參數
typedef struct {
    int client_id; // 第一個欄位
    char message[50]; // 第二個欄位
} ThreadData;

// 函式(function):靜態程式碼(任務)；執行緒(Thread):動態執行的實體(任務的執行者)

// 執行緒要執行的函式
// 注意：傳回值與參數都必須是 void* (萬能指標)，以符合 pthread_create 的要求
void* print_message(void* arg) {
    // 將 void* 強制轉型回 ThreadData* 
    ThreadData* data = (ThreadData*)arg;

    printf("[執行緒 %d] 收到訊息: %s\n", data->client_id, data->message);
    
    // 模擬處理時間
    sleep(2); 
    
    printf("[執行緒 %d] 處理完成，準備退出。\n", data->client_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2; // 定義兩個 pthread_t 變數，存放執行緒的 ID
    ThreadData d1 = {1, "這是第一個thread的訊息"}; // 1填入client_id，"這是第一個thread的訊息"填入message
    ThreadData d2 = {2, "這是第二個thread的訊息"};

    printf("[主程式] 準備建立執行緒...\n");

    // 建立執行緒:pthread_create 的參數說明 
    // 參數：&ID, 屬性(通常NULL), 函式名, 傳入參數的指標
    if (pthread_create(&thread1, NULL, print_message, (void*)&d1) != 0) {
        perror("建立執行緒 1 失敗"); // 如果 pthread_create 回傳非 0，表示建立執行緒失敗，使用 perror 輸出錯誤訊息
    }
    
    if (pthread_create(&thread2, NULL, print_message, (void*)&d2) != 0) {
        perror("建立執行緒 2 失敗");
    }

    // 等待執行緒結束 (類似 wait)
    pthread_join(thread1, NULL); //不加join會導致主程式提前結束，執行緒隨著主程式結束而被強制終止
    pthread_join(thread2, NULL);

    printf("[主程式] 所有執行緒已結束，程式退出。\n");
    return 0;
}