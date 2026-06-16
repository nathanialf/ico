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

void pac_DumpPac(void *a0) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vrnext.x $vf1, $R\n"
        "vrnext.y $vf1, $R\n"
        "vrnext.z $vf1, $R\n"
        "vsubw.xyz $vf1, $vf1, $vf0w\n"
        "sqc2 $vf1, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void pac_makeBoundingBox(void *a0) {
    VU0_REG("vrnext.xyz $vf1, $R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, 4);
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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makeNormalStrip);

extern int D_0062AFF4;
extern int dpk_SwapBuffer(int a0);
extern void dpk_Init(int a0, int a1, int a2);
extern int dl_GetPri(void);

typedef struct {
    char _pad0[0x0C];
    volatile int *volatile start; /* 0x0C */
    volatile int *volatile cur;   /* 0x10 */
    volatile int *volatile tag;   /* 0x14 */
    volatile int f_18;            /* 0x18 */
    volatile int f_1C;            /* 0x1C */
} PakBuf;
extern PakBuf D_004C3850;

void pac_getWeight(int a0, int a1, int a2, int a3, int a4) {
    int w = 0xFFFF;

    switch (a0) {
    case 0:
        switch (a1) {
        case 0:
            switch (a3) {
            case -1: w = 0x22; break;
            case 2:  w = 0x24; break;
            default: w = 0x20; break;
            }
            break;
        case 3:
            w = 0x26;
            break;
        default:
            switch (a2) {
            case 0:  w = (a3 == 2) ? 0x24 : 0x20; break;
            case 1:  w = 0x22; break;
            case 2:  w = 0x26; break;
            }
            break;
        }
        break;
    case 1:
        if (a1 != 0) {
            if (a3 == -1) {
                if (a2 == 0) goto c1_aff4;
                if (a2 != a0) goto Lret;
                w = 0x16;
                break;
            } else {
                if (a2 == 0) goto c1_aff4;
                if (a2 == a0) goto c1_w16;
                goto Lret;
            }
        } else {
            w = 0x14;
        }
        break;
    c1_aff4:
        w = (D_0062AFF4 != 1) ? 0x14 : 0x18;
        break;
    c1_w16:
        w = 0x16;
        break;
    case 2:
        if (a1 == 0) {
            w = 0x14;
        } else {
            w = (D_0062AFF4 == 0) ? 0x16 : 0x18;
        }
        break;
    case 3:
        w = 0x12;
        break;
    }

    if (w == 0xFFFF) {
        goto Lret;
    }

    {
        volatile int *p = D_004C3850.cur;
        D_004C3850.f_18 = 0;
        D_004C3850.tag = p;
        D_004C3850.start = p;
        D_004C3850.f_1C = 0;
        *(volatile unsigned long long *)p = 0x10000000;
        D_004C3850.cur = p + 2;
        p[2] = 0x15000000 | w;
        D_004C3850.cur = p + 3;
        p[3] = 0x13000000;
        D_004C3850.cur = p + 4;
        D_004C3850.tag = p + 4;
        *(volatile unsigned long long *)(p + 4) = 0x60000000;
        D_004C3850.cur = p + 6;
        p[6] = 0;
        D_004C3850.cur = p + 7;
        p[7] = 0;
        D_004C3850.cur = p + 8;
        dpk_SwapBuffer(a4);
        dpk_Init(5, (int)D_004C3850.start, 0);
        dl_GetPri();
        return;
    }
Lret:
    return;
}

extern int D_00272580[];
extern int D_0066CB10[];
extern int D_0062BF3C;
extern void pac_makeNormalStrip(int a0, int a1);
extern int dpk_SwapBuffer(int a0);
extern void dpk_Init(int a0, int a1, int a2);
extern int dl_GetPri(void);

void pac_makeClusterStrip(int a0, int a1) {
    int *q = &D_00272580[a0];
    int i;
    for (i = 0; i < 0xD; i++) {
        if ((a1 >> i) & 1) {
            if (a0 != D_0066CB10[i]) {
                D_0062BF3C++;
                pac_makeNormalStrip(a0, i);
                dpk_SwapBuffer(i);
                dpk_Init(5, *q, 0);
                dl_GetPri();
                D_0066CB10[i] = a0;
            }
        }
    }
}

