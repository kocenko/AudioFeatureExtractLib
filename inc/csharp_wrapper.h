#ifndef CSHARP_WRAPPER_H
#define CSHARP_WRAPPER_H

#include "mfcc.h"
#define STORAGE_ATTRIBUTE __declspec(dllexport)

extern "C"
{
    STORAGE_ATTRIBUTE MFCC* mfcc_create();
    STORAGE_ATTRIBUTE void mfcc_destroy(MFCC* mfcc);
    STORAGE_ATTRIBUTE double* mfcc_get_hamming(MFCC* mfcc);
}

#endif
