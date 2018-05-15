/* this is the avl tree class @_@ it use the bst and base and it should be dynamic programing.
Author: minrui huang
Date: spring 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "avl.h"

typedef struct avlvalue AVLVALUE;
AVLVALUE *newAVLVALUE(void *v, void (*d)(void *, FILE *), int (*c)(void *, void *), void (*f)(void *));
void avlSwapper(BSTNODE*a, BSTNODE*b);
void avlDisplay(void*, FILE*);
int avlComparator(void* , void*);
void avlFree(void*);
void *getAVLVALUE(AVLVALUE *v);
static void insertFixup(BST *, BSTNODE *);
static void deletionFixup(BST *, BSTNODE *);
BSTNODE* sibling(BSTNODE*);
void setBalance(BSTNODE* fixNode);
int isRoot(AVL *t, BSTNODE *compareNode);
int linear(BSTNODE *, BSTNODE *, BSTNODE *);
void rotate(BST* t,BSTNODE* a, BSTNODE* b);
BSTNODE *favor(BSTNODE *parent);
void leftRotate(BSTNODE* , BSTNODE* );
void rightRotate(BSTNODE* , BSTNODE* );


struct avl
{
	BST* tree;
	void (*display)(void*, FILE *);
	int (*compare)(void *, void*);
    void (*free)(void *);
	int size;
};

struct avlvalue
{
	void* value;
	int count;
    int height;
	int leftHeight;
	int rightHeight;
	int balance;
	void (*display)(void*, FILE *);
	int (*compare)(void *, void*);
	void (*free)(void*);
	// finish :)
};

AVL *newAVL(void (*d)(void *, FILE *), int (*c)(void *,void *), void (*f)(void *))
{
	AVL *newAVL;
	newAVL = (AVL *) malloc( sizeof(AVL) );
	assert(newAVL != 0);
	newAVL->display = d;
	newAVL->compare = c;
	newAVL->size = 0;
    newAVL->free = f;
	newAVL->tree = newBST(avlDisplay, avlComparator, avlSwapper, avlFree);
	return newAVL;
}

AVLVALUE *newAVLVALUE(void *v, void (*d)(void *, FILE *), int (*c)(void *, void *), void (*f)(void *))
{
	AVLVALUE *new;
	new = (AVLVALUE *) malloc( sizeof(AVLVALUE) );
	new->value = v;
	new->count = 1;
	new->balance = 0;
	new->leftHeight = 0;
	new->rightHeight = 0;
	new->height = 1;
	new->display = d;
	new->compare = c;
	new->free = f;
	return new;
}

void insertAVL(AVL *t, void *v)
{
	assert(t != 0);
  AVLVALUE *newValue = newAVLVALUE(v, t->display, t->compare, t->free);
	BSTNODE* Node = findBST(t->tree, newValue);

	if(Node == NULL) // node not exists
	{
		Node = insertBST(t->tree, newValue);
		if(Node == getBSTroot(t->tree))
			setBSTNODEparent(Node, NULL);
		insertFixup(t->tree, Node);// fixup function
	}
	else
	{
		AVLVALUE *avlfound = getBSTNODEvalue(Node); //if is in tree, increment frequency
		avlfound->count += 1;
		free(newValue);
	}
	t->size++;
	// finish :)
}

int findAVLcount(AVL *t,void *v)
{
	AVLVALUE *findValue = newAVLVALUE(v, NULL, t->compare, 0); // set the value
	BSTNODE *findNode = findBST(t->tree, findValue); // find the value in the BST
	if (findNode == NULL) // node do not exist
	{
		avlFree(findValue);
		return 0;
	}
	else // node exist
	{
		AVLVALUE *freq = getBSTNODEvalue(findNode);
		int c = 0;
		c = freq->count;
		avlFree(findValue);
		return c;
	}
	return 0;
}

void *findAVL(AVL *t,void *v)
{
	AVLVALUE *findValue = newAVLVALUE(v, NULL, t->compare, 0);
	BSTNODE *findNode = findBST(t->tree, findValue);
	avlFree(findValue);
	if (findNode == NULL) // node do not exist
		return NULL;
	else
	{
		void* data = 0;
		data = getBSTNODEvalue(findNode);
		//printf("%p \n",data);
		return data;
	}
	return NULL;
}

void *deleteAVL(AVL *g,void *value){
	AVLVALUE* newNode = newAVLVALUE(value,g->display, g->compare, g->free);
	void* result;
	assert(findBST(g->tree,newNode) != NULL);
	BSTNODE* w = findBST(g->tree,newNode);
	AVLVALUE* x = getBSTNODEvalue(w);
	if(x->count == 1)
	{
		BSTNODE* temp = swapToLeafBST(g->tree,w);
		deletionFixup(g->tree, temp);
		pruneLeafBST(g->tree,temp);
		setBSTsize(g->tree,sizeBST(g->tree)-1);
		result = getAVLVALUE(getBSTNODEvalue(temp));
		freeBSTNODE(temp,g->free);
	}
	else
	{
		x->count --;
		result = NULL;
	}
	free(newNode);
	g->size --;
	return result;
}

int sizeAVL(AVL *t)
{
	//*return the node number not the total number of the value
	return sizeBST(t->tree);
	// finish :)
}

int duplicatesAVL(AVL *t)
{
	int total = t->size;
	int numberNode = sizeBST(t->tree);
	return total-numberNode;
	// finish :)
}

void statisticsAVL(AVL *t, FILE *fp)
{
	fprintf(fp, "Duplicates: %d\n", duplicatesAVL(t));
	statisticsBST(t->tree,fp);
	// finish :)
}

void displayAVL(AVL *t, FILE *fp)
{
	displayBSTdecorated(t->tree, fp);
	// finish :)
}

void displayAVLdebug(AVL *t, FILE *fp)
{
	displayBST(t->tree, fp);
	// finish :)
}

void freeAVL(AVL *t)
{
    assert(t != 0);
    freeBST(t->tree);
    free(t);
	// finish :)
}

//------
void avlSwapper(BSTNODE*a, BSTNODE*b)
{
        AVLVALUE *ta = getBSTNODEvalue(a);
        AVLVALUE *tb = getBSTNODEvalue(b);

        /* swap the values stored in the AVL value objects */
        void *vtemp = ta->value;
        ta->value = tb->value;
        tb->value = vtemp;

        /* swap the counts stored in the AVL value objects */
        int ctemp = ta->count;
        ta->count = tb->count;
        tb->count = ctemp;

        /* note: AVL heights and balance factors are NOT swapped */
}

