CC = gcc
CFLAGS = 

SRC_DIR = ./
BUILD_DIR = ./build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/bin/%)

$(shell mkdir -p ${BUILD_DIR}/bin)

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: test
test:
	$(MAKE) test -C ./linked_list

.PHONY: clean
clean:
	@echo "clean..."
	@rm -rf ./build
	@rm -rf ./linked_list/build