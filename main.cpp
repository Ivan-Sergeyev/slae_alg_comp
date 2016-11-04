#include <string.h>
#include <stdio.h>

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
		int num_fails = module_test[i]();
		if (num_fails) {
			printf("%d fails in %s\n", num_fails, module_name[i]);
			total_fails += num_fails;
		}
	}
	printf("\ntotal fails: %d\n", total_fails);
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

	int num_sizes = 50;

	int *list_sizes = new int [num_sizes];
	for (int i = 0; i < num_sizes; ++i) {
		list_sizes[i] = (i + 1) * 100;
	}

	int num_runs = 10;
	double tolerance = 0.01;

	int num_methods = 4;
	GenericMethod methods[num_methods];
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
	generate_plotfile();
	printf("plot\n");
	// TODO

// perform cleanup
	printf("cleanup\n");
	delete[] list_sizes;

	printf("done\n");
	return 0;
}
