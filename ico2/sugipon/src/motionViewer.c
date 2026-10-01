#include "sugiCommon.h"
#include "memory.h"
#include "gobj.h"
#include "enemy_act.h"
#include "camera-root.h"
#include "geometryManager.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "tableSin.h"
#include <stdio.h>
#include <libpad.h>
#include <string.h>
#include "GsBase.h"
#include "motionFileManager.h"
#include "ios.h"
#include "main.h"
#include "GifPacket.h"
#include <libvu0.h>

struct MvObj;

typedef struct MvMenuEnt {
    char *name;   /* 0x00, csv window title */
    int kind;     /* 0x04, isys object kind */
    int motFirst; /* 0x08, first motion id of this object's block */
    int motLast;  /* 0x0C */
    int oriFrom;  /* 0x10, first motionOrient row */
    int oriTo;    /* 0x14, one past the last motionOrient row */
} MvMenuEnt;

/* one row of the orient csv the viewer browses: name + the kind it selects */
typedef struct OriRow {
    const char *name; /* 0x00 */
    int kind;         /* 0x04 */
} OriRow;

typedef struct OriCsv {
    int sel;
    OriRow *rows;
} OriCsv;

/* The TU's .data opens with objMenu (MAIN.MAP motionViewer.o), the five objects
   the viewer can target; its names are the first strings of the TU's .rodata. */
MvMenuEnt objMenu[] = {
    {"BoyMotion", 1, 0, 532, 0, 1283},           {"GirlMotion", 2, 532, 834, 1283, 2122},
    {"Enemy1Motion", 4, 834, 983, 2122, 2407},   {"BirdMotion", 32, 1134, 1143, 2421, 2467},
    {"QueenMotion", 47, 1072, 1134, 2407, 2421},
};

/* The TU's .sdata head, in ROM order (MAIN.MAP names nothing in it). */
static int objSel = 0; /* derived name */

static int motSel = 0; /* derived name */

static OriCsv oriCsv = {0, 0}; /* derived name */

static struct MvObj *viewObj = 0; /* derived name */

static int blinkCount = 0; /* derived name */

static int rootUpdateMode = 0; /* derived name */

static float motionSpeed = 1.0f; /* derived name */

extern MotionOrientEntry motionOrient[];
/* kept local: ico2/fumi/src/commonact.c declares the table without const, so
   motionOrientManager.h cannot carry it */
extern const MotOriName motionOriKind[];

static inline int countMotionKinds(int id, int from, int to)
{
    int n = 0;
    int i;

    for (i = from; i < to; i++) {
        if (motionOrient[i].id == id || motionOrient[i].id == 1146) {
            n++;
        }
    }
    return n;
}

static inline int makeMotionKindList(MvMenuEnt *ent, int base)
{
    OriRow *list;
    int id = ent->motFirst + base, from = ent->oriFrom, to = ent->oriTo;
    int n = countMotionKinds(id, from, to);
    int i;
    int k;

    list = iosMallocDebug(ios_partition_sugipon, n * 8, __FILE__, 93);
    if (n) {
        k = 0;
        for (i = from; i < to; i++) {
            if (motionOrient[i].id == id || motionOrient[i].id == 1146) {
                int kind = motionOrient[i].kind;

                list[k].kind = kind;
                list[k].name = motionOriKind[kind].s;
                k++;
            }
        }
    }
    oriCsv.rows = list;
    return n;
}

void setRootUpdateMode(void)
{
    SetRootUpdateMode(viewObj, rootUpdateMode);
}

void setMotionSpeed(float ratio)
{
    SetMotionPlaySpeedRatio(viewObj, ratio);
}

/* dispProgressBar is defined as a nested function inside dispMotFrameProgress
 * below (the listing names it dispProgressBar.108). */
typedef struct {
    unsigned char r, g, b, a;
} BarCol;

typedef struct {
    int x, y, w, h;
} BarRect;

/* kept local: motionOrientManager.h reaches ico2/fumi's TUs through
   typedef.h, and commonact.c declares the table char []; not const here,
   since debug_SelectCsvWindowWithLine takes its rows as void * */
extern MotionDef motionKind[];

