/*
written by Shengting Cao 
University of Alabama 
2018 FALL 
CS201 Algorithem and Data Structure
binomial heap 
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "binomial.h"
#include "dll.h"
#include "queue.h"

typedef struct BINNODE BNODE;

struct BINNODE {				
	BNODE *parent;				
	void *owner;					
	DLL *children;	
	void *value;				
	void (*display)(void *,FILE *);		
	void (*free)(void *);	
};

struct binomial {
	void (*display)(void *,FILE *);			
	int (*compare)(void *,void *);		
	void (*update)(void *,void *);			
	void (*free)(void *);			
	DLL *rootList;					
	BNODE *extreme;						
	int size;					
};

static BNODE *newBIN(void (*)(void *,FILE *),void (*)(void *),void *);
static BNODE *bubbleUp(BINOMIAL *,BNODE *);
static void consolidate(BINOMIAL *);
static void updateConsolidationArray(BINOMIAL *,BNODE **,void *);
static BNODE *combine(BINOMIAL *,BNODE *,BNODE *);
static void displayBIN(void *, FILE *fp);
static void freeBIN(void *);
//////////////////////////////////////////////
static BNODE *newBIN(void (*d)(void *,FILE *),void (*f)(void *),void *value) {
	BNODE *binNode = malloc(sizeof(BNODE));
	assert(binNode != NULL);
	binNode->value = value;
	binNode->parent = binNode;					
	binNode->owner = 0;				
	binNode->children = newDLL(displayBIN, freeBIN);
	binNode->display = d;
	binNode->free = f;
	return binNode;
}

static BNODE *bubbleUp(BINOMIAL *b, BNODE *n) {
	BNODE *p = 0;
	void *nValue = 0;
	void *pValue = 0;
	void *temp = 0;
	if (n != 0) {
		p = n -> parent;
	}
	if (n != 0) { 
	nValue = n -> value;
	}
	//printf("bubbleUp\n");
	// might affect the result
	if (n != 0) { p = n -> parent;}
	if (n != 0) { nValue = n -> value;}	// Set values
	if (p != 0) { pValue = p -> value;}
	// n is its own parent, so root of a subheap
        if (n == p) return n;					
        else if (b->compare(nValue,pValue) >= 0) return n;
        else{
			if (b->update != 0) b->update(nValue,p);
			if (b->update != 0) b->update(pValue,n);		
		
		//swap
	temp = nValue;						
    n -> value = pValue;
	p -> value = temp;
  
	return bubbleUp(b,p);
		}
}

static void consolidate(BINOMIAL *b) {
	if (b == 0) return;
	int i = 0;
	int binomialSize = sizeBINOMIAL(b);
	int arraySize = 0;
	arraySize = (int)(log(binomialSize)/log(2)) + 1;
	BNODE *pos = 0;
	BNODE *node = 0;
	void *dllNode = 0;
	// Creates consolidation array cons
	BNODE **cons = malloc(sizeof(BNODE *) * arraySize);		
	while (i < arraySize) { cons[i++] = 0; }			
	i = 0;
	firstDLL(b -> rootList);					// Get DLL head	
	
	while (sizeDLL(b -> rootList) > 0) {
		pos = removeDLL(b -> rootList, 0);			
		updateConsolidationArray(b, cons, pos);		
	}

	b -> extreme = 0;						// Set extreme to 0
	while (i < arraySize) {
		if (cons[i] != 0) {
			// Insert cons[i] into rootList
			dllNode = insertDLL(b -> rootList, sizeDLL(b -> rootList), cons[i]);
			node = cons[i];
			node -> owner = dllNode;
		
		
			if (b -> extreme == 0) { 
				b -> extreme = cons[i];
			}
			
			else if (b->compare(b ->extreme-> value, node -> value) > 0) {
				b -> extreme = cons[i];
			}
		}
		i++;
	}	
	free(cons);		
	return;
}

static void updateConsolidationArray(BINOMIAL *b, BNODE **cons, void *pos) {
	if (pos == 0) return;
	BNODE *bN = pos;
	int degree = sizeDLL(bN -> children);
	while (cons[degree] != 0) {
		bN = combine(b, bN, cons[degree]);			
								
		cons[degree++] = 0;				
	}
	cons[degree] = bN;						
	return;
}

static BNODE *combine(BINOMIAL *b, BNODE *x, BNODE *y) {
	DLL *xC = x -> children;
	DLL *yC = y -> children;
	void *xValue = 0;
	void *yValue = 0;
	if (x != 0) { 
		xValue = x -> value;
	}
	if (y != 0) {
		yValue = y -> value;
	}
	if (b->compare(xValue, yValue) < 0) {
		// Insert y into the children of x
		y -> owner = insertDLL(xC, sizeDLL(xC), y);
		// Set the parent of y to x
		y -> parent = x;

		return x;
	}
	// Insert x into the children of y
	x -> owner = insertDLL(yC, sizeDLL(yC), x);
	// Set the parent of x to y
	x -> parent = y;
	return y;
}

static void displayBIN(void *v, FILE *fp) {
	BNODE *bN = v;
	void *value = bN -> value;
	bN->display(value, fp);
	return;
}

static void freeBIN(void *v) {
	BNODE *x = v;		
	DLL *children = x -> children ;
	void *temp = x -> value;
	if (x->free != NULL) { 
		x->free(temp);
	}
	freeDLL(children);
	free(x);
	return;
}

BINOMIAL *newBINOMIAL(void (*display)(void *,FILE *),int (*comparator)(void *,void *),void (*updater)(void *,void *),void (*freer)(void *)) {
	BINOMIAL *b = malloc(sizeof(BINOMIAL));			// Allocate space
	assert(b != 0);
	b->size = 0;
	b->display = display;
	b->compare = comparator;
	b->update = updater;
	b->free = freer;
	b->rootList = newDLL(displayBIN, freeBIN);		// Initialize rootlist
	b->extreme = 0;
	return b;
}

void *insertBINOMIAL(BINOMIAL *b, void *value) {
	BNODE *n = newBIN(b->display, b->free, value);	
	insertDLL(b->rootList, 0, n);			
	b -> size ++;
	consolidate(b);
	return n;
}

int sizeBINOMIAL(BINOMIAL *b) {
	return b->size; 
}

void unionBINOMIAL(BINOMIAL *b, BINOMIAL *donor) {
	DLL *rootList1 = b -> rootList;
	DLL *rootList2 = donor -> rootList;
	unionDLL(rootList1, rootList2);				
	b -> size = sizeDLL(rootList1);			
	donor -> size = 0;					
	donor -> extreme = 0;					
	consolidate(b);
	return;
}

void deleteBINOMIAL(BINOMIAL *b, void *n) {
	decreaseKeyBINOMIAL(b, n, 0);			
	extractBINOMIAL(b);				
	return;
}

void decreaseKeyBINOMIAL(BINOMIAL *b, void *node, void *value) {
	BNODE *bN = node;
	//printf("fail heare \n");
	bN -> value = value;
	BNODE *n =  bubbleUp(b, bN);
	//printf("fail heare \n");
		
	// Update BINNODE value	
	if (b->compare(b->extreme -> value, n->value) > 0) {
		b -> extreme = n; 
	}
	return;
}

void *peekBINOMIAL(BINOMIAL *b) {
	return b -> extreme -> value;
}

void *extractBINOMIAL(BINOMIAL *b) {
	BNODE *removedValue = removeDLLnode(b -> rootList, b -> extreme -> owner);		;
	void *value = b -> extreme -> value;
	firstDLL(b -> extreme -> children);					// Iterator for head of DLL
	BNODE *current = 0;
	while (moreDLL(b -> extreme -> children)) {
		current = currentDLL(b -> extreme -> children);
		// Set each child's parent to itself
		current -> parent = current;
		nextDLL(b -> extreme -> children);				// Update iterator
	}
	unionDLL(b -> extreme -> children, b -> rootList);
	unionDLL(b -> rootList, b -> extreme -> children);				// Merge children DLL to rootList
	consolidate(b);						// Consolidate b's root list
	b -> size --;	
	freeDLL(removedValue -> children);
	free(removedValue);	
	return value;
}

void statisticsBINOMIAL(BINOMIAL *b, FILE *fp) {
	DLL *rootList = b -> rootList;
	fprintf(fp, "size: %d\n", b->size);
	fprintf(fp, "rootlist size: %d\n", sizeDLL(rootList));
	if (b -> extreme == 0) return;
	fprintf(fp, "extreme: ");
	b -> extreme->display(b -> extreme -> value, fp);
	fprintf(fp, "\n");	
	return;
}

void displayBINOMIAL(BINOMIAL *b, FILE *fp) {
	int degree = 0;
	void *minValue = 0;
	if (b == 0) {						// Empty Binomial heap
		fprintf(fp, "NULL\n");
		return;
	}
	firstDLL(b -> rootList);					// Point to rootList head
	BNODE* n = currentDLL(b -> rootList);		
	if (b -> extreme != 0) { 
		minValue = b -> extreme -> value;
	}
	fprintf(stdout, "rootlist: ");
	while (moreDLL(b -> rootList)) {
		if (degree < sizeDLL(n -> children)) {
			fprintf(fp, "NULL");
		}
		else if (degree == sizeDLL(n -> children)) {
			b->display(n -> value, fp);
			if (n -> value == minValue) { 
				fprintf(fp, "*");
			}
			nextDLL(b -> rootList);
		}	
		degree++;
		if (moreDLL(b -> rootList)) { 
			n = currentDLL(b -> rootList); 
			fprintf(fp, " ");
		}
	}
	fprintf(fp, "\n");
	return;
}

void displayBINOMIALdebug(BINOMIAL *b,FILE *fp) {
	DLL *currentList = b -> rootList;
	QUEUE *pQ = newQUEUE(displayBIN, freeBIN);
	QUEUE *cQ = newQUEUE(displayBIN, freeBIN);
	BNODE *n = 0;
	if (sizeDLL(currentList) == 0) { 
		displayDLL(currentList, fp);			
		fprintf(fp, "\n");
		return;
	}
	enqueue(pQ, currentList);			
	while (sizeQUEUE(pQ) != 0) {
		currentList = peekQUEUE(pQ);
		firstDLL(currentList);				

		displayDLL(currentList, fp);

		while (moreDLL(currentList)) {
			n = currentDLL(currentList);		
			if (sizeDLL(n -> children ) != 0) {
				enqueue(cQ, n -> children );
			}
			nextDLL(currentList);			
		}
		dequeue(pQ);
		if (sizeQUEUE(pQ) == 0) {
			if (sizeQUEUE(pQ) == 0) {
				fprintf(fp, "\n");
			}
			while (sizeQUEUE(cQ) > 0) {
				enqueue(pQ, (DLL *) dequeue(cQ));
			}

		}
	}
	freeQUEUE(pQ);
	freeQUEUE(cQ);
	return;
}

void freeBINOMIAL(BINOMIAL *b) {
	freeDLL(b -> rootList);
	free(b);
	return;
}
