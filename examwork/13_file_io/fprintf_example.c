#include <stdio.h>

int main(int argc, char* argv[]){
	FILE *fp;
	if(argc < 2){
		fprintf(stderr, "Missing file name.\n");
		return -1;
	}
	fp = fopen(argv[1], "w");
	if(fp == NULL){
		fprintf(stderr, "Could not create file (%s).\n", argv[1]);
		return -2;
	}
	fprintf(fp, "This is a number: %d\n", 17);
	fprintf(fp, "Another number: %8.4f\n", 3.141592);
	fclose(fp);
	return 0;
}