void dispMotFrameProgress(int obj, float cur)
{
    /* dispProgressBar is a nested function in the ROM: dispMotFrameProgress
     * passes it a static chain in $2 (STATIC_CHAIN_REGNUM), which it spills
     * to 0(sp).  The listing names it dispProgressBar.108. */
    void dispProgressBar(int s, int e, int n, float c, BarCol *col)
    {
        float r0 = (float)s / (float)n;
        float r1 = (float)e / (float)n;
        float rc = c / (float)n;

        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 5, 0x80);
        if (r0 < rc && rc <= r1) {
            BarCol dark = {col->r / 2, col->g / 2, col->b / 2, 0x80};
            BarRect ra = {(int)((-(ScreenWidth << 4) / 2 + (ScreenWidth << 4) * r0) * 8 / 10),
                          ((ScreenHeight << 4) * 6 / 20) & ~15,
                          (int)(((ScreenWidth << 4) * (rc - r0)) * 8 / 10),
                          (((ScreenHeight << 4) / 100) & ~15) + 24};
            BarRect rb = {(int)((-(ScreenWidth << 4) / 2 + (ScreenWidth << 4) * rc) * 8 / 10), ra.y,
                          (int)(((ScreenWidth << 4) * (r1 - rc)) * 8 / 10), ra.h};
            gif_SpriteSensitiveOrg(&ra, 0, 0, col, 1);
            gif_SpriteSensitiveOrg(&rb, 0, 0, &dark, 1);
        } else {
            BarRect rc2 = {(int)((-(ScreenWidth << 4) / 2 + (ScreenWidth << 4) * r0) * 8 / 10),
                           ((ScreenHeight << 4) * 6 / 20) & ~15,
                           (int)(((ScreenWidth << 4) * (r1 - r0)) * 8 / 10),
                           (((ScreenHeight << 4) / 100) & ~15) + 24};
            if (rc <= r0) {
                BarCol dark = {col->r / 2, col->g / 2, col->b / 2, 0x80};
                gif_SpriteSensitiveOrg(&rc2, 0, 0, &dark, 1);
            } else {
                gif_SpriteSensitiveOrg(&rc2, 0, 0, col, 1);
            }
        }
        gif_SetZTest(1);
        gif_SetZWrite(1);
        gif_EndPacket();
    }
    BarCol colA = {52, 84, 192, 128};
    BarCol colB = {192, 84, 52, 128};
    float f1 = motionKind[obj].shiftStart;
    float f2 = motionKind[obj].shiftLength;

    if (f1 >= 0.0f && f2 >= 0.0f) {
        float sum = f1 + f2;
        int rev;

        dispProgressBar(0, f1, GetNbMotionFrames(obj) - 1, cur,
                        (rev = (motionKind + obj)->flags.bits.shiftInside) ? &colB : &colA);
        dispProgressBar(f1, sum, GetNbMotionFrames(obj) - 1, cur, rev ? &colA : &colB);
        dispProgressBar(sum, GetNbMotionFrames(obj) - 1, GetNbMotionFrames(obj) - 1, cur,
                        rev ? &colB : &colA);
    } else {
        dispProgressBar(0, GetNbMotionFrames(obj) - 1, GetNbMotionFrames(obj) - 1, cur, &colA);
    }
}

typedef struct MvSub {
    char pad000[12];
    char *nodes; /* 0x00C, per-node 0x40 matrices */
    char pad010[124];
    float *ground; /* 0x08C */
    char pad090[96];
    short rot; /* 0x0F0 */
    char padF2[2];
    float speed; /* 0x0F4 */
    char padF8[136];
    char motionRequest[336]; /* 0x180, SetMotionRequest work area */
    int lookMode;            /* 0x2D0 */
    char pad2D4[12];
    float lookAt[4]; /* 0x2E0 */
    char pad2F0[64];
    int headMode; /* 0x330 */
    char pad334[12];
    float headAt[4]; /* 0x340 */
    char pad350[48];

    /* 0x380. Reconstruction: an enumerated type, not int. MotionViewer's
       gcse needs this store outside int's alias set so the in-block read of
       testMode stays available and the join's reload moves onto the skip
       edge; typed int, the ROM's one-load modulus block is unreachable
       (measured 0x814 against 0x810). Enumerator names are ours. */
    enum { TEST_OFF, TEST_PAD, TEST_RANDOM } testMode;

    char pad384[12];
    float testAt[4]; /* 0x390 */
    char pad3A0[232];
    int select; /* 0x488, "this object is the viewer target" */
} MvSub;

typedef struct MvObj {
    char pad00[40];
    void *motTbl; /* 0x28, parallel motion table, parked while viewing */
    char pad2C[304];
    MvSub *sub; /* 0x15C */
} MvObj;

