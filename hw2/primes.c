/* File: primes.c */
/* Author: Britton Wolfe (Edited by Jude Lieb) */
/* Date: July 16, 2009 */
/* This program outputs all the primes in the range given */
/* by the command line arguments */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, const char** argv){

    int lowerBound, upperBound;

    if(argc != 3){
        fprintf(stderr, "USAGE: %s lowerBound upperBound\n", argv[0]);
        return -1;
    }
  
    lowerBound = atoi(argv[1]);
    upperBound = atoi(argv[2]);
  
    if(lowerBound < 1 || upperBound < 1){
        fprintf(stderr, "ERROR: both the lowerBound (%d) and the upperBound (%d)"
	          " must be positive.\n", lowerBound, upperBound);
        return -2;
    }
  
    {
        /* TODO: fill in the code that outputs the prime numbers */
        /*   in the range [lowerBound,upperBound] in ascending order */
        int status;
        for(int i = lowerBound; i < upperBound + 1; ++i) {
            status = 1;
            for(int divisor = 2; divisor < i; ++divisor) {
                if(i % divisor == 0) {
                    status = 0; //number i is not prime, disables printing
                }
            }
            if(status == 1 && i != 1) { 
                printf("%d\n", i);
            }
        }
    }

    return 0;
}
