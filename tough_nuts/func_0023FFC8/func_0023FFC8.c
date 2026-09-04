#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

extern int D_0062BEA0;

void MakeBoundingBox(void) {
    D_0062BEA0 = 0;
}

int MakePacket(void) {
    return D_0062BEA0;
}

extern int D_0070C340[];

int AllocPObj(int a0) {
    return D_0070C340[a0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", GetGObjId);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", PrintGObjID);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D260);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D3C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D4E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D7F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D910);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023DDC0);

extern void *D_006281F8[];
extern void debug_StdPrintfDummy(void *a0);
void FreePObj(void) {
    do {
        debug_StdPrintfDummy(D_006281F8);
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", DrawVObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SetVObjRT);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsResetGraph);

extern int D_0054A960[];

void *func_0023E158(void) {
    return D_0054A960;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsResetPath);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsPutDispEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefDrawEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsPutDrawEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefDBuff);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSwapDBuff);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSyncV);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSyncPath);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefTexEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefAlphaEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefLoadImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefStoreImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsExecLoadImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsExecStoreImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsPutIMR);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetHalfOffset);

extern void GsGetIMR(void);

void func_0023FBE8(void) {
    do {
        GsGetIMR();
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGszbufaddr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefClear);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0ApplyMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FE08);

void sceVu0OuterProduct(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP_ACC(vopmula.xyz, 4, 5);
    VU0_V3OP(vopmsub.xyz, 6, 5, 4);
    VU0_V3OP(vsub.w, 6, 6, 6);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

float sceVu0InnerProduct(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "lqc2 $vf5, 0x0($5)\n"
        "vmul.xyz $vf5, $vf4, $vf5\n"
        "vaddy.x $vf5, $vf5, $vf5y\n"
        "vaddz.x $vf5, $vf5, $vf5z\n"
        "qmfc2.ni $2, $vf5\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0Normalize);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0TransposeMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0InversMatrix);

void sceVu0DivVector(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 5);
    VU0_NOREORDER_END();
    VU0_REG("vdiv $Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_REG("vmulq.xyzw $vf4, $vf4, $Q");
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void sceVu0DivVectorXYZ(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 5);
    VU0_NOREORDER_END();
    VU0_REG("vdiv $Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf4, $vf4, $Q");
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void sceVu0InterVector(void *a0, void *a1, void *a2, float t) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x0($6)\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf6\n"
        "vaddw.x $vf7, $vf0, $vf0w\n"
        "vsub.x $vf8, $vf7, $vf6\n"
        "vmulax.xyzw $ACC, $vf4, $vf6x\n"
        "vmaddx.xyzw $vf9, $vf5, $vf8x\n"
        "sqc2 $vf9, 0x0($4)\n" : : : "$8", "memory");
}

void sceVu0AddVector(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vadd.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0SubVector(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vsub.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0MulVector(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vmul.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0ScaleVector(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyzw, 6, 4, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0TransMatrix);

void sceVu0CopyVector(void *a0, void *a1) {
    QCOPY16_NO_NOP("$a2");
}

void sceVu0CopyMatrix(void *a0, void *a1) {
    QCOPY64_PARALLEL_NO_NOP("$a2", "$a3", "$t0", "$t1");
}

void sceVu0FTOI4Vector(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0FTOI0Vector(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0ITOF4Vector(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0ITOF0Vector(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0UnitMatrix(void *a0) {
    __asm__ __volatile__(
        "vsub.xyzw $vf4, $vf0, $vf0\n"
        "vadd.w $vf4, $vf4, $vf0\n"
        "vmr32.xyzw $vf5, $vf4\n"
        "vmr32.xyzw $vf6, $vf5\n"
        "vmr32.xyzw $vf7, $vf6\n"
        "sqc2 $vf4, 0x30($4)\n"
        "sqc2 $vf5, 0x20($4)\n"
        "sqc2 $vf6, 0x10($4)\n"
        "sqc2 $vf7, 0x0($4)\n" : : : "memory");
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240198);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240240);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002402E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0RotMatrix);

void sceVu0ClampVector(void *a0, void *a1, float a2, float a3) {
    VU0_MFC1(8, 12);
    VU0_MFC1(9, 13);
    VU0_LSV(lqc2, 6, 0x0, 5);
    VU0_QMTC2_NI(8, 4);
    VU0_QMTC2_NI(9, 5);
    VU0_V3OP_BC(vmaxx.xyzw, 6, 6, 4, x);
    VU0_V3OP_BC(vminix.xyzw, 6, 6, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0CameraMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0NormalLightMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0LightColorMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0ViewScreenMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0DropShadowMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240878);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002408D0);

void sceVu0CopyVectorXYZ(void *a0, void *a1) {
    ((float *)a0)[0] = ((float *)a1)[0];
    ((float *)a0)[1] = ((float *)a1)[1];
    ((float *)a0)[2] = ((float *)a1)[2];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0InterVectorXYZ);

void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0ClipScreen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0ClipScreen3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240A28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVpu0Reset);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memclr);

extern int D_0054A9D0[];

int sceDmaGetChan(unsigned int a0) {
    if (a0 < 0xA) {
        return D_0054A9D0[a0];
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaReset);

extern int D_0054A9F8_alias[] __asm__("D_0054A9F8");

int sceDmaDebug(int a0) {
    int old = D_0054A9F8_alias[0];
    D_0054A9F8_alias[0] = a0;
    return old;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240C68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaGetEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaPutStallAddr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaSend);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaSendN);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaSendI);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaRecv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaRecvN);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaRecvI);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaSync);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaWatch);

