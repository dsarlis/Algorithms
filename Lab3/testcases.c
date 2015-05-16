#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	int size;
};

typedef struct Node NodeStruct;

void swapLong(unsigned long long int *x, unsigned long long int *y) {
     unsigned long long int temp = 0;

     temp = *x;
     *x = *y;
     *y = temp;
}


unsigned long long int partition(unsigned long long int *a, unsigned long long int *b, unsigned long long int *c, unsigned long long int left, unsigned long long int right) {
    unsigned long long int pivot = 0, *firstB = NULL, *lastB = NULL;
    unsigned long long int *firstA = NULL, *lastA = NULL;
    unsigned long long int pivotPos = 0, *firstC = NULL, *lastC = NULL;

    pivotPos = left + rand()*(right - left + 1)/RAND_MAX;
    firstA = a + left;
    lastA = a + right;
    firstB = b + left;
    lastB = b + right;
    firstC = c + left;
    lastC = c + right;
    pivot = *(a + pivotPos);
    while (1 > 0) {
        while (*firstA < pivot /*|| (*firstSum == pivotSum && *firstIndex < pivotIndex)*/) {
            firstA++;
            firstB++;
	    firstC++;
        }
        while (*lastA > pivot /*|| (*lastSum == pivotSum && *lastIndex > pivotIndex)*/) {
            lastA--;
            lastB--;
	    lastC--;
        }
        if (firstA < lastA) {
           swapLong(firstA, lastA);
           swapLong(firstB, lastB);
	   swapLong(firstC, lastC);
        }
        else
           return (lastA - a);
    }
}


void quickSort(unsigned long long int *a, unsigned long long int *b, unsigned long long int *c, unsigned long long int left, unsigned long long int right) {
   unsigned long long int q = 0;

   if (left < right){
      q = partition(a, b, c, left, right);
      quickSort(a, b, c, left, q);
      quickSort(a, b, c, q + 1, right);
   }
}

void merge(unsigned long long int *A, int *B, int *C, unsigned long long int *X, int *Y, int *Z, int low, int mid, int up, int N) {

     int i = low, j = mid+1, k = low, q = 0;

     for (q = low; q <= up; q++) {
         X[q] = A[q];
         Y[q] = B[q];
	 Z[q] = C[q];
     }
     while ((i <= mid) && (j <= up)) {
           if (X[i] < X[j]) {
              A[k] = X[i];
              B[k] = Y[i];
	      C[k++] = Z[i++];
           }
           else {
              A[k] = X[j];
              B[k] = Y[j];
	      C[k++] = Z[j++];
           }
     }
     if (i > mid)
        for (q = j; q <= up; q++) {
            A[k] = X[q];
            B[k] = Y[q];
	    C[k++] = Z[q];
        }
     else
        for (q = i; q <= mid; q++) {
            A[k] = X[q];
            B[k] = Y[q];
	    C[k++] = Z[q];
        }
}

void mergeSort(unsigned long long int *A, int *B, int *C, unsigned long long int *X, int *Y, int *Z, int left, int right, int N) {

     int mid = 0;

     if (left >= right) return;
     mid = (left + right) / 2;
     mergeSort(A, B, C, X, Y, Z, left, mid, N);
     mergeSort(A, B, C, X, Y, Z, mid+1, right, N);
     merge(A, B, C, X, Y, Z, left, mid, right, N);
}


int findTreePathCompression(int x, NodeStruct *A) {

	if (x != (A+x)->value)
	   	(A+x)->value = findTreePathCompression((A+x)->value, A);
	return((A+x)->value);
}



void unionTree(int x, int y, NodeStruct *A) {
	if (x == y) return;

	(A+y)->value = x;
	(A+x)->size += (A+y)->size;
}


int main() {

	int N = 0, i = 0, *a = NULL, *b = NULL, *X = NULL, *Y = NULL, v1 = 0, v2 = 0, p1 = 0, p2 = 0;
	unsigned long long int *w = NULL, *Z = NULL, result = 0;
	NodeStruct *Parents = NULL;
	

	if (scanf("%d", &N) != 1)
		fprintf(stderr, "Wrong input format\n");

	Parents = (NodeStruct *)malloc(N*sizeof(NodeStruct));
	a = (int *)malloc((N-1)*sizeof(int));
	X = (int *)malloc((N-1)*sizeof(int));
	b = (int *)malloc((N-1)*sizeof(int));
	Y = (int *)malloc((N-1)*sizeof(int));
	w = (unsigned long long int *)malloc((N-1)*sizeof(unsigned long long int));
	Z = (unsigned long long int *)malloc((N-1)*sizeof(unsigned long long int));

	for (i = 0; i < N; i++) {
		(Parents+i)->value = i;
		(Parents+i)->size = 1;
	}

	for (i = 0; i < N - 1; i++) {
		if (scanf("%d %d %Ld", &a[i], &b[i], &w[i]) != 3)
			fprintf(stderr, "Wrong input format\n");
		a[i] = a[i] - 1;
		b[i] = b[i] - 1;
	}

	mergeSort(w, a, b, Z, X, Y, 0, N-2, N-1);
	
	/*quickSort(w, a, b, 0, N-2);*/


	for (i = 0; i < N - 1; i++) {
		v1 = a[i];
		v2 = b[i];
		p1 = findTreePathCompression(v1, Parents);
		p2 = findTreePathCompression(v2, Parents);
		result = result + w[i] + ((unsigned long long int)((Parents + p1)->size) * (unsigned long long int)((Parents + p2)->size) - 1) * (w[i] + 1);
		unionTree(p1, p2, Parents);	
	}

	printf("%llu\n", result);	

	return 0;
}