extern int D_0066CB10[];
extern int D_0062BF3C;

void pac_openDmaTag(void)
{
    int *p = D_0066CB10;
    int i = 0xC;
    D_0062BF3C = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

void pac_setVifCode(void)
{
    int *p = D_0066CB10;
    int i = 0xC;
    D_0062BF3C = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

extern void debug_assertMessage(const char *fmt, ...);
extern int func_00260340(float);
extern const char D_0054F180[];
extern const char D_0054F198[];
extern const char D_00631CD8_a[] __asm__("D_0062BE58");
extern const char D_00631CE0_a[] __asm__("D_0062BE60");
extern const char D_00631CE8_a[] __asm__("D_0062BE68");
extern const char D_00631CF0_a[] __asm__("D_0062BE70");

/* The switch jump table (jtbl_0054F1B0) is migrated into Packet.o via the
 * per-TU `.rodata` subseg carve in config/ico.aug6.yaml + splat's
 * migrate_rodata_to_functions; gcc emits its own jtbl here. */
void pac_setVifEndCode(unsigned char *arg, int slot_size) {
    int is_float = 0;
    int row;

    switch (slot_size) {
    case 0:
        is_float = 1;
        slot_size = 4;
        debug_assertMessage(D_0054F180, arg);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_assertMessage(D_0054F198, arg, slot_size);
        break;
    default:
        return;
    }

    for (row = 0; row < 0x10 / slot_size; row++) {
        if (!is_float) {
            int col;
            for (col = 0x10 / (0x10 / slot_size) - 1; col >= 0; col--) {
                debug_assertMessage(D_00631CD8_a, arg[row * slot_size + col]);
            }
            debug_assertMessage(D_00631CE0_a);
        } else {
            debug_assertMessage(D_00631CE8_a, func_00260340(((float *)arg)[row]));
        }
    }
    debug_assertMessage(D_00631CF0_a);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_setGifTag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_closeTag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_continueTag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_checkDivide);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_countOneVertexPacketSize);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Packet", pac_makeStrip);

extern char D_0066CB50[];
extern float D_00628D40;
extern float D_00628D44;

extern char D_0054F540[];

void pac_setMaterialPacket(int a0)
{
    register int mask = 0x0FFFFFFF;
    char *ctx = D_0066CB50;
    float f0 = D_00628D40;
    float f1 = D_00628D44;
    *(int *)(ctx + 0x20) = a0 & mask;
    *(int *)(ctx + 0x24) = (a0 + 0x8) & mask;
    *(int *)(ctx + 0x28) = (a0 + 0x10) & mask;
    *(int *)(ctx + 0x2C) = a0 + 0x20;
    *(float *)(ctx + 0x48) = f0;
    *(float *)(ctx + 0x44) = f0;
    *(float *)(ctx + 0x40) = f0;
    *(float *)(ctx + 0x58) = f1;
    *(float *)(ctx + 0x54) = f1;
    *(float *)(ctx + 0x50) = f1;
    debug_assertMessage(D_0054F540, a0 & mask);
}

extern char D_0054F550[];

void pac_makeMaterialTable(int a0)
{
    register char *base = D_0066CB50;
    (*(volatile int * volatile *)(base + 0x24))[0] = 0;
    (*(volatile int * volatile *)(base + 0x24))[1] = (a0 << 16) | 0x6C008000;
    {
        volatile int *p = *(volatile int * volatile *)(base + 0x24);
        debug_assertMessage(D_0054F550, p[0], p[1], (int *)p, a0);
    }
}

void pac_makeMaterialTableLine(void)
{
    register char *base = D_0066CB50;
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

void func_0011C328(int *a0, int size)
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


/* recovered struct shapes */
typedef struct {
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
    unsigned int       f_28;  /* 0x28 */
    unsigned int       f_2C;  /* 0x2C */
    unsigned int       f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_0066CB50;

typedef struct {
    unsigned long long f_0;  /* 0x00 */
} S_0054F570;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054F160;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054F1B0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054F390;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00629FD0;  /* stride 0x4 */

/* end struct shapes */
