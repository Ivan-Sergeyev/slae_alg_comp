#ifndef __GENERATE_PLOTFILE__
#define __GENERATE_PLOTFILE__


void generate_plotfile() {
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

#endif  // __GENERATE_PLOTFILE__
