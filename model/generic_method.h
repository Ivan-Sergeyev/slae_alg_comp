#ifndef __GENERIC_METHOD__
#define __GENERIC_METHOD__

#include <assert.h>
#include <algorithm>
#include <string>

#include "linear_algebra.h"


using std::string;
using std::to_string;


class GenericMethod {
private:
	string _name;

	bool _is_ok() const {
		return _name.length() >= 0;
	}

	void _set_name(string name) {
		_name = name;
	}

	void _deep_copy(const GenericMethod &other) {
		_set_name(other.get_name());
	}

	void _delete() {
		_name = string();
	}

public:
	GenericMethod() : _name() {}

	GenericMethod(string name) : _name() {
		_set_name(name);
	}

	~GenericMethod() {
		_delete();
	}

	void set_name(string name) {
		_set_name(name);
	}

	string get_name() const {
		assert(_is_ok());
		return _name;
	}

	GenericMethod operator = (const GenericMethod &other) {
		if (this != &other) {
			_deep_copy(other);
		}
		return *this;
	}

	virtual Vector run(const Matrix &A, const Vector &f) const {
		return Vector();
	}
};

#endif  // __GENERIC_METHOD__