static int lastObjSel = -1; /* derived name */

static char *savedMotTbl = 0; /* derived name */

/* kept local: agrees with debug.h, which this TU does not include (debug_PrintfDummy, debug_SelectCsvWindowWithLine differ) */
extern int debug_SelectCsvWindow(char *title, int a1, int a2, int a3, void *tbl, int stride, int a6,
                                 int a7, int count, int *cur);

int objMenuProc(void)
{
    int ret =
        debug_SelectCsvWindow("Motion Viewer", 10, 0x32, 0xB, objMenu, 0x18, 0, 1, 5, &objSel);

    if (lastObjSel != objSel) {
        if (viewObj) {
            viewObj->motTbl = savedMotTbl;
            viewObj->sub->select = 0;
        }
        viewObj = isysGObjSearchFromObjKindID_begin(objMenu[objSel].kind);
        if (objMenu[objSel].kind == 4) {
            for (; viewObj != 0; viewObj = isysGObjSearchFromObjKindID_next(viewObj)) {
                if (isEnemyActive(viewObj)) {
                    break;
                }
            }
        }
        if (viewObj) {
            CurrentTargetGObj = viewObj;
            Camctrl_SetTarget(viewObj, 0, 3);
            savedMotTbl = viewObj->motTbl;
            viewObj->motTbl = 0;
            SetParallelMotionTableWithNoRequest(viewObj, 0, 0);
            viewObj->sub->select = 1;
        }
        lastObjSel = objSel;
        CameraSetMode(2);
    }
    if (ret == 1) {
        motionSpeed = 1.0f;
        setMotionSpeed(motionSpeed);
        if (viewObj != 0) {
            motSel = 0;
        } else {
            ret = 0;
        }
    }
    if (ret == -1) {
        CurrentTargetGObj = isysGObjSearchFromObjKindID_begin(1);
        Camctrl_SetTarget(CurrentTargetGObj, 0, 3);
        if (viewObj) {
            viewObj->motTbl = savedMotTbl;
            viewObj->sub->select = 0;
        }
        viewObj = 0;
        savedMotTbl = 0;
        lastObjSel = ret;
        CameraSetMode(3);
    }
    return ret;
}

/* motionOrientManager's table row (same object as src/motionOrientManager.c) */

static int lastMotSel = -1; /* derived name */

/* MAIN.MAP line 7628 gives motionViewer.o a 4-byte .sbss and names no symbol in it,
 * so this object is a file static and the role name is ours: it is the number of
 * motion-kind rows makeMotionKindList built, and the row count motOriMenuProc hands
 * to debug_SelectCsvWindow. Evidence rung: ROM bytes plus the MAIN.MAP member row. */
static int motionKindCount;

/* kept local: void (int, int, unsigned int, const char *, ...) here, void (int, int, unsigned int, int, ...) in debug.h */
extern void debug_PrintfDummy(int x, int y, unsigned int color, const char *fmt, ...);
/* kept local: int (char *, int, int, int, void *, int, int, int, int, int *, int) here, int (char *, int, int, int, void *, int, int, int, int, int *) in debug.h */
extern int debug_SelectCsvWindowWithLine(char *title, int a1, int a2, int a3, void *tbl, int stride,
                                         int a6, int a7, int count, int *cur, int a10);

