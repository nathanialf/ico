#include "typedef.h"
#include "Packet.h"
#include "RegistPacket.h"
#include "DisplayP2O.h"
#include "debug.h"
#include "DisplayList.h"
#include "GsBase.h"
#include "Light.h"
#include "Shadow.h"
#include "Texture.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "main.h"
#include "debug_exception.h"
#include "GifPacket.h"
#include "Matrix.h"
#include "DmaPacket.h"
#include <assert.h>
#include "include_asm.h"

/* the scissor switch reg_SetScissorSw sets and reg_Init clears */
static int scissorSw = 0; /* derived name */

/* one sixteen-byte record of a part's strip list as reg_setShape reads it
 * (Shadow.c's ShadowRun is the silhouette's view of the same list).  A strip
 * opens with a head record, its vertex count (-1 ends the list) and the
 * strip's offset in its material's packet data; the vertex records that
 * follow hold the vertex and normal indices, and the first of them the
 * strip's material and texture slot. */
typedef struct RegStripHead { /* field names derived */
    short count;
    short pad2;
    int ofs;
    char pad8[8];
} RegStripHead; /* derived name */

typedef struct RegStripVtx { /* field names derived */
    short flag;
    short pad2;
    short vtx;
    short nrm;
    char pad8[4];
    short mat;
    short texSlot;
} RegStripVtx; /* derived name */

INCLUDE_ASM(reg_setShape);

typedef union { /* field names derived */
    sceVu0IVECTOR c;
    unsigned long long w[2];
} RegColor; /* derived name */

typedef struct { /* field names derived */
    int e[12][2];
} RegBoxLines; /* derived name */

static void reg_dispBoxLine(PacHeader *pk)
{
    RegColor col;
    RegBoxLines line;
    int i;

    if (pk == 0) {
        return;
    }
    _SetCurrentMatrix(matrixptr + 0x40);
    gif_StartPacketPri(11);
    col = (RegColor){{255, 255, 255, 80}};
    line = (RegBoxLines){{{0, 1},
                          {1, 3},
                          {3, 2},
                          {2, 0},
                          {4, 5},
                          {5, 7},
                          {7, 6},
                          {6, 4},
                          {0, 4},
                          {1, 5},
                          {2, 6},
                          {3, 7}}};
    gif_SetAlpha(1, 4, 0x20);
    _CopyMatrix(MatrixDrive_GetMatrix(), matrixptr + 0x40);
    for (i = 0; i < 12; i++) {
        DrawLine(pk->box[line.e[i][0]], pk->box[line.e[i][1]], col.c, 0);
    }
    gif_EndPacket();
}

INCLUDE_ASM(reg_clipPacketBoundingBox);

/* MicroCode.h is not included: its mc_TransMicroCode does not agree with this file */
extern void
mc_TransMicroCode(); /* K&R: called 1-ary here and 2-ary in reg_DispAccessoryWithShadow */

INCLUDE_ASM(reg_transMicroCode);

/* MicroCode.h is not included: its mc_TransMicroCode does not agree with this file */
extern void mc_SetMicroCode();

static void reg_chooseMicroCode(PObjMaterial *self, int clip, int pri)
{
    long long v_ll = self->attr.bits;
    int v_int = self->attr.word;
    mc_SetMicroCode(v_int & 1, ((int)(v_ll >> 5)) & 3, 0, clip, pri);
}

static void reg_chooseSpecularMicroCode(int mode, int clip, int pri)
{
    mc_SetMicroCode(mode, 1, 1, clip, pri);
}

static void reg_chooseReflectionMicroCode(int mode, int clip, int pri)
{
    mc_SetMicroCode(mode, 1, 2, clip, pri);
}

/* the quadword copy type src/Primitive.c and src/Shadow.c use */
typedef int Qw128 __attribute__((mode(TI))); /* derived name */

/* PacketBufferStruct (DmaPacket.h): every packet address (dma, ptr, tail,
 * gif, end) is one pointer union, read and written through its members. */

INCLUDE_ASM(setMatrix_27);

INCLUDE_ASM(setLight_31);

INCLUDE_ASM(reg_setNMatrixPacket);

typedef struct { /* field names derived */
    float x;
    float y;
    float z;
    float w;
} RegVec; /* derived name */

typedef struct { /* field names derived */
    RegVec r[4];
} RegMtx; /* derived name */

