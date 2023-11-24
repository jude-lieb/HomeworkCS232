#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "add_sub.h"
#include "mul_dis.h"

int main(int argc, char* argv[]) {
    int a, b;
    
    if (argc != 3) {
        printf("USAGE: %s int_1 int_2\n", argv[0]);
        return -1;
    }
    
    a = atoi(argv[1]);
    b = atoi(argv[2]);
        
    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, sub(a, b));
    printf("%d x %d = %d\n", a, b, mul(a, b));
    printf("%d / %d = %lf\n", a, b, dis(a, b));
    printf("sqrt(a) = %lf\n", sqrt(a));
    
    return 0;
}
