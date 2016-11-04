#ifndef GAUSS_METHOD__
#define GAUSS_METHOD__

#include <cmath>

#include "generic_method.h"


class GaussMethod { //: public GenericMethod {
public:
	//GaussMethod() : GenericMethod("Gauss Method") {}

	Vector get_answer_from_triangle(const Matrix M,const Vector b){
		int _size = b.getSize();
		Vector* result = new Vector(_size);
		double cash;
		for (int j = _size-1; j >=0; j--){
			cash = b(j);
			for (int i = j+1; i < _size; i++) cash -= M(j,i)*(*result)(i);
			(*result)(j) = cash/M(j,j);
		}
		return result;
	}

	Vector run(const Matrix &M, const Vector &b) const {
		double coeff;
		int _size = b.getSize();
		for( int j = 0; j < _size; j++) {
			find_max_and_swap(M, b, j, j){
				coeff = M(i)
			}
		}
	}
};

#endif  // GAUSS_METHOD__