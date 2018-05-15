OBJS = string.o binomial.o prim.o avl.o integer.o sll.o dll.o queue.o vertex.o edge.o stack.o real.o bst.o bst-0-0.o  avl-0-0.o sll-0-0.o dll-0-0.o  scanner.o 
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : test-avl test-bst test-dll test-sll prim 

test-bst : bst-0-0.o integer.o sll.o real.o string.o bst.o queue.o
	gcc $(LOPTS) bst-0-0.o integer.o real.o sll.o bst.o queue.o -o test-bst
	
test-sll : sll-0-0.o integer.o real.o string.o sll.o 
	gcc $(LOPTS) sll-0-0.o	integer.o sll.o real.o string.o -o test-sll

test-dll: dll-0-0.o integer.o real.o string.o sll.o dll.o 
	gcc $(LOPTS) dll-0-0.o integer.o sll.o real.o string.o dll.o -o test-dll 
	
test-heap : heap-0-0.o integer.o string.o sll.o dll.o real.o bst.o heap.o queue.o stack.o
	gcc $(LOPTS) heap-0-0.o	heap.o bst.o dll.o stack.o queue.o integer.o sll.o real.o -o test-heap
	
test-avl: avl-0-0.o integer.o sll.o real.o string.o bst.o queue.o avl.o
	gcc $(LOPTS) avl-0-0.o integer.o real.o sll.o bst.o  queue.o avl.o -o  test-avl

prim :	prim.o integer.o scanner.o bst.o avl.o vertex.o edge.o binomial.o dll.o stack.o queue.o sll.o 
	gcc $(LOPTS) prim.o integer.o sll.o scanner.o bst.o avl.o vertex.o edge.o binomial.o dll.o stack.o queue.o -lm -o prim 

bst-0-0.o : bst-0-0.c dll.h integer.h real.h sll.h bst.h string.h 
	gcc $(OOPTS) bst-0-0.c

sll-0-0.o : sll-0-0.c sll.h integer.h queue.h string.h
	gcc $(OOPTS) sll-0-0.c
 
dll-0-0.o: dll-0-0.c sll.h integer.h integer.h queue.h string.h
	gcc $(OOPTS) dll-0-0.c

avl-0-0.o : avl-0-0.c dll.h integer.h real.h sll.h bst.h avl.h string.h 
	gcc $(OOPTS) avl-0-0.c

scanner.o: scanner.c scanner.h
	gcc $(OOPTS) scanner.c

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

avl.o : avl.c avl.h bst.h
	gcc $(OOPTS) avl.c
	   
integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

vertex.o : vertex.c vertex.h
	gcc $(OOPTS) vertex.c

edge.o : edge.c edge.h
	gcc $(OOPTS) edge.c
binomial.o : binomial.c binomial.h
	gcc $(OOPTS) binomial.c 

prim.o : prim.c
	gcc $(OOPTS) prim.c

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
	echo testing avl list
	valgrind ./test-avl
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
	echo testing avl list
	./test-avl
	echo

clean    :
	rm -f $(OBJS) test-avl test-bst test-dll prim test-queue test-sll test-stack test-bst 
