#include "debug.h"
#include "memory.h"
#include "camera-root.h"
#include "Basic.h"
#include "Light.h"
#include "geometryManager.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include <math.h>
#include <string.h>
#include <libvu0.h>
#include "ios.h"
#include "Matrix.h"
#include "Primitive.h"
#include "debug_exception.h"
#include "wireLetter.h"
#include "main.h"
#include "GifPacket.h"

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

/* .sbss, Light.o's five words in the ROM's order (MAIN.MAP line 7576 sizes
   the run 0x14 and names no symbol in it, so the names are ours): the cursor
   debug view's two pad angles, the newest light and the newest ambient volume
   (each list is walked back through prev), and the light count the retail
   build no longer increments. */
static int cursorRotY;

static int cursorRotX;

static int lastLight;

static int lastAmbient;

static int lightCount;

/* .sdata, Light.o's run (MAIN.MAP line 6990, 0x5D, no symbol named): the
   count of flat lights light_AddLight has registered, which light_resetFlatLight
   clears; the assert text and the debug menu's labels follow as literals and
   the flat-light editor's cursor after the object menu. */
static int flatLightNum = 0; /* derived name */

extern void __assert(char *file, int line, char *expr);

void light_killLinkLight(char *node)
{
    Light *p = (Light *)node;

    if (p == 0) {
        /* "the light is NULL" */
        debug_StdPrintfDummy("Light:NULLになってんで\n");
        debug_assert("src/Light.c", 424);
        __assert("src/Light.c", 424, "0");
    }
    if (p->next != 0) {
        p->next->prev = p->prev;
    } else {
        lastLight = (int)p->prev;
    }
    if (p->prev != 0) {
        p->prev->next = p->next;
    }
    if (lastLight != 0) {
        ((Light *)lastLight)->next = 0;
    }
    freeseki(p);
}

void light_killLinkAmbient(AmbientVolume *p)
{
    if (p == 0) {
        /* "the ambient volume is NULL" */
        debug_StdPrintfDummy("AmbientVolume:NULLになってんで\n");
        debug_assert("src/Light.c", 451);
        __assert("src/Light.c", 451, "0");
    }
    if (p->next != 0) {
        p->next->prev = p->prev;
    } else {
        lastAmbient = (int)p->prev;
    }
    if (p->prev != 0) {
        p->prev->next = p->next;
    }
    if (lastAmbient != 0) {
        ((AmbientVolume *)lastAmbient)->next = 0;
    }
    freeseki(p);
}

/* .data, owned by Light.o and read only here (MAIN.MAP names no symbol in the
   run).  The three flat lights light_AddLight registers, kept so
   light_resetFlatLight can reload them from the stage setting. */
static int flatLightSlot[3] = {0, 0, 0};

/* .bss, owned by Light.o and reached only from this file (MAIN.MAP names no
   symbol in the run; its Light.o .bss size 0xF0 is exactly these three).  The
   three flat lights the stage setting is reloaded into. */
static Light flatLight[3];

extern float D_005D3DC8[][4];

/* Light.c lines 382-391: the list head keeps the newest node.  Line 391's
   counter update is a debug arm the retail build compiles out (the
   January-2002 listing still has it, three expansions, nine instructions). */
static inline void light_setLinkLight(Light *p)
{
    if (lastLight != 0) {
        ((Light *)lastLight)->next = p;
    }
    p->next = 0;
    p->prev = (Light *)lastLight;
    lastLight = (int)p;
}