int func_00241588(void *a0) {
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}

int func_002415A8(void *a0) {
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}

void sceVif1PkInit(int *a0, int a1) {
    a0[1] = a1;
    a0[0] = a1;
    a0[2] = 0;
}

int sceVif1PkReset(int *a0) {
    int v = a0[1];
    a0[2] = 0;
    a0[0] = v;
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkTerminate);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241640);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241698);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkOpenDirectCode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkCloseDirectCode);

typedef unsigned int u128_241778 __attribute__((mode(TI)));

void sceVif1PkOpenGifTag(void *a0, u128_241778 a1) {
    void **pp = (void **)a0;
    void *p = *pp;
    *(u128_241778 *)p = a1;
    *(void **)((char *)a0 + 0x14) = p;
    *pp = (char *)p + 0x10;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkCloseGifTag);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkAlign);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkAddGsData);

extern int D_0054AA90[];
extern void sceTtyInit(int a0);

void func_002418E0(int a0) {
    D_0054AA90[0] = 0;
    sceTtyInit(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", VSync);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", VSync2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", write);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", read);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241A88);

int func_00241AB0(void) {
    return -1;
}

int func_00241AB8(void) {
    return -1;
}

int func_00241AC0(void) {
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sbrk);

int func_00241B78(void) {
    return 1;
}

int fstat(void *a0, void *a1) {
    *(long long *)((char *)a1 + 0x48) = 0;
    *(int *)((char *)a1 + 0x4) = 0x2000;
    return 0;
}

int func_00241B98(void) {
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", kill);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241BC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241BF0);

extern volatile int D_0070C680[];

void *QueueInit(int a0) {
    D_0070C680[0] = a0;
    D_0070C680[2] = (int)&D_0070C680[4];
    D_0070C680[1] = 0;
    D_0070C680[3] = (int)&D_0070C680[4];
    return (void *)D_0070C680;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", QueuePeekWriteDone);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", QueuePeekReadDone);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceTtyHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241E58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceTtyRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceTtyInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifInitRpc);

extern void sceSifExitCmd(void);
extern int D_0054AA98[];

void sceSifExitRpc(void) {
    sceSifExitCmd();
    D_0054AA98[0] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceRpcGetPacket);

void _sceRpcFreePacket(void *a0) {
    int *p = (int *)a0;
    p[6] = 0;
    p[4] &= 0xFFFFFFFE;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceRpcGetFPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceRpcGetFPacket2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _request_end);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _request_rdata);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifGetOtherData);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _search_svdata);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _request_bind);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifBindRpc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _request_call);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifCallRpc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifCheckStatRpc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifSetRpcQueue);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifRegisterRpc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifRemoveRpc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifRemoveRpcQueue);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifGetNextRequest);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifExecRequest);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243058);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243098);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", new_iob);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243180);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceFs_Rcv_Intr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceFsSemInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceFsWaitS);

extern int D_0054AB24[];
extern void SignalSema(int a0);

void func_00243628(void) {
    SignalSema(D_0054AB24[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceFsInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002437D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceFsReset);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceClose);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceWrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244410);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIoctl2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceCallCode);

extern int _sceCallCode(void *a0, int a1);

int sceRemove(void *a0) {
    return _sceCallCode(a0, 6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMkdir);

int sceRmdir(void *a0) {
    return _sceCallCode(a0, 8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceFormat);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceAddDrv);

int sceDelDrv(void *a0) {
    return _sceCallCode(a0, 0x10);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDopen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDclose);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGetstat);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceChstat);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceRename);

int sceChdir(void *a0) {
    return _sceCallCode(a0, 0x12);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSync);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMount);

int sceUmount(void *a0) {
    return _sceCallCode(a0, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245DF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDevctl);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSymlink);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceReadlink);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifInitIopHeap);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifAllocIopHeap);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifFreeIopHeap);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifLoadIopHeap);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _lf_bind);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246968);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifLoadFileReset);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246A30);

extern int func_00246A30(void *a0, int a1, int a2, void *a3);

void sceSifLoadModuleBuffer(void *a0, int a1, int a2) {
    int local[4];
    func_00246A30(a0, a1, a2, &local);
}

