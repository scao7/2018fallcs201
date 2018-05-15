/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithem and Data Structure
gree search tree 
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "gst.h"
typedef struct gval{
	void* value;
	int freq;
	void (*display)(void *,FILE *);
	int (*comparator)(void *,void *);
	void (*free)(void *);
}GVAL;

GVAL* newGVAL(void* value, int freq,void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *)){
	GVAL* x = malloc(sizeof(GVAL));
	assert(x!=0);
	x ->value= value;
	x ->freq = freq;
	x -> display = d;
	x -> free = f;
	x -> comparator = c;
	return x;
}


void* getGVALvalue(GVAL* x){	// get the original value in gst value
	return x->value;
}


int getGVALfreq(GVAL* x){	//get frequency in gst value
	return x->freq;
}


void increaseFreq(GVAL* x){	// increase the frequency
	x-> freq ++;
}

void decreaseFreq(GVAL* x){
	x-> freq --;
}

int gc(void* G1, void* G2){	//they are void type but we pass gst value to it
	GVAL* gv1 = G1;
	GVAL* gv2 = G2;

	return gv1 -> comparator(getGVALvalue(gv1),getGVALvalue(gv2));
}

void gd(void* G1,FILE* fp){		//G1 is void type but pass gst value to it
	GVAL* gv = G1;
	
	gv->display(getGVALvalue(gv),fp);
	if(gv->freq != 1){
		fprintf(fp,"[%d]",gv->freq);
	}
}

void gf(void *n){	//n is void type but pass gst value to it
	GVAL* gv = n;
	if(gv->free!=NULL)
		gv->free(gv->value);
	free(n);
}

typedef struct gst{
  BST* tree;
  int size;
  void(*display)(void *, FILE *);
  int (*comparator)(void *, void *);
  void(*free)(void *);
} GST;

		
GST *newGST(void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *)){
  GST * g = malloc(sizeof(GST));
  assert(g != 0);
  g -> tree = newBST(gd,gc,NULL,gf);
  g -> size = 0;
  g -> display = d;
  g -> comparator = c;
  g -> free = f;
  return g;
}
void insertGST(GST *g,void *value){
	GVAL* newValue = newGVAL(value,1,g->display, g->comparator, g->free);
	if(findGST(g,value) == NULL){
		insertBST(g->tree, newValue);
	}
	else{
		increaseFreq(findGST(g,value));
		free(newValue);
	}
	g->size ++;
}

int findGSTcount(GST *g,void *value){
	//pass value
	if(findGST(g,value) ==NULL)
		return 0;
 return getGVALfreq(findGST(g,value));
}

void *findGST(GST *g,void *value){	// pass value return
	GVAL* newNode = newGVAL(value,1,g->display, g->comparator, 0);
	void* result;
	BSTNODE* w = findBST(g->tree,newNode);
	if(w){
		result = getBSTNODEvalue(w);
	}
	else{
		result = NULL;
	}
	free(newNode);
	return result;
}

void *deleteGST(GST *g,void *value){
	GVAL* newNode = newGVAL(value,1,g->display, g->comparator, 0);
	void* result;
	BSTNODE* w = findBST(g->tree,newNode);
	GVAL* x = getBSTNODEvalue(w);
	if(getGVALfreq(x) == 1){
		BSTNODE* y = deleteBST(g->tree,newNode);
		result = getGVALvalue(x);
		freeBSTNODE(y,0);
		free(x);
	}
	else{
		decreaseFreq(x);
		result = NULL;
	}
	free(newNode);
	g->size --;
	return result;
}

int sizeGST(GST *g){
  return sizeBST(g->tree);
}

int duplicates(GST *g){
  return g->size - sizeBST(g->tree);
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
       int lDepth = minDepth(getBSTNODEleft(node));
       int rDepth = minDepth(getBSTNODEright(node));

       /* use the small one */
       if (lDepth < rDepth)
           return(lDepth+1);
       else
		   return(rDepth+1);
   }
}

void statisticsGST(GST *g,FILE *fp){
	BST* t= g->tree;
	fprintf(fp,"Duplicates: %d\n",duplicates(g));
	fprintf(fp, "Nodes: %d\n",sizeBST(t));
	fprintf(fp,"Minimum depth: %d\n",minDepth(getBSTroot(t)));
	fprintf(fp,"Maximum depth: %d\n",maxDepth(getBSTroot(t)));
}

void displayGST(GST *g,FILE *fp){
	displayBSTdecorated(g->tree, fp);
}

void displayGSTdebug(GST *g,FILE *fp){
	displayBST(g -> tree,fp);
}

void freeGST(GST *g){
	freeBST(g->tree);
	free(g);
}
