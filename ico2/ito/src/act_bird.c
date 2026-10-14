#include "itou_common.h"
#include "sugiCommon.h"
#include "act_bird.h"
#include "memory.h"
#include "pad.h"
#include "gobj.h"
#include "act.h"
#include "lightning.h"
#include "DisplayP2O.h"
#include "StageAnimation.h"
#include "geometryManager.h"
#include "lodManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "tableSin.h"
#include "wireLetter.h"
#include <math.h>
#include <libvu0.h>
#include <string.h>
#include <stdio.h>
#include "typedef.h"
#include "GsBase.h"
#include "Matrix.h"
#include "stageMultiBgaManager.h"
#include "boyact.h"
#include "quaternion.h"
#include "main.h"
#include "fieldCollision.h"
#include "itou_sub.h"
#include "motionOrientManager.h"
#include "ios.h"
#include "debug.h"
#include "obj_manager.h"
#include "include_asm.h"

static void Debug_StickControl(GObj *self);
static void Debug_WireString_Bird(float *pos, char *fmt, ...);

inline float vector_angle_degree(void *a, void *b)
{
    float v0[4];
    float v1[4];
    sceVu0Normalize(v0, a);
    sceVu0Normalize(v1, b);
    return radians_to_degrees(acosf(sceVu0InnerProduct(v0, v1)));
}

static void interp_vector_sa(float *dst, float *a, float *b, float sa)
{
    float na[4];
    float nb[4];
    float va[4];
    float vb[4];
    float sum[4];
    float ang;
    /* fraction of the full angle that the `sa` step covers */
    float rate;

    sceVu0Normalize(na, a);
    sceVu0Normalize(nb, b);
    ang = acosf(sceVu0InnerProduct(na, nb));
    if (ang < sa) {
        sceVu0CopyVector(dst, nb);
        return;
    }

    rate = sa / ang;
    sceVu0ScaleVectorXYZ(va, na, GetTableSin((short)((1.0f - rate) * ang * 10430.378f)));
    sceVu0ScaleVectorXYZ(vb, nb, GetTableSin((short)(rate * ang * 10430.378f)));
    sceVu0AddVector(sum, va, vb);
    sceVu0DivVector(dst, sum, GetTableSin((short)(ang * 10430.378f)));
}

void birdBeforeFunc(GObj *self)
{
    Act *act = GOBJ_ACT(self);
    BirdWork *w = GOBJ_SUB(self)->work;
    float there[4];
    float here[4];
    int i;
    GObjMailQueue *q = (GObjMailQueue *)&self->mailBox;

    for (i = 0; i < q->num; i++) {
        GObjMailEntry *e = &q->e[i];
        float len;

        GetRootPosition(there, e->data);
        GetRootPosition(here, self);
        len = _GetLengthXZ(there, here);
        switch (e->mail) {
        case 423:
            if (len < 200.0f) {
                w->scared = 1;
                GetRootPosition(w->scarer, e->data);
            }
            break;

        case 424:
            if (len < 250.0f) {
                act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            }
            break;

        case 10: {
            int st = GOBJ_SUB(self)->ctrl.motion;

            if (st >= 1139 && st <= 1141) {
                act->motReq = SetMotionRequest(self, 322, act->env.motOriReq);
            }
            break;
        }

        case 7:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 26:
        case 27:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 419:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 420:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 421:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 422:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;
        }
    }
    q->num = 0;
    /* the actor's motion orient request, refreshed from the copy the
       sub-object keeps at 0x180 */
    act->env.motOriReq = *(MotOriReq *)&GOBJ_SUB(self)->root.wall;
}

/* --- act_bird.c's own small helpers, inlined into subBirdBrainMain --- */

/* a point 100 units along `dir` from `p` */
static __inline__ void point_ahead(float *dst, float *p, float *dir) /* derived name */
{
    float v[4];

    sceVu0ScaleVector(v, dir, 100.0f);
    sceVu0AddVector(dst, p, v);
}

static __inline__ float rand_range(float a, float b) /* derived name */
{
    return random_unit() * (b - a) + a;
}

static __inline__ float rand_flip(float v) /* derived name */
{
    if (random_unit() <= 0.5f) {
        v = -v;
    }
    return v;
}

static __inline__ float rand_range_rad(float a, float b) /* derived name */
{
    return degrees_to_radians(rand_range(a, b));
}

static __inline__ float rand_small_turn(void) /* derived name */
{
    return degrees_to_radians(rand_flip(rand_range(1.0f, 2.0f)));
}

/* turn `v` about Y by `ang` radians */
static __inline__ void rotate_y(float *v, float ang) /* derived name */
{
    float m[16];
    float mr[16];

    sceVu0UnitMatrix(m);
    sceVu0RotMatrixY(mr, m, ang);
    apply_matrix_w1(v, mr, v);
}

