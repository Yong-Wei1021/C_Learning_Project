/*
 * fork_test.c - 測試 fork() 函數的行為，父子進程與記憶體獨立性
 */

#include <stdio.h>
#include <unistd.h>   // Linux 系統呼叫的核心標頭檔
#include <sys/types.h>
#include <sys/wait.h>

// 定義一個全域變數，用來測試 Copy-on-Write (COW)
int global_val = 100;

int main() {
    pid_t pid; // pid_t為process identifier的類型，pid為程式判斷是父進程還是子進程的依據
    printf("--- [開始測試 fork] 當前全域變數值: %d ---\n", global_val);

    // 呼叫 fork()，此處會「分裂」成兩個進程(父進程和子進程)
    pid = fork(); //fork() 會回傳一個整數值 (0 給子進程，父進程得到子進程的 PID，失敗則回傳 -1)

    if (pid < 0) {
        // fork 失敗
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // --- 這裡是子進程 (Child Process) ---
        printf("\n[子進程] 我是兒子！我的 PID 是: %d, 我父親的 PID (PPID) 是: %d\n", getpid(), getppid());  //getppid(): get parent process ID
        
        // 修改全域變數，看看是否會影響父進程的值
        printf("[子進程] 將全域變數修改為 200...\n");
        global_val = 200;
        printf("[子進程] 修改後的全域變數值: %d\n", global_val);
    } 
    else {
        // --- 這裡是父進程 (Parent Process) ---
        printf("\n[父進程] 我是父親！我的 PID 是: %d, 我兒子的 PID 是: %d\n", getpid(), pid);
        
        // 讓父進程暫停1秒，確保子進程有機會修改全域變數
        sleep(1); 
        
        printf("[父進程] 睡醒了。目前全域變數值: %d\n", global_val);
        
        if (global_val == 100) {
            printf("[父進程] 觀察結果：變數沒被兒子影響，證明記憶體空間是獨立的！\n");
        }
    }

    return 0;
}