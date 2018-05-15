OBJS = integer.o sll.o dll.o queue.o test-stack.o stack.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : test-sll test-dll test-queue test-stack

test-sll : test-sll.o integer.o sll.o
	gcc $(LOPTS) test-sll.o integer.o sll.o  -o test-sll

test-dll : test-dll.o integer.o dll.o
	gcc $(LOPTS) test-dll.o integer.o dll.o  -o test-dll

test-queue : test-queue.o integer.o sll.o queue.o
	gcc $(LOPTS) test-queue.o integer.o sll.o queue.o -o test-queue

test-stack : test-stack.o integer.o dll.o stack.o 
	gcc $(LOPTS) test-stack.o integer.o dll.o stack.o -o test-stack
		   
test-sll.o : test-sll.c sll.h integer.h
	gcc $(OOPTS) test-sll.c

test-dll.o : test-dll.c dll.h integer.h
	gcc $(OOPTS) test-dll.c

test-queue.o : test-queue.c sll.h integer.h queue.h
	gcc $(OOPTS) test-queue.c

test-stack.o : test-stack.c integer.h integer.h stack.h
	gcc $(OOPTS) test-stack.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

stack.o : stack.c stack.h dll.h
	gcc $(OOPTS) stack.c
	   
integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

valgrind  :all
	echo testing single-linked list
	valgrind ./test-sll
	echo 
	echo testing doubly-linked list
	valgrind ./test-dll
	echo 
	echo testing stack list
	valgrind ./test-stack
	echo
	echo testing queue
	valgrind ./test-queue
test: 	
	echo testing single-linked list
	./test-sll
	echo
	echo testing single-linked list
	./test-dll
	echo
	echo testing stack 
	./test-stack
	echo
	echo testing queue 
	./test-queue
	echo
clean    :
	rm -f $(OBJS) test-sll test-dll test-queue test-stack test-*.o
