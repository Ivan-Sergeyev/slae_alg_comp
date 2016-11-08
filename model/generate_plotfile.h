#ifndef __GENERATE_PLOTFILE__
#define __GENERATE_PLOTFILE__

#include <fstream>
#include <string>

#include "generic_method.h"


using std::fstream;
using std::string;


void generate_plotfile(string plot_filename, string graph_filename,
					   string data_filename_format,
					   const int num_methods, GenericMethod **methods) {
	fstream plot_file;
	plot_file.open(plot_filename, fstream::out);

	plot_file <<
		"reset\n\n"
		"set output \"" << graph_filename << "\"\n"
		"set terminal pngcairo dashed enhanced font \"Sans,12\" size 1000,600\n"
		"set encoding utf8\n\n"
		"set key top left\n"
		"set grid\n"
		"set xlabel \"N\" offset 0,0.5,0\n"
		"set ylabel \"T, s\" offset 2,0,0\n\n"
		"set fit quiet\n\n";

	for(int i = 0; i < num_methods; ++i) {
		string method_name = methods[i]->get_name();

		// TODO: use format string
		string data_relpath = string("../data/data_converged_") +
							  method_name + string(".txt");

		plot_file <<
			"file_" << i << " = \"" << data_relpath << "\"\n"
			"title_" << i << " = \"" << method_name << "\"\n"
			"a_" << i << " = 1; b_" << i << " = 1; c_" << i << " = 1\n"
			"f_" << i << "(x) = a_" << i << "*x**2 + b_" << i << "*x + c_" << i << "\n"
			"fit f_" << i << "(x) file_" << i << " using 1:2 "
			"via a_" << i << ", b_" << i << ", c_" << i << "\n\n";
	}

	plot_file << "plot \\\n";
	for(int i = 0; i < num_methods; ++i) {
		int idx = i;
		plot_file <<
			"\tfile_" << idx << " using 1:2 with points "
			"lw 1 lt 1 lc " << idx << " title title_" << idx << ",\\\n"
			"\tf_" << idx << "(x) with lines "
			"lw 1 lt 1 lc " << idx << " notitle";
			if (i < num_methods - 1) {
				plot_file << ",\\";
			}
			plot_file << "\n";
	}

	plot_file.close();
}

#endif  // __GENERATE_PLOTFILE__
