#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 1000

int main() {
    int sum, isNum, isValid, i, len;
    char listInt[MAX_LEN];
    char* current = NULL;
    
    
    printf("Please input a list of integers: ");
    
    while(fgets(listInt, MAX_LEN, stdin) != NULL) {
        if (listInt[0] == '\n') {
            break;
        }
        
        isNum = 0;
        isValid = 1;
        sum = 0;
        current = listInt;
        len = strlen(listInt);
        
        for (i = 0; i < len; i++) {
            if ((listInt[i] == ' ') || (listInt[i] == '\n')) {
                if (isNum) {
                    listInt[i] = '\0';
                    sum += atoi(current);
                    isNum = 0;
                }
                
                current = listInt + i + 1;
            }
            else if ((listInt[i] >= '0') && (listInt[i] <= '9')) {
                isNum = 1;
            }
            else {
                isValid = 0;
                break;
            }
        }
        
        if (isValid) {
            printf("The SUM is %d\n", sum);
        }
        else {
            printf("Please input the valid numbers!\n");
        }
        
        printf("\nPlease input a list of integers: ");
    }
    
    printf("Existing the program ...\n");
    
    return 0;
}
