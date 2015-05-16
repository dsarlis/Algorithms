#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(long int *x, long int *y) {
     long int temp = 0;
     
     temp = *x;
     *x = *y;
     *y = temp;

}

long int partition(long int *a, long int *b, long int left,long int right) {
    long int pivotSum = 0, *firstSum = NULL, *lastSum = NULL;
    long int pivotPos = 0, pivotIndex = 0, *firstIndex = NULL, *lastIndex = NULL; 

    pivotPos = left + rand()*(right - left + 1)/RAND_MAX;
    firstSum = a + left;
    lastSum = a + right;
    firstIndex = b + left;
    lastIndex = b + right;
    pivotSum = *(a + pivotPos);
    pivotIndex = *(b + pivotPos);
    while (1 > 0) {
        while (*firstSum < pivotSum || (*firstSum == pivotSum && *firstIndex < pivotIndex)) {
            firstSum++;
            firstIndex++;
	}
        while (*lastSum > pivotSum || (*lastSum == pivotSum && *lastIndex > pivotIndex)) {
            lastSum--;
            lastIndex--;
        }
        if (firstSum < lastSum) {
           swap(firstSum, lastSum);
           swap(firstIndex, lastIndex);
        }
        else
           return (lastSum - a);
    }
}


void quickSort(long int *a, long int *b, long int left, long int right) {
   long int q = 0;
   
   if (left < right){
      q = partition(a, b, left, right);
      quickSort(a, b, left, q);
      quickSort(a, b, q + 1, right);
   }
}


int main(int argc, char *argv[]) {

    long int  i = 0, N = 0, C = 0, flag = 0, element = 0, diff = 0, start = 0, end = 0, max_diff = 0, min = 0;
    long int sum = 0;
    long int *sums = NULL, *ptr = NULL;
    long int *indeces = NULL, *ptr2 = NULL;
    //FILE *fd = NULL;
    
    srand(time(NULL));
    //fd = fopen(argv[1],"r");

    if (scanf("%ld %ld",&N, &C) != 2)
       fprintf(stderr,"Wrong input format\n");
    
    sums = (long int* )malloc(N*sizeof(long int));
    indeces = (long int* )malloc(N*sizeof(long int));

    i = 0;
    for (ptr = sums; ptr < sums+N; ptr++) {
        if (scanf("%ld", &element) != 1)
           fprintf(stderr,"Wrong input format\n");
        sum += element - C;
        *ptr = sum;
        *(indeces + i) = i;
        if (C <= element)
           flag = 1;
        i++;
    }
    
    if (flag == 0){
       printf("%d\n", 0);
    } 
    else {
       
       quickSort(sums, indeces, 0, N-1);
       i = 0;
       min = *indeces;
       for (ptr2 = indeces; ptr2 < indeces + N; ptr2++){
           if (*ptr2 <  min) {
              min = *ptr2;
           }
           diff = *ptr2 - min;
           if (diff > max_diff){
              start = min;
              end = *ptr2;
              sum = *(sums + i);
              max_diff = diff;
           }
           i++;
       }       

       if (start == 0) {
          sum += (end - start + i)*C;
          C = (end - start + 1)*C;
          if (sum >= C)
             printf("%ld\n", end - start + 1);
          else
             printf("%ld\n", end - start);
       }
       else
           printf("%ld\n", end - start);
    }
    //fclose(fd);
    return 0;
}
