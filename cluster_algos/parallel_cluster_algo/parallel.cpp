#include "parallel.h"

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

const data_t threshold = 0.01;
const int MAX_ITER = 7; // This is a guesstimate for max number of neighbor relations between two cells in one module, 
// needs to be determined for a layer.

void computeNext(
    data_t energy[NUM_CELLS],
    int next[NUM_CELLS]
) {
#pragma HLS ARRAY_PARTITION variable=energy complete
#pragma HLS ARRAY_PARTITION variable=next complete
#pragma HLS ARRAY_PARTITION variable=neighborArray complete dim=2 // Vitis HLS should already infer this, just have it here in case something breaks.
// You can inline computeNext also, but it does not change latency. It only changes FFs from 4034 to 5278 and LUTs from 17068 to 16810.

for_each_cell:
    for(int cell=0; cell<NUM_CELLS; cell++) {
#pragma HLS UNROLL // You can unroll this instead of pipelining, which decreases latency from 61 to 11, and clock from 7.152 to 6.96,
// BUT this increases LUTs from 17043 to 44717, AND increases FFs from 4034 to 7555.

        if(energy[cell] < threshold) {
            next[cell] = -1;
            continue;
        }

        int best = cell;
        data_t bestEnergy = energy[cell];
check_neighbors:
        for (int k=0; k<MAX_NEIGHBORS; k++) {
#pragma HLS UNROLL
            int n = neighborArray[cell][k];

            if (n == -1)
                continue;
            
            if (energy[n] > bestEnergy) {
                    best = n;
                    bestEnergy = energy[n];
            }
        }
        next[cell] = best;
    }
}

void compressPaths(int next[NUM_CELLS]) {
#pragma HLS ARRAY_PARTITION variable=next complete

    int temp[NUM_CELLS];
#pragma HLS ARRAY_PARTITION variable=temp complete

    for (int iter=0; iter<MAX_ITER; iter++) {
compress:
        for (int i=0; i<NUM_CELLS; i++) {
#pragma HLS UNROLL

            if (next[i] < 0)
                temp[i] = -1;
            else
                temp[i] = next[next[i]];
        }
copy:
        for (int i=0; i<NUM_CELLS; i++) {
#pragma HLS UNROLL
            next[i] = temp[i];
        }
    }
}

void moduleCluster2d(
    data_t energy[NUM_CELLS],
    int labels[NUM_CELLS]
) {
#pragma HLS ARRAY_PARTITION variable=energy complete
#pragma HLS ARRAY_PARTITION variable=labels complete
// You can add dataflow, but this only decreases latency by like 3 and increases FFs and LUTs from ~4000 & 17000 to ~18000 & 25000.

    int next[NUM_CELLS];
#pragma HLS ARRAY_PARTITION variable=next complete

    computeNext(energy, next);
    compressPaths(next);

assign:
    for (int i=0; i<NUM_CELLS; i++) {
#pragma HLS UNROLL
        labels[i] = next[i];
    }
}
