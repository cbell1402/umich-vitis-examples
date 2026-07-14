#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__

#include "hls_vector.h"
#include <ap_int.h>

#define NUM 32

typedef hls::vector<float, 16> float16;

extern "C" void example(float16* res, const float16* lhs, const float16* rhs,
                        int n);


#endif

// this is largely taken from the Vitis HLS intro examples
