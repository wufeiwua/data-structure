CC = gcc
CFLAGS = -c -o

SRC_DIR = .
TEST_DIR = ./test
OBJ_DIR = ./build/lib

SRC = $(wildcard $(SRC_DIR)/*.c)
TEST = ${wildcard ${TEST_DIR}/*.c}
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all:
	mkdir -p ${OBJ_DIR}
	$(MAKE) ${OBJ}

.PHONY: $(OBJ)
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $@ $<

.PHONY: test_all
test_all: $(OBJ)
	$(CC) -o $@ test/test.c $<


.PHONY: clean
clean:
	@echo "clean..."
	rm -rf ./build