int func_00246C58(void *a0, int a1, int a2, void *a3) {
    return func_00246A30(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246C78);

extern void func_00246C78(void *a0, int a1, int a2, int a3, int a4);

void sceSifLoadModule(void *a0, int a1, int a2) {
    int local;
    func_00246C78(a0, a1, a2, (int)&local, 0);
}

void sceSifLoadStartModule(void *a0, int a1, int a2, int a3) {
    do {
        func_00246C78(a0, a1, a2, a3, 0);
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246EE0);

extern int func_00246EE0(void *a0, int a1, int a2, int a3);

int sceSifLoadElfPart(void *a0, int a1, int a2) {
    return func_00246EE0(a0, a1, a2, 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifLoadElf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifGetIopAddr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifSetIopAddr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifResetIop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifIsAliveIop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifSyncIop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifRebootIop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _DumpTLB);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", kPutTLBEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", kSetTLBEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", kGetTLBEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", kProbeTLBEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", kExpandScratchPad);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SetTLBHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SetDebugHandler);

/* func_00247908 — hand-written PS2 EE syscall stub: syscall number in $v1,
 * then `syscall 0`. .set noreorder keeps the bare nop in the jr delay slot. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247908\n"
    "    addiu      $3, $0, 0x74\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247908\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", InitTLBFunctions);

/* PutTLBEntry — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel PutTLBEntry\n"
    "    addiu      $3, $0, 0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel PutTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247978 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247978\n"
    "    addiu      $3, $0, -0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247978\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247988 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247988\n"
    "    addiu      $3, $0, 0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247988\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* iSetTLBEntry — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel iSetTLBEntry\n"
    "    addiu      $3, $0, -0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel iSetTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479A8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479A8\n"
    "    addiu      $3, $0, 0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479A8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* iGetTLBEntry — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel iGetTLBEntry\n"
    "    addiu      $3, $0, -0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel iGetTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* ProbeTLBEntry — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel ProbeTLBEntry\n"
    "    addiu      $3, $0, 0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel ProbeTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479D8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479D8\n"
    "    addiu      $3, $0, -0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479D8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479E8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479E8\n"
    "    addiu      $3, $0, 0x59\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479E8\n"
    /* 8 bytes of trailing nop padding before the next (16-aligned) func */
    "    nop\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247A00);

void _change_addr(int *a0, int *a1) {
    a1[2] = a0[4];
}

extern int D_00710F00[];

int func_00247D90(int a0) {
    return D_00710F00[a0];
}

int sceSifSetSreg(int a0, int a1) {
    D_00710F00[a0] = a1;
    return a1;
}

extern int D_00710DD8[];

void *func_00247DC8(void) {
    return D_00710DD8;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247DD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifExitCmd);

extern int D_00710DD8[];

int sceSifSetCmdBuffer(int a0, int a1) {
    int old = D_00710DD8[5];
    D_00710DD8[5] = a0;
    D_00710DD8[6] = a1;
    return old;
}

int sceSifSetSysCmdBuffer(int a0, int a1) {
    int old = D_00710DD8[3];
    D_00710DD8[3] = a0;
    D_00710DD8[4] = a1;
    return old;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifAddCmdHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifRemoveCmdHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceSifSendCmd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifSendCmd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", isceSifSendCmd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceSifCmdIntrHdlr);

/* Hand-written EE assembly (NOT a C-match target) — a cache / INTC
 * critical-section module:
 *   func_002483F8  DCache hit-writeback-invalidate loop (cache 0x18 / sync).
 *   func_002484A4  + func_002484AC are ONE routine splat over-split: the ISR.
 *                  Its real entry is func_002484A4 + 0x4 (the addiu $sp,-0x10),
 *                  which sceCdDelayThread installs via %hi/%lo(func_002484A4 + 0x4);
 *                  the body ends with `ei` (enable interrupts, COP0).
 *   sceCdDelayThread  installs that ISR and toggles INTC enable.
 * `ei`, `cache`, and the address-of-instruction callback cannot be emitted by
 * ee-gcc. func_002484A4 is short enough to author inline below; the rest stay
 * as assembled .s (byte-identical via INCLUDE_ASM). */
INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002483F8);

/* func_002484A4 — hand-written: bare-return entry whose delay slot doubles as
 * the prologue (addiu $sp,-0x10) of the ISR installed at func_002484A4+0x4.
 * .set noreorder keeps the addiu in the jr delay slot as written. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002484A4\n"
    "    jr         $31\n"
    "    addiu      $29, $29, -0x10\n"
    "endlabel func_002484A4\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002484AC: handwritten ISR thunk (ei/sync, asymmetric hand-frame).
 * C-inexpressible: an honest 33-hypothesis stall floored at rc3 (the entry
 * frame adjust, sync, and ei cannot be emitted by ee-gcc 2.9). Written as
 * in-file handwritten asm per maintainer exception (one-off). */
__asm__(
    ".section .text
"
    "    .set at
"
    "    .set noreorder
"
    "    .global func_002484AC
"
    "    .type func_002484AC, @function
"
    "func_002484AC:
"
    "    sd    $31, 0x0($29)
"
    "    jal   iSignalSema
"
    "    daddu $4, $6, $0
"
    "    sync
"
    "    ei
"
    "    ld    $31, 0x0($29)
"
    "    jr    $31
"
    "    addiu $29, $29, 0x10
"
    "    .size func_002484AC, . - func_002484AC
"
    "    .set reorder
"
    "    .set at
"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdDelayThread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceCd_cd_callback);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248630);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceCd_cd_read_intr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", cmd_sem_init);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", cdvd_exit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdPOffCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceCd_Poff_Intr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", PowerOffCB);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdSearchFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248EB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249028);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdSync);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdSyncS);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002491D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdDiskReady);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdMmode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249AC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249C18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249CB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStStart);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStSeekF);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStSeek);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStStop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStPause);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStResume);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStStat);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStream);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _send_to_iop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInit2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadPortOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadPortClose);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetDmaStr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetFrameCount);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetState);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AA00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetReqState);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetReqState);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AAF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInfoAct);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInfoComb);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInfoMode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetMainMode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetActDirect);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetActAlign);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetButtonMask);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetButtonInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInfoPressMode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadEnterPressMode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadExitPressMode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetVrefParam);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetPortMax);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetSlotMax);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetModVersion);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetWarningLevel);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMcInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _lmcGetClientPtr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B7B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B870);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B930);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMcMkdir);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BAA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BB58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", mceIntrReadFixAlign);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BCC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BDE0);

