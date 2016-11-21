#ifndef __LINEAR_ALGEBRA_H__
#define __LINEAR_ALGEBRA_H__

#include <iostream>
#include <string>


using std::string;


class Vector {
public:
	size_t _size;
	double* _value;

private:
	bool _is_ok() const;
	bool _bounds_check(const size_t) const;

	void _resize(const size_t);
	void _delete();
	void _fill_zero();

	void _deep_copy(const size_t, const double*);
	void _deep_copy(const Vector&);

public:
	Vector();
	Vector(const size_t);
	Vector(const size_t, const double*);
	Vector(const Vector&);

	~Vector();

	size_t get_size() const;
	const double operator () (const size_t) const;
	double& operator () (const size_t);
	double norm() const;

	Vector operator = (const Vector&);

	bool operator == (const Vector&) const;
	bool operator != (const Vector&) const;

	friend Vector operator + (const Vector&);
	Vector operator + (const Vector&);
	Vector operator += (const Vector&);

	friend Vector operator - (const Vector&);
	Vector operator - (const Vector&);
	Vector operator -= (const Vector&);

	friend Vector operator * (const double, const Vector&);
	Vector operator * (const double) const;
	Vector operator *= (const double);

	Vector operator / (const double) const;
	Vector operator /= (const double);

	double dot_product(const Vector&) const;
	friend double dot_product(const Vector&, const Vector&);

	Vector project(const Vector&);

	string repr() const;
	friend std::ostream& operator << (std::ostream&, const Vector&);
};


class Matrix {
public:
	size_t _size;
	double** _value;

private:
	bool _is_ok() const;
	bool _bounds_check(const size_t, const size_t) const;

	void _resize(const size_t);
	void _delete();
	void _fill_zero();

	void _deep_copy(const size_t, const double*);
	void _deep_copy(const Matrix&);

public:
	Matrix();
	Matrix(const size_t);
	Matrix(const size_t, const double*);
	Matrix(const Matrix&);
	~Matrix();

	size_t get_size () const;
	const double operator () (const size_t, const size_t) const;
	double& operator () (const size_t, const size_t);
	double norm() const;
	double mu() const;

	Matrix operator = (const Matrix&);

	Vector operator * (const Vector&) const;
	Matrix operator * (const Matrix&) const;

	void swap_rows(const size_t, const size_t);
	void transpose();
	Matrix transposed() const;

	string repr() const;
	friend std::ostream& operator << (std::ostream&, const Matrix&);

// !!! all this has to be rewritten
	void find_max_and_swap(Vector&, int);
	Vector get_answer_from_triangle(const Vector&);
	Matrix inverse() const;
	Matrix ort() const;

// !!! this should not be member of class matrix
 	void sub(Vector*, int, int, double) const;
};

#endif  // __LINEAR_ALGEBRA_H__
