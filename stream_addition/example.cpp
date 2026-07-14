#include "example.h"

float dut(hls::stream<float>& s_in, int numHits) {
#pragma HLS INTERFACE axis port=s_in

    float sum = 0;

    for (int i=0; i < numHits; ++i) {
        sum += s_in.read();
    }
    return sum;
}
