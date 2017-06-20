#include <fstream>

/* AVG Meaning calculation for file */
int main() {
    int64_t sum = 0;
    uint64_t count = 0;
    int64_t avg, entropy;

    std::ifstream infile("indata.bin");

    if (!infile.is_open()) {
        printf("Can't open file: ./indata.bin\n");
        return 1;
    }

    uint32_t B4[4];
    while (!infile.eof()) {
        infile.read((char *) &B4, sizeof(B4));
        for (uint8_t i = 0; i < sizeof(B4)/sizeof(uint32_t); i++) {
            sum+=B4[i];
        }
        count+=4;
    }

    avg = sum / count;
    entropy = 100000 - abs(100000 - avg*100000/2147483648); // 0-100000
    printf("AVG Meaning: %li ~= Entropy lvl: %li\n", avg, entropy);
}
