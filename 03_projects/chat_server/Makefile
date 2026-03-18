# Makefile for Socket Project
# 定義工具與變數
CC = gcc # 指定使用的編譯器 (compiler)
IDIR = ../include # 頭文件所在的目錄
CFLAGS = -Wall -g -I$(IDIR) # 編譯選項：顯示所有警告訊息。-Wall:waring all, -g:debug 

# --- 修改處：把執行檔名加上 .out ---
PROGS = server.out client.out

#目標 (Target): 依賴檔案 (Dependencies)
#[Tab鍵] 指令 (Command)  

# 規則：寫下想產生的所有執行檔
all: $(PROGS)

# 製作 server.out
server.out: server.o
	$(CC) $(CFLAGS) -o server.out server.o 
#	$(CC) $(CFLAGS) -o $@ $^

# $(CC) $(CFLAGS) -o $@ $< 和上一行等價
# $@：目標檔案(server.out)，$<：第一個依賴檔案(server.o)

# 規則：製作 client.out
client.out: client.o
	$(CC) $(CFLAGS) -o client.out client.o

# 萬用規則：把所有的 .c 變成 .o(物件檔)，並依賴 common.h
# .c/.h:原料，.o:零件，執行檔:成品
%.o: %.c $(IDIR)/common.h
	$(CC) $(CFLAGS) -c $< -o $@

# 清除編譯產生的檔案
clean:
	rm -f *.o *.out $(PROGS)