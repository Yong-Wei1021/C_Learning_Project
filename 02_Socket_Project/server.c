#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *response = "Hello from Server! 我收到你的訊息了。";

    // 檢查 socket 是否建立成功
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket 建立失敗");
        exit(EXIT_FAILURE);
    }

    // 解決Port被佔用的問題:Address already in use
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd); // 出錯時關閉已開啟的 socket (資源釋放)
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // 加入 bind 的錯誤檢查
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind 失敗");
        close(server_fd);
        exit(EXIT_FAILURE);
    }    

    // 加入 listen 的錯誤檢查
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
        memset(buffer, 0, 1024);
        read(new_socket, buffer, 1024);
        printf("Client 說: %s\n", buffer);
        
        send(new_socket, response, strlen(response), 0);

        // 重點：處理完這位客人的要求，就把「這通電話」掛掉
        close(new_socket);
        printf("通話結束，回到櫃檯等下一位。\n");
    }
    // --- 無限循環結束 ---

    // 這行理論上永遠跑不到，除非 while 失效
    close(server_fd);
    return 0;
}