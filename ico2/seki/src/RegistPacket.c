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

/* the scissor switch reg_SetScissorSw sets and reg_Init clears */
static int scissorSw = 0; /* derived name */

void reg_setShape(Sub15C *o, int idx, int flag, PacHeader *pkt, char *mat)
{
    float vec[4];
    PObjModel *mdl;
    PObjPart *s;
    char *p;
    char *m;
    char *v;
    PacHeader *pk;
    char *t;
    int base;
    int i;
    int n;

    mdl = o->model;
    s = &mdl->parts[idx];
    {
        char *dst = s->vtx;

        for (i = 0; i < s->vtxCount; i++) {
            _CopyVector(dst + i * 0x10, s->vtxSave + i * 0x10);
        }
    }
    {
        char *dst = s->nrm;

        if (dst != 0) {
            for (i = 0; i < s->nrmCount; i++) {
                _CopyVector(dst + i * 0x10, s->nrmSave + i * 0x10);
            }
        }
    }
    for (i = 0; i < s->morphCount; i++) {
        if (o->morphWeight[i] != 0.0f) {
            m = s->morphs[i];
            if (m != 0) {
                while (*(int *)(m + 0x10) != -1) {
                    _ScaleVectorXYZ(vec, m, o->morphWeight[i]);
                    if (*(float *)(m + 0xC) == 1.0f) {
                        if (*(unsigned int *)(m + 0x10) >= s->vtxCount) {
                            debug_StdPrintfDummy("reg_setShape:illegal vertex index. %d/%d\n",
                                                 *(unsigned int *)(m + 0x10), s->vtxCount);
                            debug_assert("src/RegistPacket.c", 635);
                            __assert("src/RegistPacket.c", 635, "0");
                        }
                        t = s->vtx;
                        t += *(int *)(m + 0x10) * 0x10;
                        _AddVectorXYZ(t, t, vec);
                    } else if (*(float *)(m + 0xC) == 0.0f) {
                        if ((((int)(*(long long *)(mat + 0x60) >> 5)) & 3) == 0) {
                            switch (*(int *)(mat + 0x60) & 1) {
                            case 1:
                                break;
                            default:
                                goto nextbone;
                            }
                        }
                        if (*(unsigned int *)(m + 0x10) >= s->nrmCount) {
                            debug_StdPrintfDummy("reg_setShape:illegal normal index. %d/%d\n",
                                                 *(unsigned int *)(m + 0x10), s->nrmCount);
                            debug_assert("src/RegistPacket.c", 642);
                            __assert("src/RegistPacket.c", 642, "0");
                        }
                        t = s->nrm;
                        t += *(int *)(m + 0x10) * 0x10;
                        _AddVectorXYZ(t, t, vec);
                    } else {
                        debug_assert("src/RegistPacket.c", 647);
                        __assert("src/RegistPacket.c", 647, "0");
                    }
                nextbone:
                    m += 0x20;
                }
            }
        }
    }
    for (i = 0; i < s->stripCount; i++) {
        v = ((char **)s->strips)[i];
        while (*(short *)v != -1) {
            pk = pkt;
            n = *(short *)v;
            v += 0x10;
            while (pk != 0) {
                if (*(short *)(v + 0xE) == pk->shape && *(short *)(v + 0xC) == pk->mat) {
                    break;
                }
                pk = pk->next;
            }
            if (pk == 0) {
                break;
            }
            base = (int)pk->data;
            p = (char *)(*(int *)(v - 0xC) + base);
            if (*(int *)(v - 0xC) != 0) {
                if (n != 0) {
                    do {
                        _CopyVector(p, s->vtx + *(short *)(v + 4) * 0x10);
                        p += 0x10;
                        if ((((int)(*(long long *)(mat + 0x60) >> 5)) & 3) == 0) {
                            switch (*(int *)(mat + 0x60) & 1) {
                            case 1:
                                break;
                            default:
                                goto nocopy;
                            }
                        }
                        _CopyVector(p, s->nrm + *(short *)(v + 6) * 0x10);
                        p += 0x10;
                    nocopy:
                        if (mdl->disp != 0) {
                            p += 0x10;
                        }
                        n--;
                        v += 0x10;
                        p += 0x20;
                    } while (n != 0);
                }
            }
        }
    }
}

typedef union { /* field names derived */
    sceVu0IVECTOR c;
    unsigned long long w[2];
} RegColor; /* derived name */

typedef struct { /* field names derived */
    int e[12][2];
} RegBoxLines; /* derived name */

void reg_dispBoxLine(PacHeader *pk)
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

int reg_clipPacketBoundingBox(PacHeader *pk)
{
    int ret = 1;
    int type;

    _SetCurrentMatrix(matrixptr + 0x300);

    type = ((unsigned char *)&pk->size)[3];
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
        debug_StdPrintfDummy("illegal clip type. %d\n", type);
        debug_assert("src/RegistPacket.c", 821);
        __assert("src/RegistPacket.c", 821, "0");
        break;
    }
    if (debug_bounding_flag & 2) {
        reg_dispBoxLine(pk);
    }
    return ret;
}

/* MicroCode.h is not included: its mc_TransMicroCode does not agree with this file */
extern void
mc_TransMicroCode(); /* K&R: called 1-ary here and 2-ary in reg_DispAccessoryWithShadow */

void reg_transMicroCode(Sub15C *a0, int mask)
{
    if (a0->model->disp != 0) {
        mc_TransMicroCode(3);
        return;
    }
    if (a0->lightMtx->mode == 0) {
        mc_TransMicroCode(1);
        return;
    }
    mc_TransMicroCode(2);
}

/* MicroCode.h is not included: its mc_TransMicroCode does not agree with this file */
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

/* One 64-bit slot of a DMA/GIF packet: written either as the whole qword
   (DMAtag, GIFtag, A+D data) or as its two 32-bit halves. */
typedef union { /* field names derived */
    long long d;
    int w[2];
} RegPkWord; /* derived name */

/* the quadword copy type src/Primitive.c and src/Shadow.c use */
typedef int Qw128 __attribute__((mode(TI))); /* derived name */

/* PacketBufferStruct (DmaPacket.h): every packet address (dma, ptr, tail,
 * gif, end) is one pointer union, read and written through its members. */

