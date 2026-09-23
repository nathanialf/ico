#include "common.h"
#include "effectTool.h"
#include "pad.h"
#include "camera-root.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "particleEffect.h"
#include "tableSin.h"
#include <stdio.h>
#include <libvu0.h>
#include <sifdev.h>
#include "geometryManager.h"

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

/* the three enum name tables the type-0 fields print through; the names
   themselves are seven bytes or fewer, so the compiler puts them in .sdata,
   which this pass does not carve: they stay extern into the .sdata blob. */
extern char D_0063B7D8[]; /* "LOOP" */
extern char D_0063B7E0[]; /* "RELEASE" */
extern char D_0063B7E8[]; /* "SUB" */
extern char D_0063B7F0[]; /* "ADD" */
extern char D_0063B7F8[]; /* "BLEND" */
extern char D_0063B800[]; /* "ON" */
extern char D_0063B808[]; /* "OFF" */
extern char D_0063B810[]; /* "COLOR B" */
extern char D_0063B818[]; /* "COLOR G" */
extern char D_0063B820[]; /* "COLOR R" */

static char *drainTypeName[] = {D_0063B7E0, D_0063B7D8};

static char *alphaTypeName[] = {D_0063B7F8, D_0063B7F0, D_0063B7E8};

static char *upperLimitName[] = {D_0063B808, D_0063B800};

static EffParamDef effParam[] = {
    {"U OFFSET", 0x80, 0, 0, 0, 0, 3},
    {"V OFFSET", 0x84, 0, 0, 0, 0, 3},
    {"DRAIN TYPE", 4, drainTypeName, 0, 1, 0, 1},
    {"ALPHA TYPE", 8, alphaTypeName, 0, 0, 0, 2},
    {"CONE ANGLE", 12, 0, 3, 0, 0, 360},
    {"WIND EFFECT", 0x90, 0, 1, 0, 0, 10},
    {"VELOCITY", 16, 0, 1, 0, 0, 100},
    {"VEL RND RATIO", 20, 0, 1, 0, 0, 1},
    {"VEL ACCEL    ", 24, 0, 1, 0, 0, 2},
    {"GRAVITY ACC", 28, 0, 1, 0, -10, 10},
    {"ROT BASE", 0x88, 0, 2, 0, -180, 180},
    {"ROT BASE RND", 0x8C, 0, 1, 0, 0, 1},
    {"ROT GROW", 32, 0, 2, 0, -180, 180},
    {"ROT GROW RND", 36, 0, 1, 0, 0, 1},
    {"ROT GROW ACC", 40, 0, 1, 0, 0, 2},
    {"SIZE BASE", 44, 0, 1, 0, 0, 50},
    {"SIZE BASE RND", 48, 0, 1, 0, 0, 1},
    {"SIZE GROW", 52, 0, 1, 0, -50, 50},
    {"SIZE GROW RND", 56, 0, 1, 0, 0, 1},
    {"SIZE GROW ACC", 60, 0, 1, 0, 0, 1},
    {"NB POLYGONS", 64, 0, 0, 1, 1, 80},
    {"LIFE SPAN", 68, 0, 0, 0, 0, 1000},
    {"LIFE SPAN RND", 72, 0, 1, 0, 0, 1},
    {"BIRTH RATE", 76, 0, 1, 0, 0, 100},
    {"FADE BASE", 80, 0, 1, 0, 0, 1},
    {"FADE BASE RND", 84, 0, 1, 0, 0, 1},
    {"FADE OUT", 88, 0, 0, 0, 0, 1000},
    {"FADE OUT RND", 92, 0, 1, 0, 0, 1},
    {D_0063B820, 0x70, 0, 0, 0, 0, 255},
    {D_0063B818, 0x74, 0, 0, 0, 0, 255},
    {D_0063B810, 0x78, 0, 0, 0, 0, 255},
    {"UPPER LIMIT", 0x94, upperLimitName, 0, 0, 0, 1},
    {"LIMIT HEIGHT", 0x98, 0, 0, 0, -100000, 100000},
    {0},
};

extern char D_0063B828[]; /* "%4.3f" */
extern char D_0063B830[]; /* "(%d,%d)" */
extern char D_0063B838[]; /* "%d" */
extern char D_0063B840[]; /* "%s" */
extern char D_0063B848[]; /* "%s%s" */
/* kept local: this TU's uses of debug_PrintfDummy do not fit the prototype in debug.h */
extern void debug_PrintfDummy(int x, int y, unsigned int col, char *fmt, ...);