extern void iWakeupThread(int a0);

void mcHearAlarm(int a0, int a1, int a2) {
    iWakeupThread(a2);
    SYNC();
    EI();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", mcDelayThread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMcSync);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", mceGetInfoApdx);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMcGetInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C290);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", mceStorePwd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C470);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C5C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C7B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CA40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CBA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CC70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _type2id);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _id2type);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegDemuxPssRing);

extern void sceMpegDemuxPssRing(void *a0, int a1, int a2, int a3, int a4);
void sceMpegDemuxPss(void *a0, int a1, int a2) {
    do {
        sceMpegDemuxPssRing(a0, a1, a2, 0, -1);
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegAddStrCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pack_header);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _system_header);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _PES_packet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegCreate);

int func_0024DE40(void) {
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegAddBs);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegGetPicture);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegGetPictureRAW8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegGetPictureRAW8xy);

void sceMpegSetDecodeMode(void *a0, int a1, int a2, int a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x25] = a1;
    p[0x26] = a2;
    p[0x27] = a3;
}

void sceMpegGetDecodeMode(void *a0, int *a1, int *a2, int *a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    *a1 = *(int *)((char *)p + 0x94);
    *a2 = *(int *)((char *)p + 0x98);
    *a3 = *(int *)((char *)p + 0x9C);
}

int sceMpegIsEnd(int **a0) {
    return a0[0x10][0];
}

int sceMpegIsRefBuffEmpty(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    return *(int *)((char *)p + 0x4) == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegReset);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegClearRefBuff);

int sceMpegAddCallback(void *a0, int a1, int a2, int a3) {
    char *p = *(char **)((char *)a0 + 0x40);
    char *q0 = p + 0xC;
    int *q = (int *)(q0 + a1 * 8);
    int old;
    p += a1 * 8;
    ((int *)p)[4] = a3;
    old = *q;
    *q = a2;
    return old;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dispatchMpegCallback);

extern void _dispatchMpegCallback(void *a0, void *a1);

void _dispatchMpegCbNodata(void *a0) {
    int buf[8];
    buf[0] = 1;
    _dispatchMpegCallback(a0, buf);
}

void sceMpegSetDefaultPtsGap(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x1C] = 1;
    *(long long *)((char *)p + 0x78) = a1;
}

void sceMpegResetDefaultPtsGap(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    *(int *)((char *)p + 0x70) = 0;
    *(long long *)((char *)p + 0x78) = 0;
}

extern void *D_0054C764[];

void sceMpegSetImageBuff(int a0) {
    int *q = *(int **)((char *)D_0054C764[0] + 0x40);
    q[0x36] = a0;
}

int sceMpegDispWidth(int **a0) {
    return a0[0x10][0x33];
}

int sceMpegDispHeight(int **a0) {
    return a0[0x10][0x34];
}

void *func_0024E160(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

void *func_0024E170(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

int sceSetBrokenLink(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x40);
    int old = *(int *)((char *)p + 0xE8);
    *(int *)((char *)p + 0xE8) = a1;
    return old;
}

void sceSetPtm(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    *(long long *)((char *)p + 0xF0) = a1;
    p[0x3E] = 1;
}

void _alalcInit(int *a0, int a1, int a2) {
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a1;
    a0[3] = a1;
}

void _alalcSetDynamic(int *a0) {
    a0[3] = a0[2];
}

void _alalcFree(int *a0) {
    a0[2] = a0[3];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _alalcAlloc);

int _alalcRest(int *a0) {
    return a0[0] + a0[1] - a0[2];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _getpic);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decodeOrSkipFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decodeOrSkip);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decodeOrSkipField);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceMpegFlush);

