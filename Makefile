CC = gcc
CFLAGS = -c -o

SRC_DIR = ./
OBJ_DIR = ./build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(shell mkdir -p ${OBJ_DIR} ${DDD_DIR})

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $@ $<

.PHONY: test
test:
	$(MAKE) test -C ./linked_list

.PHONY: clean
clean:
	@echo "clean..."
	@rm -rf ./build
	@rm -rf ./linked_list/build