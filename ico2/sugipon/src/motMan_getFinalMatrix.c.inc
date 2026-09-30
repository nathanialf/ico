/* motMan_getFinalMatrix.c.inc -- #included by motionManager.c into one motionManager.o (PAL listing SRCFILE.TXT). */
inline int SetDirectMotionProgramInterpInfo(char *a0, int a1, float f)
{
    int n = GetSkeltonFocusNode(a0, a1);
    char *e = *(char **)(*(char **)(a0 + 0x15C) + 0x80C) + (n << 6);
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
    char *e = *(char **)(*(char **)(a0 + 0x15C) + 0x80C) + (n << 6);
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

    AddVectorXYZ(w, (void *)(mtx + 0x30), D_0063C490);
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
static void limitHPAngleAndSetB(short *hp, short *pp, short *bp, char *lim, short h, short kind,
                                short p, short unused, int setb, int setflag, float rate)
{
    *hp = h;
    *pp = p;
    *bp = 0;

    if (lim != 0) {
        short rev = (1.0f - rate) * 32768.0f;

        float lo = ANG_OF_DEG(*(float *)(lim + 0x30));
        float hi = ANG_OF_DEG(*(float *)(lim + 0x48));
        float pdn = *(float *)(lim + 0x70);
        float pup = *(float *)(lim + 0x10);
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

            if ((float)d < ANG_OF_DEG(*(float *)(lim + 0x58))) {
                *hp = (short)lo;
                if (setflag) {
                    *(int *)(D_0063C494 + 0x14) = *(int *)(D_0063C494 + 0x14) | 0x100;
                }
            }
        }
        if (kind > 0 && *hp < 0) {
            int base = rev - 32768;
            short d = (*hp - base) / rate;

            if ((float)d < ANG_OF_DEG(*(float *)(lim + 0x58))) {
                *hp = (short)hi;
                if (setflag) {
                    *(int *)(D_0063C494 + 0x14) = *(int *)(D_0063C494 + 0x14) | 0x200;
                }
            }
        }
        if ((float)*hp < lo) {
            *hp = (short)lo;
            if (setflag) {
                *(int *)(D_0063C494 + 0x14) = *(int *)(D_0063C494 + 0x14) | 0x100;
            }
        }
        if (hi < (float)*hp) {
            *hp = (short)hi;
            if (setflag) {
                *(int *)(D_0063C494 + 0x14) = *(int *)(D_0063C494 + 0x14) | 0x200;
            }
        }

        if (*hp >= 0) {
            t = ANG_RATE((float)*hp, ANG_OF_DEG(*(float *)(lim + 0x48)));

            dnlim = ANG_OF_DEG(pdn) + (ANG_OF_DEG(*(float *)(lim + 0x7C)) - ANG_OF_DEG(pdn)) * t;

            uplim = ANG_OF_DEG(pup) + (ANG_OF_DEG(*(float *)(lim + 0x1C)) - ANG_OF_DEG(pup)) * t;

        } else {
            /* The guard is the +0x48 limit and not the +0x30 one the division uses:
               the listing computes both here, so the 2001 line was copied from the
               positive arm above and only its divisor changed. */
            t = ANG_OF_DEG(*(float *)(lim + 0x48)) == 0.0f
                    ? 0.0f
                    : ((float)*hp / ANG_OF_DEG(*(float *)(lim + 0x30)) < 0.0f
                           ? -((float)*hp / ANG_OF_DEG(*(float *)(lim + 0x30)))
                           : (float)*hp / ANG_OF_DEG(*(float *)(lim + 0x30)));

            dnlim = ANG_OF_DEG(pdn) + (ANG_OF_DEG(*(float *)(lim + 0x64)) - ANG_OF_DEG(pdn)) * t;

            uplim = ANG_OF_DEG(pup) + (ANG_OF_DEG(*(float *)(lim + 0x04)) - ANG_OF_DEG(pup)) * t;
        }

        if ((float)*pp < dnlim) {
            *pp = (short)dnlim;
        }
        if (uplim < (float)*pp) {
            *pp = (short)uplim;
        }

        if (*hp >= 0) {
            float rh = ANG_RATE((float)*hp, hi);
            float va =
                (ANG_OF_DEG(*(float *)(lim + 0x50)) - ANG_OF_DEG(*(float *)(lim + 0x44))) * rh +
                ANG_OF_DEG(*(float *)(lim + 0x44));

            if (*pp >= 0) {
                float vb =
                    (ANG_OF_DEG(*(float *)(lim + 0x20)) - ANG_OF_DEG(*(float *)(lim + 0x14))) * rh +
                    ANG_OF_DEG(*(float *)(lim + 0x14));

                rp = ANG_RATE((float)*pp, uplim);
                *bp = (vb - va) * rp + va;

            } else {
                float vb =
                    (ANG_OF_DEG(*(float *)(lim + 0x80)) - ANG_OF_DEG(*(float *)(lim + 0x74))) * rh +
                    ANG_OF_DEG(*(float *)(lim + 0x74));

                rp = ANG_RATE((float)*pp, dnlim);
                *bp = (vb - va) * rp + va;
            }
        } else {
            float rh = ANG_RATE((float)*hp, lo);
            float va =
                (ANG_OF_DEG(*(float *)(lim + 0x38)) - ANG_OF_DEG(*(float *)(lim + 0x44))) * rh +
                ANG_OF_DEG(*(float *)(lim + 0x44));

            if (*pp >= 0) {
                float vb =
                    (ANG_OF_DEG(*(float *)(lim + 0x08)) - ANG_OF_DEG(*(float *)(lim + 0x14))) * rh +
                    ANG_OF_DEG(*(float *)(lim + 0x14));

                rp = ANG_RATE((float)*pp, uplim);
                *bp = (vb - va) * rp + va;

            } else {
                float vb =
                    (ANG_OF_DEG(*(float *)(lim + 0x68)) - ANG_OF_DEG(*(float *)(lim + 0x74))) * rh +
                    ANG_OF_DEG(*(float *)(lim + 0x74));

                rp = ANG_RATE((float)*pp, dnlim);
                *bp = (vb - va) * rp + va;
            }
        }

        if (setb) {
            if (*pp >= 0)
                *bp = (float)*bp * (1.0f - rp) + ANG_OF_DEG(*(float *)(lim + 0x14)) * rp;
            else
                *bp = (float)*bp * (1.0f - rp) + ANG_OF_DEG(*(float *)(lim + 0x74)) * rp;
        }
    }
}