extern int D_0054D030_alias[] __asm__("D_0054D030");
extern void _ipuSetMPEG1(int a0);

void _initSeqAgain(void) {
    D_0054D030_alias[0] = 0;
    _ipuSetMPEG1(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _lastFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _clearOnce);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _clearEach);

extern int D_00628EC8_alias[] __asm__("D_00628EC8");
extern void printf(void *a0, int a1);

void func_0024E8E0(int a0) {
    printf(D_00628EC8_alias, a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _Error1);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _Error);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sendDataToIPU);

int _RefImageInit(int *a0, int a1, int a2) {
    a0[0x4 / 4] = a1;
    a0[0x8 / 4] = a2;
    a0[0xC / 4] = a1 >> 4;
    a0[0x10 / 4] = a2 >> 4;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sequenceHeader);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EBC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _initRefImages);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _setDefaultQM);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sequenceExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sequenceDisplayExtension);

extern void _Error(void *a0);
extern int D_00628F38[];

void func_0024F2C0(void) {
    _Error(D_00628F38);
}

extern int D_00628F68[];
extern int D_00628F80[];
extern int D_00628FB8[];

void func_0024F2D0(void) {
    _Error(D_00628F68);
}

void func_0024F2E0(void) {
    _Error(D_00628F80);
}

void func_0024F2F0(void) {
    _Error(D_00628FB8);
}

extern void sceIpuStopDMA(void *a0);
extern void sceIpuRestartDMA(void *a0);

void func_0024F300(int **a0) {
    sceIpuStopDMA((char *)a0[0x10] + 0x4C);
}

void func_0024F310(int **a0) {
    sceIpuRestartDMA((char *)a0[0x10] + 0x4C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F320);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F658);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _getRef0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _doMC);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _rix_000);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ri0_000);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _rix_001);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ri0_001);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _rix_010);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ri0_010);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _rix_011);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ri0_011);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _rix_100);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ri0_100);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _rix_101);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ri0_101);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _rix_110);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ri0_110);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _rix_111);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ri0_111);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _copyAddRefImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251028);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ipuSetMPEG1);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _waitBdecOut);

extern int _ipuVdec(int a0);

int _dmVector(void) {
    return _ipuVdec(3);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dualPrimeVector);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _mbAddressIncrement);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pictureData0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sliceA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002517A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _skipMB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decMB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decode_motion_vector);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _motionVectors);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _motionVector);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sendIpuCommand);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _waitIpuIdle);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _waitIpuIdle64);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ipuVdec);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _peepBit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _flushBuf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _nextBit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _nextStartCode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sliceB);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _nextHeader);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pictureHeader);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _extensionAndUserData);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pictureCodingExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _extrainfo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252FC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _groupOfPicturesHeader);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _quantMatrixExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pictureDisplayExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _copyrightExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decPicture);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _outputFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _updateRefImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _isOutSizeOK);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _cpr8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _markOutput);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _getPtsDtsFlags);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dispRefImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dispRefImageField);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _doCSC);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _doCSC2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ch4dma);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _csc_storeRefImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sysbitInit);

int _sysbitNext(void *a0, int a1) {
    unsigned long long v = *(unsigned long long *)a0;
    return v >> (64 - a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sysbitFlush);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sysbitGet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sysbitMarker);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sysbitJump);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sysbitPtr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002549B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254A20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIpuStopDMA);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIpuRestartDMA);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIpuSync);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254D28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIpuInit);

extern unsigned char D_00713C80[];

void *_SgGetSlotContext(int a0) {
    return &D_00713C80[a0 * 0x58];
}

extern unsigned char D_00714D00[];

void *_SgGetSeqContext(int a0) {
    return &D_00714D00[a0 * 0x54];
}

extern int D_00715CC0[];

void *func_00254FF8(void) {
    return D_00715CC0;
}

extern unsigned char D_00713680[];

void *_SgGetVabContext(int a0) {
    return &D_00713680[a0 * 0xC];
}

extern int D_00717F80[];

void _SgSetSeVolValue(int a0, int a1) {
    D_00717F80[a0] = a1;
}

int func_00255038(int a0) {
    return D_00717F80[a0];
}

extern int D_00717F80[];
extern int D_00718180[];
extern int D_00717F40[];

void *func_00255050(void) {
    return D_00717F80;
}

void *func_00255060(void) {
    return D_00718180;
}

int func_00255070(void) {
    return D_00717F40[0];
}

extern unsigned char D_00715D40[];

void *_SgGetPacketCntext(int a0, int a1) {
    unsigned char *p = &D_00715D40[a1 * 0x10];
    return (void *)(a0 * 0x1000 + (int)p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgCalledTickProc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSetPkAdd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeMain);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgBgmMain);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSetRealtimeTickProc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSetRealtimeVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgTableEnvAdd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeqKeyOnSlot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeKeyOnSlot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeKeyOff);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeqKeyOff);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgIntoKeyOn);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgPitchTableVag);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeqSeVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgPan);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgEndSeq);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgTempoChange);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgProgChange);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContMod);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContModLoop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContPolta);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContVol);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContPan);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContDump);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContSeLoop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContParam);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContLoopCount);

