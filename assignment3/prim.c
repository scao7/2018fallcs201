/*
written by Shengting Cao 
University of Alabama 
2018 FALL 
CS201 Algorithem and Data Structure
prim algorithm for undirected graph
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "scanner.h"
#include "integer.h"
#include "string.h"
#include "edge.h"
#include "vertex.h"
#include "bst.h"
#include "queue.h"
#include "binomial.h"
#include "avl.h"


int view =0;
BINOMIAL *heap;
AVL *vTree;
AVL *eTree;
VERTEX*start;
int totalweight = 0;
DLL* MST;
int compare1(void*a, void*b);
void update(void *v, void *n);
static int processOptions(int,char **);
void Fatal(char *,...);
void update(void *v, void *n)
{
	VERTEX *p = v;
	setVERTEXowner(p, n);
}

void readDATA(FILE* dataFILE)
{
	char*v1 = readToken(dataFILE);
	char*v2 = readToken(dataFILE);
	char*w = readToken(dataFILE);
	EDGE*e1 = 0;
	EDGE*ed2 = 0;
	VERTEX*ve1 = 0;
	VERTEX*ve2 = 0;
	while(!feof(dataFILE))
	{
		if(!strcmp(w, ";"))
		{
			w = "1";	
		}
		else
		{
			readToken(dataFILE);
		}
		// insert 
			e1 = newEDGE(atoi(v1), atoi(v2), atoi(w));
			ed2 = newEDGE(atoi(v2), atoi(v1), atoi(w));
			ve1 = newVERTEX(atoi(v1));
			if(sizeBINOMIAL(heap) == 0)
			{
				start = ve1;
			}
			ve2 = newVERTEX(atoi(v2));
			if(findAVL(eTree,e1) == NULL)
			{
				insertAVL(eTree, e1);
				insertAVL(eTree, ed2);
				if(findAVLcount(vTree, ve1) == 0)
				{
					setVERTEXowner(ve1, insertBINOMIAL(heap, ve1));
				}
				if(findAVLcount(vTree, ve2) == 0)
				{
					setVERTEXowner(ve2, insertBINOMIAL(heap, ve2));
				}
				insertAVL(vTree, ve1);
				insertAVL(vTree, ve2);
				VERTEX* f1 = getBSTNODEvalue(findAVL(vTree,ve1));
				VERTEX* f2 = getBSTNODEvalue(findAVL(vTree,ve2));
				insertVERTEXneighbor(f1, f2);
				insertVERTEXneighbor(f2,f1);
				insertVERTEXweight(f1, atoi(w));
				insertVERTEXweight(f2, atoi(w));
			}
		
		v1 = readToken(dataFILE);
		v2 = readToken(dataFILE);
		w = readToken(dataFILE);
	}
}

void displaylevel(BINOMIAL* c)
{
	while(sizeBINOMIAL(c) != 0 )
	{
		VERTEX*U = extractBINOMIAL(c);
		displayVERTEX(U,stdout);
		if(compareVERTEX(U, start)){
			printf("(");
			displayVERTEX(getVERTEXpred(U),stdout);
			printf(")");
			printf("%d",getVERTEXkey(U));
		}
		if(sizeBINOMIAL(c) > 0)
		{
			printf(" ");
		}
	}
}

int compare1(void*a, void*b)
{
	VERTEX* x = a;
	VERTEX* y = b;
	return getVERTEXnumber(x)-getVERTEXnumber(y);
}

int main(int argc, char **argv)
{	processOptions(argc,argv);
	heap = newBINOMIAL(displayVERTEXdebug, compareVERTEX, update, freeVERTEX);
	vTree = newAVL(displayVERTEX, compareVERTEX, freeVERTEX);
	eTree = newAVL(displayEDGE, compareEDGE, freeEDGE);
	MST = newDLL(displayVERTEXdebug, freeVERTEX);
	
	if(view ==1){
		printf("shengting cao\n");
		return 0;
	}
	char* file = argv[1];
	FILE * dataFILE = fopen(file, "r");
	if (dataFILE == NULL)
  	{
    	fprintf(stderr,"Error opening the file\n");
    	return 0;
  	}
	readDATA(dataFILE);
	fclose(dataFILE);
		
	//delete mini spanning tree 
	setVERTEXkey(start, 0);
	decreaseKeyBINOMIAL(heap, getVERTEXowner(start), start);
	DLL* weight , *neighbor;
	VERTEX*U;
	VERTEX*P;
	while(sizeBINOMIAL(heap) > 0)
	{
		if(getVERTEXkey(peekBINOMIAL(heap)) == -1)
		{break;}
		U = extractBINOMIAL(heap);
		neighbor = getVERTEXneighbors(U);
		weight  = getVERTEXweights(U);
		if(getVERTEXpred(U))
		{
			insertVERTEXsuccessor(getVERTEXpred(U),U);
		}
		setVERTEXflag(U,1);
		firstDLL(neighbor);
		firstDLL(weight);
		int i = 0;
		while(moreDLL(neighbor))
		{
			P = currentDLL(neighbor);
			i = (int)getINTEGER(currentDLL(weight ));
			if((i<getVERTEXkey(P)||getVERTEXkey(P) == -1)&&getVERTEXflag(P) != 1) // make sure it does not form a cycyle
			{
				setVERTEXkey(P, i);
				decreaseKeyBINOMIAL(heap, getVERTEXowner(P), P);
				setVERTEXpred(P,U);
			}
			nextDLL(neighbor);
			nextDLL(weight );
		}
		totalweight += getVERTEXkey(U);
	}
	//displayMST
	QUEUE* dis = newQUEUE(displayVERTEX, freeVERTEX);
	enqueue(dis,start);
	enqueue(dis,NULL);

	VERTEX*n;
	int level = 1;
	BINOMIAL* c = newBINOMIAL(displayVERTEXdebug, compare1, 0, 0);
	printf("0: ");
	while(sizeQUEUE(dis) != 0)
	{
		n = dequeue(dis);
		if(n == NULL)
		{
			displaylevel(c);
			printf("\n");
			if(sizeQUEUE(dis) != 0)
				printf("%d: ",level);
			level++;

			if(sizeQUEUE(dis) != 0)
			{
				enqueue(dis, NULL); 
			}
		}
		else
		{
			insertBINOMIAL(c, n);
			DLL* suc = getVERTEXsuccessors(n);
			firstDLL(suc);
			while(moreDLL(suc))
			{
				enqueue(dis, currentDLL(suc));
				nextDLL(suc);
			}
		}
	}
	printf("weight: %d\n",totalweight);
}

void
Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }

/* only -oXXX  or -o XXX options */

static int
processOptions(int argc, char **argv)
    {
    int argIndex;
 
    argIndex = 1;

    while (argIndex < argc && *argv[argIndex] == '-')
        {

        if (argv[argIndex][1] == '\0') return argIndex;

        switch (argv[argIndex][1])
            {
          
          	case 'v':
				view=1;
                break;
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }

        ++argIndex;
        }

    return argIndex;
    }



















