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

	Matrix matrix_with_mu(int size, double mu){
		Matrix M = matrix_random(size);
	    double min_ev = 1;
	    double max_ev = min_ev * mu;
		M = M.ort() * matrix_diagonal(size, min_ev, max_ev);
		return M;
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
