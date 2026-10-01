/* motMan_getFinalMatrix.c.inc -- #included by motionManager.c into one motionManager.o (PAL listing SRCFILE.TXT). */
inline int SetDirectMotionProgramInterpInfo(char *a0, int a1, float f)
{
    int n = GetSkeltonFocusNode(a0, a1);
    char *e = GOBJ_SUB(a0)->p_80C + (n << 6);
    if (n < 0)
        return 0;
    *(float *)e = f;
    CopyQuaternion(e + 0x20, IdentityQuaternion);
    CopyQuaternion(e + 0x30, IdentityQuaternion);
    return 1;
}

inline int ResetMotionProgramInterpInfo(char *a0, int a1)
{
    int n = GetSkeltonFocusNode(a0, a1);
    char *e = GOBJ_SUB(a0)->p_80C + (n << 6);
    if (n < 0)
        return 0;
    *(int *)e = 0;
    CopyQuaternion(e + 0x20, IdentityQuaternion);
    CopyQuaternion(e + 0x30, IdentityQuaternion);
    return 1;
}

/* RECONSTRUCTED NAMES: listing rows 62-71 and 76-82, only ever inlined into
 * _getFinalMatrix.  The first gives a point relative to the root placed at
 * the matrix's translation, the second the same vector in the current
 * matrix's local axes. */
static inline void getRootRelativePos(float *out, int mtx, float *pos)
{
    float w[4];

    AddVectorXYZ(w, (void *)(mtx + 0x30), skelRoot->pos);
    SubVectorXYZ(out, pos, w);
    out[3] = 0.0f;
}

static inline void getLocalTargetDir(float *out, float *pos)
{
    float tmp[4];

    getRootRelativePos(tmp, MatrixDrive_GetMatrix(), pos);
    MatrixDrive_PushMatrixWithNoCopy();
    MatrixDrive_SetTransposeMatrix((void *)MatrixDrive_GetMatrix(),
                                   (int)MatrixDrive_GetLastMatrix());
    sceVu0ApplyMatrix((int *)out, MatrixDrive_GetMatrix(), (char *)tmp);
    MatrixDrive_PopMatrix();
}

/* RECONSTRUCTED spellings.  The PAL listing gives every instruction of
   limitHPAngleAndSetB the line of its call site, so the repeated degree
   conversion and the repeated clamped ratio are macros in the 2001 source and
   not inline functions (gcc 2.9 copies an inlined body's own line notes,
   integrate.c:2092-2103).  32768 units are 180 degrees. */
#define ANG_OF_DEG(x) ((x) * 32768.0f / 180.0f)
#define ANG_RATE(v, lim)                                                                           \
    ((lim) == 0.0f ? 0.0f : ((v) / (lim) < 0.0f ? -((v) / (lim)) : (v) / (lim)))

/* lim is the motion program's interp record, the same one limitInterpAngle
   reads at +0x30 and +0x48.  hp and pp are the heading and pitch of the turn
   being limited, bp the bank the record's tables interpolate from them. */
