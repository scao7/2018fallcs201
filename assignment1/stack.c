/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithm and Data Structure
stack
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"
#include "stack.h"

typedef struct stack
{
    DLL *list;
    void (*display)(void *, FILE *);
    void (*free) (void *);
}STACK;
/////////////////////////////////////////

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *))
{
   STACK *s;
   s = malloc(sizeof(STACK));
   assert(s != 0);
   s->display = d;
   s->free = f;
   s->list = newDLL(d,f);
   return s;
}
//////////////////////////////////////////

void push(STACK *s,void *value) {
	insertDLL(s->list,0,value);
}

void *pop(STACK *s) {
	assert(sizeDLL(s->list) >0);
    return removeDLL(s->list,0);
}

void *peekSTACK(STACK *s) {
	assert(sizeDLL(s->list) >0);
    return getDLL(s->list,0);
}

int sizeSTACK(STACK *s) {
    return sizeDLL(s->list);
}

void displaySTACK(STACK *s,FILE *fp) 
{
	fprintf(fp,"|");
	for(int i=0;i<sizeSTACK(s);i++){
		s->display(getDLL(s->list,i),fp);
		if(i != sizeSTACK(s)-1)
			fprintf(fp,",");
	}
	fprintf(fp,"|");
}

void displaySTACKdebug(STACK *s,FILE *fp)
{
	displayDLLdebug(s->list,fp);
}

void freeSTACK(STACK *s)
{
	freeDLL(s->list);
	free(s);
}
