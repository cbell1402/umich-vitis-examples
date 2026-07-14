#include "cluster.h"

// neighborArray tracks which cells are whose neighbors.
const int neighborArray[NUM_CELLS][MAX_NEIGHBORS] = {
    {1, 4, 5, 6, 9, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 4, 5, 6, 7, 10, -1, -1, -1, -1, -1},
    {1, 3, 5, 6, 7, 11, 33, -1, -1, -1, -1, -1},
    {2, 6, 7, 32, 33, 34, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 8, 9, 10, 13, -1, -1, -1, -1, -1},
    {0, 1, 2, 4, 6, 8, 9, 10, 11, 14, -1, -1},
    {0, 1, 2, 3, 5, 7, 9, 10, 11, 15, 35, -1},
    {1, 2, 3, 6, 10, 11, 32, 33, 35, 36, -1, -1},
    {4, 5, 9, 12, 13, 14, 16, -1, -1, -1, -1, -1},
    {0, 4, 5, 6, 8, 10, 12, 13, 14, 15, 17, -1},
    {1, 4, 5, 6, 7, 9, 11, 13, 14, 15, 18, 38},
    {2, 5, 6, 7, 10, 14, 15, 19, 33, 35, 38, 39},
    {8, 9, 13, 16, 17, -1, -1, -1, -1, -1, -1, -1},
    {4, 8, 9, 10, 12, 14, 16, 17, 18, 20, -1, -1},
    {5, 8, 9, 10, 11, 13, 15, 17, 18, 19, 21, -1},
    {6, 9, 10, 11, 14, 18, 19, 22, 35, 38, 42, -1},
    {8, 12, 13, 17, 20, 21, -1, -1, -1, -1, -1, -1},
    {9, 12, 13, 14, 16, 18, 20, 21, 22, 24, -1, -1},
    {10, 13, 14, 15, 17, 19, 20, 21, 22, 23, 25, 38},
    {11, 14, 15, 18, 21, 22, 23, 26, 38, 39, 42, -1},
    {13, 16, 17, 18, 21, 24, 25, -1, -1, -1, -1, -1},
    {14, 16, 17, 18, 19, 20, 22, 24, 25, 26, 28, -1},
    {15, 17, 18, 19, 21, 23, 24, 25, 26, 27, 29, 42},
    {18, 19, 22, 25, 26, 27, 30, 38, 42, 43, 45, -1},
    {17, 20, 21, 22, 25, 28, 29, -1, -1, -1, -1, -1},
    {18, 20, 21, 22, 23, 24, 26, 28, 29, 30, -1, -1},
    {19, 21, 22, 23, 25, 27, 28, 29, 30, 31, 45, -1},
    {22, 23, 26, 29, 30, 31, 42, 45, 46, 47, -1, -1},
    {21, 24, 25, 26, 29, -1, -1, -1, -1, -1, -1, -1},
    {22, 24, 25, 26, 27, 28, 30, -1, -1, -1, -1, -1},
    {23, 25, 26, 27, 29, 31, 47, -1, -1, -1, -1, -1},
    {26, 27, 30, 45, 47, -1, -1, -1, -1, -1, -1, -1},
    {3, 7, 33, 34, 36, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 7, 11, 32, 34, 35, 36, 37, 39, -1, -1},
    {3, 32, 33, 35, 36, 37, 40, -1, -1, -1, -1, -1},
    {6, 7, 11, 15, 33, 34, 36, 38, 39, 40, 42, -1},
    {7, 32, 33, 34, 35, 37, 38, 39, 40, 41, 43, -1},
    {33, 34, 36, 39, 40, 41, 44, -1, -1, -1, -1, -1},
    {10, 11, 15, 18, 19, 23, 35, 36, 39, 42, 43, -1},
    {11, 19, 33, 35, 36, 37, 38, 40, 42, 43, 44, 45},
    {34, 35, 36, 37, 39, 41, 42, 43, 44, 46, -1, -1},
    {36, 37, 40, 43, 44, -1, -1, -1, -1, -1, -1, -1},
    {15, 19, 22, 23, 27, 35, 38, 39, 40, 43, 45, 46},
    {23, 36, 38, 39, 40, 41, 42, 44, 45, 46, 47, -1},
    {37, 39, 40, 41, 43, 45, 46, -1, -1, -1, -1, -1},
    {23, 26, 27, 31, 39, 42, 43, 44, 46, 47, -1, -1},
    {27, 40, 42, 43, 44, 45, 47, -1, -1, -1, -1, -1},
    {27, 30, 31, 43, 45, 46, -1, -1, -1, -1, -1, -1},
};

// numNeighbors tracks how many neighbors each cell has.
const unsigned char numNeighbors[48] = {
    5,
    7,
    7,
    6,
    7,
    10,
    11,
    10,
    7,
    11,
    12,
    12,
    5,
    10,
    11,
    11,
    6,
    10,
    12,
    11,
    7,
    11,
    12,
    11,
    7,
    10,
    11,
    10,
    5,
    7,
    7,
    5,
    5,
    10,
    7,
    11,
    11,
    7,
    11,
    12,
    10,
    5,
    12,
    11,
    7,
    10,
    7,
    6,
};



const float threshold = 0.5f; // Can mess around with, once looking at more, messier data. Should probably put in the header file.

void moduleCluster2d(data_t energy[NUM_CELLS], int clusterArray[NUM_CELLS], int &numClusters) {
// Can partition the clusterArray, decreases latency from 224 to 165 for one energy above the threshold (and no other nonzero energies),
// but increases FFs and LUTs from 491 and 904 to 4997 and 5215 respectively (~5-10 times).
// You may also be able to partition clusterArray in a smarter, noncomplete way that saves space and/or latency.
#pragma HLS ARRAY_PARTITION variable=clusterArray complete

    int queue[NUM_CELLS];
    bool hitFound = false;

    for (int i=0; i<NUM_CELLS; i++) {
        if (energy[i] > threshold) {
            clusterArray[i]=-1;
            hitFound = true;}
        else {
            clusterArray[i]=-2;}
    }

    if (!hitFound) {
        numClusters = 0;
        return;
    }

    for (int seed=0; seed<NUM_CELLS; seed++) {
        if (clusterArray[seed] != -1)
            continue;
        
        int front = 0;
        int back = 0;

        queue[back++] = seed;

        clusterArray[seed] = numClusters;

        while (front < back) {
            int current = queue[front++];

            for (int k=0; k<numNeighbors[current]; k++) {
#pragma HLS LOOP_TRIPCOUNT min=5 max=12 avg=8 //these numbers will likely have to change with more complete geometry
                int neighbor = neighborArray[current][k];

                if (clusterArray[neighbor] != -1)
                    continue;
                
                clusterArray[neighbor] = numClusters;
                queue[back++] = neighbor;
            }
        }
        numClusters++;
    }
}
