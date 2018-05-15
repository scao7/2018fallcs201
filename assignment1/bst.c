/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithm and Data Structure
binary search tree
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "bst.h"

typedef struct bstnode{
	void* value;
	struct bstnode* left;
	struct bstnode* right;
	struct bstnode* parent;
}BSTNODE;
/////////////////////////////////////

BSTNODE *newBSTNODE(void *v){
	BSTNODE *items = malloc(sizeof(BSTNODE));
	assert(items !=0);
	items -> value = v;
	items -> left = 0;
	items -> right = 0;
	items -> parent = 0;
	return items;
}

void *getBSTNODEvalue(BSTNODE *n){
	return n->value;
}

void setBSTNODEvalue(BSTNODE *n, void *value){
	n->value = value;
	return;
}

BSTNODE *getBSTNODEleft(BSTNODE *n){
	return n->left;
}

void setBSTNODEleft(BSTNODE *n,BSTNODE *replacement){
	n->left = replacement;
	return;
}
BSTNODE *getBSTNODEright(BSTNODE *n){
	return n-> right;
}
void setBSTNODEright(BSTNODE *n,BSTNODE *replacement){
	n-> right = replacement;
	return;
}
BSTNODE *getBSTNODEparent(BSTNODE *n){
	return n->parent;
}
void setBSTNODEparent(BSTNODE *n,BSTNODE *replacement){
	n->parent=replacement;
	return;
};
void freeBSTNODE(BSTNODE *n,void (*f)(void *)){
	if(f!=NULL)
		f(n->value);
		free(n);
	return;
}
////////////////////////////////////////////////////////////////
typedef struct bst{
	struct bstnode *root;
	int size;
	void(*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void(*swapper)(BSTNODE *, BSTNODE *);
	void(*free)(void *);
}BST;
//swapper function
static void sw(BSTNODE* a, BSTNODE* b){
	void* temp = getBSTNODEvalue(a);
	setBSTNODEvalue(a,getBSTNODEvalue(b));
	setBSTNODEvalue(b,temp);
}
BST *newBST(void (*d)(void *, FILE *), int (*c)(void *, void *), void(*s)(BSTNODE *, BSTNODE*),void (*f)(void *)){
	BST *tree = malloc(sizeof(BST));
	assert(tree != 0);
	tree -> size = 0;
	tree -> root = 0;
	tree -> display = d;
	tree -> comparator = c;
	tree -> swapper = s;
	if (s == NULL){
		tree -> swapper =sw; //if swapper is null using own swapper function
	}
	tree -> free = f;
	return tree;
}

BSTNODE *getBSTroot(BST *t){
	return t->root;
}
void setBSTroot(BST *t,BSTNODE *replacement){
	t->root = replacement;
	return;
}

void setBSTsize(BST *t,int s){
	t->size =s;
	return;
}

BSTNODE *insertBST(BST *t,void *value){
	BSTNODE* newNode = newBSTNODE(value);
	BSTNODE* check = NULL; // check parent;
	BSTNODE* search = getBSTroot(t);
	while(search != NULL){
		check = search;
		if (t->comparator(getBSTNODEvalue(newNode),getBSTNODEvalue(search))<0)
			search = getBSTNODEleft(search);
		else
			search = getBSTNODEright(search);
	}
	setBSTNODEparent(newNode,check);
	if(check == NULL)//empty tree
		setBSTroot(t,newNode);
	else if(t->comparator(getBSTNODEvalue(newNode), getBSTNODEvalue(check))<0)
		setBSTNODEleft(check, newNode);
	else
		setBSTNODEright(check, newNode);

	setBSTsize(t,sizeBST(t)+1);
	return newNode;
}

BSTNODE *findBST(BST *t,void *value){
	BSTNODE* search = getBSTroot(t);
	while(search != NULL ){
		if(t->comparator(value,getBSTNODEvalue(search))>0)
			search = getBSTNODEright(search);
		else if(t->comparator(value,getBSTNODEvalue(search))<0)
			search = getBSTNODEleft(search);
		else
			return search;
	}
	return NULL;
}

BSTNODE *deleteBST(BST *t,void *value){
	assert(t!=NULL);
	BSTNODE* temp=findBST(t,value);
	if(temp == NULL)
		return NULL;
	temp = swapToLeafBST(t, temp);
	pruneLeafBST(t,temp);
	setBSTsize(t,sizeBST(t)-1);
	return temp;
}
//help fuction to find successor
static BSTNODE* SUCCESSOR(BSTNODE* node){
	assert(node!=NULL);
	BSTNODE* search = node;
	if(getBSTNODEright(search)!=NULL){
		search = getBSTNODEright(search);
	}
	else {
		return NULL;
	}
	while(getBSTNODEleft(search)!= NULL){
		search = getBSTNODEleft(search);
	}
	return search;
}

static BSTNODE* PRECESSOR(BSTNODE* node){
	assert(node!=NULL);
	BSTNODE* search = node;
	if(getBSTNODEleft(search)!=NULL){
		search = getBSTNODEleft(search);
	}
	else {
		return NULL;
	}
	while(getBSTNODEright(search)!= NULL){
		search = getBSTNODEright(search);
	}
	return search;
}
BSTNODE *swapToLeafBST(BST *t,BSTNODE *node){
	if(node == NULL || (getBSTNODEleft(node)== NULL && getBSTNODEright(node)== NULL))
		return node;
	else{
		if(SUCCESSOR(node)){
			t->swapper(node, SUCCESSOR(node));
			return swapToLeafBST(t, SUCCESSOR(node));
		}
		else if(PRECESSOR(node)){
			t->swapper(node, PRECESSOR(node));
			return swapToLeafBST(t, PRECESSOR(node));
		}
		else
			return node;
	}
}

void pruneLeafBST(BST *t,BSTNODE *leaf){
	assert(sizeBST(t) != 0);
	assert(leaf!= NULL);
	BSTNODE* temp = getBSTNODEparent(leaf);
	if(getBSTNODEparent(leaf)==NULL){
		setBSTroot(t,NULL);

	}

	else if (getBSTNODEleft(temp) == leaf){
		setBSTNODEleft(temp, NULL);

	}
	else{
		setBSTNODEright(temp, NULL);
	}
	//setBSTsize(t,sizeBST(t)-1); 
//The pruneLeafBST should not decrement the size
// of the BST. Only the deleteBST method should decrement the count.
	setBSTNODEparent(leaf,NULL);
}
int sizeBST(BST *t){
	return t->size;
}
//help function for max depth
static int maxDepth(BSTNODE* node)
{
   if (node==NULL)
       return -1;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = maxDepth(getBSTNODEleft(node));
       int rDepth = maxDepth(getBSTNODEright(node));

       /* use the larger one */
       if (lDepth > rDepth)
           return(lDepth+1);
       else
		   return(rDepth+1);
   }
}
//get min depth help function
static int minDepth(BSTNODE* node)
{
   if (node==NULL)
       return -1;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = minDepth(node->left);
       int rDepth = minDepth(node->right);

       /* use the small one */
       if (lDepth < rDepth)
           return(lDepth+1);
       else
		   return(rDepth+1);
   }
}

