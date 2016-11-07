#ifndef __LINEAR_ALGEBRA__
#define __LINEAR_ALGEBRA__

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>


using std::string;
using std::swap;
using std::to_string;


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
		if (_coord) {  // TODO: check redundancy (unix specific?)
			delete[] _coord;
		}
		_coord = 0;
		_size = 0;
	}

// change vector's size, coordinates might change
	void _resize(const int &size) {
		if (_size == size) {
			return;
		}
		_delete();
		_size = size;
		_coord = new double [_size];
	}

// make a copy of an array of coordinates
	void _deep_copy(const int &size, const double *value) {
		assert(!size || value);
		_resize(size);
		for (int i = 0; i < _size; ++i) {
			_coord[i] = value[i];
		}
	}

// make a copy of another vector
	void _deep_copy(const Vector &other) {
		_resize(other.get_size());
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
	void _bounds_check(const int &idx) const {
		assert(idx >= 0);
		assert(idx < _size);
	}

public:
// constructors
	Vector() : _size(0), _coord(0) {}

	Vector(const int &size) : _size(0), _coord(0) {
		_resize(size);
		_fill_zero();
	}

	Vector(const int &size, const double *value) : _size(0), _coord(0) {
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
	int get_size() const {
		return _size;
	}

// read access to coordinates
	const double operator () (const int &idx) const {
		assert(_is_ok());
		_bounds_check(idx);
		return _coord[idx];
	}

// write access to coordinates
	double& operator () (const int &idx) {
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
		double n = std::abs(_coord[0]);
		for (int i = 1; i < _size; ++i) {
			double abs_coord = std::abs(_coord[i]);
			if (abs_coord > n) {
				n = abs_coord;
			}
		}
		return n;
	}

// deep copy
	Vector operator = (const Vector &other) {
		if (this != &other) {
			_deep_copy(other);
		}
		return *this;
	}

// equality check
	bool operator == (const Vector &other) const {
		assert(_is_ok());
		if (_size != other.get_size()) {
			return 0;
		}
		for (int i = 0; i < _size; ++i) {
			if (_coord[i] != other(i)) {
				return 0;
			}
		}
		return 1;
	}

// binary plus
	Vector operator + (const Vector &other) {
		assert(_is_ok());
		assert(_size == other.get_size());
		Vector sum(*this);
		for (int i = 0; i < _size; ++i) {
			sum(i) += other(i);
		}
		return sum;
	}

// binary minus
	Vector operator - (const Vector &other) {
		assert(_is_ok());
		assert(_size == other.get_size());
		Vector sum(*this);
		for (int i = 0; i < _size; ++i) {
			sum(i) -= other(i);
		}
		return sum;
	}

// unary plus
	friend Vector operator + (const Vector &vector) {
		return vector;
	}

// unary minus
	friend Vector operator - (const Vector &vector) {
		Vector neg(vector.get_size());
		neg -= vector;
		return neg;
	}

// addition
	Vector operator += (const Vector &other) {
		assert(_is_ok());
		assert(_size == other.get_size());
		for (int i = 0; i < _size; ++i) {
			_coord[i] += other(i);
		}
		return *this;
	}

// subtraction
	Vector operator -= (const Vector &other) {
		assert(_is_ok());
		assert(_size == other.get_size());
		for (int i = 0; i < _size; ++i) {
			_coord[i] -= other(i);
		}
		return *this;
	}

// multiplication by a double
	Vector operator *= (const double &a) {
		assert(_is_ok());
		for (int i = 0; i < _size; ++i) {
			_coord[i] *= a;
		}
		return *this;
	}

// multiplication (vector times double)
	Vector operator * (const double &a) const {
		Vector mul(*this);
		for(int i = 0; i < _size; ++i) {
			mul(i) *= a;
		}
		return mul;
	}

// multiplication (double times vector)
	friend Vector operator * (const double &a, const Vector &vector) {
		return vector * a;
	}

// string representation
	string repr() const {
		assert(_is_ok());

		if (!_size) {  // empty vector
			return string("");
		}

		string rep;
		for (int i = 0; i < _size - 1; ++i) {
			rep += to_string(_coord[i]) + string(" ");
		}
		rep += to_string(_coord[_size - 1]);
		return rep;
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

// make a copy of an array of values
	void _deep_copy(const int &size, const double *value) {
		assert(!size || value);
		_resize(size);
		for (int i = 0; i < _size; ++i) {
			for (int j = 0; j < _size; ++j) {
				_value[i][j] = value[i * _size + j];
			}
		}
	}

// make a copy of another matrix
	void _deep_copy(const Matrix &other) {
		_resize(other.get_size());
		for (int i = 0; i < _size; ++i) {
			for (int j = 0; j < _size; ++j) {
				_value[i][j] = other(i, j);
			}
		}
	}

// erase
	void _delete() {
		if (_value) {  // TODO: check redundancy (unix specific?)
			for (int i = 0; i < _size; ++i) {
				if (_value[i]) {  // TODO: check redundancy (unix specific?)
					delete[] _value[i];
				}
			}
			delete[] _value;
		}
		_value = 0;
		_size = 0;
	}

// fill values with zeroes
	void _fill_zero() {
		assert(_is_ok());
		for (int i = 0; i < _size; ++i) {
			for (int j = 0; j < _size; ++j) {
				_value[i][j] = 0;
			}
		}
	}

// change matrix' size, values might change
	void _resize(const int &size) {
		if (_size == size) {
			return;
		}
		_delete();
		_size = size;
		_value = new double* [_size];
		for (int i = 0; i < _size; ++i) {
			_value[i] = new double[_size];
		}
	}

// hard check if row and col are in bounds
	void _bounds_check(const int &row, const int &col) const {
		assert(row >= 0);
		assert(row < _size);
		assert(col >= 0);
		assert(col < _size);
	}

public:
// constructors
	Matrix() : _size(0), _value (0) {}

	Matrix(const int size) : _size(0), _value(0) {
		_resize(size);
		_fill_zero();
	}

	Matrix(const int &size, const double *value) : _size(0), _value(0) {
		_deep_copy(size, value);
	}

	Matrix(const Matrix &other) : _size(0), _value(0) {
		_deep_copy(other);
	}

// destructor
	~Matrix() {
		_delete();
	}

// read access to size
	int get_size () const {
		return _size;
	}

// read access to values
	const double operator () (const int &row, const int &col) const {
		assert(_is_ok());
		_bounds_check(row, col);
		return _value[row][col];
	}

// write access to values
	double& operator () (const int &row, const int &col) {
		assert(_is_ok());
		_bounds_check(row, col);
		return _value[row][col];
	}

// get matrix' norm
	double norm() const {
		assert(_is_ok());
		double n = 0;
		for (int i = 0; i < _size; ++i) {
			double s = 0;
			for (int j = 0; j < _size; ++j) {
				s += std::abs(_value[i][j]);
			}
			if (s > n) {
				n = s;
			}
		}
		return n;
	}

// deep copy
	Matrix operator = (const Matrix &other) {
		if (this != &other) {
			_deep_copy(other);
		}
		return *this;
	}

// multiplication by a vector
	Vector operator * (const Vector &other) const {
		assert(_size == other.get_size());
		Vector result(_size);
		for (int i = 0; i < _size; ++i) {
			for (int j = 0; j < _size; ++j) {
				result(i) += _value[i][j] * other(j);
			}
		}
		return result;
	}

// string representation
	string repr() const {
		assert(_is_ok());

		if (!_size) {  // empty vector
			return string("");
		}

		string rep;
		for (int i = 0; i < _size; ++i) {
			for (int j = 0; j < _size - 1; ++j) {
					rep += to_string(_value[i][j]) + string(" ");
				}
			rep += to_string(_value[i][_size - 1]) + string("\n");
		}

		return rep;
	}

// swap two rows
	void swap_rows(int i, int j) {
		for(int k = 0; k < _size; ++k) {
			swap(_value[i][k], _value[j][k]);
		}
	}

// specific function for gauss method -- pending refactor
	void find_max_and_swap(Vector* b, int j) const {
		int max_index = j;
		for (int i = j+1; i < _size; i++) if (_value[i][j] > _value[max_index][j] ) max_index = i;
		if (max_index != j){
			double temp;
			for (int i = j; i < _size; i++) {
				temp = _value[j][i]; _value[j][i] = _value[max_index][i]; _value[max_index][i] = temp;
			}
			temp = (*b)(j); (*b)(j) = (*b)(max_index); (*b)(max_index) = temp;
		}

 	}
 	void sub(Vector* b, int k, int l, double coeff) const{
		for (int i = 0; i < _size; i++) _value[k][i] -= _value[l][i]*coeff;
		(*b)(k) -= (*b)(l)*coeff;
	}

	Vector get_answer_from_triangle(const Vector &b) {
		Vector result(_size);
		double cash;
		for (int j = _size-1; j >=0; j--){
			cash = b(j);
			for (int i = j+1; i < _size; i++) cash -= _value[j][i] * result(i);
			result(j) = cash/_value[j][j];
		}
		return result;
	}
};

#endif  // __LINEAR_ALGEBRA__
