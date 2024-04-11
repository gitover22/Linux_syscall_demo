# 编译器
CC = gcc
# 编译选项
CFLAGS = -Wall -std=c11 -g
# 找到当前目录下所有的.c文件
SOURCES := $(wildcard *.c)
# 从.c文件名生成可执行文件名列表
EXECUTABLES := $(SOURCES:%.c=%)


# 默认目标：编译所有的.c文件生成可执行文件
all: $(EXECUTABLES)

# 从每个.c文件编译生成对应的可执行文件
$(EXECUTABLES): %: %.c  # 通配符规则
	$(CC) $< -o $@ $(CFLAGS) 


# 清理指定的可执行文件
# 用法：make clean exec=文件名
clean:
	rm -f $(exec)
	rm -f $(EXECUTABLES)
.PHONY: all clean

