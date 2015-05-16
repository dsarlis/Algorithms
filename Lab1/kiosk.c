#include <stdio.h>
#include <stdlib.h>

struct kiosk{
    double pos;
    int requests;   
};

typedef struct kiosk kioskType;


double absolute(double x){
    if (x > 0.0)
       return x;
    else
       return -x;
}

int check(kioskType *kiosks, double shift, int coordinates, int distance){
    kioskType *ptr = kiosks; 
    double curPos = ptr->pos - shift, temp = 0.0;

    while (ptr < kiosks + coordinates) {
         if (curPos > ptr->pos) {
            if (absolute(curPos - ptr->pos) > shift ) {
               temp = ptr->pos + shift;
               if (temp - (curPos - distance) > shift)
                  curPos = temp;
               else
                  return 0;
	    }
         }
         else {
            if (absolute(curPos - ptr->pos) > shift )
               curPos = ptr->pos - shift; 
	 }
         curPos = curPos + ptr->requests*distance;       
         if (absolute(curPos - ptr->pos - distance) - shift > 0.001)
            return 0;
         ptr++;
    }
    return 1;
}


int main(int argc, char *argv[]) {
    int N = 0, allRequests = 0; 
    long int max = 0;
    //FILE *fd = NULL;
    double K = 0.0, low = 0.0, high = 100000000000.0, mid = 0.0;
    kioskType *kiosks = NULL, *ptr = NULL;
    
    //fd = fopen(argv[1],"r");
    if (scanf("%d %lf", &N, &K)!= 2) {
       fprintf(stderr,"Wrong input format\n");
       return 1;
    }

    kiosks = (kioskType *)malloc(N*sizeof(kioskType));
    
    for (ptr = kiosks; ptr < kiosks + N; ptr++) {
        if (scanf("%lf %d", &ptr->pos, &ptr->requests) != 2) {
           fprintf(stderr, "Wrong input format\n");
           return 1;
        }
        allRequests += ptr->requests;
        if (ptr->requests > max)
           max = ptr->requests;
    }
    //fclose(fd);
   
    low = ((max - 1) * K) / 2.0;
    high = allRequests * K;

    while (absolute(low-high) > 0.001) {
        mid = (low + high)/2.0;
        if (check(kiosks, mid, N, K) == 1)
           high = mid;
        else 
           low = mid;             
    }

    printf("%.2lf\n", mid);

    return 0;
}
