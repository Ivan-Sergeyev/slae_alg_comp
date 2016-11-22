#ifndef __LINEAR_ALGEBRA_TEST__
#define __LINEAR_ALGEBRA_TEST__

#include <iostream>
#include <string>

#include "../src/linear_algebra.h"


using std::cerr;
using std::string;


namespace linear_algebra_test {
	typedef int (*test_function_pointer)();

	int _test_v_ctor_0() {
		cerr << "  | testing Vector::Vector()\n";
		bool ret = 0;
		Vector x;

		int x_size = x.get_size();
		int x_size_ref = 0;
		string x_repr = x.repr();
		string x_repr_ref = string("");

		if (x_size != x_size_ref) {
			cerr << "  | failure:\n";
			cerr << "  | x_size = " << x_size
				 << ", should be " << x_size_ref << "\n";
			ret = 1;
		} else if (x_repr != x_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | x_repr = \"" << x_repr
				 << "\", should be \"" << x_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_ctor_i() {
		cerr << "  | testing Vector::Vector(const int size)\n";
		bool ret = 0;
		int x_size_ref = 5;

		Vector x(x_size_ref);

		string x_repr = x.repr();
		string x_repr_ref = string("0.000000 0.000000 0.000000 0.000000 0.000000");

		if (x_repr != x_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | x_repr = \"" << x_repr
				 << "\", should be \"" << x_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_ctor_ipd() {
		cerr << "  | testing Vector::Vector(const int size, const double *value)\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(size, x_value);

		string x_repr = x.repr();
		string x_repr_ref = string("1.000000 2.000000 3.000000");

		if (x_repr != x_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | x_repr = \"" << x_repr
				 << "\", should be \"" << x_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_ctor_vec() {
		cerr << "  | testing Vector::Vector(const Vector &other)\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(size, x_value);
		Vector z(x);

		string z_repr = z.repr();
		string z_repr_ref = string("1.000000 2.000000 3.000000");

		if (z_repr != z_repr_ref) {
			cerr << "  | failure\n"
				 << "  | z_repr = \"" << z_repr
				 << "\", should be \"" << z_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_get_size() {
		cerr << "  | testing Vector::get_size()\n";
		bool ret = 0;
		int x_size_ref = 3;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(x_size_ref, x_value);

		int x_size = x.get_size();

		if (x_size != x_size_ref) {
			cerr << "  | failure\n"
				 << "  | x_size = " << x_size
				 << ", should be " << x_size_ref << "\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_v_idx_c() {
		cerr << "  | testing Vector::const operator ()\n";
		bool ret = 0;
		int size = 3;
		int idx = 2;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(size, x_value);

		int x_val = x(idx);
		int x_val_ref = x_value[idx];

		if (x_val != x_val_ref) {
			cerr << "  | failure\n"
				 << "  | x[" << idx << "] = " << x_val
				 << ", should be " << x_val_ref << "\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_v_idx_v() {
		cerr << "  | testing Vector::operator ()\n";
		bool ret = 0;
		int size = 3;
		int idx = 2;
		double x_val_ref = 17.0;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(size, x_value);
		x(idx) = x_val_ref;

		int x_val = x(idx);

		if (x_val != x_val_ref) {
			cerr << "  | failure\n"
				 << "  | x[" << idx << "] = " << x_val
				 << ", should be " << x_val_ref << "\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_v_norm() {
		cerr << "  | testing Vector::norm()\n";
		bool ret = 0;
		int size = 4;
		double x_value[] = {0.0, 1.0, -2.0, 3.0};

		Vector x(size, x_value);

		double x_n = x.norm();
		double x_n_ref = 3.0;

		if (x_n != x_n_ref) {
			cerr << "  | failure\n"
				 << "  | x_norm = " << x_n
				 << ", should be " << x_n_ref << "\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_v_assignment() {
		cerr << "  | testing Vector::operator =\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(size, x_value);
		Vector z;
		z = x;

		string z_repr = z.repr();
		string z_repr_ref = string("1.000000 2.000000 3.000000");

		if (z_repr != z_repr_ref) {
			cerr << "  | failure\n"
				 << "  | z_repr = \"" << z_repr
				 << "\", should be \"" << z_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_eq() {
		cerr << "  | testing Vector::operator ==\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};
		double y_value[] = {1.0, 2.0, 3.0};
		double z_value[] = {1.0, 2.0, 3.1};
		double v_value[] = {1.0};

		Vector x(size, x_value);
		Vector y(size, y_value);
		Vector z(size, z_value);
		Vector v(size, v_value);

		if (!(x == y)) {
			cerr << "  | failure\n"
				 << "  | " << x.repr() << " should be = " << y.repr() << "\n";
			ret = 1;
		} else if (x == z) {
			cerr << "  | failure\n"
				 << "  | " << x.repr() << " should be != " << z.repr() << "\n";
			ret = 1;
		} else if (x == v) {
			cerr << "  | failure\n"
				 << "  | " << x.repr() << " should be != " << v.repr() << "\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_v_plus_b() {
		cerr << "  | testing Vector::binary operator +\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};
		double y_value[] = {10.0, 20.0, 30.0};

		Vector x(size, x_value);
		Vector y(size, y_value);
		Vector z = x + y;

		string z_repr = z.repr();
		string z_repr_ref = string("11.000000 22.000000 33.000000");

		if (z_repr != z_repr_ref) {
			cerr << "  | failure\n"
				 << "  | z_repr = \"" << z_repr
				 << "\", should be \"" << z_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_minus_b() {
		cerr << "  | testing Vector::binary operator -\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};
		double y_value[] = {10.0, 20.0, 30.0};

		Vector x(size, x_value);
		Vector y(size, y_value);
		Vector z = x - y;

		string z_repr = z.repr();
		string z_repr_ref = string("-9.000000 -18.000000 -27.000000");

		if (z_repr != z_repr_ref) {
			cerr << "  | failure\n"
				 << "  | z_repr = \"" << z_repr
				 << "\", should be \"" << z_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_plus_u() {
		cerr << "  | testing Vector::unary operator +\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(size, x_value);
		Vector z = +x;

		string z_repr = z.repr();
		string z_repr_ref = string("1.000000 2.000000 3.000000");

		if (z_repr != z_repr_ref) {
			cerr << "  | failure\n"
				 << "  | z_repr = \"" << z_repr
				 << "\", should be \"" << z_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_minus_u() {
		cerr << "  | testing Vector::unary operator -\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(size, x_value);
		Vector z;
		z = -x;

		string z_repr = z.repr();
		string z_repr_ref = string("-1.000000 -2.000000 -3.000000");

		if (z_repr != z_repr_ref) {
			cerr << "  | failure\n"
				 << "  | z_repr = \"" << z_repr
				 << "\", should be \"" << z_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_plus_e() {
		cerr << "  | testing Vector::operator +=\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};
		double y_value[] = {10.0, 20.0, 30.0};

		Vector x(size, x_value);
		Vector y(size, y_value);
		x += y;

		string x_repr = x.repr();
		string x_repr_ref = string("11.000000 22.000000 33.000000");
		string y_repr = y.repr();
		string y_repr_ref = string("10.000000 20.000000 30.000000");

		if (x_repr != x_repr_ref) {
			cerr << "  | failure\n"
				 << "  | x_repr = \"" << x_repr
				 << "\", should be \"" << x_repr_ref << "\"\n";
			ret = 1;
		} else if (y_repr != y_repr_ref) {
			cerr << "  | failure\n"
				 << "  | y_repr = \"" << y_repr
				 << "\", should be \"" << y_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_minus_e() {
		cerr << "  | testing Vector::operator -=\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};
		double y_value[] = {10.0, 20.0, 30.0};

		Vector x(size, x_value);
		Vector y(size, y_value);
		x -= y;

		string x_repr = x.repr();
		string x_repr_ref = string("-9.000000 -18.000000 -27.000000");
		string y_repr = y.repr();
		string y_repr_ref = string("10.000000 20.000000 30.000000");

		if (x_repr != x_repr_ref) {
			cerr << "  | failure\n"
				 << "  | x_repr = \"" << x_repr
				 << "\", should be \"" << x_repr_ref << "\"\n";
			ret = 1;
		} else if (y_repr != y_repr_ref) {
			cerr << "  | failure\n"
				 << "  | y_repr = \"" << y_repr
				 << "\", should be \"" << y_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_mul_e() {
		cerr << "  | testing Vector::operator *=\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};
		double a = 10;

		Vector x(size, x_value);
		x *= a;

		string x_repr = x.repr();
		string x_repr_ref = string("10.000000 20.000000 30.000000");

		if (x_repr != x_repr_ref) {
			cerr << "  | failure\n"
				 << "  | x_repr = \"" << x_repr
				 << "\", should be \"" << x_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_mul_vd() {
		cerr << "  | testing Vector::operator * (Vector, double)\n";
		bool ret = 0;
		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};
		double a = 10;

		Vector x(size, x_value);
		Vector y = x * a;

		string y_repr = y.repr();
		string y_repr_ref = string("10.000000 20.000000 30.000000");

		if (y_repr != y_repr_ref) {
			cerr << "  | failure\n"
				 << "  | y_repr = \"" << y_repr
				 << "\", should be \"" << y_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_v_mul_dv() {
		cerr << "  | testing Vector::operator * (double, Vector)\n";
		bool ret = 0;

		int size = 3;
		double x_value[] = {1.0, 2.0, 3.0};
		double a = 10;

		Vector x(size, x_value);
		Vector y = a * x;

		string y_repr = y.repr();
		string y_repr_ref = string("10.000000 20.000000 30.000000");

		if (y_repr != y_repr_ref) {
			cerr << "  | failure\n"
				 << "  | y_repr = \"" << y_repr
				 << "\", should be \"" << y_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_m_ctor_0() {
		cerr << "  | testing Matrix::Matrix()\n";
		bool ret = 0;

		Matrix m;

		int m_size = m.get_size();
		int m_size_ref = 0;

		if (m_size != m_size_ref) {
			cerr << "  | failure:\n";
			cerr << "  | m_size = " << m_size
				 << ", should be " << m_size_ref << "\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_m_ctor_i() {
		cerr << "  | testing Matrix::Matrix(const int size)\n";
		bool ret = 0;

		int m_size_ref = 2;

		Matrix m(m_size_ref);

		int m_size = m.get_size();
		string m_repr = m.repr();
		string m_repr_ref = string("0.000000 0.000000\n0.000000 0.000000");

		if (m_size != m_size_ref) {
			cerr << "  | failure:\n";
			cerr << "  | m_size = " << m_size
				 << ", should be " << m_size_ref << "\n";
			ret = 1;
		}
		if (m_repr != m_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | m_repr:\n" << m_repr << "\n"
				 << "  | should be:\n" << m_repr_ref << "\n";
			ret = 1;
		}
		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_m_ctor_id() {
		cerr << "  | testing Matrix::Matrix(const int size, const double *value)\n";
		// also testing const operator ()
		bool ret = 0;

		int m_size_ref = 2;
		double m_value[] = {3, 5, 7, 11};

		Matrix m(m_size_ref, m_value);

		int m_size = m.get_size();
		string m_repr = m.repr();
		string m_repr_ref = string("3.000000 5.000000\n7.000000 11.000000");

		if (m_size != m_size_ref) {
			cerr << "  | failure:\n";
			cerr << "  | m_size = " << m_size
				 << ", should be " << m_size_ref << "\n";
			ret = 1;
		}
		if (m_repr != m_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | m_repr:\n" << m_repr << "\n"
				 << "  | should be:\n" << m_repr_ref << "\n";
			ret = 1;
		}
		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_m_ctor_m() {
		cerr << "  | testing Matrix::Matrix(const Matrix &other)\n";
		bool ret = 0;

		int size_ref = 2;
		double m_value[] = {3, 5, 7, 11};

		Matrix a(size_ref, m_value);
		Matrix m(a);

		int m_size = m.get_size();
		string m_repr = m.repr();
		string m_repr_ref = string("3.000000 5.000000\n7.000000 11.000000");

		if (m_size != size_ref) {
			cerr << "  | failure:\n";
			cerr << "  | m_size = " << m_size
				 << ", should be " << size_ref << "\n";
			ret = 1;
		}
		if (m_repr != m_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | m_repr:\n" << m_repr << "\n"
				 << "  | should be:\n" << m_repr_ref << "\n";
			ret = 1;
		}
		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_m_get_size() {
		cerr << "  | testing Matrix::get_size()\n";
		bool ret = 0;

		int x_size_ref = 3;
		double x_value[] = {1.0, 2.0, 3.0};

		Vector x(x_size_ref, x_value);

		int x_size = x.get_size();

		if (x_size != x_size_ref) {
			cerr << "  | failure\n"
				 << "  | x_size = " << x_size
				 << ", should be " << x_size_ref << "\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_m_idx_v() {
		cerr << "  | testing Matrix::operator ()\n";
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
					cerr << "  | failure\n"
				 << "  | m(" << i << ", " << j << ") = " << m(i, j)
						 << " != " << v_ref << "\n";
					ret = 1;
				}
			}
		}
		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_m_norm() {
		cerr << "  | testing Matrix::norm()\n";
		bool ret = 0;
		int m_size_ref = 2;
		double m_value[] = {3.0, 5.0, 7.0, 11.0};
		double norm_ref = m_value[2] + m_value[3];

		Matrix m(m_size_ref, m_value);
		double norm = m.norm();

		if (norm != norm_ref) {
			cerr << "  | failure\n"
				 << "  | norm = " << norm << " != " << norm_ref << "\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_m_assignment() {
		cerr << "  | testing Matrix::operator =\n";
		bool ret = 0;

		int size_ref = 2;
		double m_value[] = {3, 5, 7, 11};

		Matrix a(size_ref, m_value);
		Matrix b;
		b = a;

		int b_size = b.get_size();
		string b_repr = b.repr();
		string b_repr_ref = string("3.000000 5.000000\n7.000000 11.000000");

		if (b_size != size_ref) {
			cerr << "  | failure:\n";
			cerr << "  | b_size = " << b_size
				 << ", should be " << size_ref << "\n";
			ret = 1;
		}
		if (b_repr != b_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | b_repr:\n" << b_repr << "\n"
				 << "  | should be:\n" << b_repr_ref << "\n";
			ret = 1;
		}
		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	int _test_m_mul() {
		cerr << "  | testing Matrix::operator *\n";
		bool ret = 0;

		int size_ref = 2;
		double m_value[] = {3, 5, 7, 11};
		double v_value[] = {2, 4};

		Matrix a(size_ref, m_value);
		Vector v(size_ref, v_value);

		Vector f(a * v);

		string f_repr = f.repr();
		string f_repr_ref = string("26.000000 58.000000");

		int f_size = f.get_size();
		if (f_size != size_ref) {
			cerr << "  | failure:\n";
			cerr << "  | f_size = " << f_size
				 << ", should be " << size_ref << "\n";
			ret = 1;
		} else if (f_repr != f_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | f_repr = \"" << f_repr
				 << "\", should be \"" << f_repr_ref << "\"\n";
			ret = 1;
		} else {
			cerr << "  | success\n";
		}

		return ret;
	}

	int _test_m_swap_rows() {
		cerr << "  | testing Matrix::swap_rows(int, int)\n";
		bool ret = 0;

		int size = 2;
		double m_value[] = {3, 5, 7, 11};

		Matrix a(size, m_value);

		a.swap_rows(0, 1);
		string a_repr = a.repr();
		string a_repr_ref = string("7.000000 11.000000\n3.000000 5.000000");

		if (a_repr != a_repr_ref) {
			cerr << "  | failure:\n";
			cerr << "  | a_repr:\n" << a_repr << "\n"
				 << "  | should be:\n" << a_repr_ref << "\n";
			ret = 1;
		}
		if (!ret) {
			cerr << "  | success\n";
		}
		return ret;
	}

	const test_function_pointer vector_tests[] =
		{_test_v_ctor_0, _test_v_ctor_i, _test_v_ctor_ipd, _test_v_ctor_vec,
		 _test_v_get_size, _test_v_idx_c, _test_v_idx_v, _test_v_norm,
		 _test_v_assignment, _test_v_eq,
		 _test_v_plus_b, _test_v_minus_b, _test_v_plus_u, _test_v_minus_u,
		 _test_v_plus_e, _test_v_minus_e, _test_v_mul_e, _test_v_mul_vd,
		 _test_v_mul_dv, 0};

	const test_function_pointer matrix_tests[] =
		{_test_m_ctor_0, _test_m_ctor_i, _test_m_ctor_id, _test_m_ctor_m,
		 _test_m_idx_v, _test_m_norm, _test_m_assignment, _test_m_mul,
		 _test_m_swap_rows, 0};
}

#endif // __LINEAR_ALGEBRA_TEST__
