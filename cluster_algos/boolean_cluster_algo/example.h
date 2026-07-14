#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__


#define NUM_CELLS 48

typedef float data_t;

void moduleCluster2d(
    data_t energy[NUM_CELLS],
    int labels[NUM_CELLS],
    int &numClusters
);


#endif