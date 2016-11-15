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
using std::ostream;
using std::fstream;
using std::string;
using std::to_string;


class PerformanceComparator {
private:
	ostream &_log_file;
	time_point<system_clock> _log_start_time;

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

/*
	 // read vector from file
	 Vector& _read_vector(FILE* file, int size){ // check for work
	 	double *coords = new double[size];
	 	int errc;
     	for (int j = 0; j < size; ++j) {
     		errc = fscanf(file, "%lf", &coords[j]);
    		if ((errc == EOF) || (errc == 0)) return 1;
     	}
     	Vector *v = new Vector(size, coords);
     	delete[] coords;
     	return *v;
	 }

	// read matrix from file
	Matrix& _read_matrix(FILE* file, int size) { //check for work
	 	int n = size * size;
	 	double *values = new double[n];
	 	for(int i = 0; i < n; ++i) {
	 		errc = fscanf(file, &value[i]);
	 		if ((errc == EOF) || (errc == 0)) return 1;
	 	}
	 	Matrix *m = new Matrix(size, values);
	 	delete[] values;
	 	return *m;
	}

 	// check that A•answer=b with accurace epsilon (max delta = epsilon)      1 - good; 0 - bad
 	int _check_answer(const Vector &answer, const Matrix &M, const Vector &b, const double &epsilon){
	    Vector check = M * answer;
    	double max = 0;
    	for (int i = 0; i < result.get_size(); ++i) if (std::abs(check(i)-result(i)) > max) max = std::abs(check(i)-result(i));
    	delete &check;
    	if (max < epsilon) return 1;
    	return 0;
	}
*/

	void _write_results_to_file(string data_filename, string results) {
		fstream data_file(data_filename, ostream::out | ostream::app);
		if (!(data_file.is_open())) {
			_log_file << "Error opening data file \"" << data_filename << "\"\n"
					  << "Aborting\n";
			return;
		}

		data_file << results << "\n";
		data_file.close();
	}

	void _run_measurements(const GenericMethod *method, int size, double mu,
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
		if (answer.get_size() == size) {
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

public:
	PerformanceComparator(ostream &log_file,
						  string size_setting, string run_setting) :
			_log_file(log_file) {
		int small_num_sizes = 30,
			large_num_sizes = 50;

		if (run_setting == string("test run")) {
			small_num_sizes = 1;
			large_num_sizes = 0;
		} else if (run_setting == string("full run")) {
			;
		} else {
			cerr << "[warning] unknown run setting \"" << run_setting << "\"\n";
		}

		if (size_setting == string("small sizes")) {
			_num_sizes = small_num_sizes;
			int small_start = 100,
				small_step = 100;
			_sizes = new int [_num_sizes];
			generators::arithm_progr<int> (_sizes, _num_sizes,
										   small_start, small_step);
		} else if (size_setting == string("large sizes")) {
			_num_sizes = large_num_sizes;
			int large_start = 3100,
				large_step = 100;
			_sizes = new int [_num_sizes];
			generators::arithm_progr<int> (_sizes, _num_sizes,
										   large_start, large_step);
		} else {
			cerr << "[warning] unknown size setting \"" << size_setting << "\"\n";
		}

		if (1) {
			_num_mus = 7;
			double mu_start = 1,
				   mu_mul = 10;
			_mus = new double [_num_mus];
			generators::geom_progr<double> (_mus, _num_mus, mu_start, mu_mul);
		} else {
			// cerr << "[warning] unknown mu setting \"" << mu_setting << "\"\n";
		}

		_num_runs = 10;
	}

	~PerformanceComparator() {
		delete[] _sizes;
		delete[] _mus;
	}

	void run_comparison(int num_methods, GenericMethod **methods,
						string data_filename_format) {
		Matrix A;
		Vector f;
		string msg;
		const string sep = string(79, '=');
		const string eol = string("\n");

		// todo: move seed to args?
		int seed = time(0);
		srand(seed);

		_log_start_time = system_clock::now();

		for(int s_idx = 0; s_idx < _num_sizes; ++s_idx) {
			const int size = _sizes[s_idx];

			for(int mu_idx = 0; mu_idx < _num_mus; ++mu_idx) {
				const double mu = _mus[mu_idx];

				for(int r_idx = 0; r_idx < _num_runs; ++r_idx) {
					msg = string("run #") + to_string(r_idx);
					msg += string(" on size = ") + to_string(size);
					msg += string(" with mu = ") + to_string(mu) + eol;
					_write_log(msg, 0);

					msg = string("generating the system") + eol;
					_write_log(msg, 0);

					f = generators::vector_random(size);
					A = generators::matrix_with_approximate_mu(size, mu);

					msg = string("running methods") + eol;
					_write_log(msg, 0);

					for (int m_idx = 0; m_idx < num_methods; ++m_idx)
					{
						string m_name = methods[m_idx]->get_name();
						string msg = string("running ") + m_name + eol;
						_write_log(msg, 1);

						_run_measurements(methods[m_idx], size, mu, A, f,
										  data_filename_format);
						// for m_idx
					}
					// for r_idx
				}
			// for mu_idx
			}
		// for s_idx
		}
	}
};

#endif // __PERFORMANCE_COMPARATOR__
