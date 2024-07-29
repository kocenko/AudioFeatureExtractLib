#include "mfcc.h"
#include "config.h"
#include <iostream>


MFCC::MFCC()
{
    initialize_filterbank();
    initialize_hamming_window();
    initialize_dct_matrix();
    initialize_twiddle();
}

void MFCC::initialize_filterbank(void)
{
    double min_mel_frequency = herz_to_mel(constants::min_frequency);
    double max_mel_frequency = herz_to_mel(constants::max_frequency);

    double_vector centre_frequencies;
    centre_frequencies.reserve(constants::mel_banks_num + 2);
    for (int i = 0; i < constants::mel_banks_num + 2; i++)
    {
        double ith_center = mel_to_herz(constants::min_frequency + (constants::min_frequency - constants::min_frequency) / (constants::mel_banks_num + 1) * i);
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
    double_vector v1(constants::mfcc_features_num + 1, 0), v2(constants::mel_banks_num, 0);
    for (int i = 0; i <= constants::mfcc_features_num; i++)
        v1[i] = i;
    for (int i = 0; i < constants::mel_banks_num; i++)
        v2[i] = i + 0.5;

    dct.reserve (constants::mel_banks_num * (constants::mfcc_features_num + 1));        
    double c = sqrt(2.0 / constants::mel_banks_num);
    for (int i = 0; i <= constants::mfcc_features_num; i++)
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

double MFCC::herz_to_mel(double frequency_in_herz)
{
    return 2595 * std::log10(1 + frequency_in_herz / 700);
}

double MFCC::mel_to_herz (double frequency_in_mel)
{
    return 700 * (std::pow(10, frequency_in_mel / 2595) - 1);
}
