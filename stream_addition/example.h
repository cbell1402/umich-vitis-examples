#ifndef __ARRAY_OF_STREAMS_EXAMPLE__
#define __ARRAY_OF_STREAMS_EXAMPLE__

#include "hls_stream.h"
#include <iostream>


extern float dut(hls::stream<float> s_in, int numHits);

#endif
