#ifndef __GAUSS_METHOD__
#define __GAUSS_METHOD__


#include <cmath>
#include <time.h>

#include "linear_algebra.h"
#include "generic_method.h"


class GaussMethod : public GenericMethod {
private:
    unsigned int start_time;
    unsigned int end_time;

	void find_max_and_swap(Matrix* M, Vector* b, int j) const {
		int n = M->get_size();
		int max_index = j;
		for (int i = j+1; i < n; i++) if ((*M)(i,j) > (*M)(max_index, j)) max_index = i;
		if (max_index != j){
			double temp;
			for (int i = j; i < n; i++) {
				temp = (*M)(j,i); (*M)(j,i) = (*M)(max_index, i); (*M)(max_index,i) = temp;
			}
			temp = (*b)(j); (*b)(j) = (*b)(max_index); (*b)(max_index) = temp;
		}

	}
	void sub(Matrix* M, Vector* b, int k, int l, double coeff) const{
		int n = M->get_size();
		for (int i = 0; i < n; i++) (*M)(k,i) -= (*M)(l,i)*coeff;
		(*b)(k) -= (*b)(l)*coeff;
	}
public:
//	GaussMethod() : GenericMethod("Gauss Method") {}

	Vector* get_answer_from_triangle(Matrix M, Vector b) {
		int _size = b.get_size();
		Vector* result = new Vector(_size);
		double cash;
		for (int j = _size-1; j >=0; j--){
			cash = b(j);
			for (int i = j+1; i < _size; i++) cash -= M(j,i)*(*result)(i);
			(*result)(j) = cash/M(j,j);
		}

    	end_time = clock();
    	printf("gauss = %f\n", (end_time - start_time)*1.0/CLOCKS_PER_SEC);
		return result;
	}

	Vector* run(Matrix A, Vector f) {
		Matrix *M = new Matrix(A);
		Vector *b = new Vector(f);
		double coeff;

    	start_time = clock();
		int _size = b->get_size();
		for( int j = 0; j < _size; j++) {
			find_max_and_swap(M, b, j);
			for (int i = j+1; i < _size; i++){
				coeff = (*M)(i,j)/(*M)(j,j);
				sub(M, b, i, j, coeff);
			}
		}
		return get_answer_from_triangle(*M, *b);
	}
};

#endif  // __GAUSS_METHOD__
