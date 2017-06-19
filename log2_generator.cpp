#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "log2_lshift16.h"

const unsigned SIZE = 131072*8*1024; // 1024MB of input bytes

int main(){
    unsigned old_log_val = 256;
    bool gen = 0;
    if (gen) {
        for (int i = 1; i < SIZE; i++) {
            double fraction = (double) i/ (double) SIZE;
            unsigned fraction_lshift16 = fraction*65536;
            int new_log_val = log2(fraction)*16;
            if (old_log_val != new_log_val) {
                printf("if (lshift16 < %u) return %i;\n", fraction_lshift16, old_log_val);
                old_log_val = new_log_val;
                if (old_log_val == 0)
                    break;
            }
        }
    } else {
        printf("fraction fraction*65536 log2() == log2_lshift16()\n");
        for (int i = 1; i < SIZE; i++) {
            double fraction = (double) i/ (double) SIZE;
            unsigned fraction_lshift16 = fraction*65536;
            int new_log_val = log2(fraction)*16;
            if (old_log_val != new_log_val) {
                //printf("if (lshift16 < %u) return %i;\n", fraction_lshift16, old_log_val);
                old_log_val = new_log_val;
                printf("%i/%i %f %i == %i\n", i, SIZE, fraction*65536, new_log_val, log2_lshift16(fraction*65536));
                if (old_log_val == 0)
                    break;
            }
        }
    }
}
