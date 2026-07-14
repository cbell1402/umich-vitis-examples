#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include <stdint.h>

#define NUM_CELLS 48
#define MAX_NEIGHBORS 12 // CHANGE LATER WHEN ADDING MORE MODULES
typedef float data_t;

void moduleCluster2d(
    data_t energy[NUM_CELLS],
    int labels[NUM_CELLS],
    int &numClusters
);


#endif