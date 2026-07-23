#ifndef __CLUSTER3D_H__
#define __CLUSTER3D_H__

#include <ap_fixed.h>

// For 2d clustering
#define NUM_CELLS 48
#define MAX_NEIGHBORS_2D 12 // CHANGE LATER WHEN ADDING MORE MODULES
typedef ap_fixed<35,15> data_t;
typedef ap_uint<11> cluster_id_t;

const cluster_id_t INVALID_CLUSTER = 0x7FF;

void clusterMaxima2d(
    data_t energy[NUM_CELLS],
    bool maxima[NUM_CELLS]
);

struct Candidate2d {
    data_t energy;
    int label;
};

Candidate2d max2(Candidate2d a, Candidate2d b);

// For 3d clustering
#define NUM_LAYERS 32
#define MAX_NEIGHBORS_3D 38 // CHANGE LATER WHEN ADDING MORE MODULES

cluster_id_t pick(cluster_id_t a, cluster_id_t b);

void cluster3d(
    bool maxima[NUM_LAYERS][NUM_CELLS],
    ap_uint<11> cluster[NUM_LAYERS][NUM_CELLS]
);

// Top function
void clusterTop(
    data_t energy[NUM_LAYERS][NUM_CELLS],
    ap_uint<11> cluster[NUM_LAYERS][NUM_CELLS]
);

#endif