INCLUDE_ASM(setMatrix_38);

INCLUDE_ASM(setLight_42);

INCLUDE_ASM(reg_setMMatrixPacket);

/* the head of a cluster matrix packet: the DMA tag with FLUSH and the
   UNPACK, then the first quadword unpacked, the unpack's quadword count and
   the alpha the microcode fades the cluster by.  The two pad words are
   stored as plain words: stored through pad14, reg_setCMatrixPacket's
   schedule moves (measured). */
typedef struct { /* field names derived */
    DpkTag dma;
    int qwc;
    int pad14[2];
    float alpha;
} RegClusterHead; /* derived name */

INCLUDE_ASM(reg_setCMatrixPacket);

/* The GS state the specular pass draws in: a VIF DIRECT of three qwords, a
   GIF A+D tag with PABE and ALPHA_1, then the VIF MSCNT; qword aligned because
   dl_OpenDma chains it into the display list as a DMA source. */
static const unsigned int regSpecularPacket[5][4] __attribute__((aligned(16))) = {
    /* derived name */
    {0, 0, 0, 0x6C038000}, {0x8002, 0x10000000, 0xE, 0}, {0, 0, 0x49, 0},
    {0x48, 0x80, 0x42, 0}, {0x15000000, 0, 0, 0},
};

/* The specular pass, a file static all six reg_disp* functions tail-call. */
static void reg_dispSpecular(PacHeader *pkt, int clip, int mode) /* derived name */
{
    short h;
    dl_SetDLPriority(4);
    h = pkt->tex1;
    if (h >= 0) {
        texturetranssize += tex_TransTexture(h, 4);
    }
    dl_OpenDma(2, regSpecularPacket, 5);
    dl_CloseDma();
    reg_chooseSpecularMicroCode(mode, clip, 4);
    dl_OpenDma(2, pkt->data, pkt->size >> 4);
    dl_CloseDma();
}

static void reg_transMaterialPacket(PacHeader *self, PObjGroup *grp)
{
    short idx = self->mat;
    if (idx != -1) {
        PObjMaterial *v = &grp->materials[idx];
        dl_OpenDma(2, v, 6);
        dl_CloseDma();
    }
}

static int reg_setDissolve(float alpha, int pri)
{
    char *p;
    char *q;
    int v;

    v = (int)((alpha < 0.0f ? alpha + 1.0f : 1.0f - alpha) * 96.0f);
    if (v >= 128) {
        v = 127;
    }
    if (v < 0) {
        v = 0;
    }
    p = PacketBufferStruct.ptr.c;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.dma.c = p;
    PacketBufferStruct.end.c = 0;
    PacketBufferStruct.tail.c = p;
    ((GifPkWord *)p)->d = 0x10000005;
    PacketBufferStruct.ptr.c = p + 8;
    ((GifPkWord *)(p + 8))->w[0] = 0;
    PacketBufferStruct.ptr.c = p + 0xC;
    PacketBufferStruct.gif.c = p + 0xC;
    ((GifPkWord *)(p + 8))->w[1] = 0x6C048000;
    PacketBufferStruct.ptr.c = p + 0x10;
    ((GifPkWord *)(p + 0x10))->d = 0x1000000000008003LL;
    PacketBufferStruct.ptr.c = p + 0x18;
    ((GifPkWord *)(p + 0x18))->d = 14;
    PacketBufferStruct.ptr.c = p + 0x20;
    ((GifPkWord *)(p + 0x20))->d = 0;
    PacketBufferStruct.ptr.c = p + 0x28;
    ((GifPkWord *)(p + 0x28))->d = 0x49;
    PacketBufferStruct.ptr.c = p + 0x30;
    if (0.0f < alpha) {
        ((GifPkWord *)(p + 0x30))->d = ((long long)v << 32) | 0x68;
        PacketBufferStruct.ptr.c = p + 0x38;
    } else {
        ((GifPkWord *)(p + 0x30))->d = ((long long)v << 32) | 0x62;
        PacketBufferStruct.ptr.c = p + 0x38;
    }
    q = PacketBufferStruct.ptr.c;
    ((GifPkWord *)q)->d = 0x42;
    q += 8;
    PacketBufferStruct.ptr.c = q;
    ((GifPkWord *)q)->d = 0x1300000C0LL;
    PacketBufferStruct.ptr.c = q + 8;
    ((GifPkWord *)(q + 8))->d = 0x4E;
    PacketBufferStruct.ptr.c = q + 0x10;
    ((GifPkWord *)(q + 0x10))->w[0] = 0x15000000;
    PacketBufferStruct.ptr.c = q + 0x14;
    ((GifPkWord *)(q + 0x10))->w[1] = 0;
    PacketBufferStruct.ptr.c = q + 0x18;
    ((GifPkWord *)(q + 0x18))->d = 0;
    PacketBufferStruct.ptr.c = q + 0x20;
    PacketBufferStruct.tail.c = q + 0x20;
    ((GifPkWord *)(q + 0x20))->d = 0x60000000;
    PacketBufferStruct.ptr.c = q + 0x28;
    ((GifPkWord *)(q + 0x28))->w[0] = 0;
    PacketBufferStruct.ptr.c = q + 0x2C;
    ((GifPkWord *)(q + 0x28))->w[1] = 0;
    PacketBufferStruct.ptr.c = q + 0x30;
    dl_SetDLPriority(pri);
    dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
    dl_CloseDma();
    return 1;
}

