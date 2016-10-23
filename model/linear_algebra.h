#include <stdio.h>


double abs(const double &a) {
	if (a > 0.0) {
		return a;
	}
	return -a;
}


template <typename T> T max (const T &a, const T &b) {
	if (a < b) {
		return b;
	}
	return a;
}


class Vector {
private:
	int _size;
	double *_value;

public:
	Vector(const int size) {
		_size = size;
		_value = new double [_size];
		for (int i = 0; i < _size; ++i) {
			_value[i] = 0;
		}
	}

	Vector(const int size, double *value) {
		_size = size;
		_value = new double [_size];
		for (int i = 0; i < _size; ++i) {
			_value[i] = value[i];
		}
	}

	double norm() const {
		double n = abs(_value[0]);
		for (int i = 1; i < _size; ++i) {
			n = max(abs(_value[i]), n);
		}
		return n;
	}

	int getSize() const {
		return _size;
	}

	double & operator [] (const int idx) const {
		return _value[idx];
	}

	bool operator == (const Vector &v) const {
		for (int i = 0; i < _size; ++i) {
			if (_value[i] != v[i]) {
				return 0;
			}
		}
		return 1;
	}
};


class Matrix {
private:
	int _size;
	double **_value;

public:
	Matrix(const int size) {
		_size = size;
		_value = new double* [_size];
		for (int i = 0; i < _size; ++i) {
			_value[i] = new double [_size];
		}
	}

	Matrix(const int size, double *value) {
		_size = size;
		_value = new double* [_size];
		for (int i = 0; i < _size; ++i) {
			_value[i] = new double [_size];
			for (int j = 0; j < _size; ++j) {
				_value[i][j] = value[i * _size + j];
			}
		}
	}

	double norm() const {
		double n = 0;
		for (int i = 0; i < _size; ++i) {
			double s = 0;
			for (int j = 0; j < _size; ++j) {
				s += abs(_value[i][j]);
			}
			n = max(n, s);
		}
		return n;
	}

	Vector operator * (const Vector &v) const {
		if (v.getSize() != _size) {
			return Vector(0, 0);
		}

		Vector result = Vector(_size);

		for (int i = 0; i < _size; ++i) {
			for (int j = 0; j < _size; ++j) {
				result[i] += _value[i][j] * v[j];
			}
		}

		return result;
	}
};


/*
int linear_algebra_test() {
	int num_tests = 0,
		num_fails = 0;

	++num_tests;
	double mat[4] = {1, 0, 0, 1};
	Matrix a = Matrix(2, mat);
	double vec[2] = {2, 3};
	Vector v = Vector(2, vec);
	double mul[2] = {2, 3};
	Vector ans = Vector(2, mul);

	Vector res = a * v;
	if (res == ans) {
		printf("test %d success\n", num_tests);
	} else {
		printf("test %d fail\n", num_tests);
		printf("%lf %lf != ", res[0], res[1]);
		printf("%lf %lf\n", mul[0], mul[1]);
	}

	printf("total number of tests: %d\n", num_tests);
	printf("total number of fails: %d\n", num_fails);
	return num_fails;
}
*/
