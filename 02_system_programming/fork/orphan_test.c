/*
 * orphan_test.c - 測試孤兒進程的行為
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // --- 子進程 ---
        printf("[子進程] 剛開始，父進程的ID是: %d\n", getppid());
        
        printf("[子進程] 我要睡 10 秒，等父進程結束...\n");
        
        sleep(10);
        
        printf("[子進程] 睡醒後，我發現我變成孤兒了。現在收養我的人是: %d\n", getppid());
        printf("[子進程] (提示: 如果是 1 或其他固定值，代表已被系統守護進程收養)\n");
    } 
    else {
        // --- 父進程 ---
        printf("[父進程] 我還有事，先領便當了！(我的 PID: %d)\n", getpid());
        exit(0); // 立即結束父進程，讓子進程成為孤兒進程
    }

    return 0;
}