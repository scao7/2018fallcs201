/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithem and Data Structure
singly linked list
*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>
#include "sll.h"

typedef struct node
{	
	void *value;
	struct node *next;
}Node;

typedef struct sll
{
	Node *head;
	Node *tail;
	int size;
	void (*display)(void *, FILE *);
	void (*free)(void *);
}SLL;

//////////////////////////////////////
//d is the display function
//f is the freeing function
SLL *newSLL(void (*d)(void *, FILE *), void(*f)(void *))
{
	SLL *items = malloc(sizeof(SLL));
	assert(items !=0);
	items -> head =0;
	items -> tail =0;
	items -> size =0;
	items ->display = d;
	items -> free =f;
	return items;
}
//////////////////////////
void insertSLL(SLL *items, int index, void *value)
{
	assert(index <= items -> size);
	assert(index >=0);
	Node *newNode = malloc (sizeof (Node));
	newNode -> value = value;
	newNode -> next =NULL;
	if (items ->size == 0){
		items -> head = newNode;
		items -> tail = newNode;
		newNode -> next =NULL;
	}
	else if (index == 0) { /////////add at front 
		newNode -> next = items -> head;
		items -> head = newNode;
	}
	else if (index == items -> size){ //////add at back 
		items -> tail -> next = newNode;
		items -> tail = newNode;
	}
	else { 
		Node *search = items -> head;
		for (int i=0;i<index-1;i++){// find previous node location 
			search = search -> next;
		}
		newNode -> next = search -> next ;
		search -> next = newNode;
		 
	} 
	items -> size ++;
}

///////////////////////
void *removeSLL(SLL *items, int index){
	assert(index < items -> size);
	assert(items -> size > 0);
	assert(index >=0 );
	void *content=NULL;
	if (index ==0){
		if (items -> head -> next != NULL){
			content = items -> head->value ;
			Node *temp=items -> head;
			items -> head = items -> head -> next;
			//free(temp -> value);
			free(temp);
		}
		else {
			//content = items -> head -> value ;
			Node *temp = items -> head;
			content = temp -> value;
			items -> head = NULL;
			items -> tail = NULL;
			free(temp);
		}
	}
	else if(index == items -> size -1){
		content = items -> tail -> value;
		Node *search = NULL;
		for (search = items -> head; search != NULL ; search = search -> next){
			if (search -> next -> next == NULL){
				Node *temp=search -> next;
				search -> next = NULL;
	
				//free(temp->value);//have debug
				free(temp);
				items -> tail = search;
			}
		}
	}
	else{	
		Node *search = items -> head;
		for (int i=0;i<index -1;i++){
			search = search -> next;
		}
		Node *temp = search -> next ;
		content = search -> next -> value;	
		search ->next = search -> next -> next ;
		free(temp);
	}
	items -> size --;
	return content;
}
////////////////////
void unionSLL(SLL *recipient,SLL *donor){
	if (recipient -> size == 0){
			recipient -> head = donor -> head;
			recipient -> tail = donor -> tail;
			recipient -> size = donor -> size;
	}
	else{
		recipient -> tail ->next = donor -> head;
		recipient -> tail = donor -> tail;
		recipient -> size = recipient -> size + donor -> size ;
	}
		donor -> head = 0;
		donor -> tail = 0;
		donor -> size = 0;
}
void *getSLL(SLL *items, int index ){
	void *content=NULL;
	if (index ==0){
		content = items -> head -> value;
	}
	else if(index == items -> size - 1){
		content = items -> tail -> value;
	}
	else {
		Node *search = items -> head;
		for (int i=0;i<index;i++){
			search = search -> next;
		}
		content = search -> value;
	}
	return content;	
}
///////////////
void *setSLL (SLL *items, int index, void *value){
	assert(index <= items ->  size);
	assert(index >=0);
	void *content=NULL;
	if (index == 0 && items -> size != 0){
		content= items -> head -> value;
		items -> head -> value = value;
	}
	else if(index == items -> size -1){///have debug
		content = items -> tail -> value;
		items -> tail -> value = value;
	}
	else if ( index == items -> size ){
		content= NULL;
		insertSLL(items, index , value);
	}
	else {
		Node *search = items -> head;
		for ( int i=0;i<index;i++){
			search = search -> next;
		}
		content = search -> value;// have debuged 
		search -> value = value;
		
	}	

	return content;
}
///////////////////////////
int sizeSLL (SLL *items){
	return items -> size;
}
///////////////////
void displaySLL (SLL *items, FILE *fp)
{
	fprintf(fp, "{");
		Node *search=items -> head;
		for (search = items -> head; search != NULL; search = search -> next){
			items -> display ( search -> value , fp);
			if (search -> next != NULL){
				fprintf(fp, ",");
			}
		
	} 
		fprintf(fp, "}");
	
		
}
///////////////////
void displaySLLdebug(SLL *items, FILE *fp){
	fprintf(fp, "head->{");
	if(items -> size >0){
		Node *search = items -> head;
		while (search !=NULL){
			items -> display (search -> value  ,fp);
			if(search -> next != NULL)
				printf(",");
			search = search -> next;
		}
	}
	fprintf(fp,"}");

	fprintf(fp, ",tail->{");
	if(items -> size >0)
		items -> display (items -> tail ->value , fp);
	fprintf(fp,"}");
}
//////////////
void freeSLL(SLL *items){
	
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
