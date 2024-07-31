#ifndef MFCC_H
#define MFCC_H

/**
 * @file mfcc.h
 * @brief MFCC (Mel-Frequency Cepstral Coefficients) extraction class.
 * 
 * This file contains the declaration of the MFCC class, which is responsible for 
 * extracting Mel-Frequency Cepstral Coefficients from audio signals. 
 * The code is slightly modified from the original code created by the author of: 
 * https://github.com/dspavankumar/compute-mfcc/blob/master/mfcc.cc.
 */

#include<complex>
#include<vector>
#include<map>
#include "config.h"

/** @brief Typedef for a vector of doubles. */
typedef std::vector<double> double_vector;

/** @brief Typedef for a complex number with double precision. */
typedef std::complex<double> complex_vector;

/** @brief Typedef for a matrix of doubles. */
typedef std::vector<double_vector> double_matrix;

/** @brief Typedef for a matrix of complex numbers. */
typedef std::vector<complex_vector> complex_matrix;

/** @brief Typedef for a map of twiddle factors. */
typedef std::map<int, std::map<int, complex_vector>> twiddle_map;


/**
 * @class MFCC
 * @brief A class to compute Mel-Frequency Cepstral Coefficients from audio signals.
 * 
 * This class provides methods for the complete process of extracting MFCC features from audio segments, 
 * including windowing, FFT, power spectrum calculation, Mel filterbank application, and DCT.
 */
class MFCC
{
private:
    /**
     * @brief Convert frequency from Hertz to Mel scale.
     * 
     * @param frequency_in_herz Frequency in Hertz.
     * @return Frequency in Mel scale.
     */
    inline double herz_to_mel (double frequency_in_herz);

    /**
     * @brief Convert frequency from Mel scale to Hertz.
     * 
     * @param frequency_in_mel Frequency in Mel scale.
     * @return Frequency in Hertz.
     */
    inline double mel_to_herz (double frequency_in_mel);

    /**
     * @brief Initialize the Mel filter bank.
     */
    void initialize_filterbank (void);

    /**
     * @brief Initialize the Hamming window.
     */
    void initialize_hamming_window(void);

    /**
     * @brief Initialize the Discrete Cosine Transform (DCT) matrix.
     */
    void initialize_dct_matrix(void);
    
    /**
     * @brief Initialize the twiddle factors for FFT.
     */
    void initialize_twiddle(void);
    
    /**
     * @brief Apply windowing and pre-emphasis to the audio frame.
     */
    void windowing_and_preemphasis(void);
    
    /**
     * @brief Perform Fast Fourier Transform (FFT) on the signal.
     * 
     * @param signal The complex matrix representing the signal.
     * @return Transformed signal as a complex matrix.
     */
    complex_matrix fft(complex_matrix signal);

    /**
     * @brief Compute the power spectrum of the audio frame.
     */
    void compute_power_spectrum(void);
    
    /**
     * @brief Compute the logarithm of the Mel-filtered power spectrum.
     */
    void compute_log_mel_filterbank(void);
    
    /**
     * @brief Compute the Discrete Cosine Transform (DCT) of the log Mel-filtered spectrum.
     */
    void compute_dct(void);
public:
    twiddle_map twiddle;
    double_vector frame, hamming, mfcc, power_spectrum, log_mel_coefficients;
    double_matrix filter_banks, dct;
    /**
     * @brief Construct a new MFCC object.
     */
    MFCC();

    /**
     * @brief Process an audio segment to extract MFCC features.
     * 
     * @param samples The audio samples of the segment.
     * @return Matrix of MFCC features.
     */
    double_matrix process_audio_segment(double_vector samples);
};

#endif //MFCC_H
