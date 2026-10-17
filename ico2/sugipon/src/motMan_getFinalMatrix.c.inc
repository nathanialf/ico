#include "include_asm.h"

/* motMan_getFinalMatrix.c.inc: the motion manager's final node matrices and their angle limits; motionManager.c includes this file. */
/* Only _getFinalMatrix uses these two.  The first gives a point relative to
 * the root placed at the matrix's translation, the second the same vector in
 * the current matrix's local axes. */
static inline void getRootRelativePos(float *out, sceVu0FVECTOR *mtx, float *pos) /* derived name */
{
    float w[4];

    AddVectorXYZ(w, mtx[3], skelRoot->pos);
    SubVectorXYZ(out, pos, w);
    out[3] = 0.0f;
}

static inline void getLocalTargetDir(float *out, float *pos) /* derived name */
{
    float tmp[4];

    getRootRelativePos(tmp, MatrixDrive_GetMatrix(), pos);
    MatrixDrive_PushMatrixWithNoCopy();
    MatrixDrive_SetTransposeMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetLastMatrix());
    sceVu0ApplyMatrix(out, MatrixDrive_GetMatrix(), tmp);
    MatrixDrive_PopMatrix();
}

/* the degree conversion and the clamped ratio limitHPAngleAndSetB repeats;
   32768 units are 180 degrees */
#define ANG_OF_DEG(x) ((x) * 32768.0f / 180.0f) /* derived name */
#define ANG_RATE(v, lim)                        /* derived name */                                 \
    ((lim) == 0.0f ? 0.0f : ((v) / (lim) < 0.0f ? -((v) / (lim)) : (v) / (lim)))

/* lim is the motion program's interp record, the same one limitInterpAngle
   reads at +0x30 and +0x48.  hp and pp are the heading and pitch of the turn
   being limited, bp the bank the record's tables interpolate from them;
   prevH is the heading the turn had, whose side the new one may not cross to,
   and prevP the pitch it had. */
