#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address; // struct 用來填寫伺服器地址，包含IP和Port
    int addrlen = sizeof(address);
    char buffer[1024] = {0}; //在記憶體挖出1024個格子
    //char *response = "Hello from Server! 我收到你的訊息了。";

    // 檢查 socket 是否建立成功
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket 建立失敗");
        exit(EXIT_FAILURE);
    }

    // 解決Port被佔用的問題: Address already in use
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) { 
        perror("setsockopt failed");
        close(server_fd); // 出錯時關閉已開啟的 socket (資源釋放)
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // 監聽所有可用的網路介面
    address.sin_port = htons(8080); // Port 8080

    // 加入 bind 的錯誤檢查，bind綁定Port和IP
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind 失敗");
        close(server_fd);
        exit(EXIT_FAILURE);
    }    

    // 加入 listen 的錯誤檢查，讓 server 開始監聽。 BACKLOG 設為 3，表示最多允許 3 個等待連線的客戶端
    if (listen(server_fd, 3) < 0) {
        perror("listen 失敗");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server 啟動！現在是「循環待機」模式，按 Ctrl+C 才能關閉...\n");

    // --- 無限循環開始 ---
    // 讓 Server 能夠處理多個訊息 (Loop)
    while(1) {
        printf("\n正在等待新的連線...\n");
        
        // 程式會卡在 accept，直到有人打電話進來
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        if (new_socket < 0) {
            perror("Accept 失敗");
            continue; // 失敗就跳過這次，繼續等下一通電話
        }

        printf("連線成功！處理資料中...\n");
        
        // 清空 buffer，避免殘留舊資料
        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, 1024); //將0和1變成文字填進格子內
        printf("Client 說: %s\n", buffer);

        buffer[strcspn(buffer, "\r\n")] = 0; // strcmp：字串比較，檢查兩字串否一樣，0代表一樣
        char response[sizeof(buffer)]; // 回傳我們要說的話

        // 根據 Client 發來的指令，決定回應內容。

        // 指令為 TIME，回傳系統時間。 使用 strcmp 判斷指令，確認字串是否相同
        if (strcmp(buffer, "TIME") == 0) {
        // 取得系統時間
        time_t now = time(NULL); // 取得目前時間
        struct tm *t = localtime(&now); // 轉換為當地時間結構
        // 使用 sprintf 組裝字串
        sprintf(response, "現在時間是: %02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
        } 
        // 指令為 HELLO，回傳問候語
        else if (strcmp(buffer, "HELLO") == 0) {
        sprintf(response, "你好！我是你的 Socket 小幫手。");
        } 
        // 其他指令，回傳字串長度
        else {
        // 計算長度並組裝字串
        int len = strlen(buffer);
        sprintf(response, "我不知道 '%s' 是什麼，但我知道它有 %d 個字。", buffer, len);
        }

        // 發送回應給 Client，把我們要說的話變成0和1傳出去
        send(new_socket, response, strlen(response), 0); 

        // 處理完這位客人的要求，就把「這通電話」掛掉
        close(new_socket);
        printf("通話結束，回到櫃檯等下一位。\n");
    }
    // --- 無限循環結束 ---

    // 關閉 server 的 socket
    close(server_fd);
    return 0;
}