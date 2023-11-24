#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
double dis(int a, int b);

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

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

double dis(int a, int b) {
    return a * 1.0 / b;
}