char *reg_setNMatrixPacket(Sub15C *o, int idx)
{
    void setMatrix(void)
    {
        char *c;
        char *m;

        c = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = c;
        ((RegPkWord *)c)->d = 0x1000000D;
        PacketBufferStruct.ptr.c = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = c + 0xC;
        PacketBufferStruct.gif.c = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0x6C0C8000;
        PacketBufferStruct.ptr.c = c + 0x50;
        _CopyMatrix(c + 0x10, matrixptr + 0x140);
        _MulMatrix(PacketBufferStruct.ptr.c, matrixptr + 0x200, matrixptr + 0x40);
        PacketBufferStruct.ptr.c = PacketBufferStruct.ptr.c + 0x40;
        _MulMatrix(PacketBufferStruct.ptr.c, matrixptr + 0x80, matrixptr + 0x40);
        m = PacketBufferStruct.ptr.c;
        PacketBufferStruct.ptr.c = m + 0x40;
        ((RegPkWord *)(m + 0x40))->w[0] = 0x15000010;
        PacketBufferStruct.ptr.c = m + 0x44;
        ((RegPkWord *)(m + 0x40))->w[1] = 0;
        PacketBufferStruct.ptr.c = m + 0x48;
        ((RegPkWord *)(m + 0x48))->d = 0;
        PacketBufferStruct.ptr.c = m + 0x50;
    }
    void setLight(void)
    {
        char *c;
        char *m;
        char *n;

        c = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = c;
        ((RegPkWord *)c)->d = 0x10000009;
        PacketBufferStruct.ptr.c = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = c + 0xC;
        PacketBufferStruct.gif.c = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0x6C088000;
        PacketBufferStruct.ptr.c = c + 0x10;
        _GetCurrentMatrix(c + 0x10);
        m = PacketBufferStruct.ptr.c;
        PacketBufferStruct.ptr.c = m + 0x80;
        _CopyMatrix(m + 0x40, (char *)o->lightMtx + 64);
        n = PacketBufferStruct.ptr.c;
        ((RegPkWord *)n)->w[0] = 0x15000012;
        n += 4;
        PacketBufferStruct.ptr.c = n;
        ((RegPkWord *)n)->w[0] = 0;
        PacketBufferStruct.ptr.c = n + 4;
        ((RegPkWord *)(n + 4))->d = 0;
        PacketBufferStruct.ptr.c = n + 0xC;
    }
    char *pkt;
    char *box;
    struct DObjNode *scl;
    int mode;

    scl = (struct DObjNode *)(idx * 80 + (int)o->nodes);
    mode = o->lightMtx->mode;
    if (scl->scale[0] != 1.0f || scl->scale[1] != 1.0f || scl->scale[2] != 1.0f) {
        _InitCurrentMatrix();
        _SetCurrentMatrix((char *)o->nodeMtx + idx * 64);
        _ScaleCurrentMatrix(o->nodes[idx].scale[0], o->nodes[idx].scale[1], o->nodes[idx].scale[2]);
        _GetCurrentMatrix(matrixptr + 0x40);
    } else {
        _CopyMatrix(matrixptr + 0x40, (char *)o->nodeMtx + idx * 64);
    }
    _MulMatrix(matrixptr + 0x300, matrixptr + 0x280, matrixptr + 0x40);
    _MulMatrix(matrixptr + 0x140, matrixptr + 0x100, matrixptr + 0x40);
    box = (char *)o->model->box;
    _SetCurrentMatrix(matrixptr + 0x300);
    if (gsb_ClipBox(box) == 0) {
        if (o->shadow != 0) {
            light_MakeLightMatrix(o, idx);
        }
        return 0;
    }
    pkt = PacketBufferStruct.ptr.c;
    PacketBufferStruct.dma.c = pkt;
    PacketBufferStruct.tail.c = 0;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.end.c = 0;
    setMatrix();
    if (mode != 0 && mode != 3) {
        light_MakeLightMatrix(o, idx);
        _SetCurrentMatrix(matrixptr + 0x40);
        _ClearTransCurrentMatrix();
        _MulCurrentMatrixL((char *)o->lightMtx);
        setLight();
    }
    {
        char *c = PacketBufferStruct.ptr.c;

        PacketBufferStruct.tail.c = c;
        ((RegPkWord *)c)->d = 0x60000000;
        PacketBufferStruct.ptr.c = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0;
        PacketBufferStruct.ptr.c = c + 0x10;
    }
    return pkt;
}

typedef struct { /* field names derived */
    float x;
    float y;
    float z;
    float w;
} RegVec; /* derived name */

typedef struct { /* field names derived */
    RegVec r[4];
} RegMtx; /* derived name */

