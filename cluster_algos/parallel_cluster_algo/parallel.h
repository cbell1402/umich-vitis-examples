#ifndef __MAXIMA_H__
#define __MAXIMA_H__

#include <ap_fixed.h>

#define NUM_CELLS 48
#define MAX_NEIGHBORS 12 // CHANGE LATER WHEN ADDING MORE MODULES
typedef ap_fixed<35,15> data_t;

void computeNext(
    data_t energy[NUM_CELLS],
    int next[NUM_CELLS]
);

void compressPaths(int next[NUM_CELLS]);

void moduleCluster2d(
    data_t energy[NUM_CELLS],
    int labels[NUM_CELLS]
);


#endif