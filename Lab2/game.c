#include <stdio.h>
#include <stdlib.h>


int main() {

	int N = 0, *p = NULL, i = 0 , *sums = NULL, current = 0, range = 0;
	int *benefit = NULL, j = 0, k = 0, cur1 = 0, cur2 = 0, test = 0;

	if (scanf("%d\n", &N) != 1)
		fprintf(stderr,"Wrong input format\n");

	p = (int* )malloc(N*sizeof(int));
        sums = (int* )malloc(N*sizeof(int));
	benefit = (int*)malloc(N*N*sizeof(int));

	for (i = 0; i < N; i++) {
	    if (scanf("%d\n", p + i) != 1)
		fprintf(stderr,"Wrong input format\n");
	    current += *(p+i);
            *(sums + i) = current;
	}
	
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			*(benefit + i*N + j) = 0;	

	for (range = 2; range < N + 1; range++) {
		for (i = 0; i < N - range + 1; i++) {
			j = i + range - 1;
			for (k = i; k < j; k++) {
				if (i == 0) 
				   cur1 = *(benefit + i*N + k) + sums[k];
				else 
				   cur1 = *(benefit + i*N + k) + sums[k] - sums[i - 1];
				cur2 = *(benefit + (k + 1)*N + j) + sums[j] - sums[k];
				if (cur1 < cur2)
				   test = cur1;
				else test = cur2;
				if (test > *(benefit + i*N + j)) {
				   *(benefit + i*N + j) = test;
				}
			}
		}
	}

	printf("%d\n", *(benefit + N - 1));

	return 0;
}
