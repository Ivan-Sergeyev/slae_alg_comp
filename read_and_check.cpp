/*
 * In this programm we work with exspression such as
 * Mx=b
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// my file in program dir which helps as to work with matrix
#include "model/gauss_method.h"
#include "model/linear_algebra.h"


int read_vector(Vector *b, FILE* file) {
	for (int j = 0; j < b->get_size(); j++) {
		int errc = fscanf(file, "%lf", &(*b)(j));
		if ((errc == EOF) || (errc == 0)) {
			return 1;
		}
	}
	return 0;
}

int matrix_read(Matrix *M, FILE* file) {
	for(int i = 0; i < M->get_size(); i++) {
		for (int j = 0; j < M->get_size(); j++) {
			int errc = fscanf(file, "%lf", &(*M)(i,j));
			if ((errc == EOF) || (errc == 0)) return 1;
		}
	}
	return 0;
}

int is_answer_good(Vector answer, Matrix M, Vector result, double epsilon) {
	Vector check = M * answer;
	double sum = 0;
	for (int i = 0; i < result.get_size(); i++) {
		sum += std::abs(check(i)-result(i));
	}
	sum /= result.get_size();
	if (sum < epsilon) {
		return 1;
	}
	return 0;
}


Matrix diag_generate(double _size, double min, double max) {
	Matrix M(_size);
	srand(time(NULL));
	M(0,0) = min,
	M(1,1) = max;
	for(int i = 2; i < _size; i++) {
		M(i,i) = min + rand() * (max - min) / RAND_MAX;
	}
	return M;
}


int main(int argc, char** argv) {
	// check if there are enough arguments
	if (argc < 3) {
	   return 0;
	}

	char* name = argv[1];	// read name of file with data
	char* fout_name = argv[2]; // read name of output file

	// open file with data
	FILE* data_file;
	FILE* fout;
	if ((data_file = fopen(name,"r")) == NULL) {
		return 0;
	}

	// create output file
	if ((fout = fopen(fout_name,"a")) == NULL) {
		return 0;
	}

	// reading data
	int num;
	int errc = fscanf(data_file, "%d", &num);
	if ((errc == 0) || (errc == EOF)) return 1;

	Vector b(num);

	if (read_vector(&b, data_file)) return 1;
 /*
	double c_rep[3] = {7, 8, 9};
	Vector c(num, c_rep);

	printf("%s \n", b.repr().c_str());
	printf("%s \n", c.repr().c_str());

	c = c - c.proj(b);
	printf("%s \n", c.repr().c_str());
 */



	Matrix M(num);

	if (matrix_read(&M, data_file)) {
		return 1;
	}

	// printf("%s", M.repr().c_str() );
	double min = 1;
	double max = 40;
	M = M.ort()*diag_generate(M.get_size(), min, max);

	printf("min = %lf, max = %lf, mu = %lf\n", min, max, M.mu());

	// printf("|-norm %lf * % lf = %lf\n", M.norm(), M.inverse().norm(), M.mu());

	unsigned int start_t = clock();
	GaussMethod Gauss;
	Vector ans = Gauss.run(M, b);
	unsigned int end_t = clock();
	// printf("%s \n", ans.repr());

	printf("gauss time: %f\n", (end_t - start_t)*1.0/CLOCKS_PER_SEC);

	if (is_answer_good(ans, M, b, 0.1)) {
		printf("ANSWER CORRECT\n");
	} else {
		printf("ANSWER INCORRECT\n");
	}

	/*
	// gauss algoritm
	element* M_dub;
	if (dublicate(M, &M_dub) > 0) return 1;
	log_err("gause algoritm start",0);
	unsigned int start_time = clock();
	if (gaus(M, b, answer)) return 8;
	unsigned int end_time = clock();
	log_err("gause algoritm finish", 0);
	log_err("print answer", 0);
	// printit(*answer, fout);
	fprintf(fout,"%f \t %d\n", (end_time - start_time)*1.0/CLOCKS_PER_SEC , num );
	log_err("start check result", 0);
	element *result;
	if (mult_m_b(M_dub, answer, &result)) return 9;

	errc = is_answer_good(*result, *b_dub, 0.1);
	fprintf(stderr,"It takes %f c\n", (end_time - start_time)*1.0/CLOCKS_PER_SEC );
	log_err("Clean body cashe", 0);
	freeit(&M_dub);
	freeit(&b_dub);
	freeit(&result);
	log_err("body finished success", 0);
	if (!errc) return 7;
	return 0;

	fclose(data_file);  // close data file
	fclose(fout);	  // close output file
	*/
	return 0;
}