static void trans_bird(void *self, float *w)
{
    float down[4] = {0.0f, -1.0f, 0.0f, 0.0f};
    float pos[4];
    float dir[4];
    float fwd[4];
    float dv[4];

    w[4] = (w[0] - w[2]) * w[6] + w[2];
    w[5] = (w[1] - w[3]) * w[6] + w[3];
    w[6] = w[6] + w[7];
    if (w[6] > 1.0f) {
        w[6] = 1.0f;
    }
    GetRootPosition(pos, self);
    _GetMotionDirection(dir, self);
    sceVu0ScaleVectorXYZ(fwd, dir, w[4] * 0.7f);
    sceVu0ScaleVectorXYZ(dv, down, w[5]);
    sceVu0AddVector(fwd, fwd, dv);
    sceVu0AddVector(pos, pos, fwd);
    SetRootPosition(self, pos);
}

/* point the bird `ang` radians round from where it faces */
static __inline__ void turn_bird(void *self, float ang) /* derived name */
{
    float d[4];

    _GetMotionDirection(d, self);
    rotate_y(d, ang);
    SetMotionDirection(self, d);
}

/* restart the flap wave from where it currently stands */
static __inline__ void set_wave(float *w, float a, float b, float step) /* derived name */
{
    w[0] = a;
    w[1] = b;
    w[7] = step;

    w[2] = w[4];
    w[3] = w[5];
    w[6] = 0.0f;
}

/* Actor sub-thread body: the actor scheduler resumes this frame after every
   _ACTWait yield, so the entry GObj lives in its stack home, not a register. */
void subBirdBrainMain(void *volatile gobj);

INCLUDE_ASM(subBirdBrainMain);

inline void subBirdControl(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        Debug_StickControl(gobj);
        _ACTWait(1);
    }
}

inline void subBirdCollision(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        _ACTWait(1);
    }
}

inline void actBirdStart(void *gobj)
{
    Act *act;

    act = (Act *)actInitialize(gobj);
    _ACTWait(1);
    actCreateSubThread(subBirdBrainMain, 20);
    actCreateSubThread(subBirdControl, 21);
    actCreateSubThread(subBirdCollision, 21);
    act->motReq = SetMotionRequest(gobj, 270, act->env.motOriReq);
}

static void Debug_WireString_Bird(float *pos, char *fmt, ...)
{
    float m[16];
    char buf[256];
    void *args = (char *)__builtin_next_arg(fmt) - 0x30;

    MatrixDrive_PushMatrix();
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 128));
    m[3] = m[7] = m[11] = 0.0f;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(pos[0], pos[1], pos[2]);
    sceVu0MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), m);
    MatrixDrive_PushMatrix();
    vsprintf(buf, fmt, args);
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    DispWireString(buf);
    MatrixDrive_PopMatrix();
    MatrixDrive_PopMatrix();
}

static void Debug_StickControl(GObj *self)
{
    float dir[4];
    Act *ext = GOBJ_ACT(self);

    if (self == CurrentTargetGObj) {
        iosPadConnect(&ext->pad, 0, 0, &ext->padConf);
        iosPadRead(&ext->pad);
        iosPadGetStick(&ext->pad, &ext->stick, 0, 2, 2, 0);
        _GetMotionDirection(dir, self);
        ext->stick.angle = CorrectStickInfo(dir, &ext->stick);
        if (ext->stick.mag > 0.001f) {
            ConvertStickToAbsCoord(ext->dir, &ext->stick);
        }
    } else if (self == CurrentTargetGObjSub) {
        iosPadConnect(&ext->pad, 0, 1, &ext->padConf);
    } else {
        iosPadConnect(&ext->pad, 0, 1, &ext->padConf);
    }
}

void BirdGeo(void *self)
{
    ExecMotionOrient(self);
}

INCLUDE_ASM(BirdDL);

inline BirdWork *InitBirdGeo(GObj *gobj, void *home)
{
    BirdWork *w;

    w = iosMallocDebug(ios_partition_sugipon, sizeof(BirdWork), __FILE__, 978);
    memset(w, 0, sizeof(BirdWork));
    CopyVector(w->home, home);
    w->scared = 0;
    InitMotionOrient(gobj, 2421, 2467, -1, -1, 1134);

    GOBJ_SUB(gobj)->ctrl.floorFit = 1;
    GOBJ_SUB(gobj)->ctrl.cliffWallCheck = 0;
    GOBJ_SUB(gobj)->ctrl.wallReact = 1;
    GOBJ_SUB(gobj)->ctrl.catchBoy = 0;
    /* the animation frame at 0x4AC and the word after it start at the same
       random frame */
    ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x4AC))->f = random_unit() * 100.0f;
    ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x4B0))->f = ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x4AC))->f;
    GOBJ_SUB(gobj)->ctrl.waterDrag = 0;
    SetLodLevel(gobj, 3);
    return w;
}

inline void BirdAI(void) {}

void _ACTSendMailToBird(void *obj, int mail, void *data)
{
    iosOmSendMail(obj, mail, data);
}

inline void _ACTSendMailToBirdAll(int mail, void *data)
{
    void *obj = isysGObjSearchFromObjKindID_begin(32);
    while (obj != 0) {
        _ACTSendMailToBird(obj, mail, data);
        obj = isysGObjSearchFromObjKindID_next(obj);
    }
}
