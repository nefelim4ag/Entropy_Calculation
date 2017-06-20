#include <fstream>
#include <cmath>

/* Shannon entropy calculation */
#define BUCKET_SIZE 1 << 8

int main() {
    int64_t count = 0;
    double entropy = 0;

    /*
     * For small data set it's possible to change size of word
     * input data size <= 65536 byte - uint16_t
     * input data size <= 4294967296 byte - uint32_t
     */
    uint32_t *array = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));

    std::ifstream infile("indata.bin");

    if (!infile.is_open()) {
        printf("Can't open file: ./indata.bin\n");
        return 1;
    }

    /* Try add compiller some space for vectorization */
    while (!infile.eof()) {
        uint8_t B4[8];
        infile.read((char *) &B4, sizeof(B4));
        for (uint8_t i = 0; i < sizeof(B4); i++) {
            array[B4[i]]++;
        }
        count+=sizeof(B4);
    }

    for (uint16_t i = 0; i < BUCKET_SIZE; i++) {
        if (array[i]) {
            double val = array[i];
            val = val/count;
            entropy += -(val)*log2(val);
        }
    }

    printf("Schanon true entropy: %f/8 ~= %f%%\n", entropy, entropy*100/8);
    free(array);
}
