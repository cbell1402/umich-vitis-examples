#ifndef __MAXIMA_H__
#define __MAXIMA_H__

#include <ap_fixed.h>

#define NUM_CELLS 48
#define MAX_NEIGHBORS 12 // CHANGE LATER WHEN ADDING MORE MODULES
typedef ap_fixed<35,15> data_t;

void clusterMaxima(
    data_t energy[NUM_CELLS],
    bool labels[NUM_CELLS]
);


struct Candidate {
    data_t energy;
    int label;
};

Candidate max2(Candidate a, Candidate b);

#endif