void _dispParam(int *pkg, int idx, int x, int y, int col)
{
    char lbl[256];
    char val[256];
    char rng[256];
    char *p = (char *)pkg + effParam[idx].off;
    EffParamDef *e = &effParam[idx];

    switch (e->type) {
    case 1:
        sprintf(val, D_0063B828, *(float *)p);
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
        sprintf(val, "Unknown Data Type \"%s\"\n", e->name);
        break;
    }
    sprintf(lbl, D_0063B848, e->name, rng);
    debug_PrintfDummy(x, y, col, "%-20s:%s", lbl, val);
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

/* .bss, owned by effectTool.o and reached only from this file (MAIN.MAP names
   no symbol in the run), in the ROM's run order: a change flag per tool row,
   then the position the tool's effect is placed at. */
static int effectToolDirty[64];

static float effectToolPos[4];

int editParam(int id, int sel)
{
    EffParamDef *e = &effParam[sel];
    int *pkg = GetParticleEffectPackage(id);
    EffVal *p = (EffVal *)((char *)pkg + effParam[sel].off);
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
        effectToolDirty[id] |= 1;
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

/* the effect tool's own line colour and the three axis-circle colours the
   XZ/YZ/XY passes draw with; drawEdge draws each once solid and once at a
   sixteenth over the top. */
static EffCol effectToolColor = {0x00, 0xC0, 0xFF, 0x1C};

static EffCol circleColorXZ = {0x00, 0x20, 0xFF, 0x1C};

static EffCol circleColorYZ = {0xFF, 0x00, 0x20, 0x1C};

static EffCol circleColorXY = {0x00, 0xFF, 0x20, 0x1C};

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

        drawEdge(&a, &b, &circleColorXZ);
    }
    for (i = from; i < to; i += step) {
        EffVec a = {0.0f, rad * GetTableSin(i), rad * GetTableCos(i), 1.0f};
        EffVec b = {0.0f, rad * GetTableSin(i + step), rad * GetTableCos(i + step), 1.0f};

        drawEdge(&a, &b, &circleColorYZ);
    }
    for (i = from; i < to; i += step) {
        EffVec a = {rad * GetTableSin(i), rad * GetTableCos(i), 0.0f, 1.0f};
        EffVec b = {rad * GetTableSin(i + step), rad * GetTableCos(i + step), 0.0f, 1.0f};

        drawEdge(&a, &b, &circleColorXY);
    }
}

void dispCircle2(float rad, short elev, int step)
{
    EffVec o;
    int i;

    memset(&o, 0, sizeof(o));
    o.w = 1.0f;
    for (i = 0; i <= 65535; i += step) {
        float r = rad * GetTableSin(elev);
        EffVec a = {r * GetTableSin((short)i), r * GetTableCos((short)i), rad * GetTableCos(elev),
                    1.0f};
        EffVec b = {r * GetTableSin((short)(i + step)), r * GetTableCos((short)(i + step)),
                    rad * GetTableCos(elev), 1.0f};

        drawEdge(&a, &b, &effectToolColor);
        drawEdge(&o, &a, &effectToolColor);
    }
}

extern short D_0063B858;
extern short D_0063B85A;
/* kept local: this TU's uses of RotQuaternionX do not fit the prototype in quaternion.h */
extern void RotQuaternionX(int *self, short y);
/* kept local: this TU's uses of RotQuaternionY do not fit the prototype in quaternion.h */
extern void RotQuaternionY(int *self, short y);
/* kept local: this TU's uses of SetIdentityQuaternion do not fit the prototype in quaternion.h */
extern void SetIdentityQuaternion(int *self);

void setQ(int *self)
{
    SetIdentityQuaternion(self);
    RotQuaternionY(self, -D_0063B858);
    RotQuaternionX(self, -D_0063B85A);
}

/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a, int b, int c);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int on);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of MultiMatrixByQuaternion do not fit the prototype in quaternion.h */
extern void MultiMatrixByQuaternion(int *q);

void dispEffectToolField(int idx)
{
    int q[4];
    EffVec o;
    int *pkg = GetParticleEffectPackage(idx);

    setQ(q);
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    gif_SetZTest(1);
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(effectToolPos[0], effectToolPos[1], effectToolPos[2]);
    dispXZYZCircle(50.0f, -0x8000, 0x8000, 0x1000);
    MultiMatrixByQuaternion(q);
    dispCircle2(50.0f, (*(unsigned short *)((char *)pkg + 0xC) << 14) / 180, 0x1000);
    dispXZYZCircle(50.0f, -0x8000, 0x8000, 0x1000);

    memset(&o, 0, sizeof(o));
    o.w = 1.0f;
    /* the 100-unit +Z spoke drawn out of the origin.  The ROM copies its
       16-byte template out of .rodata here, at the call, not at function
       entry, and the template sits between this file's string constants
       rather than in a section of its own; an initialised local in its own
       scope is the form that reproduces both. */
    {
        EffVec e = {0.0f, 0.0f, 100.0f, 1.0f};

        drawEdge(&o, &e, &effectToolColor);
    }

    MatrixDrive_PopMatrix();
    gif_EndPacket();
    debug_PrintfDummy(450, 58, 0xFFFFFF00, "POS-X:%4.3f", -effectToolPos[0]);
    debug_PrintfDummy(450, 66, 0xFFFFFF00, "POS-Y:%4.3f", -effectToolPos[1]);
    debug_PrintfDummy(450, 74, 0xFFFFFF00, "POS-Z:%4.3f", -effectToolPos[2]);
    debug_PrintfDummy(450, 88, 0xFFFFFF00, "ROT-Y:%4.3f", D_0063B858 * -180.0f / 32768.0f);
    debug_PrintfDummy(450, 96, 0xFFFFFF00, "ROT-X:%4.3f", D_0063B85A * -180.0f / 32768.0f);
}

