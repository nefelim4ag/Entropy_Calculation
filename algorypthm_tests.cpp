#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <sys/time.h>
#include <time.h>       /* time */
#include "log2_lshift16.h"

using namespace std;

const uint32_t SIZE = 128*1024*8*4; // 4MB

int main(){
    srand (time(NULL));
    uint8_t PAGE[SIZE];

    // Gen test data
    uint32_t *P4B = (uint32_t *) PAGE;
    for (uint32_t i = 0; i < SIZE/4; i++) {
        P4B[i]=rand()*rand();
    }

    for (uint32_t i = 0; i < SIZE/4; i++) {
        if (rand()%32 == 256) P4B[i]=32;
    }

    { // AVG Meaning calculation
        int64_t sum = 0;
        int64_t avg;
        int64_t entropy;

        uint32_t *P4B = (uint32_t *) PAGE;
        for (uint32_t i = 0; i < SIZE/4; i++) {
            sum+=P4B[i];
        }

        avg = sum / (SIZE/4);
        entropy = 100000 - abs(100000 - avg*100000/2147483648); // 0-100000
        cout << "AVG Meaning: " << avg << " <> Entropy lvl: " << entropy << '\n';
    }
    { // Shannon entropy calculation
        uint8_t *P1B = (uint8_t *) PAGE;
        uint64_t *array = (uint64_t *) calloc(256, sizeof(uint64_t));

        for (uint32_t i = 0; i < SIZE; i++)
            array[P1B[i]]++;

        {
            double entropy = 0;
            for (uint16_t i = 0; i < 256; i++) {
                if (array[i] == 0) continue;
                double val = array[i]*1.0/SIZE;
                entropy += -(val)*log2(val);
            }
            cout << "Schanon true entropy: " << entropy << "/8 == " << entropy*100/8 << "%" << '\n';
        }
        { // Shannon integer entropy calculation
            uint64_t entropy = 0;
            double   entropy_d = 0;
            for (uint16_t i = 0; i < 256; i++) {
                if (array[i] == 0) continue;
                uint64_t val = array[i]*65536/SIZE;
                entropy += -val*log2_lshift16(val);
            }
            entropy_d = entropy;
            cout << "Schanon integer entropy: " << entropy/65536 << "/512 == " \
                 << entropy_d*100/65536/512 << "%" << '\n';
        }
        free(array);
    }
}
