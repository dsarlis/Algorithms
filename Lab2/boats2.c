#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y) {
     int temp = 0;

     temp = *x;
     *x = *y;
     *y = temp;

}

int partition(int *a, int *b, int left, int right) {
    int pivotMan = 0, *firstMan = NULL, *lastMan = NULL;
    int pivotPos = 0, pivotWoman = 0, *firstWoman = NULL, *lastWoman = NULL;
	
    pivotPos = left + rand()%(right-left+1);
    firstMan = a + left;
    lastMan = a + right;
    firstWoman = b + left;
    lastWoman = b + right;
    pivotMan = *(a + pivotPos);
    pivotWoman = *(b + pivotPos);
    while (firstMan < lastMan) {
        while (*firstMan < pivotMan || (*firstMan == pivotMan && *firstWoman < pivotWoman)) {
            firstMan++;
            firstWoman++;
        }
        while (*lastMan > pivotMan || (*lastMan == pivotMan && *lastWoman > pivotWoman)) {
            lastMan--;
            lastWoman--;
        }
        if (firstMan < lastMan) {
           swap(firstMan, lastMan);
           swap(firstWoman, lastWoman);
	}
	if (*firstWoman == pivotWoman) {
	   lastMan--;
 	   lastWoman--;
        }
	if (*lastWoman == pivotWoman) {
	   firstMan++;
           firstWoman++;
	}
    }
    return lastMan - a;
}


void quickSort(int *a, int *b, int left, int right) {
   int q = 0;


   if (left < right) {
      q = partition(a, b, left, right);
      quickSort(a, b, left, q);
      quickSort(a, b, q + 1, right);
   }
}

int main() {
    
    int N = 0, *men = NULL, *women = NULL, *helper = NULL;
    int i = 0, mid = 0, maxLength = 0, low = 0, high = 0;

    srand(time(NULL));	
    
    if (scanf("%d", &N) != 1)
       fprintf(stderr,"Wrong input format\n");

    men = (int* ) malloc(N*sizeof(int));
    women = (int* ) malloc(N*sizeof(int));
    helper = (int* )malloc((N+1)*sizeof(int));

    for (i = 0; i < N; i++) {
        if (scanf("%d %d", men + i, women + i) != 2)
	   fprintf(stderr, "Wrong input format\n");
    }

    quickSort(men, women, 0, N-1);

    for (i = 0; i <= N; i++) {
        *(helper + i) = 0;
    }

    for (i = 0; i < N; i++) {
        low = 0;
        high = maxLength;
        mid  = low + (high-low)/2;
        while (low < high) {
              if (women[helper[mid]] <= women[i])
                 low = mid + 1;
              else
                 high = mid;
              mid = low + (high-low)/2;
        }
        if (mid == maxLength || women[i] < women[helper[mid]]) {
            helper[mid] = i;
            if (mid + 1 > maxLength)
                maxLength = mid+1;
        }
    }

    printf("%d\n", maxLength);
       
    return 0;
}
