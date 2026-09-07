#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setShape);
typedef union {
    unsigned int c[4];
    unsigned long long w[2];
} RegColor;
typedef struct {
    int e[12][2];
} RegBoxLines;
extern RegColor D_0054FAD0;
extern RegBoxLines D_0054FAE0;
extern char *matrixptr;
extern void _SetCurrentMatrix(void *mtx);
extern void gif_StartPacketPri(int pri);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_EndPacket(void);
extern void *MatrixDrive_GetMatrix(void);
extern void _CopyMatrix(void *dst, void *src);
extern void DrawLine(void *a, void *b, RegColor *col, int flag);

void reg_dispBoxLine(char *pk)
{
    RegColor col;
    RegBoxLines line;
    int i;

    if (pk == 0) {
        return;
    }
    _SetCurrentMatrix(matrixptr + 0x40);
    gif_StartPacketPri(11);
    col = D_0054FAD0;
    line = D_0054FAE0;
    gif_SetAlpha(1, 4, 0x20);
    _CopyMatrix(MatrixDrive_GetMatrix(), matrixptr + 0x40);
    for (i = 0; i < 12; i++) {
        DrawLine(pk + line.e[i][0] * 16, pk + line.e[i][1] * 16, &col, 0);
    }
    gif_EndPacket();
}
extern char *matrixptr;
extern int D_0063B184;
extern char D_0054FB40[];
extern char D_0054FA80[];
extern char D_0063A170[];
extern void _SetCurrentMatrix(void *mtx);
extern int gsb_ClipBox(void *pk);
extern void debug_StdPrintfDummy();
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void reg_dispBoxLine(char *pk);

int reg_clipPacketBoundingBox(char *pk)
{
    int ret = 1;
    int type;

    _SetCurrentMatrix(matrixptr + 0x300);

    type = *(unsigned char *)(pk + 0x93);
    switch (type) {
    case 0:
        ret = -1;
        break;
    case 1:
        ret = gsb_ClipBox(pk);
        if (ret == 2) {
            ret = 1;
        }
        break;
    case 2:
        ret = gsb_ClipBox(pk);
        break;
    case 3:
        ret = gsb_ClipBox(pk);
        if (ret == 1) {
            ret = 2;
        }
        break;
    default:
        debug_StdPrintfDummy(D_0054FB40, type);
        debug_assert(D_0054FA80, 821); __assert(D_0054FA80, 821, D_0063A170);
        break;
    }
    if (D_0063B184 & 2) {
        reg_dispBoxLine(pk);
    }
    return ret;
}
extern void mc_TransMicroCode(int a0);
void reg_transMicroCode(char *a0, int mask) {
    if (*(signed char *)(*(char **)(a0 + 0x854) + 0x2F) != 0) {
        mc_TransMicroCode(3);
        return;
    }
    if (*(int *)(*(char **)(a0 + 0x874) + 0xF0) == 0) {
        mc_TransMicroCode(1);
        return;
    }
    mc_TransMicroCode(2);
}
extern void mc_SetMicroCode();

void reg_chooseMicroCode(char *self, int b, int c)
{
    long long v_ll = *(long long *)(self + 0x60);
    int v_int = *(int *)(self + 0x60);
    mc_SetMicroCode(v_int & 1, ((int)(v_ll >> 5)) & 3, 0, b, c);
}
void reg_chooseSpecularMicroCode(int a0, int a1, int a2)
{
    mc_SetMicroCode(a0, 1, 1, a1, a2);
}
void reg_chooseReflectionMicroCode(int a0, int a1, int a2)
{
    mc_SetMicroCode(a0, 1, 2, a1, a2);
}
extern char D_0054FB80[];
extern int D_0063B124;
extern void dl_CloseDma();
extern void dl_OpenDma();
extern void dl_SetDLPriority(int a0);
extern int tex_TransTexture(int a0, int a1);
/* One 64-bit slot of a DMA/GIF packet: written either as the whole qword
   (DMAtag, GIFtag, A+D data) or as its two 32-bit halves. */
typedef union {
    long long d;
    int w[2];
} RegPkWord;
typedef struct {
    int cur;
    int *buf[2];
    char *dma;
    char *ptr;
    char *tail;
    char *gif;
    char *end;
} RegDpk;
extern RegDpk D_004EE6F0;
extern void _InitCurrentMatrix(void);
extern void _GetCurrentMatrix(void *dst);
extern void _ScaleCurrentMatrix(float x, float y, float z);
extern void _ClearTransCurrentMatrix(void);
extern void _MulCurrentMatrixL(void *m);
extern void _MulMatrix(void *dst, void *a, void *b);
extern void light_MakeLightMatrix(char *o, int idx);

