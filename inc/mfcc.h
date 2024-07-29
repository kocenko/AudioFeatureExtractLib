#ifndef MFCC_H
#define MFCC_H

/**
 * @file mfcc.h
 * @brief ...
 * Slightly modified code created by the author of: https://github.com/dspavankumar/compute-mfcc/blob/master/mfcc.cc.
 */

#include<complex>
#include<vector>
#include<map>
#include "config.h"

typedef std::vector<double> double_vector;
typedef std::complex<double> complex_vector;
typedef std::vector<double_vector> double_matrix;
typedef std::vector<complex_vector> complex_matrix;
typedef std::map<int, std::map<int, complex_vector>> twiddle_map;


class MFCC
{
private:
    twiddle_map twiddle;
    double_vector frame, hamming, mfcc, power_spectrum;
    double_matrix filter_banks, dct;

    inline double herz_to_mel (double frequency_in_herz);
    inline double mel_to_herz (double frequency_in_mel);
    void initialize_filterbank (void);
    void initialize_hamming_window(void);
    void initialize_dct_matrix(void);
    void initialize_twiddle(void);
    void windowing_and_preemphasis(void);
    complex_matrix fft(complex_matrix signal);
    void compute_power_spectrum(void);
public:
    MFCC();

};

#endif //MFCC_H
