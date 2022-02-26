CC = gcc
CFLAGS = -c -o

SRC_DIR = ./
OBJ_DIR = ./build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all:
	mkdir -p ${OBJ_DIR}
	$(MAKE) ${OBJ}

.PHONY: $(OBJ)
${OBJ}: ${SRC}
	$(CC) $(CFLAGS) $@ $<