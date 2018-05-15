/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithm and Data Structure
queue
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"
#include "queue.h"

typedef struct queue
{
    SLL *list;
    void (*display)(void *, FILE *);
    void (*free) (void *);
}QUEUE;
//////////////////////////////////
	
QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *))
{
   QUEUE *q;
   q = malloc(sizeof(QUEUE));
   assert(q != 0);
   q->display = d;
   q->free = f;
   q->list = newSLL(d,f);
   return q;
}

void enqueue(QUEUE *q ,void *value) {
    if (q ->list == NULL)
        insertSLL(q ->list,0,value);
    else
        insertSLL(q ->list,sizeSLL(q->list),value);
}

void *dequeue(QUEUE *q) {
	assert(sizeSLL(q->list) >0);
    return removeSLL(q->list,0);
}

void *peekQUEUE(QUEUE *q) {
	assert(sizeSLL(q->list) >0);
    return getSLL(q->list,0);
}

int sizeQUEUE(QUEUE *q) {
    return sizeSLL(q->list);
}

void displayQUEUE(QUEUE *q,FILE *fp) 
{
	fprintf(fp,"<");
	for(int i=0;i<sizeQUEUE(q);i++){
		q->display(getSLL(q->list,i),fp);
		if(i != sizeQUEUE(q)-1)
			fprintf(fp,",");
	}
	fprintf(fp,">");
}

void displayQUEUEdebug(QUEUE *q,FILE *fp)
{
	displaySLLdebug(q->list,fp);
}

void freeQUEUE(QUEUE *q)
{
	freeSLL(q->list);
	free(q);
}
