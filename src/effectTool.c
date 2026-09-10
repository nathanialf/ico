#include "common.h"

/* the effect-parameter descriptor table _dispParam/editParam walk: 0x1C per
 * entry, name pointer first, NULL-terminated.  `off` is the byte offset of the
 * field inside the effect package, `enums` an optional name table for a type-0
 * field and (min,max) the range printed after the label. */
typedef struct {
    char *name;        /* 0x00 */
    int off;           /* 0x04 */
    char **enums;      /* 0x08 */
    unsigned int type; /* 0x0C */
    int step;          /* 0x10 */
    int min;           /* 0x14 */
    int max;           /* 0x18 */
} EffParamDef;

extern EffParamDef D_004E74A0[];
extern char D_0061F490[]; /* "Unknown Data Type \"%s\"\n" */
extern char D_0061F4A8[]; /* "%-20s:%s" */
extern char D_0063B828[]; /* "%4.3f" */
extern char D_0063B830[]; /* "(%d,%d)" */
extern char D_0063B838[]; /* "%d" */
extern char D_0063B840[]; /* "%s" */
extern char D_0063B848[]; /* "%s%s" */
extern double fptodp(float v);
extern int sprintf();
extern void debug_PrintfDummy(int x, int y, unsigned int col, char *fmt, ...);

void _dispParam(int *pkg, int idx, int x, int y, int col)
{
    char lbl[256];
    char val[256];
    char rng[256];
    char *p = (char *)pkg + D_004E74A0[idx].off;
    EffParamDef *e = &D_004E74A0[idx];

    switch (e->type) {
    case 1:
        sprintf(val, D_0063B828, fptodp(*(float *)p));
        sprintf(rng, D_0063B830, e->min, e->max);
        break;
    case 0:
        if (e->enums == 0) {
            sprintf(val, D_0063B838, *(int *)p);
            sprintf(rng, D_0063B830, e->min, e->max);
        } else {
            sprintf(val, D_0063B840, e->enums[*(int *)p]);
            rng[0] = 0;
        }
        break;
    case 2:
        sprintf(val, D_0063B838, *(short *)p);
        sprintf(rng, D_0063B830, e->min, e->max);
        break;
    case 3:
        sprintf(val, D_0063B838, *(unsigned short *)p);
        sprintf(rng, D_0063B830, e->min, e->max);
        break;
    default:
        sprintf(val, D_0061F490, e->name);
        break;
    }
    sprintf(lbl, D_0063B848, e->name, rng);
    debug_PrintfDummy(x, y, col, D_0061F4A8, lbl, val);
}

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
 * pad, trg at 0x4 and rep at 0xC; this tool reads pad 0 and pad 1. */
typedef struct {
    int unk00;        /* 0x00 */
    int trg;          /* 0x04 */
    int unk08;        /* 0x08 */
    int rep;          /* 0x0C */
    char unk10[0x48]; /* 0x10 */
} EffToolPad;

extern EffToolPad D_0028F8F0[];

typedef union {
    int i;
    float f;
    short s;
    unsigned short us;
} EffVal;

extern int D_0063B850;
extern int D_00720070[];
extern int *GetParticleEffectPackage(int id);

