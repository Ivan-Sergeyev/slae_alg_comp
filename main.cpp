#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <unistd.h>

#include "model/generic_method.h"
#include "model/gauss_method.h"
#include "model/jacobi_method.h"
#include "model/overrelaxation_method.h"

#include "model/performance_comparator.h"

#include "model/generate_plotfile.h"


using std::cerr;
using std::system;


// #define NDEBUG  // disable tests and asserts for release

#ifndef NDEBUG  // debug version

#include "test/linear_algebra_test.h"
#include "test/jacobi_method_test.h"
#include "test/overrelaxation_method_test.h"


void test() {
	typedef int (*test_funcion_pointer)();

	const int num_modules = 3;
	string module_name[num_modules] = \
		{string("linear_algebra"), string("jacobi_method"),
		 string("overrelaxation_method")};
	test_funcion_pointer module_test[num_modules] =
		{linear_algebra_test::test, jacobi_method_test::test,
		 overrelaxation_method_test::test};

	string separator(79, '=');

	int total_fails = 0;
	for (int i = 0; i < num_modules; ++i)
	{
		cerr << "testing " << module_name[i] << "\n";
		cerr << separator << "\n";
		int num_fails = module_test[i]();
		cerr << separator << "\n";
		cerr << num_fails << " fails in " << module_name[i] << "\n\n";
		total_fails += num_fails;
	}
	cerr << "total fails: " << total_fails << "\n";
}

#endif // NDEBUG


void fill_arithm_progr(int *sizes, int num_elems, int start, int step) {
	int size = start;
	for (int idx = 0; idx < num_elems; ++idx, size += step) {
		sizes[idx] = size;
	}
}


void fill_geom_progr(double *sizes, int num_elems, double start, double mul) {
	double size = start;
	for (int idx = 0; idx < num_elems; ++idx, size *= mul) {
		sizes[idx] = size;
	}
}


int main(int argc, char **argv) {
#ifndef NDEBUG
	if (argc == 2 && string(argv[1]) == string("test")) {
		cerr << "[info] commence testing\n";
		test();
		return 0;
	}
#endif  // NDEBUG

// setup
	cerr << "[info] commence setup\n";

	// populate a list of small sizes
	int small_num_sizes = 30,
		small_start = 100,
		small_step = 100;
	int small_sizes[small_num_sizes];
	fill_arithm_progr(small_sizes, small_num_sizes, small_start, small_step);

	// populate a list of large sizes
	int large_num_sizes = 50,
		large_start = 3100,
		large_step = 100;
	int large_sizes[large_num_sizes];
	fill_arithm_progr(large_sizes, large_num_sizes, large_start, large_step);

	// populate a list of condition numbers
	int num_mus = 7;
	double mu_start = 1,
		   mu_mul = 10;
	double mus[num_mus];
	fill_geom_progr(mus, num_mus, mu_start, mu_mul);

	if (argc == 2 && string(argv[1]) == string("test_run")) {
		// only run on small number of tests
		cerr << "[info] test_run mode enabled\n";
		small_num_sizes = 1;
		large_num_sizes = 0;
	}

	// set number of runs for each size and condition number
	int num_runs = 10;

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
	assert(m_idx == num_methods);

// perform measurements
	cerr << "[info] commence measurements\n";
	// todo: use format strings
	string data_filename_format = string("./temp_data/data_%s_%s.txt");

	PerformanceComparator p_comp(cerr);
	p_comp.run_comparison(num_methods, methods,
						  small_num_sizes, small_sizes,
						  num_mus, mus,
						  num_runs, data_filename_format);

	p_comp.run_comparison(num_methods - 1, methods,
						  large_num_sizes, large_sizes,
						  num_mus, mus,
						  num_runs, data_filename_format);

// prepare plot and run gnuplot
	cerr << "[info] commence generating plotfiles\n";

	// todo: use format strings
	string plot_all = string("./temp_gnuplot/plot_all.plt"),
		   graph_all_rel = string("../temp_graphs/graph_all.png"),
		   data_format_rel = string("../temp_data/data_converged_%s.txt");

	generate_plotfile(plot_all, graph_all_rel,
					  data_format_rel, num_methods, methods);

	string plot_num = string("./temp_gnuplot/plot_num.plt"),
		   graph_num_rel = string("../temp_graphs/graph_num.png");

	generate_plotfile(plot_num, graph_num_rel,
					  data_format_rel, num_methods - 1, methods);

// run gnuplot with plot_dir as current directory
	cerr << "[info] commence plotting graphs\n";
	// todo: concatenate commands
	const char gnuplot_call_all[] = "gnuplot plot_all.plt";
	const char gnuplot_call_num[] = "gnuplot plot_num.plt";

	chdir("./temp_gnuplot/");
	int status_1 = system(gnuplot_call_all);
	int status_2 = system(gnuplot_call_num);
	remove("fit.log");
	chdir("..");

	if (status_1) {
		cerr << "[error] error during system(\"" << gnuplot_call_all << "\")\n"
			 << "        exit status " << status_1 << "\n";
	}
	if (status_2) {
		cerr << "[error] error during system(\"" << gnuplot_call_num << "\")\n"
			 << "        exit status " << status_2 << "\n";
	}

// perform cleanup
	cerr << "[info] commence cleanup\n";
	delete[] methods;

	cerr << "[info] done\n";
	return 0;
}
