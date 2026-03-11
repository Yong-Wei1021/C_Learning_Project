# Makefile for Socket Project
# 定義工具與變數
CC = gcc # 指定使用的編譯器 (compiler)
CFLAGS = -Wall -g # 編譯選項：顯示所有警告訊息。-Wall:waring all, -g:debug 

#目標 (Target): 依賴檔案 (Dependencies)
#[Tab鍵] 指令 (Command)  

# 規則：寫下想產生的所有執行檔
all: server client

# 製作 server
server: server.o
	$(CC) $(CFLAGS) -o server server.o 

# $(CC) $(CFLAGS) -o $@ $< 和上一行等價
# $@：目標檔案(server)，$<：第一個依賴檔案(server.o)

# 規則：製作 client
client: client.o
	$(CC) $(CFLAGS) -o client client.o

# 萬用規則：把所有的 .c 變成 .o(物件檔)，並依賴 common.h
# .c/.h:原料，.o:零件，執行檔:成品
%.o: %.c common.h
	$(CC) $(CFLAGS) -c $< -o $@

# 清除編譯產生的檔案
clean:
	rm -f *.o server client 