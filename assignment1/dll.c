/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithm and Data Structure
double linked list  
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dll.h"
#include "integer.h"

typedef struct node
{
    void *value;
    struct node *prev;
    struct node *next;
} Node;

typedef struct dll
{
    Node *head;
    Node *tail;
    int size;
    void (*display)(void *items, FILE *fp);
    void (*free) (void *items);
} DLL;
/////////////////////////////////////
//d is the display function
//f is the freeing function

DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *))
{
	DLL *items = malloc(sizeof(DLL));
	assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
}
/////////////////////////////////////
void insertDLL(DLL *items,int index,void *value)
{
	assert(index>=0);
	assert(index <= items-> size);
	int i = 0;
	Node *newNode = malloc(sizeof (Node));
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
			Node *search = items -> head;
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
			Node *search = items -> tail;
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
}
////////////////////////////////////////
void *removeDLL(DLL *items,int index)
{
	assert(items-> size > 0);
	assert(index >= 0);
	assert(index < items-> size);
	void *content = NULL;
	
	 if (index <items -> size/2)//have debuged....
	{
			Node *search=NULL;
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
			Node *search; 
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
///////////////////////////////////////////////
void unionDLL(DLL *recipient,DLL *donor)
{
	if (recipient -> size == 0){
			recipient -> head = donor -> head;
			recipient -> tail = donor -> tail;
			recipient -> size = donor -> size;
	}
	else{
		recipient -> tail ->next = donor -> head;
		donor -> head -> prev = recipient-> tail;
		recipient -> tail = donor -> tail;
		recipient -> size = recipient -> size + donor -> size ;
	}
		donor -> head = 0;
		donor -> tail = 0;
		donor -> size = 0;
}
////////////////////////////////////////////////
void *getDLL(DLL *items,int index)
{
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
		Node *search;
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
/////////////////////////////////////////////////////////
void *setDLL(DLL *items, int index, void *value)
{
	assert(index >= 0 );
	assert(index <= items-> size);

	Node *search;
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
///////////////////////////////////////////////////////
int sizeDLL(DLL *items)
{
	return items->size;
}
////////////////////////////////////////////////////
void displayDLL(DLL *items,FILE *fp)
{
	fprintf(fp, "{{");
	if(items ->size >0){
		Node *search=NULL;
		for (search = items -> head; search != NULL; search = search -> next){
			items -> display ( search -> value , fp);
			if (search -> next != NULL){
				fprintf(fp, ",");
			}
		}
	} 
	fprintf(fp, "}}");
	
}
//////////////////////////////////////////////
void displayDLLdebug(DLL *items,FILE *fp)
{
	fprintf(fp, "head->{{");
	if(items -> size >0){
		Node *search = items -> head;
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
	
}
///////////////////////////////////////
void freeDLL(DLL *items)
{

	
	Node *temp;
	while (items -> head != NULL){
		temp=items -> head;
		items -> head = items -> head  -> next;
		if (items -> free != 0)
			items ->free(temp-> value);
		free (temp);	
	}
	
		
free(items);	
}

