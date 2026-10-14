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

INCLUDE_ASM(birdBeforeFunc);

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
INCLUDE_ASM(subBirdBrainMain);

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

INCLUDE_ASM(Debug_StickControl);

void BirdGeo(void *self)
{
    ExecMotionOrient(self);
}

INCLUDE_ASM(BirdDL);

inline void BirdAI(void) {}

INCLUDE_ASM_LIT(InitBirdGeo);

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

INCLUDE_ASM(vector_angle_degree);

INCLUDE_ASM(subBirdControl);

INCLUDE_ASM(subBirdCollision);

INCLUDE_ASM(actBirdStart);

INCLUDE_ASM(InitBirdGeo);
