#include <assert.h>
#include <string>
#include <iostream>

#include "model/generic_method.h"
#include "model/gauss_method.h"
#include "model/jacobi_method.h"
#include "model/overrelaxation_method.h"

#include "model/performance_comparator.h"


using std::cerr;
using std::system;


// #define NDEBUG  // disable tests and asserts in release build

#ifndef NDEBUG
#include "test/project_test.h"
#endif // NDEBUG


int main(int argc, char **argv) {
#ifndef NDEBUG
	if (argc == 2 && string(argv[1]) == string("test")) {
		cerr << "[info] commence testing\n";
		project_test();
		return 0;
	}
#endif  // NDEBUG

// setup
	cerr << "[info] commence setup\n";

	// set parameters for numeric algorithms
	double tolerance = 0.0078125;  // 2^{-7}

	// populate mathods
	int num_or_methods = 2 + 3,  // number of overrelaxation methods
		num_methods = num_or_methods + 2;  // total number of methods

	GenericMethod **methods = new GenericMethod* [num_methods];
	int m_idx = 0;

	// add overrelaxation methods
	double tau = 0.0l;
	double tau_step = 1.0l / (num_or_methods - 1);
	for(; m_idx < num_or_methods; ++m_idx) {
		tau += (tau < 1.0l) * 0.5l + (tau >= 1.0l) * tau_step;
		methods[m_idx] = new OverrelaxationMethod(tau, tolerance);
		cerr << "[info] added " << methods[m_idx]->get_name() << "\n";
	}

	// add jacobi method
	JacobiMethod jacobi_method(tolerance);
	methods[m_idx] = &jacobi_method;
	cerr << "[info] added " << methods[m_idx]->get_name() << "\n";
	++m_idx;

	// add gauss method
	GaussMethod gauss_method;
	methods[m_idx] = &gauss_method;
	cerr << "[info] added " << methods[m_idx]->get_name() << "\n";
	++m_idx;

	// check that number of added methods is correct
	assert(m_idx == num_methods);

// perform measurements
	cerr << "[info] commence measurements\n";
	system("mkdir temp_data");

	// todo: use format strings
	string data_fname_fmt = string("./temp_data/data_%s_%s.txt");

	if (argc == 2) {  // special run
		string option = string(argv[1]);
		if (option == string("test_run")) {
			cerr << "[info] performing test run\n";
			PerformanceComparator comp_test(cerr, string("test run"));
			comp_test.run_comparison(num_methods, methods, data_fname_fmt);
		} else if (option == string("tiny")) {
			cerr << "[info] performing run on tiny sizes\n";
			PerformanceComparator comp_tiny(cerr, string("tiny sizes"));
			comp_tiny.run_comparison(num_methods, methods, data_fname_fmt);
		} else {
			cerr << "[error] option \"" << option << "\" not recognized\n";
		}
	} else {  // normal run
		cerr << "[info] running on small sizes\n";
		PerformanceComparator comp_small(cerr, string("small sizes"));
		comp_small.run_comparison(num_methods, methods, data_fname_fmt);

		cerr << "[info] running on large sizes\n";
		PerformanceComparator comp_large(cerr, string("large sizes"));
		comp_large.run_comparison(num_methods - 1, methods, data_fname_fmt);
	}

// perform cleanup
	cerr << "[info] commence cleanup\n";
	delete[] methods;

	cerr << "[info] done\n";
	return 0;
}
