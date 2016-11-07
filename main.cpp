#include <cstdio>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	const char module_name[num_modules][20] = {"linear_algebra"};
	test_funcion_pointer module_test[num_modules] =
		{linear_algebra_test::test};

	int total_fails = 0;
	for (int i = 0; i < num_modules; ++i)
	{
		printf("testing %s\n", module_name[i]);
		printf("===========================================================\n");
		int num_fails = module_test[i]();
		printf("===========================================================\n");
		printf("%d fails in %s\n\n", num_fails, module_name[i]);
	}
	printf("total fails: %d\n", total_fails);
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
	int *sizes = new int [num_sizes];
	for (int i = 0; i < num_sizes; ++i) {
		sizes[i] = i * 100 + 1000;
	}

	const int num_runs = 10;

	const double tolerance = 0.01;
	const int max_faults = 20;
	const int num_methods = 4;

	JacobiMethod jacobi_method(tolerance, max_faults);
	OverrelaxationMethod gauss_seidel_method(1.0, tolerance, max_faults),
						 lower_relaxation_method(0.5, tolerance, max_faults),
						 upper_relaxation_method(1.5, tolerance, max_faults);

	GenericMethod **methods = new GenericMethod* [num_methods];
	methods[0] = &jacobi_method;
	printf("added %s\n", methods[0]->get_name());
	methods[1] = &gauss_seidel_method;
	printf("added %s\n", methods[1]->get_name());
	methods[2] = &lower_relaxation_method;
	printf("added %s\n", methods[2]->get_name());
	methods[3] = &upper_relaxation_method;
	printf("added %s\n", methods[3]->get_name());

// perform measurements
	printf("measurements\n");
	const char data_filename_format[] = "./data/data_%s_%s.txt";

	PerformanceComparator p_comp;
	p_comp.run_comparison(num_methods, methods, num_sizes, sizes,
						  num_runs, data_filename_format);

// prepare plot and run gnuplot
	printf("generate plotfile\n");

	// beginstab
	const char plot_full_path[] = "./gnuplot/plot_converged.plt",
			   graph_rel_path[] = "../graphs/graph_converged.png",
			   data_filename_relformat[] = "../data/data_converged_%s.txt";
	// endstab

	generate_plotfile(plot_full_path, graph_rel_path,
					  data_filename_relformat, num_methods, methods);

// run gnuplot with plot_dir as current directory
	printf("plot graph\n");
	const char gnuplot_call[] = "gnuplot plot_converged.plt";

	_chdir("./gnuplot/");
	system(gnuplot_call);
	remove("fit.log");
	_chdir("..");

// perform cleanup
	printf("cleanup\n");
	delete[] sizes;
	delete[] methods;

	printf("done\n");
	return 0;
}
