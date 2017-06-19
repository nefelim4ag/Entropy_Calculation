#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

/* Shannon entropy calculation */
int main() {
    int64_t count = 0;

    uint64_t *array = (uint64_t *) calloc(256, sizeof(uint64_t));

    std::ifstream infile("indata.bin");

    if (infile.is_open()) {
        std::cout << "Open file: ./indata.bin\n";
    } else {
        std::cout << "Can't open file: ./indata.bin\n";
        return 1;
    }


    while (!infile.eof()) {
        uint8_t B4[8];
        infile.read((char *) &B4, sizeof(B4));
        array[B4[0]]++;
        array[B4[1]]++;
        array[B4[2]]++;
        array[B4[3]]++;
        array[B4[4]]++;
        array[B4[5]]++;
        array[B4[6]]++;
        array[B4[7]]++;
        count+=8;
    }


    double entropy = 0;
    for (uint16_t i = 0; i < 256; i++) {
        if (array[i] == 0) continue;
        double val = array[i]*1.0/count;
        entropy += -(val)*log2(val);
    }
    std::cout << "Schanon true entropy: " << entropy << "/8 == " << entropy*100/8 << "%" << '\n';

    free(array);
}
