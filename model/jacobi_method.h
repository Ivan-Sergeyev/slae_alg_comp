#ifndef __JACOBI_METHOD__
#define __JACOBI_METHOD__

#include <cmath>
#include <iostream>

#include "generic_method.h"


using std::cerr;


class JacobiMethod : public GenericMethod {
private:
	double _tolerance;  // convergence tolerance

public:
	JacobiMethod(const double &tolerance) :
		GenericMethod("Jacobi Method"), _tolerance(tolerance) {}

	Vector step(const int &n, const Matrix &A,
				const Vector &f, const Vector &u) const {
		Vector u_next(n);
		for (int i = 0; i < n; ++i) {
			u_next._value[i] = f._value[i];
			for (int j = 0; j < i; ++j) {
				u_next._value[i] -= A._value[i][j] * u._value[j];
			}
			for (int j = i + 1; j < n; ++j) {
				u_next._value[i] -= A._value[i][j] * u._value[j];
			}
			u_next._value[i] /= A._value[i][i];
		}
		return u_next;
	}

	Vector run(const Matrix &A, const Vector &f) const {
		int n = A._size;
		assert(n == f._size);
		Vector u_cur = f;
		Vector u_next = step(n, A, f, u_cur);
		double prev_dist = (u_cur - u_next).norm();
		double cur_dist;
		u_cur = u_next;

		while(1) {
			u_next = step(n, A, f, u_cur);
			cur_dist = (u_cur - u_next).norm();

			if (cur_dist <= _tolerance) {
				return u_next;  // converged
			}

			if (!std::isfinite(cur_dist)) {
				cerr << "[warning] " << get_name() << " diverged\n"
					 << "          !std::isfinite(cur_dist)\n";
				return Vector(0);  // diverged
			}

			prev_dist = cur_dist;
			u_cur = u_next;
		}
	}
};

#endif  // __JACOBI_METHOD__
