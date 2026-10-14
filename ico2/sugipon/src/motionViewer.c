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
    {"BoyMotion", 1, 0, 532, 0, 1283},           {"GirlMotion", 2, 532, 834, 1283, 2122},
    {"Enemy1Motion", 4, 834, 983, 2122, 2407},   {"BirdMotion", 32, 1134, 1143, 2421, 2467},
    {"QueenMotion", 47, 1072, 1134, 2407, 2421},
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

/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char []; not const, since
   debug_SelectCsvWindowWithLine takes its rows as void * */
extern MotionDef motionKind[];

INCLUDE_ASM(dispProgressBar_45);
INCLUDE_ASM(dispMotFrameProgress);

static int lastObjSel = -1; /* derived name */

static void *savedFn = 0; /* derived name */

/* as in debug.h, which this file does not include */
extern int debug_SelectCsvWindow(char *title, int x, int y, int rows, void *tbl, int stride,
                                 int off, int deref, int count, int *cur);

static int objMenuProc(void)
{
    int ret = debug_SelectCsvWindow("Motion Viewer", 10, 50, 11, objMenu, 24, 0, 1, 5, &objSel);

    if (lastObjSel != objSel) {
        if (viewObj) {
            viewObj->fn = savedFn;
            viewObj->dobj->ctrl.shiftStop = 0;
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
            savedFn = viewObj->fn;
            viewObj->fn = 0;
            SetParallelMotionTableWithNoRequest(viewObj, 0, 0);
            viewObj->dobj->ctrl.shiftStop = 1;
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
            viewObj->fn = savedFn;
            viewObj->dobj->ctrl.shiftStop = 0;
        }
        viewObj = 0;
        savedFn = 0;
        lastObjSel = ret;
        CameraSetMode(3);
    }
    return ret;
}

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
static int motKindMenuProc(void);

INCLUDE_ASM(motKindMenuProc);

static int lastOriSel = -1; /* derived name */

static int motOriMenuProc(void);

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

int MotionViewer(void)
{
    MvVec v;
    MvVec dir;
    float m[16];
    MvVec pos;
    MvVec p;

    union { /* field names derived */
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
            SetMotionDirection(viewObj, &dir.x);
        }
        gif_StartPacketPri(11);
        gif_SetAlpha(1, 5, 128);
        gif_SetZTest(1);
        gif_EndPacket();

        GetRootPosition(&pos, viewObj);
        q.v.x = 0.0f;
        q.v.y = -1.0f;
        q.v.z = 0.0f;
        q.v.w = pos.y + viewObj->dobj->skel->pos[1];
        p = q.v;
        dispPlane(&p, &pos.x);

        if (pad[1].flags & 0x8) {
            mode = testMode + 1;
            mode %= 3;
            viewObj->dobj->root.lookMode = testMode = mode;
        }
        mode = testMode;
        switch (mode) {
        case 0:
            break;

        case 1:
            lookAtTest(&p, 50.0f, &testAxisColor, &testRingColor, (pad[1].ana[1] - 128) * 2.0f,
                       -pad[1].ana[0] * 256);
            CopyVector(viewObj->dobj->root.lookPos, &p);
            mode = testMode;
            break;

        case 2:
            testCount++;
            lookAtTest(&p, 50.0f, &testAxisColor, &testRingColor, testDy, testAng);
            if (testCount > 100) {
                testDy = random_signed() * 256.0f;
                testAng = random_signed() * 32768.0f;
                lookAtTest(&p, 50.0f, &testAxisColor, &testRingColor, testDy, testAng);
                CopyVector(viewObj->dobj->root.lookPos, &p);
                testCount = 0;
            }
            mode = testMode;
            break;
        }
        if (mode != 0) {
            int n;
            gif_StartPacketPri(11);
            n = GetSkeltonFocusNode(viewObj, 0x23);
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            DrawLineG(&p, &focusColor, (char *)viewObj->dobj->nodeMtx + n * 64 + 48, &testRingColor,
                      0);
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
        viewObj->dobj->root.hand1.ikMode = lookMode;
        if (lookMode != 0) {
            int n;
            lookAtTest(&look, lookRadius, &p, &q.v, (pad[1].ana[1] - 128) * 2.0f,
                       -pad[1].ana[0] * 256);
            CopyVector(viewObj->dobj->root.hand1.ikDir, &look);
            gif_StartPacketPri(11);
            n = GetSkeltonFocusNode(viewObj, 3);
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            DrawLineG(&look, &col, (char *)viewObj->dobj->nodeMtx + n * 64 + 48, &q.v, 0);
            gif_EndPacket();
        }
        viewObj->dobj->root.hand0.ikMode = headMode;
        if (headMode != 0) {
            int n;
            lookAtTest(&head, lookRadius, &p, &q.v, (pad[1].ana[1] - 128) * 2.0f,
                       -pad[1].ana[0] * 256);
            CopyVector(viewObj->dobj->root.hand0.ikDir, &head);
            gif_StartPacketPri(11);
            n = GetSkeltonFocusNode(viewObj, 0x13);
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            DrawLineG(&head, &col, (char *)viewObj->dobj->nodeMtx + n * 64 + 48, &q.v, 0);
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
