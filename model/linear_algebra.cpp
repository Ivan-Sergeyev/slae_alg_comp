#ifndef __LINEAR_ALGEBRA_CPP__
#define __LINEAR_ALGEBRA_CPP__

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstring>

#include "linear_algebra.h"


using std::fill_n;
using std::swap;
using std::to_string;


// implementations for class Vector

bool Vector::_is_ok() const {
	return !_size || _value;
}

bool Vector::_bounds_check(const size_t idx) const {
	return idx >= 0 && idx < _size;
}

void Vector::_resize(const size_t size) {
	if (_size == size) {
		return;
	}
	_delete();
	_size = size;
	_value = new double [_size];
}

void Vector::_delete() {
	if (_value) {  // TODO: check redundancy (unix specific?)
		delete[] _value;
	}
	_value = 0;
	_size = 0;
}

void Vector::_fill_zero() {
	assert(_is_ok());
	fill_n(_value, _size, 0);
}

void Vector::_deep_copy(const size_t size, const double *value) {
	assert(!size || value);
	_resize(size);
	std::memcpy(_value, value, sizeof(double) * size);
}

void Vector::_deep_copy(const Vector &other) {
	_resize(other._size);
	for (int i = 0; i < _size; ++i) {
		_value[i] = other(i);
	}
}

Vector::Vector() : _size(0), _value(0) {}

Vector::Vector(const size_t size) : _size(0), _value(0) {
	_resize(size);
	_fill_zero();
}

Vector::Vector(const size_t size, const double *value) : _size(0), _value(0) {
	_deep_copy(size, value);
}

Vector::Vector(const Vector &other) : _size(0), _value(0) {
	_deep_copy(other);
}

Vector::~Vector() {
	_delete();
}

size_t Vector::get_size() const {
	return _size;
}

const double Vector::operator () (const size_t idx) const {
	assert(_is_ok());
	assert(_bounds_check(idx));
	return _value[idx];
}

double& Vector::operator () (const size_t idx) {
	assert(_is_ok());
	assert(_bounds_check(idx));
	return _value[idx];
}

double Vector::norm() const {
	assert(_is_ok());
	if (!_size) {
		return 0;
	}
	double n = std::abs(_value[0]);
	for (int i = 1; i < _size; ++i) {
		double abs_value = std::abs(_value[i]);
		if (abs_value > n) {
			n = abs_value;
		}
	}
	return n;
}

Vector Vector::operator = (const Vector &other) {
	if (this != &other) {
		_deep_copy(other);
	}
	return *this;
}

bool Vector::operator == (const Vector &other) const {
	assert(_is_ok());
	if (_size != other._size) {
		return 0;
	}
	for (int i = 0; i < _size; ++i) {
		if (_value[i] != other(i)) {
			return 0;
		}
	}
	return 1;
}

bool Vector::operator != (const Vector &other) const {
	return !(*this == other);
}

Vector operator + (const Vector &vector) {
	return vector;
}

Vector Vector::operator + (const Vector &other) {
	assert(_is_ok());
	assert(_size == other._size);
	Vector sum(*this);
	for (int i = 0; i < _size; ++i) {
		sum(i) += other(i);
	}
	return sum;
}

Vector Vector::operator += (const Vector &other) {
	assert(_is_ok());
	assert(_size == other._size);
	for (int i = 0; i < _size; ++i) {
		_value[i] += other(i);
	}
	return *this;
}

Vector operator - (const Vector &vector) {
	Vector neg(vector._size);
	neg -= vector;
	return neg;
}

Vector Vector::operator - (const Vector &other) {
	assert(_is_ok());
	assert(_size == other._size);
	Vector sum(*this);
	for (int i = 0; i < _size; ++i) {
		sum(i) -= other(i);
	}
	return sum;
}

Vector Vector::operator -= (const Vector &other) {
	assert(_is_ok());
	assert(_size == other._size);
	for (int i = 0; i < _size; ++i) {
		_value[i] -= other(i);
	}
	return *this;
}

Vector operator * (const double a, const Vector &vector) {
	return vector * a;
}

