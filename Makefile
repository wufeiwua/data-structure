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
	@rm -rf compile_commands.json

.PHONY: compile_db
compile_db:
	bear -- make all clean
	cd list && bear --append --output ../compile_commands.json -- make all clean && cd -
	cd linked_list && bear --append --output ../compile_commands.json -- make all clean && cd -
	cd queue && bear --append --output ../compile_commands.json -- make all clean && cd -
	cd stack && bear --append --output ../compile_commands.json -- make all clean && cd -
	cd tree && bear --append --output ../compile_commands.json -- make all clean && cd -