char *reg_setMMatrixPacket(Sub15C *o, int idx)
{
    RegVec s;
    RegVec v;
    char *pkt;
    char *box;
    struct DObjNode *w;
    int mode;

    void setMatrix(void)
    {
        char *c;
        char *m;

        c = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = c;
        ((RegPkWord *)c)->d = 0x1000000D;
        PacketBufferStruct.ptr.c = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = c + 0xC;
        PacketBufferStruct.gif.c = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0x6C0C8000;
        PacketBufferStruct.ptr.c = c + 0x50;
        _CopyMatrix(c + 0x10, matrixptr + 0x140);
        if ((o->nodes[idx].flags.ll & 6) != 0) {
            _MulMatrix(PacketBufferStruct.ptr.c, matrixptr + 0x1C0, matrixptr + 0x180);
        } else {
            _MulMatrix(matrixptr + 0x180, matrixptr + 0x80, matrixptr + 0x40);
            _MulMatrix(PacketBufferStruct.ptr.c, matrixptr + 0x200, matrixptr + 0x40);
        }
        PacketBufferStruct.ptr.c = PacketBufferStruct.ptr.c + 0x40;
        _MulMatrix(PacketBufferStruct.ptr.c, matrixptr + 0x80, matrixptr + 0x40);
        m = PacketBufferStruct.ptr.c;
        PacketBufferStruct.ptr.c = m + 0x40;
        ((RegPkWord *)(m + 0x40))->w[0] = 0x15000010;
        PacketBufferStruct.ptr.c = m + 0x44;
        ((RegPkWord *)(m + 0x40))->w[1] = 0;
        PacketBufferStruct.ptr.c = m + 0x48;
        ((RegPkWord *)(m + 0x48))->d = 0;
        PacketBufferStruct.ptr.c = m + 0x50;
    }
    void setLight(void)
    {
        char *c;
        char *m;
        char *n;

        c = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = c;
        ((RegPkWord *)c)->d = 0x10000009;
        PacketBufferStruct.ptr.c = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = c + 0xC;
        PacketBufferStruct.gif.c = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0x6C088000;
        PacketBufferStruct.ptr.c = c + 0x10;
        _GetCurrentMatrix(c + 0x10);
        m = PacketBufferStruct.ptr.c;
        PacketBufferStruct.ptr.c = m + 0x80;
        _CopyMatrix(m + 0x40, (char *)o->lightMtx + 64);
        n = PacketBufferStruct.ptr.c;
        ((RegPkWord *)n)->w[0] = 0x15000012;
        n += 4;
        PacketBufferStruct.ptr.c = n;
        ((RegPkWord *)n)->w[0] = 0;
        PacketBufferStruct.ptr.c = n + 4;
        ((RegPkWord *)(n + 4))->d = 0;
        PacketBufferStruct.ptr.c = n + 0xC;
    }
    w = (struct DObjNode *)(idx * 80 + (int)o->nodes);
    mode = o->lightMtx->mode;
    if ((w->flags.ll & 2) != 0) {
        RegMtx um;

        _SetCurrentMatrix((char *)o->nodeMtx + idx * 64);
        _ClearTransCurrentMatrix();
        _UnitMatrix(&um);
        _ApplyCurrentMatrix(&v, &um.r[0]);
        s.x = _GetLength(&v, &um.r[3]);
        _ApplyCurrentMatrix(&v, &um.r[1]);
        s.y = _GetLength(&v, &um.r[3]);
        _ApplyCurrentMatrix(&v, &um.r[2]);
        s.z = _GetLength(&v, &um.r[3]);
        _InitCurrentMatrix();
        if (o->nodes[idx].pos[2] < 5.0f) {
            _ScaleVectorXYZ(&s, &s, 5.0f);
            _ScaleCurrentMatrix(s.x, s.y, s.z);
            _ScaleVectorXYZ(&s, o->nodes[idx].pos, 5.0f);
            s.w = 1.0f;
            _SetTransCurrentMatrix(&s);
        } else {
            _ScaleCurrentMatrix(s.x, s.y, s.z);
            _SetTransCurrentMatrix(o->nodes[idx].pos);
        }
        _GetCurrentMatrix(matrixptr + 0x180);
        _MulMatrix(matrixptr + 0x140, matrixptr + 0x640, matrixptr + 0x180);
        _MulMatrix(matrixptr + 0x300, matrixptr + 0x680, matrixptr + 0x180);
    } else if ((w->flags.ll & 4) != 0) {
        RegMtx um2;

        _MulMatrix(matrixptr + 0x180, matrixptr + 0x80, (char *)o->nodeMtx + idx * 64);
        _UnitMatrix(&um2);
        _SetCurrentMatrix(matrixptr + 0x180);
        _ClearTransCurrentMatrix();
        _ApplyCurrentMatrix(&v, &um2.r[0]);
        s.x = _GetLength(&v, &um2.r[3]);
        _ApplyCurrentMatrix(&v, &um2.r[1]);
        s.y = _GetLength(&v, &um2.r[3]);
        _ApplyCurrentMatrix(&v, &um2.r[2]);
        s.z = _GetLength(&v, &um2.r[3]);
        _InitCurrentMatrix();
        _TransCurrentMatrix(matrixptr + 0x1B0);
        _RotCurrentMatrixZ(*(short *)((char *)&o->nodes[idx] + 58));
        _ScaleCurrentMatrix(s.x, s.y, s.z);
        _GetCurrentMatrix(matrixptr + 0x180);
        _MulMatrix(matrixptr + 0x140, matrixptr + 0xC0, matrixptr + 0x180);
        _MulMatrix(matrixptr + 0x300, matrixptr + 0x240, matrixptr + 0x180);
    } else {
        if (w->scale[0] != 1.0f || w->scale[1] != 1.0f || w->scale[2] != 1.0f) {
            _InitCurrentMatrix();
            _SetCurrentMatrix((char *)o->nodeMtx + idx * 64);
            _ScaleCurrentMatrix(o->nodes[idx].scale[0], o->nodes[idx].scale[1],
                                o->nodes[idx].scale[2]);
            _GetCurrentMatrix(matrixptr + 0x40);
        } else {
            _CopyMatrix(matrixptr + 0x40, (char *)o->nodeMtx + idx * 64);
        }
        _MulMatrix(matrixptr + 0x140, matrixptr + 0x100, matrixptr + 0x40);
        _MulMatrix(matrixptr + 0x300, matrixptr + 0x280, matrixptr + 0x40);
    }
    box = (char *)o->model->box;
    _SetCurrentMatrix(matrixptr + 0x300);
    if (gsb_ClipBox(box) == 0) {
        if (o->shadow != 0) {
            light_MakeLightMatrix(o, idx);
        }
        return 0;
    }
    pkt = PacketBufferStruct.ptr.c;
    PacketBufferStruct.dma.c = pkt;
    PacketBufferStruct.tail.c = 0;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.end.c = 0;
    setMatrix();
    if (mode != 0 && mode != 3) {
        light_MakeLightMatrix(o, idx);
        _SetCurrentMatrix(matrixptr + 0x40);
        _ClearTransCurrentMatrix();
        _MulCurrentMatrixL((char *)o->lightMtx);
        setLight();
    }
    {
        char *c = PacketBufferStruct.ptr.c;

        PacketBufferStruct.tail.c = c;
        ((RegPkWord *)c)->d = 0x60000000;
        PacketBufferStruct.ptr.c = c + 8;
        ((RegPkWord *)(c + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = c + 0xC;
        ((RegPkWord *)(c + 8))->w[1] = 0;
        PacketBufferStruct.ptr.c = c + 0x10;
    }
    return pkt;
}

void reg_setCMatrixPacket(Sub15C *o, float alpha, int prilist)
{
    int i;
    int haslight;

    inline void pack(void)
    {
        char *c;
        char *m;
        int n;

        n = o->nodeNum * 4;
        c = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = c;
        *(long long *)c = n | 0x10000002;
        PacketBufferStruct.ptr.c = c + 8;
        *(int *)(c + 8) = 0x11000000;
        PacketBufferStruct.ptr.c = c + 0xC;
        PacketBufferStruct.gif.c = c + 0xC;
        *(int *)(c + 0xC) = ((n + 1) << 16) | 0x6C008000;
        PacketBufferStruct.ptr.c = c + 0x10;
        *(int *)(c + 0x10) = n + 1;
        PacketBufferStruct.ptr.c = c + 0x14;
        *(int *)(c + 0x14) = 0;
        PacketBufferStruct.ptr.c = c + 0x18;
        *(int *)(c + 0x18) = 0;
        PacketBufferStruct.ptr.c = c + 0x1C;
        *(float *)(c + 0x1C) = alpha;
        PacketBufferStruct.ptr.c = c + 0x20;
        for (i = 0; i < o->nodeNum; i++) {
            _MulMatrix(PacketBufferStruct.ptr.c, (char *)o->nodeMtx + i * 64,
                       o->clusterMtx + i * 64);
            PacketBufferStruct.ptr.c = PacketBufferStruct.ptr.c + 0x40;
        }
        m = PacketBufferStruct.ptr.c;
        *(int *)m = 0x15000010;
        m += 4;
        PacketBufferStruct.ptr.c = m;
        *(int *)m = 0;
        PacketBufferStruct.ptr.c = m + 4;
        *(long long *)(m + 4) = 0;
        PacketBufferStruct.ptr.c = m + 0xC;
    }
    inline void light(void)
    {
        char *c;
        char *n;

        c = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = c;
        *(long long *)c = 0x10000009;
        PacketBufferStruct.ptr.c = c + 8;
        *(int *)PacketBufferStruct.ptr.c = 0;
        PacketBufferStruct.ptr.c = c + 0xC;
        PacketBufferStruct.gif.c = c + 0xC;
        *(int *)PacketBufferStruct.gif.c = 0x6C088000;
        /* the two light matrices go in through the cursor post-increment
         * src/Primitive.c's setLight uses; the c + 0x10 store is overwritten
         * by the first increment's store */
        PacketBufferStruct.ptr.c = c + 0x10;
        _CopyMatrix(((float (*)[16])PacketBufferStruct.ptr.c)++, (char *)o->lightMtx);
        _CopyMatrix(((float (*)[16])PacketBufferStruct.ptr.c)++, (char *)o->lightMtx + 64);
        n = PacketBufferStruct.ptr.c;
        *(int *)n = 0x15000012;
        n += 4;
        PacketBufferStruct.ptr.c = n;
        *(int *)n = 0;
        PacketBufferStruct.ptr.c = n + 4;
        *(long long *)(n + 4) = 0;
        PacketBufferStruct.ptr.c = n + 0xC;
    }

    haslight = o->lightMtx->mode != 0;
    light_MakeLightMatrix(o, 0);
    PacketBufferStruct.dma.c = PacketBufferStruct.ptr.c;
    PacketBufferStruct.tail.c = 0;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.end.c = 0;
    pack();
    if (haslight) {
        light();
    } else {
        debug_StdPrintfDummy("no light calc cluster model %s\n", o->model);
        debug_assert("src/RegistPacket.c", 1238);
        __assert("src/RegistPacket.c", 1238, "0");
    }
    {
        char *c = PacketBufferStruct.ptr.c;

        PacketBufferStruct.tail.c = c;
        *(long long *)c = 0x60000000;
        PacketBufferStruct.ptr.c = c + 8;
        *(int *)(c + 8) = 0;
        PacketBufferStruct.ptr.c = c + 0xC;
        *(int *)(c + 0xC) = 0;
        PacketBufferStruct.ptr.c = c + 0x10;
    }
    for (i = 0; i < 13; i++) {
        if ((prilist >> i) & 1) {
            dl_SetDLPriority(i);
            dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
            dl_CloseDma();
        }
    }
}

/* The GS state the specular pass draws in: a VIF DIRECT of three qwords, a
   GIF A+D tag with PABE and ALPHA_1, then the VIF MSCNT; qword aligned because
   dl_OpenDma chains it into the display list as a DMA source. */
static const unsigned int regSpecularPacket[5][4] __attribute__((aligned(16))) = {
    /* derived name */
    {0, 0, 0, 0x6C038000}, {0x8002, 0x10000000, 0xE, 0}, {0, 0, 0x49, 0},
    {0x48, 0x80, 0x42, 0}, {0x15000000, 0, 0, 0},
};

/* The specular pass, a file static all six reg_disp* functions tail-call. */
static void reg_dispSpecular(PacHeader *a0, int a1, int a2) /* derived name */
{
    short h;
    dl_SetDLPriority(4);
    h = a0->tex1;
    if (h >= 0) {
        texturetranssize += tex_TransTexture(h, 4);
    }
    dl_OpenDma(2, regSpecularPacket, 5);
    dl_CloseDma();
    reg_chooseSpecularMicroCode(a2, a1, 4);
    dl_OpenDma(2, a0->data, (a0->size & 0xFFFFFF) >> 4);
    dl_CloseDma();
}

void reg_transMaterialPacket(PacHeader *self, int *p)
{
    short idx = self->mat;
    if (idx != -1) {
        char *v = (char *)*p + idx * 0x70;
        dl_OpenDma(2, v, 6);
        dl_CloseDma();
    }
}

int reg_setDissolve(float a, int pri)
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
    p = PacketBufferStruct.ptr.c;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.dma.c = p;
    PacketBufferStruct.end.c = 0;
    PacketBufferStruct.tail.c = p;
    ((RegPkWord *)p)->d = 0x10000005;
    PacketBufferStruct.ptr.c = p + 8;
    ((RegPkWord *)(p + 8))->w[0] = 0;
    PacketBufferStruct.ptr.c = p + 0xC;
    PacketBufferStruct.gif.c = p + 0xC;
    ((RegPkWord *)(p + 8))->w[1] = 0x6C048000;
    PacketBufferStruct.ptr.c = p + 0x10;
    ((RegPkWord *)(p + 0x10))->d = 0x1000000000008003LL;
    PacketBufferStruct.ptr.c = p + 0x18;
    ((RegPkWord *)(p + 0x18))->d = 14;
    PacketBufferStruct.ptr.c = p + 0x20;
    ((RegPkWord *)(p + 0x20))->d = 0;
    PacketBufferStruct.ptr.c = p + 0x28;
    ((RegPkWord *)(p + 0x28))->d = 0x49;
    PacketBufferStruct.ptr.c = p + 0x30;
    if (0.0f < a) {
        ((RegPkWord *)(p + 0x30))->d = ((long long)v << 32) | 0x68;
        PacketBufferStruct.ptr.c = p + 0x38;
    } else {
        ((RegPkWord *)(p + 0x30))->d = ((long long)v << 32) | 0x62;
        PacketBufferStruct.ptr.c = p + 0x38;
    }
    q = PacketBufferStruct.ptr.c;
    ((RegPkWord *)q)->d = 0x42;
    q += 8;
    PacketBufferStruct.ptr.c = q;
    ((RegPkWord *)q)->d = 0x1300000C0LL;
    PacketBufferStruct.ptr.c = q + 8;
    ((RegPkWord *)(q + 8))->d = 0x4E;
    PacketBufferStruct.ptr.c = q + 0x10;
    ((RegPkWord *)(q + 0x10))->w[0] = 0x15000000;
    PacketBufferStruct.ptr.c = q + 0x14;
    ((RegPkWord *)(q + 0x10))->w[1] = 0;
    PacketBufferStruct.ptr.c = q + 0x18;
    ((RegPkWord *)(q + 0x18))->d = 0;
    PacketBufferStruct.ptr.c = q + 0x20;
    PacketBufferStruct.tail.c = q + 0x20;
    ((RegPkWord *)(q + 0x20))->d = 0x60000000;
    PacketBufferStruct.ptr.c = q + 0x28;
    ((RegPkWord *)(q + 0x28))->w[0] = 0;
    PacketBufferStruct.ptr.c = q + 0x2C;
    ((RegPkWord *)(q + 0x28))->w[1] = 0;
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

void reg_resetDissolve(int a0)
{
    dl_SetDLPriority(a0);
    dl_OpenDma(2, regDissolveResetPacket, 4);
    dl_CloseDma();
}

/* a file-static copy of reg_TransTexturePacket, which reg_RenderReflection
   and reg_DispMultiPri inline */
static inline void regTransTexturePacket(int tex, int pri) /* derived name */
{
    if (tex >= 0) {
        texturetranssize += tex_TransTexture(tex, pri);
    }
}

static void reg_dispSpecular(PacHeader *pkt, int r, int c);

/* The GS state the reflection pass draws in: a VIF DIRECT of four qwords, a
   GIF A+D tag with CLAMP_1, PABE and ALPHA_1, then the VIF MSCNT; qword aligned because
   dl_OpenDma chains it into the display list as a DMA source. */
static const unsigned int regReflectionPacket[6][4] __attribute__((aligned(16))) = {
    /* derived name */
    {0, 0, 0, 0x6C048000}, {0x8003, 0x10000000, 0xE, 0}, {5, 0, 8, 0},
    {0, 0, 0x49, 0},       {0x48, 0x80, 0x42, 0},        {0x15000000, 0, 0, 0},
};

/* a file-static copy of reg_GetShinePri, which the reg_disp*Obj and
   reg_Disp* functions inline */
static inline int regGetShinePri(int a0) /* derived name */
{
    switch (a0) {
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
static inline int regMaterialDLPri(int *grp, int nodeIdx, int *ext, float fade) /* derived name */
{
    char *mat = (char *)(*grp + nodeIdx * 0x70);
    int pri = 0;

    if ((((int)(*(long long *)(mat + 0x60) >> 1)) & 3) != 0) {
        switch (*(int *)(mat + 0x60) & 1) {
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
    if (ext[0x40 / 4] != 0 && ext[0x24 / 4] != 0) {
        pri = regGetShinePri(ext[0x24 / 4]);
    }
    dl_SetDLPriority(pri);
    return pri;
}

void reg_dispNObj(Sub15C *o)
{
    PObjModel *mdl;
    char *grp;
    char *pk;
    PacHeader *pkt;
    char *box;
    int i;
    int j;
    int r;
    int pri;
    int mode;

    mdl = o->model;
    grp = mdl->groups;
    reg_transMicroCode(o, 0x3B5);
    pk = reg_setNMatrixPacket(o, 0);
    if (pk != 0) {
        int prilist = 0x3B5;

        for (i = 0; i < 13; i++) {
            if ((prilist >> i) & 1) {
                dl_SetDLPriority(i);
                dl_OpenDma(5, pk, 0);
                dl_CloseDma();
            }
        }
        for (j = 0; j < mdl->partCount; j++, grp += 0x30) {
            box = (char *)(j * 128 + (int)o->model->boxes);
            _SetCurrentMatrix(matrixptr + 0x300);
            if (gsb_ClipBox(box) != 0) {
                pkt = *(PacHeader **)(grp + 8);
                while (pkt != 0) {
                    r = reg_clipPacketBoundingBox(pkt);
                    if (r != 0) {
                        pri = regMaterialDLPri((int *)grp, pkt->mat, tex_GetTexExtData(pkt->tex),
                                               0.0f);
                        regTransTexturePacket(pkt->tex, pri);
                        reg_transMaterialPacket(pkt, (int *)grp);
                        reg_chooseMicroCode((char *)(*(int *)grp + pkt->mat * 0x70), r, pri);
                        dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                        dl_CloseDma();
                        if (o->lightMtx->mode == 2) {
                            if (pkt->tex1 != -1) {
                                reg_dispSpecular(pkt, r, 0);
                            }
                        }
                        mode = o->lightMtx->mode;
                        if (pkt->tex2 != -1) {
                            if (mode == 0) {
                                debug_StdPrintfDummy("光源オフでリフレクションを表示.\n");
                                mc_TransMicroCode(2, 0x10);
                            }
                            dl_SetDLPriority(4);
                            regTransTexturePacket(pkt->tex2, 4);
                            dl_OpenDma(2, regReflectionPacket, 6);
                            dl_CloseDma();
                            reg_chooseReflectionMicroCode(0, r, 4);
                            dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                            dl_CloseDma();
                            if (mode == 0) {
                                mc_TransMicroCode(1, 0x10);
                            }
                        }
                    }
                    pkt = pkt->next;
                }
            }
        }
    }
    if (o->shadow != 0) {
        shadow_RenderVolume(o);
    }
}

/* the packet that resets the dissolve state */
static const unsigned int regDissolveResetPacket[4][4] __attribute__((aligned(16))) = {
    /* derived name */
    {0, 0, 0, 0x6C028000},
    {0x8001, 0x10000000, 0xE, 0},
    {0x300000C0, 0, 0x4E, 0},
    {0x15000000, 0, 0, 0},
};

void reg_dispMObj(Sub15C *o)
{
    PObjModel *mdl;
    char *grp;
    PacHeader *pkt;
    char *pk;
    struct DObjNode *w;
    float alpha;
    int i;
    int j;
    int r;
    int dis;
    int fade;
    int pri;
    int mode;
    int prilist;

    mdl = o->model;
    grp = mdl->groups;
    reg_transMicroCode(o, 0x3B5);
    for (i = 0; i < *(int *)((char *)o + 8); i++) {
        w = (struct DObjNode *)(i * 80 + (int)o->nodes);
        alpha = 1.0f - (1.0f - w->fade) * w->alpha;
        if ((alpha < 0.0f ? -alpha : alpha) == 1.0f) {
            continue;
        }
        pk = reg_setMMatrixPacket(o, i);
        if (pk != 0) {
            prilist = 0x3B5;
            for (j = 0; j < 13; j++) {
                if ((prilist >> j) & 1) {
                    dl_SetDLPriority(j);
                    dl_OpenDma(5, pk, 0);
                    dl_CloseDma();
                }
            }
            if (mdl->parts[i].morphCount != 0) {
                if (*(char **)(grp + 0xC) != 0) {
                    if (buffer_ID != 0) {
                        pkt = *(PacHeader **)(grp + 8);
                    } else {
                        pkt = *(PacHeader **)(grp + 0xC);
                    }
                    reg_setShape(o, i, buffer_ID == 0, pkt,
                                 (char *)(*(int *)grp + pkt->mat * 0x70));
                } else {
                    pkt = *(PacHeader **)(grp + 8);
                }
            } else {
                pkt = *(PacHeader **)(grp + 8);
            }
            while (pkt != 0) {
                r = reg_clipPacketBoundingBox(pkt);
                if (r != 0) {
                    fade = 0;
                    if ((o->nodes[i].flags.ll & 1) == 1) {
                        if (alpha != 0.0f) {
                            fade = 1;
                        }
                    }
                    pri = regMaterialDLPri((int *)grp, pkt->mat, tex_GetTexExtData(pkt->tex), fade);
                    regTransTexturePacket(pkt->tex, pri);
                    reg_transMaterialPacket(pkt, (int *)grp);
                    dis = 0;
                    if (fade != 0) {
                        dis = reg_setDissolve(alpha, pri);
                    }
                    if (dis != -1) {
                        reg_chooseMicroCode((char *)(*(int *)grp + pkt->mat * 0x70), r, pri);
                        dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                        dl_CloseDma();
                        if (o->lightMtx->mode == 2) {
                            if (pkt->tex1 != -1) {
                                reg_dispSpecular(pkt, r, 0);
                            }
                        }
                        mode = o->lightMtx->mode;
                        if (pkt->tex2 != -1) {
                            if (mode == 0) {
                                debug_StdPrintfDummy("光源オフでリフレクションを表示.\n");
                                mc_TransMicroCode(2, 0x10);
                            }
                            dl_SetDLPriority(4);
                            regTransTexturePacket(pkt->tex2, 4);
                            dl_OpenDma(2, regReflectionPacket, 6);
                            dl_CloseDma();
                            reg_chooseReflectionMicroCode(0, r, 4);
                            dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                            dl_CloseDma();
                            if (mode == 0) {
                                mc_TransMicroCode(1, 0x10);
                            }
                        }
                    }
                    if (dis == 1) {
                        reg_resetDissolve(pri);
                    }
                }
                pkt = pkt->next;
            }
        }
        if (o->shadow != 0) {
            shadow_RenderVolumeMulti(o, i);
        }
    }
}

void reg_dispSObj(Sub15C *o, int idx)
{
    char *grp;
    PacHeader *pkt;
    char *pk;
    int i;
    int r;
    int pri;
    int mode;

    grp = o->model->groups;
    pkt = *(PacHeader **)(grp + 8);
    reg_transMicroCode(o, 0x3B5);
    pk = reg_setMMatrixPacket(o, idx);
    if (pk != 0) {
        int prilist = 0x3B5;

        for (i = 0; i < 13; i++) {
            if ((prilist >> i) & 1) {
                dl_SetDLPriority(i);
                dl_OpenDma(5, pk, 0);
                dl_CloseDma();
            }
        }
        while (pkt != 0) {
            r = reg_clipPacketBoundingBox(pkt);
            if (r != 0) {
                pri = regMaterialDLPri((int *)grp, pkt->mat, tex_GetTexExtData(pkt->tex), 0.0f);
                regTransTexturePacket(pkt->tex, pri);
                reg_transMaterialPacket(pkt, (int *)grp);
                reg_chooseMicroCode((char *)(*(int *)grp + pkt->mat * 0x70), r, pri);
                dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                dl_CloseDma();
                if (o->lightMtx->mode == 2) {
                    if (pkt->tex1 != -1) {
                        reg_dispSpecular(pkt, r, 0);
                    }
                }
                mode = o->lightMtx->mode;
                if (pkt->tex2 != -1) {
                    if (mode == 0) {
                        debug_StdPrintfDummy("光源オフでリフレクションを表示.\n");
                        mc_TransMicroCode(2, 0x10);
                    }
                    dl_SetDLPriority(4);
                    regTransTexturePacket(pkt->tex2, 4);
                    dl_OpenDma(2, regReflectionPacket, 6);
                    dl_CloseDma();
                    reg_chooseReflectionMicroCode(0, r, 4);
                    dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                    dl_CloseDma();
                    if (mode == 0) {
                        mc_TransMicroCode(1, 0x10);
                    }
                }
            }
            pkt = pkt->next;
        }
    }
    if (o->shadow != 0) {
        shadow_RenderVolume(o);
    }
}

void reg_dispCObj(Sub15C *o)
{
    PObjModel *mdl;
    char *grp;
    PacHeader *pkt;
    PacHeader *node;
    int i;
    int pri;

    mdl = o->model;
    grp = mdl->groups;
    reg_transMicroCode(o, 0x3B3);
    reg_setCMatrixPacket(o, 1.0f, 0x3B3);
    for (i = 0; i < mdl->partCount; i++, grp += 0x30) {
        if (mdl->parts[i].morphCount != 0) {
            node = *(PacHeader **)(grp + 0xC);
            if (node != 0) {
                pkt = node;
                if (buffer_ID != 0) {
                    pkt = *(PacHeader **)(grp + 8);
                }
                reg_setShape(o, i, buffer_ID == 0, pkt, (char *)(*(int *)grp + pkt->mat * 0x70));
            } else {
                pkt = *(PacHeader **)(grp + 8);
            }
        } else {
            pkt = *(PacHeader **)(grp + 8);
        }
        while (pkt != 0) {
            pri = regMaterialDLPri((int *)grp, pkt->mat, tex_GetTexExtData(pkt->tex), 0.0f);
            regTransTexturePacket(pkt->tex, pri);
            reg_transMaterialPacket(pkt, (int *)grp);
            reg_chooseMicroCode((char *)(*(int *)grp + pkt->mat * 0x70), 0, pri);
            dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
            dl_CloseDma();
            if (debug_specular_flag == 2 && o->lightMtx->mode == 2) {
                if (pkt->tex1 != -1) {
                    reg_dispSpecular(pkt, 0, 1);
                }
            }
            pkt = pkt->next;
        }
    }
    if (o->shadow != 0) {
        shadow_RenderVolume(o);
    }
}

void reg_dispPoint(char *node, float alpha, int idx, int flag)
{
    float fv[4];
    int iv[4];
    int iv2[4];
    Qw128 v;
    int pri;
    int on;
    int z;

    on = 0;
    pri = (*(long long *)(node + 0xB8) & 0x1800) != 0 ? 2 : 0;
    if (alpha != 0.0f || (*(long long *)(node + 0xB8) & 0x1800) != 0) {
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
        *(unsigned int *)(c + 8) = 0x11000000;
        PacketBufferStruct.gif.c = c + 0xC;
        PacketBufferStruct.end.c = c + 0x10;
        PacketBufferStruct.ptr.c = c + 0x18;
        ((RegPkWord *)(c + 0x18))->d = 0xE;
        PacketBufferStruct.ptr.c = c + 0x20;
    }
    _RotTransPersCurrentMatrix(fv, node);
    _FTOI4Vector(iv, fv);
    if (idx == -1) {
        if (flag != 0) {
            _CopyIVector(iv2, iv);
        } else {
            if (systemStatus[5] == 0) {
                v = *(Qw128 *)(node + 0x10);
            } else {
                v = *(Qw128 *)(node + 0x20);
            }
            *(Qw128 *)iv2 = v;
        }
        if (systemStatus[5] == 0) {
            *(Qw128 *)(node + 0x20) = *(Qw128 *)(node + 0x10);
            *(Qw128 *)(node + 0x10) = *(Qw128 *)iv;
        }
    } else {
        if (flag != 0) {
            _CopyIVector(iv2, iv);
        } else {
            if (systemStatus[5] == 0) {
                _CopyIVector(iv2, node + (idx * 0x10 + 0x50));
            } else {
                _CopyIVector(iv2, node + (idx * 0x10 + 0x80));
            }
        }
        if (systemStatus[5] == 0) {
            _CopyIVector(node + (idx * 0x10 + 0x80), node + (idx * 0x10 + 0x50));
            _CopyIVector(node + (idx * 0x10 + 0x50), iv);
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
        *PacketBufferStruct.ptr.d++ = (long long)*(unsigned char *)(node + 0xB0) |
                                      ((long long)*(unsigned char *)(node + 0xB1) << 8) |
                                      ((long long)*(unsigned char *)(node + 0xB2) << 16) |
                                      ((long long)*(unsigned char *)(node + 0xB3) << 24) |
                                      (0x3F800000LL << 32);
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

            ((RegPkWord *)PacketBufferStruct.end.c)->d =
                (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c -
                                               PacketBufferStruct.end.c) >>
                                4) -
                               1) |
                0x1000000000008000LL;
            ((RegPkWord *)PacketBufferStruct.gif.c)->w[0] =
                (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
                0x6C008000;
            p = PacketBufferStruct.ptr.c;
            ((RegPkWord *)p)->w[0] = 0x15000000;
            p += 4;
            PacketBufferStruct.ptr.c = p;
            ((RegPkWord *)p)->w[0] = 0;
            PacketBufferStruct.ptr.c = p + 4;
            ((RegPkWord *)(p + 4))->w[0] = 0;
            PacketBufferStruct.ptr.c = p + 8;
            ((RegPkWord *)(p + 8))->w[0] = 0;
            PacketBufferStruct.ptr.c = p + 0xC;
            ((RegPkWord *)PacketBufferStruct.tail.c)->d =
                (unsigned int)((((unsigned int)(PacketBufferStruct.ptr.c -
                                                PacketBufferStruct.tail.c) >>
                                 4) -
                                1) |
                               0x10000000);
            q = PacketBufferStruct.ptr.c;
            PacketBufferStruct.tail.c = q;
            ((RegPkWord *)q)->d = 0x60000000;
            PacketBufferStruct.ptr.c = q + 8;
            ((RegPkWord *)(q + 8))->w[0] = 0;
            PacketBufferStruct.ptr.c = q + 0xC;
            ((RegPkWord *)(q + 8))->w[1] = 0;
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

void reg_dispLine(char *node, float alpha)
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

    h = *(long long *)(node + 0xB8);
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
        long long f = *(long long *)(node + 0xB8);

        texturetranssize += tex_TransTexture((unsigned short)f << 21 >> 21, pri);
    }
    {
        char *c = PacketBufferStruct.ptr.c;

        PacketBufferStruct.gif.c = 0;
        PacketBufferStruct.end.c = 0;
        PacketBufferStruct.dma.c = c;
        PacketBufferStruct.tail.c = c;
        PacketBufferStruct.ptr.c = c + 8;
        *(unsigned int *)(c + 8) = 0x11000000;
        PacketBufferStruct.gif.c = c + 0xC;
        PacketBufferStruct.end.c = c + 0x10;
        PacketBufferStruct.ptr.c = c + 0x18;
        ((RegPkWord *)(c + 0x18))->d = 0xE;
        PacketBufferStruct.ptr.c = c + 0x20;
    }
    _RotTransPersCurrentMatrix(fv0, node);
    _RotTransPersCurrentMatrix(fv1, node + 0x10);
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
        *PacketBufferStruct.ptr.d++ = (long long)*(unsigned char *)(node + 0xB0) |
                                      ((long long)*(unsigned char *)(node + 0xB1) << 8) |
                                      ((long long)*(unsigned char *)(node + 0xB2) << 16) |
                                      ((long long)*(unsigned char *)(node + 0xB3) << 24) |
                                      (0x3F800000LL << 32);
        *PacketBufferStruct.ptr.d++ = 1;
        if (hastex != 0) {
            RegFloatBits u;
            RegFloatBits v;

            u.f = *(float *)(node + 0x30) / fv0[3];
            v.f = *(float *)(node + 0x34) / fv0[3];
            *PacketBufferStruct.ptr.d++ = (long long)u.u | ((long long)v.u << 32);
            *PacketBufferStruct.ptr.d++ = 2;
        }
        *PacketBufferStruct.ptr.d++ =
            (long long)iv0[0] | ((long long)iv0[1] << 16) | ((long long)iv0[2] << 32);
        *PacketBufferStruct.ptr.d++ = 5;
        *PacketBufferStruct.ptr.d++ = (long long)*(unsigned char *)(node + 0xB4) |
                                      ((long long)*(unsigned char *)(node + 0xB5) << 8) |
                                      ((long long)*(unsigned char *)(node + 0xB6) << 16) |
                                      ((long long)*(unsigned char *)(node + 0xB7) << 24) |
                                      (0x3F800000LL << 32);
        *PacketBufferStruct.ptr.d++ = 1;
        if (hastex != 0) {
            RegFloatBits u;
            RegFloatBits v;

            u.f = *(float *)(node + 0x40) / fv1[3];
            v.f = *(float *)(node + 0x44) / fv1[3];
            *PacketBufferStruct.ptr.d++ = (long long)u.u | ((long long)v.u << 32);
            *PacketBufferStruct.ptr.d++ = 2;
        }
        *PacketBufferStruct.ptr.d++ =
            (long long)iv1[0] | ((long long)iv1[1] << 16) | ((long long)iv1[2] << 32);
        *PacketBufferStruct.ptr.d++ = 5;
        ((RegPkWord *)PacketBufferStruct.end.c)->d =
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >>
                            4) -
                           1) |
            0x1000000000008000LL;
        ((RegPkWord *)PacketBufferStruct.gif.c)->w[0] =
            (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
            0x6C008000;
        p = PacketBufferStruct.ptr.c;
        ((RegPkWord *)p)->w[0] = 0x15000000;
        p += 4;
        PacketBufferStruct.ptr.c = p;
        ((RegPkWord *)p)->w[0] = 0;
        PacketBufferStruct.ptr.c = p + 4;
        ((RegPkWord *)(p + 4))->w[0] = 0;
        PacketBufferStruct.ptr.c = p + 8;
        ((RegPkWord *)(p + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = p + 0xC;
        ((RegPkWord *)PacketBufferStruct.tail.c)->d =
            (unsigned int)((((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.tail.c) >>
                             4) -
                            1) |
                           0x10000000);
        q = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = q;
        ((RegPkWord *)q)->d = 0x60000000;
        PacketBufferStruct.ptr.c = q + 8;
        ((RegPkWord *)(q + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = q + 0xC;
        ((RegPkWord *)(q + 8))->w[1] = 0;
        PacketBufferStruct.ptr.c = q + 0x10;
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
}

void reg_dispPointLineObj(Sub15C *o)
{
    PObjModel *mdl;
    char *grp;
    char *hdr;
    char *node;
    struct DObjNode *w;
    long long h;
    float alpha;
    int idx;
    int flag;
    int i;

    mdl = o->model;
    grp = mdl->groups;
    hdr = o->lineHdr;
    if (hdr != 0) {
        idx = *(unsigned short *)(hdr + 2) % 3;
    } else {
        idx = -1;
    }
    flag = 0;
    if (hdr != 0) {
        flag = ((int)(*(long long *)hdr >> 14)) & 1;
    }
    if (currentScreenWidth != 0 || GlobalTimer != 0) {
        flag = 1;
    }
    for (i = 0; i < *(int *)((char *)o + 8); i++) {
        w = (struct DObjNode *)(i * 80 + (int)o->nodes);
        node = *(char **)(grp + 8);
        alpha = 1.0f - (1.0f - w->fade) * w->alpha;
        if (!flag && (alpha < 0.0f ? -alpha : alpha) == 1.0f) {
            continue;
        }
        _SetCurrentMatrix((char *)o->nodeMtx + i * 64);
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

void reg_DispAccessoryWithShadow(Sub15C *o, Sub15C *src)
{
    char *reg_setNMatrixPacketNoLightCalc(Sub15C * o, Sub15C * src, int idx)
    {
        void setMatrix(void)
        {
            char *c;
            char *m;

            c = PacketBufferStruct.ptr.c;
            PacketBufferStruct.tail.c = c;
            ((RegPkWord *)c)->d = 0x1000000D;
            PacketBufferStruct.ptr.c = c + 8;
            ((RegPkWord *)(c + 8))->w[0] = 0;
            PacketBufferStruct.ptr.c = c + 0xC;
            PacketBufferStruct.gif.c = c + 0xC;
            ((RegPkWord *)(c + 8))->w[1] = 0x6C0C8000;
            PacketBufferStruct.ptr.c = c + 0x50;
            _CopyMatrix(c + 0x10, matrixptr + 0x140);
            _MulMatrix(PacketBufferStruct.ptr.c, matrixptr + 0x200, matrixptr + 0x40);
            PacketBufferStruct.ptr.c = PacketBufferStruct.ptr.c + 0x40;
            _MulMatrix(PacketBufferStruct.ptr.c, matrixptr + 0x80, matrixptr + 0x40);
            m = PacketBufferStruct.ptr.c;
            PacketBufferStruct.ptr.c = m + 0x40;
            ((RegPkWord *)(m + 0x40))->w[0] = 0x15000010;
            PacketBufferStruct.ptr.c = m + 0x44;
            ((RegPkWord *)(m + 0x40))->w[1] = 0;
            PacketBufferStruct.ptr.c = m + 0x48;
            ((RegPkWord *)(m + 0x48))->d = 0;
            PacketBufferStruct.ptr.c = m + 0x50;
        }
        void setLight(void)
        {
            char *c;
            char *m;
            char *n;

            c = PacketBufferStruct.ptr.c;
            PacketBufferStruct.tail.c = c;
            ((RegPkWord *)c)->d = 0x10000009;
            PacketBufferStruct.ptr.c = c + 8;
            ((RegPkWord *)(c + 8))->w[0] = 0;
            PacketBufferStruct.ptr.c = c + 0xC;
            PacketBufferStruct.gif.c = c + 0xC;
            ((RegPkWord *)(c + 8))->w[1] = 0x6C088000;
            PacketBufferStruct.ptr.c = c + 0x10;
            _GetCurrentMatrix(c + 0x10);
            m = PacketBufferStruct.ptr.c;
            PacketBufferStruct.ptr.c = m + 0x80;
            _CopyMatrix(m + 0x40, (char *)o->lightMtx + 64);
            n = PacketBufferStruct.ptr.c;
            ((RegPkWord *)n)->w[0] = 0x15000012;
            n += 4;
            PacketBufferStruct.ptr.c = n;
            ((RegPkWord *)n)->w[0] = 0;
            PacketBufferStruct.ptr.c = n + 4;
            ((RegPkWord *)(n + 4))->d = 0;
            PacketBufferStruct.ptr.c = n + 0xC;
        }
        char *pkt;
        char *box;
        struct DObjNode *scl;
        int mode;

        scl = (struct DObjNode *)(idx * 80 + (int)o->nodes);
        mode = o->lightMtx->mode;
        if (scl->scale[0] != 1.0f || scl->scale[1] != 1.0f || scl->scale[2] != 1.0f) {
            _InitCurrentMatrix();
            _SetCurrentMatrix((char *)o->nodeMtx + idx * 64);
            _ScaleCurrentMatrix(o->nodes[idx].scale[0], o->nodes[idx].scale[1],
                                o->nodes[idx].scale[2]);
            _GetCurrentMatrix(matrixptr + 0x40);
        } else {
            _CopyMatrix(matrixptr + 0x40, (char *)o->nodeMtx + idx * 64);
        }
        _MulMatrix(matrixptr + 0x300, matrixptr + 0x280, matrixptr + 0x40);
        _MulMatrix(matrixptr + 0x140, matrixptr + 0x100, matrixptr + 0x40);
        box = (char *)o->model->box;
        _SetCurrentMatrix(matrixptr + 0x300);
        if (gsb_ClipBox(box) == 0) {
            return 0;
        }
        pkt = PacketBufferStruct.ptr.c;
        PacketBufferStruct.dma.c = pkt;
        PacketBufferStruct.tail.c = 0;
        PacketBufferStruct.gif.c = 0;
        PacketBufferStruct.end.c = 0;
        setMatrix();
        if (mode != 0 && mode != 3) {
            o->model->shadowLength = src->model->shadowLength;
            _CopyVector((char *)o + 0x860, (char *)src + 0x860);
            _CopyMatrix((char *)o->lightMtx, (char *)src->lightMtx);
            _CopyMatrix((char *)o->lightMtx + 64, (char *)src->lightMtx + 64);
            _SetCurrentMatrix(matrixptr + 0x40);
            _ClearTransCurrentMatrix();
            _MulCurrentMatrixL((char *)o->lightMtx);
            setLight();
        }
        {
            char *c = PacketBufferStruct.ptr.c;

            PacketBufferStruct.tail.c = c;
            ((RegPkWord *)c)->d = 0x60000000;
            PacketBufferStruct.ptr.c = c + 8;
            ((RegPkWord *)(c + 8))->w[0] = 0;
            PacketBufferStruct.ptr.c = c + 0xC;
            ((RegPkWord *)(c + 8))->w[1] = 0;
            PacketBufferStruct.ptr.c = c + 0x10;
        }
        return pkt;
    }
    PObjModel *mdl;
    char *grp;
    char *pk;
    PacHeader *pkt;
    char *box;
    int i;
    int j;
    int r;
    int pri;
    int mode;

    mdl = o->model;
    grp = mdl->groups;
    reg_transMicroCode(o, 0x3B5);
    pk = reg_setNMatrixPacketNoLightCalc(o, src, 0);
    if (pk != 0) {
        int prilist = 0x3B5;

        for (i = 0; i < 13; i++) {
            if ((prilist >> i) & 1) {
                dl_SetDLPriority(i);
                dl_OpenDma(5, pk, 0);
                dl_CloseDma();
            }
        }
        for (j = 0; j < mdl->partCount; j++, grp += 0x30) {
            box = (char *)(j * 128 + (int)o->model->boxes);
            _SetCurrentMatrix(matrixptr + 0x300);
            if (gsb_ClipBox(box) != 0) {
                pkt = *(PacHeader **)(grp + 8);
                while (pkt != 0) {
                    r = reg_clipPacketBoundingBox(pkt);
                    if (r != 0) {
                        pri = regMaterialDLPri((int *)grp, pkt->mat, tex_GetTexExtData(pkt->tex),
                                               0.0f);
                        regTransTexturePacket(pkt->tex, pri);
                        reg_transMaterialPacket(pkt, (int *)grp);
                        reg_chooseMicroCode((char *)(*(int *)grp + pkt->mat * 0x70), r, pri);
                        dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                        dl_CloseDma();
                        if (o->lightMtx->mode == 2) {
                            if (pkt->tex1 != -1) {
                                reg_dispSpecular(pkt, r, 0);
                            }
                        }
                        mode = o->lightMtx->mode;
                        if (pkt->tex2 != -1) {
                            if (mode == 0) {
                                debug_StdPrintfDummy("光源オフでリフレクションを表示.\n");
                                mc_TransMicroCode(2, 0x10);
                            }
                            dl_SetDLPriority(4);
                            regTransTexturePacket(pkt->tex2, 4);
                            dl_OpenDma(2, regReflectionPacket, 6);
                            dl_CloseDma();
                            reg_chooseReflectionMicroCode(0, r, 4);
                            dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                            dl_CloseDma();
                            if (mode == 0) {
                                mc_TransMicroCode(1, 0x10);
                            }
                        }
                    }
                    pkt = pkt->next;
                }
            }
        }
        if (o->shadow != 0) {
            shadow_RenderVolume(o);
        }
    }
}

void reg_RenderReflection(Sub15C *o, int pri)
{
    PObjModel *mdl;
    char *grp;
    PacHeader *pkt;
    char *pk;
    int i;
    int r;

    mdl = o->model;
    grp = mdl->groups;
    dl_SetDLPriority(pri);
    reg_transMicroCode(o, 1 << pri);
    pk = reg_setNMatrixPacket(o, 0);
    if (pk == 0) {
        return;
    }
    dl_SetDLPriority(pri);
    dl_OpenDma(5, pk, 0);
    dl_CloseDma();
    for (i = 0; i < mdl->partCount; i++) {
        pkt = *(PacHeader **)(grp + 8);
        while (pkt != 0) {
            r = reg_clipPacketBoundingBox(pkt);
            if (r != 0) {
                regTransTexturePacket(pkt->tex, pri);
                reg_transMaterialPacket(pkt, (int *)grp);
                reg_chooseMicroCode((char *)(*(int *)grp + pkt->mat * 0x70), r, pri);
                dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                dl_CloseDma();
            }
            pkt = pkt->next;
        }
        grp += 0x30;
    }
}

/* The sixteen bytes that close the enemy matrix packet: the VIF MSCAL 0x10
   code and three zero words, copied as one quadword. */
static const sceVu0IVECTOR regEnemyEndTag = {0x15000010, 0, 0, 0}; /* derived name */

void reg_DispEnemy(void *sub)
{
    Sub15C *o = sub;
    PObjModel *mdl;
    char *grp;
    PacHeader *pkt;
    float alpha;
    int i;
    int pri;

    void reg_setEMatrixPacket(Sub15C * o, int prilist, float alpha)
    {
        int i;

        inline void pack(void)
        {
            char *c;
            char *m;
            int n;

            /* the object's matrix count through the object record, the view
             * reg_setMMatrixPacket takes of o */
            n = o->nodeNum * 4;
            c = PacketBufferStruct.ptr.c;
            PacketBufferStruct.tail.c = c;
            *(long long *)c = n | 0x10000002;
            PacketBufferStruct.ptr.c = c + 8;
            *(int *)(c + 8) = 0x11000000;
            PacketBufferStruct.ptr.c = c + 0xC;
            PacketBufferStruct.gif.c = c + 0xC;
            *(int *)(c + 0xC) = ((n + 1) << 16) | 0x6C008000;
            PacketBufferStruct.ptr.c = c + 0x10;
            *(int *)(c + 0x10) = n + 1;
            PacketBufferStruct.ptr.c = c + 0x14;
            *(int *)(c + 0x14) = 0;
            PacketBufferStruct.ptr.c = c + 0x18;
            *(int *)(c + 0x18) = 0;
            PacketBufferStruct.ptr.c = c + 0x1C;
            *(float *)(c + 0x1C) = alpha;
            PacketBufferStruct.ptr.c = c + 0x20;
            for (i = 0; i < o->nodeNum; i++) {
                _MulMatrix(PacketBufferStruct.ptr.c, (char *)o->nodeMtx + i * 64,
                           o->clusterMtx + i * 64);
                PacketBufferStruct.ptr.c = PacketBufferStruct.ptr.c + 0x40;
            }
            m = PacketBufferStruct.ptr.c;
            *(Qw128 *)m = *(Qw128 *)&regEnemyEndTag;
            m += 0x10;
            PacketBufferStruct.ptr.c = m;
        }

        PacketBufferStruct.dma.c = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = 0;
        PacketBufferStruct.gif.c = 0;
        PacketBufferStruct.end.c = 0;
        pack();
        {
            char *c = PacketBufferStruct.ptr.c;

            PacketBufferStruct.tail.c = c;
            *(long long *)c = 0x60000000;
            PacketBufferStruct.ptr.c = c + 8;
            *(int *)(c + 8) = 0;
            PacketBufferStruct.ptr.c = c + 0xC;
            *(int *)(c + 0xC) = 0;
            PacketBufferStruct.ptr.c = c + 0x10;
        }
        for (i = 0; i < 13; i++) {
            if ((prilist >> i) & 1) {
                dl_SetDLPriority(i);
                dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
                dl_CloseDma();
            }
        }
    }

    mdl = o->model;
    grp = mdl->groups;
    alpha = 1.0f - o->nodes->fade;
    reg_transMicroCode(o, 0x3A0);
    reg_setEMatrixPacket(o, 0x3A0, alpha);
    if ((alpha < 0.0f ? -alpha : alpha) == 0.0f) {
        goto done;
    }
    {
        for (i = 0; i < mdl->partCount; i++, grp += 0x30) {
            if (mdl->parts[i].morphCount != 0) {
                if (*(char **)(grp + 0xC) != 0) {
                    if (buffer_ID != 0) {
                        pkt = *(PacHeader **)(grp + 8);
                    } else {
                        pkt = *(PacHeader **)(grp + 0xC);
                    }
                    reg_setShape(o, i, buffer_ID == 0, pkt,
                                 (char *)(*(int *)grp + pkt->mat * 0x70));
                } else {
                    pkt = *(PacHeader **)(grp + 8);
                }
            } else {
                pkt = *(PacHeader **)(grp + 8);
            }
            while (pkt != 0) {
                pri = regMaterialDLPri((int *)grp, pkt->mat, tex_GetTexExtData(pkt->tex), 0.0f);
                regTransTexturePacket(pkt->tex, pri);
                reg_transMaterialPacket(pkt, (int *)grp);
                reg_chooseMicroCode((char *)(*(int *)grp + pkt->mat * 0x70), 0, pri);
                dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                dl_CloseDma();
                pkt = pkt->next;
            }
        }
    }
done:
    if (o->shadow != 0) {
        shadow_RenderVolume(o);
    }
}

void reg_DispMultiPri(Sub15C *o, int pri)
{
    PObjModel *mdl;
    char *grp;
    PacHeader *pkt;
    PacHeader *node;
    char *pk;
    struct DObjNode *w;
    float alpha;
    int i;
    int j;
    int r;
    int dis;
    int fade;
    int mode;
    int prilist;

    mdl = o->model;
    grp = mdl->groups;
    reg_transMicroCode(o, 1 << pri);
    for (i = 0; i < *(int *)((char *)o + 8); i++) {
        w = (struct DObjNode *)(i * 80 + (int)o->nodes);
        alpha = 1.0f - (1.0f - w->fade) * w->alpha;
        if ((alpha < 0.0f ? -alpha : alpha) == 1.0f) {
            continue;
        }
        pk = reg_setMMatrixPacket(o, i);
        if (pk == 0) {
            return;
        }
        prilist = 1 << pri;
        for (j = 0; j < 13; j++) {
            if ((prilist >> j) & 1) {
                dl_SetDLPriority(j);
                dl_OpenDma(5, pk, 0);
                dl_CloseDma();
            }
        }
        if (mdl->parts[i].morphCount != 0 && (node = *(PacHeader **)(grp + 0xC)) != 0) {
            pkt = node;
            if (buffer_ID != 0) {
                pkt = *(PacHeader **)(grp + 8);
            }
            reg_setShape(o, i, buffer_ID == 0, pkt, (char *)(*(int *)grp + pkt->mat * 0x70));
        } else {
            pkt = *(PacHeader **)(grp + 8);
        }
        while (pkt != 0) {
            r = reg_clipPacketBoundingBox(pkt);
            if (r != 0) {
                fade = 0;
                if ((o->nodes[i].flags.ll & 1) == 1) {
                    if (alpha != 0.0f) {
                        fade = 1;
                    }
                }
                regTransTexturePacket(pkt->tex, pri);
                reg_transMaterialPacket(pkt, (int *)grp);
                dis = 0;
                if (fade != 0) {
                    dis = reg_setDissolve(alpha, pri);
                }
                if (dis != -1) {
                    reg_chooseMicroCode((char *)(*(int *)grp + pkt->mat * 0x70), r, pri);
                    dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                    dl_CloseDma();
                    if (o->lightMtx->mode == 2) {
                        if (pkt->tex1 != -1) {
                            reg_dispSpecular(pkt, r, 0);
                        }
                    }
                    mode = o->lightMtx->mode;
                    if (pkt->tex2 != -1) {
                        if (mode == 0) {
                            debug_StdPrintfDummy("光源オフでリフレクションを表示.\n");
                            mc_TransMicroCode(2, 0x10);
                        }
                        dl_SetDLPriority(4);
                        regTransTexturePacket(pkt->tex2, 4);
                        dl_OpenDma(2, regReflectionPacket, 6);
                        dl_CloseDma();
                        reg_chooseReflectionMicroCode(0, r, 4);
                        dl_OpenDma(2, pkt->data, (pkt->size & 0xFFFFFF) >> 4);
                        dl_CloseDma();
                        if (mode == 0) {
                            mc_TransMicroCode(1, 0x10);
                        }
                    }
                }
                if (dis == 1) {
                    reg_resetDissolve(pri);
                }
            }
            pkt = pkt->next;
        }
    }
}

void reg_DispObj(Sub15C *o)
{
    if (o->dispType == 2) {
        unsigned short type = (unsigned long long)o->model->mode.bits >> 16;

        if ((type & 3) == 2) {
            reg_dispPointLineObj(o);
        } else {
            reg_dispMObj(o);
        }
    } else {
        unsigned short type = (unsigned long long)o->model->mode.bits >> 16;

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
    if (tex >= 0) {
        texturetranssize += tex_TransTexture(tex, pri);
    }
}

void reg_Init(void)
{
    scissorSw = 0;
}

int reg_GetShinePri(int a0)
{
    switch (a0) {
    case 1:
        return 7;
    case 2:
        return 8;
    case 3:
        return 9;
    }
    return 7;
}
