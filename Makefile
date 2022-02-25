CC = gcc
CFLAGS = -o

SRC_DIR = ./
OBJ_DIR = ./build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: main linked_list

.PHONY: main linked_list

main: main.c
	$(CC) $(CFLAGS) main main.c 

linked_list:
	$(MAKE) -C ./linked_list