int motKindMenuProc(void)
{
    MvMenuEnt *ent = &objMenu[objSel];
    int mot = ForMotionViewer_GetCurrentMotion(viewObj);
    float speed = GetMotionPlaySpeedRatio(mot);
    int ret;
    int base;
    int cur;

    dispMotFrameProgress(mot, ForMotionViewer_GetCurrentAnimationFrame(viewObj));
    ret = debug_SelectCsvWindowWithLine(ent->name, 10, 0x46, 6, &motionKind[ent->motFirst], 0x194,
                                        0xC0, 0, ent->motLast - ent->motFirst, &motSel, 0);
    base = motSel;
    cur = base + ent->motFirst;
    if (motionKind[cur].node_id != 0 && motionKind[cur].blendKind == 320 && motionTable[cur] == 0) {
        base = 0;
        if (((blinkCount >> 4) & 3) != 0) {
            debug_PrintfDummy(10, 60, 0x4080FF00, "NO MOTION IN THIS STAGE.");
        }
    } else {
        debug_PrintfDummy(10, 50, 0xC0FFFF00, "Frame : %1.1f/%d",
                          ForMotionViewer_GetCurrentAnimationFrame(viewObj),
                          GetNbMotionFrames(mot) - 1);
        debug_PrintfDummy(10, 60, 0x80FFFF00, "x%1.3f: %1.1f/%d", speed,
                          ForMotionViewer_GetCurrentAnimationFrame(viewObj) / speed,
                          (int)((GetNbMotionFrames(mot) - 1) / speed));
    }
    if (motSel != lastMotSel) {
        DisableChangeRootUpdateMode(viewObj);
        DisableMotionOrientUpdate(viewObj);
        InitMotionOrient(viewObj, base + ent->oriFrom, base + ent->oriTo, -1, -1,
                         base + ent->motFirst);
        lastMotSel = motSel;
    }
    if (pad[0].flags & 0x10) {
        InitMotionOrient(viewObj, base + ent->oriFrom, base + ent->oriTo, -1, -1,
                         base + ent->motFirst);
    }
    if (ret == 1) {
        motionKindCount = makeMotionKindList(ent, base);
        oriCsv.sel = 0;
    }
    if (ret == -1) {
        InitMotionOrient(viewObj, ent->oriFrom, ent->oriTo, -1, -1, ent->motFirst);
        EnableMotionOrientUpdate(viewObj);
        EnableChangeRootUpdateMode(viewObj);
        lastMotSel = ret;
    }
    return ret;
}

static int lastOriSel = -1; /* derived name */

int motOriMenuProc(void)
{
    MvMenuEnt *ent = &objMenu[objSel];
    int cur = motSel + ent->motFirst;
    int mot = ForMotionViewer_GetCurrentMotion(viewObj);
    char buf[256];
    int ret;
    int now;
    int m;
    int i;
    MotionOrientEntry *ori;

    /* the listing places this at motionViewer.c lines 382-385, INSIDE
     * motOriMenuProc's own span and expanded at both of its call sites:
     * a nested function, always inlined (it has no ROM slot of its own). */
    inline void initOrient(void)
    {
        DisableMotionOrientUpdate(viewObj);
        InitMotionOrient(viewObj, motSel + ent->oriFrom, motSel + ent->oriTo, -1, -1,
                         motSel + ent->motFirst);
    }

    dispMotFrameProgress(mot, ForMotionViewer_GetCurrentAnimationFrame(viewObj));
    if (motionKindCount != 0) {
        sprintf(buf, "ORIENT for \"%s\" Frame: %1.1f/%d", motionKind[cur].name,
                ForMotionViewer_GetCurrentAnimationFrame(viewObj), GetNbMotionFrames(mot));
        ret = debug_SelectCsvWindow(buf, 10, 50, 11, oriCsv.rows, 8, 0, 1, motionKindCount,
                                    &oriCsv.sel);
        if (oriCsv.sel != lastOriSel) {
            initOrient();
        }
        lastOriSel = oriCsv.sel;
        m = cur;
        now = ForMotionViewer_GetCurrentMotion(viewObj);
        for (i = 0; i < 10; i++) {
            ori = GetMotionOrient(ent->oriFrom, ent->oriTo, m, oriCsv.rows[oriCsv.sel].kind);
            debug_PrintfDummy(430, i * 8 + 90, (i == 0 || m == 1145) ? 0x00FFFF00 : 0xFFFFFF00,
                              "%c %s", m == now ? 62 : 32, motionKind[m].name);
            if (m == 1145) {
                break;
            }
            if (ori == 0) {
                i++;
                if (((blinkCount >> 4) & 3) != 0) {
                    debug_PrintfDummy(430, i * 8 + 90, 0xFF000000, "  NO ORIENT.");
                }
                break;
            }
            m = ori->nextId;
        }
    } else {
        debug_PrintfDummy(10, 50, 0xFF000000, "NO ORIENT for \"%s\"", motionKind[cur].name);
        ret = (pad[0].flags & 0x40) ? -1 : 0;
    }
    if (pad[0].flags & 0x10) {
        initOrient();
    }
    if (ret == 1) {
        EnableMotionOrientUpdate(viewObj);
        SetMotionRequest(viewObj, oriCsv.rows[oriCsv.sel].kind,
                         *(MotOriReq *)viewObj->sub->motionRequest);
    }
    if (ret == -1) {
        if (oriCsv.rows != 0) {
            iosFree(oriCsv.rows);
        }
    }
    return ret;
}

