#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <unistd.h>

#include "model/generators.h"
#include "model/generic_method.h"
#include "model/gauss_method.h"
#include "model/jacobi_method.h"
#include "model/overrelaxation_method.h"

#include "model/performance_comparator.h"

#include "model/generate_plotfile.h"


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

	string run_setting = string("full run");
	if (argc == 2 && string(argv[1]) == string("test_run")) {
		cerr << "[info] test run enabled\n";
		run_setting = string("test run");
	}

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

	// todo: use format strings
	string data_filename_format = string("./temp_data/data_%s_%s.txt");

	// run on small sizes
	PerformanceComparator small_comp(cerr,
									 string("small sizes"), run_setting);
	small_comp.run_comparison(num_methods, methods, data_filename_format);

	// run on large sizes
	PerformanceComparator large_comp(cerr,
									 string("large sizes"), run_setting);
	large_comp.run_comparison(num_methods - 1, methods, data_filename_format);

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
