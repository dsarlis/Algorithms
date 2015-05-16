#include <stdio.h>
#include <stdlib.h>


void mulArray(long long int *A, long long int *B, long long int *C, int dim) {

	int i = 0, j = 0, k = 0;
	long long int temp[dim][dim];

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++) {
			temp[i][j] = 0;
			for (k = 0; k < dim; k++) {
				temp[i][j] = temp[i][j] + ((*(A + i*dim + k)) * (*(B + k*dim + j)));
				temp[i][j] = temp[i][j] % (100000000 + 7);
			}
		}

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			*(C + i*dim + j) = temp[i][j];
}

long long int *mypow(long long int *A, long long int *B, int pow, int dim) {
	
	long long int *temp = NULL;
	
	if (pow == 1) {
		B = A;
	}
	else {
	        temp = mypow(A, B, pow/2, dim);
		if (pow % 2 == 0) {
			mulArray(temp, temp, B, dim);
		}
		else {
			mulArray(temp, temp, B, dim);
			mulArray(A, B, B, dim);
		}
	}
	
	return B;
}

int main () {
	long long int *Graph = NULL, *help = NULL;
	int i = 0, N = 0, k = 0, M = 0, s = 0, t = 0;
	int j = 0, first = 0, second = 0;	

	if (scanf("%d %d %d %d %d", &k, &N, &M, &s, &t) != 5) {
		fprintf(stderr, "Wrong input format\n");
	}	

	s--;
	t--;

        Graph = (long long int *) malloc(N*N*sizeof(long long int));
	help = (long long int *) malloc(N*N*sizeof(long long int));

        for(i = 0; i < N; i++) 
		for (j = 0; j < N; j++)
                	*(Graph + i*N + j) = 0;

        for(i = 0; i < M; i++) {
        	if  (scanf("%d %d", &first, &second) != 2) {
			printf("Wrong file format2\n");
	      	}
		first--;
		second--;
		*(Graph + first*N + second) = 1;
        }

	Graph = mypow(Graph, help, k-1, N);

	printf("%Ld\n", *(Graph + s*N + t));
	
	return 0;
}

