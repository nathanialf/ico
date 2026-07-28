#include "common.h"




extern void debug_assertMessage();
extern char D_00672FD0[];
extern int D_00672F90[];
extern int D_00633C3C;
#include "vu0.h"
INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_DispQW);

void pac_DumpPac(void *p0)
{
    VU0_REG("vrnext.x $vf1, $R");
    VU0_REG("vrnext.y $vf1, $R");
    VU0_REG("vrnext.z $vf1, $R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void pac_makeBoundingBox(void *p0)
{
    VU0_REG("vrnext.xyz $vf1, $R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void pac_error(void *p0, void *p1)
{
    VU0_LSV(lqc2, 8, 0x0, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 8, w);
    VU0_REG("vdiv $Q, $vf0w, $vf10w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf10, $vf10, $Q");
    VU0_V2OP(vftoi4.xyz, 10, 10);
    VU0_V3OP(vsub.xy, 14, 10, 11);
    VU0_V3OP(vsub.xy, 15, 12, 11);
    VU0_V3OP(vsub.zw, 14, 14, 14);
    VU0_V3OP(vsub.zw, 15, 15, 15);
    VU0_V3OP_ACC(vopmula.xyz, 14, 15);
    VU0_V3OP(vopmsub.xyz, 16, 15, 14);
    VU0_V2OP(vmr32.y, 16, 16);
    VU0_V2OP(vmr32.x, 16, 16);
    VU0_LSV(sqc2, 10, 0x0, a0);
    VU0_QMFC2_NI(a3, 16);
    VU0_MTC1(a3, 0);
    VU0_V2OP(vmove.xy, 12, 11);
    VU0_V2OP(vmove.xy, 11, 10);
    VU0_NOP();
}

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeNormalStrip);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_getWeight);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeClusterStrip);

void pac_openDmaTag(void)
{
    int *p = D_00672F90;
    int i = 0xC;
    D_00633C3C = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

void pac_setVifCode(void)
{
    int *p = D_00672F90;
    int i = 0xC;
    D_00633C3C = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_setVifEndCode);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_setGifTag);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_closeTag);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_continueTag);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_checkDivide);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_countOneVertexPacketSize);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeStrip);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_setMaterialPacket);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeMaterialTable);

void pac_makeMaterialTableLine(void)
{
    register char *base = D_00672FD0;
    volatile int * volatile *curp = (volatile int * volatile *)(base + 0x2C);
    volatile int *p = *curp;
    *p++ = 0x17000000;
    *curp = p;
    p[0] = 0;
    *curp = p + 1;
    p[1] = 0;
    *curp = p + 2;
    p[2] = 0;
    *curp = p + 3;
    debug_assertMessage((const char *)(p + 3));
}

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_getTextureInfo);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makeShapeTable);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_makePacket);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_MakePacket);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_Dump);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_Init);

INCLUDE_ASM("asm/nonmatchings/src/Packet", pac_DispVu1Memory);

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011AE78);

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011B040);

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011B1F0);

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011B360);

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011B6D8);

void func_0011BF40(int a0)
{
    int v = *(int *)(a0 + 0x820);
    int p = *(int *)(a0 + 0x844);
    func_0011B6D8(v, *(int *)(p + 0xF0), *(signed char *)(v + 0x2F) > 0);
}

void func_0011BF60(int *a0, int size)
{
    int *p = a0;
    int count;
    size >>= 4;
    if (size <= 0)
        return;
    count = size;
    do {
        int *arg = p;
        p += 4;
        pac_setVifEndCode(arg, 4);
        count--;
    } while (count != 0);
}