/* The GS state the dissolve leaves behind, defined after reg_dispNObj (see
   there): a VIF DIRECT of two qwords, a GIF A+D tag with TEST_1, then the VIF
   MSCNT; qword aligned because
   dl_OpenDma chains it into the display list as a DMA source. */
static const unsigned int regDissolveResetPacket[4][4] __attribute__((aligned(16)));

static void reg_resetDissolve(int pri)
{
    dl_SetDLPriority(pri);
    dl_OpenDma(2, regDissolveResetPacket, 4);
    dl_CloseDma();
}

/* a texture upload counted into texturetranssize, which
   reg_TransTexturePacket, reg_RenderReflection and reg_DispMultiPri inline */
static inline void regTransTexturePacket(int tex, int pri) /* derived name */
{
    if (tex >= 0) {
        texturetranssize += tex_TransTexture(tex, pri);
    }
}

/* The GS state the reflection pass draws in: a VIF DIRECT of four qwords, a
   GIF A+D tag with CLAMP_1, PABE and ALPHA_1, then the VIF MSCNT; qword aligned because
   dl_OpenDma chains it into the display list as a DMA source. */
static const unsigned int regReflectionPacket[6][4] __attribute__((aligned(16))) = {
    /* derived name */
    {0, 0, 0, 0x6C048000}, {0x8003, 0x10000000, 0xE, 0}, {5, 0, 8, 0},
    {0, 0, 0x49, 0},       {0x48, 0x80, 0x42, 0},        {0x15000000, 0, 0, 0},
};

/* the display-list priority of a shine level, which reg_GetShinePri, the
   reg_disp*Obj and the reg_Disp* functions inline */
static inline int regGetShinePri(int shine) /* derived name */
{
    switch (shine) {
    case 1:
        return 7;
    case 2:
        return 8;
    case 3:
        return 9;
    }
    return 7;
}

/* Pick the display-list priority for one material and install it. */
static inline int regMaterialDLPri(PObjGroup *grp, int nodeIdx, TexExt *ext,
                                   float fade) /* derived name */
{
    PObjMaterial *mat = &grp->materials[nodeIdx];
    int pri = 0;

    if ((((int)(mat->attr.bits >> 1)) & 3) != 0) {
        switch (mat->attr.word & 1) {
        case 0:
            pri = 2;
            break;
        case 1:
            pri = 1;
            break;
        }
    }
    if (fade != 0.0f) {
        pri = 5;
    }
    if (ext->animated != 0 && ext->file.shine != 0) {
        pri = regGetShinePri(ext->file.shine);
    }
    dl_SetDLPriority(pri);
    return pri;
}

INCLUDE_ASM(reg_dispNObj);

/* the packet that resets the dissolve state */
static const unsigned int regDissolveResetPacket[4][4] __attribute__((aligned(16))) = {
    /* derived name */
    {0, 0, 0, 0x6C028000},
    {0x8001, 0x10000000, 0xE, 0},
    {0x300000C0, 0, 0x4E, 0},
    {0x15000000, 0, 0, 0},
};

INCLUDE_ASM(reg_dispMObj);

static void reg_dispSObj(Sub15C *o, int idx);

INCLUDE_ASM(reg_dispSObj);

INCLUDE_ASM(reg_dispCObj);

