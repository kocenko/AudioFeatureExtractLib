#include <vector>
#include "mfcc.h"
#include "config.h"
#include "csharp_wrapper.h"

MFCC* mfcc_create()
{
    return new MFCC();
}

void mfcc_destroy(MFCC* mfcc)
{
    delete mfcc;
}

double* mfcc_process_audio_segment(MFCC* mfcc, double* signal, int signal_length)
{
    std::vector<double> signal_vector(signal, signal + signal_length);
    mfcc->process_audio_segment(signal_vector);
    return mfcc->mfcc_output.data();
}
