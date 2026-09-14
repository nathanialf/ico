#define MV_DEFS_WANT_ALLOC

#include "common.h"
#include "mv_defs.h"

int readBufCreate(int *self)
{
    int buf;

    buf = alloc_zeroed(0x50000, 0x40);
    self[0] = buf;
    if (buf == 0) {
        return -1;
    }
    self[1] = 0x50000;
    self[2] = self[3] = 0;
    return 0;
}

void readBufDelete(void) {}

int readBufBeginPut(int *a0, int *a1)
{
    int new_var;
    int diff = a0[1] - a0[3];
    if (diff != 0) {
        new_var = a0[2];
        a1[0] = a0[0] + new_var;
    }
    return diff;
}

void readBufEndPut(int *a0, int a1)
{
    int size;
    int pos;
    int cum;
    int remaining;
    int step;
    size = a0[1];
    cum = a0[3];
    pos = a0[2];
    remaining = size - cum;
    step = (a1 < remaining) ? (a1) : (remaining);
    pos += step;
    cum = cum + step;
    a0[2] = pos % size;
    a0[3] = cum;
}

int readBufBeginGet(int *a0, int *out)
{
    int a2 = a0[3];
    if (a2 != 0) {
        int v1 = a0[2] - a2;
        int divisor = a0[1];
        v1 = v1 + divisor;
        *out = a0[0] + (v1 % divisor);
    }
    return a2;
}

int readBufEndGet(int a0, int a1)
{
    int rest = *(int *)(a0 + 0xC);
    if (a1 < rest) {
        rest = a1;
    }
    *(int *)(a0 + 0xC) -= rest;
    return rest;
}