Vector Vector::operator * (const double a) const {
	Vector mul(*this);
	for (int i = 0; i < _size; ++i) {
		mul(i) *= a;
	}
	return mul;
}

Vector Vector::operator *= (const double a) {
	assert(_is_ok());
	for (int i = 0; i < _size; ++i) {
		_value[i] *= a;
	}
	return *this;
}

Vector Vector::operator / (const double a) const {
	assert(a);
	return *this * (1 / a);
}

Vector Vector::operator /= (const double a) {
	assert(_is_ok());
	assert(a);
	(*this) *= (1 / a);
}

double Vector::dot_product(const Vector &other) const {
	assert(_is_ok());
	assert(_size == other._size);
	double prod = 0;
	for (int i = 0; i < _size; ++i) {
		prod += _value[i] * other(i);
	}
	return prod;
}

double dot_product(const Vector &a, const Vector &b) {
	return a.dot_product(b);
}

Vector Vector::project(const Vector &other) {
	assert(_is_ok());
	assert(_size == other._size);
	double c1 = dot_product(other);
	double c2 = dot_product(*this);
	return other * c1 / c2;
}

string Vector::repr() const {
	assert(_is_ok());

	if (!_size) {
		return string("");
	}

	string rep;
	for (int i = 0; i < _size - 1; ++i) {
		rep += to_string(_value[i]) + string(" ");
	}
	rep += to_string(_value[_size - 1]);
	return rep;
}

std::ostream& operator << (std::ostream &out, const Vector &vector) {
	return out << vector.repr();
}


// implementations for class Matrix

bool Matrix::_is_ok() const {
	return !_size || _value;
}

bool Matrix::_bounds_check(const size_t row, const size_t col) const {
	return row >= 0 && row < _size && col >= 0 && col < _size;
}

void Matrix::_resize(size_t size) {
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

void Matrix::_delete() {
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

void Matrix::_fill_zero() {
	assert(_is_ok());
	for (int i = 0; i < _size; ++i) {
		fill_n(_value[i], _size, 0);
	}
}

void Matrix::_deep_copy(const size_t size, const double *value) {
	assert(!size || value);
	_resize(size);
	for (int i = 0; i < _size; ++i) {
		memcpy(_value[i], value + i * _size, sizeof(double) * size);
	}
}

void Matrix::_deep_copy(const Matrix &other) {
	_resize(other._size);
	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < _size; ++j) {
			_value[i][j] = other(i, j);
		}
	}
}

Matrix::Matrix() : _size(0), _value (0) {}

Matrix::Matrix(const size_t size) : _size(0), _value(0) {
	_resize(size);
	_fill_zero();
}

Matrix::Matrix(const size_t size, const double *value) : _size(0), _value(0) {
	_deep_copy(size, value);
}

Matrix::Matrix(const Matrix &other) : _size(0), _value(0) {
	_deep_copy(other);
}

Matrix::~Matrix() {
	_delete();
}

size_t Matrix::get_size () const {
	return _size;
}

const double Matrix::operator () (const size_t row, const size_t col) const {
	assert(_is_ok());
	assert(_bounds_check(row, col));
	return _value[row][col];
}

double& Matrix::operator () (const size_t row, const size_t col) {
	assert(_is_ok());
	assert(_bounds_check(row, col));
	return _value[row][col];
}

double Matrix::norm() const {
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

Matrix Matrix::operator = (const Matrix &other) {
	if (this != &other) {
		_deep_copy(other);
	}
	return *this;
}

Vector Matrix::operator * (const Vector &other) const {
	assert(_size == other._size);
	Vector result(_size);
	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < _size; ++j) {
			result(i) += _value[i][j] * other(j);
		}
	}
	return result;
}

Matrix Matrix::operator * (const Matrix &other) const {
	assert(_size == other._size);
	Matrix result(_size);
	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < _size; ++j) {
			for (int k = 0; k < _size; ++k) {
				result(i, j) += _value[i][k] * other(k, j);
			}
		}
	}
	return result;
}