static void limitHPAngleAndSetB(short *hp, short *pp, short *bp, MotLimAng *lim, short h,
                                short kind, short p, short unused, int setb, int setflag,
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

        if (kind < 0 && *hp > 0) {
            /* base and d share one listing line (both are line 159, resp. 170):
               the subtraction has to be its own object or fold folds 32768 onto
               the heading instead, and the ROM recomputes it in each arm. */
            int base = rev - 32768;
            short d = (-*hp - base) / rate;

            if ((float)d < ANG_OF_DEG(lim[7].p)) {
                *hp = (short)lo;
                if (setflag) {
                    skelMotCtrl->flags = skelMotCtrl->flags | 0x100;
                }
            }
        }
        if (kind > 0 && *hp < 0) {
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
            /* The guard is the +0x48 limit and not the +0x30 one the division uses:
               the listing computes both here, so the 2001 line was copied from the
               positive arm above and only its divisor changed. */
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

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined (rows
 * 104-133, above every def line in this file), so it carries no symbol in
 * MAIN.MAP.  It clamps a turn angle to the motion-program interp range and
 * returns 0 when the angle is already inside it. */
static inline short limitInterpAngle(MotLimAng *info, short ang)
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

int avoidReverseInterpOnCurrentMatrix(char *q, MotLimAng *info, void *out)
{
    float mtx[16];
    Vec16 up;
    Vec16 dir;
    short ang;
    short ang2;

    GetMatrixFromQuaternion(mtx, q);
    _ApplyMatrix(&up, (int)mtx, YUnitVector);
    MatrixDrive_SetTransposeMatrix(mtx, MatrixDrive_GetMatrix());
    _ApplyMatrix(&dir, (int)mtx, (char *)&up);
    MatrixDrive_GetTurnYAngleXZ(&ang, &ang2, dir.f[0], dir.f[1], dir.f[2]);
    if (limitInterpAngle(info, ang) != 0) {
        MultiQuaternion(q, GetCurrentQuaternion(), out);
        return 1;
    }
    return 0;
}

/* RECONSTRUCTED NAME: rows 296-306, inlined only into
 * avoidReverseInterpOnCurrentMatrixWithLimit (def line 314), no MAIN.MAP
 * symbol.  0 = inside the range, 1 = outside the plain range, 2 = outside the
 * range scaled by the limit factor. */
static inline short classifyInterpAngle(MotLimAng *info, short ang, float k)
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

void avoidReverseInterpOnCurrentMatrixWithLimit(char *q, MotLimAng *info, void *outA, void *outB,
                                                float k)
{
    float mtx[16];
    Vec16 up;
    Vec16 dir;
    short ang;
    short ang2;

    GetMatrixFromQuaternion(mtx, q);
    _ApplyMatrix(&up, (int)mtx, YUnitVector);
    MatrixDrive_SetTransposeMatrix(mtx, MatrixDrive_GetMatrix());
    _ApplyMatrix(&dir, (int)mtx, (char *)&up);
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

/* kept local: float (int) here, float (char *) in weapon.h */
extern float GetWeaponWeight(int w);
/* kept local: agrees with libvu0.h, which this TU does not include (sceVu0ApplyMatrix, sceVu0MulMatrix differ) */
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float s);
/* kept local: void (int, int) here, void (void *, void *) in libvu0.h */
extern void sceVu0TransposeMatrix(int dst, int src);

/* The arm IK's angles: the shoulder's turns about Z and Y and the two
   joints' bends. */
static short ikRotZ = 0; /* derived name */

static short ikRotY = 0; /* derived name */

static short ikBend0 = 0; /* derived name */

static short ikBend1 = 0; /* derived name */

extern char motionKind[];

/* RECONSTRUCTION, names ours: the 0x194-byte motion-table record of
 * motionKind (motionViewer.c's MotRec); only the flag word this file reads
 * is named.  The ROM loads it with a 0x190 displacement from the record, the
 * shape of a structure member. */
typedef struct {
    char pad[0x190];
    unsigned int flags;
} MotTblRec;

/* The frame-rate factors every blend in _getFinalMatrix scales by: the
 * frame counter pair gives the frames per second of the current mode. */
#define MOT_FPS ((float)((60 - systemStatus[0] * 10) / systemStatus[1]))
#define MOT_SPEED                                                                                  \
    (debug_now_motion_viewer != 0 ? (float)debug_face_rot_w_ratio * 0.01f                          \
                                  : *(float *)(skelMotDef + 0x158))
#define MOT_RATE(f) (skelRoot->f * (60.0f / MOT_FPS))
#define MOT_BLEND(off) (MOT_RATE(off) + (1.0f - MOT_RATE(off)) * MOT_SPEED)

/* RECONSTRUCTED NAMES: listing rows 370-376 and 380-385, only ever inlined
 * into _getFinalMatrix.  A unit direction from a heading and a pitch, and
 * the rotation that turns the x axis onto a direction. */
static inline void getDirOfAngle(float *v, short h, short p)
{
    float c = GetTableCos(p);

    v[0] = GetTableCos(h) * c;
    v[1] = GetTableSin(h) * c;
    v[2] = -GetTableSin(p);
    v[3] = 0.0f;
}

static inline void getRotOfDir(float *q, float *v)
{
    float axis[4];
    short ang = GetTableArcCos(_InnerProduct(v, XUnitVector));

    _OuterProduct(axis, v, XUnitVector);
    SetQuaternionByAxisRotateV(q, ang, axis);
}

/* The motion's own rotation for the node, the matrix rebuilt from it, and
 * the stream's offset from the skeleton's rest rotation. */
#define GET_NODE_ROT(q, dq)                                                                        \
    MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), node + 0x20);                     \
    GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());               \
    CopyQuaternion(q, IdentityQuaternion);                                                         \
    DivQuaternion(dq, elem + 0x10, node + 0x20)
#define APPLY_ROT(q)                                                                               \
    MultiCurrentQuaternion(q);                                                                     \
    GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion())