/* kept local: this TU's uses of these do not fit the prototypes in matrixDrive.h */
extern void MatrixDrive_GetTurnYAngleXZ(short *a0, short *a1, float x, float y, float z);
extern char YUnitVector[];

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined (rows
 * 104-133, above every def line in this file), so it carries no symbol in
 * MAIN.MAP.  It clamps a turn angle to the motion-program interp range and
 * returns 0 when the angle is already inside it. */
static inline short limitInterpAngle(char *info, short ang)
{
    float lo;
    float hi;

    if (info != 0) {
        lo = *(float *)(info + 0x30) * 32768.0f / 180.0f;
        hi = *(float *)(info + 0x48) * 32768.0f / 180.0f;
        if ((float)ang < lo) {
            return (short)lo;
        }
        if (hi < (float)ang) {
            return (short)hi;
        }
    }
    return 0;
}

int avoidReverseInterpOnCurrentMatrix(char *q, char *info, void *out)
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
static inline short classifyInterpAngle(char *info, short ang, float k)
{
    float lo;
    float hi;
    float a;
    float b;

    if (info != 0) {
        lo = *(float *)(info + 0x30) * 32768.0f / 180.0f;
        hi = *(float *)(info + 0x48) * 32768.0f / 180.0f;
        a = lo * k;
        b = hi * k;
        if ((float)ang < a || b < (float)ang)
            return 2;
        if ((float)ang < lo || hi < (float)ang)
            return 1;
    }
    return 0;
}

void avoidReverseInterpOnCurrentMatrixWithLimit(char *q, char *info, void *outA, void *outB,
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

extern void *GetLastQuaternion(void);
extern void GetMatrixFromQuaternionRotElem(char *a0, char *a1);
extern void DivQuaternion(void *dst, void *a, void *b);
extern void GetSlerpQuaternion(void *dst, void *a, void *b, float t);
extern void MultiCurrentQuaternion(void *q);
extern void GetInverseQuaternion(void *dst, void *q);
extern void RegularizeQuaternion(void *q);
extern void RotQuaternionX(void *q, short ang);
extern void RotQuaternionZ(void *q, short ang);
extern void MatrixDrive_RotMatrixX(int a0);
extern void MatrixDrive_GetTurnMinusZAngleXY(short *a0, short *a1, float x, float y, float z);
extern void MatrixDrive_GetTurnZAngleXY(short *a0, short *a1, float x, float y, float z);
extern void MatrixDrive_GetTurnXAngleZY(short *a0, short *a1, float x, float y, float z);
extern void SetQuaternionByAxisRotateWithNoRegularize(void *q, short ang, float x, float y,
                                                      float z);
extern float GetTableCos(short a);
extern float GetTableSin(short a);
extern short GetTableArcCos(float c);
extern float _InnerProduct(void *a, void *b);
extern void _OuterProduct(void *dst, void *a, void *b);
extern float VectorLength(void *v);
extern float GetWeaponWeight(int w);
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float s);
extern void sceVu0TransposeMatrix(int dst, int src);
extern void _AddVector(void *dst, void *a, void *b);
extern char XUnitVector[];
extern char ZeroPoint[];
extern int D_0028F4C0[];
extern int D_0063B198;
extern int D_0063B1E0;