void avlDisplay(void*v, FILE*fp)
{
	AVLVALUE* data = v;
	data->display(data->value, fp);
	if(data->count > 1)
		fprintf(fp, "[%d]", data->count);
	if (data->balance == 1)
		fprintf(fp, "+");
	else if (data->balance == -1)
		fprintf(fp, "-");
}

int avlComparator(void*a , void*b)
{
	AVLVALUE *v1 = a;
	AVLVALUE *v2 = b;
	return v1->compare(v1->value, v2->value);
}

void avlFree(void *v)
{
    assert(v != 0);
    if (((AVLVALUE *)v)->free != NULL)
        ((AVLVALUE *)v)->free(getAVLVALUE((AVLVALUE *) v));
    free((AVLVALUE *) v);
}

void *getAVLVALUE(AVLVALUE *v)
{
    assert(v != 0);
    return v->value;
}

static void insertFixup(BST *t, BSTNODE *fixNode)
{
	while(1)
	{
		if(getBSTNODEparent(fixNode) == NULL)
			break; // if add node is root
		else if(sibling(fixNode)!= NULL && favor(getBSTNODEparent(fixNode)) == sibling(fixNode))
		{
			setBalance(getBSTNODEparent(fixNode));
			break;
		}
		else if(favor(getBSTNODEparent(fixNode)) == NULL)
		{
			setBalance(getBSTNODEparent(fixNode));
			fixNode = getBSTNODEparent(fixNode);// recursive go up and fix
		}
		else
		{
			//parent favor the fixNode need to rotate
			BSTNODE* y = favor(fixNode);// favor child of fixNode
			BSTNODE* p = getBSTNODEparent(fixNode);
			if(y != NULL && linear(y,fixNode,p) == 0)
			{
				rotate(t, y,fixNode);
				rotate(t,y,p);
				setBalance(fixNode);
				setBalance(p);
				setBalance(y);
			}
			else
			{
				rotate(t, fixNode,p);
				setBalance(p);
				setBalance(fixNode);
			}
			break;
		}
	}
}

static void deletionFixup(BST *t, BSTNODE *fixNode)
{
	AVLVALUE* n = getBSTNODEvalue(fixNode);
	n->height = 0;// set the height of x to zero since it will be deleted
    while (1)//loop forever
	{
        if (getBSTroot(t) == fixNode)
            break; //exit the loop
        else if (fixNode == favor(getBSTNODEparent(fixNode)))//parent favors n       //case 1
        {
			BSTNODE *parent = getBSTNODEparent(fixNode);
            setBalance(parent);//set the balance of parent
			fixNode = parent;
        }
        else if (favor(getBSTNODEparent(fixNode)) == NULL) //parent has no favorite           //case 2
        {
			BSTNODE *parent = getBSTNODEparent(fixNode);
            setBalance(parent); //set the balance of parent
            break;
        }
        else
        {
			BSTNODE *parent = getBSTNODEparent(fixNode);
			BSTNODE *z = sibling(fixNode);
            BSTNODE *y = favor(z); //the favorite of z
            if (y != NULL && linear(y, z, parent) == 0) //y exists and y,z,p are not linear//case 3
        		{
                rotate(t,y,z);
								rotate(t,y,parent);
                setBalance(parent);//set the balance of parent
                setBalance(z);//set the balance of z
                setBalance(y);//set the balance of y
									fixNode = y;
            }
            else                                   //case 4
            {
                rotate(t,z,parent);
                setBalance(parent);//set the balance of parent
                setBalance(z);//set the balance of z
					if (y == NULL)
						break;
					fixNode = z;
            }
        }
	}
}