char *reg_setNMatrixPacket(char *o, int idx)
{
    void setMatrix(void)
    {
        char *c;
        char *m;

        c = D_004EE6F0.ptr;
        D_004EE6F0.tail = c;
        ((RegPkWord *)c)->d = 0x1000000D;
        D_004EE6F0.ptr = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        D_004EE6F0.ptr = c + 0xC;
        D_004EE6F0.gif = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0x6C0C8000;
        D_004EE6F0.ptr = c + 0x50;
        _CopyMatrix(c + 0x10, matrixptr + 0x140);
        _MulMatrix(D_004EE6F0.ptr, matrixptr + 0x200, matrixptr + 0x40);
        D_004EE6F0.ptr = D_004EE6F0.ptr + 0x40;
        _MulMatrix(D_004EE6F0.ptr, matrixptr + 0x80, matrixptr + 0x40);
        m = D_004EE6F0.ptr;
        D_004EE6F0.ptr = m + 0x40;
        ((RegPkWord *)(m + 0x40))->w[0] = 0x15000010;
        D_004EE6F0.ptr = m + 0x44;
        ((RegPkWord *)(m + 0x40))->w[1] = 0;
        D_004EE6F0.ptr = m + 0x48;
        ((RegPkWord *)(m + 0x48))->d = 0;
        D_004EE6F0.ptr = m + 0x50;
    }
    void setLight(void)
    {
        char *c;
        char *m;
        char *n;

        c = D_004EE6F0.ptr;
        D_004EE6F0.tail = c;
        ((RegPkWord *)c)->d = 0x10000009;
        D_004EE6F0.ptr = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        D_004EE6F0.ptr = c + 0xC;
        D_004EE6F0.gif = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0x6C088000;
        D_004EE6F0.ptr = c + 0x10;
        _GetCurrentMatrix(c + 0x10);
        m = D_004EE6F0.ptr;
        D_004EE6F0.ptr = m + 0x80;
        _CopyMatrix(m + 0x40, *(char **)(o + 0x874) + 0x40);
        n = D_004EE6F0.ptr;
        ((RegPkWord *)n)->w[0] = 0x15000012;
        n += 4;
        D_004EE6F0.ptr = n;
        ((RegPkWord *)n)->w[0] = 0;
        D_004EE6F0.ptr = n + 4;
        ((RegPkWord *)(n + 4))->d = 0;
        D_004EE6F0.ptr = n + 0xC;
    }
    char *pkt;
    char *box;
    float *scl;
    int mode;

    scl = (float *)(idx * 0x50 + *(int *)(o + 0x870));
    mode = *(int *)(*(int *)(o + 0x874) + 0xF0);
    if (scl[8] != 1.0f || scl[9] != 1.0f || scl[10] != 1.0f) {
        _InitCurrentMatrix();
        _SetCurrentMatrix(*(char **)(o + 0xC) + idx * 0x40);
        _ScaleCurrentMatrix(*(float *)(idx * 0x50 + *(int *)(o + 0x870) + 0x20),
                            *(float *)(idx * 0x50 + *(int *)(o + 0x870) + 0x24),
                            *(float *)(idx * 0x50 + *(int *)(o + 0x870) + 0x28));
        _GetCurrentMatrix(matrixptr + 0x40);
    } else {
        _CopyMatrix(matrixptr + 0x40, *(char **)(o + 0xC) + idx * 0x40);
    }
    _MulMatrix(matrixptr + 0x300, matrixptr + 0x280, matrixptr + 0x40);
    _MulMatrix(matrixptr + 0x140, matrixptr + 0x100, matrixptr + 0x40);
    box = *(char **)(o + 0x854) + 0x50;
    _SetCurrentMatrix(matrixptr + 0x300);
    if (gsb_ClipBox(box) == 0) {
        if (*(int *)(o + 0x858) != 0) {
            light_MakeLightMatrix(o, idx);
        }
        return 0;
    }
    pkt = D_004EE6F0.ptr;
    D_004EE6F0.dma = pkt;
    D_004EE6F0.tail = 0;
    D_004EE6F0.gif = 0;
    D_004EE6F0.end = 0;
    setMatrix();
    if (mode != 0 && mode != 3) {
        light_MakeLightMatrix(o, idx);
        _SetCurrentMatrix(matrixptr + 0x40);
        _ClearTransCurrentMatrix();
        _MulCurrentMatrixL(*(char **)(o + 0x874));
        setLight();
    }
    {
        char *c = D_004EE6F0.ptr;

        D_004EE6F0.tail = c;
        ((RegPkWord *)c)->d = 0x60000000;
        D_004EE6F0.ptr = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        D_004EE6F0.ptr = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0;
        D_004EE6F0.ptr = c + 0x10;
    }
    return pkt;
}
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setMatrix_116);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setLight_120);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setMMatrixPacket);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setCMatrixPacket);