void _SgContLoop(void) {
    /* TODO: scaffold unavailable — recover from asm */
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgBendForm);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgDeltaTime);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeqSeRrEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgfadeParam);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSndn2Remote);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSndn2RemoteInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSndn2RemoteSync);

extern void _SgInit(int a0);

void func_00258948(void) {
    _SgInit(0);
}

void func_00258950(void) {
    _SgInit(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgQuit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgCalledTickProc);

extern void _SgSetPkAdd(int a0, int a1, int a2, int a3);

void SgSetDigitalOutputMode(int a0) {
    _SgSetPkAdd(0x32, 0xA, a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgDmaWrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgDmaRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgDmaCommon);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetDmaTransferStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgVabOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgVabOpenFakeBody);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgVabClose);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgBgmOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgBgmClose);

void SgSetReverbEndAddr(int a0, int a1) {
    _SgSetPkAdd(0x14, a0, a1, 0);
}

void SgSetReverbType(int a0, int a1) {
    _SgSetPkAdd(0x15, a0, a1, 0);
}

void SgSetReverbDepth(int a0, int a1, int a2) {
    _SgSetPkAdd(0x16, a0, a1, a2);
}

void SgSetReverbDelaytime(int a0, int a1) {
    _SgSetPkAdd(0x17, a0, a1, 0);
}

void SgSetReverbFeedback(int a0, int a1) {
    _SgSetPkAdd(0x18, a0, a1, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetOutputMode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetTickMode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetSlotStatus);

void SgSetMasterVol(int a0, int a1, int a2) {
    _SgSetPkAdd(0x28, a0, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetBgmVol);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetSeMasterVol);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgBgmPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgBgmStop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetBgmTempo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetBgmTempo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetBgmStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetBgmChStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetBgmPanpot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSePlay);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSeStop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSeStopAll);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetSeVolDirect);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetSePitchDirect);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetSpuSlotMalloc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetSpuSlotFree);

void SgStAdpcmInit(void) {
    _SgSetPkAdd(0x3C, 0, 0, 0);
}

void SgStAdpcmQuit(void) {
    _SgSetPkAdd(0x3D, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStAdpcmOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStAdpcmClose);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStAdpcmChannelVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStAdpcmChannelPitch);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStAdpcmPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStAdpcmStop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStAdpcmIopReadAddr);

void SgStPcmInit(void) {
    _SgSetPkAdd(0x46, 0, 0, 0);
}

void SgStPcmQuit(void) {
    _SgSetPkAdd(0x47, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStPcmOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStPcmClose);

void SgStPcmSetEffect(int a0) {
    _SgSetPkAdd(0x4E, a0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStPcmPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStPcmStop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStPcmLseek);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStPcmVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStPcmIopReadAddr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStPcmBufMode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sinf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A768);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", atan2f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fmodf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_acosf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_asinf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_atan2f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_fmodf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_rem_pio2f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_sqrtf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __kernel_cosf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __kernel_rem_pio2f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __kernel_sinf);

extern void dpcmp(long a0, long a1);

int matherr(void *a0) {
    long p = *(long *)((char *)a0 + 8);
    dpcmp(p, p);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", atanf);

/* fabsf(x) via the standard IEEE-754 bit twiddle: clear the sign bit. */
float fabsf(float a0) {
    unsigned int ix;
    GET_FLOAT_WORD(ix, a0);
    SET_FLOAT_WORD(a0, ix & 0x7fffffff);
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", floorf);

/* isnanf(x) via the standard IEEE-754 bit test: NaN iff |x| bits > 0x7F800000 (+inf). */
int isnanf(float x) {
    int hx;
    GET_FLOAT_WORD(hx, x);
    hx &= 0x7fffffff;
    hx = 0x7f800000 - hx;
    return (unsigned)hx >> 31;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scalbnf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", copysignf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CF30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __do_global_ctors);

/* D_007181E8 is a .bss global splat left as a raw lui/lw (no name); declared in
 * symbol_addrs + defined for the linker in undefined_funcs_extra.aug6.txt so the
 * %hi/%lo base reuses one reg like the ROM. Byte-identical in the link
 * (ninja verify_elf OK); match_diff shows a residual only because the reference
 * .s keeps the raw value rather than %hi(D_007181E8). */
extern int D_007181E8[];
extern void __do_global_ctors(void);
void __main(void) {
    if (D_007181E8[0] == 0) {
        D_007181E8[0] = 1;
        __do_global_ctors();
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __divdi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __fixunsdfdi);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __floatdidf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __moddi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __muldi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __udivdi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __umoddi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __pack_d);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __unpack_d);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _fpadd_parts);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dpadd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dpsub);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dpmul);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dpdiv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __fpcmp_parts_d);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dpcmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", litodp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dptoli);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dptoul);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __negdf2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __make_dp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dptofp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __pack_f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __unpack_f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F940);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fpadd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fpsub);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fpmul);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fpdiv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __fpcmp_parts_f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fpcmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sitofp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fptosi);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fptoui);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __negsf2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __make_fp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fptodp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __assert);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", atoi);

