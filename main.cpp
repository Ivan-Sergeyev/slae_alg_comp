#include <cstdio>
//#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "model/generic_method.h"
#include "model/gauss_method.h"
#include "model/jacobi_method.h"
#include "model/overrelaxation_method.h"

#include "model/performance_comparator.h"

#include "model/generate_plotfile.h"


// #define NDEBUG  // disable tests and asserts for release

#ifndef NDEBUG  // debug version

#include "model/linear_algebra_test.h"


void test() {
	typedef int (*test_funcion_pointer)();

	const int num_modules = 1;
	string module_name[num_modules] = {string("linear_algebra")};
	test_funcion_pointer module_test[num_modules] =
		{linear_algebra_test::test};

	int total_fails = 0;
	for (int i = 0; i < num_modules; ++i)
	{
		cout << "testing " << module_name[i] << "\n";
		cout << "===========================================================\n";
		int num_fails = module_test[i]();
		cout << "===========================================================\n";
		cout << num_fails << " fails in " << module_name[i] << "\n\n";
		total_fails += num_fails;
	}
	cout << "total fails: " << total_fails << "\n";
}

#endif // NDEBUG


int main(int argc, char **argv) {
#ifndef NDEBUG
	if (argc == 2 && !strcmp(argv[1], "test")) {
		test();
		return 0;
	}
#endif  // NDEBUG

// setup
	printf("setup\n");

	const int num_sizes = 1;
	int sizes[num_sizes];
	for (int i = 0; i < num_sizes; ++i) {
		sizes[i] = i * 100 + 100;
	}

	const int num_runs = 10;

	const double tolerance = 0.0078125;  // 2^{-7}
	const int max_faults = 20;

	const int num_methods = 4;
	JacobiMethod jacobi_method(tolerance, max_faults);
	OverrelaxationMethod gauss_seidel_method(1.0, tolerance, max_faults),
						 lower_relaxation_method(0.5, tolerance, max_faults),
						 upper_relaxation_method(1.5, tolerance, max_faults);

	GenericMethod **methods = new GenericMethod* [num_methods];
	methods[0] = &jacobi_method;
	cout << "added " << methods[0]->get_name() << "\n";
	methods[1] = &gauss_seidel_method;
	cout << "added " << methods[1]->get_name() << "\n";
	methods[2] = &lower_relaxation_method;
	cout << "added " << methods[2]->get_name() << "\n";
	methods[3] = &upper_relaxation_method;
	cout << "added " << methods[3]->get_name() << "\n";

// perform measurements
	printf("measurements\n");
	string data_filename_format = string("./data/data_%s_%s.txt");

	PerformanceComparator p_comp;
	p_comp.run_comparison(num_methods, methods, num_sizes, sizes,
						  num_runs, data_filename_format);

// prepare plot and run gnuplot
	printf("generate plotfile\n");

	// beginstab
	string plot_full_path = string("./gnuplot/plot_converged.plt"),
		   graph_rel_path = string("../graphs/graph_converged.png"),
		   data_filename_relformat = string("../data/data_converged_%s.txt");
	// endstab

	generate_plotfile(plot_full_path, graph_rel_path,
					  data_filename_relformat, num_methods, methods);

// run gnuplot with plot_dir as current directory
	printf("plot graph\n");
	const char gnuplot_call[] = "gnuplot plot_converged.plt";

	chdir("./gnuplot/");
	system(gnuplot_call);
	remove("fit.log");
	chdir("..");

// perform cleanup
	printf("cleanup\n");
	delete[] methods;

	printf("done\n");
	return 0;
}
