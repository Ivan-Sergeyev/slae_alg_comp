#ifndef __PROJECT_TEST__
#define __PROJECT_TEST__

#include <iostream>
#include <string>

#include "linear_algebra_test.h"
#include "jacobi_method_test.h"
#include "overrelaxation_method_test.h"


using std::cerr;
using std::string;


void project_test() {
	typedef int (*test_funcion_pointer)();

	const int num_modules = 4;
	string module_name[num_modules] =
		{string("Vector"), string("Matrix"), /*, string("Gauss Method") */
		 string("Jacobi Method"), string("OverrelaxationMethod")};

	const test_funcion_pointer *module_tests[] =
		{linear_algebra_test::vector_tests, linear_algebra_test::matrix_tests,
		 jacobi_method_test::jacobi_method_tests,
		 overrelaxation_method_test::overrelaxation_method_tests};


	string separator(79, '=');

	int total_fails = 0;

	for(int module_idx = 0; module_idx < num_modules; ++module_idx) {
		string module = module_name[module_idx];
		int num_fails = 0;

		cerr << "testing " << module << "\n";
		cerr << separator << "\n";
		for (int test_idx = 0; module_tests[module_idx][test_idx]; ++test_idx) {
			cerr << "  test #" << test_idx << "\n";
			num_fails += module_tests[module_idx][test_idx]();
		}
		cerr << separator << "\n";
		cerr << "fails in " << module << ": " << num_fails << "\n\n";

		total_fails += num_fails;
	}

	cerr << "total fails: " << total_fails << "\n";
}


#endif // __PROJECT_TEST__
