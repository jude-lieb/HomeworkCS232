#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* filename = "matrix.txt";
	int numRows, numCols, res, row, col;
	double **matrix;
	
	FILE *fp = fopen(filename, "r");
	if(fp == NULL){
		fprintf(stderr, "Could not open file (%s).\n", filename);
		return -1;
	}
	
	res = fscanf(fp, "%d", &numRows);
	if(res != 1){
		fprintf(stderr, "File format error.\n");
		return -2;
	}
	
	res = fscanf(fp, "%d", &numCols);
	if(res != 1){
		fprintf(stderr, "File format error.\n");
		return -2;
	}
	
	matrix = malloc(sizeof(double*) * numRows);
	for(row=0; row<numRows; row++) {
	    matrix[row] = malloc(sizeof(double) * numCols);
	}
	
	for(row=0; row<numRows; row++){
		for(col=0; col<numCols; col++){
			fscanf(fp, "%lf", &(matrix[row][col]));
		}
	}
	fclose(fp);
	
	for(row=0; row<numRows; row++){
		for(col=0; col<numCols; col++){
			printf("%f\t", matrix[row][col]);
		}
		printf("\n");
	}
	
	for (row=0; row<numRows; row++)
		free(matrix[row]);
	free(matrix);
}
