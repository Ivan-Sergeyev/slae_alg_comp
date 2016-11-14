#ifndef __PERFORMANCE_COMPARATOR__
#define __PERFORMANCE_COMPARATOR__

#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

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

	string _timestamp(const time_point<system_clock> &time) const {
		const string begin = string("["),
					 end = string("]"),
					 sep = string(":");

		auto time_diff = time - _log_start_time;
		string h = to_string(duration_cast<hours>(time_diff).count()),
			   m = to_string(duration_cast<minutes>(time_diff).count() % 60),
			   s = to_string(duration_cast<seconds>(time_diff).count() % 60);
		return begin + h + sep + m + sep + s + end;
	}

	void _write_log(string msg, int level=0) {
		assert(_log_file.good());

		string full_msg = _timestamp(system_clock::now()) + string(" ");

		if (level == 0) {
			full_msg += string("= ");
		} else if (level == 1) {
			full_msg += string("|- ");
		} else if (level == 2) {
			full_msg += string("|== ");
		} else if (level == 3) {
			full_msg += string("|--- ");
		}

		full_msg += msg;
		_log_file << full_msg;
	}

	// TODO:
	//  * move generators to separate files
	//  * pass generator functions as arguments to run_comparison

	Matrix _generate_random_matrix(int size) {
		srand(time(NULL));
		int n = size * size;
		double *values = new double[n];
		for(int i = 0; i < n; ++i) {
			values[i] = rand() + 1;
		}
		Matrix m(size, values);
		delete[] values;
		return m;
	}

	Matrix _diag_generate(int size, double min, double max){
    	Matrix M(size);
	    srand(time(NULL));
	    M(0, 0) = min,
	    M(1, 1) = max;
	    for(int i = 2; i < size; ++i) {
	    	M(i, i) = min + rand() * (max - min) / RAND_MAX;
	    }
	    return M;
	}

	Matrix _generate_random_matrix_with_mu(int size, double mu){
		Matrix M = _generate_random_matrix(size);
	    double min = 1;
	    double max = min * mu;
		M = M.ort() * _diag_generate(M.get_size(), min, max);
		return M;
	}

	void _make_diagonally_dominant(Matrix &m) {
		int n = m.get_size();
		for(int i = 0; i < n; ++i) {
			double sum_row = 0;
			for(int j = 0; j < n; ++j) {
				sum_row += m(i, j);
			}
			m(i, i) = sum_row;
		}
	}

	Vector _generate_random_vector(int size) {
		double *coords = new double[size];
		for(int i = 0; i < size; ++i) {
			coords[i] = rand();
		}
		Vector v(size, coords);
		delete[] coords;
		return v;
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
		// write results to file
		data_file << results << "\n";
		data_file.close();
	}

	void _run_measurements(const GenericMethod *method, int size, double mu,
						   const Matrix &A, const Vector &f,
						   string data_filename_format) {
		// measure performance
		auto t_start = high_resolution_clock::now();
		Vector answer = method->run(A, f);
		auto t_end = high_resolution_clock::now();

		// calculate time difference in seconds
		auto elapsed_ns = duration_cast<nanoseconds>(t_end - t_start).count();
		double elapsed_s = (double)elapsed_ns / (double)1000000000;
		// gather data to be saved
		string results = to_string(size) + string(" ") + to_string(elapsed_s) +
						 string(" ") + to_string(mu);

		string verdict;
		if (answer.get_size() == size) {
			verdict = string("converged");
		} else {
			verdict = string("diverged");
		}

		// assemble filename to save data to
		// todo: use data_filename_format
		string data_filename =
			string("./data/data_") + verdict + string("_") +
			method->get_name() + string(".txt");

		// open data file
		_write_results_to_file(data_filename, results);
	}

public:
	PerformanceComparator(ostream &log_file) : _log_file(log_file) {}

	void run_comparison(int num_methods, GenericMethod **methods,
						int num_sizes, const int *sizes,
						int num_mus, const double *mus,
						int num_runs, string data_filename_format) {
		Matrix A;
		Vector f;
		string msg;
		const string eol = string("\n");

		_log_start_time = system_clock::now();

		for(int s_idx = 0; s_idx < num_sizes; ++s_idx) {
			const int size = sizes[s_idx];
			msg = string("running on size = ") + to_string(size) + eol;
			_write_log(msg, 0);

			for(int mu_idx = 0; mu_idx < num_mus; ++mu_idx) {
				const double mu = mus[mu_idx];
				msg = string("running on mu = ") + to_string(mu) + eol;
				_write_log(msg, 1);

				for(int r_idx = 0; r_idx < num_runs; ++r_idx) {
					msg = string("run #") + to_string(r_idx) + eol;
					_write_log(msg, 2);

					msg = string("generating the system") + eol;
					_write_log(msg, 2);

					f = _generate_random_vector(size);
					A = _generate_random_matrix_with_mu(size, mu);

					msg = string("running methods") + eol;
					_write_log(msg, 2);

					for (int m_idx = 0; m_idx < num_methods; ++m_idx)
					{
						string m_name = methods[m_idx]->get_name();
						string msg = string("running ") + m_name + eol;
						_write_log(msg, 3);

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