Light *light_AddLight(char *self, int b, int kind)
{
    int i;
    float d;
    float *t;

    switch (kind) {
    case 0: {
        Light *l;

        if (flatLightNum != 0) {
            debug_StdPrintfDummy("Flat Lights already exist.\n");
            light_resetFlatLight();
            return 0;
        }
        for (i = 0; i < 3; i++) {
            l = &flatLight[i];
            _CopyVector(l->f_20, GlobalStageSetting.flatLightCol[i]);
            _NormalizeVector(l->f_10, GlobalStageSetting.flatLightDir[i]);
            l->f_30 = 1.0f;
            l->f_34 = 0.0f;
            l->f_38 = 1.0f;
            d = (l->f_20[0] + l->f_20[1] + l->f_20[2]) * 0.3333f;
            if (d < 0.0f) {
                d = -d;
            }
            l->f_3C = d;
            light_setLinkLight(l);
            flatLightSlot[(flatLightNum)++] = (int)l;
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
        q = (Light *)iosMallocDebug(ios_partition_seki, 0x50, "src/Light.c", 620);
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

        r = (Light *)iosMallocDebug(ios_partition_seki, 0x50, "src/Light.c", 685);
        r->f_44 = kind;
        r->f_30 = 1.0f;
        r->f_34 = 32768.0f;
        light_setLinkLight(r);
        return r;
    }
    default:
        debug_StdPrintfDummy("Added Light is illegal.\n");
        debug_assert("src/Light.c", 705);
        __assert("src/Light.c", 705, "0");
    }
    return 0;
}

/* Listing rows 754-964.  The January listing's rows 877-881 (a flag-guarded
   copy of near[] and its weights into two debug arrays) are absent from the
   retail build.  Each switch arm writes its own abs and weight store and
   jump.c cross-jumps the copies (listing lines 802, 841-842); the range tests
   are nested ifs, since an && pair folds into one unsigned compare where the
   ROM keeps bltz and slti. */
void light_getNearLight(char *self, int idx)
{
    Light *near[3];
    float pos[4];
    float dir[4];
    float tmp[4];
    Light *p;
    float d;
    int i;
    int j;
    int k;

    memset(dir, 0, 16);
    if (lastLight == 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        near[i] = 0;
    }
    if (*(unsigned short *)(self + 0x84C) == 2) {
        _CopyVector(pos, *(char **)(self + 0xC) + idx * 0x40 + 0x30);
    } else {
        _CopyVector(pos, *(char **)(self + 0xC) + 0x30);
    }
    for (p = (Light *)lastLight; p != 0; p = p->prev) {
        switch (p->f_44) {
        case 0:
            p->f_30 = 1.0f;
            p->f_34 = 0.0f;
            p->f_38 = 1.0f;
            d = (p->f_20[0] + p->f_20[1] + p->f_20[2]) * 0.3333f;
            if (d < 0.0f) {
                d = -d;
            }
            p->f_3C = d;
            break;
        case 1:
            /* Listing line 805 reads the dobj's light number and 806 tests
               it.  The ROM keeps that word in $6, the insert loop's index
               register, so it is the same variable as j (gcc 2.9 gives one
               variable one allocno); the bytes pin the sharing, not the
               name.  GetRootPositionByDObj takes the dobj as its second
               argument (geometryManager.c), already in $5 from the test. */
            j = *(int *)(*(int *)(p->f_40 + 0x15C) + 0x83C);
            if (j == 0) {
                p->f_38 = 0.0f;
                p->f_3C = 0.0f;
                continue;
            }
            GetRootPositionByDObj(p, *(char **)(p->f_40 + 0x15C));
            d = _GetLength(pos, p);
            if (p->f_34 < d) {
                p->f_38 = 0.0f;
                p->f_3C = 0.0f;
                continue;
            }
            p->f_38 = (p->f_34 - d) / p->f_34;
            d = p->f_38 * p->f_30 * ((p->f_20[0] + p->f_20[1] + p->f_20[2]) * 0.3333f);
            if (d < 0.0f) {
                d = -d;
            }
            p->f_3C = d;
            break;
        case 2:
        case 3:
            d = _GetLength(pos, p);
            if (p->f_34 < d) {
                p->f_38 = 0.0f;
                p->f_3C = 0.0f;
                continue;
            }
            p->f_38 = (p->f_34 - d) / p->f_34;
            d = p->f_38 * p->f_30 * ((p->f_20[0] + p->f_20[1] + p->f_20[2]) * 0.3333f);
            if (d < 0.0f) {
                d = -d;
            }
            p->f_3C = d;
            break;
        default:
            continue;
        }
    }
    for (p = (Light *)lastLight; p != 0; p = p->prev) {
        if (p->f_3C == 0.0f) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            if (near[j] == 0 || near[j]->f_3C < p->f_3C) {
                for (k = 2; k > j; k--) {
                    near[k] = near[k - 1];
                }
                near[j] = p;
                break;
            }
        }
    }
    for (p = (Light *)lastLight; p != 0; p = p->prev) {
        if (p->f_3C == 0.0f) {
            continue;
        }
        if (p->f_44 == 0) {
            _ScaleVectorXYZ(tmp, p->f_10, p->f_3C);
            _AddVector(dir, dir, tmp);
        } else if (p->f_44 >= 0) {
            if (p->f_44 < 3) {
                _SubVector(tmp, pos, p);
                _NormalizeVector(tmp, tmp);
                _ScaleVectorXYZ(tmp, tmp, p->f_3C);
                _AddVector(dir, dir, tmp);
            }
        }
    }
    _NormalizeVector(self + 0x860, dir);
    for (i = 0; i < 3; i++) {
        if (near[i] != 0) {
            if (near[i]->f_44 == 0) {
                _NormalizeVector(((LightMatrix *)*(char **)(self + 0x874))->dir[i], near[i]->f_10);
                _CopyVector(((LightMatrix *)*(char **)(self + 0x874))->col[i], near[i]->f_20);
            } else if (near[i]->f_44 >= 0) {
                if (near[i]->f_44 < 4) {
                    _SubVector(((LightMatrix *)*(char **)(self + 0x874))->dir[i], pos, near[i]);
                    _NormalizeVector(((LightMatrix *)*(char **)(self + 0x874))->dir[i],
                                     ((LightMatrix *)*(char **)(self + 0x874))->dir[i]);
                    _ScaleVectorXYZ(((LightMatrix *)*(char **)(self + 0x874))->col[i],
                                    near[i]->f_20, near[i]->f_38 * near[i]->f_30);
                }
            }
        } else {
            _UnitVector(((LightMatrix *)*(char **)(self + 0x874))->dir[i]);
            _UnitVector(((LightMatrix *)*(char **)(self + 0x874))->col[i]);
        }
        ((LightMatrix *)*(char **)(self + 0x874))->dir[i][3] = 0.0f;
        ((LightMatrix *)*(char **)(self + 0x874))->col[i][3] = 1.0f;
    }
}

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
    if (lastAmbient == 0) {
        _CopyVector(*(char **)(a + 0x874) + 0xE0, GlobalStageSetting.ambientCol);
        return;
    }
    _CopyVector(*(char **)(a + 0x874) + 0xE0, GlobalStageSetting.ambientCol);
    best = 3.0f;
    if (*(unsigned short *)(a + 0x84C) == 2) {
        _CopyVector(pos, *(char **)(a + 0xC) + (b << 6) + 0x30);
    } else {
        _CopyVector(pos, *(char **)(a + 0xC) + 0x30);
    }
    for (v = (AmbientVolume *)lastAmbient; v != 0; v = v->prev) {
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
                _SubVectorXYZ(s0, GlobalStageSetting.ambientCol, v->f_40);
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
                _SubVectorXYZ(s1, GlobalStageSetting.ambientCol, v->f_40);
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

/* Light.c lines 1200-1373.  The January-2002 listing carries two debug arms
   the retail build does not: a kind-0 search of the three editor slots
   (rows 1211-1217), the same search again before the packet (rows 1241-1258)
   and the ambient volume's selected-slot blink and print (rows 1323-1324,
   1363-1364).  Retail keeps neither, so the slot search that sets `i` in the
   listing is gone and the test below reads what the previous light left in
   it: the ROM's `li 3` in the gif_EndPacket delay slot is loop.c's final
   value for the reversed three-step loop, emitted because `i` is still live
   out of the loop through the back edge.
   Both lists are walked as `p = head; while (p != 0) { ...; p = p->prev; }`
   (rows 1202/1203 and 1307/1309, 1313/1314 and 1370/1372: the step is a body
   statement and the bottom test carries the closing brace's line).  The first
   block's arrays are declared in its `if` block, so they are freed when it
   ends and the ambient loop's colour and extents re-take the frame base (the
   ROM's sp+0 and sp+0x10); a `for` would expand its step at the arrays' own
   level after their addresses were taken, and stmt.c's preserve_temp_slots
   would then keep them for the whole function (measured, frame 0x280).
   Row 1315 is one declaration: the ambient colour is built by its
   initializer in a temporary (the three conversions, the 128 and the ld/sd
   copy all sit on that row), and the temporary is the slot the extents
   re-take. */

/* kept local: int (char *, char *, ...) here, int (void *, int, ...) in stdio.h */
extern int sprintf(char *buf, char *fmt, ...);

void light_DispVolume(void)
{
    int i;

    if (debug_ambient_volume & 1) {
        sceVu0FMATRIX m;
        char buf[256];
        int col[4];
        int black[4];
        int dir[4];
        float pos[4];
        float p0[4];
        float p1[4];
        Light *lp;

        lp = (Light *)lastLight;
        while (lp != 0) {
            switch (lp->f_44) {
            case 1:
                if (lp == 0) {
                    break;
                }
                if (lp->f_40 == 0) {
                    break;
                }
                if (*(int *)(*(char **)(lp->f_40 + 0x15C) + 0x83C) == 0) {
                    break;
                }
            case 2:
            case 3:
                if (lp->f_34 == 0.0f) {
                    break;
                }
                _UnitMatrix(MatrixDrive_GetMatrix());
                _CopyVector((char *)MatrixDrive_GetMatrix() + 0x30, lp);
                _TransposeMatrix(m, matrixptr + 0x80);
                m[0][3] = m[1][3] = m[2][3] = 0.0f;
                _MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), m);
                if (lp->f_44 == 1) {
                    sprintf(buf, "OBJ");
                } else {
                    sprintf(buf, "FIX");
                }
                DispWireString(buf);
                gif_StartPacketPri(11);
                col[0] = lp->f_20[0] * 255.0f;
                col[1] = lp->f_20[1] * 255.0f;
                col[2] = lp->f_20[2] * 255.0f;
                col[3] = 128;
                black[0] = black[1] = black[2] = 0;
                black[3] = 128;
                _UnitMatrix(MatrixDrive_GetMatrix());
                _CopyVector((char *)MatrixDrive_GetMatrix() + 0x30, lp);
                gif_SetZTest(1);
                gif_SetAlpha(1, 2, 64);
                prim_DispWireSphere(lp->f_34 * 0.1f, col, 6, 6);
                if (i != 0) {
                    GetRootPosition(pos, boyGObj);
                    _SubVector(pos, pos, lp);
                    pos[3] = 1.0f;
                    _NormalizeVector(pos, pos);
                    _ScaleVectorXYZ(pos, pos, lp->f_34);
                    _UnitVector(dir);
                    DrawLineG(dir, col, pos, black, 0);
                }
                for (i = 0; i < 3; i++) {
                    _UnitVector(p0);
                    _UnitVector(p1);
                    p0[i] -= lp->f_34;
                    p1[i] += lp->f_34;
                    p0[3] = p1[3] = 1.0f;
                    DrawLineG(p0, col, p1, col, 0);
                }
                gif_EndPacket();
                break;
            }
            lp = lp->prev;
        }
    }
    if (debug_ambient_volume & 2) {
        AmbientVolume *av;

        av = (AmbientVolume *)lastAmbient;
        while (av != 0) {
            Col4 col = {{av->f_40[0] * 255.0f, av->f_40[1] * 255.0f, av->f_40[2] * 255.0f, 128}};
            float ext[4];

            /* Row 1316.  The null test folds away (the loop test already
               proved av), but as a loop exit it is what makes stmt.c's
               expand_end_loop roll the colour with the loop test, so jump.c
               copies both above the loop: the ROM's two colour blocks.  The
               bytes pin a loop exit after the initializer and before the
               switch, not its spelling; the same function re-tests its
               light pointer the same way in case 1 of the first loop, where
               the test survives.  Without it the copy is gone (362 of 380). */
            if (av == 0) {
                break;
            }
            switch (av->f_90) {
            case 2:
                _SetCurrentMatrix(av);
                _ScaleCurrentMatrix(1.0f / av->f_70[0], 1.0f / av->f_70[1], 1.0f / av->f_70[2]);
                _GetCurrentMatrix(MatrixDrive_GetMatrix());
                gif_StartPacketPri(11);
                gif_SetZTest(1);
                gif_SetAlpha(1, 2, 64);
                prim_DispWireSphere(1.0f / av->f_60[0], &col, 6, 6);
                prim_DispWireSphere(1.0f / av->f_50[0], &col, 6, 6);
                gif_EndPacket();
                break;
            case 1:
                _SetCurrentMatrix(av);
                _ScaleCurrentMatrix(1.0f / av->f_70[0], 1.0f / av->f_70[1], 1.0f / av->f_70[2]);
                _GetCurrentMatrix(MatrixDrive_GetMatrix());
                gif_StartPacketPri(11);
                gif_SetZTest(1);
                gif_SetAlpha(1, 2, 64);
                ext[0] = 1.0f / av->f_50[0];
                ext[1] = 1.0f / av->f_50[1];
                ext[2] = 1.0f / av->f_50[2];
                prim_DispWireBox(ext, &col);
                ext[0] = 1.0f / av->f_60[0];
                ext[1] = 1.0f / av->f_60[1];
                ext[2] = 1.0f / av->f_60[2];
                prim_DispWireBox(ext, &col);
                gif_EndPacket();
                break;
            }
            av = av->prev;
        }
    }
}

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
        l = (Light *)flatLightSlot[i];
        if (l != 0) {
            _CopyVector(l->f_20, GlobalStageSetting.flatLightCol[i]);
            _NormalizeVector(l->f_10, GlobalStageSetting.flatLightDir[i]);
            l->f_30 = 1.0f;
            l->f_34 = 0.0f;
            l->f_38 = 1.0f;
            l->f_3C = (l->f_20[0] + l->f_20[1] + l->f_20[2]) * 0.3333f;
        }
    }
}

