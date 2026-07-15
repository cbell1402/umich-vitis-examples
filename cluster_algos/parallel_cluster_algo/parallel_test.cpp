#include "parallel.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    data_t energy[NUM_CELLS];

    ifstream infile("test_data.txt");

    if (!infile) {
        cout << "Could not open test_data.txt\n";
        return 1;
    }

    for (int i=0; i<NUM_CELLS; i++) {
        if (!(infile >> energy[i])) {
            cout << "Error reading energy " << i << "\n";
            return 1;
        }
    }

    infile.close();

    int labels[NUM_CELLS];

    moduleCluster2d(energy, labels);

    for (int i=0; i<NUM_CELLS; i++) {
        if (energy[i] > 0) {
            cout << "Cell " << i << " Energy = " << energy[i] << "  Cluster = " << labels[i] << "\n";
        }
    }

    cout << "\n";
    return 0;
}