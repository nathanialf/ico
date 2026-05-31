#include "matching.h"

void func_00193F68(short *p) {
    *(volatile short *)(p + 1) = 1;
    KEEP_LIVE_MEM(p);
    p[0] = 1;
}
