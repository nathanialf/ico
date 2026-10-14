#include "debug.h"
#include "debug_exception.h"
#include "gobj.h"
#include "s_init.h"
#include "frameDependSequence.h"
#include "matrixDrive.h"
#include "motionManager.h"
#include "motionManager2.h"
#include "geometryManager.h"
#include "wireLetter.h"
#include "obj_manager.h"
#include "quaternion.h"
#include "motionOrientManager.h"
#include <stdio.h>
#include <assert.h>
#include "streamMotionManager.h"
#include "tableSin.h"
#include "typedef.h"
#include "GifPacket.h"
#include <libvu0.h>
#include "GsBase.h"
#include "motionFileManager.h"
#include "fieldCollision.h"
#include <math.h>
#include "lineManager.h"
#include "main.h"
#include "Matrix.h"
#include "include_asm.h"

static void getMotionGeometry(void *self);
static void getStreamBlendShapeGeometry(void *self, void *m0, void *m1, float t);
static void getStreamShapeGeometry(void *self, void *sm);
static void shiftMotionData(int obj, int motion, int request, int shiftMode);

/* The rope's interpolation rate: the chain's geometry sets it from the hang
   height and rootUpdateY_Rope moves the root by it. */
float ropeInterRate = 0.0f; /* derived name */

extern MotionOrientEntry motionOrient[];

struct MotOriHead8 { /* field names derived */
    long long v;
} __attribute__((packed));

struct MotOriFloat { /* field names derived */
    float frame;
};

/* the object's display object, read through geometryManager.h's SubHandle
   union */
#define MOWORK(self) (((SubHandle *)&((GObj *)(self))->dobj)->sub) /* derived name */

/* The 0x470 motion work area is motionManager.h's MotCtrl. */

/* the trigger definition table, read-only */
extern const MotionDef motionKind[];

/* the seventeen fixed captions the orientation debug window prints, one per
   trigger kind, plus the window's own format */

/* declared here: ico2/fumi/src/commonact.c declares the table without
   const, so motionOrientManager.h cannot carry it */
extern const MotOriName motionOriKind[];
static void orientDebug(void *self, int idx, int y);

INCLUDE_ASM(orientDebug);

static inline void checkMotionKind(int i, int j) /* derived name */
{
    if (motionKind[i].blendKind != 320) {
        char buf[256];

        /* EUC-JP: "the node-blending motion (%s) uses a node-blending motion again" */
        debug_StdPrintfDummy(
            "ノードを混ぜるモーション(%s)が、\n再度ノードを混ぜるモーションを利用しています。\n",
            motionKind[j].name);
        sprintf(buf, "NODE BLEND MOTION \"%s\" REFERS\nNODE BLEND MOTION RECURSIVELY.\n",
                motionKind[j].name);
        debug_assertMessage(__FILE__, 152, buf);
        __assert(__FILE__, 152, "e");
    }
}

int GetNbMotionFrames(int id);

INCLUDE_ASM(GetNbMotionFrames);

INCLUDE_ASM(GetMotionPlaySpeedRatio);

INCLUDE_ASM(execFrameTrigger);

/* inlined here and in UpdateFrameCounter; the store order is the
 * source's own */
static __inline__ void clearFrameTriggerState(void *self) /* derived name */
{
    GOBJ_SUB(self)->ctrl.trigger1 = 0;
    GOBJ_SUB(self)->ctrl.trigger2 = 0;
    GOBJ_SUB(self)->ctrl.trigger1Done = 0;
    GOBJ_SUB(self)->ctrl.trigger2Done = 0;
}

/* three range tests; shiftMotionData and UpdateFrameCounter both inline
 * them */
static __inline__ int checkFrameInRange(int mot, float t) /* derived name */
{
    if ((float)motionKind[mot].triggerStart <= t && t <= (float)motionKind[mot].triggerEnd) {
        return 1;
    }
    return 0;
}

static __inline__ int checkFrameInRange2(int mot, float t, float t2) /* derived name */
{
    if ((float)motionKind[mot].trigger2Start <= t2 && t <= (float)motionKind[mot].trigger2End) {
        return 1;
    }
    return 0;
}

