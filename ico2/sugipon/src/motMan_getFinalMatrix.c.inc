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
                                short p, int unused, int setb, int setflag, float rate)
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
    unsigned int n;

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

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", avoidReverseInterpOnCurrentMatrixWithLimit);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", _getFinalMatrix);

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

extern int D_0063B914;
extern int D_0063B13C;
extern int D_0063B918;
extern float D_0063B90C;
extern float D_0063B910;
extern char D_0061FCB0[];
extern char D_0061FCD0[];
extern char D_0061FCE0[];

void EditRotEmphasys(void)
{
    int sel;

    if (((EditPad *)D_0028F8F0)->trg & 0x20) {
        D_0063B914 = D_0063B914 == 0;
    }
    if (D_0063B914 != 0) {
        if (D_0063B13C & 1) {
            debug_Printf(300, 170, 0xFFFFFF00u, (int)D_0061FCB0);
        }
        if (D_0063B13C & 1) {
            debug_Printf(300, 180, D_0063B918 != 0 ? 0xFFFFFF00u : 0x80808000u, (int)D_0061FCD0,
                         D_0063B90C);
        }
        if (D_0063B13C & 1) {
            debug_Printf(300, 180, D_0063B918 != 0 ? 0x80808000u : 0xFFFFFF00u, (int)D_0061FCE0,
                         D_0063B910);
        }
        sel = D_0063B918;
        if (((EditPad *)D_0028F8F0)->trg & 0xA000) {
            sel++;
            sel &= 1;
            D_0063B918 = sel;
        }
        switch (sel) {
        default:
        case 0:
            if (((EditPad *)D_0028F8F0)->hold & 0x1000) {
                D_0063B910 = D_0063B910 + 0.01f;
            }
            if (((EditPad *)D_0028F8F0)->hold & 0x4000) {
                D_0063B910 = D_0063B910 - 0.01f;
            }
            break;
        case 1:
            if (((EditPad *)D_0028F8F0)->hold & 0x1000) {
                D_0063B90C = D_0063B90C + 0.01f;
            }
            if (((EditPad *)D_0028F8F0)->hold & 0x4000) {
                D_0063B90C = D_0063B90C - 0.01f;
            }
            break;
        }
    }
}

static inline void getFinalMatrixCore(int id)
{
    char *e = D_0063B938 + id * 0x40;
    MatrixDrive_PushMatrixWithNoCopy();
    PushQuaternionWithNoCopy();
    _getFinalMatrix(id);
    CopyMatrix(*(char **)(*(char **)(D_0063B93C + 0x15C) + 0xC) + id * 0x40,
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
 * D_0063B93C chase off the ROM's registers. */
extern void GetMatrixFromQuaternionRotElem(char *a0, char *a1);

/* RECONSTRUCTED NAME: rows 1440-1447, inlined only into
 * getFinalMatrixWithNaturalGeometry (def line 1452), no MAIN.MAP symbol. */
static inline void applyNaturalGeometry(int id)
{
    char *e = D_0063B938 + id * 0x40;
    Vec16 t;

    if (*(int *)(e + 0x38) != -1) {
        _ScaleVectorXYZ(&t, e + 0x10, D_0063B900);
        _ApplyMatrix((char *)MatrixDrive_GetMatrix() + 0x30, MatrixDrive_GetLastMatrix(),
                     (char *)&t);
    }
    MultiQuaternion(GetCurrentQuaternion(), GetLastQuaternion(), D_0063C478 + id * 0x20 + 0x10);
    GetMatrixFromQuaternionRotElem((char *)MatrixDrive_GetMatrix(), (char *)GetCurrentQuaternion());
}

void getFinalMatrixWithNaturalGeometry(int id)
{
    char *e = D_0063B938 + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);

    MatrixDrive_PushMatrixWithNoCopy();
    PushQuaternionWithNoCopy();
    applyNaturalGeometry(id);
    CopyMatrix(*(char **)(*(char **)(D_0063B93C + 0x15C) + 0xC) + id * 0x40,
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
    char *elemA = D_0063B938 + a0 * 0x40;
    char *elemB = D_0063C4A4 + a0 * 0x20;
    int x;
    if (*(int *)(elemA + 0x38) != -1) {
        _ScaleVectorXYZ(D_007201E0, elemA + 0x10, D_0063B900);
        GetMatrixFromQuaternionPos(D_007201A0, elemB + 0x10, D_007201E0);
    } else {
        GetMatrixFromQuaternion(D_007201A0, elemB + 0x10);
    }
    x = MatrixDrive_GetMatrix();
    _MulMatrix((void *)x, MatrixDrive_GetLastMatrix(), D_007201A0);
}

static inline void pursueNaturalGeometry(int id)
{
    char *e = D_0063B938 + id * 0x40;
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