static void reg_dispPoint(PacLine *node, float alpha, int idx, int flag)
{
    float fv[4];
    int iv[4];
    int iv2[4];
    Qw128 v;
    int pri;
    int on;
    int z;

    on = 0;
    pri = (node->attr.word & 0x1800) != 0 ? 2 : 0;
    if (alpha != 0.0f || (node->attr.word & 0x1800) != 0) {
        on = 1;
    }
    z = (int)(((alpha < 0.0f) ? (alpha + 1.0f) : (1.0f - alpha)) * 128.0f);
    dl_SetDLPriority(pri);
    {
        char *c = PacketBufferStruct.ptr.c;

        PacketBufferStruct.gif.c = 0;
        PacketBufferStruct.end.c = 0;
        PacketBufferStruct.dma.c = c;
        PacketBufferStruct.tail.c = c;
        PacketBufferStruct.ptr.c = c + 8;
        ((DpkTag *)c)->vif[0] = 0x11000000;
        PacketBufferStruct.gif.c = c + 0xC;
        PacketBufferStruct.end.c = c + 0x10;
        PacketBufferStruct.ptr.c = c + 0x18;
        ((GifPkWord *)(c + 0x18))->d = 0xE;
        PacketBufferStruct.ptr.c = c + 0x20;
    }
    _RotTransPersCurrentMatrix(fv, node->pos[0]);
    _FTOI4Vector(iv, fv);
    if (idx == -1) {
        if (flag != 0) {
            _CopyIVector(iv2, iv);
        } else {
            if (systemStatus[5] == 0) {
                v = *(Qw128 *)node->pos[1];
            } else {
                v = *(Qw128 *)node->scrPrev;
            }
            *(Qw128 *)iv2 = v;
        }
        if (systemStatus[5] == 0) {
            *(Qw128 *)node->scrPrev = *(Qw128 *)node->pos[1];
            *(Qw128 *)node->pos[1] = *(Qw128 *)iv;
        }
    } else {
        if (flag != 0) {
            _CopyIVector(iv2, iv);
        } else {
            if (systemStatus[5] == 0) {
                _CopyIVector(iv2, node->trail[idx]);
            } else {
                _CopyIVector(iv2, node->trailPrev[idx]);
            }
        }
        if (systemStatus[5] == 0) {
            _CopyIVector(node->trailPrev[idx], node->trail[idx]);
            _CopyIVector(node->trail[idx], iv);
        }
    }
    if (_IsInScreen(iv) != 0 && _IsInScreen(iv2) != 0) {
        if (on != 0) {
            if (0.0f < alpha) {
                *PacketBufferStruct.ptr.d++ = 0;
                *PacketBufferStruct.ptr.d++ = 0x49;
                *PacketBufferStruct.ptr.d++ = ((long long)z << 32) | 104;
                *PacketBufferStruct.ptr.d++ = 0x42;
            } else {
                *PacketBufferStruct.ptr.d++ = 0;
                *PacketBufferStruct.ptr.d++ = 0x49;
                *PacketBufferStruct.ptr.d++ = ((long long)z << 32) | 98;
                *PacketBufferStruct.ptr.d++ = 0x42;
            }
        }
        *PacketBufferStruct.ptr.d++ = ((long long)on << 6) | 0x101;
        *PacketBufferStruct.ptr.d++ = 0;
        *PacketBufferStruct.ptr.d++ = (long long)node->col0.r | ((long long)node->col0.g << 8) |
                                      ((long long)node->col0.b << 16) |
                                      ((long long)node->col0.a << 24) | (0x3F800000LL << 32);
        *PacketBufferStruct.ptr.d++ = 1;
        *PacketBufferStruct.ptr.d++ =
            (long long)iv2[0] | ((long long)iv2[1] << 16) | ((long long)iv2[2] << 32);
        *PacketBufferStruct.ptr.d++ = 5;
        *PacketBufferStruct.ptr.d++ =
            (long long)iv[0] | ((long long)iv[1] << 16) | ((long long)iv[2] << 32);
        *PacketBufferStruct.ptr.d++ = 5;
        {
            char *p;
            char *q;

            ((GifPkWord *)PacketBufferStruct.end.c)->d =
                (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c -
                                               PacketBufferStruct.end.c) >>
                                4) -
                               1) |
                0x1000000000008000LL;
            ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
                (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
                0x6C008000;
            p = PacketBufferStruct.ptr.c;
            ((GifPkWord *)p)->w[0] = 0x15000000;
            p += 4;
            PacketBufferStruct.ptr.c = p;
            ((GifPkWord *)p)->w[0] = 0;
            PacketBufferStruct.ptr.c = p + 4;
            ((GifPkWord *)(p + 4))->w[0] = 0;
            PacketBufferStruct.ptr.c = p + 8;
            ((GifPkWord *)(p + 8))->w[0] = 0;
            PacketBufferStruct.ptr.c = p + 0xC;
            ((GifPkWord *)PacketBufferStruct.tail.c)->d =
                (unsigned int)((((unsigned int)(PacketBufferStruct.ptr.c -
                                                PacketBufferStruct.tail.c) >>
                                 4) -
                                1) |
                               0x10000000);
            q = PacketBufferStruct.ptr.c;
            PacketBufferStruct.tail.c = q;
            ((GifPkWord *)q)->d = 0x60000000;
            PacketBufferStruct.ptr.c = q + 8;
            ((GifPkWord *)(q + 8))->w[0] = 0;
            PacketBufferStruct.ptr.c = q + 0xC;
            ((GifPkWord *)(q + 8))->w[1] = 0;
            PacketBufferStruct.ptr.c = q + 0x10;
            dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
            dl_CloseDma();
        }
    }
}

