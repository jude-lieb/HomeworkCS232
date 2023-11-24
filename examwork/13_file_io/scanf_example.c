#include <stdio.h>

int main() {
    const int numCols = 3;
    int sums[3] = {0,0,0};
    int lineNum, colNum;
    int n;
    
    printf("input # of lines: ");
    scanf("%d%*c", &n);
    
    for(lineNum=0; lineNum<n; lineNum++){
    	int vals[numCols];
    	scanf("%d %d %d%*c", vals, vals+1, vals+2);
    	for(colNum=0; colNum<numCols; colNum++){
    		sums[colNum] += vals[colNum];
    	}
    }
    printf("%d %d %d\n", sums[0], sums[1], sums[2]);

}