string Matrix::repr() const {
	assert(_is_ok());

	if (!_size) {
		// empty matrix
		return string("");
	}

	string rep;
	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < _size - 1; ++j) {
				rep += to_string(_value[i][j]) + string(" ");
			}
		rep += to_string(_value[i][_size - 1]);
		rep += string((i != _size - 1), '\n');
	}

	return rep;
}

std::ostream& operator << (std::ostream &out, const Matrix &matrix) {
	return out << matrix.repr();
}

void Matrix::swap_rows(const size_t i, const size_t j) {
	for (int k = 0; k < _size; ++k) {
		swap(_value[i][k], _value[j][k]);
	}
}

void Matrix::transpose() {
	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < _size; ++j) {
			swap(_value[i][j], _value[j][i]);
		}
	}
}

Matrix Matrix::transposed() const {
	Matrix t(*this);
	t.transpose();
	return t;
}

double Matrix::mu() const {
	return this->norm() * this->inverse().norm();
}

// !!! all this has to be rewritten
void Matrix::find_max_and_swap(Vector &b, int j) {
	int max_index = j;
	for (int i = j + 1; i < _size; ++i) {
		if (_value[i][j] > _value[max_index][j]) {
			max_index = i;
		}
	}
	if (max_index != j) {
		double temp;
		swap_rows(max_index, j);
		swap(b(j), b(max_index));
	}
}

Vector Matrix::get_answer_from_triangle(const Vector &b) {
	Vector result(_size);
	double temp;
	for (int j = _size-1; j >= 0; j--) {
		temp = b(j);
		for (int i = j + 1; i < _size; ++i) {
			temp -= _value[j][i] * result(i);
		}
		result(j) = temp / _value[j][j];
	}
	return result;
}

Matrix Matrix::inverse() const{
	Matrix m;
	Vector answer(_size);
	double coeff;
	double* a = new double [_size*_size];
	for (int k = 0; k < _size; ++k) {
		m = *this;
		Vector b(_size);
		b(k) = 1;

		for (int j = 0; j < _size; ++j) {
			m.find_max_and_swap(b, j);
			for (int i = j + 1; i < _size; ++i) {
				coeff = m(i, j) / m(j, j);
				m.sub(&b, i, j, coeff);
			}
		}
		answer = m.get_answer_from_triangle(b);
		for (int l = 0; l < _size; ++l) {
			a[k + l * _size] = answer(l);
		}
	}
	Matrix M(_size,a);
	delete[] a;
	return M;
}

Matrix Matrix::ort() const {
	double* a = new double [_size*_size];
	double* add = new double [_size];
	double coeff1;
	double coeff2;
	for (int j = 0; j  < _size ; ++j) {
		fill_n(add, _size, 0);

		for (int k = 0; k < j; ++k) {
			coeff1 = 0;
			coeff2 = 0;
			for (int l = 0;  l < _size; ++l) {
				coeff1 += _value[l][j] * a[l * _size + k];
				coeff2 += a[l * _size + k] * a[l * _size + k];
			}
			coeff1 = coeff1 / coeff2;
			for (int l = 0; l < _size; ++l) {
				add[l] -= coeff1 * a[l*_size + k];
			}
		}

		for (int l = 0; l < _size; ++l) {
			a[l * _size + j] = _value[l][j] + add[l];
		}
		coeff1 = 0;
		for (int l = 0; l < _size; ++l) {
			coeff1 += a[l * _size + j] * a[l * _size + j];
		}
		coeff1 = sqrt(coeff1);
		for (int l = 0; l < _size; ++l) {
			a[l * _size + j] /= coeff1;
		}
	}
	Matrix M(_size, a);
	delete[] a;
	delete[] add;
	return M;
}

// !!! this should not be member of class matrix
void Matrix::sub(Vector* b, int k, int l, double coeff) const{
	for (int i = 0; i < _size; ++i) {
		_value[k][i] -= _value[l][i] * coeff;
	}
	(*b)(k) -= (*b)(l) * coeff;
}

#endif  // __LINEAR_ALGEBRA_CPP__
