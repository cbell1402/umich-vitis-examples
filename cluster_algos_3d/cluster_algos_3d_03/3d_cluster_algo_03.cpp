#include "3d_cluster_algo_03.h"

// neighborArray tracks which cells are whose neighbors.
const int neighborArray[NUM_CELLS][MAX_NEIGHBORS_2D] = {
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

const data_t threshold = 0.01; // Threshold energy for what is considered a hit while making the local maxima.
const int MAX_ITER = 7; // This is a guesstimate for max number of neighbor relations between two cells in one module, 
// This should be explicitly determined for a layer. 
// Can also reduce to maybe 1 or 2 if we want to reduce cluster size (although this would require some edits to the logic).
const int COMPRESS_ITERS = 5;

// Gives the greater of 2 values, used for comparing neighbors' energies in clusterMaxima2d.
Candidate2d max2(Candidate2d a, Candidate2d b) {
#pragma HLS INLINE
    return (a.energy >= b.energy) ? a : b;
}

// Finds the local maxima in each layer.
void clusterMaxima2d(
    data_t energy[NUM_CELLS],
    bool maxima[NUM_CELLS]
) {
#pragma HLS ARRAY_PARTITION variable=energy complete
#pragma HLS ARRAY_PARTITION variable=maxima complete
#pragma HLS ARRAY_PARTITION variable=neighborArray complete dim=2

for_each_cell:
    for(int cell=0; cell<NUM_CELLS; cell++) {
#pragma HLS UNROLL

        if(energy[cell] < threshold) {
            maxima[cell] = false;
            continue;
        }

        Candidate2d c[13];
#pragma HLS ARRAY_PARTITION variable=c complete

        c[0].energy = energy[cell];
        c[0].label = cell;

        for (int k=0; k<MAX_NEIGHBORS_2D; k++) {
#pragma HLS UNROLL

            int n = neighborArray[cell][k];

            if (n == -1) {
                    c[k+1].energy = -1;
                    c[k+1].label = -1;
            } else {
                c[k+1].energy = energy[n];
                c[k+1].label = n;
            }
        }

        Candidate2d l1[7];
#pragma HLS ARRAY_PARTITION variable=l1 complete

        l1[0]=max2(c[0],c[1]);
        l1[1]=max2(c[2],c[3]);
        l1[2]=max2(c[4],c[5]);
        l1[3]=max2(c[6],c[7]);
        l1[4]=max2(c[8],c[9]);
        l1[5]=max2(c[10],c[11]);
        l1[6]=c[12];

        Candidate2d l2[4];
#pragma HLS ARRAY_PARTITION variable=l2 complete

        l2[0]=max2(l1[0],l1[1]);
        l2[1]=max2(l1[2],l1[3]);
        l2[2]=max2(l1[4],l1[5]);
        l2[3]=l1[6];

        Candidate2d l3[2];
#pragma HLS ARRAY_PARTITION variable=l3 complete

        l3[0]=max2(l2[0],l2[1]);
        l3[1]=max2(l2[2],l2[3]);

        Candidate2d winner = max2(l3[0],l3[1]);

        maxima[cell] = (winner.label == cell);
    }
}

// Helper function to store the layer and cell index for each unique cell.
parent_t makeIndex(int layer, int cell) {
#pragma HLS INLINE

    parent_t p;
    p.layer = layer;
    p.cell = cell;
    return p;
}

// Creates an array of pointers that point to the local maxima in the neighboring cells in the layer behind a given local maxima.
// If there are none, then it points to itself.
void buildClusterPointers(
    bool maxima[NUM_LAYERS][NUM_CELLS],
    parent_t clusterPointer[NUM_LAYERS][NUM_CELLS]
)
{
#pragma HLS ARRAY_PARTITION variable=maxima complete dim=2
#pragma HLS ARRAY_PARTITION variable=clusterPointer complete dim=2

init:
    for (int l=0; l<NUM_LAYERS; l++) {
        for (int c=0; c<NUM_CELLS; c++) {
#pragma HLS UNROLL
            clusterPointer[l][c] = makeIndex(l,c);
        }
    }

layers:
    for (int l=0; l<NUM_LAYERS-1; l++) {

cells:
        for (int c=0; c<NUM_CELLS; c++) {
#pragma HLS UNROLL

            if (!maxima[l][c]) {
                continue;
            }

            if (maxima[l+1][c]) {
                clusterPointer[l][c] = makeIndex(l+1, c);
                continue;
            }

            bool found=false;

neighbors:
            for (int k=0; k<MAX_NEIGHBORS_2D ;k++) {
#pragma HLS UNROLL

                int n = neighborArray[c][k];

                if (n == -1)
                    continue;

                if (maxima[l+1][n] && !found) {
                    clusterPointer[l][c] = makeIndex(l+1, n);
                    found=true;
                }
            }
        }
    }
}

// This compresses the pointers over 32 interations to make each pointer now point to the root.
// The root is the local maximum in a cluster that is furthest back.
void compressClusterPointers(
    bool maxima[NUM_LAYERS][NUM_CELLS],
    parent_t clusterPointer[NUM_LAYERS][NUM_CELLS]
) {
#pragma HLS ARRAY_PARTITION variable=maxima complete dim=2
#pragma HLS ARRAY_PARTITION variable=clusterPointer complete dim=2

    parent_t temp[NUM_LAYERS][NUM_CELLS];
#pragma HLS ARRAY_PARTITION variable=temp complete dim=2

compress_iter:
    for (int iter=0; iter<COMPRESS_ITERS; iter++) {

compress_read:
        for (int l = 0; l<NUM_LAYERS; l++) {

compress_cells:
            for (int c=0; c<NUM_CELLS; c++) {
#pragma HLS UNROLL

                if (!maxima[l][c]) {
                    temp[l][c] = clusterPointer[l][c];
                    continue;
                }

                parent_t parent = clusterPointer[l][c];

                if (parent.layer == l && parent.cell == c) {
                    temp[l][c] = parent;
                } else {
                    temp[l][c] = clusterPointer[parent.layer][parent.cell];
                }
            }
        }

copy_back:
        for (int l=0; l<NUM_LAYERS; l++) {
            for (int c=0; c<NUM_CELLS; c++) {
#pragma HLS UNROLL
                clusterPointer[l][c] = temp[l][c];
            }
        }
    }
}

// This step creates a cluster ID array that lists -1 for all cells that aren't maxima and the root for any that are.
// This is necessary since the buildClusterPointers does not consider whether a cell is a local maximum.
void makeClusters(
    bool maxima[NUM_LAYERS][NUM_CELLS],
    parent_t clusterPointer[NUM_LAYERS][NUM_CELLS],
    int cluster[NUM_LAYERS][NUM_CELLS]
) {
#pragma HLS ARRAY_PARTITION variable=maxima complete dim=2
#pragma HLS ARRAY_PARTITION variable=clusterPointer complete dim=2
#pragma HLS ARRAY_PARTITION variable=cluster complete dim=2

assign:
    for (int l=0; l<NUM_LAYERS; l++) {
        for (int c=0; c<NUM_CELLS; c++) {
#pragma HLS UNROLL

            if (!maxima[l][c]) {
                cluster[l][c] = -1;
                continue;
            }

            parent_t root = clusterPointer[l][c];

            cluster[l][c] = root.layer*NUM_CELLS + root.cell;
        }
    }
}

// This is the top function.
void clusterTop(
    data_t energy[NUM_LAYERS][NUM_CELLS],
    int cluster[NUM_LAYERS][NUM_CELLS]
) {
#pragma HLS ARRAY_PARTITION variable=energy complete dim=2
#pragma HLS ARRAY_PARTITION variable=cluster complete dim=2

    bool maxima[NUM_LAYERS][NUM_CELLS];
#pragma HLS ARRAY_PARTITION variable=maxima complete dim=2

    parent_t clusterPointer[NUM_LAYERS][NUM_CELLS];
#pragma HLS ARRAY_PARTITION variable=clusterPointer complete dim=2

layer_loop:
    for (int l=0; l<NUM_LAYERS; l++) {
        clusterMaxima2d(
            energy[l],
            maxima[l]
        );
    }

    buildClusterPointers(
        maxima,
        clusterPointer
    );

    compressClusterPointers(
        maxima,
        clusterPointer
    );

    makeClusters(
        maxima,
        clusterPointer,
        cluster
    );
}