extern int D_0054D504[];

int func_002603E0(void) {
    return D_0054D504[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fiprintf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memcmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memcpy);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memset);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _printf_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", printf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", qsort);

extern void *D_0054D504_alias[] __asm__("D_0054D504");

void srand(int a0) {
    char *p = (char *)D_0054D504_alias[0];
    *(int *)(p + 0x58) = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", rand);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sprintf_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sprintf);

int func_002611F8(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sscanf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strcat);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strcmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strcpy);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strlen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strncmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strncpy);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strrchr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strstr);

extern int D_0054D504[];
extern int func_00261BA8(int a0, int a1, int a2);

int strtok(int a0, int a1) {
    return func_00261BA8(a0, a1, D_0054D504[0] + 0x5C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261E80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261EB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261F00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261FB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262030);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262C00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", cvt);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", exponent);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __svfscanf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sccl);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", vsprintf);

typedef struct { char pad38[0x38]; int p54_f38; } PObjLink54;
typedef struct {
    int field_0;
    int field_4;
    int field_8;
    unsigned short field_C;
    unsigned short field_E;
    int field_10;
    int field_14;
    int field_18;
    int pad_1C[5];
    void *field_30;
    int pad_34[3];
    int field_40[5];
    PObjLink54 *field_54;
} PObjUpd;
extern int D_0054D504[];
extern void __sinit(char *a0);
extern void _free_r(PObjLink54 *p);
extern void __smakebuf(PObjUpd *s);

int __swsetup(PObjUpd *s0) {
    int flags;
    if (s0->field_54 == 0) {
        s0->field_54 = (PObjLink54 *)D_0054D504[0];
    }
    if (s0->field_54->p54_f38 == 0) {
        __sinit((char *)s0->field_54);
    }
    flags = s0->field_C;
    if (!(flags & 8)) {
        if (!(flags & 0x10)) {
            return -1;
        }
        if (flags & 4) {
            PObjLink54 *fp = s0->field_54;
            void *q = s0->field_30;
            if (q != 0) {
                if (q != (void *)s0->field_40) {
                    _free_r(fp);
                    flags = s0->field_C;
                }
                s0->field_30 = 0;
            }
            s0->field_4 = 0;
            {
                int t = flags & ~0x24;
                s0->field_C = t;
                flags = t;
            }
            s0->field_0 = s0->field_10;
        }
        s0->field_C = flags | 8;
    }
    if (s0->field_10 != 0) {
        flags = s0->field_C;
    } else {
        __smakebuf(s0);
        flags = s0->field_C;
    }
    if (flags & 1) {
        s0->field_8 = 0;
        s0->field_18 = -s0->field_14;
    } else {
        s0->field_8 = (flags & 2) ? 0 : s0->field_14;
    }
    return 0;
}


extern void func_002697C0(int a0);
extern void InitDelayFree(int a0);
void func_00265298(void) {
    for (;;) {
        func_002697C0(6);
        InitDelayFree(1);
    }
}

extern int func_0026A958();

int func_002652B8(void *a0) {
    return func_0026A958(a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", quorem);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dtoa_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fflush);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", std);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sfmoreglue);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sfp);

extern int fflush(void);
extern void _fwalk(int a0, void *a1);

void func_00266970(int a0) {
    _fwalk(a0, fflush);
}

void func_00266980(void) {
    func_00266970(D_0054D504[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sinit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _free_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _malloc_trim_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sfvwrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _fwalk);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _setlocale_r);

extern int D_0062A818[];

void *func_002674C8(int a0) {
    return D_0062A818;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002674D8);

void *func_00267508(void) {
    return func_002674C8(D_0054D504[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __smakebuf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", malloc_extend_top);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _malloc_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _mbtowc_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memchr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memmove);

void func_00268270(void) {
}

void func_00268278(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _Balloc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _Bfree);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _multadd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _s2b);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _hi0bits);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _lo0bits);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _i2b);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _multiply);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pow5mult);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _lshift);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __mcmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __mdiff);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ulp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _b2d);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _d2b);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ratio);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _mprec_log10);

int func_002692A0(void) {
    return fflush();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __srefill);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", isinf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", isnan);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sbrk_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _init_signal_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _signal_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _raise_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sigtramp_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002697C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002697E8);

extern void *_init_signal_r(int a0);

void *func_00269818(void) {
    return _init_signal_r(D_0054D504[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269840);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269868);

int func_002698C8(void) {
    return func_00241B98();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __swrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sseek);

extern int _close_r(int a0, int a1);
int __sclose(void *a0) {
    return _close_r(*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE));
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _strtod_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026A958);

extern int dptofp(int a0);

