#include <cmath>

#include "generic_method.h"


class JacobiMethod : public GenericMethod {
public:
	JacobiMethod() : GenericMethod("Jacobi Method") {}

	Vector step(const int n, const Matrix &A,
				const Vector &f, const Vector &u) const {
		Vector *u_next = new Vector(n);
		for (int i = 0; i < n; ++i) {
			(*u_next)[i] = f[i];
			for (int j = 0; j < i; ++j) {
				(*u_next)[i] -= A(i, j) * u[j];
			}
			for (int j = i + 1; j < n; ++j) {
				(*u_next)[i] -= A(i, j) * u[j];
			}
			(*u_next)[i] = (*u_next)[i] / A(i, i);
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

			if (cur_dist < tolerance) {
				return u_next;
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
