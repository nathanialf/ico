#include "common.h"
#include "debug.h"
#include "memory.h"
#include "camera-root.h"
#include "Basic.h"
#include "geometryManager.h"
#include "lineManager.h"
#include "matrixDrive.h"

typedef struct Light {
    char _pad0[0x10];
    float f_10[4]; /* 0x10 */
    float f_20[4]; /* 0x20 */
    float f_30;    /* 0x30 */
    float f_34;    /* 0x34 */
    float f_38;    /* 0x38 */
    float f_3C;    /* 0x3C */
    char *f_40;    /* 0x40 */
    short f_44;    /* 0x44 */
    char _pad46[2];
    struct Light *next; /* 0x48 */
    struct Light *prev; /* 0x4C */
} Light;

typedef struct AmbientVolume {
    char _pad0[0x40];
    float f_40[4]; /* 0x40 */
    float f_50[4]; /* 0x50 */
    float f_60[4]; /* 0x60 */
    float f_70[4]; /* 0x70 */
    float f_80;    /* 0x80 */
    char _pad84[0xC];
    int f_90;                   /* 0x90 */
    struct AmbientVolume *next; /* 0x94 */
    struct AmbientVolume *prev; /* 0x98 */
} AmbientVolume;

extern char D_0054F0B0[];
extern char D_0054F0C8[];
extern char D_0054F0D8[];
extern char D_0063A090[];
extern int D_0063C134;
extern int D_0063C138;
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

void light_killLinkLight(char *node)
{
    Light *p = (Light *)node;

    if (p == 0) {
        debug_StdPrintfDummy(D_0054F0B0);
        debug_assert(D_0054F0C8, 0x1A8);
        __assert(D_0054F0C8, 0x1A8, D_0063A090);
    }
    if (p->next != 0) {
        p->next->prev = p->prev;
    } else {
        D_0063C134 = (int)p->prev;
    }
    if (p->prev != 0) {
        p->prev->next = p->next;
    }
    if (D_0063C134 != 0) {
        ((Light *)D_0063C134)->next = 0;
    }
    freeseki(p);
}

void light_killLinkAmbient(AmbientVolume *p)
{
    if (p == 0) {
        debug_StdPrintfDummy(D_0054F0D8);
        debug_assert(D_0054F0C8, 0x1C3);
        __assert(D_0054F0C8, 0x1C3, D_0063A090);
    }
    if (p->next != 0) {
        p->next->prev = p->prev;
    } else {
        D_0063C138 = (int)p->prev;
    }
    if (p->prev != 0) {
        p->prev->next = p->next;
    }
    if (D_0063C138 != 0) {
        ((AmbientVolume *)D_0063C138)->next = 0;
    }
    freeseki(p);
}

typedef struct StageSetting {
    float flatLightDir[3][4]; /* 0x00 */
    float flatLightCol[3][4]; /* 0x30 */
    float ambientCol[4];      /* 0x60 */
} StageSetting;

extern StageSetting D_0028F720;
extern int D_002908B8[];
/* kept local: this TU's uses of _CopyVector do not fit the prototype in Matrix.h */
extern void _CopyVector(void *dst, void *src);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *dst, void *src);
extern char D_0063A088[8];
extern char D_0054F0F8[];
extern char D_0054F118[];
extern int D_0063A44C;
/* kept local: this TU's uses of light_resetFlatLight do not fit the prototype in Light.h */
extern void light_resetFlatLight(void);
extern Light D_0067BCE0[];
extern float D_005D3DC8[][4];
extern int D_0063C13C;

/* Light.c lines 382-391: the list head keeps the newest node.  Line 391's
   counter update is a debug arm the retail build compiles out (the
   January-2002 listing still has it, three expansions, nine instructions). */
static inline void light_setLinkLight(Light *p)
{
    if (D_0063C134 != 0) {
        ((Light *)D_0063C134)->next = p;
    }
    p->next = 0;
    p->prev = (Light *)D_0063C134;
    D_0063C134 = (int)p;
}

