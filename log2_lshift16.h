/*
 * Precalculated log2 values
 * Shifting used for avoiding floating point
 * Fraction must be left shifted by 16
 * Return of log are left shifted by 6
 */
 
#define LOG2_ARG_SHIFT (1 << 16)
#define LOG2_RET_SHIFT (1 << 6)
int log2_lshift16(long long unsigned lshift16);