void _getFinalMatrix(int id)
{
    char *node = skelNode + id * 0x40;
    char *elem = skelMotion + id * 0x20;
    char *geo = (char *)GOBJ_SUB(skelGObj) + 0xA0;
    MotIk *ik = *(MotIk **)(geo + 0x76C) + id;
    MotLimAng *lim = ((MotLimAng **)*(char **)(geo + 0x770))[id];
    float v[4];
    float dq[4];
    float q[4];
    int dbg = 0;

    if (*(int *)(node + 0x38) != -1) {
        sceVu0ScaleVectorXYZ(v, node + 0x10, skelScale);
        sceVu0ApplyMatrix((int *)(MatrixDrive_GetMatrix() + 0x30), (int)MatrixDrive_GetLastMatrix(),
                          (char *)v);
    } else {
        ikRotZ = ikRotY = ikBend0 = ikBend1 = 0;
    }

    switch (*(int *)(node + 4)) {
    case 0:
        MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), elem + 0x10);
        MultiQuaternion(GetCurrentQuaternion(), twistQuatLow, GetCurrentQuaternion());
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        break;

    case 44:
        MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), elem + 0x10);
        DivQuaternion(GetCurrentQuaternion(), GetCurrentQuaternion(), twistQuat);
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        break;

    case 34: {
        GET_NODE_ROT(q, dq);
        if (skelRoot->f_318 != 0 && skelRoot->f_2E0 != 0) {
            ik->rate = ik->rate + (1.0f - ik->rate) * MOT_BLEND(f_3BC);
        } else {
            ik->rate = ik->rate * (1.0f - MOT_BLEND(f_3BC));
        }
        {
            float q3[4];
            float q2[4];

            memset(q2, 0, 16);
            q2[3] = 1.0f;
            if (skelGeoType == 2) {
                RotQuaternionZ(q2, 1820);
            }
            GetSlerpQuaternion(q3, q2, dq, ik->rate);
            MultiQuaternion(q, q, q3);
            APPLY_ROT(q);
            GetInverseQuaternion(q3, skelRoot->q2D0);
            MultiQuaternion(GetCurrentQuaternion(), q3, GetCurrentQuaternion());
            GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        }
        break;
    }

    case 35: {
        /* A 16-byte block array no retail instruction references.  The bytes
           pin its frame slot (without it strict 2511 of 2835 words change,
           the frame and every later slot moving); its reader is the DEBUG
           build's report of the rolled quaternion (report ours). */
        float work[4];

        GET_NODE_ROT(q, dq);
        RotQuaternionZ(GetCurrentQuaternion(), skelRoot->b);
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
#ifdef DEBUG
        CopyQuaternion(work, GetCurrentQuaternion());
        scePrintf("node roll %f %f %f %f\n", work[0], work[1], work[2], work[3]);
#endif
        if (skelRoot->f_318 != 0 && skelRoot->f_2E0 != 0) {
            ik->rate = ik->rate + (1.0f - ik->rate) * (skelRoot->f_3BC * (60.0f / MOT_FPS));
        } else {
            ik->rate = ik->rate * (1.0f - skelRoot->f_3BC * (60.0f / MOT_FPS));
        }
        if (ik->rate < 0.01f) {
            CopyQuaternion(ik->q, GetCurrentQuaternion());
            SetIdentityQuaternion(ik->q30);
            CopyQuaternion(ik->q20, ik->q30);
        } else {
            float out[4];
            short h;
            short p;
            short ha;
            short pa;
            short ba;

            if (skelGeoType == 4) {
                MatrixDrive_RotMatrixX(-0x8000);
            }
            getLocalTargetDir(out, (float *)skelRoot->v2F0);
            MatrixDrive_GetTurnYAngleXZ(&h, &p, out[0], out[1], out[2]);
            limitHPAngleAndSetB(&ha, &pa, &ba, lim, h, 0, -p, 0, 0, 1, 1.0f);
            pa *= -1;
            if (skelGeoType == 4) {
                pa *= -1;
            }
            skelRoot->h = h - ha;
            skelRoot->p = p - pa;
            {
                float rq[4];
                float t[4];
                float t2[4];
                float t3[4];

                SetIdentityQuaternion(rq);
                RotQuaternionX(rq, -ha);
                RotQuaternionZ(rq, -pa);
                RotQuaternionY(rq, -ba);
                avoidReverseInterpOnCurrentMatrixWithLimit(ik->q, lim, ik->q30, rq, 1.2f);
                MultiQuaternion(t, GetCurrentQuaternion(), rq);
                DivQuaternion(t2, t, ik->q);
                GetSlerpQuaternion(t3, t2, IdentityQuaternion, skelRoot->f_3C4 * 30.0f / MOT_FPS);
                GetSlerpQuaternion(ik->q20, t3, ik->q20, skelRoot->f_3C8 * 30.0f / MOT_FPS);
                MultiQuaternion(ik->q, ik->q, ik->q20);
                RegularizeQuaternion(ik->q);
                DivQuaternion(ik->q30, ik->q, GetCurrentQuaternion());
            }
        }
        {
            float r[4];

            RotQuaternionX(GetCurrentQuaternion(), -skelRoot->twist * 2.5f);
            MultiQuaternion(r, GetCurrentQuaternion(), dq);
            GetSlerpQuaternion(GetCurrentQuaternion(), ik->q, r, ik->rate);
            MultiQuaternion(GetCurrentQuaternion(), twistQuatHigh, GetCurrentQuaternion());
            GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        }
        break;
    }

    case 1: {
        GET_NODE_ROT(q, dq);
        MultiQuaternion(GetCurrentQuaternion(), GetCurrentQuaternion(), dq);
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        if (skelRoot->f_31C != 0 && ((skelRoot->f_318 != 0 && skelRoot->f_2E0 != 0) ||
                                     skelRoot->f_230 != 0 || skelRoot->f_290 != 0)) {
            ik->rate = ik->rate + (1.0f - ik->rate) * MOT_BLEND(f_3BC);
        } else {
            ik->rate = ik->rate * (1.0f - MOT_BLEND(f_3BC));
        }
        if (ik->rate < 0.01f) {
            CopyQuaternion(ik->q, GetCurrentQuaternion());
            SetIdentityQuaternion(ik->q30);
            CopyQuaternion(ik->q20, ik->q30);
        } else {
            /* work0 and work1 are referenced by no retail instruction.  The
               bytes pin their two 16-byte frame slots around out (without them
               393 words change); their reader is the DEBUG build's report of
               the interpolation's two quaternions (report ours). */
            float work0[4];
            float out[4];
            float work1[4];
            int h;
            int p;
            int n;
            int hv;
            short a0, a1;
            short b0, b1;
            short c0, c1;
            short ha, pa, ba;
            short hb, pb, bb;
            float rate = 1.0f;

            avoidReverseInterpOnCurrentMatrix(ik->q, lim, ik->q30);
#ifdef DEBUG
            CopyQuaternion(work0, ik->q);
            CopyQuaternion(work1, ik->q30);
            scePrintf("interp %f %f %f %f -> %f %f %f %f\n", work0[0], work0[1], work0[2], work0[3],
                      work1[0], work1[1], work1[2], work1[3]);
#endif
            p = h = 0;
            n = 0;
            if (skelRoot->f_31C == 1 && skelRoot->f_290 != 0) {
                n++;
                getLocalTargetDir(out, (float *)skelRoot->v2A0);
                MatrixDrive_GetTurnMinusZAngleXY(&a0, &a1, out[0], out[1], out[2]);
                h = a0;
            }
            if (skelRoot->f_31C == 1 && skelRoot->f_230 != 0) {
                float out2[4];

                n++;
                getLocalTargetDir(out2, (float *)skelRoot->v240);
                MatrixDrive_GetTurnZAngleXY(&b0, &b1, out2[0], out2[1], out2[2]);
                h -= b0;
            }
            hv = h;
            if (skelRoot->f_318 != 0 && skelRoot->f_2E0 != 0) {
                float out3[4];

                getLocalTargetDir(out3, (float *)skelRoot->v2F0);
                MatrixDrive_GetTurnYAngleXZ(&c0, &c1, out3[0], out3[1], out3[2]);
                if (skelRoot->f_2E0 == 2) {
                    h = hv + c0;
                    p = c1;
                    hv = h;
                } else {
                    h = hv + skelRoot->h;
                    p = skelRoot->p;
                    hv += c0 / 2;
                }
                n++;
            }
            if (n != 0) {
                h /= n;
                hv /= n;
            }
            limitHPAngleAndSetB(&ha, &pa, &ba, lim, h, ik->h, -p, -ik->p, 0, 0, rate);
            limitHPAngleAndSetB(&hb, &pb, &bb, lim, hv, ik->h, -p, -ik->p, 0, 0, rate);
            pb *= -1;
            {
                float r[4];
                float t[4];
                float t2[4];
                float t3[4];

                SetIdentityQuaternion(r);
                RotQuaternionX(r, -ha);
                RotQuaternionZ(r, -pb);
                RotQuaternionY(r, -ba);
                MultiQuaternion(t, GetCurrentQuaternion(), r);
                DivQuaternion(t2, t, ik->q);
                GetSlerpQuaternion(t3, t2, IdentityQuaternion, skelRoot->f_3C4 * 30.0f / MOT_FPS);
                GetSlerpQuaternion(ik->q20, t3, ik->q20, skelRoot->f_3C8 * 30.0f / MOT_FPS);
                MultiQuaternion(ik->q, ik->q, ik->q20);
                RegularizeQuaternion(ik->q);
                DivQuaternion(ik->q30, ik->q, GetCurrentQuaternion());
            }
            ik->dp = ik->dp + ((pb - ik->p) * (skelRoot->f_3C4 * 30.0f / MOT_FPS) - ik->dp) *
                                  (skelRoot->f_3C8 * 30.0f / MOT_FPS);
            ik->p += ik->dp;
            skelRoot->b = ik->p * ik->rate;
        }
        {
            RotQuaternionX(GetCurrentQuaternion(), skelRoot->twist * 2.5f);
            GetSlerpQuaternion(GetCurrentQuaternion(), ik->q, GetCurrentQuaternion(), ik->rate);
            MultiQuaternion(GetCurrentQuaternion(), skelRoot->q2D0, GetCurrentQuaternion());
            GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
            _ApplyMatrix(ikXAxis, MatrixDrive_GetMatrix(), XUnitVector);
        }
        break;
    }

    case 18:
        GET_NODE_ROT(q, dq);
        MultiQuaternion(q, q, dq);
        APPLY_ROT(q);
        break;

    case 19: {
        float s[4];
        int flag;

        GET_NODE_ROT(q, dq);
        {
            float out[4], r[4], work0[4], qa[4], work1[4], dv[4];
            short a0, a1;
            short ha, pa, ba;

            memset(qa, 0, 16);
            qa[3] = 1.0f;
            /* RECONSTRUCTION: listing lines 727-734 carry no word, yet the
             * frame holds two 16-byte vectors whose address escapes (work0,
             * work1: they stay live to the end of the block, function.c's
             * temp-slot rules) and a 4-byte permanent slot of address-taken
             * scalars at sp+0x100, allocated ahead of a0/a1 and never read
             * or written by the ROM.  What the bytes pin: those two vectors
             * and those four bytes, made in that window.  What they cannot
             * pin: the window's text and condition; a turn computed from the
             * work vectors, as the next line computes it from out, under the
             * function's local debug switch, is ours (case 3 has the same
             * window with one vector). */
            if (dbg) {
                short w0, w1;

                CopyVector(work0, work1);
                MatrixDrive_GetTurnXAngleZY(&w0, &w1, work0[0], work0[1], work0[2]);
            }
            getLocalTargetDir(out, (float *)skelRoot->v2A0);
            MatrixDrive_GetTurnXAngleZY(&a0, &a1, out[0], out[1], out[2]);
            limitHPAngleAndSetB(&ha, &pa, &ba, lim, a0, 0, a1, 0, 1, 0, 1.0f);
            if (skelRoot->f_294 != 0) {
                _NormalizeVector(dv, out);
            } else {
                getDirOfAngle(dv, ha, pa);
            }
            getRotOfDir(r, dv);
            MultiQuaternion(qa, qa, r);
            switch (skelRoot->f_290) {
            case 1: {
                float len[4], t[4], p[4];
                float d;
                float l;
                float dd;
                int i;
                int ci;
                char *cn;

                d = VectorLength(out);
                for (i = 0, cn = node; i < 2; i++) {
                    ci = *(int *)(cn + 0x30);
                    if (ci == -1) {
                        break;
                    }
                    cn = skelNode + ci * 0x40;
                    len[i] = skelScale * VectorLength(cn + 0x10);
                }
                len[1] += skelScale *
                          VectorLength(skelNode + GetSkeltonFocusNode((char *)skelGObj, 32) * 0x40 +
                                       0x10);
                {
                    float ax[4], w[4];
                    short ang;
                    int n;

                    {
                        MatrixDrive_PushMatrixWithNoCopy();
                        n = GetSkeltonFocusNode((char *)skelGObj, 22);
                        GetMatrixFromQuaternion((void *)MatrixDrive_GetMatrix(),
                                                skelMotion + n * 0x20 + 0x10);
                        MatrixDrive_TransMatrix(5.0f, -3.0f, 0.0f);
                        CopyVector(p, (void *)(MatrixDrive_GetMatrix() + 0x30));
                        _AddVector(t, skelNode + *(int *)(node + 0x30) * 0x40 + 0x10, p);
                        l = skelScale * VectorLength(t);
                        w[0] = l;
                        w[1] = 0.0f;
                        w[2] = 0.0f;
                        w[3] = 1.0f;
                        _SubVectorXYZ(w, w, p);
                        _NormalizeVector(w, w);
                        _OuterProduct(ax, w, XUnitVector);
                        ang = GetTableArcCos(_InnerProduct(XUnitVector, w));

                        SetQuaternionByAxisRotateV(ikBendQuat, ang, ax);
                        len[1] = l;
                        MatrixDrive_PopMatrix();
                    }
                }
                if (skelRoot->f_2C4 == 0) {
                    if (len[0] + len[1] < d) {
                        d = len[0] + len[1];
                    }
                }
                dd = d * d;
                ikBend0 =
                    GetTableArcCos((dd + len[0] * len[0] - len[1] * len[1]) / (2.0f * len[0] * d));
                ikBend1 =
                    GetTableArcCos((dd + len[1] * len[1] - len[0] * len[0]) / (2.0f * len[1] * d));
                RotQuaternionX(qa, ba);
                RotQuaternionZ(qa, ikBend0);
                CopyQuaternion(s, qa);
                getRootRelativePos(t, MatrixDrive_GetMatrix(), (float *)skelRoot->v2A0);
                _NormalizeVector(t, t);
                _OuterProduct(p, t, ikXAxis);
                if (skelRoot->f_360 == 2 && d + 0.0f > len[0] + len[1]) {
                    float rq[4];

                    SetQuaternionByAxisRotateV(rq, (d + 0.0f - (len[0] + len[1])) * 208.60756f, p);
                    GetSlerpQuaternion(skelRoot->q2D0, skelRoot->q2D0, rq, 0.6f);
                } else {
                    GetSlerpQuaternion(skelRoot->q2D0, skelRoot->q2D0, IdentityQuaternion, 0.9f);
                }
                break;
            }
            case 2:
                MultiQuaternion(s, qa, skelRoot->q2B0);
                MultiQuaternion(s, s, dq);
                GetSlerpQuaternion(skelRoot->q2D0, skelRoot->q2D0, IdentityQuaternion, 0.9f);
                break;
            default:
                CopyQuaternion(s, dq);
                GetSlerpQuaternion(skelRoot->q2D0, skelRoot->q2D0, IdentityQuaternion, 0.9f);
                break;
            }
        }
        GetSlerpQuaternion(ik->q, s, ik->q, skelRoot->f_2C0 * (60.0f / MOT_FPS));
        if (skelRoot->f_290 != 0) {
            ik->rate = ik->rate + (1.0f - ik->rate) * (skelRoot->f_3C0 * (60.0f / MOT_FPS));
        } else {
            ik->rate = ik->rate * (1.0f - skelRoot->f_3C0 * (60.0f / MOT_FPS));
        }
        {
            float r2[4];

            GetSlerpQuaternion(r2, ik->q, dq, ik->rate);
            MultiQuaternion(q, q, r2);
            APPLY_ROT(q);
            ikSlerpRate = ik->rate;
            flag = ikSlerpRate > 0.99f;
            if (flag && skelRoot->f_2C8 == 0) {
                skelRoot->f_2C4 = 1;
            } else {
                skelRoot->f_2C4 = 0;
            }
            skelRoot->f_2C8 = flag;
        }
        break;
    }

    case 20: {
        GET_NODE_ROT(q, dq);
        {
            float t[4];
            float r[4];

            CopyQuaternion(t, dq);
            if (skelRoot->f_290 == 1) {
                SetQuaternionByAxisRotateWithNoRegularize(t, -(ikBend0 + ikBend1), 0.0f, 0.0f,
                                                          -1.0f);
                MultiQuaternion(t, t, ikBendQuat);
            }
            GetSlerpQuaternion(ik->q, t, ik->q, skelRoot->f_2C0 * (60.0f / MOT_FPS));
            GetSlerpQuaternion(r, ik->q, dq, ikSlerpRate);
            MultiQuaternion(q, q, r);
            APPLY_ROT(q);
        }
        break;
    }

    case 22: {
        float t[4];
        float w;

        GET_NODE_ROT(q, dq);
        if (skelRoot->f_330 != 0)
            CopyQuaternion(t, IdentityQuaternion);
        else
            CopyQuaternion(t, dq);
        {
            float r[4];

            GetSlerpQuaternion(r, t, dq, ikSlerpRate);
            MultiQuaternion(q, q, r);
            APPLY_ROT(q);
            if (skelMotCtrl->f_1C0 != 0 &&
                !(((MotTblRec *)(motionKind + skelMotCtrl->motion * 404))->flags >> 4 & 1)) {
                switch (skelMotCtrl->rootUpdateMode) {
                case 0:
                case 6:
                case 14:
                case 19:
                    break;
                default:
                    w = GetWeaponWeight(skelMotCtrl->f_1C0) * 0.00016666666f;
                    w = 0.8f < w ? 0.8f : w;
                    GetSlerpQuaternion(ik->q, ik->q, GetCurrentQuaternion(), w);
                    CopyQuaternion(GetCurrentQuaternion(), ik->q);
                    GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
                    return;
                }
            }
            CopyQuaternion(ik->q, GetCurrentQuaternion());
        }
        break;
    }

    case 21:
        CopyQuaternion(GetCurrentQuaternion(), GetLastQuaternion());
        MultiQuaternion(GetCurrentQuaternion(), GetCurrentQuaternion(), elem + 0x10);
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        break;

    case 2:
        GET_NODE_ROT(q, dq);
        MultiQuaternion(q, q, dq);
        APPLY_ROT(q);
        break;

    case 3: {
        float t[4];

        GET_NODE_ROT(q, dq);
        {
            float qa[4], out[4], r[4], work[4], dv[4];
            short a0, a1;
            short ha, pa, ba;

            memset(qa, 0, 16);
            qa[3] = 1.0f;
            /* RECONSTRUCTION: listing lines 1020-1027, case 19's window
             * (727-734) again, carry no word; the frame holds one escaping
             * 16-byte vector (work) there.  What the bytes pin: that vector.
             * What they cannot pin: the window's text and condition, ours
             * here. */
            if (dbg) {
                CopyVector(work, out);
            }
            getLocalTargetDir(out, (float *)skelRoot->v240);
            MatrixDrive_GetTurnXAngleZY(&a0, &a1, out[0], out[1], out[2]);
            limitHPAngleAndSetB(&ha, &pa, &ba, lim, a0, 0, a1, 0, 1, 0, 1.0f);
            if (skelRoot->f_234 != 0) {
                _NormalizeVector(dv, out);
            } else {
                getDirOfAngle(dv, ha, pa);
            }
            getRotOfDir(r, dv);
            MultiQuaternion(qa, qa, r);
            switch (skelRoot->f_230) {
            case 1: {
                float len[4];
                float d;
                int i;
                int ci;
                char *cn;

                d = VectorLength(out);
                for (i = 0, cn = node; i < 2; i++) {
                    ci = *(int *)(cn + 0x30);
                    if (ci == -1) {
                        break;
                    }
                    cn = skelNode + ci * 0x40;
                    len[i] = skelScale * VectorLength(cn + 0x10);
                }
                len[1] += skelScale *
                          VectorLength(skelNode + GetSkeltonFocusNode((char *)skelGObj, 16) * 0x40 +
                                       0x10);
                ikBend0 = GetTableArcCos((d * d + len[0] * len[0] - len[1] * len[1]) /
                                         (2.0f * len[0] * d));
                ikBend1 = GetTableArcCos((d * d + len[1] * len[1] - len[0] * len[0]) /
                                         (2.0f * len[1] * d));
                RotQuaternionX(qa, ba);
                RotQuaternionZ(qa, ikBend0);
                CopyQuaternion(t, qa);
                break;
            }
            case 2:
                MultiQuaternion(t, qa, skelRoot->q250);
                MultiQuaternion(t, t, dq);
                break;
            default:
                CopyQuaternion(t, dq);
                break;
            }
        }
        GetSlerpQuaternion(ik->q, t, ik->q, skelRoot->f_3C0 * (60.0f / MOT_FPS));
        if (skelRoot->f_230 != 0) {
            ik->rate = ik->rate + (1.0f - ik->rate) * (skelRoot->f_3C0 * (60.0f / MOT_FPS));
        } else {
            ik->rate = ik->rate * (1.0f - skelRoot->f_3C0 * (60.0f / MOT_FPS));
        }
        {
            float r2[4];

            GetSlerpQuaternion(r2, ik->q, dq, ik->rate);
            MultiQuaternion(q, q, r2);
            APPLY_ROT(q);
            ikSlerpRate = ik->rate;
        }
        break;
    }

    case 4: {
        GET_NODE_ROT(q, dq);
        {
            float t[4];
            float r[4];

            CopyQuaternion(t, dq);
            if (skelRoot->f_230 == 1) {
                SetQuaternionByAxisRotateWithNoRegularize(t, -(ikBend0 + ikBend1), 0.0f, 0.0f,
                                                          -1.0f);
            }
            GetSlerpQuaternion(ik->q, t, ik->q, skelRoot->f_3C0 * (60.0f / MOT_FPS));
            GetSlerpQuaternion(r, ik->q, dq, ikSlerpRate);
            MultiQuaternion(q, q, r);
            APPLY_ROT(q);
        }
        break;
    }

    case 6: {
        GET_NODE_ROT(q, dq);
        if (skelRoot->f_334 != 0) {
            CopyQuaternion(ik->q, IdentityQuaternion);
        } else {
            CopyQuaternion(ik->q, dq);
        }
        {
            float r[4];

            GetSlerpQuaternion(r, ik->q, dq, ikSlerpRate);
            MultiQuaternion(q, q, r);
            APPLY_ROT(q);
        }
        break;
    }

    case 5:
        GET_NODE_ROT(q, dq);
        if (skelRoot->f_230 != 0) {
            if (skelRoot->f_230 != 1) {
                MultiQuaternion(q, q, dq);
            }
        } else {
            MultiQuaternion(q, q, dq);
        }
        APPLY_ROT(q);
        break;

    case 45:
    case 49:
        if (skelRoot->f_204 != 0) {
            int i;
            int flag;
            char *cn;
            int ci;
            float len[2];
            float p[4];
            float sv[4];
            float d;
            float dd;
            float d2;
            float aa;
            float bb;
            int m;

            GET_NODE_ROT(q, dq);
            flag = 0;
            MatrixDrive_PushMatrix();
            CopyVector((void *)(MatrixDrive_GetMatrix() + 0x30), ZeroPoint);
            MultiMatrixByQuaternion(dq);
            MatrixDrive_PushMatrix();
            for (i = 0, cn = node; i < 2; i++) {
                ci = *(int *)(cn + 0x30);
                if (ci == -1) {
                    flag = 1;
                    break;
                }
                cn = skelNode + ci * 0x40;
                sceVu0ScaleVectorXYZ(sv, cn + 0x10, skelScale);
                MatrixDrive_TransMatrixV(sv);
                MultiMatrixByQuaternion(skelMotion + ci * 0x20 + 0x10);
                len[i] = skelScale * VectorLength(cn + 0x10);
            }
            CopyVector(p, (void *)(MatrixDrive_GetMatrix() + 0x30));
            switch (*(int *)(node + 4)) {
            case 45:
                p[1] += skelRoot->lift[0];
                break;
            case 49:
                p[1] += skelRoot->lift[1];
                break;
            }
            d = VectorLength(p);
            MatrixDrive_PopMatrix();
            dd = d * d;
            m = MatrixDrive_GetMatrix();
            sceVu0TransposeMatrix(m, m);
            sceVu0ApplyMatrix((int *)p, m, (char *)p);
            sceVu0Normalize(p, p);
            ikRotZ = asinf(p[1]) * 10430.378f;
            ikRotY = -asinf(p[2]) * 10430.378f;
            aa = len[0] * len[0];
            bb = len[1] * len[1];
            d2 = d + d;
            ikBend0 = acosf((dd + aa - bb) / (d2 * len[0])) * 10430.378f;
            ikBend1 = acosf((dd + bb - aa) / (d2 * len[1])) * 10430.378f;
            MatrixDrive_PopMatrix();
            if (flag == 0) {
                MultiQuaternion(q, q, dq);
                RotQuaternionZ(q, ikRotZ);
                RotQuaternionY(q, ikRotY);
                RotQuaternionZ(q, -ikBend0);
            } else {
                MultiQuaternion(q, q, dq);
            }
            APPLY_ROT(q);
            break;
        }
    case 46:
    case 50:
        if (skelRoot->f_204 != 0) {
            GET_NODE_ROT(q, dq);
            RotQuaternionZ(q, ikBend0 + ikBend1);
            APPLY_ROT(q);
            break;
        }
    case 47:
    case 51:
        if (skelRoot->f_204 != 0) {
            GET_NODE_ROT(q, dq);
            RotQuaternionZ(q, -ikBend1);
            RotQuaternionY(q, -ikRotY);
            RotQuaternionZ(q, -ikRotZ);
            MultiQuaternion(q, q, skelMotion + *(int *)(node + 0x38) * 0x20 + 0x10);
            MultiQuaternion(q, q, dq);
            APPLY_ROT(q);
            break;
        }
        MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), elem + 0x10);
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        break;

    default:
        MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), elem + 0x10);
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        break;
    }
}

