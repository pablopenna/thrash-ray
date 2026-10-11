#ifndef UTIL_MATH_H
#define UTIL_MATH_H

static inline int imax(int a, int b) { return a > b ? a : b; }
static inline int imin(int a, int b) { return a < b ? a : b; }

static inline int iClamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

#endif