void func_00121428(char *a0, int a1, int a2) {
    short h;
    dl_SetDLPriority(4);
    h = *(short *)(a0 + 0x86);
    if (h >= 0) {
        D_0063B124 += tex_TransTexture(h, 4);
    }
    dl_OpenDma(2, D_0054FB80, 5);
    dl_CloseDma();
    reg_chooseSpecularMicroCode(a2, a1, 4);
    dl_OpenDma(2, *(void **)(a0 + 0x98), (*(int *)(a0 + 0x90) & 0xFFFFFF) >> 4);
    dl_CloseDma();
}
void reg_transMaterialPacket(short *self, int *p)
{
    short idx = self[0x80/2];
    if (idx != -1) {
        int v = *p + idx * 0x70;
        dl_OpenDma(2, v, 6);
        dl_CloseDma();
    }
}

int reg_setDissolve(int pri, float a)
{
    char *p;
    char *q;
    int v;

    v = (int)((a < 0.0f ? a + 1.0f : 1.0f - a) * 96.0f);
    if (v >= 128) {
        v = 127;
    }
    if (v < 0) {
        v = 0;
    }
    p = D_004EE6F0.ptr;
    D_004EE6F0.gif = 0;
    D_004EE6F0.dma = p;
    D_004EE6F0.end = 0;
    D_004EE6F0.tail = p;
    ((RegPkWord *)p)->d = 0x10000005;
    D_004EE6F0.ptr = p + 8;
    ((RegPkWord *)(p + 8))->w[0] = 0;
    D_004EE6F0.ptr = p + 0xC;
    D_004EE6F0.gif = p + 0xC;
    ((RegPkWord *)(p + 8))->w[1] = 0x6C048000;
    D_004EE6F0.ptr = p + 0x10;
    ((RegPkWord *)(p + 0x10))->d = 0x1000000000008003LL;
    D_004EE6F0.ptr = p + 0x18;
    ((RegPkWord *)(p + 0x18))->d = 14;
    D_004EE6F0.ptr = p + 0x20;
    ((RegPkWord *)(p + 0x20))->d = 0;
    D_004EE6F0.ptr = p + 0x28;
    ((RegPkWord *)(p + 0x28))->d = 0x49;
    D_004EE6F0.ptr = p + 0x30;
    if (0.0f < a) {
        ((RegPkWord *)(p + 0x30))->d = ((long long)v << 32) | 0x68;
        D_004EE6F0.ptr = p + 0x38;
    } else {
        ((RegPkWord *)(p + 0x30))->d = ((long long)v << 32) | 0x62;
        D_004EE6F0.ptr = p + 0x38;
    }
    q = D_004EE6F0.ptr;
    ((RegPkWord *)q)->d = 0x42;
    q += 8;
    D_004EE6F0.ptr = q;
    ((RegPkWord *)q)->d = 0x1300000C0LL;
    D_004EE6F0.ptr = q + 8;
    ((RegPkWord *)(q + 8))->d = 0x4E;
    D_004EE6F0.ptr = q + 0x10;
    ((RegPkWord *)(q + 0x10))->w[0] = 0x15000000;
    D_004EE6F0.ptr = q + 0x14;
    ((RegPkWord *)(q + 0x10))->w[1] = 0;
    D_004EE6F0.ptr = q + 0x18;
    ((RegPkWord *)(q + 0x18))->d = 0;
    D_004EE6F0.ptr = q + 0x20;
    D_004EE6F0.tail = q + 0x20;
    ((RegPkWord *)(q + 0x20))->d = 0x60000000;
    D_004EE6F0.ptr = q + 0x28;
    ((RegPkWord *)(q + 0x28))->w[0] = 0;
    D_004EE6F0.ptr = q + 0x2C;
    ((RegPkWord *)(q + 0x28))->w[1] = 0;
    D_004EE6F0.ptr = q + 0x30;
    dl_SetDLPriority(pri);
    dl_OpenDma(5, D_004EE6F0.dma, 0);
    dl_CloseDma();
    return 1;
}
extern char D_0054FC60[];

void reg_resetDissolve(int a0)
{
    dl_SetDLPriority(a0);
    dl_OpenDma(2, D_0054FC60, 4);
    dl_CloseDma();
}
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispNObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispMObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispSObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispCObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispPoint);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispLine);
extern int D_0063A06C;
extern int GlobalTimer;
extern void _MulCurrentMatrixL(void *m);
extern void reg_dispPoint(char *node, float alpha, int idx, int flag);
extern void reg_dispLine(char *node, float alpha);