extern double fptodp(float v);

/* RECONSTRUCTION: the pad snapshot at pad as this TU reads it; only the
 * two words the rotation-emphasis editor uses carry names. */
typedef struct {
    int _00[0x17];
    int trg; /* 0x5C */
    int _60;
    int hold; /* 0x64 */
} EditPad;

/* EditRotEmphasys's tuning: the two coefficients it shows and edits, the
   switch that turns the editor on and the coefficient selected. */
static float emphasysAccel = 0.1f; /* derived name */

static float emphasysVelocity = 0.97f; /* derived name */

static int emphasysEdit = 0; /* derived name */

static int emphasysSelect = 0; /* derived name */

void EditRotEmphasys(void)
{
    int sel;

    if (((EditPad *)pad)->trg & 0x20) {
        emphasysEdit = emphasysEdit == 0;
    }
    if (emphasysEdit != 0) {
        if (debug_font_flag & 1) {
            debug_Printf(300, 170, 0xFFFFFF00u, (int)"Emphasys Accel   Velocity");
        }
        if (debug_font_flag & 1) {
            debug_Printf(300, 180, emphasysSelect != 0 ? 0xFFFFFF00u : 0x80808000u,
                         (int)"         %1.5f ", emphasysAccel);
        }
        if (debug_font_flag & 1) {
            debug_Printf(300, 180, emphasysSelect != 0 ? 0x80808000u : 0xFFFFFF00u,
                         (int)"                 %1.5f", emphasysVelocity);
        }
        sel = emphasysSelect;
        if (((EditPad *)pad)->trg & 0xA000) {
            sel++;
            sel &= 1;
            emphasysSelect = sel;
        }
        switch (sel) {
        default:
        case 0:
            if (((EditPad *)pad)->hold & 0x1000) {
                emphasysVelocity = emphasysVelocity + 0.01f;
            }
            if (((EditPad *)pad)->hold & 0x4000) {
                emphasysVelocity = emphasysVelocity - 0.01f;
            }
            break;
        case 1:
            if (((EditPad *)pad)->hold & 0x1000) {
                emphasysAccel = emphasysAccel + 0.01f;
            }
            if (((EditPad *)pad)->hold & 0x4000) {
                emphasysAccel = emphasysAccel - 0.01f;
            }
            break;
        }
    }
}

