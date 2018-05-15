/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithm and Data Structure
heapsort algortithm 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "real.h"
#include "integer.h"
#include "string.h"
#include "scanner.h"
#include "heap.h"
#include "bst.h"

/* options */
int view = 0;    /* option -s      */
int sortInteger = 0;
int sortReal=0;
int sortString=0;
int sortInc=0;
int sortDec=0;
//char* Name = 0;     /* option -N YYYY */

static int processOptions(int,char **);
void Fatal(char *,...);
static char* readItem(FILE* fp){
	if(stringPending(fp))
		return readString(fp);
	else
		return readToken(fp);
}

int
main(int argc,char **argv)
    {


    if (argc == 1) Fatal("%d arguments!\n",argc-1);

   	processOptions(argc,argv);
	
	if(view == 0 && sortInteger == 0 && sortReal == 0 &&sortString==0&&sortInc==0&&sortDec==0){
		sortInteger=1;
	}
  	if(view==1){
		printf("////////////////////////////////////////////////////////////////\n");
		printf("/////////Written by Shengting Cao\n");
		printf("/////////The toal sorting algrithom should performs theta(nlogn) time.\n");
		printf("/////////When add value to the loop, it takes logn time to travel to the last node\n");
		printf("/////////then it take constant time to add node to it\n");
		printf("/////////For the ordering, it goes backward of every node and do heapfiy(constant)\n");
		printf("/////////For the extracting, it swap the root with last node, and call build function(logn)\n");
		printf("////////////////////////////////////////////////////////////////\n");
	}

	if(sortInteger == 1){
		HEAP* h = NULL;
		if(sortDec == 1)
			h = newHEAP(displayINTEGER, rcompareINTEGER, freeINTEGER);
		else
			h = newHEAP(displayINTEGER, compareINTEGER, freeINTEGER);

		FILE* fp= fopen(argv[argc-1],"r");
		int num = readInt(fp);
		while(!feof(fp)){
			insertHEAP(h,newINTEGER(num));
			num = readInt(fp);

		}
		buildHEAP(h);

		while(sizeHEAP(h) > 0){
			INTEGER *r = extractHEAP(h);
    		printf("%d",getINTEGER(r));
			freeINTEGER(r);
			if(sizeHEAP(h) >=1)
				printf(" ");
		}
	
		printf("\n");
		
	freeHEAP(h);
	}

	if(sortReal == 1){
		HEAP* h = NULL;
		if(sortDec ==1)
			h = newHEAP(displayREAL, rcompareREAL, freeREAL);
		else
			h = newHEAP(displayREAL, compareREAL, freeREAL);
		
		FILE* fp= fopen(argv[argc-1],"r");
		double num = readReal(fp);
		while(!feof(fp)){
			insertHEAP(h,newREAL(num));
			num = readReal(fp);
		}
		buildHEAP(h);
		
		while(sizeHEAP(h) > 0){
			REAL *r = extractHEAP(h);
    		printf("%lf",getREAL(r));
			freeREAL(r);
			if(sizeHEAP(h) >=1)
				printf(" ");
		}
		printf("\n");
	
		freeHEAP(h);

	}
	if(sortString==1){
		HEAP* h = NULL;
		if(sortDec ==1)
			 h = newHEAP(displaySTRING, rcompareSTRING, freeSTRING);
		else
			 h = newHEAP(displaySTRING, compareSTRING, freeSTRING);

		FILE* fp= fopen(argv[argc-1],"r");
		char* num = readItem(fp);
		while(!feof(fp)){
			insertHEAP(h,newSTRING(num));
			num = readItem(fp);
		}
		buildHEAP(h);
		
		while(sizeHEAP(h) > 0){
			STRING *r = extractHEAP(h);
    		printf("%s",getSTRING(r));
			freeSTRING(r);
			if(sizeHEAP(h)>=1)
				printf(" ");
		}
		printf("\n");

		freeHEAP(h);
	}


    return 0;
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
            case 'i':
               //	printf("sort integer\n");
				sortInteger = 1;
                break;
            case 'r':
                //printf("sort real\n");
				sortReal =1;
                break;
			case 's':
			//printf("sort string\n");
				sortString =1;
				break;
			case 'I':
				//printf("increase order\n");
				sortInc = 1;
				break;
			case 'D':
				//printf("decrease order\n");
				sortDec =1;
				break;
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }

        ++argIndex;
        }

    return argIndex;
    }
