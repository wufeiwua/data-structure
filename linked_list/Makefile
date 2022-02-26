CC = gcc
CFLAGS = -c -o

SRC_DIR = .
TEST_DIR = ./test
BUILD_DIR = ./build

SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_TEST = ${wildcard ${TEST_DIR}/*.c}

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_TEST = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/bin/%_test)
TEST_FILE := ./test/test.c

# $(info $(SRC))
# $(info $(SRC_TEST))
# $(info $(OBJ))
# $(info $(OBJ_TEST))

$(shell mkdir -p $(BUILD_DIR) $(BUILD_DIR)/bin)

all: $(OBJ) test

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $@ $<

.PHONY: test run
test: $(OBJ_TEST)

$(OBJ_TEST): $(OBJ)
	$(CC) $(TEST_FILE) $< -o $@

run: $(OBJ_TEST)
	$<

.PHONY: clean
clean:
	@echo "clean..."
	rm -rf ./build