int editParam(int id, int sel)
{
    EffParamDef *e = &D_004E74A0[sel];
    int *pkg = GetParticleEffectPackage(id);
    EffVal *p = (EffVal *)((char *)pkg + D_004E74A0[sel].off);
    int changed = 0;
    float step;
    int v;

    if ((D_0028F8F0[0].unk00 & 0x8000) || (D_0028F8F0[1].unk00 & 0x8000) ||
        (D_0028F8F0[0].unk00 & 0x2000) || (D_0028F8F0[1].unk00 & 0x2000)) {
        D_0063B850++;
    } else {
        D_0063B850 = 0;
    }
    if (D_0063B850 > 30) {
        step = (D_0063B850 - 10) / 10;
    } else {
        step = 1.0f;
    }
    switch (e->type) {
    case 1:
        if ((D_0028F8F0[0].rep & 0x8000) || (D_0028F8F0[1].rep & 0x8000)) {
            p->f -= step * 0.01f;
            if (p->f < e->min) {
                p->f = e->min;
            } else {
                changed = 1;
            }
        }
        if ((D_0028F8F0[0].rep & 0x2000) || (D_0028F8F0[1].rep & 0x2000)) {
            p->f += step * 0.01f;
            if (e->max < p->f) {
                p->f = e->max;
            } else {
                changed |= 1;
            }
        }
        break;
    case 0:
        if ((D_0028F8F0[0].rep & 0x8000) || (D_0028F8F0[1].rep & 0x8000)) {
            p->i = (float)p->i - step;
            if (p->i < e->min) {
                p->i = e->min;
            } else {
                changed = 1;
            }
        }
        if ((D_0028F8F0[0].rep & 0x2000) || (D_0028F8F0[1].rep & 0x2000)) {
            p->i = (float)p->i + step;
            if (e->max < p->i) {
                p->i = e->max;
            } else {
                changed |= 1;
            }
        }
        break;
    case 2:
        if ((D_0028F8F0[0].rep & 0x8000) || (D_0028F8F0[1].rep & 0x8000)) {
            v = p->s;
            v = (float)v - step;
            if (v < e->min) {
                p->s = e->min;
            } else {
                p->s = v;
                changed = 1;
            }
        }
        if ((D_0028F8F0[0].rep & 0x2000) || (D_0028F8F0[1].rep & 0x2000)) {
            v = p->s;
            v = (float)v + step;
            if (e->max < v) {
                p->s = e->max;
            } else {
                p->s = v;
                changed |= 1;
            }
        }
        break;
    case 3:
        if ((D_0028F8F0[0].rep & 0x8000) || (D_0028F8F0[1].rep & 0x8000)) {
            v = p->us;
            v = (float)v - step;
            if (v < e->min) {
                p->us = e->min;
            } else {
                p->us = v;
                changed = 1;
            }
        }
        if ((D_0028F8F0[0].rep & 0x2000) || (D_0028F8F0[1].rep & 0x2000)) {
            v = p->us;
            v = (float)v + step;
            if (e->max < v) {
                p->us = e->max;
            } else {
                p->us = v;
                changed |= 1;
            }
        }
        break;
    default:
        break;
    }
    if (changed) {
        D_00720070[id] |= 1;
    }
    return (changed && e->step != 0) || (D_0028F8F0[0].trg & 0x20) || (D_0028F8F0[1].trg & 0x20);
}

/* the tool's line colour (r=0, g=0xC0, b=0xFF, a=0x1C) and the dimmed copy the
 * second, blended pass draws with. */
typedef struct {
    int r;
    int g;
    int b;
    int a;
} __attribute__((aligned(16))) EffCol;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) EffVec;

extern EffCol D_004E7860; /* {0, 0xC0, 0xFF, 0x1C} */
extern EffCol D_004E7870; /* {0, 0x20, 0xFF, 0x1C} */
extern EffCol D_004E7880;
extern EffCol D_004E7890;
extern float GetTableSin(short a);
extern float GetTableCos(short a);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);
extern void *memset(void *d, int c, int n);

/* a static helper the PAL listing places at effectTool.c lines 286-289 and
 * inlines into dispXZYZCircle (three times, with three different colours),
 * dispCircle2 and dispEffectToolField; it is not emitted out of line, so it
 * has no MAIN.MAP symbol and this name is ours.  It draws the edge once solid
 * and once with a 1/16 colour over the top. */
static inline void drawEdge(EffVec *p0, EffVec *p1, EffCol *c)
{
    EffCol dim = {c->r >> 4, c->g >> 4, c->b >> 4, c->a};

    DrawLineG(p0, c, p1, c, 0);
    DrawLineG(p0, &dim, p1, &dim, -1);
}