static void limitHPAngleAndSetB(short *hp, short *pp, short *bp, MotLimAng *lim, short h,
                                short prevH, short p, short prevP, int setb, int setflag,
                                float rate)
{
    *hp = h;
    *pp = p;
    *bp = 0;

    if (lim != 0) {
        short rev = (1.0f - rate) * 32768.0f;

        float lo = ANG_OF_DEG(lim[4].h);
        float hi = ANG_OF_DEG(lim[6].h);
        float pdn = lim[9].p;
        float pup = lim[1].p;
        float dnlim;
        float uplim;
        float t;
        float rp;

        if (prevH < 0 && *hp > 0) {
            int base = rev - 32768;
            short d = (-*hp - base) / rate;

            if ((float)d < ANG_OF_DEG(lim[7].p)) {
                *hp = (short)lo;
                if (setflag) {
                    skelMotCtrl->flags = skelMotCtrl->flags | 0x100;
                }
            }
        }
        if (prevH > 0 && *hp < 0) {
            int base = rev - 32768;
            short d = (*hp - base) / rate;

            if ((float)d < ANG_OF_DEG(lim[7].p)) {
                *hp = (short)hi;
                if (setflag) {
                    skelMotCtrl->flags = skelMotCtrl->flags | 0x200;
                }
            }
        }
        if ((float)*hp < lo) {
            *hp = (short)lo;
            if (setflag) {
                skelMotCtrl->flags = skelMotCtrl->flags | 0x100;
            }
        }
        if (hi < (float)*hp) {
            *hp = (short)hi;
            if (setflag) {
                skelMotCtrl->flags = skelMotCtrl->flags | 0x200;
            }
        }

        if (*hp >= 0) {
            t = ANG_RATE((float)*hp, ANG_OF_DEG(lim[6].h));

            dnlim = ANG_OF_DEG(pdn) + (ANG_OF_DEG(lim[10].p) - ANG_OF_DEG(pdn)) * t;

            uplim = ANG_OF_DEG(pup) + (ANG_OF_DEG(lim[2].p) - ANG_OF_DEG(pup)) * t;

        } else {
            /* the guard is the +0x48 limit, the division the +0x30 one, as in the
               positive arm above */
            t = ANG_OF_DEG(lim[6].h) == 0.0f ? 0.0f
                                             : ((float)*hp / ANG_OF_DEG(lim[4].h) < 0.0f
                                                    ? -((float)*hp / ANG_OF_DEG(lim[4].h))
                                                    : (float)*hp / ANG_OF_DEG(lim[4].h));

            dnlim = ANG_OF_DEG(pdn) + (ANG_OF_DEG(lim[8].p) - ANG_OF_DEG(pdn)) * t;

            uplim = ANG_OF_DEG(pup) + (ANG_OF_DEG(lim[0].p) - ANG_OF_DEG(pup)) * t;
        }

        if ((float)*pp < dnlim) {
            *pp = (short)dnlim;
        }
        if (uplim < (float)*pp) {
            *pp = (short)uplim;
        }

        if (*hp >= 0) {
            float rh = ANG_RATE((float)*hp, hi);
            float va = (ANG_OF_DEG(lim[6].b) - ANG_OF_DEG(lim[5].b)) * rh + ANG_OF_DEG(lim[5].b);

            if (*pp >= 0) {
                float vb =
                    (ANG_OF_DEG(lim[2].b) - ANG_OF_DEG(lim[1].b)) * rh + ANG_OF_DEG(lim[1].b);

                rp = ANG_RATE((float)*pp, uplim);
                *bp = (vb - va) * rp + va;

            } else {
                float vb =
                    (ANG_OF_DEG(lim[10].b) - ANG_OF_DEG(lim[9].b)) * rh + ANG_OF_DEG(lim[9].b);

                rp = ANG_RATE((float)*pp, dnlim);
                *bp = (vb - va) * rp + va;
            }
        } else {
            float rh = ANG_RATE((float)*hp, lo);
            float va = (ANG_OF_DEG(lim[4].b) - ANG_OF_DEG(lim[5].b)) * rh + ANG_OF_DEG(lim[5].b);

            if (*pp >= 0) {
                float vb =
                    (ANG_OF_DEG(lim[0].b) - ANG_OF_DEG(lim[1].b)) * rh + ANG_OF_DEG(lim[1].b);

                rp = ANG_RATE((float)*pp, uplim);
                *bp = (vb - va) * rp + va;

            } else {
                float vb =
                    (ANG_OF_DEG(lim[8].b) - ANG_OF_DEG(lim[9].b)) * rh + ANG_OF_DEG(lim[9].b);

                rp = ANG_RATE((float)*pp, dnlim);
                *bp = (vb - va) * rp + va;
            }
        }

        if (setb) {
            if (*pp >= 0)
                *bp = (float)*bp * (1.0f - rp) + ANG_OF_DEG(lim[1].b) * rp;
            else
                *bp = (float)*bp * (1.0f - rp) + ANG_OF_DEG(lim[9].b) * rp;
        }
    }
}

/* Clamp a turn angle to the motion-program interp range; 0 when the angle
 * is already inside it. */
static inline short limitInterpAngle(MotLimAng *info, short ang) /* derived name */
{
    float lo;
    float hi;

    if (info != 0) {
        lo = info[4].h * 32768.0f / 180.0f;
        hi = info[6].h * 32768.0f / 180.0f;
        if ((float)ang < lo) {
            return (short)lo;
        }
        if (hi < (float)ang) {
            return (short)hi;
        }
    }
    return 0;
}