static inline void getFinalMatrixCore(int id)
{
    char *e = skelNode + id * 0x40;
    MatrixDrive_PushMatrixWithNoCopy();
    PushQuaternionWithNoCopy();
    _getFinalMatrix(id);
    CopyMatrix((char *)GOBJ_SUB(skelGObj)->f_C + id * 0x40, (void *)MatrixDrive_GetMatrix());
    CopyQuaternion(skelQuat + id * 0x10, GetCurrentQuaternion());
    if (*(int *)(e + 0x30) != -1) {
        getFinalMatrixCore(*(int *)(e + 0x30));
    }
    MatrixDrive_PopMatrix();
    PopQuaternion();
    if (*(int *)(e + 0x34) != -1) {
        getFinalMatrixCore(*(int *)(e + 0x34));
    }
}

void getFinalMatrix(int id)
{
    char v[0x10];

    MatrixDrive_PushMatrix();
    _ApplyMatrix(v, MatrixDrive_GetMatrix(), ZUnitVector);
    SetQuaternionByAxisRotateV(twistQuat, skelRoot->twist, v);
    SetQuaternionByAxisRotateV(twistQuatLow, skelRoot->twist * (skelRoot->twistRate - 1.0f - 0.5f),
                               v);
    SetQuaternionByAxisRotateV(twistQuatHigh, skelRoot->twist * (skelRoot->twistRate - 1.0f + 0.5f),
                               v);
    MatrixDrive_PopMatrix();
    getFinalMatrixCore(id);
}

