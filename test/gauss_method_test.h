#ifndef __GAUSS_METHOD_TEST__
#define __GAUSS_METHOD_TEST__

#include <iostream>
#include <stdlib.h>
#include <string>

#include "../src/generators.h"
#include "../src/linear_algebra.h"
#include "../src/gauss_method.h"


using std::cerr;
using std::string;


namespace gauss_method_test {
	typedef int (*test_function_pointer)();

	int _test_identity_matrix() {
		cerr << "  | testing GaussMethod with identity matrix\n";
		bool ret = 0;

		double tolerance = 1e-7;
		GaussMethod gauss_method;

		const int size = 3;
		const double a_value[size * size] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
		const double f_value[size] = {19, 38, 57};

		Matrix a(size, a_value);
		Vector f(size, f_value);

		Vector res = gauss_method.run(a, f);
		Vector res_ref(f);

		if (res.repr() != res_ref.repr()) {
			cerr << "  | failure\n"
				 << "  | result = " << res << "\n"
				 << "  | should be " << res_ref << "\n";
			ret = 1;
		}
		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_coursebook_ex() {
		cerr << "  | testing GaussMethod with coursebook example\n";
		bool ret = 0;

		double tolerance = 1e-7;
		GaussMethod gauss_method;

		const int size = 2;
		const double a_value[size * size] = {2, 1, 1, 2};
		const double f_value[size] = {1, -1};

		Matrix a(size, a_value);
		Vector f(size, f_value);

		Vector res = gauss_method.run(a, f);
		Vector res_ref(f);

		if (res.repr() != res_ref.repr()) {
			cerr << "  | failure\n"
				 << "  | result = " << res << "\n"
				 << "  | should be " << res_ref << "\n";
			ret = 1;
		}
		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_with_generator() {
		cerr << "  | testing GaussMethod with matrix generator with mu\n";
		bool ret = 0;

		int size = 10;
		double tolerance = 1e-7;
		GaussMethod gauss_method;

		for(int mu = 1; mu < 400; ++mu) {
			srand(mu);
			Vector f = generators::vector_random(size);
			Matrix A = generators::matrix_with_approximate_mu(size, mu);
			Vector result = gauss_method.run(A, f);

			if (result.get_size() != size) {
				cerr << "  | failure\n"
					 << "  | result has size = " << result.get_size() << "\n"
					 << "  | vector: " << f << "\n"
					 << "  | matrix:\n" << A << "\n\n";
				ret = 1;
			} else {
				Vector res_f = A * result;

				if ((f - res_f).norm() > 10 * tolerance) {
					cerr << "  | failure\n"
						 << "  | answer of jacobi method yields RHS = "
						 << res_f << "\n"
						 << "  | vector: " << f << "\n"
						 << "  | matrix:\n" << A << "\n\n";
					ret = 1;
				}
			}
		}

		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	const test_function_pointer gauss_method_tests[] =
		{_test_identity_matrix, _test_coursebook_ex, _test_with_generator, 0};
}

#endif // __GAUSS_METHOD_TEST__
