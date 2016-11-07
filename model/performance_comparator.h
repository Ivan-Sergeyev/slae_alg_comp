#ifndef __PERFORMANCE_COMPARATOR__
#define __PERFORMANCE_COMPARATOR__

#include <stdlib.h>
#include <time.h>

#include "generic_method.h"
#include "linear_algebra.h"


const int BUFFER_LEN = 200;


class PerformanceComparator {
private:
	clock_t _start_time;

	void _write_log(const char *msg, const int &level=0) {
		// TODO: use log file
		if (level == 1) {
			printf("| ");
		} else if (level == 2) {
			printf("|-");
		}
		// TODO: add timestamp
		// printf("[]: ", _start_time);
		printf("%s");
	}

	// TODO:
	//  * move generators to separate files
	//  * pass generator functions as arguments to run_comparison

	Matrix& _generate_random_matrix(const int &size) {
		int n = size * size;
		double *values = new double[n];
		for(int i = 0; i < n; ++i) {
			values[i] = rand();
		}
		Matrix *m = new Matrix(size, values);
		delete[] values;
		return *m;
	}

	Matrix& _make_diagonally_dominant(const Matrix &a) {
		int n = a.get_size();
		Matrix *m = new Matrix(a);
		for(int i = 0; i < n; ++i) {
			double sum_row = 0;
			for(int j = 0; j < n; ++j) {
				sum_row += (*m)(i, j);
			}
			(*m)(i, i) = sum_row;
		}
		return *m;
	}

	Vector& _generate_random_vector(const int &size) {
		double *coords = new double[size];
		for(int i = 0; i < size; ++i) {
			coords[i] = rand();
		}
		Vector *v = new Vector(size, coords);
		delete[] coords;
		return *v;
	}

	// read vector from file
	Vector& _read_vector(FILE* file, const int &size){ // check for work
		double *coords = new double[size];
		int errc;
    	for (int j = 0; j < size; j++) {
    		errc = fscanf(file, "%lf", &coords[j]);
    		if ((errc == EOF) || (errc == 0)) return 1;
    	}
    	Vector *v = new Vector(size, coords);
    	delete[] coords;
    	return *v;
	}

	//read matrix from file
	Matrix& _read_matrix(FILE* file, const int &size) { //check for work
		int n = size * size;
		double *values = new double[n];
		for(int i = 0; i < n; ++i) {
			errc = fscanf(file, &value[i]);
			if ((errc == EOF) || (errc == 0)) return 1;
		}
		Matrix *m = new Matrix(size, values);
		delete[] values;
		return *m;
	}

	// check that A•answer=b with accurace epsilon (max delta = epsilon)      1 - good; 0 - bad
	int _check_answer(const Vector &answer, const Matrix &M, const Vector &b, const double &epsilon){
    Vector check = M * answer;
    double max = 0;
    for (int i = 0; i < result.get_size(); i++) if (std::abs(check(i)-result(i)) > max) max = std::abs(check(i)-result(i));
    delete &check;
    if (max < epsilon) return 1;
    return 0;
}


public:
	PerformanceComparator() {}

	void run_comparison(const int &num_methods, GenericMethod **methods,
						const int &num_sizes, const int *sizes,
						const int &num_runs, const char *data_filename_format) {
		char *data_filename = new char[BUFFER_LEN];
		char *verdict = new char[20];

		Matrix A;
		Vector f;
		Vector res;

		// _start_time = clock(); // for what?

		for(int s_idx = 0; s_idx < num_sizes; ++s_idx) {
			int size = sizes[s_idx];
			for(int r_idx = 0; r_idx < num_runs; ++r_idx) {
				A = _generate_random_matrix(size);
				A = _make_diagonally_dominant(A);
				f = _generate_random_vector(size);

				for (int m_idx = 0; m_idx < num_methods; ++m_idx)
				{
					time_t time = -clock();
					res = methods[m_idx]->run(A, f);
					time += clock();
					double dtime = ((double) time) / CLOCKS_PER_SEC;

					verdict[0] = 0;
					if (res.get_size() == size) {
						sprintf(verdict, "converged");
					} else {
						sprintf(verdict, "diverged");
					}

					data_filename[0] = 0;
					sprintf(data_filename, data_filename_format,
							verdict, methods[m_idx]->get_name());

					FILE *data_file = fopen(data_filename, "a");
					fprintf(data_file, "%d %lf\n", size, dtime);
					fclose(data_file);
				}
			}
		}
		delete[] data_filename;
		delete[] verdict;
	}
};

#endif // __PERFORMANCE_COMPARATOR__
