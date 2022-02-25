CC = gcc
CFLAGS = -o


all: test test_doubly

test: test.c linked_list.c linked_list.h
	$(CC) $(CFLAGS) test test.c linked_list.c

test_doubly: test.c doubly_linked_list.c linked_list.h
	$(CC) $(CFLAGS) test_doubly test.c doubly_linked_list.c

.PHONY: clean
clean:
	rm -rf test