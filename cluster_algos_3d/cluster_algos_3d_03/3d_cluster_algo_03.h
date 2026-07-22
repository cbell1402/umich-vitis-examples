#ifndef __CLUSTER3D_H__
#define __CLUSTER3D_H__

#include <ap_fixed.h>

// For 2d clustering
#define NUM_CELLS 48
#define MAX_NEIGHBORS_2D 12 // CHANGE LATER WHEN ADDING MORE MODULES
typedef ap_fixed<35,15> data_t;

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

struct parent_t {
    ap_uint<5> layer;
    ap_uint<6> cell;
};

parent_t makeIndex(int layer, int cell);

void buildClusterPointers(
    bool maxima[NUM_LAYERS][NUM_CELLS],
    parent_t clusterPointer[NUM_LAYERS][NUM_CELLS]
);

void compressClusterPointers(
    bool maxima[NUM_LAYERS][NUM_CELLS],
    parent_t clusterPointer[NUM_LAYERS][NUM_CELLS]
);

void makeClusters(
    bool maxima[NUM_LAYERS][NUM_CELLS],
    parent_t clusterPointer[NUM_LAYERS][NUM_CELLS],
    int cluster[NUM_LAYERS][NUM_CELLS]
);


// Top function
void clusterTop(
    data_t energy[NUM_LAYERS][NUM_CELLS],
    int cluster[NUM_LAYERS][NUM_CELLS]
);

#endif