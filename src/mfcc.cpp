#include "mfcc.h"
#include "config.h"
#include <iostream>
#include <algorithm>


double MFCC::herz_to_mel(double frequency_in_herz)
{
    return 2595 * std::log10(1 + frequency_in_herz / 700);
}

double MFCC::mel_to_herz (double frequency_in_mel)
{
    return 700 * (std::pow(10, frequency_in_mel / 2595) - 1);
}

void MFCC::initialize_filterbank(void)
{
    double min_mel_frequency = herz_to_mel(constants::min_frequency);
    double max_mel_frequency = herz_to_mel(constants::max_frequency);

    double_vector centre_frequencies;
    centre_frequencies.reserve(constants::mel_banks_num + 2);
    for (int i = 0; i < constants::mel_banks_num + 2; i++)
    {
        double ith_center = mel_to_herz(min_mel_frequency + (max_mel_frequency - min_mel_frequency) / (constants::mel_banks_num + 1) * i);
        centre_frequencies.push_back(ith_center);
    }

    short fft_bins_num = constants::fft_size / 2 + 1;
    double_vector fft_bins;
    fft_bins.reserve(fft_bins_num);
    for (int i=0; i < fft_bins_num; i++)
        fft_bins.push_back(constants::sampling_rate / 2.0 / (fft_bins_num - 1) * i);
        
    filter_banks.reserve(constants::mel_banks_num * fft_bins_num);
    
    for (int filter_idx = 1; filter_idx <= constants::mel_banks_num; filter_idx++)
    {
        double_vector single_filter;
        for (int bin = 0; bin < fft_bins_num; bin++)
        {
            double weight;
            if (fft_bins[bin] < centre_frequencies[filter_idx - 1])
                weight = 0;
            else if (fft_bins[bin] <= centre_frequencies[filter_idx])
                weight = (fft_bins[bin] - centre_frequencies[filter_idx - 1]) / (centre_frequencies[filter_idx] - centre_frequencies[filter_idx - 1]);
            else if (fft_bins[bin] <= centre_frequencies[filter_idx + 1])
                weight = (centre_frequencies[filter_idx + 1] - fft_bins[bin]) / (centre_frequencies[filter_idx + 1] - centre_frequencies[filter_idx]);
            else
                weight = 0;
            single_filter.push_back (weight);
        }
        filter_banks.push_back(single_filter);
    }
}

void MFCC::initialize_hamming_window(void)
{
    hamming.assign(constants::window_size, 0);
    for (int i = 0; i < constants::window_size; i++)
        hamming[i] = 0.54 - 0.46 * cos(2 * PI * i / (constants::window_size - 1));
}

void MFCC::initialize_dct_matrix(void)
{
    double_vector v1(constants::mfcc_features_num, 0), v2(constants::mel_banks_num, 0);
    for (int i = 0; i < constants::mfcc_features_num; i++)
        v1[i] = i;
    for (int i = 0; i < constants::mel_banks_num; i++)
        v2[i] = i + 0.5;

    dct.reserve (constants::mel_banks_num * (constants::mfcc_features_num));        
    double c = sqrt(2.0 / constants::mel_banks_num);
    for (int i = 0; i < constants::mfcc_features_num; i++)
    {
        double_vector single_feature;
        for (int j = 0; j < constants::mel_banks_num; j++)
            single_feature.push_back (c * cos(PI / constants::mel_banks_num * v1[i] * v2[j]));
        dct.push_back(single_feature);
    }
}

void MFCC::initialize_twiddle(void)
{
    const complex_vector j(0, 1);
    for (int n = 2; n <= constants::fft_size; n *= 2)
    {
        for (int k = 0; k <= n / 2 - 1; k++)
            twiddle[n][k] = exp(-2 * PI * k / n * j);
    }
}

void MFCC::rescale_signal(double_vector& signal)
{
    double min_value = *std::min_element(signal.begin(), signal.end());
    double max_value = *std::max_element(signal.begin(), signal.end());

    for (double& value: signal)
        value = 2 * (value - min_value) / (max_value - min_value) - 1;
}

void MFCC::windowing_and_preemphasis(void)
{
    double_vector processed_frame(frame.size(), hamming[0] * frame[0]);
    for (int i = 0; i < frame.size(); i++)
        processed_frame[i] = hamming[i] * (frame[i] - constants::pre_emphasis_coefficient * frame[i - 1]);
    frame = processed_frame;
}

complex_matrix MFCC::fft(complex_matrix signal)
{
    int N = signal.size();
    if (N == 1)
        return signal;

    complex_matrix even_samples(N / 2, 0), odd_samples(N / 2, 0), Xjo, Xjo2;

    for (int i = 0; i < N; i += 2)
        even_samples[i / 2] = signal[i];
    for (int i = 1; i < N; i += 2)
        odd_samples[(i - 1) / 2] = signal[i];

    // Compute N/2-point FFT
    Xjo = fft(even_samples);
    Xjo2 = fft(odd_samples);
    Xjo.insert (Xjo.end(), Xjo2.begin(), Xjo2.end());

    // Butterfly computations
    for (int i = 0; i <= N / 2 - 1; i++) {
        complex_vector t = Xjo[i], tw = twiddle[N][i];
        Xjo[i] = t + tw * Xjo[i + N / 2];
        Xjo[i + N / 2] = t - tw * Xjo[i + N / 2];
    }
    return Xjo;
}

void MFCC::compute_power_spectrum(void)
{
    frame.resize(constants::fft_size);  // zero-padding
    complex_matrix complex_frame(frame.begin(), frame.end());
    complex_matrix complex_fft = fft(complex_frame);

    for (int i = 0; i < constants::fft_size / 2 + 1; i++)
        power_spectrum[i] = pow(abs(complex_fft[i]), 2);
}

void MFCC::compute_log_mel_filterbank(void)
{
    log_mel_coefficients.assign(constants::mel_banks_num, 0);
        
    for (int i = 0; i < constants::mel_banks_num; i++)
    {
        for (int j = 0; j < filter_banks[i].size(); j++)
            log_mel_coefficients[i] += filter_banks[i][j] * power_spectrum[j];

        if (log_mel_coefficients[i] < 1.0)
            log_mel_coefficients[i] = 1.0;
    }
    
    for (int i = 0; i < constants::mel_banks_num; i++)
        log_mel_coefficients[i] = std::log(log_mel_coefficients[i]);
}

void MFCC::compute_dct(void)
{
    mfcc.assign(constants::mfcc_features_num, 0);
    for (int i = 0; i < constants::mfcc_features_num; i++) {
        for (int j = 0; j < constants::mel_banks_num; j++)
            mfcc[i] += dct[i][j] * log_mel_coefficients[j];
    }
}

MFCC::MFCC()
{
    power_spectrum.assign(constants::fft_size / 2 + 1, 0);
    initialize_filterbank();
    initialize_hamming_window();
    initialize_dct_matrix();
    initialize_twiddle();
}

void MFCC::process_audio_segment(double_vector samples)
{
    mfcc_output.clear();
    rescale_signal(samples);
    
    // If the signal is not divisible by the interval, the end is discarted
    for (int i = 0; i < samples.size() - constants::window_size; i += constants::interval_size)
    {
        frame.assign(samples.begin() + i, samples.begin() + i + constants::window_size);
        windowing_and_preemphasis();
        compute_power_spectrum();
        compute_log_mel_filterbank();
        compute_dct();
        mfcc_output.insert(mfcc_output.end(), mfcc.begin(), mfcc.end());
    }
}
