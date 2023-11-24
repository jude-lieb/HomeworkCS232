#include <stdio.h>

int main() {
    const char *filename = "birthday.txt";
	FILE *fp = fopen(filename, "w");

    // writing
	if(fp == NULL){
		fprintf(stderr, "Could not open file (%s)\n", filename);
		return -1;
	}

	fprintf(fp, "%d/%d/%d\n", 3, 28, 1928);
	fclose(fp);

    // reading
    fp = fopen(filename, "r");
	int month, date, year, res;
	if(fp == NULL){
		fprintf(stderr, "Could not open file (%s)\n", filename);
		return -1;
	}
	res = fscanf(fp, "%d/%d/%d\n", &month, &date, &year);
	if(res != 3){
		fprintf(stderr, "File format error.\n");
		return -2;
	}
	
	printf("birthday is :%d-%d-%d\n", month, date, year);
	
	fclose(fp);
	return 0;
}