void reg_dispPointLineObj(char *o)
{
    char *mdl;
    char *grp;
    char *hdr;
    char *node;
    float *w;
    long long h;
    float alpha;
    int idx;
    int flag;
    int i;

    mdl = *(char **)(o + 0x854);
    grp = *(char **)(mdl + 0x48);
    hdr = *(char **)(o + 0x850);
    if (hdr != 0) {
        idx = *(unsigned short *)(hdr + 2) % 3;
    } else {
        idx = -1;
    }
    flag = 0;
    if (hdr != 0) {
        flag = ((int)(*(long long *)hdr >> 14)) & 1;
    }
    if (D_0063A06C != 0 || GlobalTimer != 0) {
        flag = 1;
    }
    for (i = 0; i < *(int *)(o + 8); i++) {
        w = (float *)(i * 0x50 + *(int *)(o + 0x870));
        node = *(char **)(grp + 8);
        alpha = 1.0f - (1.0f - w[12]) * w[13];
        if (!flag && (alpha < 0.0f ? -alpha : alpha) == 1.0f) {
            continue;
        }
        _SetCurrentMatrix(*(char **)(o + 0xC) + i * 0x40);
        _MulCurrentMatrixL(matrixptr + 0x100);
        node = *(char **)(node + 0xC);
        h = *(long long *)(node + 0xB8);
        while (h & 0xE000) {
            switch ((short)h >> 13) {
            case 1:
                reg_dispPoint(node, alpha, idx, flag);
                break;
            case 2:
                reg_dispLine(node, alpha);
                break;
            }
            node += 0xC0;
            h = *(long long *)(node + 0xB8);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setMatrix_190);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setLight_194);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setNMatrixPacketNoLightCalc);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispAccessoryWithShadow);
/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines reg_TransTexturePacket (line 1259) into reg_RenderReflection
   and reg_DispMultiPri, so it is `inline` in the dev's TU; while this tail
   still has asm members a deferred inline would land at the object end instead
   of at its ROM slot, so the public body stays a plain definition there and the
   C callers that inline it call this static stand-in.
   Collapses to one `inline` definition at layout. */
static inline void regTransTexturePacket(int tex, int pri) {
    if (tex >= 0) {
        D_0063B124 += tex_TransTexture(tex, pri);
    }
}
extern char *reg_setNMatrixPacket(char *o, int flag);

void reg_RenderReflection(char *o, int pri)
{
    char *mdl;
    char *grp;
    char *pkt;
    char *pk;
    int i;
    int r;

    mdl = *(char **)(o + 0x854);
    grp = *(char **)(mdl + 0x48);
    dl_SetDLPriority(pri);
    reg_transMicroCode(o, 1 << pri);
    pk = reg_setNMatrixPacket(o, 0);
    if (pk == 0) {
        return;
    }
    dl_SetDLPriority(pri);
    dl_OpenDma(5, pk, 0);
    dl_CloseDma();
    for (i = 0; i < *(signed char *)(mdl + 0x2E); i++) {
        pkt = *(char **)(grp + 8);
        while (pkt != 0) {
            r = reg_clipPacketBoundingBox(pkt);
            if (r != 0) {
                regTransTexturePacket(*(short *)(pkt + 0x84), pri);
                reg_transMaterialPacket((short *)pkt, (int *)grp);
                reg_chooseMicroCode((char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70), r, pri);
                dl_OpenDma(2, *(char **)(pkt + 0x98), (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                dl_CloseDma();
            }
            pkt = *(char **)(pkt + 0x94);
        }
        grp += 0x30;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setEMatrixPacket);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispEnemy);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispMultiPri);
extern void reg_dispNObj(char *o);
extern void reg_dispCObj(char *o);
extern void reg_dispMObj(char *o);
extern void reg_dispPointLineObj(char *o);

void reg_DispObj(char *o)
{
    if (*(unsigned short *)(o + 0x84C) == 2) {
        unsigned short type = *(unsigned long long *)(*(char **)(o + 0x854) + 0x30) >> 16;

        if ((type & 3) == 2) {
            reg_dispPointLineObj(o);
        } else {
            reg_dispMObj(o);
        }
    } else {
        unsigned short type = *(unsigned long long *)(*(char **)(o + 0x854) + 0x30) >> 16;

        switch (type & 3) {
        case 0:
            reg_dispNObj(o);
            break;
        case 1:
            reg_dispCObj(o);
            break;
        case 2:
            reg_dispPointLineObj(o);
            break;
        }
    }
}
extern void reg_dispSObj();

void reg_DispObj2(int a0, int a1, int a2, int a3)
{
    reg_dispSObj(a0, a1, a2, a3);
}
extern int D_0063A168;

void reg_SetScissorSw(int val) {
    D_0063A168 = val;
}
void reg_TransTexturePacket(int tex, int pri)
{
    if (tex >= 0) {
        D_0063B124 += tex_TransTexture(tex, pri);
    }
}
void reg_Init(void) {
    D_0063A168 = 0;
}
int reg_GetShinePri(int a0)
{
    switch (a0) {
        case 1: return 7;
        case 2: return 8;
        case 3: return 9;
    }
    return 7;
}