void statisticsBST(BST *t,FILE *fp){
	fprintf(fp, "Nodes: %d\n", t->size);
	fprintf(fp,"Minimum depth: %d\n",minDepth(getBSTroot(t)));
	fprintf(fp,"Maximum depth: %d\n",maxDepth(getBSTroot(t)));
}
//help function for preorder
static void printPreorder(BST* t,BSTNODE* node,FILE* fp)
{
	assert(t!=NULL);
     if (node == NULL){
		  return;
	 }

     /* first print data of node */
	 if(node != getBSTroot(t))
		fprintf(fp," ");
	 fprintf(fp,"[");
	 if(getBSTNODEvalue(node )!=NULL)
     t->display(getBSTNODEvalue(node), fp);
     /* then recur on left subtree */

     printPreorder(t,getBSTNODEleft(node),fp);

     /* now recur on right subtree */
     printPreorder(t,getBSTNODEright(node),fp);
	 fprintf(fp,"]");
}

void displayBST(BST *t,FILE *fp){
	if(getBSTroot(t)==NULL)
		fprintf(fp,"[]");
	printPreorder(t, getBSTroot(t),fp);
}

void displayBSTdebug(BST *t,FILE *fp){
	if(getBSTroot(t)== NULL) return;
	QUEUE* q= newQUEUE(t->display,t->free);
	enqueue(q,getBSTroot(t));//enque node
	BSTNODE* search=getBSTroot(t);
	while(1){
		int nodeCount = sizeQUEUE(q);
		if(nodeCount == 0)
			break;
		while (nodeCount > 0){
			search = peekQUEUE(q);

			t->display(getBSTNODEvalue(search),fp);
			if(nodeCount != 1)
				fprintf(fp," ");
			dequeue(q);
			if(getBSTNODEleft(search))
				enqueue(q,getBSTNODEleft(search));

			if(getBSTNODEright(search))
				enqueue(q,getBSTNODEright(search));

			nodeCount--;
		}

		fprintf(fp,"\n");
	}
	freeQUEUE(q);

}
//healp function for free
static void deallocate (BST* t, BSTNODE* node){
    //do nothing if passed a non-existent node
    if (node == NULL)
        return;

    //now onto the recursion
    deallocate(t,getBSTNODEleft(node));
    deallocate(t,getBSTNODEright(node));

    freeBSTNODE(node, t->free);
}
void freeBST(BST *t){
	deallocate(t,getBSTroot(t));
	free(t);

}
