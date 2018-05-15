/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithem and Data Structure
AVL tree 
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "avl.h"
typedef struct aval{
	void* value;
	int freq;
	int height;
	int balance;
	void (*display)(void *,FILE *);
	int (*comparator)(void *,void *);
	void (*free)(void *);
}AVAL;

AVAL* newAVAL(void* value, int freq,void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *)){
	AVAL* x = malloc(sizeof(AVAL));
	assert(x!=0);
	x->height = 1;
	x->balance = 0;
	x ->value= value;
	x ->freq = freq;
	x -> display = d;
	x -> free = f;
	x -> comparator = c;
	return x;
}


void* getAVALvalue(AVAL* x){	// get the original value in avl value
	return x->value;
}


int getAVALfreq(AVAL* x){	//get frequency in avl value
	return x->freq;
}

int getAVALbalance(AVAL* x){
	return x->balance;
}
int getAVALheight(AVAL* x){
	return x->height;
}

void increaseAFreq(AVAL* x){	// increase the frequency
	x-> freq ++;
}

void decreaseAFreq(AVAL* x){
	x-> freq --;
}

int ac(void* G1, void* G2){	//they are void type but we pass avl value to it
	AVAL* gv1 = G1;
	AVAL* gv2 = G2;

	return gv1 -> comparator(getAVALvalue(gv1),getAVALvalue(gv2));
}

void ad(void* G1,FILE* fp){		//G1 is void type but pass avl value to it
	AVAL* gv = G1;
	gv->display(getAVALvalue(gv),fp);
	//printf("height is %d", gv->height );
	//printf("balance value here is %d\n",gv ->balance);
	if(gv->freq !=1){
	fprintf(fp,"[%d]",gv->freq);
	}
	if(getAVALbalance(gv) == 1 )
		fprintf(fp,"+");
	if(getAVALbalance(gv)== -1)
		fprintf(fp,"-");
}

void af(void *n){	//n is void type but pass avl value to it
	AVAL* gv = n;
	if(gv->free!=NULL)
		gv->free(gv->value);
	free(n);
}
static void asw(BSTNODE *a,BSTNODE *b)
        {
        AVAL *ta = getBSTNODEvalue(a);
        AVAL *tb = getBSTNODEvalue(b);


        void *vtemp = ta->value;
        ta->value = tb->value;
        tb->value = vtemp;


        int ctemp = ta->freq;
        ta->freq = tb->freq;
        tb->freq = ctemp;

}

typedef struct avl{
  BST* tree;
  int size;
  void(*display)(void *, FILE *);
  int (*comparator)(void *, void *);
  void(*free)(void *);
} AVL;


AVL *newAVL(void (*d)(void *,FILE *),int (*c)(void *,void *),void (*f)(void *)){
  AVL * g = malloc(sizeof(AVL));
  assert(g != 0);
  g -> tree = newBST(ad,ac,asw,af);
  g -> size = 0;
  g -> display = d;
  g -> comparator = c;
  g -> free = f;
  return g;
}
//set balance
void setBalance(BSTNODE* x){
	BSTNODE* left = getBSTNODEleft(x);
	BSTNODE* right = getBSTNODEright(x);
	AVAL* v = getBSTNODEvalue(x);
	int leftheight;
	int rightheight;
	if(getBSTNODEleft(x) == NULL)
		leftheight =0;
	else{
		leftheight = getAVALheight(getBSTNODEvalue(left));
	}

	if(getBSTNODEright(x) == NULL)
		rightheight =0;
	else{
		rightheight = getAVALheight(getBSTNODEvalue(right));
	}

	if(leftheight >= rightheight)
		v->height = leftheight+1;
	else
		v->height = rightheight+1;
	v -> balance = leftheight - rightheight;
}

BSTNODE* favorite(BSTNODE* p){//pass a parent node return the favorite child
	AVAL* v = getBSTNODEvalue(p);
	if(getAVALbalance(v) > 0)
		return getBSTNODEleft(p);
	else if(getAVALbalance(v) < 0)
		return getBSTNODEright(p);
	else
		return NULL;
}