Light *light_AddLight(char *self, int b, int kind)
{
    int i;
    float d;
    float *t;

    switch (kind) {
    case 0: {
        Light *l;

        if (*(int *)D_0063A088 != 0) {
            debug_StdPrintfDummy(D_0054F0F8);
            light_resetFlatLight();
            return 0;
        }
        for (i = 0; i < 3; i++) {
            l = &D_0067BCE0[i];
            _CopyVector(l->f_20, D_0028F720.flatLightCol[i]);
            _NormalizeVector(l->f_10, D_0028F720.flatLightDir[i]);
            l->f_30 = 1.0f;
            l->f_34 = 0.0f;
            l->f_38 = 1.0f;
            d = (l->f_20[0] + l->f_20[1] + l->f_20[2]) * 0.3333f;
            if (d < 0.0f) {
                d = -d;
            }
            l->f_3C = d;
            light_setLinkLight(l);
            D_002908B8[(*(int *)D_0063A088)++] = (int)l;
        }
        return 0;
    }
    case 1: {
        Light *q;

        if (b == 0) {
            return 0;
        }
        if (*(int *)(self + 0x15C) == 0) {
            return 0;
        }
        q = (Light *)iosMallocDebug(D_0063A44C, 0x50, D_0054F0C8, 620);
        *(int *)(*(int *)(self + 0x15C) + 0x83C) = b;
        q->f_40 = self;
        q->f_44 = kind;
        t = D_005D3DC8[b];
        q->f_20[0] = t[0] * 0.00390625f;
        q->f_20[1] = t[1] * 0.00390625f;
        q->f_20[2] = t[2] * 0.00390625f;
        q->f_20[3] = 1.0f;
        q->f_30 = 1.0f;
        q->f_34 = (0.0f < t[3]) ? t[3] : 1.0f;
        q->f_38 = 1.0f;
        d = q->f_20[0] + q->f_20[1] + q->f_20[2];
        if (d < 0.0f) {
            d = -d;
        }
        q->f_3C = d;
        light_setLinkLight(q);
        return q;
    }
    case 2:
    case 3: {
        Light *r;

        r = (Light *)iosMallocDebug(D_0063A44C, 0x50, D_0054F0C8, 685);
        r->f_44 = kind;
        r->f_30 = 1.0f;
        r->f_34 = 32768.0f;
        light_setLinkLight(r);
        return r;
    }
    default:
        debug_StdPrintfDummy(D_0054F118);
        debug_assert(D_0054F0C8, 705);
        __assert(D_0054F0C8, 705, D_0063A090);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Light", light_getNearLight);

extern float D_0028F780[4];
/* kept local: this TU's uses of _GetNorm do not fit the prototype in Matrix.h */
extern float _GetNorm(void *p);
/* kept local: this TU's uses of _SetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _SetCurrentMatrix(void *m);
/* kept local: this TU's uses of _InverseCurrentMatrix do not fit the prototype in Matrix.h */
extern void _InverseCurrentMatrix(void);
/* kept local: this TU's uses of _ScaleVector2XYZ do not fit the prototype in Matrix.h */
extern void _ScaleVector2XYZ(void *dst, void *src, void *scale);
/* kept local: this TU's uses of _SubVectorXYZ do not fit the prototype in Matrix.h */
extern void _SubVectorXYZ(void *dst, void *x, void *y);
/* kept local: this TU's uses of _AddVector do not fit the prototype in Matrix.h */
extern void _AddVector(void *dst, void *x, void *y);
/* kept local: this TU's uses of _ApplyCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ApplyCurrentMatrix(void *dst, void *src);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float s);

/* Light.c lines 1024-1025 call _GetNorm three times per value (once for the
   sign test, once in each arm), which is what a macro does to a call
   argument: ABS is a macro here, not a function. */
#define LIGHT_ABS(x) ((x) < 0.0f ? -(x) : (x))

void light_getAmbientLight(char *a, int b)
{
    float pos[4];
    float p[4];
    float q[4];
    float s0[4];
    float s1[4];
    AmbientVolume *v;
    float best;
    float scale;
    /* mx/my carry the largest inner-ellipsoid component and its outer
       partner in the kind-1 arm; the kind-2 arm reuses my as its own blend
       total, a scratch reuse the ROM's register file proves (both roles are
       $f20 there, and the two arms' other scratch values are separate). */
    float mx;
    float my;

    scale = 1.0f;
    if (D_0063C138 == 0) {
        _CopyVector(*(char **)(a + 0x874) + 0xE0, D_0028F780);
        return;
    }
    _CopyVector(*(char **)(a + 0x874) + 0xE0, D_0028F780);
    best = 3.0f;
    if (*(unsigned short *)(a + 0x84C) == 2) {
        _CopyVector(pos, *(char **)(a + 0xC) + (b << 6) + 0x30);
    } else {
        _CopyVector(pos, *(char **)(a + 0xC) + 0x30);
    }
    for (v = (AmbientVolume *)D_0063C138; v != 0; v = v->prev) {
        if (v->f_90 == 0) {
            continue;
        }
        _SetCurrentMatrix(v);
        _InverseCurrentMatrix();
        _ApplyCurrentMatrix(p, pos);
        _ApplyCurrentMatrix(q, pos);
        _ScaleVector2XYZ(p, p, v->f_70);
        _ScaleVector2XYZ(q, q, v->f_70);
        _ScaleVector2XYZ(p, p, v->f_50);
        _ScaleVector2XYZ(q, q, v->f_60);
        switch (v->f_90) {
        case 2: {
            float nx;
            float ny;
            float rx;
            float ry;

            nx = LIGHT_ABS(_GetNorm(p));
            ny = LIGHT_ABS(_GetNorm(q));
            if (nx <= 1.0f) {
                _CopyVector(*(char **)(a + 0x874) + 0xE0, v->f_40);
                scale = v->f_80;
                goto found;
            }
            if (ny <= 1.0f) {
                rx = nx - 1.0f;
                ry = 1.0f - ny;
                _SubVectorXYZ(s0, D_0028F780, v->f_40);
                _ScaleVectorXYZ(s0, s0, rx / (rx + ry));
                _AddVector(s0, v->f_40, s0);
                my = s0[0] + s0[1] + s0[2];
                if (my < best) {
                    _CopyVector(*(char **)(a + 0x874) + 0xE0, s0);
                    best = my;
                    scale = v->f_80 + (1.0f - v->f_80) * rx / (rx + ry);
                }
            }
            break;
        }
        case 1: {
            float sum;

            if (LIGHT_ABS(p[0]) <= 1.0f && LIGHT_ABS(p[1]) <= 1.0f && LIGHT_ABS(p[2]) <= 1.0f) {
                _CopyVector(*(char **)(a + 0x874) + 0xE0, v->f_40);
                scale = v->f_80;
                goto found;
            }
            if (LIGHT_ABS(q[0]) <= 1.0f && LIGHT_ABS(q[1]) <= 1.0f && LIGHT_ABS(q[2]) <= 1.0f) {
                mx = LIGHT_ABS(p[0]);
                my = LIGHT_ABS(q[0]);
                if (mx < LIGHT_ABS(p[1])) {
                    mx = LIGHT_ABS(p[1]);
                    my = LIGHT_ABS(q[1]);
                }
                if (mx < LIGHT_ABS(p[2])) {
                    mx = LIGHT_ABS(p[2]);
                    my = LIGHT_ABS(q[2]);
                }
                mx = mx - 1.0f;
                my = 1.0f - my;
                _SubVectorXYZ(s1, D_0028F780, v->f_40);
                _ScaleVectorXYZ(s1, s1, mx / (mx + my));
                _AddVector(s1, v->f_40, s1);
                sum = s1[0] + s1[1] + s1[2];
                if (sum < best) {
                    /* the kind-1 arm copies the volume colour here where the
                       kind-2 arm copies its blended vector; the ROM's $s0
                       (v + 0x40) at this call site is what it is. */
                    _CopyVector(*(char **)(a + 0x874) + 0xE0, v->f_40);
                    best = sum;
                    scale = v->f_80 + (1.0f - v->f_80) * mx / (mx + my);
                }
            }
            break;
        }
        }
    }
found:
    _ScaleVectorXYZ(*(char **)(a + 0x874) + 0xB0, *(char **)(a + 0x874) + 0xB0, scale);
    _ScaleVectorXYZ(*(char **)(a + 0x874) + 0xC0, *(char **)(a + 0x874) + 0xC0, scale);
    _ScaleVectorXYZ(*(char **)(a + 0x874) + 0xD0, *(char **)(a + 0x874) + 0xD0, scale);
    *(float *)(*(char **)(a + 0x874) + 0xEC) = 1.0f;
}

/* kept local: this TU's uses of light_getNearLight do not fit the prototype in Light.h */
extern void light_getNearLight(char *a, int b);
/* kept local: this TU's uses of light_getAmbientLight do not fit the prototype in Light.h */
extern void light_getAmbientLight(char *a, int b);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float s);
/* kept local: this TU's uses of _MakeNormalLightMatrix do not fit the prototype in Matrix.h */
extern void _MakeNormalLightMatrix(void *a, void *b, void *c, void *d);
/* kept local: this TU's uses of _MakeLightColorMatrix do not fit the prototype in Matrix.h */
extern void _MakeLightColorMatrix(void *a, void *b, void *c, void *d, void *e);

void light_MakeLightMatrix(char *a, int b)
{
    int i;

    if (*(int *)(*(char **)(a + 0x874) + 0xF0) == 0) {
        return;
    }
    light_getNearLight(a, b);
    light_getAmbientLight(a, b);
    for (i = 0; i < 3; i++) {
        _ScaleVectorXYZ(*(char **)(a + 0x874) + 0xB0 + i * 0x10,
                        *(char **)(a + 0x874) + 0xB0 + i * 0x10,
                        *(float *)(*(char **)(a + 0x854) + 0x34));
    }
    _ScaleVectorXYZ(*(char **)(a + 0x874) + 0xE0, *(char **)(a + 0x874) + 0xE0,
                    *(float *)(*(char **)(a + 0x854) + 0x38));
    _MakeNormalLightMatrix(*(char **)(a + 0x874), *(char **)(a + 0x874) + 0x80,
                           *(char **)(a + 0x874) + 0x90, *(char **)(a + 0x874) + 0xA0);
    _MakeLightColorMatrix(*(char **)(a + 0x874) + 0x40, *(char **)(a + 0x874) + 0xB0,
                          *(char **)(a + 0x874) + 0xC0, *(char **)(a + 0x874) + 0xD0,
                          *(char **)(a + 0x874) + 0xE0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Light", light_DispVolume);

/* Light.c line 1388.  Declared `inline`, so ee-gcc expands it into light_Tool
   (listing rows 1388-1406 sit inside light_Tool's span) and defers the
   out-of-line copy to the end of the object, which is where the ROM has it
   (0x00118F58, after light_AddAmbientObject).  light_AddLight sits above this
   definition and so keeps its out-of-line call. */
inline void light_resetFlatLight(void)
{
    int i;
    Light *l;

    for (i = 0; i < 3; i++) {
        l = (Light *)D_002908B8[i];
        if (l != 0) {
            _CopyVector(l->f_20, D_0028F720.flatLightCol[i]);
            _NormalizeVector(l->f_10, D_0028F720.flatLightDir[i]);
            l->f_30 = 1.0f;
            l->f_34 = 0.0f;
            l->f_38 = 1.0f;
            l->f_3C = (l->f_20[0] + l->f_20[1] + l->f_20[2]) * 0.3333f;
        }
    }
}

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4; the right analog stick pair sits at 0x54 of pad 1. */
typedef struct Pad {
    int unk00;            /* 0x00 */
    int trg;              /* 0x04 */
    int unk08;            /* 0x08 */
    int rep;              /* 0x0C */
    char unk10[0x44];     /* 0x10 */
    unsigned char ana[4]; /* 0x54 */
} Pad;

extern Pad D_0028F8F0[];
extern float atan2f(float y, float x);
/* kept local: this TU's uses of _Sqrt do not fit the prototype in Matrix.h */
extern float _Sqrt(float v);

void light_GetColorAnalog(float *col)
{
    float x;
    float y;
    float a;
    float r;
    float g;
    float b;
    float d;

    x = (float)(D_0028F8F0[1].ana[0] - 128);
    y = (float)(D_0028F8F0[1].ana[1] - 128);

    a = atan2f(x, y);
    r = 0.0f - a;
    g = 2.0943952f - a;
    b = 4.1887903f - a;
    while (r > 3.1415927f) {
        r -= 3.1415927f;
    }
    while (g > 3.1415927f) {
        g -= 3.1415927f;
    }
    while (b > 3.1415927f) {
        b -= 3.1415927f;
    }
    while (r < -3.1415927f) {
        r += 3.1415927f;
    }
    while (g < -3.1415927f) {
        g += 3.1415927f;
    }
    while (b < -3.1415927f) {
        b += 3.1415927f;
    }
    if (r > 2.0943952f) {
        r = 0.0f;
    }
    if (g > 2.0943952f) {
        g = 0.0f;
    }
    if (b > 2.0943952f) {
        b = 0.0f;
    }
    r = (2.0943952f - r) * 64.0f / 2.0943952f;
    g = (2.0943952f - g) * 64.0f / 2.0943952f;
    b = (2.0943952f - b) * 64.0f / 2.0943952f;
    d = _Sqrt(x * x + y * y);
    r += d - 64.0f;
    g += d - 64.0f;
    b += d - 64.0f;
    r *= 1.2f;
    g *= 1.2f;
    b *= 1.2f;
    if (r > 255.0f) {
        r = 255.0f;
    }
    if (g > 255.0f) {
        g = 255.0f;
    }
    if (b > 255.0f) {
        b = 255.0f;
    }
    if (r < 0.0f) {
        r = 0.0f;
    }
    if (g < 0.0f) {
        g = 0.0f;
    }
    if (b < 0.0f) {
        b = 0.0f;
    }
    col[0] = r;
    col[1] = g;
    col[2] = b;
}

typedef union LtVec {
    float f[4];
    long long ll[2];
} LtVec;

/* .rodata cursor geometry: tip, and the two base corners; the cursor colour
   is the four-byte RGBA word set at D_0054F170. */
extern const LtVec D_0054F140;
extern const LtVec D_0054F150;
extern const LtVec D_0054F160;
extern const LtVec D_0054F170;
extern int D_0063C12C;
extern int D_0063C130;
extern void *memset(void *p, int c, int n);
/* kept local: this TU's uses of _InitCurrentMatrix do not fit the prototype in Matrix.h */
extern void _InitCurrentMatrix(void);
/* kept local: this TU's uses of _TransCurrentMatrix do not fit the prototype in Matrix.h */
extern void _TransCurrentMatrix(void *p);
/* kept local: this TU's uses of _RotCurrentMatrixX do not fit the prototype in Matrix.h */
extern void _RotCurrentMatrixX(short a);
/* kept local: this TU's uses of _RotCurrentMatrixY do not fit the prototype in Matrix.h */
extern void _RotCurrentMatrixY(short a);
/* kept local: this TU's uses of _ApplyCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ApplyCurrentMatrix(void *dst, void *src);
/* kept local: this TU's uses of _SubVector do not fit the prototype in Matrix.h */
extern void _SubVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of _AddVector do not fit the prototype in Matrix.h */
extern void _AddVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *dst, void *src, float s);
/* kept local: this TU's uses of _UnitMatrix do not fit the prototype in Matrix.h */
extern void _UnitMatrix(void *m);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);

void light_DrawCursor(float *dir, int mode)
{
    float m[4][4];
    LtVec sub;
    LtVec tip;
    LtVec base;
    LtVec left;
    LtVec right;
    int i;

    tip = D_0054F140;
    memset(&base, 0, 16);
    left = D_0054F150;
    right = D_0054F160;
    base.f[3] = 1.0f;
    GetRootMatrix(m, CameraGetTarget());
    if (mode == 0) {
        LtVec col;

        D_0063C12C = (128 - D_0028F8F0[1].ana[0]) * 32767 / 128;
        D_0063C130 = (D_0028F8F0[1].ana[1] - 128) * 32767 / 128;
        _InitCurrentMatrix();
        _TransCurrentMatrix(m[3]);
        _RotCurrentMatrixX(D_0063C130);
        _RotCurrentMatrixY(D_0063C12C);
        _ApplyCurrentMatrix(&tip, &tip);
        _ApplyCurrentMatrix(&left, &left);
        _ApplyCurrentMatrix(&right, &right);
        _ApplyCurrentMatrix(&base, &base);
        _SubVector(&sub, &tip, &base);
        _AddVector(&tip, &tip, &sub);
        _AddVector(&left, &left, &sub);
        _AddVector(&right, &right, &sub);
        _AddVector(&base, &base, &sub);
        dir[0] = dir[1] = dir[3] = 0.0f;
        dir[2] = 1.0f;
        _ApplyCurrentMatrix(dir, dir);
        _NormalizeVector(dir, dir);
        gif_StartPacketPri(11);
        col = D_0054F170;
        MatrixDrive_PushMatrix();
        _UnitMatrix(MatrixDrive_GetMatrix());
        DrawLine(&tip, &base, &col, -1);
        DrawLine(&left, &base, &col, -1);
        DrawLine(&right, &base, &col, -1);
        MatrixDrive_PopMatrix();
        gif_EndPacket();
    }
    gif_StartPacketPri(11);
    {
        LtVec col;

        col = D_0054F170;
        for (i = 0; i < 3; i++) {
            _ScaleVector(&tip, D_0028F720.flatLightDir[i], -100.0f);
            _ScaleVector(&left, D_0028F720.flatLightDir[i], -200.0f);
            _AddVectorXYZ(&tip, &tip, m[3]);
            _AddVectorXYZ(&left, &left, m[3]);
            MatrixDrive_PushMatrix();
            _UnitMatrix(MatrixDrive_GetMatrix());
            DrawLine(&tip, &left, &col, -1);
            MatrixDrive_PopMatrix();
        }
    }
    gif_EndPacket();
}

/* Light.c lines 1535-1684, the flat-light editor page of the debug menu.
   Three pages selected by D_0063A0A4 (colour, direction vector, ambient),
   each editing light D_0063A0AC with component D_0063A0A8 (3 = all three at
   once).  The retail build calls debug_PrintfDummy where the January-2002
   listing calls debug_Printf; everything else is instruction for instruction
   the same function, so the listing's per-instruction line map is the
   source-shape oracle here.  The blink guard masks frame_count with an
   unsigned constant: masked with a plain int 0x1F, gcc knows the value fits
   0..31 and picks slti, while the ROM has sltiu at all six sites.
   light_resetFlatLight is expanded at the tail (listing rows 1388-1406). */
extern int D_002908C8[];
extern int D_0063A0A4; /* the editor page: 0 colour, 1 vector, 2 ambient */
extern int D_0063A0A8; /* the selected component: 0 x/r, 1 y/g, 2 z/b, 3 all */
extern int D_0063A0AC; /* the selected flat light: 0..2 */
extern int frame_count;
extern char D_0063A0B0[]; /* "r:" */
extern char D_0063A0B8[]; /* "g:" */
extern char D_0063A0C0[]; /* "b:" */
extern char D_0063A0C8[]; /* "COL " */
extern char D_0063A0D0[]; /* "%s%11f" */
extern char D_0063A0D8[]; /* "VEC " */
extern char D_0063A0E0[]; /* "AMB " */
/* kept local: this TU's uses of light_GetColorAnalog do not fit the prototype in Light.h */
extern void light_GetColorAnalog(float *col);
/* kept local: this TU's uses of light_DrawCursor do not fit the prototype in Light.h */
extern void light_DrawCursor(float *dir, int mode);
/* kept local: this TU's uses of _InitCurrentMatrix do not fit the prototype in Matrix.h */
extern void _InitCurrentMatrix(void);
/* kept local: this TU's uses of _RotCurrentMatrixX do not fit the prototype in Matrix.h */
extern void _RotCurrentMatrixX(short a);
/* kept local: this TU's uses of _RotCurrentMatrixY do not fit the prototype in Matrix.h */
extern void _RotCurrentMatrixY(short a);
/* kept local: this TU's uses of _RotCurrentMatrixZ do not fit the prototype in Matrix.h */
extern void _RotCurrentMatrixZ(short a);
/* kept local: this TU's uses of _ApplyCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ApplyCurrentMatrix(void *dst, void *src);

int light_Tool(void)
{
    float dir[4];
    float col1[4];
    float col2[4];
    int ret = 0;
    int i;
    char *name[3] = {D_0063A0B0, D_0063A0B8, D_0063A0C0};
    unsigned int col;
    short rot;
    float (*c)[4];

    if (D_0028F8F0[0].trg & 0x4000) {
        if (++D_0063A0A4 == 3) {
            D_0063A0A4 = 0;
        }
    }
    if (D_0028F8F0[0].trg & 0x1000) {
        if (--D_0063A0A4 == -1) {
            D_0063A0A4 = 2;
        }
    }
    if (D_0028F8F0[0].trg & 0x1) {
        if (++D_0063A0AC == 3) {
            D_0063A0AC = 0;
        }
    }
    if (D_0028F8F0[0].trg & 0x100) {
        D_002908C8[0] = D_002908C8[1] = D_002908C8[2] = 1;
        ret = -1;
    }
    if (D_002908C8[1] == 0 && D_0063A0A4 == 1) {
        light_DrawCursor(dir, 0);
    } else {
        light_DrawCursor(dir, 1);
    }
    switch (D_0063A0A4) {
    case 0:
        D_002908C8[1] = D_002908C8[2] = 1;
        light_GetColorAnalog(col1);
        if ((D_0028F8F0[0].trg & 0x400) && D_0063A0A8 == 3) {
            D_002908C8[0] ^= 1;
        }
        if (D_002908C8[0] == 0 && D_0063A0A8 == 3) {
            /* The row pointer is into flatLightDir, so the three stores keep
               the +0x30 to flatLightCol in the store displacement off one
               base; spelling the destination as flatLightCol[idx][n] at each
               of the three sites folds 0x30 onto the symbol and makes gcse PRE
               insert two reaching-register copies the ROM does not have. */
            c = &D_0028F720.flatLightDir[D_0063A0AC];
            c[3][0] = col1[0] / 128.0f;
            c[3][1] = col1[1] / 128.0f;
            c[3][2] = col1[2] / 128.0f;
            break;
        }
        if (D_0028F8F0[0].trg & 0x2000) {
            if (++D_0063A0A8 == 4) {
                D_0063A0A8 = 0;
            }
        }
        if (D_0028F8F0[0].trg & 0x8000) {
            if (--D_0063A0A8 == -1) {
                D_0063A0A8 = 3;
            }
        }
        if (D_0063A0A8 != 3) {
            if (D_0028F8F0[0].rep & 0x20) {
                D_0028F720.flatLightCol[D_0063A0AC][D_0063A0A8] += 0.01f;
            }
            if (D_0028F8F0[0].rep & 0x40) {
                D_0028F720.flatLightCol[D_0063A0AC][D_0063A0A8] -= 0.01f;
            }
            break;
        }
        if (D_0028F8F0[0].rep & 0x20) {
            for (i = 0; i < 3; i++) {
                D_0028F720.flatLightCol[D_0063A0AC][i] *= 1.01f;
            }
        }
        if (D_0028F8F0[0].rep & 0x40) {
            for (i = 0; i < 3; i++) {
                D_0028F720.flatLightCol[D_0063A0AC][i] *= 0.99f;
            }
        }
        break;
    case 1:
        D_002908C8[0] = D_002908C8[2] = 1;
        if ((D_0028F8F0[0].trg & 0x400) && D_0063A0A8 == 3) {
            D_002908C8[1] ^= 1;
        }
        if (D_002908C8[1] == 0 && D_0063A0A8 == 3) {
            _CopyVector(D_0028F720.flatLightDir[D_0063A0AC], dir);
            break;
        }
        if (D_0028F8F0[0].trg & 0x2000) {
            if (++D_0063A0A8 == 4) {
                D_0063A0A8 = 0;
            }
        }
        if (D_0028F8F0[0].trg & 0x8000) {
            if (--D_0063A0A8 == -1) {
                D_0063A0A8 = 3;
            }
        }
        if (D_0063A0A8 == 3) {
            break;
        }
        if (D_0028F8F0[0].rep & 0x20) {
            rot = 1024;
        } else {
            rot = (D_0028F8F0[0].rep & 0x40) ? -1024 : 0;
        }
        _InitCurrentMatrix();
        switch (D_0063A0A8) {
        case 0:
            _RotCurrentMatrixX(rot);
            break;
        case 1:
            _RotCurrentMatrixY(rot);
            break;
        case 2:
            _RotCurrentMatrixZ(rot);
            break;
        }
        _ApplyCurrentMatrix(D_0028F720.flatLightDir[D_0063A0AC],
                            D_0028F720.flatLightDir[D_0063A0AC]);
        break;
    case 2:
        D_002908C8[0] = D_002908C8[1] = 1;
        light_GetColorAnalog(col2);
        if ((D_0028F8F0[0].trg & 0x400) && D_0063A0A8 == 3) {
            D_002908C8[2] ^= 1;
        }
        if (D_002908C8[2] == 0 && D_0063A0A8 == 3) {
            D_0028F720.ambientCol[0] = col2[0] / 255.0f;
            D_0028F720.ambientCol[1] = col2[1] / 255.0f;
            D_0028F720.ambientCol[2] = col2[2] / 255.0f;
            break;
        }
        if (D_0028F8F0[0].trg & 0x2000) {
            if (++D_0063A0A8 == 4) {
                D_0063A0A8 = 0;
            }
        }
        if (D_0028F8F0[0].trg & 0x8000) {
            if (--D_0063A0A8 == -1) {
                D_0063A0A8 = 3;
            }
        }
        if (D_0063A0A8 != 3) {
            if (D_0028F8F0[0].rep & 0x20) {
                D_0028F720.ambientCol[D_0063A0A8] += 0.01f;
            }
            if (D_0028F8F0[0].rep & 0x40) {
                D_0028F720.ambientCol[D_0063A0A8] -= 0.01f;
            }
            break;
        }
        if (D_0028F8F0[0].rep & 0x20) {
            for (i = 0; i < 3; i++) {
                D_0028F720.ambientCol[i] *= 1.01f;
            }
        }
        if (D_0028F8F0[0].rep & 0x40) {
            for (i = 0; i < 3; i++) {
                D_0028F720.ambientCol[i] *= 0.99f;
            }
        }
        break;
    }
    debug_PrintfDummy(10, 46, 0xFF800000, "PUSH R2 SELECT LIGHT (%d/3) ('SELECT'RETURN MENU)",
                      D_0063A0AC + 1);
    col = (D_0063A0A4 == 0) ? 0xFFC0C000 : 0xFFFFFF00;
    if (D_002908C8[0] != 0 || (frame_count & 0x1FU) < 20) {
        debug_PrintfDummy(10, 56, col, D_0063A0C8);
    }
    for (i = 0; i < 3; i++) {
        if (D_002908C8[0] == 0 || D_0063A0A4 != 0 || (D_0063A0A8 != i && D_0063A0A8 != 3) ||
            (frame_count & 0x1FU) < 20) {
            debug_PrintfDummy(46 + i * 168, 56, col, D_0063A0D0, name[i],
                              D_0028F720.flatLightCol[D_0063A0AC][i] * 128.0f);
        }
    }
    col = (D_0063A0A4 == 1) ? 0xFFC0C000 : 0xFFFFFF00;
    if (D_002908C8[1] != 0 || (frame_count & 0x1FU) < 20) {
        debug_PrintfDummy(10, 66, col, D_0063A0D8);
    }
    for (i = 0; i < 3; i++) {
        if (D_002908C8[1] == 0 || D_0063A0A4 != 1 || (D_0063A0A8 != i && D_0063A0A8 != 3) ||
            (frame_count & 0x1FU) < 20) {
            debug_PrintfDummy(46 + i * 168, 66, col, D_0063A0D0, name[i],
                              D_0028F720.flatLightDir[D_0063A0AC][i]);
        }
    }
    col = (D_0063A0A4 == 2) ? 0xFFC0C000 : 0xFFFFFF00;
    if (D_002908C8[2] != 0 || (frame_count & 0x1FU) < 20) {
        debug_PrintfDummy(10, 76, col, D_0063A0E0);
    }
    for (i = 0; i < 3; i++) {
        if (D_002908C8[2] == 0 || D_0063A0A4 != 2 || (D_0063A0A8 != i && D_0063A0A8 != 3) ||
            (frame_count & 0x1FU) < 20) {
            debug_PrintfDummy(46 + i * 168, 76, col, D_0063A0D0, name[i],
                              D_0028F720.ambientCol[i] * 255.0f);
        }
    }
    light_resetFlatLight();
    return ret;
}