static __inline__ int checkMotionShiftRange(int mot, float t, float t2) /* derived name */
{
    const MotionDef *e = &motionKind[mot];
    float a = (float)e->shiftStart;
    float b = (float)e->shiftLength;
    float ab = a + b;

    if (a < 0.0f || b < 0.0f) {
        return 0;
    }
    if (e->flags.bits.shiftInside) {
        if (a < t2 && t < ab) {
            return 1;
        }
        return 0;
    }
    if (a < t2 && t < ab) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM(UpdateFrameCounter);

static void sendStateMail(void *self)
{
    float m[4][4];
    float pos[4];
    struct MotCtrl *w = &MOWORK(self)->ctrl;

    if (debug_wire_string != 0) {
        MatrixDrive_PushMatrix();
        sceVu0TransposeMatrix(m, matrixptr + 0x80);
        m[0][3] = m[1][3] = m[2][3] = 0.0f;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        GetRootPosition(pos, self);
        MatrixDrive_TransMatrixV((char *)pos);
        sceVu0MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), m);
    }
    if (w->flags & 0x2) {
        if (debug_wire_string != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, 80.0f, 0.0f);
            DispWireString("HIT");
            MatrixDrive_PopMatrix();
        }
    }
    if (w->flags & 0x4) {
        iosOmSendMail(self, 7, self);
        if (debug_wire_string != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(-50.0f, 0.0f, 0.0f);
            DispWireString("FALL");
            MatrixDrive_PopMatrix();
        }
    }
    if (w->flags & 0x10) {
        iosOmSendMail(self, 8, self);
        if (debug_wire_string != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(50.0f, 40.0f, 0.0f);
            DispWireString("CLIFF");
            MatrixDrive_PopMatrix();
        }
    }
    if (w->flags & 0x20) {
        iosOmSendMail(self, 9, self);
        if (debug_wire_string != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(50.0f, 0.0f, 0.0f);
            DispWireString("WALL");
            MatrixDrive_PopMatrix();
        }
    }
    if (w->flags & 0x1000) {
        iosOmSendMail(self, 33, self);
        if (debug_wire_string != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(50.0f, 0.0f, 0.0f);
            DispWireString("UPPER WALL");
            MatrixDrive_PopMatrix();
        }
    }
    if (w->flags & 0x8) {
        iosOmSendMail(self, 10, self);
        if (debug_wire_string != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, -80.0f, 0.0f);
            DispWireString("LANDING");
            MatrixDrive_PopMatrix();
        }
    }
    if (w->flags & 0x400) {
        iosOmSendMail(self, 26, self);
        if (debug_wire_string != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, -80.0f, 0.0f);
            DispWireString("WATER");
            MatrixDrive_PopMatrix();
        }
    }
    if (w->flags & 0x800) {
        iosOmSendMail(self, 27, self);
    }
    if (w->flags & 0x100) {
        iosOmSendMail(self, 15, self);
    }
    if (w->flags & 0x200) {
        iosOmSendMail(self, 16, self);
    }
    if (debug_wire_string != 0) {
        MatrixDrive_PopMatrix();
    }
}

/* Both shift functions inline it: it walks the request table at the work
 * area's 0x1C and returns the paired entry from the table at 0x20. */
static inline int searchMotionShift(void *self, int id, int cur) /* derived name */
{
    struct MotCtrl *m = &MOWORK(self)->ctrl;
    int i;

    if (m->shiftReq != 0 && m->shiftNext != 0) {
        for (i = 0; (m->shiftReq)[i] != -1; i++) {
            if ((m->shiftReq)[i] == id) {
                if ((m->shiftNext)[i] == cur) {
                    return 0x479;
                }
                return (m->shiftNext)[i];
            }
        }
    }
    return -1;
}

/* mirrorMotionTable is six {request, substitute} pairs */
static __inline__ int searchAltMotion(int req) /* derived name */
{
    int i;

    for (i = 0; i < 6; i++) {
        if (mirrorMotionTable[i].req == req) {
            return mirrorMotionTable[i].alt;
        }
    }
    return req;
}

INCLUDE_ASM(shiftMotionData);

static void shiftMotionOrientEndFunc(void *self);

INCLUDE_ASM(shiftMotionOrientEndFunc);

static void shiftMotionOrientBeginFunc(void *self, int motion, int request, int shiftMode);

INCLUDE_ASM(shiftMotionOrientBeginFunc);

void ForTest_ForceShiftMotion(int obj, int motion)
{
    shiftMotionData(obj, motion, motion, 0);
}

/* Clear the pending-shift words and report whether the entry may start.
 * The 0x479 arm's refusal goes to the guard's `return 0`. */
