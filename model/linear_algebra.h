#ifndef __LINEAR_ALGEBRA__
#define __LINEAR_ALGEBRA__

#include <assert.h>
#include <cmath>
#include <stdio.h>


const int REPR_BUFFER_LEN = 1000;  // string representation buffer size


class Vector {
private:
	int _size;       // vector's size
	double *_coord;  // vector's coordinates

// hard check if vector's state is ok
	bool _is_ok() const {
		return !_size || _coord;
	}

// erase
	void _delete() {
		_size = 0;
		delete[] _coord;
		_coord = 0;
	}

// change vector's size, coordinates might change
	void _resize(const int size) {
		if (_size != size) {
			if (_size) {  // TODO: check redundancy (unix specific?)
				_delete();
			}
			_size = size;
			_coord = new double [_size];
		}
	}

// make a copy of an array of coordinates
	void _deep_copy(const int size, const double *value) {
		assert(!size || value);
		_resize(size);
		for (int i = 0; i < _size; ++i) {
			_coord[i] = value[i];
		}
	}

// make a copy of another vector
	void _deep_copy(const Vector &other) {
		_resize(other.getSize());
		for (int i = 0; i < _size; ++i) {
			_coord[i] = other(i);
		}
	}

// fill coordinates with zeroes
	void _fill_zero() {
		assert(_is_ok());
		for (int i = 0; i < _size; ++i) {
			_coord[i] = 0;
		}
	}

// hard check if idx is in bounds
	void _bounds_check(const int idx) const {
		assert(idx >= 0);
		assert(idx < _size);
	}

public:
// constructors
	Vector() : _size(0), _coord(0) {}

	Vector(const int size) : _size(0), _coord(0) {
		_resize(size);
		_fill_zero();
	}

	Vector(const int size, const double *value) : _size(0), _coord(0) {
		_deep_copy(size, value);
	}

	Vector(const Vector &other) : _size(0), _coord(0) {
		_deep_copy(other);
	}

// destructor
	~Vector() {
		_delete();
	}

// read access to size
	int getSize() const {
		return _size;
	}

// read access to coordinates
	const double& operator () (const int idx) const {
		assert(_is_ok());
		_bounds_check(idx);
		return _coord[idx];
	}

// write access to coordinates
	double& operator () (const int idx) {
		assert(_is_ok());
		_bounds_check(idx);
		return _coord[idx];
	}

// get vector's norm
	double norm() const {
		assert(_is_ok());
		if (!_size) {
			return 0;
		}
		double n = abs(_coord[0]);
		for (int i = 1; i < _size; ++i) {
			double abs_coord = abs(_coord[i]);
			if (abs_coord > n) {
				n = abs_coord;
			}
		}
		return n;
	}

// deep copy
	Vector& operator = (const Vector &other) {
		if (this != &other) {
			_deep_copy(other);
		}
		return *this;
	}

// binary plus
	Vector& operator + (const Vector &other) {
		assert(_is_ok());
		assert(_size == other.getSize());
		Vector *sum = new Vector(*this);
		for (int i = 0; i < _size; ++i) {
			sum[i] += other(i);
		}
		return *sum;
	}

// binary minus
	Vector& operator - (const Vector &other) {
		assert(_is_ok());
		assert(_size == other.getSize());
		Vector *sum = new Vector(*this);
		for (int i = 0; i < _size; ++i) {
			sum[i] -= other(i);
		}
		return *sum;
	}

// unary plus
	friend Vector operator + (const Vector &vector) {
		return vector;
	}

// unary minus
	friend Vector operator - (const Vector &vector) {
		Vector *neg = new Vector(vector.getSize());
		(*neg) -= vector;
		return *neg;
	}

// addition
	Vector& operator += (const Vector &other) {
		assert(_is_ok());
		assert(_size == other.getSize());
		for (int i = 0; i < _size; ++i) {
			_coord[i] += other(i);
		}
		return *this;
	}

// subtraction
	Vector& operator -= (const Vector &other) {
		assert(_is_ok());
		assert(_size == other.getSize());
		for (int i = 0; i < _size; ++i) {
			_coord[i] -= other(i);
		}
		return *this;
	}

// multiplication
	Vector& operator *= (const double &a) {
		assert(_is_ok());
		for (int i = 0; i < _size; ++i) {
			_coord[i] *= a;
		}
		return *this;
	}

// multiplication
	friend Vector operator * (const double &a, const Vector &vector) {
		return vector * a;
	}

// multiplication
	friend Vector operator * (const Vector &vector, const double &a) {
		return a * vector;
	}

// equality check
	bool operator == (const Vector &other) const {
		assert(_is_ok());
		for (int i = 0; i < _size; ++i) {
			if (_coord[i] != other(i)) {
				return 0;
			}
		}
		return 1;
	}

// string representation
	const char* repr() const {
		assert(_is_ok());

		char *string = new char[REPR_BUFFER_LEN];
		char *s = string;
		int delta;

		*s = 0;
		for(int i = 0; i < _size - 1; ++i) {
			delta = sprintf(s, "%lf ", _coord[i]);
			if (delta > 0) {  // success : delta characters appended
				s += delta;
			} else {          // failure, return whatever
				// TODO: indicate failure
				return string;
			}
		}
		sprintf(s, "%lf", _coord[_size - 1]);
		return string;
	}
};


class Matrix {
private:
	int _size;        // matrix' size
	double **_value;  // matrix' values

// hard check if matrix' state is ok
	bool _is_ok() const {
		return !_size || _value;
	}

// hard check if row and col are in bounds
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

	~Matrix() {
		_size = 0;
		delete[] _value;
		_value = 0;
	}

	int getSize () const {
		return _size;
	}

	double& operator ()(const int row, const int col) {
		_bounds_check(row, col);
		return _value[row][col];
	}

	const double& operator ()(const int row, const int col) const {
		_bounds_check(row, col);
		return _value[row][col];
	}

	double norm() const {
		double n = 0;
		for (int i = 0; i < _size; ++i) {
			double s = 0;
			for (int j = 0; j < _size; ++j) {
				s += abs(_value[i][j]);
			}
			if (s > n) {
				n = s;
			}
		}
		return n;
	}

	friend Vector operator * (const Matrix &a, const Vector &v) {
		int size = a.getSize();
		assert(v.getSize() == size);
		Vector *result = new Vector(size);
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				(*result)(i) += a(i, j) * v(j);
			}
		}
		return *result;
	}
};

#endif  // __LINEAR_ALGEBRA__
