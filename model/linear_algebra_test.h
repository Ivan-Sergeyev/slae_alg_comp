#ifndef __LINEAR_ALGEBRA_TEST__
#define __LINEAR_ALGEBRA_TEST__

#include "linear_algebra.h"
#include "string.h"


namespace linear_algebra_test {
	typedef int (*test_function_pointer)();

	int _test_constructor() {
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);

		const char *x1_str = x.repr();
		const char *x1_ref = "1.000000 2.000000 3.000000";

		if (strcmp(x1_str, x1_ref)) {
			printf("| failure:\n");
			printf("| repr of x is \"%s\", should be \"%s\"\n", x1_str, x1_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int _test_assignment() {
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z(size);
		z = x;

		const char *x2_str = x.repr();
		const char *x2_ref = "1.000000 2.000000 3.000000";
		const char *z1_str = z.repr();
		const char *z1_ref = "1.000000 2.000000 3.000000";

		if (strcmp(x2_str, x2_ref)) {
			printf("| failure\n");
			printf("| repr of x is \"%s\", should be \"%s\"\n", x2_str, x2_ref);
			return 1;
		}
		if (strcmp(z1_str, z1_ref)) {
			printf("| failure\n");
			printf("| repr of z is \"%s\", should be \"%s\"\n", z1_str, z1_ref);
			return 1;
		}
		printf("| success\n");
		return 0;
	}

	int test() {
		const int num_tests = 2;
		test_function_pointer single_tests[num_tests] =
			{_test_constructor, _test_assignment};

		int num_fails = 0;
		for (int i = 0; i < num_tests; ++i) {
			printf("test %d\n", i);
			num_fails += single_tests[i]();
		}

		return num_fails;
	}
}

#endif // __LINEAR_ALGEBRA_TEST__
