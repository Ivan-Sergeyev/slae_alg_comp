#include <string.h>
#include <stdio.h>

#include "model/linear_algebra.h"
#include "model/generic_method.h"
#include "model/jacobi_method.h"
#include "model/seidel_method.h"


void generate_plot_file() {
	const char plot_preamble[] =
		"reset\n\n"
		"set output \"%s\"\n"
		"set terminal pngcairo dashed enhanced font \"Sans,12\" size 1000,600\n"
		"set encoding utf8\n\n"
		"set key top left\n"
		"set grid\n"
		"set xlabel \"N\" offset 0,0.5,0\n"
		"set ylabel \"T, s\" offset 2,0,0\n\n"
		"set fit quiet\n\n";
	const char method_format_string[] = "TODO";
	const char plot_format_string[] = "TODO";

	// TODO
}


int main(int argc, char **argv) {
	if (argc == 2 && !strcmp(argv[1], "test")) {
	// run tests
		printf("test\n");
		// TODO
		return 0;
	}

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

	int num_methods = 2;
	GenericMethod methods[num_methods];
	methods[0] = JacobiMethod();
	printf("added %s\n", methods[0].getName());
	methods[1] = SeidelMethod();
	printf("added %s\n", methods[1].getName());

// measurements
	printf("measurements\n");
	// TODO

// plot
	printf("plot\n");
	// TODO

// cleanup
	printf("cleanup\n");
	delete[] list_sizes;

	printf("done\n");
	return 0;
}
