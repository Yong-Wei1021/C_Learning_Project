# Linux OS 實作筆記：進程管理

這是一個關於作業系統（OS）核心概念的實作紀錄，主要使用 C 語言於 Ubuntu 環境開發。

## 第一階段：進程與執行緒 (Progress & Threads)

### Day 1-2：進程建立與 fork()
* **核心指令**：`fork()`, `getpid()`, `getppid()`
* **實驗心得**：
    1.  **Copy-on-Write (COW)**：`fork` 產生的子進程會擁有獨立的記憶體空間。修改子進程的全域變數不會影響父進程，這展現了進程間的「隔離性」。
    2.  **身分識別**：`fork()` 呼叫一次回傳兩次。父進程拿到子進程 PID，子進程拿到 0。
    3.  **孤兒進程 (Orphan Process)**：當父進程先於子進程結束，子進程會被系統的 `init` 進程（PID 為 1 或由系統決定）自動收養。

### 如何執行
1. 編譯：`gcc stage1_process/day1_fork.c -o fork_test`
2. 執行：`./fork_test`