void modeMessage(void)
{
    char buf[256];
    unsigned char rdata[32];

    debug_PrintfDummy(470, 58, 0xFFFFFF00, " \202: Restart");
    switch (rootUpdateMode) {
    case 0:
    default:
        sprintf(buf, "Depend");
        break;
    case 19:
        sprintf(buf, "RotOnly");
        break;
    }
    debug_PrintfDummy(470, 66, 0xFFFFFF00, " \203: %s", buf);
    /* The speed goes to the variadic call as a plain float: the default
       argument promotion is the compiler's own fptodp libcall, whose load of
       the float sits ahead of the lui of the format address as the ROM has
       it.  This replaced the approved pointer carrier `float *pf` (re-audit,
       completeness pass 57), with the whole object byte-identical; an
       explicit fptodp call on the plain global reverses the pair. */
    debug_PrintfDummy(470, 74, 0xFFFFFF00, "\206\207: x%1.2f", motionSpeed);
    if (pad[0].flags & 0x80) {
        switch (rootUpdateMode) {
        case 0:
        default:
            rootUpdateMode = 19;
            break;
        case 19:
            rootUpdateMode = 0;
            break;
        }
        setRootUpdateMode();
    }
    if (pad[0].rep & 0x8000) {
        motionSpeed -= 0.01f;
        if (motionSpeed < 0.0f) {
            motionSpeed = 0.0f;
        }
        setMotionSpeed(motionSpeed);
    }
    if (pad[0].rep & 0x2000) {
        motionSpeed += 0.01f;
        if (motionSpeed > 2.0f) {
            motionSpeed = 2.0f;
        }
        setMotionSpeed(motionSpeed);
    }
    scePadRead(0, 0, rdata);
    if (pad[0].now & 0x8) {
        motionSpeed = 1.0f - rdata[17] / 255.0f;
        setMotionSpeed(motionSpeed);
    }
    if (pad[0].now & 0x2) {
        viewObj->sub->speed = 1.0f - rdata[19] * 0.0078125f;
    } else {
        viewObj->sub->speed = 1.0f;
    }
    if (pad[0].now & 0x8000) {
        viewObj->sub->rot = rdata[9] / 255.0f * 8192.0f;
    } else if (pad[0].now & 0x2000) {
        viewObj->sub->rot = rdata[8] / 255.0f * -8192.0f;
    } else {
        viewObj->sub->rot = 0;
    }
}

typedef struct MvVec {
    float x, y, z, w;
} __attribute__((aligned(16))) MvVec;

typedef struct MvCol {
    int r, g, b, a;
} __attribute__((aligned(16))) MvCol;

void lookAtTest(MvVec *pos, float rad, void *colAxis, void *colRing, short dy, short ang)
{
    float p0[4];
    float p1[4];
    float fdy = dy;
    float sx = rad * GetTableSin(ang);
    float cx = rad * GetTableCos(ang);
    int a;

    GetRootPosition(pos, viewObj);
    gif_StartPacketPri(0xB);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(pos);
    for (a = 0; a <= 65535; a += 2048) {
        p0[1] = p1[1] = 0.0f;
        p0[0] = rad * GetTableCos(a);
        p0[2] = rad * GetTableSin(a);
        p1[0] = rad * GetTableCos(a + 2048);
        p1[2] = rad * GetTableSin(a + 2048);
        DrawLineG(p0, colRing, p1, colRing, 0);
    }
    gif_EndPacket();

    pos->y += fdy;
    gif_StartPacketPri(0xB);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(pos);
    for (a = 0; a <= 65535; a += 2048) {
        p0[1] = p1[1] = 0.0f;
        p0[0] = rad * GetTableCos(a);
        p0[2] = rad * GetTableSin(a);
        p1[0] = rad * GetTableCos(a + 2048);
        p1[2] = rad * GetTableSin(a + 2048);
        DrawLineG(p0, colRing, p1, colRing, 0);
    }
    gif_EndPacket();

    pos->x += sx;
    pos->z += cx;
    gif_StartPacketPri(0xB);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(pos);

    CopyVector(p0, ZeroPoint);
    CopyVector(p1, ZeroPoint);
    p1[0] -= sx;
    p1[2] -= cx;
    DrawLineG(p0, colAxis, p1, colAxis, 0);

    CopyVector(p0, ZeroPoint);
    CopyVector(p1, ZeroPoint);
    p1[1] -= fdy;
    DrawLineG(p0, colAxis, p1, colAxis, 0);

    p0[1] -= fdy;
    p1[0] -= sx;
    p1[2] -= cx;
    DrawLineG(p0, colAxis, p1, colAxis, 0);

    MatrixDrive_RotMatrixX(random_unit() * 65536.0f);
    MatrixDrive_RotMatrixY(random_unit() * 65536.0f);
    MatrixDrive_RotMatrixZ(random_unit() * 65536.0f);
    MatrixDrive_ScaleMatrix(random_unit() * 3.0f + 1.0f, random_unit() * 3.0f + 1.0f,
                            random_unit() * 3.0f + 1.0f);
    for (a = 0; a < 3; a++) {
        CopyVector(p0, ZeroPoint);
        CopyVector(p1, ZeroPoint);
        p0[a] -= 10.0f;
        p1[a] += 10.0f;
        DrawLineG(p0, colAxis, p1, colAxis, 0);
    }
    gif_EndPacket();
}

