#include <string.h>

#include "linear_algebra.h"


class GenericMethod {
private:
	char *_name;

public:
	GenericMethod(const char *name) {
		_name = new char [strlen(name)];
		strcpy(_name, name);
	}

	~GenericMethod() {
		delete[] _name;
	}

	const char* getName() const {
		return _name;
	}

	virtual Vector run(int n, Matrix A, Vector f, Vector u_0, double tolerance) const;
};
