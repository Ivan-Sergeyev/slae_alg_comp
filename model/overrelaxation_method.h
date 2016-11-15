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
	double _tolerance;  // convergence tolerance
	int _max_faults;    // divergence criteria
	double _tau;        // relaxation parameter

public:
	OverrelaxationMethod(const double &tau,
						 const double &tolerance, const int &max_faults) :
			_tolerance(tolerance), _max_faults(max_faults) {
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
			u_next(i) = f(i);
			for (int j = 0; j < i; ++j) {
				u_next(i) -= A(i, j) * u_next(j);
			}
			for (int j = i + 1; j < n; ++j) {
				u_next(i) -= A(i, j) * u(j);
			}
			u_next(i) *= _tau / A(i, i);
			u_next(i) += (1 - _tau) * u(i);
		}
		return u_next;
	}

	Vector run(const Matrix &A, const Vector &f) const {
		int n = A.get_size();
		assert(n == f.get_size());
		Vector u_cur = Vector(n);
		Vector u_next = step(n, A, f, u_cur);
		double prev_dist = (u_cur - u_next).norm();
		double cur_dist;
		u_cur = u_next;
		int number_faults = 0;

		while(1) {
			u_next = step(n, A, f, u_cur);
			cur_dist = (u_cur - u_next).norm();

			if (cur_dist <= _tolerance) {
				return u_next;  // converged
			}

			if (!std::isfinite(cur_dist)) {
				cerr << "[warning] " << get_name() << " diverged\n"
					 << "          !std::isfinite(cur_dist)\n";
				u_next = Vector(0);
				return u_next;  // diverged
			}
			if (cur_dist >= prev_dist) {
				++number_faults;
				if (number_faults > _max_faults) {
					u_next = Vector(0);
					cerr << "[warning] " << get_name() << " diverged\n"
						 << "          number_faults > _max_faults\n";
					return u_next;  // diverged
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