void dispXZYZCircle(float rad, int from, int to, int step)
{
    int i;

    for (i = from; i < to; i += step) {
        EffVec a = {rad * GetTableSin(i), 0.0f, rad * GetTableCos(i), 1.0f};
        EffVec b = {rad * GetTableSin(i + step), 0.0f, rad * GetTableCos(i + step), 1.0f};

        drawEdge(&a, &b, &D_004E7870);
    }
    for (i = from; i < to; i += step) {
        EffVec a = {0.0f, rad * GetTableSin(i), rad * GetTableCos(i), 1.0f};
        EffVec b = {0.0f, rad * GetTableSin(i + step), rad * GetTableCos(i + step), 1.0f};

        drawEdge(&a, &b, &D_004E7880);
    }
    for (i = from; i < to; i += step) {
        EffVec a = {rad * GetTableSin(i), rad * GetTableCos(i), 0.0f, 1.0f};
        EffVec b = {rad * GetTableSin(i + step), rad * GetTableCos(i + step), 0.0f, 1.0f};

        drawEdge(&a, &b, &D_004E7890);
    }
}

void dispCircle2(float rad, short elev, int step)
{
    EffVec o;
    int i;

    memset(&o, 0, sizeof(o));
    o.w = 1.0f;
    for (i = 0; i <= 0xFFFF; i += step) {
        float r = rad * GetTableSin(elev);
        EffVec a = {r * GetTableSin((short)i), r * GetTableCos((short)i), rad * GetTableCos(elev),
                    1.0f};
        EffVec b = {r * GetTableSin((short)(i + step)), r * GetTableCos((short)(i + step)),
                    rad * GetTableCos(elev), 1.0f};

        drawEdge(&a, &b, &D_004E7860);
        drawEdge(&o, &a, &D_004E7860);
    }
}

extern short D_0063B858;
extern short D_0063B85A;
extern void RotQuaternionX(int *self, short y);
extern void RotQuaternionY(int *self, short y);
extern void SetIdentityQuaternion(int *self);

void setQ(int *self)
{
    SetIdentityQuaternion(self);
    RotQuaternionY(self, -D_0063B858);
    RotQuaternionX(self, -D_0063B85A);
}

