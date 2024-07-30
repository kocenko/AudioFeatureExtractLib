#include <iostream>
#include <vector>
#include "mfcc.h"


using namespace std;

int main()
{
    MFCC mfcc_extractor;
    double_vector temp(16000, 1);
    double_matrix output = mfcc_extractor.process_audio_segment(temp);
    cout << "Rows: " << output.size() << " _ Columns: " << output[0].size() << endl;
}