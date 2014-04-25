#include <stdio.h>

#ifndef lint
static char SccsId[] = "@(#) b_sort.c (Yale) version 1.2 2/21/91" ;
#endif

bubble_sort(array,n)
int array[],n;
{
int i,j,temp;
 for (i=1;i<=n;i++)
 {
   for (j=1;j<=n-i;j++)
   {
    if (array[j]>array[j+1])
    {
    temp=array[j+1];
    array[j+1]=array[j];
    array[j]=temp;
    }
  }
  }
/* for (i=1;i<=n;i++)
  printf("%d  ",array[i]);*/
  }

int clean_red(array,n)
int array[],n;
{
int i,j,temp;
temp = n;
i=1;
j = i+1;
label: while (array[i] == array[j]) {
 j++;
 n--;
}
i++;
array[i] = array[j];
j++;
if (j <= temp) goto label;
return (n);
}