/* a float's bits as the GS ST register takes them */
typedef union { /* field names derived */
    float f;
    unsigned int u;
} RegFloatBits; /* derived name */

static void reg_dispLine(PacLine *node, float alpha)
{
    float fv0[4];
    float fv1[4];
    int iv0[4];
    int iv1[4];
    char *p;
    char *q;
    long long h;
    int pri;
    int tex;
    int hastex;
    int on;
    int z;

    h = node->attr.word;
    pri = (h & 0x1800) != 0 ? 2 : 0;
    tex = (unsigned short)h << 21 >> 21;
    hastex = tex >= 0;
    on = 0;
    if (alpha != 0.0f || (h & 0x1800) != 0) {
        on = 1;
    }
    z = (int)(((alpha < 0.0f) ? (alpha + 1.0f) : (1.0f - alpha)) * 128.0f);
    dl_SetDLPriority(pri);
    if (hastex != 0) {
        long long f = node->attr.word;

        texturetranssize += tex_TransTexture((unsigned short)f << 21 >> 21, pri);
    }
    {
        char *c = PacketBufferStruct.ptr.c;

        PacketBufferStruct.gif.c = 0;
        PacketBufferStruct.end.c = 0;
        PacketBufferStruct.dma.c = c;
        PacketBufferStruct.tail.c = c;
        PacketBufferStruct.ptr.c = c + 8;
        ((DpkTag *)c)->vif[0] = 0x11000000;
        PacketBufferStruct.gif.c = c + 0xC;
        PacketBufferStruct.end.c = c + 0x10;
        PacketBufferStruct.ptr.c = c + 0x18;
        ((GifPkWord *)(c + 0x18))->d = 0xE;
        PacketBufferStruct.ptr.c = c + 0x20;
    }
    _RotTransPersCurrentMatrix(fv0, node->pos[0]);
    _RotTransPersCurrentMatrix(fv1, node->pos[1]);
    _FTOI4Vector(iv0, fv0);
    _FTOI4Vector(iv1, fv1);
    if (_IsInScreen(iv0) != 0 && _IsInScreen(iv1) != 0) {
        if (on != 0) {
            if (0.0f < alpha) {
                *PacketBufferStruct.ptr.d++ = 0;
                *PacketBufferStruct.ptr.d++ = 0x49;
                *PacketBufferStruct.ptr.d++ = ((long long)z << 32) | 104;
                *PacketBufferStruct.ptr.d++ = 0x42;
            } else {
                *PacketBufferStruct.ptr.d++ = 0;
                *PacketBufferStruct.ptr.d++ = 0x49;
                *PacketBufferStruct.ptr.d++ = ((long long)z << 32) | 98;
                *PacketBufferStruct.ptr.d++ = 0x42;
            }
        }
        /* PRIM in the GS register's field order: LINE with IIP, TME, ABE */
        *PacketBufferStruct.ptr.d++ = 9 | ((long long)hastex << 4) | ((long long)on << 6);
        *PacketBufferStruct.ptr.d++ = 0;
        *PacketBufferStruct.ptr.d++ = (long long)node->col0.r | ((long long)node->col0.g << 8) |
                                      ((long long)node->col0.b << 16) |
                                      ((long long)node->col0.a << 24) | (0x3F800000LL << 32);
        *PacketBufferStruct.ptr.d++ = 1;
        if (hastex != 0) {
            RegFloatBits u;
            RegFloatBits v;

            u.f = node->uv[0][0] / fv0[3];
            v.f = node->uv[0][1] / fv0[3];
            *PacketBufferStruct.ptr.d++ = (long long)u.u | ((long long)v.u << 32);
            *PacketBufferStruct.ptr.d++ = 2;
        }
        *PacketBufferStruct.ptr.d++ =
            (long long)iv0[0] | ((long long)iv0[1] << 16) | ((long long)iv0[2] << 32);
        *PacketBufferStruct.ptr.d++ = 5;
        *PacketBufferStruct.ptr.d++ = (long long)node->col1.r | ((long long)node->col1.g << 8) |
                                      ((long long)node->col1.b << 16) |
                                      ((long long)node->col1.a << 24) | (0x3F800000LL << 32);
        *PacketBufferStruct.ptr.d++ = 1;
        if (hastex != 0) {
            RegFloatBits u;
            RegFloatBits v;

            u.f = node->uv[1][0] / fv1[3];
            v.f = node->uv[1][1] / fv1[3];
            *PacketBufferStruct.ptr.d++ = (long long)u.u | ((long long)v.u << 32);
            *PacketBufferStruct.ptr.d++ = 2;
        }
        *PacketBufferStruct.ptr.d++ =
            (long long)iv1[0] | ((long long)iv1[1] << 16) | ((long long)iv1[2] << 32);
        *PacketBufferStruct.ptr.d++ = 5;
        ((GifPkWord *)PacketBufferStruct.end.c)->d =
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >>
                            4) -
                           1) |
            0x1000000000008000LL;
        ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
            (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
            0x6C008000;
        p = PacketBufferStruct.ptr.c;
        ((GifPkWord *)p)->w[0] = 0x15000000;
        p += 4;
        PacketBufferStruct.ptr.c = p;
        ((GifPkWord *)p)->w[0] = 0;
        PacketBufferStruct.ptr.c = p + 4;
        ((GifPkWord *)(p + 4))->w[0] = 0;
        PacketBufferStruct.ptr.c = p + 8;
        ((GifPkWord *)(p + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = p + 0xC;
        ((GifPkWord *)PacketBufferStruct.tail.c)->d =
            (unsigned int)((((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.tail.c) >>
                             4) -
                            1) |
                           0x10000000);
        q = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = q;
        ((GifPkWord *)q)->d = 0x60000000;
        PacketBufferStruct.ptr.c = q + 8;
        ((GifPkWord *)(q + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = q + 0xC;
        ((GifPkWord *)(q + 8))->w[1] = 0;
        PacketBufferStruct.ptr.c = q + 0x10;
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
}

INCLUDE_ASM(reg_dispPointLineObj);

INCLUDE_ASM(setMatrix_106);

INCLUDE_ASM(setLight_110);

INCLUDE_ASM(reg_setNMatrixPacketNoLightCalc_102);

INCLUDE_ASM(reg_DispAccessoryWithShadow);

INCLUDE_ASM(reg_RenderReflection);

/* The sixteen bytes that close the enemy matrix packet: the VIF MSCAL 0x10
   code and three zero words, copied as one quadword. */
static const sceVu0IVECTOR regEnemyEndTag = {0x15000010, 0, 0, 0}; /* derived name */

INCLUDE_ASM(reg_setEMatrixPacket_120);

INCLUDE_ASM(reg_DispEnemy);

INCLUDE_ASM(reg_DispMultiPri);

INCLUDE_ASM(reg_DispObj);

void reg_DispObj2(Sub15C *o, int idx)
{
    reg_dispSObj(o, idx);
}

void reg_SetScissorSw(int val)
{
    scissorSw = val;
}

void reg_TransTexturePacket(int tex, int pri)
{
    regTransTexturePacket(tex, pri);
}

void reg_Init(void)
{
    scissorSw = 0;
}

int reg_GetShinePri(int shine)
{
    return regGetShinePri(shine);
}
