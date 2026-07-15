#include "example.h"
#include <iostream>
#include <fstream>
#include <cmath>


int main() {

    std::ifstream fin("root_data_dense_1event.txt");

    if (!fin) {
        std::cout << "Could not open root_data_dense_1event.txt\n";
        return 1;
    }

    for (int event = 0; event < 1; event++) {

        std::cout << "Event " << event << "\n";

        sum_t event_expected = 0;
        sum_t event_result = 0;


        for (int layer = 0; layer < 32; layer++) {

            std::cout << "Layer " << layer << "\n";

            sum_t layer_expected = 0;
            sum_t layer_result = 0;

            for (int module = 0; module < 7; module++) {

                data_t input[48];
                sum_t expected = 0;

                for (int i=0; i<48; i++) {

                    float value;

                    if (!(fin >> value)) {
                        std::cout << "Read failed at index " << layer << ", module " << module << ", cell " << i << "\n";
                        return 1;
                    }

                    input[i] = value;
                    expected += sum_t(value);
                }

                sum_t result = add48(input);

                layer_expected += expected;
                layer_result += result;

                std::cout << "Module " << module << " Expected = " << (float)expected << " Result = " << (float)result;

                if (std::fabs((float)(expected - result)) < 1e-3) 
                    std::cout << " PASS\n";
                else {
                    std::cout << " FAIL\n";
                    return 1;
                }
            }

            event_expected += layer_expected;
            event_result += layer_result;

            std::cout << "Layer " << layer << " Layer Expected = " << (float)layer_expected << " Layer Result = " << (float)layer_result;

            if (std::fabs((float)(layer_expected - layer_result)) < 1e-3)
                std::cout << " PASS\n";
            else {
                std::cout << " FAIL\n";
                return 1;
            }
            
            std::cout << "\n";
        }

        std::cout << "Event " << event << " Event Expected = " << (float)event_expected << " Event Result = " << (float)event_result;

        if (std::fabs((float)(event_expected - event_result)) < 1e-3)
            std::cout << " PASS\n";
        else {
            std::cout << " FAIL\n";
            return 1;
        }

        std::cout << "\n";
    }

    return 0;
}
