/*
written by Shengting Cao 
University of Alabama 
2018 SPRING 
CS201 Algorithm and Data Structure
algorithm compare with the gree search tree with AVL tree
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "string.h"
#include "scanner.h"
#include "bst.h"
#include "gst.h"
#include "avl.h"
GST* g;
AVL* a;
/* options */
int view = 0;    /* option -s      */
int gtree=0;
int atree =0;
//char* Name = 0;     /* option -N YYYY */

void clean(char* input){
	if (input == NULL)
		return;
	int len = strlen(input);
	for(int i = len-1;i>=0;i--){
		
		if(isalpha(input[i])){
			if(i != len-1)
			input[i+1] = 0;
			break;
		}
	}
	
    char *old = input;
	char *new = input;
	int flag =0;
	
	
    while (*old)
    {	
		if ((ispunct(*old)||isdigit(*old)||isspace(*old))&&flag !=1)
        {	
            while((ispunct(*old)||isdigit(*old)||isspace(*old)))//delete the space in front 
                old++;
        }
		if(isalpha(*old)||isspace(*old)){
			while(isspace(*old)&&isspace(*(old +1))){//clear double space
				old++;
			}
			*new++ = tolower((unsigned char)*old);
			old++;
			flag =1;
		}
		else if(*old !='\0'){
			old++;
			flag =1;
		}
    }
    *new = 0;
  //  input = new;
}
char *readItem(FILE *fp){
	char *input = NULL;
    if (stringPending(fp))
      input = readString(fp);
    else
      input = readToken(fp);
    clean(input);
	return input;
}
void insertInput(char* data){
	if(gtree == 1)
	{
		insertGST(g,newSTRING(data));
	}
	else
		insertAVL(a,newSTRING(data));

}
void frequencyInput(char* data){
	if (gtree == 1)
    {
		int fre = findGSTcount(g, newSTRING(data));
		fprintf(stdout,"Frequency of %s: %d\n",data,fre);
    }
    else
    {
		int fre = findAVLcount(a, newSTRING(data));
		fprintf(stdout,"Frequency of %s: %d\n",data,fre);
    }

}
static int processOptions(int,char **);
void Fatal(char *,...);
void deleteInput(char* input)
{
  if (gtree == 1)
  {
    if (findGST(g,newSTRING(input)) == NULL)
      fprintf(stdout,"Value %s not found.\n",input);
    else{
      deleteGST(g,newSTRING(input));
	}
  }
  else
  {
    if (findAVL(a,newSTRING(input)) == NULL)
      fprintf(stdout,"Value %s not found.\n",input);
    else
      deleteAVL(a,newSTRING(input));
  }
}

int
main(int argc,char **argv)
    {
	processOptions(argc,argv);
	
	char * data = NULL; // data
	char * command = NULL; // command
	if(view ==1)
	{
		fprintf(stdout," Wrriten by Shengting Cao\n");
		return 0;
	}
	if (argc == 3)
	{
		//default avl
		data = argv[1];
		command = argv[2];
	}
	else
	{
		data = argv[2];
		command = argv[3];
	}
	if (argc == 1) Fatal("%d arguments!\n",argc-1);
   	
	FILE * dataFile = fopen(data, "r");
	FILE * commandFile = fopen(command, "r");
	if (dataFile == NULL || commandFile == NULL)
	{
    fprintf(stderr,"Error opening the file\n");
    return 0;
	}
  //set up tree
  if (gtree ==1)
    g = newGST(displaySTRING, compareSTRING, freeSTRING);
  else
    a = newAVL(displaySTRING, compareSTRING, freeSTRING);
  //read and process the command
  char *input = readItem(dataFile); 
  while(!feof(dataFile))
  {
	if(strcmp(input,"")!= 0)
	{
		insertInput(input);
	}
	input = readItem(dataFile);
  }
  char *inst = readItem(commandFile);
  while(!feof(commandFile))
  {
      switch (*inst)
      {
          case 'i':
            input = readItem(commandFile);
			if(strcmp(input, "")!=0)
				insertInput(input);
			break;
          case 'd':
            input = readItem(commandFile);
			if(strcmp(input, "")!=0)
            	deleteInput(input);
            break;
          case 'f':
			input = readItem(commandFile);
			frequencyInput(input);
            break;
          case 's':
              if (gtree == 1)
                displayGST(g,stdout);
              else
                displayAVL(a,stdout);
              break;
          case 'r':
            if (gtree == 1)
                statisticsGST(g,stdout);
            else
                statisticsAVL(a,stdout);
              break;
          default:
              fprintf(stderr,"Invalid command\n");
              return 0;
      }
	  inst = readItem(commandFile); //read
  }
  
  
	if(gtree==1)
      freeGST(g);
	else
      freeAVL(a);
    fclose(commandFile);
    fclose(dataFile);
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
            case 'g':
               //	printf("sort integer\n");
				gtree = 1;
                break;
            case 'r':
                //printf("sort real\n");
				atree =1;
                break;
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }

        ++argIndex;
        }

    return argIndex;
    }
