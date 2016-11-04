#ifndef __GENERATE_PLOTFILE__
#define __GENERATE_PLOTFILE__


void generate_plotfile() {
	const char plot_preamble[] =
		"reset\n\n"
		"set output \"%0$s\"\n"
		"set terminal pngcairo dashed enhanced font \"Sans,12\" size 1000,600\n"
		"set encoding utf8\n\n"
		"set key top left\n"
		"set grid\n"
		"set xlabel \"N\" offset 0,0.5,0\n"
		"set ylabel \"T, s\" offset 2,0,0\n\n"
		"set fit quiet\n\n";
	const char method_format_string[] =
		"file_%0$s = \"%2$s\"\n"
		"title_%0$s = \"%1$s\"\n"
		"a_%0$s = 1; b_%0$s = 1; c_%0$s = 1\n"
		"f_%0$s(x) = a_%0$s*x**2 + b_%0$s*x + c_%0$s\n"
		"fit f_%0$s(x) file_%0$s using 1:2 "
		"via a_%0$s, b_%0$s, c_%0$s\n\n";
	const char plot_format_string[] =
		"\tfile_%0$s using 1:2 with points "
		"lw 1 lt 1 lc %0$s title title_%0$s,\\\n"
		"\tf_%0$s(x) with lines "
		"lw 1 lt 1 lc %0$s notitle";

	// TODO
}

#endif  // __GENERATE_PLOTFILE__
