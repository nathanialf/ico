#include "common.h"
#include "vu0.h"

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
    char _pad0[0x80];
    float f_80; /* 0x80 */
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
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void freeseki(void *p);

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
} StageSetting;

extern StageSetting D_0028F720;
extern int D_002908B8[];
extern void _CopyVector(void *dst, void *src);
extern void _NormalizeVector(void *dst, void *src);
extern char D_0063A088[8];
extern char D_0054F0F8[];
extern char D_0054F118[];
extern int D_0063A44C;
extern void *iosMallocDebug(int part, int size, char *file, int line);
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

ASM_LIT4_SLOT(D_00638BDC, 0.3333f);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_getNearLight);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_getAmbientLight);

extern void light_getNearLight(char *a, int b);
extern void light_getAmbientLight(char *a, int b);
extern void _ScaleVectorXYZ(void *dst, void *src, float s);
extern void _MakeNormalLightMatrix(void *a, void *b, void *c, void *d);
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

ASM_LIT4_SLOT(D_00638BE0, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_DispVolume);

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4; the right analog stick pair sits at 0x54 of pad 1. */
typedef struct Pad {
    int unk00;            /* 0x00 */
    int trg;              /* 0x04 */
    char unk08[0x4C];     /* 0x08 */
    unsigned char ana[4]; /* 0x54 */
} Pad;

extern Pad D_0028F8F0[];
extern float atan2f(float y, float x);
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
extern int CameraGetTarget(void);
extern void GetRootMatrix(void *dst, int gobj);
extern void _InitCurrentMatrix(void);
extern void _TransCurrentMatrix(void *p);
extern void _RotCurrentMatrixX(short a);
extern void _RotCurrentMatrixY(short a);
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern void _SubVector(void *dst, void *a, void *b);
extern void _AddVector(void *dst, void *a, void *b);
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern void _ScaleVector(void *dst, void *src, float s);
extern void _UnitMatrix(void *m);
extern void MatrixDrive_PushMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void DrawLine(void *from, void *to, void *col, int flag);
extern void gif_StartPacketPri(int pri);
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

ASM_LIT4_SLOT(D_00638C18, 0.01f);
ASM_LIT4_SLOT(D_00638C1C, 0.01f);
ASM_LIT4_SLOT(D_00638C20, 1.01f);
ASM_LIT4_SLOT(D_00638C24, 0.99f);
ASM_LIT4_SLOT(D_00638C28, 0.01f);
ASM_LIT4_SLOT(D_00638C2C, 0.01f);
ASM_LIT4_SLOT(D_00638C30, 1.01f);
ASM_LIT4_SLOT(D_00638C34, 0.99f);
ASM_LIT4_SLOT(D_00638C38, 0.3333f);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_Tool);

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
extern void *iosMallocDebug(int part, int size, char *file, int line);

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

void light_resetFlatLight(void)
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
