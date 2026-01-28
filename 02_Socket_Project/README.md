# Linux Socket Programming 練習 (TCP/IP)

這是我第一個 Linux Socket 練習專案，實現了基礎的 TCP: Server 與 Client 溝通。

### 核心技術點
- **TCP 三向交握**：理解連線建立過程(SYN、SYN-ACK、ACK)
- **Socket System Calls**：實作 `socket`, `bind`, `listen`, `accept`, `connect` 等函式。
- **Address Reuse**：使用 `SO_REUSEADDR` 解決 `TIME_WAIT` 導致的 Port 佔用問題。
- **持續性監聽**：透過 `while(1)` 讓 Server 持續服務，而非一次結束。

### 如何執行
1. 編譯：`gcc server.c -o server` 與 `gcc client.c -o client`
2. 先啟動伺服器：`./server`
3. 再啟動客戶端：`./client`