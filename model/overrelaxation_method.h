#ifndef __OVERRELAXATION_METHOD__
#define __OVERRELAXATION_METHOD__

#include <cmath>

#include "generic_method.h"


class OverrelaxationMethod : public GenericMethod {
private:
	double _tau;  // relaxation parameter

public:
	OverrelaxationMethod(const double &tau) {
		assert(tau > 0);
		assert(tau < 2);

		if (tau == 1.0) {
			set_name("Seidel Method");
		} else {
			char *name = new char[52];
			*name = 0;
			sprintf(name, "Overrelaxation Method with tau=%lf", tau);
			set_name(name);
		}
	}

	Vector& step(const int n, const Matrix &A,
				 const Vector &f, const Vector &u) const {
		Vector *u_next = new Vector(n);
		for (int i = 0; i < n; ++i) {
			(*u_next)(i) = f(i);
			for (int j = 0; j < i; ++j) {
				(*u_next)(i) -= A(i, j) * (*u_next)(j);
			}
			for (int j = i + 1; j < n; ++j) {
				(*u_next)(i) -= A(i, j) * u(j);
			}
			(*u_next)(i) *= _tau / A(i, i);
			(*u_next)(i) += (1 - _tau) * u(i);
		}
		return *u_next;
	}

	Vector run(const int n, const Matrix &A, const Vector &f,
			   const Vector &u_0, const double tolerance) const {
		Vector u_cur = u_0;
		Vector u_next = step(n, A, f, u_cur);
		double prev_dist = (u_cur - u_next).norm();
		double cur_dist;
		u_cur = u_next;
		int number_faults = 0;

		while(1) {
			u_next = step(n, A, f, u_cur);
			cur_dist = (u_cur - u_next).norm();

			if (cur_dist <= tolerance) {
				return u_next; // converged
			}

			if (!std::isfinite(cur_dist)) {
				return Vector(0); // diverged
			}
			if (cur_dist >= prev_dist) {
				++number_faults;
				if (number_faults > 20) {
					return Vector(0); // diverged
				}
			} else {
				number_faults = 0;
			}

			prev_dist = cur_dist;
			u_cur = u_next;
		}
	}
};

#endif  // __OVERRELAXATION_METHOD__
