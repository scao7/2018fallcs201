  #include <stdio.h>
   #include <stdlib.h>
   #include "dll.h"
   #include "integer.h"
   #include "string.h"

   static void showItems(DLL *items)
       {
       printf("The items are ");
       displayDLL(items,stdout);
       printf(".\n");
       printf("The items (debugged) are ");
       displayDLLdebug(items,stdout);
       printf(".\n");
	
       }

   int main(void)
       {
		   int i,b,c,d;
			DLL *items = newDLL(displayINTEGER,freeINTEGER);
			showItems(items);
			for(  i=0; i<1583256; i=i+2){
				insertDLL(items,0,newINTEGER(i));
			}
			for(  b=1000000; b>50000; b=b-4){
				insertDLL(items,5,newINTEGER(b));
			}
			for(  c=0; c<10000; c++){
				INTEGER *z = removeDLL(items,5);
				freeINTEGER(z);
			}
			int x = sizeDLL(items)-1;
			for( d=0; d<x-5 ;d++){
				INTEGER *y = removeDLL(items,0);
				freeINTEGER(y);
			}
			
			showItems(items);
			DLL *items2 = newDLL(displaySTRING,freeSTRING);
			showItems(items2);
			for (i=0;i<10; i=i+3){
				insertDLL(items2,0,newSTRING("SO"));
			}
			
			
			showItems(items2);
       		freeDLL(items2);
       		return 0;
       }