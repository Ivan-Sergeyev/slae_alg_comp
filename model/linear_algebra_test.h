#ifndef __LINEAR_ALGEBRA_TEST__
#define __LINEAR_ALGEBRA_TEST__


#include "linear_algebra.h"
#include "string.h"


namespace linear_algebra_test {
	typedef int (*test_function_pointer)();

	int _test_v_ctor_0() {
		printf("  | testing Vector()\n");
		bool ret = 0;
		Vector x;

		int x_size = x.get_size();
		int x_size_ref = 0;
		char *x_repr = x.repr();
		const char *x_repr_ref = "";

		if (x_size != x_size_ref) {
			printf("  | failure:\n");
			printf("  | x_size = \"%d\", should be \"%d\"\n", x_size, x_size_ref);
			ret = 1;
		} else if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure:\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] x_repr;
		return ret;
	}

	int _test_v_ctor_i() {
		printf("  | testing Vector(const int size)\n");
		bool ret = 0;
		int x_size_ref = 5;

		Vector x(x_size_ref);

		char *x_repr = x.repr();
		const char *x_repr_ref = "0.000000 0.000000 0.000000 0.000000 0.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure:\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] x_repr;
		return ret;
	}

	int _test_v_ctor_ipd() {
		printf("  | testing Vector(const int size, const double *value)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);

		char *x_repr = x.repr();
		const char *x_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure:\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] x_repr;
		return ret;
	}

	int _test_v_ctor_vec() {
		printf("  | testing Vector(const Vector &other)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z(x);

		char *z_repr = z.repr();
		const char *z_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] z_repr;
		return ret;
	}

	int _test_v_get_size() {
		printf("  | testing int get_size()\n");
		bool ret = 0;
		int x_size_ref = 3;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(x_size_ref, x_coord);

		int x_size = x.get_size();

		if (x_size != x_size_ref) {
			printf("  | failure\n");
			printf("  | x_size = \"%d\", should be \"%d\"\n", x_size, x_size_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_v_idx_c() {
		printf("  | testing const double& operator () (const int idx) const\n");
		bool ret = 0;
		int size = 3;
		int idx = 2;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);

		int x_val = x(idx);
		int x_val_ref = x_coord[idx];

		if (x_val != x_val_ref) {
			printf("  | failure\n");
			printf("  | x[%d] = \"%d\", should be \"%d\"\n", idx, x_val, x_val_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_v_idx_v() {
		printf("  | testing double& operator () (const int idx)\n");
		bool ret = 0;
		int size = 3;
		int idx = 2;
		double x_val_ref = 17.0;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		x(idx) = x_val_ref;

		int x_val = x(idx);

		if (x_val != x_val_ref) {
			printf("  | failure\n");
			printf("  | x[%d] = \"%d\", should be \"%d\"\n", idx, x_val, x_val_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_v_norm() {
		printf("  | testing double norm()\n");
		bool ret = 0;
		int size = 4;
		double x_coord[] = {0.0, 1.0, -2.0, 3.0};

		Vector x(size, x_coord);

		double x_n = x.norm();
		double x_n_ref = 3.0;

		if (x_n != x_n_ref) {
			printf("  | failure\n");
			printf("  | x_norm = \"%s\", should be \"%s\"\n", x_n, x_n_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_v_assignment() {
		printf("  | testing Vector& operator = (const Vector &other)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z;
		z = x;

		char *z_repr = z.repr();
		const char *z_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] z_repr;
		return ret;
	}

	int _test_v_eq() {
		printf("  | testing bool operator == (const Vector &other) const\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};
		double y_coord[] = {1.0, 2.0, 3.0};
		double z_coord[] = {1.0, 2.0, 3.1};
		double v_coord[] = {1.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		Vector z(size, z_coord);
		Vector v(size, v_coord);

		if (!(x == y)) {
			printf("  | failure\n");
			printf("  | %s should be = %s \"%s\"\n", x.repr(), y.repr());
			ret = 1;
		} else if (x == z) {
			printf("  | failure\n");
			printf("  | %s should be != %s \"%s\"\n", x.repr(), z.repr());
			ret = 1;
		} else if (x == v) {
			printf("  | failure\n");
			printf("  | %s should be != %s \"%s\"\n", x.repr(), v.repr());
			ret = 1;
		} else {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_v_plus_b() {
		printf("  | testing Vector& operator + (const Vector &other)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};
		double y_coord[] = {10.0, 20.0, 30.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		Vector z = x + y;

		char *z_repr = z.repr();
		const char *z_repr_ref = "11.000000 22.000000 33.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] z_repr;
		return ret;
	}

	int _test_v_minus_b() {
		printf("  | testing Vector& operator - (const Vector &other)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};
		double y_coord[] = {10.0, 20.0, 30.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		Vector z = x - y;

		char *z_repr = z.repr();
		const char *z_repr_ref = "-9.000000 -18.000000 -27.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] z_repr;
		return ret;
	}

	int _test_v_plus_u() {
		printf("  | testing friend Vector operator + (const Vector &vector)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z = +x;

		char *z_repr = z.repr();
		const char *z_repr_ref = "1.000000 2.000000 3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] z_repr;
		return ret;
	}

	int _test_v_minus_u() {
		printf("  | testing friend Vector operator - (const Vector &vector)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(size, x_coord);
		Vector z;
		z = -x;

		char *z_repr = z.repr();
		const char *z_repr_ref = "-1.000000 -2.000000 -3.000000";

		if (strcmp(z_repr, z_repr_ref)) {
			printf("  | failure\n");
			printf("  | z_repr = \"%s\", should be \"%s\"\n", z_repr, z_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] z_repr;
		return ret;
	}

	int _test_v_plus_e() {
		printf("  | testing Vector& operator += (const Vector &other)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};
		double y_coord[] = {10.0, 20.0, 30.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		x += y;

		char *x_repr = x.repr();
		const char *x_repr_ref = "11.000000 22.000000 33.000000";
		char *y_repr = y.repr();
		const char *y_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			ret = 1;
		} else if (strcmp(y_repr, y_repr_ref)) {
			printf("  | failure\n");
			printf("  | y_repr = \"%s\", should be \"%s\"\n", y_repr, y_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] x_repr;
		delete[] y_repr;
		return ret;
	}

	int _test_v_minus_e() {
		printf("  | testing Vector& operator -= (const Vector &other)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};
		double y_coord[] = {10.0, 20.0, 30.0};

		Vector x(size, x_coord);
		Vector y(size, y_coord);
		x -= y;

		char *x_repr = x.repr();
		const char *x_repr_ref = "-9.000000 -18.000000 -27.000000";
		char *y_repr = y.repr();
		const char *y_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			ret = 1;
		} else if (strcmp(y_repr, y_repr_ref)) {
			printf("  | failure\n");
			printf("  | y_repr = \"%s\", should be \"%s\"\n", y_repr, y_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] x_repr;
		delete[] y_repr;
		return ret;
	}

	int _test_v_mul_e() {
		printf("  | testing Vector& operator *= (const double &a)\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};
		double a = 10;

		Vector x(size, x_coord);
		x *= a;

		char *x_repr = x.repr();
		const char *x_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(x_repr, x_repr_ref)) {
			printf("  | failure\n");
			printf("  | x_repr = \"%s\", should be \"%s\"\n", x_repr, x_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] x_repr;
		return ret;
	}

	int _test_v_mul_vd() {
		printf("  | testing Vector& operator * (const double &a) const\n");
		bool ret = 0;
		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};
		double a = 10;

		Vector x(size, x_coord);
		Vector y = x * a;

		char *y_repr = y.repr();
		const char *y_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(y_repr, y_repr_ref)) {
			printf("  | failure\n");
			printf("  | y_repr = \"%s\", should be \"%s\"\n", y_repr, y_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] y_repr;
		return ret;
	}

	int _test_v_mul_dv() {
		printf("  | testing friend Vector operator * (const double &a, const Vector &vector)\n");
		bool ret = 0;

		int size = 3;
		double x_coord[] = {1.0, 2.0, 3.0};
		double a = 10;

		Vector x(size, x_coord);
		Vector y = a * x;

		char *y_repr = y.repr();
		const char *y_repr_ref = "10.000000 20.000000 30.000000";

		if (strcmp(y_repr, y_repr_ref)) {
			printf("  | failure\n");
			printf("  | y_repr = \"%s\", should be \"%s\"\n", y_repr, y_repr_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}

		delete[] y_repr;
		return ret;
	}

	int _test_m_ctor_0() {
		printf("  | testing Matrix()\n");
		bool ret = 0;

		Matrix m;

		int m_size = m.get_size();
		int m_size_ref = 0;

		if (m_size != m_size_ref) {
			printf("  | failure:\n");
			printf("  | m_size = \"%d\", should be \"%d\"\n", m_size, m_size_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_m_ctor_i() {
		printf("  | testing Matrix(const int size)\n");
		bool ret = 0;

		int m_size_ref = 2;

		Matrix m(m_size_ref);

		int m_size = m.get_size();

		if (m_size != m_size_ref) {
			printf("  | failure:\n");
			printf("  | m_size = \"%d\", should be \"%d\"\n", m_size, m_size_ref);
			ret = 1;
		}
		for(int i = 0; i < m_size; ++i) {
			for(int j = 0; j < m_size; ++j) {
				if (m(i, j)) {
					printf("  | failure:\n");
					printf("  | m(%d, %d) != 0\n", i, j);
					ret = 1;
				}
			}
		}
		if (!ret) {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_m_ctor_id() {
		printf("  | testing Matrix(const int size, const double *value)\n");
		bool ret = 0;
		// also testing const double& operator () (const int row, const int col) const

		int m_size_ref = 2;
		double m_value[] = {3, 5, 7, 11};

		Matrix m(m_size_ref, m_value);

		int m_size = m.get_size();

		if (m_size != m_size_ref) {
			printf("  | failure:\n");
			printf("  | m_size = \"%d\", should be \"%d\"\n", m_size, m_size_ref);
			ret = 1;
		}
		for(int i = 0; i < m_size; ++i) {
			for(int j = 0; j < m_size; ++j) {
				double v_ref = m_value[i * m_size + j];
				if (m(i, j) != v_ref) {
					printf("  | failure:\n");
					printf("  | m(%d, %d) != %lf\n", i, j, v_ref);
					ret = 1;
				}
			}
		}
		if (!ret) {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_m_ctor_m() {
		printf("  | testing Matrix(const Matrix &other)\n");
		bool ret = 0;

		int size_ref = 2;
		double m_value[] = {3, 5, 7, 11};

		Matrix a(size_ref, m_value);
		Matrix b(a);

		int b_size = b.get_size();

		if (b_size != size_ref) {
			printf("  | failure:\n");
			printf("  | m_size = \"%d\", should be \"%d\"\n", b_size, size_ref);
			ret = 1;
		}
		for(int i = 0; i < b_size; ++i) {
			for(int j = 0; j < b_size; ++j) {
				double v_ref = a(i, j);
				if (b(i, j) != v_ref) {
					printf("  | failure:\n");
					printf("  | b(%d, %d) != %lf\n", i, j, v_ref);
					ret = 1;
				}
			}
		}
		if (!ret) {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_m_get_size() {
		printf("  | testing int get_size() const\n");
		bool ret = 0;

		int x_size_ref = 3;
		double x_coord[] = {1.0, 2.0, 3.0};

		Vector x(x_size_ref, x_coord);

		int x_size = x.get_size();

		if (x_size != x_size_ref) {
			printf("  | failure\n");
			printf("  | x_size = \"%d\", should be \"%d\"\n", x_size, x_size_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_m_idx_v() {
		printf("  | testing const double& operator () (const int row, const int col) const\n");
		bool ret = 0;

		int m_size_ref = 2;
		double m_value[] = {3.0, 5.0, 7.0, 11.0};
		double m_value_ref[] = {13.0, 25.0, 37.0, 51.0};

		Matrix m(m_size_ref, m_value);

		for(int i = 0; i < m_size_ref; ++i) {
			for(int j = 0; j < m_size_ref; ++j) {
				double v_ref = m_value_ref[i * m_size_ref + 1];
				m(i, j) = v_ref;
				if (m(i, j) != v_ref) {
					printf("  | failure\n");
					printf("  | m(%d, %d) != %lf\n", i, j, v_ref);
					ret = 1;
				}
			}
		}
		if (!ret) {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_m_norm() {
		printf("  | testing double norm() const\n");
		bool ret = 0;
		int m_size_ref = 2;
		double m_value[] = {3.0, 5.0, 7.0, 11.0};
		double norm_ref = m_value[2] + m_value[3];

		Matrix m(m_size_ref, m_value);
		double norm = m.norm();
		if (norm != norm_ref) {
			printf("  | failure\n");
			printf("  | norm = %lf != %lf\n", norm, norm_ref);
			ret = 1;
		} else {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_m_assignment() {
		printf("  | testing Matrix& operator = (const Matrix &other)\n");
		bool ret = 0;

		int size_ref = 2;
		double m_value[] = {3, 5, 7, 11};

		Matrix a(size_ref, m_value);
		Matrix b;
		b = a;

		int b_size = b.get_size();

		if (b_size != size_ref) {
			printf("  | failure:\n");
			printf("  | m_size = \"%d\", should be \"%d\"\n", b_size, size_ref);
			ret = 1;
		}
		for(int i = 0; i < b_size; ++i) {
			for(int j = 0; j < b_size; ++j) {
				double v_ref = a(i, j);
				if (b(i, j) != v_ref) {
					printf("  | failure:\n");
					printf("  | b(%d, %d) != %lf\n", i, j, v_ref);
					ret = 1;
				}
			}
		}
		if (!ret) {
			printf("  | success\n");
		}
		return ret;
	}

	int _test_m_mul() {
		printf("  | testing Vector& operator * (const Vector &other) const\n");
		bool ret = 0;

		int size_ref = 2;
		double m_value[] = {3, 5, 7, 11};
		double v_value[] = {2, 4};

		Matrix a(size_ref, m_value);
		Vector v(size_ref, v_value);

		Vector f(a * v);

		char *f_repr = f.repr();
		const char *f_repr_ref = "26.000000 58.000000";

		int f_size = f.get_size();
		if (f_size != size_ref) {
			printf("  | failure:\n");
			printf("  | f_size = \"%d\", should be \"%d\"\n", f_size, size_ref);
			ret = 1;
		}
		if (strcmp(f_repr, f_repr_ref)) {
			printf("  | failure:\n");
			printf("  | f = %s != %s\n", f_repr, f_repr_ref);
			ret = 1;
		}
		if (!ret) {
			printf("  | success\n");
		}

		delete[] f_repr;
		return ret;
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
			{_test_m_ctor_0, _test_m_ctor_i, _test_m_ctor_id, _test_m_ctor_m,
			 _test_m_idx_v, _test_m_norm, _test_m_assignment, _test_m_mul, 0};

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

#endif // __LINEAR_ALGEBRA_TEST__
