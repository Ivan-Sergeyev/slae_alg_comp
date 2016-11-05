#ifndef __GENERATE_PLOTFILE__
#define __GENERATE_PLOTFILE__

#include "generic_method.h"


const int FILENAME_BUFFER_LEN = 200;


void generate_plotfile(const char *plot_filename, const char *graph_filename,
					   const char *data_filename_format,
					   const int num_methods, const GenericMethod *methods) {
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
	const char method_format_string[] =
		"file_%d = \"%s\"\n"
		"title_%d = \"%s\"\n"
		"a_%d = 1; b_%d = 1; c_%d = 1\n"
		"f_%d(x) = a_%d*x**2 + b_%d*x + c_%d\n"
		"fit f_%d(x) file_%d using 1:2 "
		"via a_%d, b_%d, c_%d\n\n";
	const char plot_format_string[] =
		"\tfile_%d using 1:2 with points "
		"lw 1 lt 1 lc %d title title_%d,\\\n"
		"\tf_%d(x) with lines "
		"lw 1 lt 1 lc %d notitle";

	FILE *plot_file = fopen(plot_filename, "w");

	fprintf(plot_file, plot_preamble, graph_filename);

	char *data_relpath = new char [FILENAME_BUFFER_LEN];
	for(int i = 0; i < num_methods; ++i) {
		const char *method_name = methods[i].get_name();

		data_relpath[0] = 0;
		sprintf(data_relpath, data_filename_format, method_name);

		fprintf(plot_file, method_format_string,
			i, data_relpath, i, method_name,
			i, i, i, i, i, i, i, i, i, i, i, i);
	}
	delete[] data_relpath;

	fprintf(plot_file, "plot \\\n");
	for(int i = 0; i < num_methods - 1; ++i) {
		int idx = i;
		fprintf(plot_file, plot_format_string, idx, idx, idx, idx, idx);
		fprintf(plot_file, ",\\\n");
	}
	int idx = num_methods - 1;
	fprintf(plot_file, plot_format_string, idx, idx, idx, idx, idx);
	fprintf(plot_file, "\n");

	fclose(plot_file);
}

#endif  // __GENERATE_PLOTFILE__
