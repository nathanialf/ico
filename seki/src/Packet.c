#include "common.h"
#include "vu0.h"

float pac_DispQW(void) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "vrnext.x $vf1, $R\n"
        "vsubw.x $vf1, $vf1, $vf0w\n"
        "qmfc2.ni $7, $vf1\n"
        "mtc1 $7, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$7");
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_DumpPac);

void pac_makeBoundingBox(void *a0) {
    VU0_REG("vrnext.xyz $vf1, $R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, 4);
    VU0_NOP();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_error);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makeNormalStrip);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_getWeight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makeClusterStrip);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_openDmaTag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_setVifCode);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_setVifEndCode);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_setGifTag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_closeTag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_continueTag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_checkDivide);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_countOneVertexPacketSize);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makeStrip);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_setMaterialPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makeMaterialTable);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makeMaterialTableLine);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_getTextureInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makeShapeTable);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makePacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_MakePacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_Dump);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_DispVu1Memory);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", func_0011B2A0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", func_0011B468);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", func_0011B618);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", func_0011B788);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", func_0011BB00);

extern void func_0011BB00(void *a0, int a1, int a2);

void func_0011C308(void *a0) {
    void *p = *(void **)((char *)a0 + 0x810);
    void *q = *(void **)((char *)a0 + 0x834);
    func_0011BB00(p, *(int *)((char *)q + 0xF0), *(signed char *)((char *)p + 0x2F) > 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", func_0011C328);
