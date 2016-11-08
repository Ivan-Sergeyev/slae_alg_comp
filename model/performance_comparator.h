#ifndef __PERFORMANCE_COMPARATOR__
#define __PERFORMANCE_COMPARATOR__

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h>

#include "generic_method.h"
#include "linear_algebra.h"


using std::cout;
using std::fstream;
using std::string;
using std::to_string;


class PerformanceComparator {
private:
	clock_t _log_start_time;

	void _write_log(string msg, int level=0) {
		// TODO: use log file (fstream)
		if (level == 1) {
			cout << "| ";
		} else if (level == 2) {
			cout << "|-";
		}
		// TODO: add timestamp using _log_start_time
		cout << msg;
	}

	// TODO:
	//  * move generators to separate files
	//  * pass generator functions as arguments to run_comparison

	Matrix _generate_random_matrix(int size) {
		int n = size * size;
		double *values = new double[n];
		for(int i = 0; i < n; ++i) {
			values[i] = rand();
		}
		Matrix m(size, values);
		delete[] values;
		return m;
	}

	void _make_diagonally_dominant(Matrix &m) {
		int n = m.get_size();
		for(int i = 0; i < n; ++i) {
			double sum_row = 0;
			for(int j = 0; j < n; ++j) {
				sum_row += m(i, j);
			}
			m(i, i) = sum_row;
		}
	}

	Vector _generate_random_vector(int size) {
		double *coords = new double[size];
		for(int i = 0; i < size; ++i) {
			coords[i] = rand();
		}
		Vector v(size, coords);
		delete[] coords;
		return v;
	}
/*
	 // read vector from file
	 Vector& _read_vector(FILE* file, int size){ // check for work
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

	// //read matrix from file
	Matrix& _read_matrix(FILE* file, int size) { //check for work
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
*/
public:
	PerformanceComparator() {}

	void run_comparison(int num_methods, GenericMethod **methods,
						int num_sizes, const int *sizes,
						int num_runs, string data_filename_format) {
		Matrix A;
		Vector f;
		Vector res;

		// _log_start_time = clock();

		for(int s_idx = 0; s_idx < num_sizes; ++s_idx) {
			int size = sizes[s_idx];
			for(int r_idx = 0; r_idx < num_runs; ++r_idx) {
				A = _generate_random_matrix(size);
				_make_diagonally_dominant(A);
				f = _generate_random_vector(size);

				for (int m_idx = 0; m_idx < num_methods; ++m_idx)
				{
					string msg =
						string("- running ") + methods[m_idx]->get_name() +
						" on matrix size " + to_string(size) + "\n";
					_write_log(msg, 1);

					time_t time = -clock();
					res = methods[m_idx]->run(A, f);
					time += clock();
					double dtime = ((double) time) / CLOCKS_PER_SEC;

					string verdict;
					if (res.get_size() == size) {
						verdict = string("converged");
					} else {
						verdict = string("diverged");
					}

					// todo: use data_filename_format
					string data_filename =
						string("./data/data_") + verdict + string("_") +
						methods[m_idx]->get_name() + string(".txt");

					fstream data_file;
					data_file.open(data_filename, fstream::out | fstream::app);
					data_file << size << " " << dtime << "\n";
					data_file.close();
				}
			}
		}
	}
};

#endif // __PERFORMANCE_COMPARATOR__