/* The rest of the TU's .data: the test lines' colours, after objMenu. */
static MvCol testAxisColor = {128, 192, 255, 128}; /* derived name */

static MvCol testRingColor = {0, 64, 128, 128}; /* derived name */

static MvCol focusColor = {0, 0, 0, 128}; /* derived name */

/* The look-at and head test colours. They are integer colours that MotionViewer
   copies into its vector locals whole; the ROM's copy reads them as a const
   object of the vector type (its loads carry the read-only flag a const decl
   gives, which a cast of the address does not), hence the union. */
typedef union MvColVec {
    MvCol c;
    MvVec v;
} MvColVec;

static const MvColVec lookAxisColor = {{128, 64, 32, 128}}; /* derived name */

static const MvColVec lookRingColor = {{64, 16, 0, 128}}; /* derived name */

/* kept local: agrees with debug.h, which this TU does not include (debug_PrintfDummy, debug_SelectCsvWindowWithLine differ) */
extern int debug_now_motion_viewer;

/* The TU's .sdata tail: MotionViewer's state, in ROM order. */
static int menuLevel = 0; /* derived name */

static int testMode = 0; /* derived name */

static int testCount = 0; /* derived name */

static short testDy = 0; /* derived name */

static short testAng = 0; /* derived name */

static int lookMode = 0; /* derived name */

static int headMode = 0; /* derived name */

static int lookHeadStep = 0; /* derived name */

static float lookRadius = 100.0f; /* derived name */

extern void dispPlane(MvVec *plane, MvVec *pos);