BSTNODE* sibling(BSTNODE* c){
	BSTNODE* p = getBSTNODEparent(c);
	assert(p);
	if(c == getBSTNODEleft(p))
		return getBSTNODEright(p);

	if(c == getBSTNODEright(p))
		return getBSTNODEleft(p);

	return NULL;
}
//check linear
int linear(BSTNODE* gp, BSTNODE* p, BSTNODE* c){
	return (getBSTNODEleft(gp)== p && getBSTNODEleft(p) == c)|| (getBSTNODEright(gp) == p && getBSTNODEright(p) == c);
}
//left rotation
void leftRotate(BSTNODE* p, BSTNODE* x){
	setBSTNODEright(p,getBSTNODEleft(x));	//p->right = x->left;
    if(getBSTNODEleft(x) !=0) setBSTNODEparent(getBSTNODEleft(x),p);   //if (x->left != 0) x->left->parent = p;
	setBSTNODEleft(x,p);//x->left = p;
    setBSTNODEparent(p,x);//p->parent = x;*/
}
//right rotation
void rightRotate(BSTNODE* p, BSTNODE* x){
	setBSTNODEleft(p,getBSTNODEright(x));//p->left = x->right;
    if(getBSTNODEright(x) !=0) setBSTNODEparent(getBSTNODEright(x),p);//   if (x->right != 0) x->right->parent = p;
    setBSTNODEright(x,p); //   x->right = p;
    setBSTNODEparent(p,x);//    p->parent = x;
}
void rotate(BST* t,BSTNODE* a, BSTNODE* b){//rotate a to b
	//handle grandparent
	BSTNODE* grandparent = getBSTNODEparent(b);
	if(grandparent == NULL){
		setBSTNODEparent(a,NULL);
		setBSTroot(t,a);
	}
	else if(getBSTNODEleft(grandparent)== b){
		setBSTNODEleft(grandparent,a);
		setBSTNODEparent(a,grandparent);
	}
	else{
		setBSTNODEright(grandparent,a);
		setBSTNODEparent(a,grandparent);
	}

	//rotate
	if(getBSTNODEleft(b) == a){//if a is left child do right rotation
		rightRotate(b,a);
	}
	else if(getBSTNODEright(b) == a){//if a is right child do left rotation
		leftRotate(b,a);
	}
}
//insert fix
static void insertionFixup(BST* t, BSTNODE* x){
	while(1){
		if(getBSTNODEparent(x) == NULL) //if v is the root
			break;
		else if(sibling(x)&&favorite(getBSTNODEparent(x)) == sibling(x)){
			setBalance(getBSTNODEparent(x));
			//printf("get the p's balance factors is %d\n", getAVALbalance(getBSTNODEvalue(p)));
			break;
		}
		else if(favorite(getBSTNODEparent(x)) == NULL){
			setBalance(getBSTNODEparent(x));
			//printf("get the p's balance factors is %d\n", getAVALbalance(getBSTNODEvalue(p)));
			x = getBSTNODEparent(x);
		}
		else{
			BSTNODE* y = favorite(x);
			BSTNODE* p = getBSTNODEparent(x);
			if(y && linear(p,x,y) == 0){
				rotate(t,y,x);
				rotate(t,y,p);
				setBalance(x);
				setBalance(p);
				setBalance(y);
			}
			else{
				rotate(t,x,p);
				setBalance(p);
				setBalance(x);
			}
			//printf("get the p's balance factors is %d\n", getAVALbalance(getBSTNODEvalue(p)));
			break;
		}
	}
}
void insertAVL(AVL *g,void *value){
	AVAL* newValue = newAVAL(value,1,g->display, g->comparator, g->free);
	if(findAVL(g,value) == NULL){
		//set parent of new insert to NULL if it is root;
		BSTNODE* newInsert = insertBST(g->tree, newValue);
		if(newInsert == getBSTroot(g->tree)){
			setBSTNODEparent(newInsert,NULL);
		}
		insertionFixup(g->tree, newInsert);//take newly inserted node
	}
	else{
		increaseAFreq(findAVL(g,value));
		free(newValue);
	}
	g->size ++;
}

int findAVLcount(AVL *g,void *value){
	//pass value
	if(findAVL(g,value) ==NULL)
		return 0;
	return getAVALfreq(findAVL(g,value));
}

void *findAVL(AVL *g,void *value){	// pass value return
	AVAL* newNode = newAVAL(value,1,g->display, g->comparator, g->free);
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

// delete fix
void deleteFixup(BST* t, BSTNODE* x){
	AVAL* v = getBSTNODEvalue(x);
	v->height = 0;
	while(1){
		if(getBSTroot(t) == x){
			//printf("case1\n" );
			break;
		}
		else if(favorite(getBSTNODEparent(x)) == x){
			//printf("case2\n");
			setBalance(getBSTNODEparent(x));
			x = getBSTNODEparent(x);
		}
		else if(favorite(getBSTNODEparent(x)) == NULL){
			//printf("case3\n");
			setBalance(getBSTNODEparent(x));
			break;
		}
		else{
			BSTNODE* p = getBSTNODEparent(x);
			BSTNODE* z= sibling(x);
			BSTNODE* y= favorite(z);
			if(y && linear(p,z,y)==0){
				//printf("case4\n");
				rotate(t,y,z);
				rotate(t,y,p);
				setBalance(p);
				setBalance(z);
				setBalance(y);
				x = y;
			}
			else{
				//printf("case5\n" );
				rotate(t,z,p);
				setBalance(p);
				setBalance(z);
				if(y==NULL)
					break;
				x=z;
			}
		}
	}
}

void *deleteAVL(AVL *g,void *value){
	AVAL* newNode = newAVAL(value,1,g->display, g->comparator, g->free);
	void* result;
	assert(findBST(g->tree,newNode))	;
	BSTNODE* w = findBST(g->tree,newNode);
	AVAL* x = getBSTNODEvalue(w);
	assert(x);
	if(getAVALfreq(x) == 1){
		BSTNODE* temp = swapToLeafBST(g->tree,w);
		deleteFixup(g->tree, temp);
		pruneLeafBST(g->tree,temp);
		setBSTsize(g->tree,sizeBST(g->tree)-1);
		result = getAVALvalue(getBSTNODEvalue(temp));
		freeBSTNODE(temp,g->free);
	}
	else{
		decreaseAFreq(x);
		result = NULL;
	}
	free(newNode);
	
	g->size --;
	return result;
}

int sizeAVL(AVL *g){
  return sizeBST(g->tree);
}

int duplicatesAVL(AVL *g){
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

void statisticsAVL(AVL *g,FILE *fp){
	BST* t= g->tree;
	fprintf(fp,"Duplicates: %d\n",duplicatesAVL(g));
	fprintf(fp, "Nodes: %d\n",sizeBST(t));
	fprintf(fp,"Minimum depth: %d\n",minDepth(getBSTroot(t)));
	fprintf(fp,"Maximum depth: %d\n",maxDepth(getBSTroot(t)));
}

void displayAVL(AVL *g,FILE *fp){
	displayBSTdecorated(g->tree, fp);
}

void displayAVLdebug(AVL *g,FILE *fp){
	displayBST(g -> tree,fp);
}

void freeAVL(AVL *g){
	freeBST(g->tree);
	free(g);
}
