#include <assert.h>
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

	void _delete() {
		_size = 0;
		delete[] _value;
		_value = 0;
	}

	void _deep_copy(const int size, double *value) {
		if (_size != size) {
			_delete();
			_size = size;
			_value = new double [_size];
		}
		for (int i = 0; i < _size; ++i) {
			_value[i] = value[i];
		}
	}

	void _deep_copy(Vector v) {
		if (_size != v.getSize()) {
			_delete();
			_size = v.getSize();
			_value = new double [_size];
		}
		for (int i = 0; i < _size; ++i) {
			_value[i] = v[i];
		}
	}

	void _fill_zero() {
		for (int i = 0; i < _size; ++i) {
			_value[i] = 0;
		}
	}

	void _bounds_check(const int idx) const {
		assert(idx >= 0);
		assert(idx < _size);
	}

public:
// constructors
	Vector(const int size) {
		_size = size;
		_value = new double [_size];
		_fill_zero();
	}

	Vector(const int size, double *value) {
		assert(value);
		_deep_copy(size, value);
	}

// destructor
	~Vector() {
		_delete();
	}

// access to properties
	int getSize() const {
		return _size;
	}

	double& operator [] (const int idx) {
		_bounds_check(idx);
		return _value[idx];
	}

	const double& operator [] (const int idx) const {
		_bounds_check(idx);
		return _value[idx];
	}

	double norm() const {
		assert(_value);
		double n = abs(_value[0]);
		for (int i = 1; i < _size; ++i) {
			n = max(abs(_value[i]), n);
		}
		return n;
	}

// deep copy
	Vector& operator = (const Vector &v) {
		if (this != &v) {
			_deep_copy(v);
		}
		return *this;
	}

// arithmetic
	Vector& operator += (const Vector &v) {
		assert(_size == v.getSize());
		for (int i = 0; i < _size; ++i) {
			_value[i] += v[i];
		}
		return *this;
	}

	Vector& operator -= (const Vector &v) {
		assert(_size == v.getSize());
		for (int i = 0; i < _size; ++i) {
			_value[i] -= v[i];
		}
		return *this;
	}

	friend Vector operator + (Vector lhs, const Vector& rhs) {
		lhs += rhs;
		return lhs;
	}

	friend Vector operator - (Vector lhs, const Vector &rhs) {
		lhs -= rhs;
		return lhs;
	}

	friend Vector operator - (const Vector &v) {
		Vector *neg = new Vector(v.getSize());
		(*neg) -= v;
		return *neg;
	}

	Vector& operator *= (const double &a) {
		for (int i = 0; i < _size; ++i) {
			_value[i] *= a;
		}
		return *this;
	}

	friend Vector operator * (const double &a, Vector rhs) {
		rhs *= a;
		return rhs;
	}

	friend Vector operator * (Vector lhs, const double &a) {
		return a * lhs;
	}

// relation
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

	void _bounds_check(const int row, const int col) const {
		assert(row >= 0);
		assert(row < _size);
		assert(col >= 0);
		assert(col < _size);
	}

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

	int getSize () const {
		return _size;
	}

	double& operator ()(const int row, const int col) {
		_bounds_check(row, col);
		return _value[row][col];
	}

	const double& operator ()(const int row, const int col) const {
		assert(row >= 0);
		assert(row < _size);
		assert(col >= 0);
		assert(col < _size);
		return _value[row][col];
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

	friend Vector operator * (const Matrix &a, const Vector &v) {
		int size = a.getSize();
		assert(v.getSize() == size);
		Vector *result = new Vector(size);
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				(*result)[i] += a(i, j) * v[j];
			}
		}
		return *result;
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
