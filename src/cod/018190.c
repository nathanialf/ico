#include "vu0.h"

void func_00118190(void)
{
    VU0_V3OP(vsub.xyzw, 1, 0, 0);
    VU0_V3OP_BC(vsubw.x, 2, 0, 0, w);
    VU0_V3OP_BC(vaddx.y, 14, 1, 5, x);
    VU0_V3OP_BC(vaddx.z, 14, 1, 6, x);
    VU0_V3OP_BC(vaddy.x, 15, 1, 4, y);
    VU0_V3OP_BC(vaddy.z, 15, 1, 6, y);
    VU0_V3OP_BC(vaddz.x, 16, 1, 4, z);
    VU0_V3OP_BC(vaddz.y, 16, 1, 5, z);
    VU0_V3OP_BC(vmulx.xyz, 17, 7, 2, x);
    VU0_V2OP(vmove.yz, 4, 14);
    VU0_V2OP(vmove.xz, 5, 15);
    VU0_V2OP(vmove.xy, 6, 16);
    VU0_V2OP(vmove.w, 17, 0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 0, 17, w);
    VU0_NOP();
}
