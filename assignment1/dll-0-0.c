#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(744);
    DLL *p = newDLL(displayINTEGER,freeINTEGER);
    DLL *q = newDLL(displayINTEGER,freeINTEGER);
    unionDLL(p,q);
    /* do some inserts */
    int i;
    for (i = 0; i < 36; ++i)
        {
        int x = random() % (sizeDLL(p) + 1);
        int j = random() % 100;
        insertDLL(p,x,newINTEGER(j));
        }
    /* do some inserts */
    for (i = 0; i < 36; ++i)
        {
        int x = random() % (sizeDLL(q) + 1);
        int j = random() % 100;
        insertDLL(q,x,newINTEGER(j));
        }
    /* now a bunch of unions */
    printf("starting 1000000 unions\n");
    for (i = 0; i < 1000000; ++i)
        {
        unionDLL(q,p);
        unionDLL(p,q);
        }
    /* do some more inserts */
    for (i = 0; i < 36; ++i)
        {
        int x = random() % (sizeDLL(q) + 1);
        int j = random() % 100;
        insertDLL(q,x,newINTEGER(j));
        }
    if (sizeDLL(p) < 100)
        {
        printf("p: ");
        displayDLL(p,stdout);
        printf("\n");
        printf("p (debug): ");
        displayDLLdebug(p,stdout);
        printf("\n");
        printf("\n");
        }
    if (sizeDLL(q) < 100)
        {
        printf("q: ");
        displayDLL(q,stdout);
        printf("\n");
        printf("q (debug): ");
        displayDLLdebug(q,stdout);
        printf("\n");
        printf("\n");
        }
    if (sizeDLL(p) > 0)
        {
        i = random() % sizeDLL(p);
        int value = random() % 100;
        printf("size is %d\n",sizeDLL(p));
        printf("value at %d is %d\n",i,getINTEGER(getDLL(p,i)));
        printf("setting value at %d to %d\n",i,value);
        freeINTEGER(setDLL(p,i,newINTEGER(value)));
        printf("value at %d now is %d\n",i,getINTEGER(getDLL(p,i)));
        }
    if (sizeDLL(q) > 0)
        {
        i = random() % sizeDLL(q);
        int value = random() % 100;
        printf("size is %d\n",sizeDLL(q));
        printf("value at %d is %d\n",i,getINTEGER(getDLL(q,i)));
        printf("setting value at %d to %d\n",i,value);
        freeINTEGER(setDLL(q,i,newINTEGER(value)));
        printf("value at %d now is %d\n",i,getINTEGER(getDLL(q,i)));
        }
    freeDLL(p);
    freeDLL(q);
    return 0;
    }
