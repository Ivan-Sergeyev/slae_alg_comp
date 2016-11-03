#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "linear_algebra.h"


int main(int num, char* argv[]){
//	assert(num>2);
//	int size = strlen(argv[1]);
	int size = 3;
	double b[3] = {1.0, 2.0, 3.0};
	double c[3] = {2, 4, 5};
	Vector x(size, b);
	Vector y(size, c);
	Vector z(size);
	//z = x;
	x.print();
	printf("\n");
	return 0;

}