/*
written by Shengting Cao 
University of Alabama 
2018 FALL 
CS201 Algorithem and Data Structure
double linked list 
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include "dll.h"

typedef struct dllNODE DLLNODE;

struct dllNODE {
	void *value;
	DLLNODE *next;
	DLLNODE *prev;					
};

struct dll {
	DLLNODE *iterator;					
	int size;						
	DLLNODE *head;						
	DLLNODE *tail;						
	void (*display)(void *, FILE*);	
	void (*free)(void *);
	
};

////////////////////////////////////
DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)) {
	DLL *items = malloc(sizeof(DLL));
	assert(items != 0);
	items->head = 0;
	items->tail = 0;
	items->size = 0;
	items->display = d;
	items->free = f;
	return items;
}
 
void *insertDLL(DLL *items,int index,void *value) {
assert(index>=0);
	assert(index <= items-> size);
	int i = 0;
	DLLNODE *newNode = malloc(sizeof (DLLNODE));
	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;
	
	if (index ==  0)//add to head for constant time 
	{
		if (items -> head ==NULL){
			items -> head =newNode;
			items -> tail = newNode;
			newNode->next =NULL;
			newNode -> prev=NULL;
		}
		else {
			newNode -> next = items -> head;
			newNode -> prev = NULL;
			items -> head -> prev = newNode;
			items -> head = newNode;
		}
		

	}
	else if (index == items -> size )//add to tail for constant time 
	{
		newNode -> prev = items -> tail;
		newNode -> next = NULL;
		items -> tail -> next = newNode;
		items -> tail = newNode;
			
	}
	else {			//add in middle for linear time
		
		
		if (index < (items->size)/2) //travel from the front
		{
			DLLNODE *search = items -> head;
			for (i = 0; i<index; i++)//have debuged.....
			{
				search = search->next;	
			}
			newNode -> next = search;
			newNode -> prev = search -> prev;
			search -> prev -> next = newNode;
			search -> prev = newNode;
		}
		else// travel from the back 
		{
			DLLNODE *search = items -> tail;
			for (i = 0; i< items->size - index-1; i++)
			{
				search = search->prev;	
			}
			newNode -> next = search;// have debuged 
			newNode -> prev = search -> prev;
			search -> prev -> next = newNode;
			search -> prev = newNode;
		}
	}
	items -> size ++; 

	return newNode;
}


void *removeDLL(DLL *items,int index) {
	assert(items-> size > 0);
	assert(index >= 0);
	assert(index < items-> size);
	void *content = NULL;
	
	 if (index <items -> size/2)//have debuged....
	{
			DLLNODE *search=NULL;
			search = items->head;		
			for(int i = 0; i < index ; i++)
			{
				search = search->next;
			}
			content=search ->value;
			if (search -> prev==NULL){
				
				items -> head = search-> next ;
	
			}
			else {
				
				search -> prev -> next = search -> next;
				
			}
			if (search -> next == NULL){
				items -> tail = search -> prev;
			}
			else {
				
				search -> next -> prev=search -> prev;
				
			}
			free(search);
	}
	else{
			DLLNODE *search; 
			search = items->tail;
			for(int i = 0; i < items-> size-index-1; ++i)
			{
				search = search->prev;
				
			}			
			content=search -> value;
			if(search -> next == NULL)
				items-> tail = search -> prev;
			else {
	
				search -> next -> prev = search -> prev;
			
			}
			if(search -> prev== NULL)
				items -> head = search -> next ;
			else {
			
				search -> prev  -> next = search -> next;

			}
			free(search);
	}
	
	items -> size --;
	return content;
}

void unionDLL(DLL *recipient,DLL *donor) {
	int sizeDonor = sizeDLL(donor);
	int sizeRecip = sizeDLL(recipient);

	if (sizeDonor == 0) {
		return;
	}

	else if (sizeRecip == 0) {
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = donor->size;

		donor->head = donor->tail = 0;
		donor->size = 0;

		return;
	}

	(recipient->tail)->next = donor->head;
	(donor->head)->prev = recipient->tail;
	recipient->tail = donor->tail;
	recipient->size += donor->size;
	
	donor->head = donor->tail = 0;
	donor->size = 0;

	return;
}


void *getDLL(DLL *items,int index) {
	assert(index >= 0 );
	assert(index < items-> size);
	//Node *newNode;
	void *content= NULL;

// if is head Node 
	if (index == 0)
	{
		content = items-> head ->value;
	}
// if is tail Node
	else if (index == items-> size-1){
		content = items -> tail -> value;
	}
// if is middle Node 

	else{
		//int i = 0;
		DLLNODE *search;
		if (index < (items-> size)/2 )// travel from the front
		{
			search = items-> head;
			for (int i = 0; i < index; i++)
			{
				search = search->next;
			}
		}
		else // travel from the back
		{
			search = items-> tail;
			for (int i = 0; i < (items-> size) - index-1; i++)
			{
				search = search->prev;
			}			
		}
		content = search->value;
	}
	return content;
}

void *setDLL(DLL *items,int index,void *value) {
	
	assert(index >= 0 );
	assert(index <= items-> size);

	DLLNODE *search;
	void *content = NULL;
	if (index == 0 && (items -> size != 0))// update first one
	{
		content = items->head -> value;
		items->head->value = value;
	}
	// set the tail
	else if ((items->size != 0) && (index == items-> size -1))// update the last one
	{
		content = items->tail-> value;
		items->tail->value = value;
		
	}
	// set the size index
	else if (index == items-> size)
	{
		insertDLL(items,index,value);
		content= NULL;
	}
	// set at the middle
	else
	{
		int i = 0;
		if (index < (items->size) /2)// travel from front
		{
			search = items->head;
			for (i=0; i<index; i++){
				search = search->next;
			}
			content = search -> value;
			search->value = value;
		
		}
		else// travel from back
		{
			search = items->tail;
			for (i=0; i<(items->size)- index-1; i++)
			{
				search = search->prev;
			}
			content = search->value;
			search->value = value;
		}
	}
	return content;
}


int sizeDLL(DLL *items) {
	return items->size;
}

void displayDLL(DLL *items,FILE *fp) {
	fprintf(fp, "{{");
	if(items ->size >0){
		DLLNODE *search=NULL;
		for (search = items -> head; search != NULL; search = search -> next){
			items -> display ( search -> value , fp);
			if (search -> next != NULL){
				fprintf(fp, ",");
			}
		}
	} 
	fprintf(fp, "}}");
	return;
}

void displayDLLdebug(DLL *items,FILE *fp) {
	fprintf(fp, "head->{{");
	if(items -> size >0){
		DLLNODE *search = items -> head;
		while (search !=NULL){
			items -> display (search -> value  ,fp);
			if(search -> next != NULL)
				printf(",");
			search = search -> next;
		}
	}
	fprintf(fp,"}}");

	fprintf(fp, ",tail->{{");
	if(items -> size >0)
		items -> display (items -> tail ->value , fp);
	fprintf(fp,"}}");

	return;
}

void freeDLL(DLL *items) {
	DLLNODE *temp;
	while (items -> head != NULL){
		temp=items -> head;
		items -> head = items -> head  -> next;
		if (items -> free != 0)
			items ->free(temp-> value);
		free (temp);	
	}
	
		
	free(items);
}
 
void removeDLLall(DLL *items) {
	int size = sizeDLL(items);
	DLLNODE *head = items -> head;
	
	while (size > 0) {					// Free list nodes
		removeDLLnode(items, head);
		
		size = sizeDLL(items);
		head = items -> head;
	}

	items -> head =0;
	items -> tail =0;

	return;
}

void *removeDLLnode(DLL *items, void *n) {
	DLLNODE *node = n;					// void * is DLLNODE *
	DLLNODE *oldNode = 0;
	void *old = 0;
	int size = sizeDLL(items);
	
	assert(size > 0);
	assert(node != 0);

	items -> iterator = node;


	if (items -> iterator == items -> head) {
		old = items -> iterator -> value;
		oldNode = items -> iterator;					
		items -> head =  items -> iterator -> next; 

		if (size == 1){
			items -> tail =0;
		}
		
		else {
			items -> head -> prev = 0;
		}
	}

	else if (items -> iterator == items -> tail) {
		old = items -> iterator -> value;
		oldNode = items -> iterator;
		items -> tail = items -> iterator -> prev; 

		if (size == 1){
			items -> tail =0;
		} 
	
		else {
			items -> tail -> next =0;
		}
	}
	
	else {
		old =items -> iterator -> value ;
		oldNode = items -> iterator;
		items -> iterator -> prev -> next = items -> iterator -> next; 

		if (items -> iterator -> next == 0){
			items -> tail = items -> iterator -> prev;
		}
		
		else{
			items -> iterator -> next -> prev = items -> iterator -> prev;
		}
	}
	
	free(oldNode);

	items -> size --; 

	return old;	
}

void firstDLL(DLL *items) {
	items -> iterator = items -> head;
	return;
}

void lastDLL(DLL *items) {
	items -> iterator = items -> tail;	
	return;
}

int moreDLL(DLL *items) {
	if(items -> iterator == 0){
		return 0;
	}
	else{
		return 1;
	}
}

void nextDLL(DLL *items) {
	items -> iterator = items -> iterator -> next;
	return;
}

void prevDLL(DLL *items) {
	items -> iterator = items -> iterator -> prev;
	return;
}

void *currentDLL(DLL *items) {
	return items -> iterator -> value;
}

