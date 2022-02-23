all: test test_doubly

test: test.c linked_list.c linked_list.h
	gcc -o test test.c linked_list.c

test_doubly: test.c doubly_linked_list.c linked_list.h
	gcc -o test_doubly test.c doubly_linked_list.c

.PHONY: clean
clean:
	rm -rf test