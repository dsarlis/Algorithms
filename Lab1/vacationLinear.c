#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    long int  i = 0, N = 0, C = 0, flag = 0, element = 0, diff = 0, start = 0, end = 0, max_diff = 0, min = 0, minPos = 0, checkSum = 0;
    long int sum = 0, maxLen = 0;
    long int *sums = NULL, *ptr = NULL;
    long int *indeces = NULL, *ptr2 = NULL;
    FILE *fd = NULL;
    
    fd = fopen(argv[1],"r");

    if (fscanf(fd,"%ld %ld",&N, &C) != 2)
       fprintf(stderr,"Wrong input format\n");
    
    sums = (long int* )malloc(N*sizeof(long int));
    indeces = (long int* )malloc(N*sizeof(long int));

    i = 0;
    for (ptr = sums; ptr < sums+N; ptr++) {
        if (fscanf(fd,"%ld", &element) != 1)
           fprintf(stderr,"Wrong input format\n");
        sum -= element - C;
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
    	i = 0;
    	for (i = 0; i < N; i++) {
           if (*(sums+i) > min) {
              min = *(sums + i);
              minPos = i;
	   }
           else {
              diff = i - minPos;
              if (diff > max_diff) {
                 checkSum = *(sums+i);
                 end = i; 
                 max_diff = diff;
              }
           }    
        }  
        i = 0;
        ptr = sums;
        while (*ptr < checkSum) {
            i++; 
            ptr++;
        }
        printf("%ld\n", end-i);  
    }
    fclose(fd);
    
    return 0;
}