/* The arm IK's angles: the shoulder's turns about Z and Y and the two
   joints' bends. */
static short ikRotZ = 0; /* derived name */

static short ikRotY = 0; /* derived name */

static short ikBend0 = 0; /* derived name */

static short ikBend1 = 0; /* derived name */

extern char D_0055FE58[];

/* RECONSTRUCTION, names ours: members of the geo block (D_0063C490).  The
 * two lifts at +0x208 are the arm-target height offsets cases 45 and 49 add;
 * the look-at turn sits at +0x300.  The ROM's stores to them do not order
 * against the stack shorts and do not invalidate skelScale, which holds
 * for structure members (alias.c fixed_scalar_and_varying_struct_p) and not
 * for plain pointer casts. */
typedef struct {
    char pad000[0x208];
    float lift[2];
    char pad210[0x300 - 0x210];
    short h;
    short p;
    short b;
} MotGeoTurn;

/* RECONSTRUCTION, names ours: the 0x194-byte motion-table record of
 * D_0055FE58 (motionViewer.c's MotRec); only the flag word this file reads
 * is named.  The ROM loads it with a 0x190 displacement from the record, the
 * shape of a structure member. */
typedef struct {
    char pad[0x190];
    unsigned int flags;
} MotTblRec;

/* The frame-rate factors every blend in _getFinalMatrix scales by: the
 * frame counter pair gives the frames per second of the current mode. */
