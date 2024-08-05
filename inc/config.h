#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file config.h
 * @brief Configuration constants for audio processing.
 * 
 * Defines a set of constants used in audio processing tasks.
 * They are intended to be used throughout the application to maintain
 * consistent configuration values. They are inspired by the values used
 * in the "Efficient Voice Trigger Detection for Low Resource Hardware"
 * (https://api.semanticscholar.org/CorpusID:52186997).
 */

#define PI 3.14159265358979323846

namespace constants
{
    /**
     * @brief The expected number of samples of the recording.
     */
    constexpr short recording_samples = 16000;

    /**
     * @brief The sampling rate of the audio signal in Hz.
     * 
     * Defines the number of samples per second taken from the signal.
     */
    constexpr short sampling_rate = 16000;
    
    /**
     * @brief The number of Mel-frequency cepstral coefficients (MFCC) features.
     * 
     * Defines the number of MFCC features to be extracted from the audio signal.
     */
    constexpr short mfcc_features_num = 13;

    /**
     * @brief The duration of the analysis window in number of frames.
     * 
     * Defines the length of the window used for analyzing the audio signal.
     * With the given sampling rate (16kHz) it is equivalent to 25ms.
     */
    constexpr short window_size = 400;

    /**
     * @brief The duration between the start of each frame expressed in number of frames.
     * 
     * With the given sampling rate (16kHz) it is around 10ms resulting in 60% of overlap.
     * By applying this interval we achieve 100 frames per second. 
     */
    constexpr short interval_size = 156;

    /**
     * @brief The number of Mel filter banks.
     * 
     * Defines the number of Mel filter banks to be used in the MFCC extraction.
     */
    constexpr short mel_banks_num = 40;

    /**
     * @brief The minimum frequency to be considered in the Mel filter banks.
     * 
     * Defines the lower bound of the frequency range for the Mel filter banks.
     * The frequencies below this value will not be considered in the Mel filter bank calculation.
     */
    constexpr short min_frequency = 0;

    /**
     * @brief The maximum frequency to be considered in the Mel filter banks.
     * 
     * Defines the upper bound of the frequency range for the Mel filter banks.
     * The frequencies above this value will not be considered in the Mel filter bank calculation.
     */

    constexpr short max_frequency = 8000;

    /**
     * @brief The size of the Fast Fourier Transform (FFT) to be used.
     * 
     * Defines the number of points used in the FFT computation.
     */
    constexpr short fft_size = 512;

    /**
     * @brief The pre-emphasis coefficient for the audio signal.
     * 
     * Defines the coefficient used in the pre-emphasis filter applied to the audio signal.
     */
    constexpr double pre_emphasis_coefficient = 0.97;
}

#endif //CONFIG_H