static int avoidReverseInterpOnCurrentMatrix(float *q, MotLimAng *info, void *out)
{
    float mtx[16];
    Vec16 up;
    Vec16 dir;
    short ang;
    short ang2;

    GetMatrixFromQuaternion(mtx, q);
    _ApplyMatrix(&up, mtx, YUnitVector);
    MatrixDrive_SetTransposeMatrix(mtx, MatrixDrive_GetMatrix());
    _ApplyMatrix(&dir, mtx, &up);
    MatrixDrive_GetTurnYAngleXZ(&ang, &ang2, dir.f[0], dir.f[1], dir.f[2]);
    if (limitInterpAngle(info, ang) != 0) {
        MultiQuaternion(q, GetCurrentQuaternion(), out);
        return 1;
    }
    return 0;
}

/* 0 = inside the range, 1 = outside the plain range, 2 = outside the range
 * scaled by the limit factor; avoidReverseInterpOnCurrentMatrixWithLimit's
 * helper. */
static inline short classifyInterpAngle(MotLimAng *info, short ang, float k) /* derived name */
{
    float lo;
    float hi;
    float a;
    float b;

    if (info != 0) {
        lo = info[4].h * 32768.0f / 180.0f;
        hi = info[6].h * 32768.0f / 180.0f;
        a = lo * k;
        b = hi * k;
        if ((float)ang < a || b < (float)ang)
            return 2;
        if ((float)ang < lo || hi < (float)ang)
            return 1;
    }
    return 0;
}

static void avoidReverseInterpOnCurrentMatrixWithLimit(float *q, MotLimAng *info, void *outA,
                                                       void *outB, float k)
{
    float mtx[16];
    Vec16 up;
    Vec16 dir;
    short ang;
    short ang2;

    GetMatrixFromQuaternion(mtx, q);
    _ApplyMatrix(&up, mtx, YUnitVector);
    MatrixDrive_SetTransposeMatrix(mtx, MatrixDrive_GetMatrix());
    _ApplyMatrix(&dir, mtx, &up);
    MatrixDrive_GetTurnYAngleXZ(&ang, &ang2, dir.f[0], dir.f[1], dir.f[2]);
    switch (classifyInterpAngle(info, ang, k)) {
    case 1:
        MultiQuaternion(q, GetCurrentQuaternion(), outA);
        break;
    case 2:
        MultiQuaternion(q, GetCurrentQuaternion(), outB);
        break;
    }
}

/* The arm IK's angles: the shoulder's turns about Z and Y and the two
   joints' bends. */
static short ikRotZ = 0; /* derived name */

static short ikRotY = 0; /* derived name */

static short ikBend0 = 0; /* derived name */

static short ikBend1 = 0; /* derived name */

/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];

/* The frame-rate factors every blend in _getFinalMatrix scales by: the
 * frame counter pair gives the frames per second of the current mode. */
#define MOT_FPS ((float)((60 - systemStatus[0] * 10) / systemStatus[1])) /* derived name */
#define MOT_SPEED                                                        /* derived name */        \
    (debug_now_motion_viewer != 0 ? (float)debug_face_rot_w_ratio * 0.01f                          \
                                  : skelMotDef->faceRotRatio)
#define MOT_RATE(f) (skelRoot->f * (60.0f / MOT_FPS))                       /* derived name */
#define MOT_BLEND(off) (MOT_RATE(off) + (1.0f - MOT_RATE(off)) * MOT_SPEED) /* derived name */

/* Only _getFinalMatrix uses these two: a unit direction from a heading and
 * a pitch, and the rotation that turns the x axis onto a direction. */
static inline void getDirOfAngle(float *v, short h, short p) /* derived name */
{
    float c = GetTableCos(p);

    v[0] = GetTableCos(h) * c;
    v[1] = GetTableSin(h) * c;
    v[2] = -GetTableSin(p);
    v[3] = 0.0f;
}

static inline void getRotOfDir(float *q, float *v) /* derived name */
{
    float axis[4];
    short ang = GetTableArcCos(_InnerProduct(v, XUnitVector));

    _OuterProduct(axis, v, XUnitVector);
    SetQuaternionByAxisRotateV(q, ang, axis);
}

/* The motion's own rotation for the node, the matrix rebuilt from it, and
 * the stream's offset from the skeleton's rest rotation. */
