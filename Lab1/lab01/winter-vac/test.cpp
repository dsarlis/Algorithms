#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;


int main(int argc, char *argv[]){

    int N = 0, C = 0, i = 0, x = 0, len = 0, maxlen = 0, start = 0, end = 0;
    FILE *fd = NULL;
    int sigma = 0, maxsigma = 0;
    map< int, int > exclude;

    exclude[ 0 ] = 0;
    fd = fopen(argv[1], "r");

    if (fscanf(fd, "%i %i", &N, &C) != 2){
           ;
    }
    for (i = 1; i <= N; i++){
        if (fscanf(fd, "%i", &x) != 1){
           ;
        }
        sigma -= x - C;
        if (sigma > maxsigma) {
           maxsigma = sigma;
           exclude[sigma] = i;
        }
        else {
           len = i - (*exclude.lower_bound(sigma)).second;
           if (len > maxlen) {
              maxlen = len;
              end = i;
              start = (*exclude.lower_bound(sigma)).second;
           }
        } 
    }

    printf("%i %i %i\n", start, end, maxlen);

    fclose(fd);

    return 0;
} 