extern int D_0063B854;
extern int D_0063B85C;
extern int D_0063B864;

/* two static helpers the PAL listing places at effectTool.c lines 260 and
 * 266-275 and inlines into EditTarget; neither is emitted out of line, so
 * neither has a MAIN.MAP symbol and these names are ours. */
static inline int countEffectParams(void)
{
    int n = 0;
    if (effParam[0].name != 0) {
        do {
            n++;
        } while (effParam[n].name != 0);
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
        D_0063B854 = SetParticleEffect(D_0063B85C, effectToolPos, q);
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

extern int D_0063AA08;
extern int D_0063B86C;
/* kept local: this TU's uses of debug_StdPrintfDummy do not fit the prototype in debug.h */
extern void debug_StdPrintfDummy(char *fmt, ...);

/* static helper the PAL listing places at effectTool.c lines 403-415 and
 * inlines at the head of EffectTool; never emitted out of line, so it has no
 * MAIN.MAP symbol and this name is ours. */
static inline void initEffectTool(void)
{
    int q[4];
    int i;

    setQ(q);
    D_0063B86C = CameraGetTarget();
    GetRootPosition(effectToolPos, D_0063B86C);
    effectToolPos[3] = 1.0f;
    GetRootQuaternion(q, D_0063B86C);
    CameraSetMode(1);
    D_0063AA08 = 1;
    debug_StdPrintfDummy("initialize\n");
    for (i = 0x3C; i >= 0; i--) {
        effectToolDirty[i] = 0;
    }
}

/* particleEffect.c's effect table is 0x50 bytes per entry: char name[0x20]
   then char file[0x30].  D_0062A298 is &tbl[0].file (D_0062A278 = &tbl[0].name). */
extern char D_0062A298[];
/* kept local: this TU's uses of debug_closeLog do not fit the prototype in debug.h */
extern void debug_closeLog(void);
/* kept local: this TU's uses of debug_openLog do not fit the prototype in debug.h */
extern void debug_openLog(void);
/* kept local: this TU's uses of debugSceOpen do not fit the prototype in debug.h */
extern int debugSceOpen(void *name, int flags);
/* kept local: this TU's uses of debugSceClose do not fit the prototype in debug.h */
extern int debugSceClose(int fd);

int saveEffectData(int id)
{
    int *pkg;

    pkg = GetParticleEffectPackage(id);
    debug_closeLog();
    debug_StdPrintfDummy("==== Save effect ============================================\n");
    if (debugSceOpen(D_0062A298 + id * 0x50, 0x602) < 0) {
        debug_StdPrintfDummy("saveEffectData: host file open error.\n");
    } else {
        debug_StdPrintfDummy("Save effect file [\033[36m%s\033[m](%s:%dbytes) \n",
                             D_0062A298 + id * 0x50, D_0062A298 + id * 0x50 - 0x20, 0xA0);
        debug_StdPrintfDummy("%d bytes wrote\n", sceWrite(0, pkg, 0xA0));
        debugSceClose(0);
    }
    debug_StdPrintfDummy("=============================================================\n");
    debug_openLog();
    return 0;
}

extern char iosPadConfDefault[];

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
        effectToolPos[0] += v[0] * st0.mag * 16.0f;
        effectToolPos[2] += v[2] * st0.mag * 16.0f;
    }
    if (st1.mag > 0.001f) {
        if (padCtx[2] & 2) {
            effectToolPos[1] += st1.fz * st1.mag * 16.0f;
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
        SetParticleEffectGeometry(D_0063B854, effectToolPos, q);
    }
}

extern char D_0062A278[];
extern int targetMemo;
extern int D_0063B860;
extern int D_0063B868;
/* kept local: this TU's uses of debug_SelectCsvWindow do not fit the prototype in debug.h */
extern int debug_SelectCsvWindow(char *title, int a1, int a2, int a3, void *tbl, int stride, int a6,
                                 int a7, int count, int *cur);

int execEffectTool(void)
{
    int q[4];
    int r;

    switch (targetMemo) {
    default:
    case 0:
        r = debug_SelectCsvWindow("Effect Tools: PUSH 2-CON'\202' TO SAVE SELECTED DATA", 10, 0x32,
                                  0xB, D_0062A278, 0x50, 0, 0, 0x3D, &D_0063B85C);
        if (D_0063B85C != D_0063B860) {
            setQ(q);
            if (D_0063B854 != -1) {
                DeleteParticleEffect(D_0063B854);
            }
            D_0063B854 = SetParticleEffect(D_0063B85C, effectToolPos, q);
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

extern char D_0063B878[];

void exitEffectTool(void)
{
    DeleteParticleEffect(D_0063B854);
    D_0063B854 = -1;
    Camctrl_SetTarget(D_0063B86C, 0, 3);
    D_0063AA08 = 0;
    debug_StdPrintfDummy(D_0063B878);
}

extern int D_0063B880;

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
