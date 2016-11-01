#ifndef __GENERIC_METHOD__
#define __GENERIC_METHOD__

#include <string.h>

#include "linear_algebra.h"


class GenericMethod {
private:
	int _name_len;
	char *_name;

	void _deep_copy(const GenericMethod &other) {
		const char *new_name = other.getName();
		int new_len = strlen(new_name);
		if (_name_len != new_len) {
			_delete();
			_name = new char[_name_len];
		}
		strcpy(_name, new_name);
	}

	void _delete() {
		delete[] _name;
		_name = 0;
	}

public:
	GenericMethod() : _name(0), _name_len(0) {}

	GenericMethod(const char *name) {
		_name_len = strlen(name);
		_name = new char [_name_len];
		strcpy(_name, name);
	}

	~GenericMethod() {
		_delete();
	}

	GenericMethod& operator = (const GenericMethod &other) {
		if (this != &other) {
			_deep_copy(other);
		}
		return *this;
	}

	const char* getName() const {
		return _name;
	}

	virtual Vector run(int n, Matrix A, Vector f,
					   Vector u_0, double tolerance) const {}
};

#endif  // __GENERIC_METHOD__