static inline int checkMotionShiftReady(struct MotCtrl *m, MotionOrientEntry *p) /* derived name */
{
    int kind;

    m->ctrlFlags = 0;
    m->shifted = 0;
    if (m->orientUpdateOff != 0 || p->kind == -1) {
    fail:
        return 0;
    }
    kind = p->nextId;
    m->orientReq = kind;
    if (kind == 0x479) {
        if (m->frameEnd == 0) {
            goto fail;
        }
        m->ctrlFlags = 4;
        return 1;
    }
    if (m->frameEnd != 0) {
        m->animFrame = (float)(GetNbMotionFrames(m->motion) - 1) - 1.0e-6f;
        m->ctrlFlags |= 0x10;
        return 1;
    }
    return p->shiftFrom != -1 && (float)p->shiftFrom < m->animFrame;
}

static int normalMotionShift(void *self, int force);

INCLUDE_ASM(normalMotionShift);

/* parallelMotionOrient is 54 rows of five words, keyed on the current and
 * the requested motion. */
static inline MotionOrientEntry *findParallelMotion(int cur, int next) /* derived name */
{
    int i;

    if (cur == next) {
        return &motionOrient[2467];
    }
    for (i = 0; i < 54; i++) {
        if (parallelMotionOrient[i].id == cur) {
            if (parallelMotionOrient[i].kind == next) {
                return (MotionOrientEntry *)&parallelMotionOrient[i];
            }
        }
    }
    return 0;
}

/* the -1 test encloses the body and every refusal falls to the one
 * `return 0` at the end */
static int parallelMotionShift(void *self)
{
    struct MotCtrl *m = &MOWORK(self)->ctrl;
    int next = searchMotionShift(self, m->request, m->motion);
    MotionOrientEntry *p;

    if (next != -1) {
        p = findParallelMotion(m->motion, next);

        if (p != 0) {
            if (checkMotionShiftReady(&MOWORK(self)->ctrl, p) != 0) {
                shiftMotionOrientEndFunc(self);
                shiftMotionOrientBeginFunc(self, p->nextId, m->request, p->shiftMode);
                return 1;
            }
        } else if (next != 0x479) {
            MotionOrientEntry e = {m->motion, m->orientKind, next, m->shiftFrom, m->shiftMode};

            if (checkMotionShiftReady(&MOWORK(self)->ctrl, &e) != 0) {
                shiftMotionOrientEndFunc(self);
                shiftMotionOrientBeginFunc(self, next, m->request, m->shiftMode);
                return 1;
            }
        }
    }
    return 0;
}

/* The ignored-request report: how many times in a row, and for which
   motion. */
static int ignoreCount = 0; /* derived name */

static int ignoreMotion = 0; /* derived name */

/* The four one-character spinners the debug line cycles with the frame count. */
typedef struct MotOriSpin { /* field names derived */
    char *s[4];
} MotOriSpin; /* derived name */

INCLUDE_ASM(SetMotionRequest);

INCLUDE_ASM(getNodeBlendedFloatingMotion);

/* the slope vector getMotionGeometry normalises for its pitch angle */
static sceVu0FVECTOR slopeVector = {0.0f, 0.0f, 0.0f, 0.0f}; /* derived name */

/* getMotionGeometry is its only caller */
static inline void getMotionRootPos(struct MotCtrl *w, float *v) /* derived name */
{
    int m = blendMotionKind[motionKind[w->motion].blendKind].motion;
    float t = w->lastFrame;

    checkMotionKind(m, w->motion);
    GetFloatingMotionRootPos(v, motionTable[m], t);
}

/* The motion-loaded assert and the node-count assert, each an inlined body
 * of its own with its own 1024-byte message buffer. */
static inline void assertMotionLoaded(struct MotCtrl *w, int *md) /* derived name */
{
    if (md == 0) {
        char buf[1024];

        sprintf(buf, "THE MOTION \"%s\"(%d)\nDID NOT LOAD IN THIS STAGE\nOR IS INVALID ID.\n",
                motionKind[w->motion].name, w->motion);
        debug_assertMessage(__FILE__, 1275, buf);
        __assert(__FILE__, 1275, "e");
    }
}

static inline void assertMotionNodeCount(struct MotCtrl *w, int *md, int n) /* derived name */
{
    int *e = (int *)md[3];
    int i = 0;

    do {
        i++;
    } while (*e++ != 0);
    if (i - 1 != n) {
        char buf[1024];

        sprintf(
            buf,
            "THE NUMBER OF NODE DATAS OF MOTION\n\"%s\"(%d SKELTONS) DOES NOT MATCH\nTHE NUMBER OF SKELTON NODES(%d SKELTONS)\n",
            motionKind[w->motion].name, i - 1, n);
        debug_assertMessage(__FILE__, 1287, buf);
        __assert(__FILE__, 1287, "e");
    }
}

