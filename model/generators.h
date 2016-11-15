#ifndef __GENERATORS__
#define __GENERATORS__

#include <stdlib.h>

#include "linear_algebra.h"


namespace generators {
	Matrix matrix_random(int size) {
		int n = size * size;
		double *values = new double[n];
		for(int i = 0; i < n; ++i) {
			values[i] = rand() + 1;
		}
		Matrix m(size, values);
		delete[] values;
		return m;
	}

	Matrix matrix_diagonal(int size, double min_ev, double max_ev){
    	Matrix M(size);
	    M(0, 0) = min_ev,
	    M(1, 1) = max_ev;
	    for(int i = 2; i < size; ++i) {
	    	M(i, i) = min_ev + rand() * (max_ev - min_ev) / RAND_MAX;
	    }
	    return M;
	}

	Matrix matrix_with_exact_mu(int size, double mu){
		Matrix M = matrix_random(size);
	    double min_ev = 1;
	    double max_ev = min_ev * mu;
		M = M.ort() * matrix_diagonal(size, min_ev, max_ev);
		return M;
	}

	Matrix matrix_with_approximate_mu(int size, double mu){
		if (size == 1) {
			double value = 1;
			return Matrix(1, &value);
		}

		int n = size * size;
		double max_diag = mu,
			   min_diag = 1;

		int max_row = rand() % size,
			min_row = rand() % size;
		min_row = (min_row + (min_row == max_row)) % size;

		double *values = new double[n];
		double diag_val, val;
		for(int i = 0; i < size; ++i) {
			diag_val = 0;
			diag_val += (double)(i == min_row) * min_diag;
			diag_val += (double)(i == max_row) * max_diag;
			if (diag_val == 0) {
				diag_val = rand();
				diag_val *= (max_diag - min_diag) / RAND_MAX;
				diag_val += min_diag;
			}
			values[i * (size + 1)] = diag_val;

			for(int j = 0; j < i; ++j) {
				values[i * size + j] = values[j * size + i];
			}
			diag_val = min_diag / (size - 1);
			for(int j = i + 1; j < size; ++j) {
				val = rand();
				val *= diag_val / 2 / RAND_MAX;
				values[i * size + j] = val;
				diag_val -= val;
			}
		}

		Matrix m(size, values);
		delete[] values;
		return m;
	}

	Vector vector_random(int size) {
		double *coords = new double[size];
		for(int i = 0; i < size; ++i) {
			coords[i] = rand();
		}
		Vector v(size, coords);
		delete[] coords;
		return v;
	}
}

#endif  // __GENERATORS__
