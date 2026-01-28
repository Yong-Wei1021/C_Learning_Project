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

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 解決 Port 被佔用的問題 (這是你學過的重點！)
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server 啟動！現在是「長青店」模式，按 Ctrl+C 才能關閉...\n");

    // --- 無限循環開始 ---
    while(1) {
        printf("\n正在等待新的連線...\n");
        
        // 程式會卡在 accept，直到有人撥電話進來
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        if (new_socket < 0) {
            perror("Accept 失敗");
            continue; // 失敗就跳過這次，繼續等下一個
        }

        printf("連線成功！處理資料中...\n");
        
        // 清空 buffer，避免殘留舊資料
        memset(buffer, 0, 1024);
        read(new_socket, buffer, 1024);
        printf("Client 說: %s\n", buffer);
        
        send(new_socket, response, strlen(response), 0);

        // 重點：處理完這個客人的要求，就把「這通電話」掛掉
        close(new_socket);
        printf("通話結束，回到櫃檯等下一位。\n");
    }
    // --- 無限循環結束 ---

    // 這行理論上永遠跑不到，除非 while 破裂
    close(server_fd);
    return 0;
}