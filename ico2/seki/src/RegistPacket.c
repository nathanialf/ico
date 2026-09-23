#include "common.h"
#include "typedef.h"
#include "RegistPacket.h"
#include "debug.h"
#include "DisplayList.h"
#include "GsBase.h"
#include "Light.h"
#include "Shadow.h"
#include "Texture.h"
#include "lineManager.h"
#include "matrixDrive.h"

extern char D_0054FA50[];
extern char D_0054FA80[];
extern char D_0054FA98[];
extern char D_0063A170[];
/* kept local: this TU's uses of _CopyVector do not fit the prototype in Matrix.h */
extern void _CopyVector(void *dst, void *src);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

void reg_setShape(char *o, int idx, int flag, char *pkt, char *mat)
{
    float vec[4];
    char *mdl;
    char *s;
    char *p;
    char *m;
    char *v;
    char *pk;
    char *t;
    int base;
    int i;
    int n;

    mdl = *(char **)(o + 0x854);
    s = *(char **)(mdl + 0x40) + idx * 0x180;
    {
        char *dst = *(char **)(s + 0x90);

        for (i = 0; i < *(unsigned int *)(s + 0x94); i++) {
            _CopyVector(dst + i * 0x10, *(char **)(s + 0x174) + i * 0x10);
        }
    }
    {
        char *dst = *(char **)(s + 0xA0);

        if (dst != 0) {
            for (i = 0; i < *(unsigned int *)(s + 0xA4); i++) {
                _CopyVector(dst + i * 0x10, *(char **)(s + 0x178) + i * 0x10);
            }
        }
    }
    for (i = 0; i < *(unsigned int *)(s + 0x124); i++) {
        if (*(float *)(i * 4 + *(int *)(o + 0x838)) != 0.0f) {
            m = *(char **)(i * 4 + *(int *)(s + 0x120));
            if (m != 0) {
                while (*(int *)(m + 0x10) != -1) {
                    _ScaleVectorXYZ(vec, m, *(float *)(i * 4 + *(int *)(o + 0x838)));
                    if (*(float *)(m + 0xC) == 1.0f) {
                        if (*(unsigned int *)(m + 0x10) >= *(unsigned int *)(s + 0x94)) {
                            debug_StdPrintfDummy(D_0054FA50, *(unsigned int *)(m + 0x10),
                                                 *(unsigned int *)(s + 0x94));
                            debug_assert(D_0054FA80, 635);
                            __assert(D_0054FA80, 635, D_0063A170);
                        }
                        t = *(char **)(s + 0x90);
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
                        if (*(unsigned int *)(m + 0x10) >= *(unsigned int *)(s + 0xA4)) {
                            debug_StdPrintfDummy(D_0054FA98, *(unsigned int *)(m + 0x10),
                                                 *(unsigned int *)(s + 0xA4));
                            debug_assert(D_0054FA80, 642);
                            __assert(D_0054FA80, 642, D_0063A170);
                        }
                        t = *(char **)(s + 0xA0);
                        t += *(int *)(m + 0x10) * 0x10;
                        _AddVectorXYZ(t, t, vec);
                    } else {
                        debug_assert(D_0054FA80, 647);
                        __assert(D_0054FA80, 647, D_0063A170);
                    }
                nextbone:
                    m += 0x20;
                }
            }
        }
    }
    for (i = 0; i < *(unsigned int *)(s + 0x104); i++) {
        v = *(char **)(i * 4 + *(int *)(s + 0x100));
        while (*(short *)v != -1) {
            pk = pkt;
            n = *(short *)v;
            v += 0x10;
            while (pk != 0) {
                if (*(short *)(v + 0xE) == *(short *)(pk + 0x82) &&
                    *(short *)(v + 0xC) == *(short *)(pk + 0x80)) {
                    break;
                }
                pk = *(char **)(pk + 0x94);
            }
            if (pk == 0) {
                break;
            }
            base = *(int *)(pk + 0x98);
            p = (char *)(*(int *)(v - 0xC) + base);
            if (*(int *)(v - 0xC) != 0) {
                if (n != 0) {
                    do {
                        _CopyVector(p, *(char **)(s + 0x90) + *(short *)(v + 4) * 0x10);
                        p += 0x10;
                        if ((((int)(*(long long *)(mat + 0x60) >> 5)) & 3) == 0) {
                            switch (*(int *)(mat + 0x60) & 1) {
                            case 1:
                                break;
                            default:
                                goto nocopy;
                            }
                        }
                        _CopyVector(p, *(char **)(s + 0xA0) + *(short *)(v + 6) * 0x10);
                        p += 0x10;
                    nocopy:
                        if (*(signed char *)(mdl + 0x2F) != 0) {
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
/* kept local: this TU's uses of _SetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _SetCurrentMatrix(void *mtx);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a, int b, int c);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of _CopyMatrix do not fit the prototype in Matrix.h */
extern void _CopyMatrix(void *dst, void *src);

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

extern int D_0063B184;
extern char D_0054FB40[];

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
        debug_assert(D_0054FA80, 821);
        __assert(D_0054FA80, 821, D_0063A170);
        break;
    }
    if (D_0063B184 & 2) {
        reg_dispBoxLine(pk);
    }
    return ret;
}

/* kept local: this TU's uses of mc_TransMicroCode do not fit the prototype in MicroCode.h */
extern void
mc_TransMicroCode(); /* K&R: called 1-ary here and 2-ary in reg_DispAccessoryWithShadow */

void reg_transMicroCode(char *a0, int mask)
{
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

/* kept local: this TU's uses of mc_SetMicroCode do not fit the prototype in MicroCode.h */
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

/* One 64-bit slot of a DMA/GIF packet: written either as the whole qword
   (DMAtag, GIFtag, A+D data) or as its two 32-bit halves. */
typedef union {
    long long d;
    int w[2];
} RegPkWord;

/* the quadword copy type src/Primitive.c and src/Shadow.c use */
typedef int Qw128 __attribute__((mode(TI)));

/* The display-list packet builder state, the record src/Shadow.c carries as
 * ShadowDpk. RECONSTRUCTION: every packet address (dma, ptr, tail, gif, end)
 * is one pointer union, read and written through its members, so each field
 * access is alias set 0 (c-common.c c_get_alias_set: a reference through a
 * union). WHAT THE BYTES PIN (reg_setEMatrixPacket): its typed packet words
 * keep every ptr store alive through flow's dead-store scan and stay in source
 * order with the ptr, tail and gif stores, while the two parameter homes, which
 * no typed packet word of another type may alias, sink below them (measured:
 * char pointer fields leave the ptr stores dead, 116 of 128 words; char
 * pointer tail and gif sink below the packet; union packet words pin the
 * homes above it). WHAT THEY CANNOT PIN: the member names and
 * types beyond one 64-bit packet pointer and one byte pointer. The matched
 * functions of this TU are byte-identical under either field typing. */
typedef union {
    unsigned long long *d;
    char *c;
} RegPkPtr;

typedef struct {
    int cur;
    int *buf[2];
    RegPkPtr dma;
    RegPkPtr ptr;
    RegPkPtr tail;
    RegPkPtr gif;
    RegPkPtr end;
} RegDpk;

extern RegDpk PacketBufferStruct;
/* kept local: this TU's uses of _InitCurrentMatrix do not fit the prototype in Matrix.h */
extern void _InitCurrentMatrix(void);
/* kept local: this TU's uses of _GetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _GetCurrentMatrix(void *dst);
/* kept local: this TU's uses of _ScaleCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ScaleCurrentMatrix(float x, float y, float z);
/* kept local: this TU's uses of _ClearTransCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ClearTransCurrentMatrix(void);
/* kept local: this TU's uses of _MulCurrentMatrixL do not fit the prototype in Matrix.h */
extern void _MulCurrentMatrixL(void *m);
/* kept local: this TU's uses of _MulMatrix do not fit the prototype in Matrix.h */
extern void _MulMatrix(void *dst, void *a, void *b);

char *reg_setNMatrixPacket(char *o, int idx)
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
        _CopyMatrix(m + 0x40, *(char **)(o + 0x874) + 0x40);
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
        _MulCurrentMatrixL(*(char **)(o + 0x874));
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

/* kept local: this TU's uses of these matrix helpers do not fit the prototypes
   in Matrix.h (two arguments and a float result for _GetLength) */
extern void _UnitMatrix(void *m);
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern float _GetLength(void *a, void *b);
extern void _SetTransCurrentMatrix(void *v);
extern void _TransCurrentMatrix(void *v);
extern void _RotCurrentMatrixZ(int a);

typedef struct {
    float x;
    float y;
    float z;
    float w;
} RegVec;

typedef struct {
    RegVec r[4];
} RegMtx;

char *reg_setMMatrixPacket(char *o, int idx)
{
    RegVec s;
    RegVec v;
    char *pkt;
    char *box;
    char *w;
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
        if ((*(long long *)(*(int *)(o + 0x870) + idx * 0x50 + 0x38) & 6) != 0) {
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
        _CopyMatrix(m + 0x40, *(char **)(o + 0x874) + 0x40);
        n = PacketBufferStruct.ptr.c;
        ((RegPkWord *)n)->w[0] = 0x15000012;
        n += 4;
        PacketBufferStruct.ptr.c = n;
        ((RegPkWord *)n)->w[0] = 0;
        PacketBufferStruct.ptr.c = n + 4;
        ((RegPkWord *)(n + 4))->d = 0;
        PacketBufferStruct.ptr.c = n + 0xC;
    }
    w = (char *)(idx * 0x50 + (int)((Sub15C *)o)->p_870);
    mode = ((LightMatrix *)((Sub15C *)o)->p_874)->mode;
    if ((*(long long *)(w + 0x38) & 2) != 0) {
        RegMtx um;

        _SetCurrentMatrix(*(char **)(o + 0xC) + idx * 0x40);
        _ClearTransCurrentMatrix();
        _UnitMatrix(&um);
        _ApplyCurrentMatrix(&v, &um.r[0]);
        s.x = _GetLength(&v, &um.r[3]);
        _ApplyCurrentMatrix(&v, &um.r[1]);
        s.y = _GetLength(&v, &um.r[3]);
        _ApplyCurrentMatrix(&v, &um.r[2]);
        s.z = _GetLength(&v, &um.r[3]);
        _InitCurrentMatrix();
        if (*(float *)(idx * 0x50 + *(int *)(o + 0x870) + 0x48) < 5.0f) {
            _ScaleVectorXYZ(&s, &s, 5.0f);
            _ScaleCurrentMatrix(s.x, s.y, s.z);
            _ScaleVectorXYZ(&s, (char *)(*(int *)(o + 0x870) + idx * 0x50) + 0x40, 5.0f);
            s.w = 1.0f;
            _SetTransCurrentMatrix(&s);
        } else {
            _ScaleCurrentMatrix(s.x, s.y, s.z);
            _SetTransCurrentMatrix((char *)(*(int *)(o + 0x870) + idx * 0x50) + 0x40);
        }
        _GetCurrentMatrix(matrixptr + 0x180);
        _MulMatrix(matrixptr + 0x140, matrixptr + 0x640, matrixptr + 0x180);
        _MulMatrix(matrixptr + 0x300, matrixptr + 0x680, matrixptr + 0x180);
    } else if ((*(long long *)(w + 0x38) & 4) != 0) {
        RegMtx um2;

        _MulMatrix(matrixptr + 0x180, matrixptr + 0x80, *(char **)(o + 0xC) + idx * 0x40);
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
        _RotCurrentMatrixZ(*(short *)(idx * 0x50 + *(int *)(o + 0x870) + 0x3A));
        _ScaleCurrentMatrix(s.x, s.y, s.z);
        _GetCurrentMatrix(matrixptr + 0x180);
        _MulMatrix(matrixptr + 0x140, matrixptr + 0xC0, matrixptr + 0x180);
        _MulMatrix(matrixptr + 0x300, matrixptr + 0x240, matrixptr + 0x180);
    } else {
        if (*(float *)(w + 0x20) != 1.0f || *(float *)(w + 0x24) != 1.0f ||
            *(float *)(w + 0x28) != 1.0f) {
            _InitCurrentMatrix();
            _SetCurrentMatrix(*(char **)(o + 0xC) + idx * 0x40);
            _ScaleCurrentMatrix(*(float *)(idx * 0x50 + *(int *)(o + 0x870) + 0x20),
                                *(float *)(idx * 0x50 + *(int *)(o + 0x870) + 0x24),
                                *(float *)(idx * 0x50 + *(int *)(o + 0x870) + 0x28));
            _GetCurrentMatrix(matrixptr + 0x40);
        } else {
            _CopyMatrix(matrixptr + 0x40, *(char **)(o + 0xC) + idx * 0x40);
        }
        _MulMatrix(matrixptr + 0x140, matrixptr + 0x100, matrixptr + 0x40);
        _MulMatrix(matrixptr + 0x300, matrixptr + 0x280, matrixptr + 0x40);
    }
    box = *(char **)(o + 0x854) + 0x50;
    _SetCurrentMatrix(matrixptr + 0x300);
    if (gsb_ClipBox(box) == 0) {
        if (*(int *)(o + 0x858) != 0) {
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
        _MulCurrentMatrixL(*(char **)(o + 0x874));
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

extern char D_0054FB58[];

void reg_setCMatrixPacket(char *o, float alpha, int prilist)
{
    int i;
    int haslight;

    inline void pack(void)
    {
        char *c;
        char *m;
        int n;

        n = ((Sub15C *)o)->f_8 * 4;
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
        for (i = 0; i < ((Sub15C *)o)->f_8; i++) {
            _MulMatrix(PacketBufferStruct.ptr.c, *(char **)(o + 0xC) + i * 0x40,
                       *(char **)(o + 0x90) + i * 0x40);
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
        /* the two light matrices go in through the cursor post-increment src/Primitive.c's
         * setLight uses; the listing's line 1217 has no instruction, the c + 0x10 store
         * being dead under the first increment's store */
        PacketBufferStruct.ptr.c = c + 0x10;
        _CopyMatrix(((float (*)[16])PacketBufferStruct.ptr.c)++, *(char **)(o + 0x874));
        _CopyMatrix(((float (*)[16])PacketBufferStruct.ptr.c)++, *(char **)(o + 0x874) + 0x40);
        n = PacketBufferStruct.ptr.c;
        *(int *)n = 0x15000012;
        n += 4;
        PacketBufferStruct.ptr.c = n;
        *(int *)n = 0;
        PacketBufferStruct.ptr.c = n + 4;
        *(long long *)(n + 4) = 0;
        PacketBufferStruct.ptr.c = n + 0xC;
    }

    haslight = ((LightMatrix *)((Sub15C *)o)->p_874)->mode != 0;
    light_MakeLightMatrix(o, 0);
    PacketBufferStruct.dma.c = PacketBufferStruct.ptr.c;
    PacketBufferStruct.tail.c = 0;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.end.c = 0;
    pack();
    if (haslight) {
        light();
    } else {
        debug_StdPrintfDummy(D_0054FB58, *(char **)(o + 0x854));
        debug_assert(D_0054FA80, 1238);
        __assert(D_0054FA80, 1238, D_0063A170);
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

/* This helper has NO NAME IN THE DISC MAPS, so it keeps the placeholder on
   purpose.  The retail object out-of-lines it and tail-calls it from all six
   reg_disp* functions; the January listing inlines the same block at every site
   (it cites RegistPacket.c lines 1290-1313 inside reg_dispCObj) and so gives it
   no label, and MAIN.MAP has no global for it.  A helper the map does not export
   is a file static, which is what it is here.  Every other function of the TU
   aligns one-to-one with the listing around it, between reg_setCMatrixPacket and
   reg_transMaterialPacket. */
static void func_00121428(char *a0, int a1, int a2)
{
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
    short idx = self[0x80 / 2];
    if (idx != -1) {
        int v = *p + idx * 0x70;
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

extern char D_0054FC60[];

void reg_resetDissolve(int a0)
{
    dl_SetDLPriority(a0);
    dl_OpenDma(2, D_0054FC60, 4);
    dl_CloseDma();
}

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines reg_TransTexturePacket (line 1259) into reg_RenderReflection
   and reg_DispMultiPri, so it is `inline` in the dev's TU; while this tail
   still has asm members a deferred inline would land at the object end instead
   of at its ROM slot, so the public body stays a plain definition there and the
   C callers that inline it call this static stand-in.
   Collapses to one `inline` definition at layout. */
static inline void regTransTexturePacket(int tex, int pri)
{
    if (tex >= 0) {
        D_0063B124 += tex_TransTexture(tex, pri);
    }
}

/* ===== su-a sweep begin ===== */

static void func_00121428(char *pkt, int r, int c);
extern char D_0054FBD0[];
extern char D_0054FC30[];
extern int buffer_ID;
extern int D_0063B1AC;

/* INTERIM, same rule as regTransTexturePacket above: reg_GetShinePri
   (listing line 705) is `inline` in the dev's TU -- its body is inlined into
   the whole reg_disp*Obj / reg_Disp* family -- but it also owns a ROM slot,
   so the public body stays a plain definition at that slot and the C callers
   that inline it call this static stand-in. */
static inline int regGetShinePri(int a0)
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

/* Inline-only helper (listing lines 727-752, no MAIN.MAP symbol): pick the
   display-list priority for one material and install it. */
static inline int regMaterialDLPri(int *grp, int nodeIdx, int *ext, float fade)
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

void reg_dispNObj(char *o)
{
    char *mdl;
    char *grp;
    char *pk;
    char *pkt;
    char *box;
    int i;
    int j;
    int r;
    int pri;
    int mode;

    mdl = *(char **)(o + 0x854);
    grp = *(char **)(mdl + 0x48);
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
        for (j = 0; j < *(signed char *)(mdl + 0x2E); j++, grp += 0x30) {
            box = (char *)(j * 0x80 + *(int *)(*(char **)(o + 0x854) + 0x44));
            _SetCurrentMatrix(matrixptr + 0x300);
            if (gsb_ClipBox(box) != 0) {
                pkt = *(char **)(grp + 8);
                while (pkt != 0) {
                    r = reg_clipPacketBoundingBox(pkt);
                    if (r != 0) {
                        pri = regMaterialDLPri((int *)grp, *(short *)(pkt + 0x80),
                                               tex_GetTexExtData(*(short *)(pkt + 0x84)), 0.0f);
                        regTransTexturePacket(*(short *)(pkt + 0x84), pri);
                        reg_transMaterialPacket((short *)pkt, (int *)grp);
                        reg_chooseMicroCode((char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70),
                                            r, pri);
                        dl_OpenDma(2, *(char **)(pkt + 0x98),
                                   (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                        dl_CloseDma();
                        if (*(int *)(*(char **)(o + 0x874) + 0xF0) == 2) {
                            if (*(short *)(pkt + 0x86) != -1) {
                                func_00121428(pkt, r, 0);
                            }
                        }
                        mode = *(int *)(*(char **)(o + 0x874) + 0xF0);
                        if (*(short *)(pkt + 0x88) != -1) {
                            if (mode == 0) {
                                debug_StdPrintfDummy(D_0054FC30);
                                mc_TransMicroCode(2, 0x10);
                            }
                            dl_SetDLPriority(4);
                            regTransTexturePacket(*(short *)(pkt + 0x88), 4);
                            dl_OpenDma(2, D_0054FBD0, 6);
                            dl_CloseDma();
                            reg_chooseReflectionMicroCode(0, r, 4);
                            dl_OpenDma(2, *(char **)(pkt + 0x98),
                                       (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                            dl_CloseDma();
                            if (mode == 0) {
                                mc_TransMicroCode(1, 0x10);
                            }
                        }
                    }
                    pkt = *(char **)(pkt + 0x94);
                }
            }
        }
    }
    if (*(int *)(o + 0x858) != 0) {
        shadow_RenderVolume(o);
    }
}

void reg_dispMObj(char *o)
{
    char *mdl;
    char *grp;
    char *pkt;
    char *pk;
    float *w;
    float alpha;
    int i;
    int j;
    int r;
    int dis;
    int fade;
    int pri;
    int mode;
    int prilist;

    mdl = *(char **)(o + 0x854);
    grp = *(char **)(mdl + 0x48);
    reg_transMicroCode(o, 0x3B5);
    for (i = 0; i < *(int *)(o + 8); i++) {
        w = (float *)(i * 0x50 + *(int *)(o + 0x870));
        alpha = 1.0f - (1.0f - w[12]) * w[13];
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
            if (*(int *)(i * 0x180 + *(int *)(mdl + 0x40) + 0x124) != 0) {
                if (*(char **)(grp + 0xC) != 0) {
                    if (buffer_ID != 0) {
                        pkt = *(char **)(grp + 8);
                    } else {
                        pkt = *(char **)(grp + 0xC);
                    }
                    reg_setShape(o, i, buffer_ID == 0, pkt,
                                 (char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70));
                } else {
                    pkt = *(char **)(grp + 8);
                }
            } else {
                pkt = *(char **)(grp + 8);
            }
            while (pkt != 0) {
                r = reg_clipPacketBoundingBox(pkt);
                if (r != 0) {
                    fade = 0;
                    if ((*(long long *)(i * 0x50 + *(int *)(o + 0x870) + 0x38) & 1) == 1) {
                        if (alpha != 0.0f) {
                            fade = 1;
                        }
                    }
                    pri = regMaterialDLPri((int *)grp, *(short *)(pkt + 0x80),
                                           tex_GetTexExtData(*(short *)(pkt + 0x84)), fade);
                    regTransTexturePacket(*(short *)(pkt + 0x84), pri);
                    reg_transMaterialPacket((short *)pkt, (int *)grp);
                    dis = 0;
                    if (fade != 0) {
                        dis = reg_setDissolve(alpha, pri);
                    }
                    if (dis != -1) {
                        reg_chooseMicroCode((char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70),
                                            r, pri);
                        dl_OpenDma(2, *(char **)(pkt + 0x98),
                                   (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                        dl_CloseDma();
                        if (*(int *)(*(char **)(o + 0x874) + 0xF0) == 2) {
                            if (*(short *)(pkt + 0x86) != -1) {
                                func_00121428(pkt, r, 0);
                            }
                        }
                        mode = *(int *)(*(char **)(o + 0x874) + 0xF0);
                        if (*(short *)(pkt + 0x88) != -1) {
                            if (mode == 0) {
                                debug_StdPrintfDummy(D_0054FC30);
                                mc_TransMicroCode(2, 0x10);
                            }
                            dl_SetDLPriority(4);
                            regTransTexturePacket(*(short *)(pkt + 0x88), 4);
                            dl_OpenDma(2, D_0054FBD0, 6);
                            dl_CloseDma();
                            reg_chooseReflectionMicroCode(0, r, 4);
                            dl_OpenDma(2, *(char **)(pkt + 0x98),
                                       (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
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
                pkt = *(char **)(pkt + 0x94);
            }
        }
        if (*(int *)(o + 0x858) != 0) {
            shadow_RenderVolumeMulti(o, i);
        }
    }
}

void reg_dispSObj(char *o, int idx)
{
    char *grp;
    char *pkt;
    char *pk;
    int i;
    int r;
    int pri;
    int mode;

    grp = *(char **)(*(char **)(o + 0x854) + 0x48);
    pkt = *(char **)(grp + 8);
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
                pri = regMaterialDLPri((int *)grp, *(short *)(pkt + 0x80),
                                       tex_GetTexExtData(*(short *)(pkt + 0x84)), 0.0f);
                regTransTexturePacket(*(short *)(pkt + 0x84), pri);
                reg_transMaterialPacket((short *)pkt, (int *)grp);
                reg_chooseMicroCode((char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70), r, pri);
                dl_OpenDma(2, *(char **)(pkt + 0x98), (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                dl_CloseDma();
                if (*(int *)(*(char **)(o + 0x874) + 0xF0) == 2) {
                    if (*(short *)(pkt + 0x86) != -1) {
                        func_00121428(pkt, r, 0);
                    }
                }
                mode = *(int *)(*(char **)(o + 0x874) + 0xF0);
                if (*(short *)(pkt + 0x88) != -1) {
                    if (mode == 0) {
                        debug_StdPrintfDummy(D_0054FC30);
                        mc_TransMicroCode(2, 0x10);
                    }
                    dl_SetDLPriority(4);
                    regTransTexturePacket(*(short *)(pkt + 0x88), 4);
                    dl_OpenDma(2, D_0054FBD0, 6);
                    dl_CloseDma();
                    reg_chooseReflectionMicroCode(0, r, 4);
                    dl_OpenDma(2, *(char **)(pkt + 0x98), (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                    dl_CloseDma();
                    if (mode == 0) {
                        mc_TransMicroCode(1, 0x10);
                    }
                }
            }
            pkt = *(char **)(pkt + 0x94);
        }
    }
    if (*(int *)(o + 0x858) != 0) {
        shadow_RenderVolume(o);
    }
}

void reg_dispCObj(char *o)
{
    char *mdl;
    char *grp;
    char *pkt;
    char *node;
    int i;
    int pri;

    mdl = *(char **)(o + 0x854);
    grp = *(char **)(mdl + 0x48);
    reg_transMicroCode(o, 0x3B3);
    reg_setCMatrixPacket(o, 1.0f, 0x3B3);
    for (i = 0; i < *(signed char *)(mdl + 0x2E); i++, grp += 0x30) {
        if (*(int *)(i * 0x180 + *(int *)(mdl + 0x40) + 0x124) != 0) {
            node = *(char **)(grp + 0xC);
            if (node != 0) {
                pkt = node;
                if (buffer_ID != 0) {
                    pkt = *(char **)(grp + 8);
                }
                reg_setShape(o, i, buffer_ID == 0, pkt,
                             (char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70));
            } else {
                pkt = *(char **)(grp + 8);
            }
        } else {
            pkt = *(char **)(grp + 8);
        }
        while (pkt != 0) {
            pri = regMaterialDLPri((int *)grp, *(short *)(pkt + 0x80),
                                   tex_GetTexExtData(*(short *)(pkt + 0x84)), 0.0f);
            regTransTexturePacket(*(short *)(pkt + 0x84), pri);
            reg_transMaterialPacket((short *)pkt, (int *)grp);
            reg_chooseMicroCode((char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70), 0, pri);
            dl_OpenDma(2, *(char **)(pkt + 0x98), (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
            dl_CloseDma();
            if (D_0063B1AC == 2 && *(int *)(*(char **)(o + 0x874) + 0xF0) == 2) {
                if (*(short *)(pkt + 0x86) != -1) {
                    func_00121428(pkt, 0, 1);
                }
            }
            pkt = *(char **)(pkt + 0x94);
        }
    }
    if (*(int *)(o + 0x858) != 0) {
        shadow_RenderVolume(o);
    }
}

extern int D_0028F4C0[];
/* kept local: this TU's calls pass the two arguments the VU0 bodies read,
   where Matrix.h declares three */
extern void _RotTransPersCurrentMatrix(void *dst, void *src);
extern void _FTOI4Vector(void *dst, void *src);
extern void _CopyIVector(void *dst, void *src);
extern int _IsInScreen(int *p);

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
            if (D_0028F4C0[5] == 0) {
                v = *(Qw128 *)(node + 0x10);
            } else {
                v = *(Qw128 *)(node + 0x20);
            }
            *(Qw128 *)iv2 = v;
        }
        if (D_0028F4C0[5] == 0) {
            *(Qw128 *)(node + 0x20) = *(Qw128 *)(node + 0x10);
            *(Qw128 *)(node + 0x10) = *(Qw128 *)iv;
        }
    } else {
        if (flag != 0) {
            _CopyIVector(iv2, iv);
        } else {
            if (D_0028F4C0[5] == 0) {
                _CopyIVector(iv2, node + (idx * 0x10 + 0x50));
            } else {
                _CopyIVector(iv2, node + (idx * 0x10 + 0x80));
            }
        }
        if (D_0028F4C0[5] == 0) {
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
typedef union {
    float f;
    unsigned int u;
} RegFloatBits;

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

        D_0063B124 += tex_TransTexture((unsigned short)f << 21 >> 21, pri);
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

extern int D_0063A06C;
extern int GlobalTimer;
/* kept local: this TU's uses of _MulCurrentMatrixL do not fit the prototype in Matrix.h */
extern void _MulCurrentMatrixL(void *m);

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

void reg_DispAccessoryWithShadow(char *o, char *src)
{
    char *reg_setNMatrixPacketNoLightCalc(char *o, char *src, int idx)
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
            _CopyMatrix(m + 0x40, *(char **)(o + 0x874) + 0x40);
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
            return 0;
        }
        pkt = PacketBufferStruct.ptr.c;
        PacketBufferStruct.dma.c = pkt;
        PacketBufferStruct.tail.c = 0;
        PacketBufferStruct.gif.c = 0;
        PacketBufferStruct.end.c = 0;
        setMatrix();
        if (mode != 0 && mode != 3) {
            *(float *)(*(char **)(o + 0x854) + 0x3C) = *(float *)(*(char **)(src + 0x854) + 0x3C);
            _CopyVector(o + 0x860, src + 0x860);
            _CopyMatrix(*(char **)(o + 0x874), *(char **)(src + 0x874));
            _CopyMatrix(*(char **)(o + 0x874) + 0x40, *(char **)(src + 0x874) + 0x40);
            _SetCurrentMatrix(matrixptr + 0x40);
            _ClearTransCurrentMatrix();
            _MulCurrentMatrixL(*(char **)(o + 0x874));
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
    char *mdl;
    char *grp;
    char *pk;
    char *pkt;
    char *box;
    int i;
    int j;
    int r;
    int pri;
    int mode;

    mdl = *(char **)(o + 0x854);
    grp = *(char **)(mdl + 0x48);
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
        for (j = 0; j < *(signed char *)(mdl + 0x2E); j++, grp += 0x30) {
            box = (char *)(j * 0x80 + *(int *)(*(char **)(o + 0x854) + 0x44));
            _SetCurrentMatrix(matrixptr + 0x300);
            if (gsb_ClipBox(box) != 0) {
                pkt = *(char **)(grp + 8);
                while (pkt != 0) {
                    r = reg_clipPacketBoundingBox(pkt);
                    if (r != 0) {
                        pri = regMaterialDLPri((int *)grp, *(short *)(pkt + 0x80),
                                               tex_GetTexExtData(*(short *)(pkt + 0x84)), 0.0f);
                        regTransTexturePacket(*(short *)(pkt + 0x84), pri);
                        reg_transMaterialPacket((short *)pkt, (int *)grp);
                        reg_chooseMicroCode((char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70),
                                            r, pri);
                        dl_OpenDma(2, *(char **)(pkt + 0x98),
                                   (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                        dl_CloseDma();
                        if (*(int *)(*(char **)(o + 0x874) + 0xF0) == 2) {
                            if (*(short *)(pkt + 0x86) != -1) {
                                func_00121428(pkt, r, 0);
                            }
                        }
                        mode = *(int *)(*(char **)(o + 0x874) + 0xF0);
                        if (*(short *)(pkt + 0x88) != -1) {
                            if (mode == 0) {
                                debug_StdPrintfDummy(D_0054FC30);
                                mc_TransMicroCode(2, 0x10);
                            }
                            dl_SetDLPriority(4);
                            regTransTexturePacket(*(short *)(pkt + 0x88), 4);
                            dl_OpenDma(2, D_0054FBD0, 6);
                            dl_CloseDma();
                            reg_chooseReflectionMicroCode(0, r, 4);
                            dl_OpenDma(2, *(char **)(pkt + 0x98),
                                       (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                            dl_CloseDma();
                            if (mode == 0) {
                                mc_TransMicroCode(1, 0x10);
                            }
                        }
                    }
                    pkt = *(char **)(pkt + 0x94);
                }
            }
        }
        if (*(int *)(o + 0x858) != 0) {
            shadow_RenderVolume(o);
        }
    }
}

/* ===== su-a sweep end ===== */

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

/* The sixteen bytes that close the enemy matrix packet: the VIF MSCAL 0x10
   code and three zero words, copied as one quadword (the ROM's lq/sq pair). */
static const struct {
    int w[4];
} regEnemyEndTag __attribute__((aligned(16))) = {{0x15000010, 0, 0, 0}};

void reg_DispEnemy(void *sub)
{
    char *o = sub;
    char *mdl;
    char *grp;
    char *pkt;
    float alpha;
    int i;
    int pri;

    void reg_setEMatrixPacket(char *o, int prilist, float alpha)
    {
        int i;

        inline void pack(void)
        {
            char *c;
            char *m;
            int n;

            /* the object's matrix count through the object record, the view
             * reg_setMMatrixPacket takes of o: an in-struct reference, so the
             * frame home of i does not wait for the loop test (alias.c
             * fixed_scalar_and_varying_struct_p); `*(int *)(o + 8)` in the
             * loop test costs the blez delay slot */
            n = ((Sub15C *)o)->f_8 * 4;
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
            for (i = 0; i < ((Sub15C *)o)->f_8; i++) {
                _MulMatrix(PacketBufferStruct.ptr.c, *(char **)(o + 0xC) + i * 0x40,
                           *(char **)(o + 0x90) + i * 0x40);
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

    mdl = *(char **)(o + 0x854);
    grp = *(char **)(mdl + 0x48);
    alpha = 1.0f - *(float *)(*(int *)(o + 0x870) + 0x30);
    reg_transMicroCode(o, 0x3A0);
    reg_setEMatrixPacket(o, 0x3A0, alpha);
    if ((alpha < 0.0f ? -alpha : alpha) == 0.0f) {
        goto done;
    }
    {
        for (i = 0; i < *(signed char *)(mdl + 0x2E); i++, grp += 0x30) {
            if (*(int *)(i * 0x180 + *(int *)(mdl + 0x40) + 0x124) != 0) {
                if (*(char **)(grp + 0xC) != 0) {
                    if (buffer_ID != 0) {
                        pkt = *(char **)(grp + 8);
                    } else {
                        pkt = *(char **)(grp + 0xC);
                    }
                    reg_setShape(o, i, buffer_ID == 0, pkt,
                                 (char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70));
                } else {
                    pkt = *(char **)(grp + 8);
                }
            } else {
                pkt = *(char **)(grp + 8);
            }
            while (pkt != 0) {
                pri = regMaterialDLPri((int *)grp, *(short *)(pkt + 0x80),
                                       tex_GetTexExtData(*(short *)(pkt + 0x84)), 0.0f);
                regTransTexturePacket(*(short *)(pkt + 0x84), pri);
                reg_transMaterialPacket((short *)pkt, (int *)grp);
                reg_chooseMicroCode((char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70), 0, pri);
                dl_OpenDma(2, *(char **)(pkt + 0x98), (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                dl_CloseDma();
                pkt = *(char **)(pkt + 0x94);
            }
        }
    }
done:
    if (*(int *)(o + 0x858) != 0) {
        shadow_RenderVolume(o);
    }
}

void reg_DispMultiPri(char *o, int pri)
{
    char *mdl;
    char *grp;
    char *pkt;
    char *node;
    char *pk;
    float *w;
    float alpha;
    int i;
    int j;
    int r;
    int dis;
    int fade;
    int mode;
    int prilist;

    mdl = *(char **)(o + 0x854);
    grp = *(char **)(mdl + 0x48);
    reg_transMicroCode(o, 1 << pri);
    for (i = 0; i < *(int *)(o + 8); i++) {
        w = (float *)(i * 0x50 + *(int *)(o + 0x870));
        alpha = 1.0f - (1.0f - w[12]) * w[13];
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
        if (*(int *)(i * 0x180 + *(int *)(mdl + 0x40) + 0x124) != 0 &&
            (node = *(char **)(grp + 0xC)) != 0) {
            pkt = node;
            if (buffer_ID != 0) {
                pkt = *(char **)(grp + 8);
            }
            reg_setShape(o, i, buffer_ID == 0, pkt,
                         (char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70));
        } else {
            pkt = *(char **)(grp + 8);
        }
        while (pkt != 0) {
            r = reg_clipPacketBoundingBox(pkt);
            if (r != 0) {
                fade = 0;
                if ((*(long long *)(i * 0x50 + *(int *)(o + 0x870) + 0x38) & 1) == 1) {
                    if (alpha != 0.0f) {
                        fade = 1;
                    }
                }
                regTransTexturePacket(*(short *)(pkt + 0x84), pri);
                reg_transMaterialPacket((short *)pkt, (int *)grp);
                dis = 0;
                if (fade != 0) {
                    dis = reg_setDissolve(alpha, pri);
                }
                if (dis != -1) {
                    reg_chooseMicroCode((char *)(*(int *)grp + *(short *)(pkt + 0x80) * 0x70), r,
                                        pri);
                    dl_OpenDma(2, *(char **)(pkt + 0x98), (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
                    dl_CloseDma();
                    if (*(int *)(*(char **)(o + 0x874) + 0xF0) == 2) {
                        if (*(short *)(pkt + 0x86) != -1) {
                            func_00121428(pkt, r, 0);
                        }
                    }
                    mode = *(int *)(*(char **)(o + 0x874) + 0xF0);
                    if (*(short *)(pkt + 0x88) != -1) {
                        if (mode == 0) {
                            debug_StdPrintfDummy(D_0054FC30);
                            mc_TransMicroCode(2, 0x10);
                        }
                        dl_SetDLPriority(4);
                        regTransTexturePacket(*(short *)(pkt + 0x88), 4);
                        dl_OpenDma(2, D_0054FBD0, 6);
                        dl_CloseDma();
                        reg_chooseReflectionMicroCode(0, r, 4);
                        dl_OpenDma(2, *(char **)(pkt + 0x98),
                                   (*(int *)(pkt + 0x90) & 0xFFFFFF) >> 4);
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
            pkt = *(char **)(pkt + 0x94);
        }
    }
}

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

void reg_DispObj2(char *o, int idx)
{
    reg_dispSObj(o, idx);
}

extern int D_0063A168;

void reg_SetScissorSw(int val)
{
    D_0063A168 = val;
}

void reg_TransTexturePacket(int tex, int pri)
{
    if (tex >= 0) {
        D_0063B124 += tex_TransTexture(tex, pri);
    }
}

void reg_Init(void)
{
    D_0063A168 = 0;
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