int strtodf(void) {
    return dptofp(func_0026A958());
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _strtoul_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026ABD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __submore);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", ungetc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _calloc_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _close_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AFF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B058);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B0B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _realloc_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceSDC);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B730);

extern void _sceSDC(int a0, int a1);

void func_0026B7B0(int a0, int a1) {
    _sceSDC(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceIDC);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B870);

extern void _sceIDC(int a0, int a1);

void func_0026B8F0(int a0, int a1) {
    _sceIDC(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __fixdfdi);


/* recovered struct shapes */
typedef struct {
    /* width 16 */ unsigned char f_10;  /* 0x10 */
    /* width 16 */ unsigned char f_20;  /* 0x20 */
    /* width 16 */ unsigned char f_30;  /* 0x30 */
    /* width 16 */ unsigned char f_40;  /* 0x40 */
    /* width 16 */ unsigned char f_50;  /* 0x50 */
    /* width 16 */ unsigned char f_60;  /* 0x60 */
    /* width 16 */ unsigned char f_70;  /* 0x70 */
    /* width 16 */ unsigned char f_80;  /* 0x80 */
    /* width 16 */ unsigned char f_90;  /* 0x90 */
    /* width 16 */ unsigned char f_A0;  /* 0xA0 */
    /* width 16 */ unsigned char f_B0;  /* 0xB0 */
    /* width 16 */ unsigned char f_C0;  /* 0xC0 */
    /* width 16 */ unsigned char f_D0;  /* 0xD0 */
    /* width 16 */ unsigned char f_E0;  /* 0xE0 */
    /* width 16 */ unsigned char f_F0;  /* 0xF0 */
    /* width 16 */ unsigned char f_100;  /* 0x100 */
    /* width 16 */ unsigned char f_110;  /* 0x110 */
    /* width 16 */ unsigned char f_120;  /* 0x120 */
    /* width 16 */ unsigned char f_130;  /* 0x130 */
    /* width 16 */ unsigned char f_140;  /* 0x140 */
    /* width 16 */ unsigned char f_150;  /* 0x150 */
    /* width 16 */ unsigned char f_160;  /* 0x160 */
    /* width 16 */ unsigned char f_170;  /* 0x170 */
    /* width 16 */ unsigned char f_180;  /* 0x180 */
    /* width 16 */ unsigned char f_190;  /* 0x190 */
    /* width 16 */ unsigned char f_1C0;  /* 0x1C0 */
    /* width 16 */ unsigned char f_1D0;  /* 0x1D0 */
    /* width 16 */ unsigned char f_1E0;  /* 0x1E0 */
    /* width 16 */ unsigned char f_1F0;  /* 0x1F0 */
} S_00710AC0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_1C;  /* 0x1C */
} S_007115C0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
} S_00710DD8;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_007112D0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
    unsigned int       f_28;  /* 0x28 */
} S_0070E240;

typedef struct {
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0054D520;  /* stride 0x8 */

typedef struct {
    /* width 16 */ unsigned char f_0;  /* 0x00 */
    /* width 16 */ unsigned char f_10;  /* 0x10 */
    /* width 16 */ unsigned char f_20;  /* 0x20 */
    /* width 16 */ unsigned char f_30;  /* 0x30 */
    /* width 16 */ unsigned char f_40;  /* 0x40 */
} S_0054D160;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0054C918;

typedef struct {
    unsigned long long f_0;  /* 0x00 */
} S_0062A870;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070C340;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00710F00;  /* stride 0x4 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_00710FC8;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00717F80;  /* stride 0x4 */

typedef struct {
    unsigned int       f_108;  /* 0x108 */
} S_004CED88;  /* stride 0x10C */

typedef struct {
    unsigned long long f_8;  /* 0x08 */
} S_0054C698;  /* stride 0x10 */

typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_0054D1D0;  /* stride 0x2 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0070C680;

typedef struct {
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_0070C790;

typedef struct {
    /* width 16 */ unsigned char f_0;  /* 0x00 */
    /* width 16 */ unsigned char f_10;  /* 0x10 */
} S_0054A970;

typedef struct {
    /* width 16 */ unsigned char f_0;  /* 0x00 */
    /* width 16 */ unsigned char f_10;  /* 0x10 */
} S_0054A9B0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054AB48;  /* stride 0x4 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_0054C968;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_0054C978;

typedef struct {
    /* width 16 */ unsigned char f_0;  /* 0x00 */
    /* width 16 */ unsigned char f_10;  /* 0x10 */
} S_0054D1B0;

typedef struct {
    short              f_0;  /* 0x00 */
} S_0062A350;  /* stride 0x2 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_0062E160;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054A940;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054A9D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054C650;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054C670;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054D048;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054D068;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054D088;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054D0F8;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00629860;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00629930;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0062A860;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_007113C0;  /* stride 0x100 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00628430;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00628640;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006287C0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00628E90;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006292A0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00629430;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A1E0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A380;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A570;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A800;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A990;  /* stride 0x4 */

/* end struct shapes */
