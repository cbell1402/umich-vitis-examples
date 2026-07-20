#include "3d_cluster_02.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    data_t energy[NUM_LAYERS][NUM_CELLS];
    bool maxima[NUM_LAYERS][NUM_CELLS];
    int cluster[NUM_LAYERS][NUM_CELLS];

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

    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        clusterMaxima2d(energy[layer], maxima[layer]);
    }

    cluster3d(maxima,cluster);

    cout << "Local maxima:\n\n";

    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        cout << "Layer " << layer << "\n";
        for (int cell = 0; cell < NUM_CELLS; cell++) {
            if (maxima[layer][cell]) {
            cout << "   Cell " << cell
                << " Cluster = "<< cluster[layer][cell]
                << "\n";
            }
        }
        cout << "\n";
    }

    return 0;
}