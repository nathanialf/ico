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
#include "motionViewer.h"
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
#include "include_asm.h"

typedef struct MvMenuEnt { /* field names derived */
    char *name;            /* 0x00, csv window title */
    int kind;              /* 0x04, isys object kind */
    int motFirst;          /* 0x08, first motion id of this object's block */
    int motLast;           /* 0x0C */
    int oriFrom;           /* 0x10, first motionOrient row */
    int oriTo;             /* 0x14, one past the last motionOrient row */
} MvMenuEnt;               /* derived name */

/* one row of the orient csv the viewer browses: name + the kind it selects */
typedef struct OriRow { /* field names derived */
    const char *name;   /* 0x00 */
    int kind;           /* 0x04 */
} OriRow;               /* derived name */

typedef struct OriCsv { /* field names derived */
    int sel;
    OriRow *rows;
} OriCsv; /* derived name */

/* objMenu: the five objects the viewer can target */
MvMenuEnt objMenu[] = {
    {"BoyMotion", 1, 0, 521, 0, 1207},           {"GirlMotion", 2, 521, 821, 1207, 1772},
    {"Enemy1Motion", 4, 821, 1002, 1772, 2106},  {"BirdMotion", 32, 1153, 1163, 2120, 2165},
    {"QueenMotion", 45, 1091, 1153, 2106, 2120},
};

static int objSel = 0; /* derived name */

static int motSel = 0; /* derived name */

static OriCsv oriCsv = {0, 0}; /* derived name */

static GObj *viewObj = 0; /* derived name */

static int blinkCount = 0; /* derived name */

static int rootUpdateMode = 0; /* derived name */

static float motionSpeed = 1.0f; /* derived name */

extern MotionOrientEntry motionOrient[];
/* declared here: ico2/fumi/src/commonact.c declares the table without
   const, so motionOrientManager.h cannot carry it */
extern const MotOriName motionOriKind[];

static inline int countMotionKinds(int id, int from, int to) /* derived name */
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

static inline int makeMotionKindList(MvMenuEnt *ent, int base) /* derived name */
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

static void setRootUpdateMode(void)
{
    SetRootUpdateMode(viewObj, rootUpdateMode);
}

static void setMotionSpeed(float ratio)
{
    SetMotionPlaySpeedRatio(viewObj, ratio);
}

INCLUDE_ASM(dispProgressBar_45_motionViewer);

/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char []; not const, since
   debug_SelectCsvWindowWithLine takes its rows as void * */
extern MotionDef motionKind[];

INCLUDE_ASM(dispMotFrameProgress);

static int lastObjSel = -1; /* derived name */

static void *savedFn = 0; /* derived name */

/* as in debug.h, which this file does not include */
extern int debug_SelectCsvWindow(char *title, int x, int y, int rows, void *tbl, int stride,
                                 int off, int deref, int count, int *cur);

INCLUDE_ASM(objMenuProc);

static int lastMotSel = -1; /* derived name */

/* the number of motion-kind rows makeMotionKindList built, the row count
 * motOriMenuProc hands to debug_SelectCsvWindow */
static int motionKindCount; /* derived name */

/* as in debug.h, which this file does not include (its 11-argument
   debug_SelectCsvWindowWithLine below conflicts with debug.h's 10) */
extern void debug_PrintfDummy(int x, int y, unsigned int color, const char *fmt, ...);
/* int (char *, int, int, int, void *, int, int, int, int, int *, int) here, int (char *, int, int, int, void *, int, int, int, int, int *) in debug.h */
extern int debug_SelectCsvWindowWithLine(char *title, int x, int y, int rows, void *tbl, int stride,
                                         int off, int deref, int count, int *cur, int extra);

INCLUDE_ASM(motKindMenuProc);

static int lastOriSel = -1; /* derived name */

INCLUDE_ASM(motOriMenuProc);

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
    /* the speed goes to the variadic call as a plain float */
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
        viewObj->dobj->root.twistRate = 1.0f - rdata[19] * 0.0078125f;
    } else {
        viewObj->dobj->root.twistRate = 1.0f;
    }
    if (pad[0].now & 0x8000) {
        viewObj->dobj->root.twist = rdata[9] / 255.0f * 8192.0f;
    } else if (pad[0].now & 0x2000) {
        viewObj->dobj->root.twist = rdata[8] / 255.0f * -8192.0f;
    } else {
        viewObj->dobj->root.twist = 0;
    }
}

typedef struct MvVec { /* field names derived */
    float x, y, z, w;
} __attribute__((aligned(16))) MvVec; /* derived name */

typedef struct MvCol { /* field names derived */
    int r, g, b, a;
} __attribute__((aligned(16))) MvCol; /* derived name */

static void lookAtTest(MvVec *pos, float rad, void *colAxis, void *colRing, short dy, short ang)
{
    float p0[4];
    float p1[4];
    float fdy = dy;
    float sx = rad * GetTableSin(ang);
    float cx = rad * GetTableCos(ang);
    int a;

    GetRootPosition(pos, viewObj);
    gif_StartPacketPri(11);
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
    gif_StartPacketPri(11);
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
    gif_StartPacketPri(11);
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

/* the test lines' colours */
static MvCol testAxisColor = {128, 192, 255, 128}; /* derived name */

static MvCol testRingColor = {0, 64, 128, 128}; /* derived name */

static MvCol focusColor = {0, 0, 0, 128}; /* derived name */

/* The look-at and head test colours: integer colours MotionViewer copies
   into its vector locals whole, read as a const object of the vector type,
   hence the union. */
typedef union MvColVec { /* field names derived */
    MvCol c;
    MvVec v;
} MvColVec; /* derived name */

static const MvColVec lookAxisColor = {{128, 64, 32, 128}}; /* derived name */

static const MvColVec lookRingColor = {{64, 16, 0, 128}}; /* derived name */

/* as in debug.h, which this file does not include */
extern int debug_now_motion_viewer;

/* MotionViewer's state */
static int menuLevel = 0; /* derived name */

/* the test mode the root block's look mode is driven by: off, the pad or random */
static enum { TEST_OFF, TEST_PAD, TEST_RANDOM } testMode = TEST_OFF; /* derived name */

static int testCount = 0; /* derived name */

static short testDy = 0; /* derived name */

static short testAng = 0; /* derived name */

static int lookMode = 0; /* derived name */

static int headMode = 0; /* derived name */

static int lookHeadStep = 0; /* derived name */

static float lookRadius = 100.0f; /* derived name */

INCLUDE_ASM(MotionViewer);
