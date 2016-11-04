#ifndef __GENERIC_METHOD__
#define __GENERIC_METHOD__

#include <string.h>

#include "linear_algebra.h"


class GenericMethod {
private:
	int _name_len;
	char *_name;

	bool _is_ok() const {
		return !_name_len || _name;
	}

	void _set_name(const char *name) {
		assert(name);
		int new_len = strlen(name);
		if (_name_len != new_len) {
			_delete();
			_name = new char [new_len];
		}
		strcpy(_name, name);
		_name_len = new_len;
	}

	void _deep_copy(const GenericMethod &other) {
		const char *new_name = other.get_name();
		_set_name(new_name);
	}

	void _delete() {
		if (_name) {
			delete[] _name;
		}
		_name = 0;
		_name_len = 0;
	}

public:
	GenericMethod() : _name_len(0), _name(0) {}

	GenericMethod(const char *name) : _name_len(0), _name(0) {
		_set_name(name);
	}

	~GenericMethod() {
		_delete();
	}

	void set_name(const char *name) {
		_set_name(name);
	}

	const char* get_name() const {
		assert(_is_ok());
		return _name;
	}

	GenericMethod& operator = (const GenericMethod &other) {
		if (this != &other) {
			_deep_copy(other);
		}
		return *this;
	}

	virtual Vector run(int n, Matrix A, Vector f,
					   Vector u_0, double tolerance) const {}
};

#endif  // __GENERIC_METHOD__
