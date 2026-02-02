#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // 提供 read, write, close 
#include <arpa/inet.h>   // 提供網路地址轉換函式

int main() {
    int sock_fd = 0;
    struct sockaddr_in serv_addr; //struct 用來填寫伺服器地址，包含IP和Port
    //char *message = "Hello, Server!";
    char buffer[1024] = {0}; //

    // 建立 Socket
    // AF_INET: 使用 IPv4 地址
    // SOCK_STREAM: 使用 TCP 協議
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket 建立失敗 \n");
        return -1;
    }

    // 設定伺服器地址資訊
    serv_addr.sin_family = AF_INET;   // 設定為 IPv4
    serv_addr.sin_port = htons(8080); // 設定 Port 為 8080 (htons 處理 Byte Order)

    // 將 IP 地址從字串 (127.0.0.1) 轉換為網路二進位格式
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n 無效的地址 / 不支援的地址 \n");
        return -1;
    }

    //  連線 (Connect) 到伺服器：用到指標轉型，把 struct sockaddr_in 轉成 struct sockaddr (通用)。 sockaddr_in：IPv4 的結構
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n 連線失敗，請確認 Server 是否已啟動 \n");
        return -1;
    }

    // 發送資料 (Send)
    char *message = "HELLO\n"; // 自動說密語
    send(sock_fd, message, strlen(message), 0);
    printf("已自動發送密語: %s\n", message);

    // 接收伺服器的回覆 (Read)
    read(sock_fd, buffer, 1024);
    printf("Server 回傳訊息: %s\n", buffer);

    // 關閉 Socket
    close(sock_fd);
    return 0;
}