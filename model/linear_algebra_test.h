#ifndef __LINEAR_ALGEBRA_TEST__
#define __LINEAR_ALGEBRA_TEST__


#include "linear_algebra.h"
#include "string.h"


namespace linear_algebra_test {
	typedef int (*test_function_pointer)();

	int _test_v_ctor_0() {
		printf("  | testing Vector()\n");
		Vector x;

		const int x_size = x.get_size();
		const int x_size_ref = 0;
		const char *x_repr = x.repr();
		const char *x_repr_ref = "";

		if (x_size != x_size_ref) {
			printf("  | failure:\n");
			printf("  | x_size = \"%d\", should be \"%d\"\n", x_size, x_size_ref);
			return 1;
		}
		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure:\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_ctor_i() {
		printf("  | testing Vector(const int size)\n");
		const int x_size_ref = 5;

		Vector x(x_size_ref);

		const char *x_repr = x.repr();
		const char *x_repr_ref = "0.000000 0.000000 0.000000 0.000000 0.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure:\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_ctor_ipd() {
		printf("  | testing Vector(const int size, const double *value)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);

		const char *x_repr = x.repr();
		const char *x_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure:\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_ctor_vec() {
		printf("  | testing Vector(const Vector &other)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z(x);

		const char *z_repr = z.repr();
		const char *z_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_get_size() {
		printf("  | testing int get_size()\n");
		const int x_size_ref = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(x_size_ref, x_coord);

		const int x_size = x.get_size();

		if (x_size != x_size_ref) {
			printf("  | failure\n");
			printf("  | x_size = \"%d\", should be \"%d\"\n", x_size, x_size_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_idx_c() {
		printf("  | testing const double& operator () (const int idx) const\n");
		const int size = 3;
		const int idx = 2;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);

		const int x_val = x(idx);
		const int x_val_ref = x_coord[idx];

		if (x_val != x_val_ref) {
			printf("  | failure\n");
			printf("  | x[%d] = \"%d\", should be \"%d\"\n", idx, x_val, x_val_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_idx_v() {
		printf("  | testing double& operator () (const int idx)\n");
		const int size = 3;
		const int idx = 2;
		const double x_val_ref = 17.0;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		x(idx) = x_val_ref;

		const int x_val = x(idx);

		if (x_val != x_val_ref) {
			printf("  | failure\n");
			printf("  | x[%d] = \"%d\", should be \"%d\"\n", idx, x_val, x_val_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_norm() {
		printf("  | testing double norm()\n");
		const int size = 4;
		const double x_coord[] = {0.0, 1.0, -2.0, 3.0};

		Vector x(size, x_coord);

		const double x_n = x.norm();
		const double x_n_ref = 3.0;

		if (x_n != x_n_ref) {
			printf("  | failure\n");
			printf("  | x_norm = \"%s\", should be \"%s\"\n", x_n, x_n_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_assignment() {
		printf("  | testing Vector& operator = (const Vector &other)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z;
		z = x;

		const char *z_repr = z.repr();
		const char *z_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_eq() {
		printf("  | testing bool operator == (const Vector &other) const\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};
		const double y_coord[] = {1.0, 2.0, 3.0};
		const double z_coord[] = {1.0, 2.0, 3.1};
		const double v_coord[] = {1.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		Vector z(size, z_coord);
		Vector v(size, v_coord);

		if (!(x == y)) {
			printf("  | failure\n");
			printf("  | %s should be = %s \"%s\"\n", x.repr(), y.repr());
			return 1;
		}
		if (x == z) {
			printf("  | failure\n");
			printf("  | %s should be != %s \"%s\"\n", x.repr(), z.repr());
			return 1;
		}
		if (x == v) {
			printf("  | failure\n");
			printf("  | %s should be != %s \"%s\"\n", x.repr(), v.repr());
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_plus_b() {
		printf("  | testing Vector& operator + (const Vector &other)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};
		const double y_coord[] = {10.0, 20.0, 30.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		Vector z = x + y;

		const char *z_repr = z.repr();
		const char *z_repr_ref = "11.000000 22.000000 33.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_minus_b() {
		printf("  | testing Vector& operator - (const Vector &other)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};
		const double y_coord[] = {10.0, 20.0, 30.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		Vector z = x - y;

		const char *z_repr = z.repr();
		const char *z_repr_ref = "-9.000000 -18.000000 -27.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_plus_u() {
		printf("  | testing friend Vector operator + (const Vector &vector)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z = +x;

		const char *z_repr = z.repr();
		const char *z_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_minus_u() {
		printf("  | testing friend Vector operator - (const Vector &vector)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z;
		z = -x;

		const char *z_repr = z.repr();
		const char *z_repr_ref = "-1.000000 -2.000000 -3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_plus_e() {
		printf("  | testing Vector& operator += (const Vector &other)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};
		const double y_coord[] = {10.0, 20.0, 30.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		x += y;

		const char *x_repr = x.repr();
		const char *x_repr_ref = "11.000000 22.000000 33.000000";
		const char *y_repr = y.repr();
		const char *y_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		if (strcmp(y_repr, y_repr_ref)) {
			printf("  | failure\n");
			printf("  | y_repr = \"%s\", should be \"%s\"\n", y_repr, y_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_minus_e() {
		printf("  | testing Vector& operator -= (const Vector &other)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};
		const double y_coord[] = {10.0, 20.0, 30.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		x -= y;

		const char *x_repr = x.repr();
		const char *x_repr_ref = "-9.000000 -18.000000 -27.000000";
		const char *y_repr = y.repr();
		const char *y_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		if (strcmp(y_repr, y_repr_ref)) {
			printf("  | failure\n");
			printf("  | y_repr = \"%s\", should be \"%s\"\n", y_repr, y_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_mul_e() {
		printf("  | testing Vector& operator *= (const double &a)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};
		const double a = 10;

		Vector x(size, x_coord);
		x *= a;

		const char *x_repr = x.repr();
		const char *x_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_mul_vd() {
		printf("  | testing Vector& operator * (const double &a) const\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};
		const double a = 10;

		Vector x(size, x_coord);
		Vector y = x * a;

		const char *y_repr = y.repr();
		const char *y_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(y_repr, y_repr_ref)) {
			printf("  | failure\n");
			printf("  | y_repr = \"%s\", should be \"%s\"\n", y_repr, y_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_v_mul_dv() {
		printf("  | testing "
		  "friend Vector operator * (const double &a, const Vector &vector)\n");
		const int size = 3;
		const double x_coord[] = {1.0, 2.0, 3.0};
		const double a = 10;

		Vector x(size, x_coord);
		Vector y = a * x;

		const char *y_repr = y.repr();
		const char *y_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(y_repr, y_repr_ref)) {
			printf("  | failure\n");
			printf("  | y_repr = \"%s\", should be \"%s\"\n", y_repr, y_repr_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int _test_m_ctor_0() {
		printf("  | testing Matrix()\n");

		Matrix m;

		const int m_size = m.get_size();
		const int m_size_ref = 0;

		if (m_size != m_size_ref) {
			printf("  | failure:\n");
			printf("  | m_size = \"%d\", should be \"%d\"\n", m_size, m_size_ref);
			return 1;
		}
		printf("  | success\n");
		return 0;
	}

	int test() {
		const test_function_pointer vector_tests[] =
			{_test_v_ctor_0, _test_v_ctor_i, _test_v_ctor_ipd, _test_v_ctor_vec,
			 _test_v_get_size, _test_v_idx_c, _test_v_idx_v, _test_v_norm,
			 _test_v_assignment, _test_v_eq,
			 _test_v_plus_b, _test_v_minus_b, _test_v_plus_u, _test_v_minus_u,
			 _test_v_plus_e, _test_v_minus_e, _test_v_mul_e, _test_v_mul_vd,
			 _test_v_mul_dv, 0};
		const test_function_pointer matrix_tests[] =
			{_test_m_ctor_0, 0};

		int num_fails = 0;
		for (int i = 0; vector_tests[i]; ++i) {
			printf("  class Vector -- test #%d\n", i);
			num_fails += vector_tests[i]();
		}
		printf("-----------------------------------------------------------\n");
		for (int i = 0; matrix_tests[i]; ++i) {
			printf("  class Matrix -- test #%d\n", i);
			num_fails += matrix_tests[i]();
		}

		return num_fails;
	}
}

#endif // __LINEAR_ALGEBRA_TEST_v__
