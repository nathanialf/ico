#include "vu0.h"

void func_00117C20(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(a2, 12);
    VU0_QMTC2_NI(a2, 1);
    VU0_NOREORDER_END();
    VU0_WORD(0x4A0103BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(a3, 22);
    VU0_MTC1(a3, 0);
    VU0_NOREORDER_END();
}