/* RECONSTRUCTED NAME: rows 1440-1447, inlined only into
 * getFinalMatrixWithNaturalGeometry (def line 1452), no MAIN.MAP symbol. */
static inline void applyNaturalGeometry(int id)
{
    char *e = skelNode + id * 0x40;
    Vec16 t;

    if (*(int *)(e + 0x38) != -1) {
        _ScaleVectorXYZ(&t, e + 0x10, skelScale);
        _ApplyMatrix((char *)MatrixDrive_GetMatrix() + 0x30, MatrixDrive_GetLastMatrix(),
                     (char *)&t);
    }
    MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), skelMotion + id * 0x20 + 0x10);
    GetMatrixFromQuaternionRotElem((char *)MatrixDrive_GetMatrix(), (char *)GetCurrentQuaternion());
}

void getFinalMatrixWithNaturalGeometry(int id)
{
    char *e = skelNode + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);

    MatrixDrive_PushMatrixWithNoCopy();
    PushQuaternionWithNoCopy();
    applyNaturalGeometry(id);
    CopyMatrix((char *)GOBJ_SUB(skelGObj)->f_C + id * 0x40, (void *)MatrixDrive_GetMatrix());
    CopyQuaternion(skelQuat + id * 0x10, GetCurrentQuaternion());
    if (child != -1) {
        getFinalMatrixWithNaturalGeometry(child);
    }
    MatrixDrive_PopMatrix();
    PopQuaternion();
    if (next != -1) {
        getFinalMatrixWithNaturalGeometry(next);
    }
}

void _calcNaturalGeometry(int a0)
{
    char *elemA = skelNode + a0 * 0x40;
    char *elemB = naturalMotion + a0 * 0x20;
    int x;
    if (*(int *)(elemA + 0x38) != -1) {
        _ScaleVectorXYZ(naturalTrans, elemA + 0x10, skelScale);
        GetMatrixFromQuaternionPos(naturalMatrix, elemB + 0x10, naturalTrans);
    } else {
        GetMatrixFromQuaternion(naturalMatrix, elemB + 0x10);
    }
    x = MatrixDrive_GetMatrix();
    _MulMatrix((void *)x, MatrixDrive_GetLastMatrix(), naturalMatrix);
}

static inline void pursueNaturalGeometry(int id)
{
    char *e = skelNode + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);
    char *o;
    int m;
    MatrixDrive_PushMatrixWithNoCopy();
    _calcNaturalGeometry(id);
    o = naturalNodePos + id * 0x10;
    m = MatrixDrive_GetMatrix();
    CopyVector((void *)o, (char *)m + 0x30);
    if (child != -1) {
        pursueNaturalGeometry(child);
    }
    MatrixDrive_PopMatrix();
    if (next != -1) {
        pursueNaturalGeometry(next);
    }
}
