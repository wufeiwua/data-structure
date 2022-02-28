CC = gcc
CFLAGS = -c
INC=-I../include/

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
.PHONY: test run
all: $(OBJ) test

$(OBJ): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< $(INC) -o $@

test: $(OBJ_TEST) 

$(OBJ_TEST): $(BUILD_DIR)/bin/%_test: $(BUILD_DIR)/%.o $(TEST_FILE)
	$(CC) $(TEST_FILE) $< $(INC) -o $@

define run_test
$(foreach item,$(OBJ_TEST),$(item)
)
endef

run:
	$(call run_test)

.PHONY: clean
clean:
	@echo "clean..."
	rm -rf ./build