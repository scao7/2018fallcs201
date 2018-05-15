OBJS = string.o integer.o sll.o dll.o queue.o stack.o real.o bst.o heap.o bst-0-0.o heap-0-0.o sll-0-0.o dll-0-0.o heapsort.o scanner.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : test-bst test-heap test-dll test-sll heapsort

test-bst : bst-0-0.o integer.o sll.o real.o string.o bst.o queue.o
	gcc $(LOPTS) bst-0-0.o integer.o real.o sll.o bst.o queue.o -o test-bst
	
test-sll : sll-0-0.o integer.o real.o string.o sll.o 
	gcc $(LOPTS) sll-0-0.o	integer.o sll.o real.o string.o -o test-sll

test-dll: dll-0-0.o integer.o real.o string.o sll.o dll.o 
	gcc $(LOPTS) dll-0-0.o integer.o sll.o real.o string.o dll.o -o test-dll 
	
test-heap : heap-0-0.o integer.o string.o sll.o dll.o real.o bst.o heap.o queue.o stack.o
	gcc $(LOPTS) heap-0-0.o	heap.o bst.o dll.o stack.o queue.o integer.o sll.o real.o -o test-heap

heapsort: heapsort.o integer.o string.o real.o sll.o dll.o bst.o queue.o stack.o heap.o scanner.o 
	gcc $(LOPTS) heapsort.o heap.o integer.o string.o real.o sll.o dll.o bst.o queue.o stack.o scanner.o -o  heapsort
	
heapsort.o : heapsort.c dll.h integer.h real.h sll.h bst.h queue.h stack.h scanner.h
	gcc $(OOPTS) heapsort.c

bst-0-0.o : bst-0-0.c dll.h integer.h real.h sll.h bst.h string.h 
	gcc $(OOPTS) bst-0-0.c

sll-0-0.o : sll-0-0.c sll.h integer.h queue.h string.h
	gcc $(OOPTS) sll-0-0.c
 
dll-0-0.o: dll-0-0.c sll.h integer.h integer.h queue.h string.h
	gcc $(OOPTS) dll-0-0.c

heap-0-0.o : heap-0-0.c sll.h integer.h real.h queue.h stack.h heap.h bst.h dll.h scanner.h
	gcc $(OOPTS) heap-0-0.c

scanner.o: scanner.c scanner.h
	gcc $(OOPTS) scanner.c

heap.o : heap.c heap.h bst.h sll.h dll.h queue.h stack.h 
	gcc $(OOPTS) heap.c 
	
bst.o : bst.c bst.h
	gcc $(OOPTS) bst.c
	
real.o : real.c real.h
	gcc $(OOPTS) real.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

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
	echo testing sll list
	valgrind ./test-sll
	echo
	echo testing dll list
	valgrind ./test-dll
	echo 
	echo testing bst list
	valgrind ./test-bst
	echo 
	echo testing heap list
	valgrind ./test-heap
	echo
	
test: 	
	echo testing sll list
	./test-sll
	echo
	echo testing dll list
	./test-dll
	echo 
	echo testing bst list
	./test-bst
	echo 
	echo testing heap list
	./test-heap
	echo
clean    :
	rm -f $(OBJS) test-bst test-dll test-queue test-sll test-stack test-bst test-heap heapsort
