#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv){
	int c, goLower;
	if(argc < 2){
		fprintf(stderr, "USAGE: %s [lower|upper]\n", argv[0]);
		return -1;
	}
	goLower = !strcmp("lower", argv[1]);
	c = getchar();
	while( c != EOF ){
		if (goLower)
			putchar(tolower(c));
		else
			putchar(toupper(c));
	
		c = getchar();
	}
	return 0;
}
