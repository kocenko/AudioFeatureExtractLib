#ifndef CSHARP_WRAPPER_H
#define CSHARP_WRAPPER_H

#include "mfcc.h"
#define STORAGE_ATTRIBUTE __declspec(dllexport)

extern "C"
{
    STORAGE_ATTRIBUTE MFCC* mfcc_create();
    STORAGE_ATTRIBUTE void mfcc_destroy(MFCC* mfcc);
    STORAGE_ATTRIBUTE double* mfcc_process_audio_segment(MFCC* mfcc, double* signal, int signal_length);
}

#endif