extern const EffVec D_0061F4C0; /* .rodata: { 0.0f, 0.0f, 100.0f, 1.0f } */
extern char D_0061F4D0[];       /* "POS-X:%4.3f" */
extern char D_0061F4E0[];       /* "POS-Y:%4.3f" */
extern char D_0061F4F0[];       /* "POS-Z:%4.3f" */
extern char D_0061F500[];
extern char D_0061F510[];
extern float D_00720170[];
extern short D_0063B858;
extern short D_0063B85A;
extern int *GetParticleEffectPackage(int id);
extern void gif_StartPacketPri(int pri);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_SetZTest(int on);
extern void gif_EndPacket(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void sceVu0UnitMatrix(void *m);
extern void MultiMatrixByQuaternion(int *q);
extern void dispXZYZCircle(float rad, int a, int b, int step);
extern void dispCircle2(float rad, short elev, int step);
extern double fptodp(float v);
extern void debug_PrintfDummy(int x, int y, unsigned int col, char *fmt, ...);

void dispEffectToolField(int idx)
{
    int q[4];
    EffVec o;
    EffVec e;
    int *pkg = GetParticleEffectPackage(idx);

    setQ(q);
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    gif_SetZTest(1);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(D_00720170[0], D_00720170[1], D_00720170[2]);
    dispXZYZCircle(50.0f, -0x8000, 0x8000, 0x1000);
    MultiMatrixByQuaternion(q);
    dispCircle2(50.0f, (*(unsigned short *)((char *)pkg + 0xC) << 14) / 180, 0x1000);
    dispXZYZCircle(50.0f, -0x8000, 0x8000, 0x1000);

    memset(&o, 0, sizeof(o));
    o.w = 1.0f;
    e = D_0061F4C0;
    drawEdge(&o, &e, &D_004E7860);

    MatrixDrive_PopMatrix();
    gif_EndPacket();
    debug_PrintfDummy(450, 58, 0xFFFFFF00, D_0061F4D0, fptodp(-D_00720170[0]));
    debug_PrintfDummy(450, 66, 0xFFFFFF00, D_0061F4E0, fptodp(-D_00720170[1]));
    debug_PrintfDummy(450, 74, 0xFFFFFF00, D_0061F4F0, fptodp(-D_00720170[2]));
    debug_PrintfDummy(450, 88, 0xFFFFFF00, D_0061F500, fptodp(D_0063B858 * -180.0f / 32768.0f));
    debug_PrintfDummy(450, 96, 0xFFFFFF00, D_0061F510, fptodp(D_0063B85A * -180.0f / 32768.0f));
}

extern float D_00720170[];
extern int D_0063B854;
extern int D_0063B85C;
extern int D_0063B864;
extern int *GetParticleEffectPackage(int id);
extern void ResetParticleEffectPackages(int *pkg);
extern void DeleteParticleEffect(int id);
extern int SetParticleEffect(int id, void *pos, void *quat);
extern int editParam(int id, int sel);

/* two static helpers the PAL listing places at effectTool.c lines 260 and
 * 266-275 and inlines into EditTarget; neither is emitted out of line, so
 * neither has a MAIN.MAP symbol and these names are ours. */
static inline int countEffectParams(void)
{
    int n = 0;
    if (D_004E74A0[0].name != 0) {
        do {
            n++;
        } while (D_004E74A0[n].name != 0);
    }
    return n;
}

static inline void dispEffectParams(int id, int sel)
{
    int n = countEffectParams();
    int *pkg = GetParticleEffectPackage(id);
    int start = sel - 5;
    int i;

    if (start < 0) {
        start = 0;
    }
    if (start + 10 > n) {
        start = n - 10;
    }
    for (i = 0; i < 10 && start + i < n; i++) {
        _dispParam(pkg, start + i, 10, i * 8 + 0x32, (sel == start + i) ? 0x00E0FF00 : 0xFFFFFF00);
    }
}

int EditTarget(int id)
{
    int q[4];
    int n;

    n = countEffectParams();
    setQ(q);
    if (editParam(id, D_0063B864) != 0) {
        ResetParticleEffectPackages(GetParticleEffectPackage(id));
        DeleteParticleEffect(D_0063B854);
        D_0063B854 = SetParticleEffect(D_0063B85C, D_00720170, q);
    }
    dispEffectParams(id, D_0063B864);
    if ((D_0028F8F0[0].rep & 0x1000) || (D_0028F8F0[1].rep & 0x1000)) {
        D_0063B864--;
        if (D_0063B864 < 0) {
            D_0063B864 = n - 1;
        }
    }
    if ((D_0028F8F0[0].rep & 0x4000) || (D_0028F8F0[1].rep & 0x4000)) {
        D_0063B864++;
        if (D_0063B864 == n) {
            D_0063B864 = 0;
        }
    }
    if ((D_0028F8F0[0].trg & 0x40) || (D_0028F8F0[1].trg & 0x40)) {
        return -1;
    }
    return 0;
}

extern char D_0061F530[];
extern char D_0061F570[];
extern char D_0061F598[];
extern char D_0061F5C8[];
extern char D_0061F5D8[];
/* particleEffect.c's effect table is 0x50 bytes per entry: char name[0x20]
   then char file[0x30].  D_0062A298 is &tbl[0].file (D_0062A278 = &tbl[0].name). */
extern char D_0062A298[];
extern int *GetParticleEffectPackage(int id);
extern void debug_closeLog(void);
extern void debug_openLog(void);
extern int debugSceOpen(void *name, int flags);
extern int debugSceClose(int fd);
extern int sceWrite(int fd, void *buf, int size);
extern void debug_StdPrintfDummy(char *fmt, ...);

int saveEffectData(int id)
{
    int *pkg;

    pkg = GetParticleEffectPackage(id);
    debug_closeLog();
    debug_StdPrintfDummy(D_0061F530);
    if (debugSceOpen(D_0062A298 + id * 0x50, 0x602) < 0) {
        debug_StdPrintfDummy(D_0061F570);
    } else {
        debug_StdPrintfDummy(D_0061F598, D_0062A298 + id * 0x50, D_0062A298 + id * 0x50 - 0x20,
                             0xA0);
        debug_StdPrintfDummy(D_0061F5C8, sceWrite(0, pkg, 0xA0));
        debugSceClose(0);
    }
    debug_StdPrintfDummy(D_0061F5D8);
    debug_openLog();
    return 0;
}

extern char iosPadConfDefault[];
extern float D_00720170[];
extern int D_0063B854;

/* iosPadGetStick's output block (camera-ico2.c's IosPadStick, extended): the
 * camera-coord helper reads the two floats at 0xC/0x10 as a1[3]/a1[4]. */
typedef struct {
    int x;         /* 0x00 */
    int y;         /* 0x04 */
    int unk08;     /* 0x08 */
    float fx;      /* 0x0C */
    float fz;      /* 0x10 */
    float mag;     /* 0x14 */
    char unk18[8]; /* 0x18 */
} EffToolStick;

extern int iosPadConnect(void *pad, int slot, int port, void *conf);
extern void iosPadRead(void *pad);
extern int iosPadGetStick(void *pad, EffToolStick *out, int a2, int a3, int a4, int a5);
extern void iosPadStickCameraCoord(void *out, float *stick);
extern int *GetParticleEffectPackage(int id);
extern void SetParticleEffectGeometry(int id, void *pos, void *quat);

void moveEffectToolGeometry(int idx)
{
    float v[4];
    int padCtx[0x60 / 4];
    EffToolStick st0;
    EffToolStick st1;
    int q[4];
    int *pkg;

    iosPadConnect(padCtx, 0, 0, iosPadConfDefault);
    iosPadRead(padCtx);
    iosPadGetStick(padCtx, &st0, 0, 2, 2, 0);
    iosPadGetStick(padCtx, &st1, 1, 2, 2, 0);
    iosPadStickCameraCoord(v, (float *)&st0);
    if (st0.mag > 0.001f) {
        D_00720170[0] += v[0] * st0.mag * 16.0f;
        D_00720170[2] += v[2] * st0.mag * 16.0f;
    }
    if (st1.mag > 0.001f) {
        if (padCtx[2] & 2) {
            D_00720170[1] += st1.fz * st1.mag * 16.0f;
        } else {
            D_0063B858 = D_0063B858 + st1.fx * 256.0f * st1.mag;
            D_0063B85A = D_0063B85A + st1.fz * 256.0f * st1.mag;
            if (D_0063B85A < -0x4000) {
                D_0063B85A = -0x4000;
            }
            if (D_0063B85A > 0x4000) {
                D_0063B85A = 0x4000;
            }
        }
    }
    pkg = GetParticleEffectPackage(idx);
    if (pkg[1] != 0) {
        setQ(q);
        SetParticleEffectGeometry(D_0063B854, D_00720170, q);
    }
}

extern char D_0061F618[];
extern char D_0062A278[];
extern float D_00720170[];
extern int targetMemo;
extern int D_0063B854;
extern int D_0063B85C;
extern int D_0063B860;
extern int D_0063B864;
extern int D_0063B868;
extern int debug_SelectCsvWindow(char *title, int a1, int a2, int a3, void *tbl, int stride, int a6,
                                 int a7, int count, int *cur);
extern void DeleteParticleEffect(int id);
extern int SetParticleEffect(int id, void *pos, void *quat);
extern int EditTarget(int idx);
extern void moveEffectToolGeometry(int idx);
extern void dispEffectToolField(int idx);
extern int saveEffectData(int idx);

int execEffectTool(void)
{
    int q[4];
    int r;

    switch (targetMemo) {
    default:
    case 0:
        r = debug_SelectCsvWindow(D_0061F618, 10, 0x32, 0xB, D_0062A278, 0x50, 0, 0, 0x3D,
                                  &D_0063B85C);
        if (D_0063B85C != D_0063B860) {
            setQ(q);
            if (D_0063B854 != -1) {
                DeleteParticleEffect(D_0063B854);
            }
            D_0063B854 = SetParticleEffect(D_0063B85C, D_00720170, q);
            D_0063B860 = D_0063B85C;
            D_0063B864 = 0;
        }
        if (D_0028F8F0[1].trg & 0x10) {
            saveEffectData(D_0063B85C);
        }
        if (D_0028F8F0[1].trg & 0x20) {
            r = 1;
        }
        if (D_0028F8F0[1].rep & 0x1000) {
            D_0063B85C--;
            if (D_0063B85C < 0) {
                D_0063B85C = 0x3C;
            }
        }
        if (D_0028F8F0[1].rep & 0x4000) {
            D_0063B85C++;
            if (D_0063B85C >= 0x3D) {
                D_0063B85C = 0;
            }
        }
        if (r == 1) {
            r = 0;
            targetMemo++;
        }
        break;
    case 1:
        r = EditTarget(D_0063B85C);
        if (r == -1) {
            targetMemo--;
        }
        r = 0;
        break;
    }
    moveEffectToolGeometry(D_0063B85C);
    if ((D_0028F8F0[0].trg & 0x80) || (D_0028F8F0[1].trg & 0x80)) {
        D_0063B868 = (D_0063B868 == 0);
    }
    if (D_0063B868) {
        dispEffectToolField(D_0063B85C);
    }
    return r;
}

extern void Camctrl_SetTarget(int x, int y, int z);
extern int D_0063AA08;
extern int D_0063B854;
extern int D_0063B86C;
extern char D_0063B878[];
extern void DeleteParticleEffect(int x);
extern void debug_StdPrintfDummy(char *fmt, ...);

void exitEffectTool(void)
{
    DeleteParticleEffect(D_0063B854);
    D_0063B854 = -1;
    Camctrl_SetTarget(D_0063B86C, 0, 3);
    D_0063AA08 = 0;
    debug_StdPrintfDummy(D_0063B878);
}

extern char D_0061F520[];
extern float D_00720170[];
extern int D_00720070[];
extern int D_0063B880;
extern int D_0063B868;
extern int D_0063B860;
extern int D_0063B864;
extern int CameraGetTarget(void);
extern void GetRootPosition(void *dst, int gobj);
extern void GetRootQuaternion(void *dst, int gobj);
extern void CameraSetMode(int mode);
extern int execEffectTool(void);

/* static helper the PAL listing places at effectTool.c lines 403-415 and
 * inlines at the head of EffectTool; never emitted out of line, so it has no
 * MAIN.MAP symbol and this name is ours. */
static inline void initEffectTool(void)
{
    int q[4];
    int i;

    setQ(q);
    D_0063B86C = CameraGetTarget();
    GetRootPosition(D_00720170, D_0063B86C);
    D_00720170[3] = 1.0f;
    GetRootQuaternion(q, D_0063B86C);
    CameraSetMode(1);
    D_0063AA08 = 1;
    debug_StdPrintfDummy(D_0061F520);
    for (i = 0x3C; i >= 0; i--) {
        D_00720070[i] = 0;
    }
}

int EffectTool(void)
{
    int r;

    if (D_0063B880 == 0) {
        initEffectTool();
        D_0063B880 = 1;
        D_0063B868 = 1;
    }
    r = execEffectTool();
    if (r == -1) {
        exitEffectTool();
        D_0063B880 = 0;
        D_0063B860 = r;
        D_0063B864 = 0;
    }
    return r;
}
