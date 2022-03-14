CC = gcc -g
CFLAGS = -c
INC=-I../include/

SRC_DIR = .
TEST_DIR = ./test
BUILD_DIR = ./build

$(shell mkdir -p $(BUILD_DIR) $(BUILD_DIR)/bin)

.PHONY: all binary_search_tree avl_tree

all: binary_search_tree avl_tree spaly_tree

binary_search_tree: binary_search_tree.c test/binary_search_tree_test.c
	$(CC) $(INC)  binary_search_tree.c test/binary_search_tree_test.c -o $(BUILD_DIR)/bin/binary_search_tree_test

avl_tree: avl_tree.c test/avl_tree_test.c
	$(CC) $(INC) avl_tree.c test/avl_tree_test.c -o $(BUILD_DIR)/bin/avl_tree_test

spaly_tree: spaly_tree.c test/spaly_tree_test.c
	$(CC) $(INC) spaly_tree.c test/spaly_tree_test.c -o $(BUILD_DIR)/bin/spaly_tree_test

.PHONY: clean
clean:
	@echo "clean..."
	rm -rf ./build