#define GET_NODE_ROT(q, dq) /* derived name */                                                     \
    MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), node->quat);                      \
    GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());               \
    CopyQuaternion(q, IdentityQuaternion);                                                         \
    DivQuaternion(dq, elem + 16, node->quat)
#define APPLY_ROT(q) /* derived name */                                                            \
    MultiCurrentQuaternion(q);                                                                     \
    GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion())

static void _getFinalMatrix(int id);

INCLUDE_ASM(_getFinalMatrix);

extern double fptodp(float v);

/* EditRotEmphasys's tuning: the two coefficients it shows and edits, the
   switch that turns the editor on and the coefficient selected. */
static float emphasysAccel = 0.1f; /* derived name */

static float emphasysVelocity = 0.97f; /* derived name */

static int emphasysEdit = 0; /* derived name */

static int emphasysSelect = 0; /* derived name */

void EditRotEmphasys(void)
{
    int sel;

    if (pad[1].flags & 0x20) {
        emphasysEdit = emphasysEdit == 0;
    }
    if (emphasysEdit != 0) {
        if (debug_font_flag & 1) {
            debug_Printf(300, 170, 0xFFFFFF00u, "Emphasys Accel   Velocity");
        }
        if (debug_font_flag & 1) {
            debug_Printf(300, 180, emphasysSelect != 0 ? 0xFFFFFF00u : 0x80808000u,
                         "         %1.5f ", emphasysAccel);
        }
        if (debug_font_flag & 1) {
            debug_Printf(300, 180, emphasysSelect != 0 ? 0x80808000u : 0xFFFFFF00u,
                         "                 %1.5f", emphasysVelocity);
        }
        sel = emphasysSelect;
        if (pad[1].flags & 0xA000) {
            sel++;
            sel &= 1;
            emphasysSelect = sel;
        }
        switch (sel) {
        default:
        case 0:
            if (pad[1].rep & 0x1000) {
                emphasysVelocity = emphasysVelocity + 0.01f;
            }
            if (pad[1].rep & 0x4000) {
                emphasysVelocity = emphasysVelocity - 0.01f;
            }
            break;
        case 1:
            if (pad[1].rep & 0x1000) {
                emphasysAccel = emphasysAccel + 0.01f;
            }
            if (pad[1].rep & 0x4000) {
                emphasysAccel = emphasysAccel - 0.01f;
            }
            break;
        }
    }
}

INCLUDE_ASM(getFinalMatrix);

/* getFinalMatrixWithNaturalGeometry's helper */
static inline void applyNaturalGeometry(int id) /* derived name */
{
    SkelNode *e = &skelNode[id];
    Vec16 t;

    if (e->parent != -1) {
        _ScaleVectorXYZ(&t, e->pos, skelScale);
        _ApplyMatrix(MatrixDrive_GetMatrix()[3], MatrixDrive_GetLastMatrix(), &t);
    }
    MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), skelMotion + id * 32 + 16);
    GetMatrixFromQuaternionRotElem((char *)MatrixDrive_GetMatrix(), (char *)GetCurrentQuaternion());
}

static void getFinalMatrixWithNaturalGeometry(int id);

INCLUDE_ASM(getFinalMatrixWithNaturalGeometry);

/* this build calls libvu0's entry points here, not Matrix.c's wrappers */
static void _calcNaturalGeometry(int id)
{
    SkelNode *elemA = &skelNode[id];
    char *elemB = naturalMotion + id * 32;
    float (*x)[4];
    if (elemA->parent != -1) {
        sceVu0ScaleVectorXYZ(naturalTrans, elemA->pos, skelScale);
        GetMatrixFromQuaternionPos(naturalMatrix, elemB + 16, naturalTrans);
    } else {
        GetMatrixFromQuaternion(naturalMatrix, elemB + 16);
    }
    x = MatrixDrive_GetMatrix();
    sceVu0MulMatrix(x, MatrixDrive_GetLastMatrix(), naturalMatrix);
}