int MotionViewer(void)
{
    MvVec v;
    MvVec dir;
    float m[16];
    MvVec pos;
    MvVec p;

    union {
        MvVec v;
        float f[4];
    } q;

    MvCol col;
    MvVec look;
    MvVec head;
    int ret;
    int mode;

    debug_now_motion_viewer = 1;
    switch (menuLevel) {
    default:
    case 0:
        ret = objMenuProc();
        break;

    case 1:
        ret = motKindMenuProc();
        modeMessage();
        break;

    case 2:
        ret = motOriMenuProc();
        modeMessage();
        break;
    }

    if (viewObj != 0) {
        memset(&dir, 0, sizeof(dir));
        dir.x = (pad[1].ana[2] - 128) * 0.0078125f;
        dir.z = (128 - pad[1].ana[3]) * 0.0078125f;
        v = dir;
        sceVu0TransposeMatrix(m, matrixptr + 128);
        sceVu0ApplyMatrix(&dir, m, &v);
        if (FSqrt(sceVu0InnerProduct(&dir, &dir)) > 0.5f && (pad[1].now & 0x200) == 0) {
            SetMotionDirection(viewObj, &dir);
        }
        gif_StartPacketPri(0xB);
        gif_SetAlpha(1, 5, 0x80);
        gif_SetZTest(1);
        gif_EndPacket();

        GetRootPosition(&pos, viewObj);
        q.v.x = 0.0f;
        q.v.y = -1.0f;
        q.v.z = 0.0f;
        q.v.w = pos.y + viewObj->sub->ground[5];
        p = q.v;
        dispPlane(&p, &pos);

        if (pad[1].flags & 0x8) {
            mode = testMode + 1;
            mode %= 3;
            viewObj->sub->testMode = testMode = mode;
        }
        mode = testMode;
        switch (mode) {
        case 0:
            break;

        case 1:
            lookAtTest(&p, 50.0f, &testAxisColor, &testRingColor, (pad[1].ana[1] - 128) * 2.0f,
                       -pad[1].ana[0] * 256);
            CopyVector(viewObj->sub->testAt, &p);
            mode = testMode;
            break;

        case 2:
            testCount++;
            lookAtTest(&p, 50.0f, &testAxisColor, &testRingColor, testDy, testAng);
            if (testCount > 100) {
                testDy = random_signed() * 256.0f;
                testAng = random_signed() * 32768.0f;
                lookAtTest(&p, 50.0f, &testAxisColor, &testRingColor, testDy, testAng);
                CopyVector(viewObj->sub->testAt, &p);
                testCount = 0;
            }
            mode = testMode;
            break;
        }
        if (mode != 0) {
            int n;
            gif_StartPacketPri(0xB);
            n = GetSkeltonFocusNode(viewObj, 0x23);
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            DrawLineG(&p, &focusColor, viewObj->sub->nodes + n * 64 + 0x30, &testRingColor, 0);
            gif_EndPacket();
        }

        p = lookAxisColor.v;
        q.v = lookRingColor.v;
        memset(&col, 0, sizeof(col));
        col.a = 128;
        if (pad[1].now & 0x200) {
            lookRadius = pad[1].ana[2] * 100.0f / 255.0f;
        }
        if (pad[1].flags & 0x2) {
            switch (lookHeadStep) {
            default:
            case 0:
                lookMode = 1;
                lookHeadStep = lookHeadStep + 1;
                headMode = 0;
                break;

            case 1:
                lookMode = 2;
                lookHeadStep = lookHeadStep + 1;
                headMode = 0;
                break;

            case 2:
                headMode = 1;
                lookHeadStep = lookHeadStep + 1;
                lookMode = 0;
                break;

            case 3:
                headMode = 2;
                lookHeadStep = lookHeadStep + 1;
                lookMode = 0;
                break;

            case 4:
                headMode = 0;
                lookMode = 0;
                lookHeadStep = 0;
                break;
            }
        }
        viewObj->sub->lookMode = lookMode;
        if (lookMode != 0) {
            int n;
            lookAtTest(&look, lookRadius, &p, &q.v, (pad[1].ana[1] - 128) * 2.0f,
                       -pad[1].ana[0] * 256);
            CopyVector(viewObj->sub->lookAt, &look);
            gif_StartPacketPri(0xB);
            n = GetSkeltonFocusNode(viewObj, 3);
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            DrawLineG(&look, &col, viewObj->sub->nodes + n * 64 + 0x30, &q.v, 0);
            gif_EndPacket();
        }
        viewObj->sub->headMode = headMode;
        if (headMode != 0) {
            int n;
            lookAtTest(&head, lookRadius, &p, &q.v, (pad[1].ana[1] - 128) * 2.0f,
                       -pad[1].ana[0] * 256);
            CopyVector(viewObj->sub->headAt, &head);
            gif_StartPacketPri(0xB);
            n = GetSkeltonFocusNode(viewObj, 0x13);
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            DrawLineG(&head, &col, viewObj->sub->nodes + n * 64 + 0x30, &q.v, 0);
            gif_EndPacket();
        }
        switch (lookMode) {
        default:
            break;

        case 1:
            debug_PrintfDummy(300, 180, 0xFFFFFF00, "Left: Target direct orient.");
            break;

        case 2:
            debug_PrintfDummy(300, 180, 0xFFFFFF00, "Left: Target with motion.");
            break;
        }
        switch (headMode) {
        default:
            break;

        case 1:
            debug_PrintfDummy(300, 180, 0xFFFFFF00, "Right: Target direct orient.");
            break;

        case 2:
            debug_PrintfDummy(300, 180, 0xFFFFFF00, "Right: Target with motion.");
            break;
        }
    }
    if (ret == -1) {
        menuLevel = menuLevel - 1;
        if (menuLevel < 0) {
            menuLevel = 0;
            debug_now_motion_viewer = 0;
            return -1;
        }
    }
    if (ret == 1) {
        menuLevel = menuLevel + 1;
        if (menuLevel == 3) {
            menuLevel = menuLevel - 1;
        }
    }
    blinkCount = (blinkCount + 1) & 0x7F;
    return 0;
}
