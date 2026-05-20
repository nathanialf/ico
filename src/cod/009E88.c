#include "matching.h"

typedef struct { long long w[62]; } _0x1F0;

extern int func_001442E0(void);
extern _0x1F0 D_00275DB0;

void func_00109E88(_0x1F0 *self) {
    *self = D_00275DB0;
    *(int *)((char *)self + 0x1AC) = func_001442E0();
    *(int *)((char *)self + 0x1B0) = func_001442E0();
}
