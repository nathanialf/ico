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

/* PAL's rope interpolation rate (ropeInterRate) is not in this build's
   .sdata */

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

INCLUDE_ASM(orientDebug);

INCLUDE_ASM_LIT(orientDebug);

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

INCLUDE_ASM(sendStateMail);

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

INCLUDE_ASM(shiftMotionOrientEndFunc);

inline void CopyBlendMotionDataSource(void *self, short ang);

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
INCLUDE_ASM(parallelMotionShift);

/* The ignored-request report: how many times in a row, and for which
   motion. */
static int ignoreCount = 0; /* derived name */

static int ignoreMotion = 0; /* derived name */

/* The four one-character spinners the debug line cycles with the frame count. */
typedef struct MotOriSpin { /* field names derived */
    char *s[4];
} MotOriSpin; /* derived name */

INCLUDE_ASM(SetMotionRequest);

INCLUDE_ASM(D_0067AF10);

INCLUDE_ASM_LIT(SetMotionRequest);

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

INCLUDE_ASM(getStreamMotionGeometry);

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

INCLUDE_ASM(getStreamShapeGeometry);

INCLUDE_ASM(func_001D4380);

static void getStreamMotion(void *self);

INCLUDE_ASM(ExecMotionOrient);

INCLUDE_ASM(SetNodeRotationLimitDataTable);

INCLUDE_ASM(GetMotionOrient);

INCLUDE_ASM(getMotionOrient);

INCLUDE_ASM(SetParallelMotionTableWithNoRequest);

INCLUDE_ASM(SetParallelMotionTable);

INCLUDE_ASM(InitMotionOrient);

INCLUDE_ASM(GetCurrentMotionDirectionAdjustFlag);

INCLUDE_ASM(ExecuteSlipProc);

INCLUDE_ASM(ExecutePauseSlipProc);
