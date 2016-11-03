#ifndef __LINEAR_ALGEBRA_TEST__
#define __LINEAR_ALGEBRA_TEST__


#include "linear_algebra.h"
#include "string.h"


namespace linear_algebra_test {
	typedef int (*test_function_pointer)();

	int _test_ctor_0() {  // Vector()
		Vector x;

		const int x_size = x.get_size();
		const int x_size_ref = 0;
		const char *x_repr = x.repr();
		const char *x_repr_ref = "";

		if (x_size != x_size_ref) {
			printf("| failure:\n");
			printf("| x_size = \"%d\", should be \"%d\"\n", x_size, x_size_ref);
			return 1;
		}
		if (strcmp(x_repr, x_repr_ref)) {
			printf("| failure:\n");
			printf("| x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_ctor_i() {  // Vector(const int size)
		const int x_size_ref = 5;

		Vector x(x_size_ref);

		const char *x_repr = x.repr();
		const char *x_repr_ref = "0.000000 0.000000 0.000000 0.000000 0.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("| failure:\n");
			printf("| x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_ctor_i_pd() {  // Vector(const int size, const double *value)
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);

		const char *x_repr = x.repr();
		const char *x_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("| failure:\n");
			printf("| x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_ctor_vec() {  // Vector(const Vector &other)
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z(x);

		const char *z_repr = z.repr();
		const char *z_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("| failure\n");
			printf("| z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_get_size() {  // int get_size()
		const int x_size_ref = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(x_size_ref, x_coord);

		const int x_size = x.get_size();

		if (x_size != x_size_ref) {
			printf("| failure\n");
			printf("| x_size = \"%d\", should be \"%d\"\n", x_size, x_size_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_op_idx_const() {  // const double& operator () (const int idx)
		const int size = 3;
		const int idx = 2;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);

		const int x_val = x(idx);
		const int x_val_ref = x_coord[idx];

		if (x_val != x_val_ref) {
			printf("| failure\n");
			printf("| x[%d] = \"%d\", should be \"%d\"\n", idx, x_val, x_val_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_op_idx_var() {  // double& operator () (const int idx)
		const int size = 3;
		const int idx = 2;
		const double x_val_ref = 4.0;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		x(idx) = x_val_ref;

		const int x_val = x(idx);

		if (x_val != x_val_ref) {
			printf("| failure\n");
			printf("| x[%d] = \"%d\", should be \"%d\"\n", idx, x_val, x_val_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_norm() {  // double norm()
		const int size = 4;
		const double x_coord[] = {0.0, 1.0, -2.0, 3.0};

		Vector x(size, x_coord);

		const double x_n = x.norm();
		const double x_n_ref = 3.0;

		if (x_n != x_n_ref) {
			printf("| failure\n");
			printf("| x_norm = \"%s\", should be \"%s\"\n", x_n, x_n_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_assignment() {
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z;
		z = x;

		const char *z_repr = z.repr();
		const char *z_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("| failure\n");
			printf("| z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int test() {
		const int num_tests = 9;
		test_function_pointer single_tests[num_tests] =
			{_test_ctor_0, _test_ctor_i, _test_ctor_i_pd, _test_ctor_vec,
			 _test_get_size, _test_op_idx_const, _test_op_idx_var, _test_norm,
			 _test_assignment};

		int num_fails = 0;
		for (int i = 0; i < num_tests; ++i) {
			printf("test %d\n", i);
			num_fails += single_tests[i]();
		}

		return num_fails;
	}
}

#endif // __LINEAR_ALGEBRA_TEST__
