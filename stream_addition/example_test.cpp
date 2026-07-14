#include "example.h"
#include <fstream>
#include <sstream>
#include <vector>

int main() {

    std::ifstream infile("root_data.txt");

    if (!infile.is_open()) {
        std::cerr << "Could not open root_data.txt\n";
        return 1;
    }

    std::string line;
    int event = 0;
    bool passed = true;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        hls::stream<float> s_in;
        std::vector<float> energies;
        float energy;

        while (ss >> energy) {
            energies.push_back(energy);
            s_in.write(energy)
        }

        int numHits = energies.size();
        float expected = 0.0f;

        for (float e : energies) {
            expected += e;
        }

        float result = dut(s_in, numHits);

        if (std::abs(result - expected) < 1e-6f) {
            std::cout << "Event " << event
                      << " PASSED"
                      << std::endl;
        } else {
            std::cout << "Event " << event
                      << " FAILED"
                      << std::endl;

            std::cout << "Expected = "
                      << expected
                      << std:endl;

            std::cout << "Got      = "
                      << result
                      << std::endl;

            passed = false;
        }

        event++;
    }

    if (passed) {
        std::cout << "\nAll tests passed!" << std::endl;
        return 0;
    }
    else {
        std::cout << "\nOne or more tests failed." << std::endl;
        return 1;
    }
}


/*int main() {

    std::ifstream infile("root_data.txt");
    std::string line;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        hls::stream<flot> s_in;
        std::vector<float> energies;
        float value;

        while (ss >> value) {
            energies.push_back(value);
            s_in.write(value);
        }

        int numHits = energies.size();
        float result = dut(s_in, numHits);

        std::cout
            << "Hits = "
            << numHits
            << "    Total Energy = "
            << result
            << std::endl;
    }

    return 0;
}
