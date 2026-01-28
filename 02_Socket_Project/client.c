#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // 提供 read, write, close 
#include <arpa/inet.h>   // 提供網路地址轉換函式

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr; // 這是我們提到的「結構體」，用來填寫伺服器地址
    char *message = "Hello, Server!";
    char buffer[1024] = {0};

    // 1. 建立 Socket
    // AF_INET: 使用 IPv4 地址
    // SOCK_STREAM: 使用 TCP 協議
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket 建立失敗 \n");
        return -1;
    }

    // 2. 設定伺服器地址資訊
    serv_addr.sin_family = AF_INET;   // 設定為 IPv4
    serv_addr.sin_port = htons(8080); // 設定 Port 為 8080 (htons 處理 Byte Order)

    // 將 IP 地址從字串 (127.0.0.1) 轉換為網路二進位格式
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n 無效的地址 / 不支援的地址 \n");
        return -1;
    }

    // 3. 連線 (Connect) 到伺服器
    // 這裡用了你學過的 C 語言指標轉型：(struct sockaddr *)&serv_addr
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n 連線失敗，請確認 Server 是否已啟動 \n");
        return -1;
    }

    // 4. 發送資料 (Send)
    send(sock, message, strlen(message), 0);
    printf("訊息已發送\n");

    // 5. 接收伺服器的回覆 (Read)
    read(sock, buffer, 1024);
    printf("Server 回傳訊息: %s\n", buffer);

    // 6. 關閉 Socket
    close(sock);

    return 0;
}