#define MOT_FPS ((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]))
#define MOT_SPEED (D_0063B198 != 0 ? (float)D_0063B1E0 * 0.01f : *(float *)(D_0063C4A8 + 0x158))
#define MOT_RATE(off) (*(float *)(D_0063C490 + (off)) * (60.0f / MOT_FPS))
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
    char *elem = D_0063C478 + id * 0x20;
    char *geo = (char *)GOBJ_SUB(skelGObj) + 0xA0;
    char *ik = *(char **)(geo + 0x76C) + id * 0x40;
    char *lim = ((char **)*(char **)(geo + 0x770))[id];
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
        MultiQuaternion(GetCurrentQuaternion(), D_004EC9F0, GetCurrentQuaternion());
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        break;

    case 44:
        MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), elem + 0x10);
        DivQuaternion(GetCurrentQuaternion(), GetCurrentQuaternion(), D_004EC9E0);
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        break;

    case 34: {
        GET_NODE_ROT(q, dq);
        if (*(int *)(D_0063C490 + 0x318) != 0 && *(int *)(D_0063C490 + 0x2E0) != 0) {
            *(float *)ik = *(float *)ik + (1.0f - *(float *)ik) * MOT_BLEND(0x3BC);
        } else {
            *(float *)ik = *(float *)ik * (1.0f - MOT_BLEND(0x3BC));
        }
        {
            float q3[4];
            float q2[4];

            memset(q2, 0, 16);
            q2[3] = 1.0f;
            if (D_0063C498 == 2) {
                RotQuaternionZ(q2, 1820);
            }
            GetSlerpQuaternion(q3, q2, dq, *(float *)ik);
            MultiQuaternion(q, q, q3);
            APPLY_ROT(q);
            GetInverseQuaternion(q3, D_0063C490 + 0x2D0);
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
        RotQuaternionZ(GetCurrentQuaternion(), *(short *)(D_0063C490 + 0x304));
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
#ifdef DEBUG
        CopyQuaternion(work, GetCurrentQuaternion());
        scePrintf("node roll %f %f %f %f\n", work[0], work[1], work[2], work[3]);
#endif
        if (*(int *)(D_0063C490 + 0x318) != 0 && *(int *)(D_0063C490 + 0x2E0) != 0) {
            *(float *)ik = *(float *)ik + (1.0f - *(float *)ik) *
                                              (*(float *)(D_0063C490 + 0x3BC) * (60.0f / MOT_FPS));
        } else {
            *(float *)ik =
                *(float *)ik * (1.0f - *(float *)(D_0063C490 + 0x3BC) * (60.0f / MOT_FPS));
        }
        if (*(float *)ik < 0.01f) {
            CopyQuaternion(ik + 0x10, GetCurrentQuaternion());
            SetIdentityQuaternion(ik + 0x30);
            CopyQuaternion(ik + 0x20, ik + 0x30);
        } else {
            float out[4];
            short h;
            short p;
            short ha;
            short pa;
            short ba;

            if (D_0063C498 == 4) {
                MatrixDrive_RotMatrixX(-0x8000);
            }
            getLocalTargetDir(out, (float *)(D_0063C490 + 0x2F0));
            MatrixDrive_GetTurnYAngleXZ(&h, &p, out[0], out[1], out[2]);
            limitHPAngleAndSetB(&ha, &pa, &ba, lim, h, 0, -p, 0, 0, 1, 1.0f);
            pa *= -1;
            if (D_0063C498 == 4) {
                pa *= -1;
            }
            ((MotGeoTurn *)D_0063C490)->h = h - ha;
            ((MotGeoTurn *)D_0063C490)->p = p - pa;
            {
                float rq[4];
                float t[4];
                float t2[4];
                float t3[4];

                SetIdentityQuaternion(rq);
                RotQuaternionX(rq, -ha);
                RotQuaternionZ(rq, -pa);
                RotQuaternionY(rq, -ba);
                avoidReverseInterpOnCurrentMatrixWithLimit(ik + 0x10, lim, ik + 0x30, rq, 1.2f);
                MultiQuaternion(t, GetCurrentQuaternion(), rq);
                DivQuaternion(t2, t, ik + 0x10);
                GetSlerpQuaternion(t3, t2, IdentityQuaternion,
                                   *(float *)(D_0063C490 + 0x3C4) * 30.0f / MOT_FPS);
                GetSlerpQuaternion(ik + 0x20, t3, ik + 0x20,
                                   *(float *)(D_0063C490 + 0x3C8) * 30.0f / MOT_FPS);
                MultiQuaternion(ik + 0x10, ik + 0x10, ik + 0x20);
                RegularizeQuaternion(ik + 0x10);
                DivQuaternion(ik + 0x30, ik + 0x10, GetCurrentQuaternion());
            }
        }
        {
            float r[4];

            RotQuaternionX(GetCurrentQuaternion(), -*(short *)(D_0063C490 + 0x50) * 2.5f);
            MultiQuaternion(r, GetCurrentQuaternion(), dq);
            GetSlerpQuaternion(GetCurrentQuaternion(), ik + 0x10, r, *(float *)ik);
            MultiQuaternion(GetCurrentQuaternion(), D_004ECA00, GetCurrentQuaternion());
            GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        }
        break;
    }

    case 1: {
        GET_NODE_ROT(q, dq);
        MultiQuaternion(GetCurrentQuaternion(), GetCurrentQuaternion(), dq);
        GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
        if (*(int *)(D_0063C490 + 0x31C) != 0 &&
            ((*(int *)(D_0063C490 + 0x318) != 0 && *(int *)(D_0063C490 + 0x2E0) != 0) ||
             *(int *)(D_0063C490 + 0x230) != 0 || *(int *)(D_0063C490 + 0x290) != 0)) {
            *(float *)ik = *(float *)ik + (1.0f - *(float *)ik) * MOT_BLEND(0x3BC);
        } else {
            *(float *)ik = *(float *)ik * (1.0f - MOT_BLEND(0x3BC));
        }
        if (*(float *)ik < 0.01f) {
            CopyQuaternion(ik + 0x10, GetCurrentQuaternion());
            SetIdentityQuaternion(ik + 0x30);
            CopyQuaternion(ik + 0x20, ik + 0x30);
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

            avoidReverseInterpOnCurrentMatrix(ik + 0x10, lim, ik + 0x30);
#ifdef DEBUG
            CopyQuaternion(work0, ik + 0x10);
            CopyQuaternion(work1, ik + 0x30);
            scePrintf("interp %f %f %f %f -> %f %f %f %f\n", work0[0], work0[1], work0[2], work0[3],
                      work1[0], work1[1], work1[2], work1[3]);
#endif
            p = h = 0;
            n = 0;
            if (*(int *)(D_0063C490 + 0x31C) == 1 && *(int *)(D_0063C490 + 0x290) != 0) {
                n++;
                getLocalTargetDir(out, (float *)(D_0063C490 + 0x2A0));
                MatrixDrive_GetTurnMinusZAngleXY(&a0, &a1, out[0], out[1], out[2]);
                h = a0;
            }
            if (*(int *)(D_0063C490 + 0x31C) == 1 && *(int *)(D_0063C490 + 0x230) != 0) {
                float out2[4];

                n++;
                getLocalTargetDir(out2, (float *)(D_0063C490 + 0x240));
                MatrixDrive_GetTurnZAngleXY(&b0, &b1, out2[0], out2[1], out2[2]);
                h -= b0;
            }
            hv = h;
            if (*(int *)(D_0063C490 + 0x318) != 0 && *(int *)(D_0063C490 + 0x2E0) != 0) {
                float out3[4];

                getLocalTargetDir(out3, (float *)(D_0063C490 + 0x2F0));
                MatrixDrive_GetTurnYAngleXZ(&c0, &c1, out3[0], out3[1], out3[2]);
                if (*(int *)(D_0063C490 + 0x2E0) == 2) {
                    h = hv + c0;
                    p = c1;
                    hv = h;
                } else {
                    h = hv + *(short *)(D_0063C490 + 0x300);
                    p = *(short *)(D_0063C490 + 0x302);
                    hv += c0 / 2;
                }
                n++;
            }
            if (n != 0) {
                h /= n;
                hv /= n;
            }
            limitHPAngleAndSetB(&ha, &pa, &ba, lim, h, *(short *)(ik + 4), -p, -*(short *)(ik + 8),
                                0, 0, rate);
            limitHPAngleAndSetB(&hb, &pb, &bb, lim, hv, *(short *)(ik + 4), -p, -*(short *)(ik + 8),
                                0, 0, rate);
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
                DivQuaternion(t2, t, ik + 0x10);
                GetSlerpQuaternion(t3, t2, IdentityQuaternion,
                                   *(float *)(D_0063C490 + 0x3C4) * 30.0f / MOT_FPS);
                GetSlerpQuaternion(ik + 0x20, t3, ik + 0x20,
                                   *(float *)(D_0063C490 + 0x3C8) * 30.0f / MOT_FPS);
                MultiQuaternion(ik + 0x10, ik + 0x10, ik + 0x20);
                RegularizeQuaternion(ik + 0x10);
                DivQuaternion(ik + 0x30, ik + 0x10, GetCurrentQuaternion());
            }
            *(short *)(ik + 0xE) =
                *(short *)(ik + 0xE) +
                ((pb - *(short *)(ik + 8)) * (*(float *)(D_0063C490 + 0x3C4) * 30.0f / MOT_FPS) -
                 *(short *)(ik + 0xE)) *
                    (*(float *)(D_0063C490 + 0x3C8) * 30.0f / MOT_FPS);
            *(short *)(ik + 8) += *(short *)(ik + 0xE);
            *(short *)(D_0063C490 + 0x304) = *(short *)(ik + 8) * *(float *)ik;
        }
        {
            RotQuaternionX(GetCurrentQuaternion(), *(short *)(D_0063C490 + 0x50) * 2.5f);
            GetSlerpQuaternion(GetCurrentQuaternion(), ik + 0x10, GetCurrentQuaternion(),
                               *(float *)ik);
            MultiQuaternion(GetCurrentQuaternion(), D_0063C490 + 0x2D0, GetCurrentQuaternion());
            GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
            _ApplyMatrix(D_00720180, MatrixDrive_GetMatrix(), XUnitVector);
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
            getLocalTargetDir(out, (float *)(D_0063C490 + 0x2A0));
            MatrixDrive_GetTurnXAngleZY(&a0, &a1, out[0], out[1], out[2]);
            limitHPAngleAndSetB(&ha, &pa, &ba, lim, a0, 0, a1, 0, 1, 0, 1.0f);
            if (*(int *)(D_0063C490 + 0x294) != 0) {
                _NormalizeVector(dv, out);
            } else {
                getDirOfAngle(dv, ha, pa);
            }
            getRotOfDir(r, dv);
            MultiQuaternion(qa, qa, r);
            switch (*(int *)(D_0063C490 + 0x290)) {
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
                                                D_0063C478 + n * 0x20 + 0x10);
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

                        SetQuaternionByAxisRotateV(D_00720190, ang, ax);
                        len[1] = l;
                        MatrixDrive_PopMatrix();
                    }
                }
                if (*(int *)(D_0063C490 + 0x2C4) == 0) {
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
                getRootRelativePos(t, MatrixDrive_GetMatrix(), (float *)(D_0063C490 + 0x2A0));
                _NormalizeVector(t, t);
                _OuterProduct(p, t, D_00720180);
                if (*(int *)(D_0063C490 + 0x360) == 2 && d + 0.0f > len[0] + len[1]) {
                    float rq[4];

                    SetQuaternionByAxisRotateV(rq, (d + 0.0f - (len[0] + len[1])) * 208.60756f, p);
                    GetSlerpQuaternion(D_0063C490 + 0x2D0, D_0063C490 + 0x2D0, rq, 0.6f);
                } else {
                    GetSlerpQuaternion(D_0063C490 + 0x2D0, D_0063C490 + 0x2D0, IdentityQuaternion,
                                       0.9f);
                }
                break;
            }
            case 2:
                MultiQuaternion(s, qa, D_0063C490 + 0x2B0);
                MultiQuaternion(s, s, dq);
                GetSlerpQuaternion(D_0063C490 + 0x2D0, D_0063C490 + 0x2D0, IdentityQuaternion,
                                   0.9f);
                break;
            default:
                CopyQuaternion(s, dq);
                GetSlerpQuaternion(D_0063C490 + 0x2D0, D_0063C490 + 0x2D0, IdentityQuaternion,
                                   0.9f);
                break;
            }
        }
        GetSlerpQuaternion(ik + 0x10, s, ik + 0x10,
                           *(float *)(D_0063C490 + 0x2C0) * (60.0f / MOT_FPS));
        if (*(int *)(D_0063C490 + 0x290) != 0) {
            *(float *)ik = *(float *)ik + (1.0f - *(float *)ik) *
                                              (*(float *)(D_0063C490 + 0x3C0) * (60.0f / MOT_FPS));
        } else {
            *(float *)ik =
                *(float *)ik * (1.0f - *(float *)(D_0063C490 + 0x3C0) * (60.0f / MOT_FPS));
        }
        {
            float r2[4];

            GetSlerpQuaternion(r2, ik + 0x10, dq, *(float *)ik);
            MultiQuaternion(q, q, r2);
            APPLY_ROT(q);
            D_0063C474 = *(float *)ik;
            flag = D_0063C474 > 0.99f;
            if (flag && *(int *)(D_0063C490 + 0x2C8) == 0) {
                *(int *)(D_0063C490 + 0x2C4) = 1;
            } else {
                *(int *)(D_0063C490 + 0x2C4) = 0;
            }
            *(int *)(D_0063C490 + 0x2C8) = flag;
        }
        break;
    }

    case 20: {
        GET_NODE_ROT(q, dq);
        {
            float t[4];
            float r[4];

            CopyQuaternion(t, dq);
            if (*(int *)(D_0063C490 + 0x290) == 1) {
                SetQuaternionByAxisRotateWithNoRegularize(t, -(ikBend0 + ikBend1), 0.0f, 0.0f,
                                                          -1.0f);
                MultiQuaternion(t, t, D_00720190);
            }
            GetSlerpQuaternion(ik + 0x10, t, ik + 0x10,
                               *(float *)(D_0063C490 + 0x2C0) * (60.0f / MOT_FPS));
            GetSlerpQuaternion(r, ik + 0x10, dq, D_0063C474);
            MultiQuaternion(q, q, r);
            APPLY_ROT(q);
        }
        break;
    }

    case 22: {
        float t[4];
        float w;

        GET_NODE_ROT(q, dq);
        if (*(int *)(D_0063C490 + 0x330) != 0)
            CopyQuaternion(t, IdentityQuaternion);
        else
            CopyQuaternion(t, dq);
        {
            float r[4];

            GetSlerpQuaternion(r, t, dq, D_0063C474);
            MultiQuaternion(q, q, r);
            APPLY_ROT(q);
            if (*(int *)(D_0063C494 + 0x1C0) != 0 &&
                !(((MotTblRec *)(D_0055FE58 + *(int *)(D_0063C494 + 0x30) * 404))->flags >> 4 &
                  1)) {
                switch (*(int *)(D_0063C494 + 0x68)) {
                case 0:
                case 6:
                case 14:
                case 19:
                    break;
                default:
                    w = GetWeaponWeight(*(int *)(D_0063C494 + 0x1C0)) * 0.00016666666f;
                    w = 0.8f < w ? 0.8f : w;
                    GetSlerpQuaternion(ik + 0x10, ik + 0x10, GetCurrentQuaternion(), w);
                    CopyQuaternion(GetCurrentQuaternion(), ik + 0x10);
                    GetMatrixFromQuaternionRotElem(MatrixDrive_GetMatrix(), GetCurrentQuaternion());
                    return;
                }
            }
            CopyQuaternion(ik + 0x10, GetCurrentQuaternion());
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
            getLocalTargetDir(out, (float *)(D_0063C490 + 0x240));
            MatrixDrive_GetTurnXAngleZY(&a0, &a1, out[0], out[1], out[2]);
            limitHPAngleAndSetB(&ha, &pa, &ba, lim, a0, 0, a1, 0, 1, 0, 1.0f);
            if (*(int *)(D_0063C490 + 0x234) != 0) {
                _NormalizeVector(dv, out);
            } else {
                getDirOfAngle(dv, ha, pa);
            }
            getRotOfDir(r, dv);
            MultiQuaternion(qa, qa, r);
            switch (*(int *)(D_0063C490 + 0x230)) {
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
                MultiQuaternion(t, qa, D_0063C490 + 0x250);
                MultiQuaternion(t, t, dq);
                break;
            default:
                CopyQuaternion(t, dq);
                break;
            }
        }
        GetSlerpQuaternion(ik + 0x10, t, ik + 0x10,
                           *(float *)(D_0063C490 + 0x3C0) * (60.0f / MOT_FPS));
        if (*(int *)(D_0063C490 + 0x230) != 0) {
            *(float *)ik = *(float *)ik + (1.0f - *(float *)ik) *
                                              (*(float *)(D_0063C490 + 0x3C0) * (60.0f / MOT_FPS));
        } else {
            *(float *)ik =
                *(float *)ik * (1.0f - *(float *)(D_0063C490 + 0x3C0) * (60.0f / MOT_FPS));
        }
        {
            float r2[4];

            GetSlerpQuaternion(r2, ik + 0x10, dq, *(float *)ik);
            MultiQuaternion(q, q, r2);
            APPLY_ROT(q);
            D_0063C474 = *(float *)ik;
        }
        break;
    }

    case 4: {
        GET_NODE_ROT(q, dq);
        {
            float t[4];
            float r[4];

            CopyQuaternion(t, dq);
            if (*(int *)(D_0063C490 + 0x230) == 1) {
                SetQuaternionByAxisRotateWithNoRegularize(t, -(ikBend0 + ikBend1), 0.0f, 0.0f,
                                                          -1.0f);
            }
            GetSlerpQuaternion(ik + 0x10, t, ik + 0x10,
                               *(float *)(D_0063C490 + 0x3C0) * (60.0f / MOT_FPS));
            GetSlerpQuaternion(r, ik + 0x10, dq, D_0063C474);
            MultiQuaternion(q, q, r);
            APPLY_ROT(q);
        }
        break;
    }

    case 6: {
        GET_NODE_ROT(q, dq);
        if (*(int *)(D_0063C490 + 0x334) != 0) {
            CopyQuaternion(ik + 0x10, IdentityQuaternion);
        } else {
            CopyQuaternion(ik + 0x10, dq);
        }
        {
            float r[4];

            GetSlerpQuaternion(r, ik + 0x10, dq, D_0063C474);
            MultiQuaternion(q, q, r);
            APPLY_ROT(q);
        }
        break;
    }

    case 5:
        GET_NODE_ROT(q, dq);
        if (*(int *)(D_0063C490 + 0x230) != 0) {
            if (*(int *)(D_0063C490 + 0x230) != 1) {
                MultiQuaternion(q, q, dq);
            }
        } else {
            MultiQuaternion(q, q, dq);
        }
        APPLY_ROT(q);
        break;

    case 45:
    case 49:
        if (*(int *)(D_0063C490 + 0x204) != 0) {
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
                MultiMatrixByQuaternion(D_0063C478 + ci * 0x20 + 0x10);
                len[i] = skelScale * VectorLength(cn + 0x10);
            }
            CopyVector(p, (void *)(MatrixDrive_GetMatrix() + 0x30));
            switch (*(int *)(node + 4)) {
            case 45:
                p[1] += *(float *)(D_0063C490 + 0x208);
                break;
            case 49:
                p[1] += *(float *)(D_0063C490 + 0x20C);
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
        if (*(int *)(D_0063C490 + 0x204) != 0) {
            GET_NODE_ROT(q, dq);
            RotQuaternionZ(q, ikBend0 + ikBend1);
            APPLY_ROT(q);
            break;
        }
    case 47:
    case 51:
        if (*(int *)(D_0063C490 + 0x204) != 0) {
            GET_NODE_ROT(q, dq);
            RotQuaternionZ(q, -ikBend1);
            RotQuaternionY(q, -ikRotY);
            RotQuaternionZ(q, -ikRotZ);
            MultiQuaternion(q, q, D_0063C478 + *(int *)(node + 0x38) * 0x20 + 0x10);
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

/* kept local: this TU's uses of these do not fit the prototypes in debug.h. */
extern void debug_Printf(int a, int b, unsigned int c, int x, ...);
extern double fptodp(float v);
extern unsigned char D_0028F8F0[];

/* RECONSTRUCTION: the pad snapshot at D_0028F8F0 as this TU reads it; only the
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

extern int D_0063B13C;

void EditRotEmphasys(void)
{
    int sel;

    if (((EditPad *)D_0028F8F0)->trg & 0x20) {
        emphasysEdit = emphasysEdit == 0;
    }
    if (emphasysEdit != 0) {
        if (D_0063B13C & 1) {
            debug_Printf(300, 170, 0xFFFFFF00u, (int)"Emphasys Accel   Velocity");
        }
        if (D_0063B13C & 1) {
            debug_Printf(300, 180, emphasysSelect != 0 ? 0xFFFFFF00u : 0x80808000u,
                         (int)"         %1.5f ", emphasysAccel);
        }
        if (D_0063B13C & 1) {
            debug_Printf(300, 180, emphasysSelect != 0 ? 0x80808000u : 0xFFFFFF00u,
                         (int)"                 %1.5f", emphasysVelocity);
        }
        sel = emphasysSelect;
        if (((EditPad *)D_0028F8F0)->trg & 0xA000) {
            sel++;
            sel &= 1;
            emphasysSelect = sel;
        }
        switch (sel) {
        default:
        case 0:
            if (((EditPad *)D_0028F8F0)->hold & 0x1000) {
                emphasysVelocity = emphasysVelocity + 0.01f;
            }
            if (((EditPad *)D_0028F8F0)->hold & 0x4000) {
                emphasysVelocity = emphasysVelocity - 0.01f;
            }
            break;
        case 1:
            if (((EditPad *)D_0028F8F0)->hold & 0x1000) {
                emphasysAccel = emphasysAccel + 0.01f;
            }
            if (((EditPad *)D_0028F8F0)->hold & 0x4000) {
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
    CopyMatrix(*(char **)(*(char **)(skelGObj + 0x15C) + 0xC) + id * 0x40,
               (void *)MatrixDrive_GetMatrix());
    CopyQuaternion(D_0063C480 + id * 0x10, GetCurrentQuaternion());
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
    SetQuaternionByAxisRotateV(D_004EC9E0, *(short *)(D_0063C490 + 0x50), v);
    SetQuaternionByAxisRotateV(
        D_004EC9F0, *(short *)(D_0063C490 + 0x50) * (*(float *)(D_0063C490 + 0x54) - 1.0f - 0.5f),
        v);
    SetQuaternionByAxisRotateV(
        D_004ECA00, *(short *)(D_0063C490 + 0x50) * (*(float *)(D_0063C490 + 0x54) - 1.0f + 0.5f),
        v);
    MatrixDrive_PopMatrix();
    getFinalMatrixCore(id);
}

/* kept local: this TU's uses of GetMatrixFromQuaternionRotElem do not fit the
 * prototype in quaternion.h.  It must be prototyped above its only call site:
 * left implicit it returns int, which reserves $2 at the call and moves the
 * skelGObj chase off the ROM's registers. */
extern void GetMatrixFromQuaternionRotElem(char *a0, char *a1);

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
    MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), D_0063C478 + id * 0x20 + 0x10);
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
    CopyMatrix(*(char **)(*(char **)(skelGObj + 0x15C) + 0xC) + id * 0x40,
               (void *)MatrixDrive_GetMatrix());
    CopyQuaternion(D_0063C480 + id * 0x10, GetCurrentQuaternion());
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
    char *elemB = D_0063C4A4 + a0 * 0x20;
    int x;
    if (*(int *)(elemA + 0x38) != -1) {
        _ScaleVectorXYZ(D_007201E0, elemA + 0x10, skelScale);
        GetMatrixFromQuaternionPos(D_007201A0, elemB + 0x10, D_007201E0);
    } else {
        GetMatrixFromQuaternion(D_007201A0, elemB + 0x10);
    }
    x = MatrixDrive_GetMatrix();
    _MulMatrix((void *)x, MatrixDrive_GetLastMatrix(), D_007201A0);
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
    o = D_0063C4A0 + id * 0x10;
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
