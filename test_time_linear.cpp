#include <stdio.h>
#include "model/linear_algebra.h"
#include "c_lib/mymatrix.h"
#include <time.h>

int main(int argn, char* argv[]){ 
	int num = 3;
	unsigned int start_t;
	unsigned int end_t;

	element* A;
	init('m',&A, num);
	for(int i = 0; i < A->len; i++) {
		for (int j = 0; j < A->len; j++) {
			(A->M[i]).b[j] = i+j+1;
			}
		}
	printit(*A, stdout);

	double ma[] = {1,2,2,4, 5, 6, 7, 8, 9};
	Matrix M(3, ma);
	printf("%s", M.repr());
	double x;
	
	int N = 1000000;

	start_t = clock();
	for(int i = 0; i < N; i++) x = A->M[1].b[1];
	end_t = clock();
	printf("struct time: %f\n", (end_t - start_t)*1.0/CLOCKS_PER_SEC);
    

	start_t = clock();
	for(int i = 0; i < N; i++) x = M(1,1);
	end_t = clock();
	printf("class time: %f\n", (end_t - start_t)*1.0/CLOCKS_PER_SEC);

	return 0;
}

