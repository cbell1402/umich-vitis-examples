#ifndef _CPP_AP_INT_ARITH_H_
#define _CPP_AP_INT_ARITH_H_

#include "ap_int.h"
#include <stdio.h>

#define N 9


typedef ap_int<6> dinA_t;
typedef ap_int<12> dinB_t;
typedef ap_int<22> dinc_t;
typedef ap_int<33> dinD_t;

typedef ap_int<18> dout1_t;
typedef ap_int<13> dout2_t;
typedef ap_int<22> dout3_t;
typedef ap_int<6> dout4_t;

void cpp_ap_int_arith(dinA_t inA, dinB_t inB, dinC_t inC, dinD_t inD, dout1_t* out1, dout2_t* out2, dout3_t* out3, dout4_t* out4);

#endif

// this is largely taken from the Vitis HLS intro examples