BSTNODE* sibling(BSTNODE* given)
{
	// this function will return the sibling of the given node
	BSTNODE* p = getBSTNODEparent(given);
	if(getBSTNODEright(p) == given)
		return getBSTNODEleft(p);// return the sibling
	if(getBSTNODEleft(p) == given)
		return getBSTNODEright(p);
	return NULL;
}

void setBalance(BSTNODE* fixNode)
{
	AVLVALUE* x = getBSTNODEvalue(fixNode);
	BSTNODE* leftNode = getBSTNODEleft(fixNode);

	if(leftNode == NULL)
		x->leftHeight = 0;
	else
	{
		AVLVALUE* leftChild= getBSTNODEvalue(leftNode);
		x->leftHeight = leftChild->height;
	}
	//update rightHeight
	BSTNODE* rightNode = getBSTNODEright(fixNode);
	if(rightNode == NULL)
		x->rightHeight = 0;
	else
	{
		AVLVALUE* rightChild= getBSTNODEvalue(rightNode);
		x->rightHeight = rightChild->height;
	}
	//update height and balance
	if(leftNode == NULL && rightNode == NULL)
	{
		x->height = 1;
		x->balance = 0;
	}
	else if (leftNode == NULL)
	{
		AVLVALUE* rightChild= getBSTNODEvalue(rightNode);
		x->height = ((rightChild->height) + 1);
		x->balance =  (-(rightChild->height));

	}
	else if(rightNode == NULL)
	{
		AVLVALUE* leftChild= getBSTNODEvalue(leftNode);
		x->height = ((leftChild->height) + 1);
		x->balance =  ((leftChild->height));
	}
	else
	{
		AVLVALUE* rightChild= getBSTNODEvalue(rightNode);
		AVLVALUE* leftChild= getBSTNODEvalue(leftNode);
		if((leftChild->height) > (rightChild->height))
			x->height = ((leftChild->height) + 1);
		else
			x->height = ((rightChild->height) + 1);
		x->balance =  ((leftChild->height)-(rightChild->height));
	}
}

int isRoot(AVL *t, BSTNODE *compareNode)
{
	if(compareNode == getBSTroot(t->tree))
		return 1;
	else
		return 0;
}

BSTNODE *favor(BSTNODE *parent)
{
	AVLVALUE* p = getBSTNODEvalue(parent);
	if (p->balance > 0) //favor left
		return getBSTNODEleft(parent);
	else if (p->balance < 0) //favor right
		return getBSTNODEright(parent);
	return NULL; //balance
}

int linear(BSTNODE *c, BSTNODE *p, BSTNODE *gp)
{
	// gp: grandparent p:parent c:child
	int rightlinear = getBSTNODEright(gp) == p && getBSTNODEright(p) == c;//(gp.right == p && p.right == c);
	int leftlinear = getBSTNODEleft(gp) == p && getBSTNODEleft(p) == c;//(gp.left == p && p.left == c)
	return  leftlinear|| rightlinear;
}

void rotate(BST* t,BSTNODE* a, BSTNODE* b)
{//rotate a to b
	//handle grandparent
	BSTNODE* grandparent = getBSTNODEparent(b);
	if(grandparent == NULL)
	{
		setBSTNODEparent(a,NULL);
		setBSTroot(t,a);
	}
	else if(getBSTNODEleft(grandparent)== b)
	{
		setBSTNODEleft(grandparent,a);
		setBSTNODEparent(a,grandparent);
	}
	else
	{
		setBSTNODEright(grandparent,a);
		setBSTNODEparent(a,grandparent);
	}
	//rotate
	if(getBSTNODEleft(b) == a)
		rightRotate(b,a);
	else if(getBSTNODEright(b) == a)
		leftRotate(b,a);
}

void leftRotate(BSTNODE* p, BSTNODE* x){
	setBSTNODEright(p,getBSTNODEleft(x));	//p->right = x->left;
    if(getBSTNODEleft(x) !=0) 
		setBSTNODEparent(getBSTNODEleft(x),p);   //if (x->left != 0) x->left->parent = p;
	setBSTNODEleft(x,p);//x->left = p;
    setBSTNODEparent(p,x);//p->parent = x;*/
}

//right rotation
void rightRotate(BSTNODE* p, BSTNODE* x){
	setBSTNODEleft(p,getBSTNODEright(x));//p->left = x->right;
    if(getBSTNODEright(x) !=0) 
		setBSTNODEparent(getBSTNODEright(x),p);//   if (x->right != 0) x->right->parent = p;
    setBSTNODEright(x,p); //   x->right = p;
    setBSTNODEparent(p,x);//    p->parent = x;
}
