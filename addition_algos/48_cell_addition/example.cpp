#include "example.h"

sum_t add48(data_t input[48]) {

#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=input complete

    sum_t stage1[24];
#pragma HLS ARRAY_PARTITION variable=stage1 complete

stage_one:
    for (int i=0; i<24; i++) {
#pragma HLS UNROLL
        stage1[i] = input[2*i] + input[2*i+1];
    }

    sum_t stage2[12];
#pragma HLS ARRAY_PARTITION variable=stage2 complete

stage_two:
    for (int i=0; i<12; i++) {
#pragma HLS UNROLL
        stage2[i] = stage1[2*i] + stage1[2*i+1];
    }

    sum_t stage3[6];
#pragma HLS ARRAY_PARTITION variable=stage3 complete

stage_three:
    for (int i=0; i<6; i++) {
#pragma HLS UNROLL
        stage3[i] = stage2[2*i] + stage2[2*i+1];
    }

    sum_t stage4[3];
#pragma HLS ARRAY_PARTITION variable=stage4 complete

stage_four:
    for (int i=0; i<3; i++) {
#pragma HLS UNROLL
        stage4[i] = stage3[2*i] + stage3[2*i+1];
    }


 //   sum_t out = stage4[0] + stage4[1] + stage4[2];

    return stage4[0] + stage4[1] + stage4[2];
}