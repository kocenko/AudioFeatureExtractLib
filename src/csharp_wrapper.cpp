#include "mfcc.h"
#include "csharp_wrapper.h"

MFCC* mfcc_create()
{
    return new MFCC();
}

void mfcc_destroy(MFCC* mfcc)
{
    delete mfcc;
}

double* mfcc_get_hamming(MFCC* mfcc)
{
    return mfcc->hamming.data();
}