INCLUDE_ASM(getMotionGeometry);

/* The two line colours the debug bar graph draws with: 16-byte records,
 * 8-byte aligned; ico2/omori/src/camera-editor.c spells the union the same
 * way (BoxCol4). */
typedef union { /* field names derived */
    unsigned int c[4];
    unsigned long long w[2];
} MotOriCol4; /* derived name */

/* debug_bar_flag is debug.o's debug bar mode, which ico2/common/src/debug.c
 * clears and debug_DrawBar dispatches on 1 and 2; this file reads it as an
 * enumerated mode. */
enum DebugDisplayMode {
    DEBUG_DISPLAY_OFF,
    DEBUG_DISPLAY_ON,
    DEBUG_DISPLAY_FULL
}; /* derived name */

extern enum DebugDisplayMode debug_bar_flag;
static void getShapeGeometry(void *self);

INCLUDE_ASM(getShapeGeometry);

/* both stream-geometry functions inline it (once and twice) */
static inline int getStreamVec(void *self, void *sm, float *v, void *mot) /* derived name */
{
    float s = MOWORK(self)->nodes->scale[0];

    if (GetStreamMotion(mot, v, sm, MOWORK(self)->skel) != 0) {
        if (MOWORK(self)->streamScale != 0) {
            _ScaleVectorXYZ(v, v, s);
        }
        v[0] -= MOWORK(self)->streamOfs[0];
        v[1] -= MOWORK(self)->streamOfs[1];
        v[2] += MOWORK(self)->streamOfs[2];
        return 1;
    }
    return 0;
}

static void getStreamMotionGeometry(void *self, void *sm)
{
    float v[4];
    StreamElem mot[MOWORK(self)->skelNodeNum];

    if (getStreamVec(self, sm, v, mot)) {
        GetGeometryOfMotion(self, mot, mot, v, 1.0f, ZeroVector, -1);
        CopyMotion(MOWORK(self)->motionBuf, mot, MOWORK(self)->skelNodeNum);
        CopyVector(MOWORK(self)->motionPos, v);
        DispSkelton(self, mot);
    }
}

static void getStreamBlendMotionGeometry(void *self, void *sm0, void *sm1, float t)
{
    float v0[4];
    float v1[4];
    float v2[4];
    int n = MOWORK(self)->skelNodeNum;
    StreamElem mot0[n];

    if (getStreamVec(self, sm0, v0, mot0)) {
        StreamElem mot1[n], mot2[n];

        getStreamVec(self, sm1, v1, mot1);
        GetBlendedMotion(mot2, v2, mot1, v1, mot0, v0, t, MOWORK(self)->blendless, n);
        GetGeometryOfMotion(self, mot2, mot2, v2, 1.0f, ZeroVector, -1);
        CopyMotion(MOWORK(self)->motionBuf, mot2, MOWORK(self)->skelNodeNum);
        CopyVector(MOWORK(self)->motionPos, v2);
        DispSkelton(self, mot2);
    }
}

/* The clamp and its own `int *p` declaration, a macro with a block body
 * shared by getStreamBlendShapeGeometry and getStreamShapeGeometry.  The test
 * is this programmer's absolute-value idiom (box.c, geometryManager.c,
 * motionManager.c). */
#define SET_SHAPE_VALUE(self, i, x) /* derived name */                                             \
    {                                                                                              \
        int *p = (int *)((i) * 4 + *(int *)((char *)*(int *)((char *)(self) + 0x15C) + 0x838));    \
                                                                                                   \
        if (0.0001f < ((x) < 0.0f ? -(x) : (x))) {                                                 \
            *(float *)p = (x);                                                                     \
        } else {                                                                                   \
            *p = 0;                                                                                \
        }                                                                                          \
    }

static void getStreamBlendShapeGeometry(void *self, void *sm0, void *sm1, float t)
{
    int i;
    int n = GOBJ_SUB(self)->morphNum;
    if (n != 0) {
        float a[n];
        if (GetStreamShapeMotion(a, sm0) != 0) {
            float b[n];

            GetStreamShapeMotion(b, sm1);
            for (i = 0; i < n; i++) {
                float x;
                x = (a[i] * (1.0f - t) + b[i] * t) * 0.01f;
                SET_SHAPE_VALUE(self, i, x);
            }

        } else
            for (i = 0; i < n; i++)
                *(int *)(*(int *)((char *)GOBJ_SUB(self) + 0x838) + i * 4) = 0;
    }
}

