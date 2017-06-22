#include <stdint.h>
#include <stdbool.h>

enum compress_advice {
    COMPRESS_NONE,
    COMPRESS_COST_EASY,
    COMPRESS_COST_MEDIUM,
    COMPRESS_COST_HARD
};

enum compress_advice heuristic(const uint8_t *input_data,
    const uint64_t bytes_len);
