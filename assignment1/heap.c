/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithm and Data Structure
binary heap 
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "bst.h"
#include "stack.h"
#include "bst.h"
#include "heap.h"
typedef struct heap{
	BST* tree;
	QUEUE* q;
	STACK* s;
	int size;
	void(*display)(void*,FILE*);
	int (*compare)(void*,void*);
	void(*free)(void*);
}HEAP;

HEAP *newHEAP( void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *)){
	HEAP* h=malloc(sizeof(HEAP));
	h-> tree = newBST(d,c,NULL,f);
	h-> size = 0;
	h-> display = d;
	h-> compare = c;
	h-> free = f;
	h-> q = newQUEUE(d,0);
	h-> s = newSTACK(d,0);
	return h;
} 

void insertHEAP(HEAP *h,void *value){ 
	BSTNODE* newNode = newBSTNODE(value);
	assert(newNode);
	BSTNODE* temp = NULL; //this is for parent 
	//QUEUE* newqueue = newQUEUE(h->display, h->free);
	if(getBSTroot(h->tree)==NULL){
		setBSTroot(h->tree, newNode);
		setBSTNODEparent(newNode, NULL);
		h->size ++;
		push(h->s,newNode);
		enqueue(h->q, newNode);
		setBSTsize(h->tree, sizeBST(h->tree)+1);
	}
	else{
		temp = peekQUEUE(h->q);
		if(getBSTNODEleft(temp) == 0){
			setBSTNODEparent(newNode,temp);
			setBSTNODEleft(temp, newNode);
			push(h->s, newNode);
			enqueue(h->q,newNode);
			setBSTsize(h->tree, sizeBST(h->tree)+1);
			h->size++;

		}
		else{
			setBSTNODEparent(newNode,temp);
			setBSTNODEright(temp,newNode);
			dequeue(h->q);
			push(h->s,newNode);
			enqueue(h->q,newNode);
			setBSTsize(h->tree, sizeBST(h->tree)+1);
			h->size ++;
		}

	}

	return;
}
//swapper ---help function
static void heapsw(BSTNODE* a, BSTNODE* b){
	void* temp = getBSTNODEvalue(a);
	setBSTNODEvalue(a,getBSTNODEvalue(b));
	setBSTNODEvalue(b,temp);
}

static void pushDown(HEAP* h, BSTNODE* node){
	BSTNODE* next = node;
	if(getBSTNODEleft(node) && h->compare(getBSTNODEvalue(getBSTNODEleft(node)),getBSTNODEvalue(next))<0)
		next = getBSTNODEleft(node);
	//else return;
	if(getBSTNODEright(node) && h->compare(getBSTNODEvalue(getBSTNODEright(node)),getBSTNODEvalue(next))<0)
		next = getBSTNODEright(node);
	//else return;
	if(getBSTNODEvalue(next) != getBSTNODEvalue(node))
	{
		heapsw(next, node);
		pushDown(h,next);
	
	}
}

void buildHEAP(HEAP *h){
	STACK* stack = newSTACK(h->display,0);
while(sizeSTACK(h->s)>0){
	BSTNODE* temp = pop(h->s);
	push(stack, temp);
	pushDown(h, temp);
	
}
while(sizeSTACK(stack) >0)
	push(h->s, pop(stack));
	freeSTACK(stack);
}
void *peekHEAP(HEAP *h){
	return getBSTNODEvalue(getBSTroot(h->tree));
}

///heapfunctionfor fix heap
void fixHeap(HEAP* h, BSTNODE* node)
        {
        if (getBSTNODEparent(node) && h->compare(getBSTNODEvalue(node),getBSTNODEvalue(getBSTNODEparent(node)))<0)
            {
            heapsw(node,getBSTNODEparent(node));
            fixHeap(h,getBSTNODEparent(node));
            }
}

void *extractHEAP(HEAP *h){
	void* temp= peekHEAP(h);
	BSTNODE* leaf = pop(h->s);
	if(h->size == 1){
		pruneLeafBST(h->tree, leaf);
		//setBSTroot(h->tree,NULL);
		freeBSTNODE(leaf,NULL);
		h->size --;
		setBSTsize(h->tree,sizeBST(h->tree)-1);
		//setBSTsize(h->tree,sizeBST(h->tree)-1);
		return temp;
	}
		
	heapsw(getBSTroot(h->tree),leaf);	

	pruneLeafBST(h->tree, leaf);
	pushDown(h, getBSTroot(h->tree));
	setBSTsize(h->tree,sizeBST(h->tree)-1);
	h->size --;
	freeBSTNODE(leaf,NULL);
	return temp;
}
int sizeHEAP(HEAP *h){
	return h->size;
}
void displayHEAP(HEAP *h,FILE *fp){
	displayBST(h->tree,fp);
	return;
}
void displayHEAPdebug(HEAP *h,FILE *fp){
	fprintf(fp,"heap size: %d\n", h->size);
	fprintf(fp,"bst size: %d\n",sizeBST(h->tree));
	displayBSTdebug(h->tree,fp);
	return;
}
void freeHEAP(HEAP *h){
	freeBST(h->tree);
	freeQUEUE(h->q);
	freeSTACK(h->s);
	free(h);
}
