#ifndef __PERFORMANCE_COMPARATOR__
#define __PERFORMANCE_COMPARATOR__

#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

#include "generators.h"
#include "generic_method.h"
#include "linear_algebra.h"


using namespace std::chrono;

using std::cerr;
using std::istream;
using std::fstream;
using std::ostream;
using std::stod;
using std::string;
using std::to_string;


class PerformanceComparator {
private:
	ostream &_log_file;
	time_point<system_clock> _log_start_time;

	string _progress_filename;

	int _num_sizes;
	int *_sizes;
	int _num_mus;
	double *_mus;
	int _num_runs;

	string _timestamp(const time_point<system_clock> &time) const {
		auto time_diff = time - _log_start_time;

		string h = to_string(duration_cast<hours>(time_diff).count() % 100),
			   m = to_string(duration_cast<minutes>(time_diff).count() % 60),
			   s = to_string(duration_cast<seconds>(time_diff).count() % 60);

		h = string(2 - h.length(), '0') + h;
		m = string(2 - m.length(), '0') + m;
		s = string(2 - s.length(), '0') + s;

		const string begin = string("["),
					 end = string("]"),
					 sep = string(":");
		return begin + h + sep + m + sep + s + end;
	}

	void _write_log(string msg, int level=0) {
		assert(_log_file.good());

		string full_msg = _timestamp(system_clock::now()) + string(" ");

		if (level == 1) {
			full_msg += string("= ");
		} else if (level == 2) {
			full_msg += string("|- ");
		} else if (level == 3) {
			full_msg += string("|== ");
		} else if (level == 4) {
			full_msg += string("|--- ");
		}

		full_msg += msg;
		_log_file << full_msg;
	}

	bool _find_sm(int size, double mu, int &s_idx, int &mu_idx) {
		bool found = 0;
		for (int i = 0; i < _num_sizes; ++i) {
			if (_sizes[i] == size) {
				s_idx = i;
				found = 1;
				break;
			}
		}

		if (!found) {
			cerr << "size " << size << " not found in _sizes\n";
			return 0;
		}

		found = 0;
		for (int i = 0; i < _num_mus; ++i) {
			if (_mus[i] == mu) {
				mu_idx = i;
				found = 1;
				return 1;
			}
		}

		if (!found) {
			string msg = string("mu ") + to_string(mu) +
						 string("not found in _mus\n");
			_write_log(msg);
			return 0;
		}
		return 1;
	}

	bool _restore_progress(int &s_idx, int &mu_idx, int &r_idx) {
		std::ifstream progress_file(_progress_filename);

		if (!progress_file.is_open()) {
			cerr << "progress file does not exist\n";
			s_idx = mu_idx = r_idx = 0;
			return 1;
		}

		bool ret = 1;

		string str[3];
		double val[3];

		for (int i = 0; i < 3; ++i) {
			if (!(progress_file >> str[i])) {
				cerr << "reding from progress file failed\n";
				ret = 0;
				break;
			}

			if (str[i] == string("done")) {
				cerr << "measurements have already been done\n";
				ret = 0;
				break;
			}

			try {
				val[i] = stod(str[i]);
			} catch (...) {
				cerr << "could not convert \"" << val[i] << "\" to double\n";
				ret = 0;
				break;
			}
		}

		if (!ret) {
			progress_file.close();
			return 0;
		}

		int size = int(val[0]);
		double mu = val[1];
		r_idx = int(val[2]);

		if (!_find_sm(size, mu, s_idx, mu_idx)) {
			cerr << "one or more indices could not be determined\n";
			return 0;
		}

		cerr << "progress restored:"
			 << " s_idx = " << s_idx
			 << " mu_idx = " << mu_idx
			 << " r_idx = " << r_idx << "\n";
		progress_file.close();
		return 1;
	}

	void _update_progress(int s_idx, int mu_idx, int r_idx) {
		fstream progress_file(_progress_filename,
							  ostream::out | ostream::trunc);
		if (s_idx < _num_sizes) {
			progress_file << _sizes[s_idx] << " " << _mus[mu_idx] << " "
						  << r_idx << "\n";
		} else {
			progress_file << "done\n";
		}
		progress_file.close();
	}

	void _write_results_to_file(string data_filename, string results) {
		fstream data_file(data_filename, ostream::out | ostream::app);
		if (!(data_file.is_open())) {
			_log_file << "Error opening data file \"" << data_filename << "\"\n"
					  << "Data will be discarded\n";
			return;
		}

		data_file << results << "\n";
		data_file.close();
	}

	void _run_method(const GenericMethod *method, int size, double mu,
					 const Matrix &A, const Vector &f,
					 string data_filename_format) {
		auto t_start = high_resolution_clock::now();
		Vector answer = method->run(A, f);
		auto t_end = high_resolution_clock::now();

		auto elapsed_ns = duration_cast<nanoseconds>(t_end - t_start).count();
		double elapsed_s = (double)elapsed_ns / (double)1000000000;

		string results = to_string(size) + string(" ") + to_string(elapsed_s) +
						 string(" ") + to_string(mu);

		string verdict;
		if (answer._size == size) {
			verdict = string("converged");
		} else {
			verdict = string("diverged");
		}

		// todo: use data_filename_format
		string data_filename =
			string("./temp_data/data_") + verdict + string("_") +
			method->get_name() + string(".txt");

		_write_results_to_file(data_filename, results);
	}