static void getStreamShapeGeometry(void *self, void *sm)
{
    int n = GOBJ_SUB(self)->morphNum;

    if (n != 0) {
        float buf[n];
        int i;

        if (GetStreamShapeMotion(buf, sm) != 0) {
            for (i = 0; i < n; i++) {
                float x = buf[i] * 0.01f;
                SET_SHAPE_VALUE(self, i, x);
            }
        } else {
            for (i = 0; i < n; i++) {
                *(int *)(*(int *)((char *)GOBJ_SUB(self) + 0x838) + i * 4) = 0;
            }
        }
    }
}

static void getStreamMotion(void *self)
{
    int s = MOWORK(self)->ctrl.stream;
    char a[GetDataSizeOfStreamMotion(s)];
    float t = GetStreamMotionData(a, s);

    if (t <= 0.0f) {
        getStreamMotionGeometry(self, a);
        getStreamShapeGeometry(self, a);
    } else {
        char b[GetDataSizeOfStreamMotion(s)];

        GetStreamMotionDataNext(b, s);
        getStreamBlendMotionGeometry(self, a, b, t);
        getStreamBlendShapeGeometry(self, a, b, t);
    }
}

void ExecMotionOrient(void *self)
{
    struct MotCtrl *w = &GOBJ_SUB(self)->ctrl;

    if (w->shiftStop != 0) {
        /* EUC-JP: "the motion replacement function is stopped" */
        debug_StdPrintfDummy("\033[36mモーション置き換え機能が停止しています。\033[m: %p\n", self);
    }
    if (w->stream == -1) {
        if (w->orientKind != 269) {
            normalMotionShift(self, 0);
        } else {
            parallelMotionShift(self);
        }
        if ((debug_mot_debug_target == 0 && self == boyGObj) ||
            (debug_mot_debug_target == 1 && self == girlGObj) ||
            (debug_mot_debug_target == 2 && self == isysGObjSearchFromObjKindID_begin(32)) ||
            (debug_mot_debug_target == 3 && self == isysGObjSearchFromObjKindID_begin(4)) ||
            (debug_mot_debug_target == 4 && self == isysGObjSearchFromObjKindID_begin(47))) {
            if (w->shifted != 0) {
                if (ignoreCount != 0 && debug_window_flag != 0) {
                    debug_PrintFontWindow(0xC0FF20, "\n ");
                }
                orientDebug(self, w->orientKind, 0xE0FF20);
                ignoreCount = 0;
            }
        }
        if (w->justShifted != 0) {
            int n = GOBJ_SUB(self)->morphNum;
            int i;

            for (i = 0; i < n; i++) {
                *(int *)(i * 4 + *(int *)((char *)GOBJ_SUB(self) + 0x838)) = 0;
            }
        }
        getMotionGeometry(self);
        getShapeGeometry(self);
    } else {
        getStreamMotion(self);
    }
}

void SetNodeRotationLimitDataTable(void *self, int from, int to);

INCLUDE_ASM(SetNodeRotationLimitDataTable);

inline int ExecuteSlipProc(GObj *self)
{
    Sub15C *e = self->dobj;
    if (e->ctrl.lastSlipFlags != e->ctrl.slipFlags) {
        StopSEPackageWithGroupVariation(self, 1);
        if (GOBJ_SUB(self)->ctrl.slipFlags & 0x100000) {
            ExecuteSEPackageWithGroupVariation(self, 114, 1);
        }
        if (GOBJ_SUB(self)->ctrl.slipFlags & 0x200000) {
            ExecuteSEPackageWithGroupVariation(self, 116, 1);
        }
        if (GOBJ_SUB(self)->ctrl.slipFlags & 0x400000) {
            ExecuteSEPackageWithGroupVariation(self, 118, 1);
        }
        if (GOBJ_SUB(self)->ctrl.slipFlags & 0x800000) {
            ExecuteSEPackageWithGroupVariation(self, 120, 1);
        }
    }
    return 1;
}

inline int ExecutePauseSlipProc(GObj *self)
{
    if (systemStatus[5] != 0) {
        GOBJ_SUB(self)->ctrl.lastSlipFlags = 0;
        StopSEPackageWithGroupVariation(self, 1);
    }
    return 1;
}

INCLUDE_ASM(GetMotionOrient);

INCLUDE_ASM(getMotionOrient);

INCLUDE_ASM(CopyBlendMotionDataSource);

INCLUDE_ASM(SetParallelMotionTableWithNoRequest);

INCLUDE_ASM(SetParallelMotionTable);

INCLUDE_ASM(InitMotionOrient);

INCLUDE_ASM(GetCurrentMotionDirectionAdjustFlag);
