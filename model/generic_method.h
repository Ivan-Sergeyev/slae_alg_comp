class GenericMethod {
	char *_name;

	GenericMethod(const char *name) {
		_name = name;
	}

	const char* getName() const {
		return _name;
	}

	virtual Vector run(int n, Matrix A, Vector f, Vector u_0, double tolerance) const;
}