	void _run_methods(int num_methods, GenericMethod **methods,
					  int size, double mu, Matrix A, Vector f,
					  string data_filename_format) {
		string msg = string("running methods") + string("\n");
		_write_log(msg, 0);

		for (int m_idx = 0; m_idx < num_methods; ++m_idx)
		{
			string m_name = methods[m_idx]->get_name();
			string msg = string("running ") + m_name + string("\n");
			_write_log(msg, 1);

			_run_method(methods[m_idx], size, mu, A, f,
						data_filename_format);
		}
	}

public:
	PerformanceComparator(ostream &log_file, string run_setting) :
			_log_file(log_file) {
		int small_num_sizes = 30,
			large_num_sizes = 50;

		// initialize _sizes and _num_sizes
		if (run_setting == string("test run")) {
			_progress_filename = string(".progress_test");

			_num_sizes = 1;
			int test_start = 100,
				test_step = 100;
			_sizes = new int [_num_sizes];

			generators::arithm_progr<int> (_sizes, _num_sizes,
										   test_start, test_step);
		} else if (run_setting == string("small sizes")) {
			_progress_filename = string(".progress_small");

			_num_sizes = small_num_sizes;
			int small_start = 100,
				small_step = 100;
			_sizes = new int [_num_sizes];

			generators::arithm_progr<int> (_sizes, _num_sizes,
										   small_start, small_step);
		} else if (run_setting == string("large sizes")) {
			_progress_filename = string(".progress_large");

			_num_sizes = large_num_sizes;
			int large_start = 3100,
				large_step = 100;
			_sizes = new int [_num_sizes];

			generators::arithm_progr<int> (_sizes, _num_sizes,
										   large_start, large_step);
		} else {
			cerr << "[warning] unknown run setting \"" << run_setting << "\"\n";
			_num_sizes = 0;
			_sizes = 0;
		}

		// initialize _mus and _num_mus
		if (1) {
			_num_mus = 7;
			double mu_start = 1,
				   mu_mul = 10;
			_mus = new double [_num_mus];

			generators::geom_progr<double> (_mus, _num_mus, mu_start, mu_mul);
		} else {
			// cerr << "[warning] unknown mu setting \"" << mu_setting << "\"\n";
			_num_mus = 0;
			_mus = 0;
		}

		// initialize _num_runs
		_num_runs = 10;
	}

	~PerformanceComparator() {
		delete[] _sizes;
		delete[] _mus;
	}

	void run_comparison(int num_methods, GenericMethod **methods,
						string data_filename_format) {
		int s_idx, mu_idx, r_idx;
		if (!_restore_progress(s_idx, mu_idx, r_idx)) {
			return;
		}

		cerr << "starting indices:\n"
			 << "s_idx = " << s_idx << "\n"
			 << "mu_idx = " << mu_idx << "\n"
			 << "r_idx = " << r_idx << "\n\n";

		if (mu_idx == _num_mus) {
			cerr << "mu_idx reached its limit\n";
			cerr << "advancing s_idx and resetting mu_idx\n";
			mu_idx = 0;
			++s_idx;
		}

		if (s_idx == _num_sizes) {
			cerr << "s_idx reached its limit\n";
			return;
		}

		cerr << "starting values:\n"
			 << "size = " << _sizes[s_idx] << "\n"
			 << "mu = " << _mus[mu_idx] << "\n"
			 << "run = " << r_idx << "\n\n";

		Matrix A;
		Vector f;
		string msg;
		const string sep_dash = string(79, '-') + string("\n"),
					 sep_ddash = string(79, '=') + string("\n");
		const string eol = string("\n");

		// todo: move seed to args?
		const int seed = time(0);
		srand(seed);

		_log_start_time = system_clock::now();

		for (; s_idx < _num_sizes; ++s_idx) {
			const int size = _sizes[s_idx];

			for (; mu_idx < _num_mus; ++mu_idx) {
				const double mu = _mus[mu_idx];

				for (; r_idx < _num_runs; ++r_idx) {
					_update_progress(s_idx, mu_idx, r_idx);

					msg = string("run #") + to_string(r_idx);
					msg += string(" on size = ") + to_string(size);
					msg += string(" with mu = ") + to_string(mu) + eol;
					_write_log(msg, 0);

					msg = string("generating the system") + eol;
					_write_log(msg, 0);

					f = generators::vector_random(size);
					A = generators::matrix_with_approximate_mu(size, mu);

					_run_methods(num_methods, methods, size, mu, A, f,
								 data_filename_format);

					_write_log(sep_dash, 0);
				}
				r_idx = 0;
			}
			mu_idx = 0;
			_write_log(sep_ddash, 0);
		}
		_update_progress(s_idx, mu_idx, r_idx);
	}
};

#endif // __PERFORMANCE_COMPARATOR__
