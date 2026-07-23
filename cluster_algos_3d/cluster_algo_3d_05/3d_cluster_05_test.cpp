#include "3d_cluster_05.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    data_t energy[NUM_LAYERS][NUM_CELLS];
    ap_uint<11> cluster[NUM_LAYERS][NUM_CELLS];

    ifstream infile("test_data.txt");

    if (!infile) {
        cout << "Could not open test_data.txt\n";
        return 1;
    }

    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        for (int cell = 0; cell < NUM_CELLS; cell++) {
            if (!(infile >> energy[layer][cell])) {
                cout << "Error reading energy " << layer << "cell" << cell << "\n";
                return 1;
            }
        }
    }

    infile.close();

    clusterTop(energy, cluster);

    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        cout << "Layer " << layer << "\n";

        for (int cell = 0; cell < NUM_CELLS; cell++) {
            if (cluster[layer][cell] != INVALID_CLUSTER) {
                cout << "   Cell " << cell << " Cluster = " << cluster[layer][cell] << "\n";
            }
        }

        cout << "\n";
    }

    return 0;
}