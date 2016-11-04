#include <cstdio>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model/generic_method.h"
#include "model/jacobi_method.h"
#include "model/overrelaxation_method.h"
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

	const char plot_dir[] = "./gnuplot/",
			   graphs_dir[] = "./graphs/",
			   data_dir[] = "./data/";

	const char data_filename_format[] = "data_%s_%s.txt",
			   plot_filename_format[] = "plot_%s.plt",
			   graph_filename_format[] = "graph_%s.png";

	const int num_sizes = 50;

	int *list_sizes = new int [num_sizes];
	for (int i = 0; i < num_sizes; ++i) {
		list_sizes[i] = (i + 1) * 100;
	}

	const int num_runs = 10;
	const double tolerance = 0.01;

	const int num_methods = 4;
	GenericMethod *methods = new GenericMethod [num_methods];
	methods[0] = JacobiMethod();
	printf("added %s\n", methods[0].get_name());
	methods[1] = OverrelaxationMethod(1.0);
	printf("added %s\n", methods[1].get_name());
	methods[2] = OverrelaxationMethod(0.5);
	printf("added %s\n", methods[2].get_name());
	methods[3] = OverrelaxationMethod(1.5);
	printf("added %s\n", methods[3].get_name());

// perform measurements
	printf("measurements\n");
	// TODO

// prepare plot and run gnuplot
	printf("generate plotfile\n");

	// beginstab
	const char plot_filename[] = "plot_converged.plt",
			   graphs_reldir[] = "../graphs/",
			   graph_filename[] = "graph_converged.png",
			   data_reldir[] = "../data/",
			   data_filename_result_format[] = "data_converged_%s.txt";
	// endstab

	generate_plotfile(
		plot_filename, plot_dir, graphs_reldir, graph_filename, data_reldir,
		data_filename_result_format, num_methods, methods);

// run gnuplot with plot_dir as current directory
	printf("plot graph\n");

	_chdir(plot_dir);
	char *gnuplot_call = new char [200];
	sprintf(gnuplot_call, "gnuplot  %s", plot_filename);
	system(gnuplot_call);
	remove("fit.log");
	_chdir("..");

// perform cleanup
	printf("cleanup\n");
	delete[] list_sizes;

	printf("done\n");
	return 0;
}
