#ifndef __OVERRELAXATION_METHOD__
#define __OVERRELAXATION_METHOD__

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "generic_method.h"


using std::cerr;
using std::string;
using std::to_string;


class OverrelaxationMethod : public GenericMethod {
private:
	double _tau;        // relaxation parameter
	double _tolerance;  // convergence tolerance

public:
	OverrelaxationMethod(const double &tau, const double &tolerance) :
			_tau(tau), _tolerance(tolerance) {
		assert(tau > 0);
		assert(tau < 2);

		if (tau == 1.0) {
			set_name(string("Seidel Method"));
		} else {
			string name = string("Overrelaxation Method with tau=") +
						  to_string(tau);
			set_name(name);
		}
	}

	Vector step(const int &n, const Matrix &A,
				const Vector &f, const Vector &u) const {
		Vector u_next(n);
		for (int i = 0; i < n; ++i) {
			u_next._coord[i] = f._coord[i];
			for (int j = 0; j < i; ++j) {
				u_next._coord[i] -= A._value[i][j] * u_next._coord[j];
			}
			for (int j = i + 1; j < n; ++j) {
				u_next._coord[i] -= A._value[i][j] * u._coord[j];
			}
			u_next._coord[i] *= _tau / A._value[i][i];
			u_next._coord[i] += (1 - _tau) * u._coord[i];
		}
		return u_next;
	}

	Vector run(const Matrix &A, const Vector &f) const {
		int n = A._size;
		assert(n == f._size);
		Vector u_cur = Vector(n);
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

#endif  // __OVERRELAXATION_METHOD__