void light_GetColorAnalog(float *col)
{
    float x;
    float y;
    float a;
    float r;
    float g;
    float b;
    float d;

    x = (float)(pad[1].ana[0] - 128);
    y = (float)(pad[1].ana[1] - 128);

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

/* A cursor vertex or the cursor's RGBA colour, one quadword either way. */
typedef union LtVec {
    sceVu0FVECTOR f;
    int i[4];
} LtVec;

void light_DrawCursor(float *dir, int mode)
{
    float m[4][4];
    LtVec sub;
    LtVec tip;
    LtVec base;
    LtVec left;
    LtVec right;
    int i;

    tip = (LtVec){{0.0f, 0.0f, -100.0f, 1.0f}};
    memset(&base, 0, 16);
    left = (LtVec){{10.0f, 0.0f, -25.0f, 1.0f}};
    right = (LtVec){{-10.0f, 0.0f, -25.0f, 1.0f}};
    base.f[3] = 1.0f;
    GetRootMatrix(m, CameraGetTarget());
    if (mode == 0) {
        LtVec col;

        cursorRotY = (128 - pad[1].ana[0]) * 32767 / 128;
        cursorRotX = (pad[1].ana[1] - 128) * 32767 / 128;
        _InitCurrentMatrix();
        _TransCurrentMatrix(m[3]);
        _RotCurrentMatrixX(cursorRotX);
        _RotCurrentMatrixY(cursorRotY);
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
        col = (LtVec){.i = {255, 255, 255, 128}};
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

        col = (LtVec){.i = {255, 255, 255, 128}};
        for (i = 0; i < 3; i++) {
            _ScaleVector(&tip, GlobalStageSetting.flatLightDir[i], -100.0f);
            _ScaleVector(&left, GlobalStageSetting.flatLightDir[i], -200.0f);
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
   Three pages selected by toolPage (colour, direction vector, ambient),
   each editing light toolLight with component toolItem (3 = all three at
   once).  The retail build calls debug_PrintfDummy where the January-2002
   listing calls debug_Printf; everything else is instruction for instruction
   the same function, so the listing's per-instruction line map is the
   source-shape oracle here.  The blink guard masks frame_count with an
   unsigned constant: masked with a plain int 0x1F, gcc knows the value fits
   0..31 and picks slti, while the ROM has sltiu at all six sites.
   light_resetFlatLight is expanded at the tail (listing rows 1388-1406). */
/* .data, owned by Light.o and read only here.  One idle flag per editor page
   (0 colour, 1 vector, 2 ambient): 1 while the page is only being shown, 0
   while the analog sticks are driving that page's values. */
static int pageIdle[3] = {1, 1, 1};

static int toolPage = 0; /* derived name */ /* the editor page: 0 colour, 1 vector, 2 ambient */

static int toolItem = 0; /* derived name */ /* the selected component: 0 x/r, 1 y/g, 2 z/b, 3 all */

static int toolLight = 0; /* derived name */ /* the selected flat light: 0..2 */

int light_Tool(void)
{
    float dir[4];
    float col1[4];
    float col2[4];
    int ret = 0;
    int i;
    char *name[3] = {"r:", "g:", "b:"};
    unsigned int col;
    short rot;
    float (*c)[4];

    if (pad[0].flags & 0x4000) {
        if (++toolPage == 3) {
            toolPage = 0;
        }
    }
    if (pad[0].flags & 0x1000) {
        if (--toolPage == -1) {
            toolPage = 2;
        }
    }
    if (pad[0].flags & 0x1) {
        if (++toolLight == 3) {
            toolLight = 0;
        }
    }
    if (pad[0].flags & 0x100) {
        pageIdle[0] = pageIdle[1] = pageIdle[2] = 1;
        ret = -1;
    }
    if (pageIdle[1] == 0 && toolPage == 1) {
        light_DrawCursor(dir, 0);
    } else {
        light_DrawCursor(dir, 1);
    }
    switch (toolPage) {
    case 0:
        pageIdle[1] = pageIdle[2] = 1;
        light_GetColorAnalog(col1);
        if ((pad[0].flags & 0x400) && toolItem == 3) {
            pageIdle[0] ^= 1;
        }
        if (pageIdle[0] == 0 && toolItem == 3) {
            /* The row pointer is into flatLightDir, so the three stores keep
               the +0x30 to flatLightCol in the store displacement off one
               base; spelling the destination as flatLightCol[idx][n] at each
               of the three sites folds 0x30 onto the symbol and makes gcse PRE
               insert two reaching-register copies the ROM does not have. */
            c = &GlobalStageSetting.flatLightDir[toolLight];
            c[3][0] = col1[0] / 128.0f;
            c[3][1] = col1[1] / 128.0f;
            c[3][2] = col1[2] / 128.0f;
            break;
        }
        if (pad[0].flags & 0x2000) {
            if (++toolItem == 4) {
                toolItem = 0;
            }
        }
        if (pad[0].flags & 0x8000) {
            if (--toolItem == -1) {
                toolItem = 3;
            }
        }
        if (toolItem != 3) {
            if (pad[0].rep & 0x20) {
                GlobalStageSetting.flatLightCol[toolLight][toolItem] += 0.01f;
            }
            if (pad[0].rep & 0x40) {
                GlobalStageSetting.flatLightCol[toolLight][toolItem] -= 0.01f;
            }
            break;
        }
        if (pad[0].rep & 0x20) {
            for (i = 0; i < 3; i++) {
                GlobalStageSetting.flatLightCol[toolLight][i] *= 1.01f;
            }
        }
        if (pad[0].rep & 0x40) {
            for (i = 0; i < 3; i++) {
                GlobalStageSetting.flatLightCol[toolLight][i] *= 0.99f;
            }
        }
        break;
    case 1:
        pageIdle[0] = pageIdle[2] = 1;
        if ((pad[0].flags & 0x400) && toolItem == 3) {
            pageIdle[1] ^= 1;
        }
        if (pageIdle[1] == 0 && toolItem == 3) {
            _CopyVector(GlobalStageSetting.flatLightDir[toolLight], dir);
            break;
        }
        if (pad[0].flags & 0x2000) {
            if (++toolItem == 4) {
                toolItem = 0;
            }
        }
        if (pad[0].flags & 0x8000) {
            if (--toolItem == -1) {
                toolItem = 3;
            }
        }
        if (toolItem == 3) {
            break;
        }
        if (pad[0].rep & 0x20) {
            rot = 1024;
        } else {
            rot = (pad[0].rep & 0x40) ? -1024 : 0;
        }
        _InitCurrentMatrix();
        switch (toolItem) {
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
        _ApplyCurrentMatrix(GlobalStageSetting.flatLightDir[toolLight],
                            GlobalStageSetting.flatLightDir[toolLight]);
        break;
    case 2:
        pageIdle[0] = pageIdle[1] = 1;
        light_GetColorAnalog(col2);
        if ((pad[0].flags & 0x400) && toolItem == 3) {
            pageIdle[2] ^= 1;
        }
        if (pageIdle[2] == 0 && toolItem == 3) {
            GlobalStageSetting.ambientCol[0] = col2[0] / 255.0f;
            GlobalStageSetting.ambientCol[1] = col2[1] / 255.0f;
            GlobalStageSetting.ambientCol[2] = col2[2] / 255.0f;
            break;
        }
        if (pad[0].flags & 0x2000) {
            if (++toolItem == 4) {
                toolItem = 0;
            }
        }
        if (pad[0].flags & 0x8000) {
            if (--toolItem == -1) {
                toolItem = 3;
            }
        }
        if (toolItem != 3) {
            if (pad[0].rep & 0x20) {
                GlobalStageSetting.ambientCol[toolItem] += 0.01f;
            }
            if (pad[0].rep & 0x40) {
                GlobalStageSetting.ambientCol[toolItem] -= 0.01f;
            }
            break;
        }
        if (pad[0].rep & 0x20) {
            for (i = 0; i < 3; i++) {
                GlobalStageSetting.ambientCol[i] *= 1.01f;
            }
        }
        if (pad[0].rep & 0x40) {
            for (i = 0; i < 3; i++) {
                GlobalStageSetting.ambientCol[i] *= 0.99f;
            }
        }
        break;
    }
    debug_PrintfDummy(10, 46, 0xFF800000, "PUSH R2 SELECT LIGHT (%d/3) ('SELECT'RETURN MENU)",
                      toolLight + 1);
    col = (toolPage == 0) ? 0xFFC0C000 : 0xFFFFFF00;
    if (pageIdle[0] != 0 || (frame_count & 0x1FU) < 20) {
        debug_PrintfDummy(10, 56, col, "COL ");
    }
    for (i = 0; i < 3; i++) {
        if (pageIdle[0] == 0 || toolPage != 0 || (toolItem != i && toolItem != 3) ||
            (frame_count & 0x1FU) < 20) {
            debug_PrintfDummy(46 + i * 168, 56, col, "%s%11f", name[i],
                              GlobalStageSetting.flatLightCol[toolLight][i] * 128.0f);
        }
    }
    col = (toolPage == 1) ? 0xFFC0C000 : 0xFFFFFF00;
    if (pageIdle[1] != 0 || (frame_count & 0x1FU) < 20) {
        debug_PrintfDummy(10, 66, col, "VEC ");
    }
    for (i = 0; i < 3; i++) {
        if (pageIdle[1] == 0 || toolPage != 1 || (toolItem != i && toolItem != 3) ||
            (frame_count & 0x1FU) < 20) {
            debug_PrintfDummy(46 + i * 168, 66, col, "%s%11f", name[i],
                              GlobalStageSetting.flatLightDir[toolLight][i]);
        }
    }
    col = (toolPage == 2) ? 0xFFC0C000 : 0xFFFFFF00;
    if (pageIdle[2] != 0 || (frame_count & 0x1FU) < 20) {
        debug_PrintfDummy(10, 76, col, "AMB ");
    }
    for (i = 0; i < 3; i++) {
        if (pageIdle[2] == 0 || toolPage != 2 || (toolItem != i && toolItem != 3) ||
            (frame_count & 0x1FU) < 20) {
            debug_PrintfDummy(46 + i * 168, 76, col, "%s%11f", name[i],
                              GlobalStageSetting.ambientCol[i] * 255.0f);
        }
    }
    light_resetFlatLight();
    return ret;
}

void light_InitLight(void)
{
    lastLight = 0;
    lastAmbient = 0;
    flatLightNum = 0;
}

void light_ResetLight(void) {}

void light_KillAllFixLight(void)
{
    Light *p = (Light *)lastLight;
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
    lightCount = 0;
}

void light_KillAllAmbient(void)
{
    AmbientVolume *p = (AmbientVolume *)lastAmbient;
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

static inline void light_setLinkAmbient(AmbientVolume *p)
{
    if (lastAmbient != 0)
        ((AmbientVolume *)lastAmbient)->next = p;
    p->next = 0;
    p->prev = (AmbientVolume *)lastAmbient;
    lastAmbient = (int)p;
}

AmbientVolume *light_AddAmbientObject(int obj)
{
    AmbientVolume *p;

    p = (AmbientVolume *)iosMallocDebug(ios_partition_seki, 0xA0, "src/Light.c", 723);
    p->f_90 = obj;
    p->f_80 = 1.0f;
    light_setLinkAmbient(p);
    return p;
}
