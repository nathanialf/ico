#include "matching.h"

typedef struct {
    long long a __attribute__((packed));
    long long b __attribute__((packed));
    int c;
} R20;

extern R20 D_005507A8;

R20 *func_00244920(R20 *dst)
{
    *dst = D_005507A8;
    return dst;
}
