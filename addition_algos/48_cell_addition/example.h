#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__

#include <ap_fixed.h>


typedef ap_fixed<35,15> data_t;
typedef ap_fixed<48,24> sum_t;

sum_t add48(data_t input[48]);

#endif
