#include <stdio.h>
#define MAX_NAME_LEN 100

int main() {
    const char *filename = "scores.txt";
    int score, sum = 0, res, count = 0;
    char name[MAX_NAME_LEN];
    FILE * fp;
    
    fp = fopen(filename, "r");
	if(fp == NULL){
		fprintf(stderr, "Could not open file (%s)\n", filename);
		return -1;
	}
	
	res = fscanf(fp, "%s %d\n", name, &score);
	while (res == 2) {
	    sum += score;
	    count++;
	    res = fscanf(fp, "%s %d\n", name, &score);
	}
	
	printf ("The average is %lf\n", 1.0 * sum / count);
	
	fclose(fp);
}