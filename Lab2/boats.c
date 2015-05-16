#include <stdio.h>
#include <stdlib.h>


void merge(int *A, int *B, int *X, int *Y, int low, int mid, int up, int N) {

     int i = low, j = mid+1, k = low, q = 0;
	
     for (q = low; q <= up; q++) {
	 X[q] = A[q];
	 Y[q] = B[q];
     }
     while ((i <= mid) && (j <= up)) {
           if (X[i] < X[j]) {
              A[k] = X[i];
	      B[k++] = Y[i++];
           }
           else if (X[i] == X[j]) {
              if (Y[i] <= Y[j]) {
                  A[k] = X[i];
                  B[k++] = Y[i++];
              }
              else {
		  A[k] = X[j];
                  B[k++] = Y[j++];
              }
	   }
           else { 
              A[k] = X[j];
              B[k++] = Y[j++];
	   }
     }
     if (i > mid)
        for (q = j; q <= up; q++) {
            A[k] = X[q];
            B[k++] = Y[q];
	}
     else
        for (q = i; q <= mid; q++) {
            A[k] = X[q];
            B[k++] = Y[q];
        }
}

void mergeSort(int *A, int *B, int *X, int *Y, int left, int right, int N) {
	
     int mid = 0;
	
     if (left >= right) return;
     mid = (left + right) / 2;
     mergeSort(A, B, X, Y, left, mid, N);
     mergeSort(A, B, X, Y, mid+1, right, N);
     merge(A, B, X, Y, left, mid, right, N); 
}

int main() {
    
    int N = 0, *men = NULL, *women = NULL, *helper = NULL, *X = NULL, *Y = NULL;
    int i = 0, mid = 0, maxLength = 0, low = 0, high = 0;
    
    if (scanf("%d", &N) != 1)
       fprintf(stderr,"Wrong input format\n");

    men = (int* ) malloc(N*sizeof(int));
    women = (int* ) malloc(N*sizeof(int));
    X = (int* )malloc(N*sizeof(int));
    Y = (int* )malloc(N*sizeof(int));
    helper = (int* )malloc((N+1)*sizeof(int));

    for (i = 0; i < N; i++) {
        if (scanf("%d %d", men + i, women + i) != 2)
	   fprintf(stderr, "Wrong input format\n");
	*(X + i) = *(men+i);
        *(Y + i) = *(women+i); 
    }

    mergeSort(men, women, X, Y, 0, N-1, N);

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
