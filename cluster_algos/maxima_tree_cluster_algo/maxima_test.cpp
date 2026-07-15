#include "maxima.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    data_t energy[NUM_CELLS];

    ifstream infile("test_data.txt");

    if (!infile) {
        cout << "Could not open test_data.txt\n";
        return 1;
    }

    for (int i = 0; i < NUM_CELLS; i++) {
        if (!(infile >> energy[i])) {
            cout << "Error reading energy " << i << "\n";
            return 1;
        }
    }

    infile.close();

    bool labels[NUM_CELLS];

    clusterMaxima(energy, labels);

    for (int i = 0; i < NUM_CELLS; i++) {
        cout << "Cell " << i
             << " Label = "<< labels[i]
             << "\n";
    }

    return 0;
}