#include "vu0.h"

void func_00117C20(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("mfc1 $a2, $f12");
    VU0_MOVE("qmtc2.ni $a2, $vf1");
    VU0_NOREORDER_END();
    VU0_WORD(0x4A0103BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("cfc2.ni $a3, $vi22");
    VU0_MOVE("mtc1 $a3, $f0");
    VU0_NOREORDER_END();
}
