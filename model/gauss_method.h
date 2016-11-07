#ifndef __GAUSS_METHOD__
#define __GAUSS_METHOD__


#include <cmath>
#include <time.h>

#include "linear_algebra.h"
#include "generic_method.h"


class GaussMethod : public GenericMethod {
public:
	GaussMethod() : GenericMethod("Gauss Method") {}

	Vector run(const Matrix &A, const Vector &f) const {
		Matrix M(A);
		Vector b(f);
		double coeff;

		int _size = b.get_size();
		for( int j = 0; j < _size; j++) {
			M.find_max_and_swap(&b, j);
			for (int i = j+1; i < _size; i++){
				coeff = M(i,j)/M(j,j);
				M.sub(&b, i, j, coeff);
			}
		}
		Vector answer = M.get_answer_from_triangle(b);
		return answer;
	}
};

#endif  // __GAUSS_METHOD__
