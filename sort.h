#include <stdint.h>

static int compare(const void *lhs, const void *rhs) {
    int lhs_integer = *(const int *)(lhs);
    int rhs_integer = *(const int *)(rhs);
    return rhs_integer - lhs_integer;
}

void sort(
    void *base, uint64_t num, uint64_t size,
    int (*cmp_func)(const void *, const void *),
    void (*swap_func)(void *, void *, int size));