extern char D_0063A088[8];
extern int D_0063C134;
extern int D_0063C138;

void light_InitLight(void)
{
    D_0063C134 = 0;
    D_0063C138 = 0;
    *(int *)D_0063A088 = 0;
}

void light_ResetLight(void) {}

extern int D_0063C13C;
/* kept local: this TU's uses of light_killLinkLight do not fit the prototype in Light.h */
extern void light_killLinkLight(char *node);

void light_KillAllFixLight(void)
{
    Light *p = (Light *)D_0063C134;
    while (p != 0) {
        short v = p->f_44;
        if (v < 4) {
            if (v >= 2) {
                Light *node = p;
                p = p->prev;
                light_killLinkLight((char *)node);
                continue;
            }
        }
        p = p->prev;
    }
    D_0063C13C = 0;
}

extern int D_0063C138;
/* kept local: this TU's uses of light_killLinkAmbient do not fit the prototype in Light.h */
extern void light_killLinkAmbient();

void light_KillAllAmbient(void)
{
    AmbientVolume *p = (AmbientVolume *)D_0063C138;
    while (p != 0) {
        int v = p->f_90;
        if (v < 3) {
            if (v >= 0) {
                AmbientVolume *node = p;
                p = p->prev;
                light_killLinkAmbient((char *)node);
                continue;
            }
        }
        p = p->prev;
    }
}

extern char D_0054F0C8[];
extern int D_0063A44C;

static inline void light_setLinkAmbient(AmbientVolume *p)
{
    if (D_0063C138 != 0)
        ((AmbientVolume *)D_0063C138)->next = p;
    p->next = 0;
    p->prev = (AmbientVolume *)D_0063C138;
    D_0063C138 = (int)p;
}

AmbientVolume *light_AddAmbientObject(int obj)
{
    AmbientVolume *p;

    p = (AmbientVolume *)iosMallocDebug(D_0063A44C, 0xA0, D_0054F0C8, 723);
    p->f_90 = obj;
    p->f_80 = 1.0f;
    light_setLinkAmbient(p);
    return p;
}
