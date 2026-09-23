#include "common.h"
#include "debug.h"
#include "debug_exception.h"
#include "gobj.h"
#include "s_init.h"
#include "frameDependSequence.h"
#include "matrixDrive.h"
#include "motionManager.h"
#include "quaternion.h"
#include "motionOrientManager.h"
#include <stdio.h>
#include "streamMotionManager.h"
#include "tableSin.h"
#include "typedef.h"
#include "GifPacket.h"
#include <libvu0.h>

extern MotionOrientEntry D_002ADD60[];
extern MotionOrientEntry D_002BC4A8;
/* kept local: this declaration is identical to the motionManager2.h prototype, but the
 * TU cannot include that header while its GetStreamMotion, DispSkelton and
 * FeedbackWallWorkInfoToBrainSystem uses still need declarations of their own. */
extern void CopyMotion(void *dst, void *src, int n);

struct MotOriHead8 {
    long long v;
} __attribute__((packed));

struct MotOriFloat {
    float frame;
};

#define MOWORK(self) (*(char **)((char *)(self) + 0x15C))

typedef struct MotOriTrigEnt {
    /* 0x000 */ char pad000[0xC0];
    /* 0x0C0 */ char name[0x30];
    /* 0x0F0 */ char pad0F0[0x14];
    /* 0x104 */ int f104;
    /* 0x108 */ int f108;
    /* 0x10C */ int f10C;
    /* 0x110 */ int f110;
    /* 0x114 */ int f114;
    /* 0x118 */ int f118;
    /* 0x11C */ char pad11C[0x14];
    /* 0x130 */ int f130;
    /* 0x134 */ char pad134[0x8];
    /* 0x13C */ int f13C;
    /* 0x140 */ int f140;
    /* 0x144 */ int f144;
    /* 0x148 */ int f148;
    /* 0x14C */ int f14C;
    /* 0x150 */ int f150;
    /* 0x154 */ int f154;
    /* 0x158 */ char pad158[0x4];
    /* 0x15C */ float f15C;
    /* 0x160 */ char pad160[0x4];
    /* 0x164 */ float f164;
    /* 0x168 */ char pad168[0x4];
    /* 0x16C */ int f16C;
    /* 0x170 */ int f170;
    /* 0x174 */ float f174;
    /* 0x178 */ int f178;
    /* 0x17C */ int f17C;
    /* 0x180 */ char pad180[0x8];
    /* 0x188 */ unsigned int f188;
    /* 0x18C */ unsigned int f18C;
    /* 0x190 */ unsigned int f190;
} MotOriTrigEnt;

/* The 0x470 motion work area, reconstructed from the ROM's own displacements.
   The TU reaches it as bytes elsewhere; UpdateFrameCounter needs the record
   form because a field reference and an `extern int` are in different alias
   sets, which is what lets the ROM's motionFrameUpdate load schedule above the
   two preceding work-area stores. */
typedef struct MotOriWork {
    /* 0x000 */ char pad000[0x30];
    /* 0x030 */ int f30;
    /* 0x034 */ char pad034[0x4];
    /* 0x038 */ int f38;
    /* 0x03C */ float f3C;
    /* 0x040 */ float f40;
    /* 0x044 */ float f44;
    /* 0x048 */ float f48;
    /* 0x04C */ float f4C;
    /* 0x050 */ float f50;
    /* 0x054 */ int f54;
    /* 0x058 */ int f58;
    /* 0x05C */ int f5C;
    /* 0x060 */ char pad060[0x8];
    /* 0x068 */ int f68;
    /* 0x06C */ char pad06C[0x14];
    /* 0x080 */ int f80;
    /* 0x084 */ char pad084[0x8];
    /* 0x08C */ int f8C;
    /* 0x090 */ char pad090[0x10];
    /* 0x0A0 */ int fA0;
    /* 0x0A4 */ int fA4;
    /* 0x0A8 */ char pad0A8[0xE8];
    /* 0x190 */ int f190;
    /* 0x194 */ int f194;
} MotOriWork;

/* .rodata at 0x55FE58 in the ROM: the trigger definition table is read-only. */
extern const MotOriTrigEnt D_0055FE58[];
extern int D_0028F4D4[];
/* the seventeen fixed captions the orientation debug window prints, one per
   trigger kind, plus the window's own format at 0x6201C8 */
extern char D_0063B948[];
extern char D_0063B950[];
extern char D_0063B958[];
extern char D_0063B960[];
extern char D_0063B968[];
extern char D_0063B970[];
extern char D_0063B978[];
extern char D_0063B980[];
extern char D_00620120[];
extern char D_00620130[];
extern char D_00620140[];
extern char D_00620158[];
extern char D_00620170[];
extern char D_00620188[];
extern char D_00620198[];
extern char D_006201A8[];
extern char D_006201B8[];
extern char D_006201C8[];
extern int D_0063B160;

/* The motion-name row the debug line prints: 32 bytes the ROM copies with
 * ldl/ldr, so a 4-aligned record and not an 8-aligned one. */
typedef struct MotOriName {
    char s[0x20];
} MotOriName;

extern MotOriName D_005D1278[];

void orientDebug(void *self, int idx, int y)
{
    char buf[256];
    MotOriName name;

    switch (D_0055FE58[*(int *)(MOWORK(self) + 0x4A0)].f118) {
    default:
    case 12:
    case 13:
    case 14:
    case 18:
    case 19:
        sprintf(buf, D_0063B948);
        break;
    case 1:
        sprintf(buf, D_0063B950);
        break;
    case 20:
        sprintf(buf, D_0063B958);
        break;
    case 2:
        sprintf(buf, D_00620120);
        break;
    case 17:
        sprintf(buf, D_00620130);
        break;
    case 7:
        sprintf(buf, D_00620140);
        break;
    case 16:
        sprintf(buf, D_00620158);
        break;
    case 8:
        sprintf(buf, D_00620170);
        break;
    case 9:
        sprintf(buf, D_00620188);
        break;
    case 10:
        sprintf(buf, D_0063B960);
        break;
    case 15:
        sprintf(buf, D_00620198);
        break;
    case 11:
        sprintf(buf, D_0063B968);
        break;
    case 5:
        sprintf(buf, D_0063B970);
        break;
    case 4:
        sprintf(buf, D_0063B978);
        break;
    case 3:
        sprintf(buf, D_0063B980);
        break;
    case 0:
        sprintf(buf, D_006201A8);
        break;
    case 6:
        sprintf(buf, D_006201B8);
        break;
    }
    if (D_0063B160 != 0) {
        name = D_005D1278[idx];
        debug_PrintFontWindow(y, D_006201C8, &name, D_0055FE58[*(int *)(MOWORK(self) + 0x4A0)].name,
                              buf);
    }
}

extern char D_00620238[];
extern char D_00620290[];
extern char D_006202D0[];
extern char D_0063B988[];

typedef struct MotOriSub {
    /* 0x0 */ int f0;
    /* 0x4 */ int f4;
    /* 0x8 */ int f8;
    /* 0xC */ int fC;
} MotOriSub;

extern MotOriSub D_00623470[];

static inline void checkMotionKind(int i, int j)
{
    if (D_0055FE58[i].f178 != 0x140) {
        char buf[0x100];

        debug_StdPrintfDummy(D_00620238, D_0055FE58[j].name);
        sprintf(buf, D_00620290, D_0055FE58[j].name);
        debug_assertMessage(D_006202D0, 152, buf);
        __assert(D_006202D0, 152, D_0063B988);
    }
}

extern int *D_004EB758[];

int GetNbMotionFrames(int id)
{
    int m;
    int n;

    if (D_0055FE58[id].f178 == 0x140) {
        return *D_004EB758[id];
    }
    m = D_00623470[D_0055FE58[id].f178].f0;
    n = D_00623470[D_0055FE58[id].f178].fC;
    checkMotionKind(m, id);
    if (n != -1) {
        return n;
    }
    return *D_004EB758[m];
}

float GetMotionPlaySpeedRatio(int id)
{
    int m;

    if (D_0055FE58[id].f178 == 0x140) {
        return D_0055FE58[id].f174;
    }
    m = D_00623470[D_0055FE58[id].f178].f0;
    checkMotionKind(m, id);
    return D_0055FE58[m].f174;
}

void execFrameTrigger(void *self)
{
    char *w = MOWORK(self) + 0x470;
    float t;

    t = (float)D_0055FE58[*(int *)(w + 0x30)].f144;
    if (0.0f <= t) {
        if (*(int *)(w + 0x19C) == 0) {
            if (t < *(float *)(w + 0x3C)) {
                *(int *)(w + 0x198) = 1;
                *(int *)(w + 0x19C) = 1;
            } else {
                *(int *)(w + 0x198) = 0;
            }
        } else {
            *(int *)(w + 0x198) = 0;
        }
    }
    t = (float)D_0055FE58[*(int *)(w + 0x30)].f14C;
    if (0.0f <= t) {
        if (*(int *)(w + 0x1A4) != 0) {
            *(int *)(w + 0x1A0) = 0;
        } else if (t < *(float *)(w + 0x3C)) {
            *(int *)(w + 0x1A0) = 1;
            *(int *)(w + 0x1A4) = 1;
        } else {
            *(int *)(w + 0x1A0) = 0;
        }
    }
}

/* No symbol and no census row: the listing gives it lines 230 to 237, between
 * GetMotionPlaySpeedRatio (219 to 229) and execFrameTrigger (241), and inlines
 * it here and in UpdateFrameCounter. The store order is the source's own. */
static __inline__ void clearFrameTriggerState(void *self)
{
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x608) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x610) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x60C) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x614) = 0;
}

/* Three range tests with no symbol and no census row, listing lines 156 to 193;
 * shiftMotionData and UpdateFrameCounter both inline them. */
static __inline__ int checkFrameInRange(int mot, float t)
{
    if ((float)D_0055FE58[mot].f144 <= t && t <= (float)D_0055FE58[mot].f148) {
        return 1;
    }
    return 0;
}

static __inline__ int checkFrameInRange2(int mot, float t, float t2)
{
    if ((float)D_0055FE58[mot].f14C <= t2 && t <= (float)D_0055FE58[mot].f154) {
        return 1;
    }
    return 0;
}

static __inline__ int checkMotionShiftRange(int mot, float t, float t2)
{
    MotOriTrigEnt *e = &D_0055FE58[mot];
    float a = (float)e->f13C;
    float b = (float)e->f140;
    float ab = a + b;

    if (a < 0.0f || b < 0.0f) {
        return 0;
    }
    if ((e->f18C >> 19) & 1) {
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

extern int D_0028F4C0[];
extern int motionFrameUpdate;

int UpdateFrameCounter(void *self)
{
    char *m = MOWORK(self);
    MotOriWork *w = (MotOriWork *)(m + 0x470);
    int nf = GetNbMotionFrames(w->f30);
    float t;
    float r;
    float frame;

    if (w->f58 != 0) {
        w->f58 = 0;
    }
    w->f5C = 0;
    w->f80 = 0;
    if (motionFrameUpdate == 1) {
        t = w->f48 * D_0055FE58[w->f30].f174 * w->f4C *
            (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f);
        if (D_0028F4C0[0] != 0) {
            t = t * D_0055FE58[w->f30].f15C;
        }
        if (w->f54 != 0) {
            switch (w->f68) {
            case 1:
            case 2:
            case 17:
            case 20:
                if (*(int *)(MOWORK(self) + 0x8C) != 0) {
                    float a =
                        1.0f - *(float *)(MOWORK(self) + 0x644) * *(float *)(MOWORK(self) + 0x824);

                    if (a < 0.1f) {
                        a = 0.1f;
                    }
                    if (1.0f < a) {
                        a = 1.0f;
                    }
                    t = t * a;
                }
                break;
            }
        }
        w->f40 = w->f3C;
        w->f3C = w->f3C + t;
        switch (D_0055FE58[w->f30].f150) {
        case 1:
            if ((float)(nf - 1) <= w->f3C) {
                w->f3C = w->f3C - (float)(nf - 1);
                w->f5C = D_0055FE58[w->f30].f150;
                InitFrameDependSequence(m + 0x740);
                clearFrameTriggerState(self);
                if (((D_0055FE58[w->f30].f18C >> 20) & 1) != 0) {
                    w->f80 = 1;
                }
            }
            break;
        case 4:
            r = w->f50;
            r = r < 0.0f ? 0.0f : (1.0f < r ? 1.0f : r);
            w->f3C = (float)(nf - 1) * r;
            break;
        default:
            if ((float)(nf - 1) <= w->f3C) {
                w->f3C = w->f40;
                w->f5C = 1;
            }
            break;
        }
        w->f44 =
            w->f44 + w->f48 * (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f);
        w->f8C = w->f8C + 1;
        if (!(w->fA4 < w->fA0)) {
            w->fA0 = w->fA0 + 1;
        }
        /* The two-frame range tests take a second frame value; here it is the
           same frame, held in a local, and the ROM's mov.s of the loaded frame
           into a second register is that local's copy. */
        frame = w->f3C;
        w->f190 = checkFrameInRange(w->f30, w->f3C);
        w->f194 = checkFrameInRange2(w->f30, w->f3C, frame);
        w->f38 = checkMotionShiftRange(w->f30, w->f3C, frame);
    }
    return w->f5C;
}

inline MotionOrientEntry *GetMotionOrient(int i, int n, int id, int kind)
{
    int found = -1;

    for (; i < n; i++) {
        if (D_002ADD60[i].kind == kind) {
            if (D_002ADD60[i].id == id) {
                return &D_002ADD60[i];
            }
            if (D_002ADD60[i].id == 0x47A) {
                found = i;
            }
        }
    }
    if (found != -1) {
        return &D_002ADD60[found];
    }
    return 0;
}

inline MotionOrientEntry *getMotionOrient(int i, int n, int id, int kind)
{
    MotionOrientEntry *p = GetMotionOrient(i, n, id, kind);

    if (p != 0) {
        return p;
    }
    return &D_002BC4A8;
}

extern int D_0063B188;
extern char D_0063B968[];
extern char D_0063B990[];
extern char D_0063B998[];
extern char D_0063B9A0[];
extern char D_0063B9A8[];
extern char D_0063B9B0[];
extern char D_006202F0[];
extern char *matrixptr;

void sendStateMail(void *self)
{
    float m[4][4];
    float pos[4];
    char *w = MOWORK(self) + 0x470;

    if (D_0063B188 != 0) {
        MatrixDrive_PushMatrix();
        sceVu0TransposeMatrix(m, matrixptr + 0x80);
        m[0][3] = m[1][3] = m[2][3] = 0.0f;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        GetRootPosition(pos, self);
        MatrixDrive_TransMatrixV((char *)pos);
        sceVu0MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), m);
    }
    if (*(int *)(w + 0x14) & 0x2) {
        if (D_0063B188 != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, 80.0f, 0.0f);
            DispWireString(D_0063B990);
            MatrixDrive_PopMatrix();
        }
    }
    if (*(int *)(w + 0x14) & 0x4) {
        iosOmSendMail(self, 7, self);
        if (D_0063B188 != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(-50.0f, 0.0f, 0.0f);
            DispWireString(D_0063B998);
            MatrixDrive_PopMatrix();
        }
    }
    if (*(int *)(w + 0x14) & 0x10) {
        iosOmSendMail(self, 8, self);
        if (D_0063B188 != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(50.0f, 40.0f, 0.0f);
            DispWireString(D_0063B9A0);
            MatrixDrive_PopMatrix();
        }
    }
    if (*(int *)(w + 0x14) & 0x20) {
        iosOmSendMail(self, 9, self);
        if (D_0063B188 != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(50.0f, 0.0f, 0.0f);
            DispWireString(D_0063B9A8);
            MatrixDrive_PopMatrix();
        }
    }
    if (*(int *)(w + 0x14) & 0x1000) {
        iosOmSendMail(self, 33, self);
        if (D_0063B188 != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(50.0f, 0.0f, 0.0f);
            DispWireString(D_006202F0);
            MatrixDrive_PopMatrix();
        }
    }
    if (*(int *)(w + 0x14) & 0x8) {
        iosOmSendMail(self, 10, self);
        if (D_0063B188 != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, -80.0f, 0.0f);
            DispWireString(D_0063B9B0);
            MatrixDrive_PopMatrix();
        }
    }
    if (*(int *)(w + 0x14) & 0x400) {
        iosOmSendMail(self, 26, self);
        if (D_0063B188 != 0) {
            MatrixDrive_PushMatrix();
            MatrixDrive_TransMatrix(0.0f, -80.0f, 0.0f);
            DispWireString(D_0063B968);
            MatrixDrive_PopMatrix();
        }
    }
    if (*(int *)(w + 0x14) & 0x800) {
        iosOmSendMail(self, 27, self);
    }
    if (*(int *)(w + 0x14) & 0x100) {
        iosOmSendMail(self, 15, self);
    }
    if (*(int *)(w + 0x14) & 0x200) {
        iosOmSendMail(self, 16, self);
    }
    if (D_0063B188 != 0) {
        MatrixDrive_PopMatrix();
    }
}

/* Listing lines 413-425: a static inline both shift functions absorb, with no
 * symbol and no census row, so its name is not on the disc; searchMotionShift
 * is this repo's spelling. It walks the request table at the work area's 0x1C
 * and returns the paired entry from the table at 0x20. */
static inline int searchMotionShift(void *self, int id, int cur)
{
    char *m = MOWORK(self) + 0x470;
    int i;

    if (*(int **)(m + 0x1C) != 0 && *(int **)(m + 0x20) != 0) {
        for (i = 0; (*(int **)(m + 0x1C))[i] != -1; i++) {
            if ((*(int **)(m + 0x1C))[i] == id) {
                if ((*(int **)(m + 0x20))[i] == cur) {
                    return 0x479;
                }
                return (*(int **)(m + 0x20))[i];
            }
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", shiftMotionData);

extern char D_00620300[];
extern char D_0063B9B8[];
/* kept local: this TU's uses of FeedbackWallWorkInfoToBrainSystem do not fit the prototype in motionManager2.h */
extern void FeedbackWallWorkInfoToBrainSystem(void *self);

void shiftMotionOrientEndFunc(void *self)
{
    char *w = MOWORK(self) + 0x470;
    int x;

    if (*(int *)(w + 0x1AC) == -1) {
        debug_StdPrintfDummy(D_00620300);
        debug_assert(D_006202D0, 745);
        __assert(D_006202D0, 745, D_0063B9B8);
    }
    StopSEPackageWithGroupVariation(self, 0);
    StopSEPackageWithGroupVariation(self, 1);
    *(int *)(w + 0x1B8) = 0;
    x = *(int *)(w + 0x68);
    if (x < 9) {
        if (x >= 7) {
            goto ok;
        }
        return;
    }
    if (x != 16) {
        return;
    }
ok:
    if (D_0055FE58[*(int *)(w + 0x30)].f130 == 0) {
        return;
    }
    FeedbackWallWorkInfoToBrainSystem(self);
}

inline void CopyBlendMotionDataSource(void *self, short ang)
{
    char quat[0x10];
    char *mot = *(char **)(MOWORK(self) + 0x7D0);
    int i = 0;

    CopyMotion(mot, *(char **)(MOWORK(self) + 0x7B4), *(int *)(MOWORK(self) + 0x88));
    CopyVector(MOWORK(self) + 0x7E0, MOWORK(self) + 0x7C0);
    CopyVector(MOWORK(self) + 0x7F0, MOWORK(self) + 0x130);
    *(struct MotOriFloat *)(MOWORK(self) + 0x808) = *(struct MotOriFloat *)(MOWORK(self) + 0x160);
    *(struct MotOriHead8 *)(MOWORK(self) + 0x800) = *(struct MotOriHead8 *)MOWORK(self);
    while (*(int *)(*(char **)(MOWORK(self) + 0x8C) + i * 0x40 + 0x38) == -1) {
        SetQuaternionByAxisRotate(quat, ang, 0.0f, 1.0f, 0.0f);
        MultiQuaternion(mot + i * 0x20 + 0x10, quat, mot + i * 0x20 + 0x10);
        i = *(int *)(*(char **)(MOWORK(self) + 0x8C) + i * 0x40 + 0x34);
    }
}

extern char D_0063B9C0[];
extern char D_00620348[];
extern char D_00620390[];
extern char D_006203B8[];
extern char D_006203D8[];
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *dst, void *src);
/* kept local: GetOutOutsideOfWall is defined in src/motionManager2 and no header of
 * this tree declares it */
extern void GetOutOutsideOfWall(void *self, float d);

void shiftMotionOrientBeginFunc(void *self, int a1, int a2, int a3)
{
    Vec16 v;
    char *m = MOWORK(self);
    char *w = m + 0x470;
    char *p = m + 0xA0;
    short ang;

    debug_StdPrintfDummy(D_00620348, D_005D1278[*(int *)(w + 0xD0)].s, *(int *)(w + 0xD0),
                         D_0055FE58[*(int *)(w + 0x30)].name, *(int *)(w + 0x30), D_0063B9C0);
    shiftMotionData((int)self, a1, a2, a3);
    if (*(int *)(w + 0x6C) != 0) {
        GetOutOutsideOfWall(self, *(float *)(p + 0x338));
    }
    memset(&v, 0, 16);
    ang = 0;
    v.f[2] = 1.0f;
    if (*(int *)(w + 0x68) != 0 && *(int *)(w + 0x68) != 6) {
        int kind = D_0055FE58[*(int *)(w + 0x94)].f108;

        if (((unsigned int)D_0055FE58[*(int *)(w + 0x30)].f18C >> 27) & 1 || kind != 0) {
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            if (kind != 0 && kind != 1) {
                ang = (short)(kind * 32768 / 180);
                debug_StdPrintfDummy(D_00620390, ang, (float)ang * 180.0f / 32768.0f);
            } else {
                float mtx[4][4];

                GetMatrixFromQuaternion((char *)mtx, m + 0xE0);
                sceVu0ApplyMatrix(&v, mtx, &v);
                v.f[1] = 0.0f;
                _NormalizeVector(&v, &v);
                ang = GetTableArcTan2(v.f[0], v.f[2]);
                debug_StdPrintfDummy(D_006203B8, ang, (float)ang * 180.0f / 32768.0f);
            }
            MatrixDrive_RotMatrixY(ang);
            sceVu0ApplyMatrix(w + 0xB0, MatrixDrive_GetMatrix(), w + 0xB0);
        } else {
            debug_StdPrintfDummy(D_006203D8, 0, (float)ang);
        }
    }
    CopyBlendMotionDataSource(self, ang);
    StopFDSVibration(MOWORK(self) + 0x740);
    InitFrameDependSequence(MOWORK(self) + 0x740);
    clearFrameTriggerState(self);
}

void ForTest_ForceShiftMotion(int a0, int a1)
{
    shiftMotionData(a0, a1, a1, 0);
}

/* Listing lines 877-920: a static inline with no symbol and no census row, so
 * its name is not on the disc; checkMotionShiftReady is this repo's spelling.
 * It clears the pending-shift words and reports whether the entry may start.
 * The 0x479 arm's refusal jumps back to the guard's `return 0` (listing 886):
 * the ROM keeps that block and branches to it backward, where a second
 * `return 0` in the arm is the copy jump2's cross-jumping keeps instead (it
 * deletes the first identical block it reaches, jump.c find_cross_jump). */
static inline int checkMotionShiftReady(char *m, MotionOrientEntry *p)
{
    int kind;

    *(int *)(m + 0x10) = 0;
    *(int *)(m + 0xC) = 0;
    if (*(int *)(m + 0x74) != 0 || p->kind == -1) {
    fail:
        return 0;
    }
    kind = p->nextId;
    *(int *)(m + 0x90) = kind;
    if (kind == 0x479) {
        if (*(int *)(m + 0x5C) == 0) {
            goto fail;
        }
        *(int *)(m + 0x10) = 4;
        return 1;
    }
    if (*(int *)(m + 0x5C) != 0) {
        *(float *)(m + 0x3C) = (float)(GetNbMotionFrames(*(int *)(m + 0x30)) - 1) - 1.0e-6f;
        *(int *)(m + 0x10) |= 0x10;
        return 1;
    }
    return p->fC != -1 && (float)p->fC < *(float *)(m + 0x3C);
}

int normalMotionShift(void *self, int force)
{
    char *w = MOWORK(self) + 0x470;
    MotionOrientEntry *p = getMotionOrient(*(int *)(w + 0x4), *(int *)(w + 0x8), *(int *)(w + 0x2C),
                                           *(int *)(w + 0xD0));

    if (force == 0) {
        if (p->id == 0x47A) {
            return 0;
        }
    }
    if (checkMotionShiftReady(MOWORK(self) + 0x470, p) != 0) {
        int kind = p->nextId;
        int mode = p->f10;
        int next;
        int r = -1; /* no pairing found; the else arm searches with it as cur */

        if (kind == 0x479) {
            kind = p->id;
            mode = 5;
            r = searchMotionShift(self, kind, *(int *)(w + 0x30));
            if (r == -1 || r == 0x479) {
                return 0;
            }
            next = r;
        } else {
            r = searchMotionShift(self, kind, r);
            next = (r == -1) ? kind : r;
        }
        shiftMotionOrientEndFunc(self);
        shiftMotionOrientBeginFunc(self, next, kind, mode);
        return 1;
    }
    return 0;
}

/* Listing lines 432-441: a static inline with no symbol and no census row, so
 * its name is not on the disc; findParallelMotion is this repo's spelling.
 * The table at D_00629E40 is 54 rows of five words, keyed on the current and
 * the requested motion. */
typedef struct {
    /* 0x00 */ int id;
    /* 0x04 */ int kind;
    /* 0x08 */ int nextId;
    /* 0x0C */ int fC;
    /* 0x10 */ int f10;
} MotOriParallelEnt;

extern MotOriParallelEnt D_00629E40[];

static inline MotionOrientEntry *findParallelMotion(int cur, int next)
{
    int i;

    if (cur == next) {
        return &D_002BC4A8;
    }
    for (i = 0; i < 54; i++) {
        if (D_00629E40[i].id == cur) {
            if (D_00629E40[i].kind == next) {
                return (MotionOrientEntry *)&D_00629E40[i];
            }
        }
    }
    return 0;
}

/* Listing 998 to 1032: the -1 test encloses the body and every refusal falls
 * to the one `return 0` at the end.  loop.c (find_and_verify_loops) moves the
 * inlined search's found-block to the first barrier after its loop, which the
 * ROM has after findParallelMotion's cur == next return; an early
 * `return 0` for -1 would put a barrier ahead of it. */
int parallelMotionShift(void *self)
{
    char *m = MOWORK(self) + 0x470;
    int next = searchMotionShift(self, *(int *)(m + 0x2C), *(int *)(m + 0x30));
    MotionOrientEntry *p;

    if (next != -1) {
        p = findParallelMotion(*(int *)(m + 0x30), next);

        if (p != 0) {
            if (checkMotionShiftReady(MOWORK(self) + 0x470, p) != 0) {
                shiftMotionOrientEndFunc(self);
                shiftMotionOrientBeginFunc(self, p->nextId, *(int *)(m + 0x2C), p->f10);
                return 1;
            }
        } else if (next != 0x479) {
            MotionOrientEntry e = {*(int *)(m + 0x30), *(int *)(m + 0xD0), next, *(int *)(m + 0x24),
                                   *(int *)(m + 0x28)};

            if (checkMotionShiftReady(MOWORK(self) + 0x470, &e) != 0) {
                shiftMotionOrientEndFunc(self);
                shiftMotionOrientBeginFunc(self, next, *(int *)(m + 0x2C), *(int *)(m + 0x28));
                return 1;
            }
        }
    }
    return 0;
}

extern char D_0063B9D0[];
extern int D_0063B194;
extern void *D_00639EA4;
extern void *D_00639EA8;
extern int D_0063B9C4;
extern int D_0063B160;
extern char D_006203F0[];
extern char D_00620438[];
extern int D_0028F8F0[];
extern int D_0063B9C8;
extern int frame_count;

/* The four one-character spinners the debug line cycles with the frame count. */
typedef struct MotOriSpin {
    char *s[4];
} MotOriSpin;

extern MotOriSpin D_00620428;

char *SetMotionRequest(void *self, int mot, MotOriReq req)
{
    char *w = (char *)*(int *)((char *)self + 0x15C) + 0x470;
    int old = *(int *)(w + 0xD0);

    *(int *)(w + 0xD0) = mot;
    if (normalMotionShift(self, 1) != 0) {
        *(int *)(w + 0x44) = 0;
        switch (*(int *)(w + 0x68)) {
        case 3:
        case 7:
        case 8:
        case 9:
        case 10:
        case 13:
        case 15:
        case 16:
            *(MotOriReq *)((char *)*(int *)((char *)self + 0x15C) + 0x180) = req;
            debug_StdPrintfDummy(D_006203F0);
            break;
        }
        if ((D_0063B194 == 0 && self == D_00639EA4) || (D_0063B194 == 1 && self == D_00639EA8) ||
            (D_0063B194 == 2 && self == isysGObjSearchFromObjKindID_begin(32)) ||
            (D_0063B194 == 3 && self == isysGObjSearchFromObjKindID_begin(4)) ||
            (D_0063B194 == 4 && self == isysGObjSearchFromObjKindID_begin(47))) {
            if (D_0063B9C4 != 0 && D_0063B160 != 0) {
                debug_PrintFontWindow(0xC0FF20, D_0063B9D0);
            }
            orientDebug(self, mot, 0xFFFFFF80);
            D_0063B9C4 = 0;
        }
    } else {
        *(int *)(w + 0xD0) = old;
        if (D_0028F8F0[0] & 0x2) {
            if ((D_0063B194 == 0 && self == D_00639EA4) ||
                (D_0063B194 == 1 && self == D_00639EA8) ||
                (D_0063B194 == 2 && self == isysGObjSearchFromObjKindID_begin(32)) ||
                (D_0063B194 == 3 && self == isysGObjSearchFromObjKindID_begin(4)) ||
                (D_0063B194 == 4 && self == isysGObjSearchFromObjKindID_begin(47))) {
                MotOriSpin spin = D_00620428;

                if (D_0063B9C8 != mot && D_0063B9C4 != 0) {
                    D_0063B9C4 = 0;
                    if (D_0063B160 != 0) {
                        debug_PrintFontWindow(0xC0FF20, D_0063B9D0);
                    }
                }
                if (D_0063B160 != 0) {
                    MotOriName name = D_005D1278[mot];

                    debug_PrintFontWindow(0x3080FF20, D_00620438, spin.s[frame_count & 3], name.s,
                                          D_0055FE58[*(int *)(w + 0x30)].name, ++D_0063B9C4);
                }
                D_0063B9C8 = mot;
            }
        }
    }
    return w;
}

inline void SetParallelMotionTableWithNoRequest(void *self, int a1, int a2)
{
    char *m = (char *)*(int *)((char *)self + 0x15C) + 0x470;

    if (*(int *)(m + 0x18) == 0) {
        *(int *)(m + 0x1C) = a2;
        *(int *)(m + 0x20) = a1;
    }
}

inline void SetParallelMotionTable(void *self, int a1, int a2, int a3, int a4)
{
    char *m = (char *)*(int *)((char *)self + 0x15C) + 0x470;
    int old = *(int *)(m + 0xD0);

    *(int *)(m + 0xD0) = 0x10D;
    SetParallelMotionTableWithNoRequest(self, a1, a2);
    *(int *)(m + 0x24) = a3;
    *(int *)(m + 0x28) = a4;
    if (parallelMotionShift(self) != 0) {
        *(int *)(m + 0x44) = 0;
    } else {
        *(int *)(m + 0xD0) = old;
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getNodeBlendedFloatingMotion);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getMotionGeometry);

extern char D_00620580[];
extern char D_006205D8[];

/* The two line colours the debug bar graph draws with: 16-byte records the ROM
 * copies into the frame with ld/sd, so the type is 8-byte aligned; the union
 * spelling is the one ico2/omori/src/camera-editor.c already carries (BoxCol4). */
typedef union {
    unsigned int c[4];
    unsigned long long w[2];
} MotOriCol4;

extern const MotOriCol4 D_00620610;
extern const MotOriCol4 D_00620620;
extern int ScreenWidth;
extern int ScreenHeight;

/* RECONSTRUCTION, the type and enumerator names are ours: debug_bar_flag is debug.o's
 * debug bar mode (MAIN.MAP line 7189 names the word debug_bar_flag by position),
 * which ico2/common/src/debug.c clears and debug_DrawBar dispatches on 1 and 2.
 * The ROM proves it is not read as a plain int here: its load sits in the clamp
 * loop's preheader, and gcse only places it there when the loop body is
 * transparent for it, which the loop's int store to the shape weight makes false
 * for any int-typed global (gcse's mems_conflict_for_gcse_p asks
 * true_dependence, and DIFFERENT_ALIAS_SETS_P is its only exit). An enumerated
 * mode has an alias set of its own; the act-game MpsrMode record is the same
 * proof in another TU. */
enum DebugDisplayMode { DEBUG_DISPLAY_OFF, DEBUG_DISPLAY_ON, DEBUG_DISPLAY_FULL };

extern enum DebugDisplayMode debug_bar_flag;
/* kept local: motionFileManager.h types the argument unsigned int *, this TU's is the motion block */
extern int CheckMotionIncludeFacialData(void *mot);
/* kept local: no header declares it; the shape motion is written into the caller's buffer */
extern void GetFloatingShapeMotion(float *dst, void *mot, int n, float frame);
/* kept local: no header declares it (lineManager.h has only the segment calls) */
extern void Draw2DLine(int *p1, int *p2, int *color, int z);

void getShapeGeometry(void *self)
{
    char *m = (char *)*(int *)((char *)self + 0x15C) + 0x470;

    if (D_0055FE58[*(int *)(m + 0x30)].f178 == 0x140) {
        void *mot = D_004EB758[*(int *)(m + 0x30)];

        if (CheckMotionIncludeFacialData(mot) == 0) {
            int n = **(int **)((char *)mot + 0x10);
            float buf[n];
            int i;

            GetFloatingShapeMotion(buf, mot, n, *(float *)(m + 0x3C));
            if (n != 0) {
                int cnt = *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x834);

                if (cnt != 0) {
                    if (cnt != n) {
                        debug_StdPrintfDummy(D_00620580, n, cnt);
                    }
                    for (i = 0; i < n; i++) {
                        float x = buf[i] * 0.01f;
                        int *p = (int *)(i * 4 +
                                         *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x838));

                        if (x < 0.0f) {
                            if (0.0001f < -x) {
                                *(float *)p = x;
                            } else {
                                *p = 0;
                            }
                        } else {
                            if (0.0001f < x) {
                                *(float *)p = x;
                            } else {
                                *p = 0;
                            }
                        }
                    }
                } else {
                    debug_StdPrintfDummy(D_006205D8);
                }
                if (debug_bar_flag != 0) {
                    gif_StartPacketPri(11);
                    {
                        int p1[4];
                        int p2[4];
                        MotOriCol4 c0;
                        MotOriCol4 c1;

                        c0 = D_00620610;
                        c1 = D_00620620;

                        gif_SetAlpha(1, 5, 128);
                        for (i = 0; i < n; i++) {
                            p1[0] = (ScreenWidth / 2 + 1824) << 4;
                            p2[0] = (ScreenWidth / 2 + 2024) << 4;
                            p1[1] = p2[1] = (ScreenHeight / 2 - n * 6 + 2024 + i * 6) << 4;
                            Draw2DLine(p1, p2, (int *)c0.c, -1);
                            p1[0] = p2[0] = (ScreenWidth / 2 + (int)buf[i] + 1924) << 4;
                            p1[1] = (ScreenHeight / 2 - n * 6 + 2025 + i * 6) << 4;
                            p2[1] = (ScreenHeight / 2 - n * 6 + 2028 + i * 6) << 4;
                            Draw2DLine(p1, p2, (int *)c1.c, -1);
                        }
                        gif_EndPacket();
                    }
                }
            }
        }
    }
}

/* kept local: this TU's uses of GetStreamMotion do not fit the prototype in motionManager2.h */
extern int GetStreamMotion(void *dst, float *v, void *sm, int n);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(float *dst, float *src, float s);
/* kept local: this TU's uses of DispSkelton do not fit the prototype in motionManager2.h */
extern void DispSkelton(void *self, void *m);

/* Listing lines 1640-1647: a static inline both stream-geometry functions absorb
 * (once and twice), with no symbol and no census row, so its name is not on
 * the disc; getStreamVec is this repo's spelling. */
static inline int getStreamVec(void *self, void *sm, float *v, void *mot)
{
    float s = *(float *)(*(char **)(MOWORK(self) + 0x870) + 0x20);

    if (GetStreamMotion(mot, v, sm, *(int *)(MOWORK(self) + 0x8C)) != 0) {
        if (*(int *)(MOWORK(self) + 0x660) != 0) {
            _ScaleVectorXYZ(v, v, s);
        }
        v[0] -= *(float *)(MOWORK(self) + 0x670);
        v[1] -= *(float *)(MOWORK(self) + 0x674);
        v[2] += *(float *)(MOWORK(self) + 0x678);
        return 1;
    }
    return 0;
}

void getStreamMotionGeometry(void *self, void *sm)
{
    float v[4];
    char mot[*(int *)(MOWORK(self) + 0x88) * 0x20];

    if (getStreamVec(self, sm, v, mot)) {
        GetGeometryOfMotion(self, mot, mot, v, 1.0f, ZeroVector, -1);
        CopyMotion(*(void **)(MOWORK(self) + 0x7B4), mot, *(int *)(MOWORK(self) + 0x88));
        CopyVector(MOWORK(self) + 0x7C0, v);
        DispSkelton(self, mot);
    }
}

/* kept local: this declaration is identical to the motionManager2.h prototype, but the
 * TU cannot include that header while its GetStreamMotion, DispSkelton and
 * FeedbackWallWorkInfoToBrainSystem uses still need declarations of their own. */
extern void GetBlendedMotion(void *dst, float *dv, void *m1, float *v1, void *m0, float *v0,
                             float t, int tbl, int n);

void getStreamBlendMotionGeometry(void *self, void *sm0, void *sm1, float t)
{
    float v0[4];
    float v1[4];
    float v2[4];
    int n = *(int *)(MOWORK(self) + 0x88);
    char mot0[n * 0x20];

    if (getStreamVec(self, sm0, v0, mot0)) {
        char mot1[n * 0x20], mot2[n * 0x20];

        getStreamVec(self, sm1, v1, mot1);
        GetBlendedMotion(mot2, v2, mot1, v1, mot0, v0, t, *(int *)(MOWORK(self) + 0x820), n);
        GetGeometryOfMotion(self, mot2, mot2, v2, 1.0f, ZeroVector, -1);
        CopyMotion(*(void **)(MOWORK(self) + 0x7B4), mot2, *(int *)(MOWORK(self) + 0x88));
        CopyVector(MOWORK(self) + 0x7C0, v2);
        DispSkelton(self, mot2);
    }
}

/* Reconstruction, this repo's name: the listing gives the whole clamp AND its own
 * `int *p` declaration on one physical source line, at 1711 in
 * getStreamBlendShapeGeometry and again at 1729 in getStreamShapeGeometry, so the
 * developer's source held a macro with a block body shared by both functions. */
#define SET_SHAPE_VALUE(self, i, x)                                                                \
    {                                                                                              \
        int *p = (int *)((i) * 4 + *(int *)((char *)*(int *)((char *)(self) + 0x15C) + 0x838));    \
                                                                                                   \
        if ((x) < 0.0f) {                                                                          \
            if (0.0001f < -(x)) {                                                                  \
                *(float *)p = (x);                                                                 \
            } else {                                                                               \
                *p = 0;                                                                            \
            }                                                                                      \
        } else {                                                                                   \
            if (0.0001f < (x)) {                                                                   \
                *(float *)p = (x);                                                                 \
            } else {                                                                               \
                *p = 0;                                                                            \
            }                                                                                      \
        }                                                                                          \
    }

/* kept local: this declaration is identical to the motionManager2.h prototype, but the
 * TU cannot include that header while its GetStreamMotion, DispSkelton and
 * FeedbackWallWorkInfoToBrainSystem uses still need declarations of their own. */
extern int GetStreamShapeMotion(float *dst, void *sm);

/* The else arm is a developer wrapper macro that expanded to a do/while(0) block,
 * the same shape this tree already carries in ico2/sugipon/src/rope.c,
 * ico2/common/src/PObj.c and ico2/fumi/src/act-game.c. The back edge costs no
 * instructions, and the listing proves it two ways: the loop note raises the else
 * arm one loop level, which is what puts `n` ahead of the alloca size in
 * global.c's allocno_compare and hands `n` $s0 the way the ROM has it, and the
 * -g line notes then reproduce the listing's own attribution row for row over
 * 1714 to 1718, with the epilogue on the same line as the closing brace. */
void getStreamBlendShapeGeometry(void *self, void *sm0, void *sm1, float t)
{
    int i;
    int n = *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x834);
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
            do {
                for (i = 0; i < n; i++)
                    *(int *)(*(int *)((char *)*(int *)((char *)self + 0x15C) + 0x838) + i * 4) = 0;
            } while (0);
    }
}

void getStreamShapeGeometry(void *self, void *sm)
{
    int n = *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x834);

    if (n != 0) {
        float buf[n];
        int i;

        if (GetStreamShapeMotion(buf, sm) != 0) {
            for (i = 0; i < n; i++) {
                float x = buf[i] * 0.01f;
                int *p = (int *)(i * 4 + *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x838));

                if (x < 0.0f) {
                    if (0.0001f < -x) {
                        *(float *)p = x;
                    } else {
                        *p = 0;
                    }
                } else {
                    if (0.0001f < x) {
                        *(float *)p = x;
                    } else {
                        *p = 0;
                    }
                }
            }
        } else {
            for (i = 0; i < n; i++) {
                *(int *)(*(int *)((char *)*(int *)((char *)self + 0x15C) + 0x838) + i * 4) = 0;
            }
        }
    }
}

void getStreamMotion(void *self)
{
    void *s = *(void **)(MOWORK(self) + 0x470);
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

extern char D_00620630[];

void ExecMotionOrient(void *self)
{
    char *w = (char *)*(int *)((char *)self + 0x15C) + 0x470;

    if (*(int *)(w + 0x18) != 0) {
        debug_StdPrintfDummy(D_00620630, self);
    }
    if (*(int *)w == -1) {
        if (*(int *)(w + 0xD0) != 0x10D) {
            normalMotionShift(self, 0);
        } else {
            parallelMotionShift(self);
        }
        if ((D_0063B194 == 0 && self == D_00639EA4) || (D_0063B194 == 1 && self == D_00639EA8) ||
            (D_0063B194 == 2 && self == isysGObjSearchFromObjKindID_begin(32)) ||
            (D_0063B194 == 3 && self == isysGObjSearchFromObjKindID_begin(4)) ||
            (D_0063B194 == 4 && self == isysGObjSearchFromObjKindID_begin(47))) {
            if (*(int *)(w + 0xC) != 0) {
                if (D_0063B9C4 != 0 && D_0063B160 != 0) {
                    debug_PrintFontWindow(0xC0FF20, D_0063B9D0);
                }
                orientDebug(self, *(int *)(w + 0xD0), 0xE0FF20);
                D_0063B9C4 = 0;
            }
        }
        if (*(int *)(w + 0x58) != 0) {
            int n = *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x834);
            int i;

            for (i = 0; i < n; i++) {
                *(int *)(i * 4 + *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x838)) = 0;
            }
        }
        getMotionGeometry(self);
        getShapeGeometry(self);
    } else {
        getStreamMotion(self);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", SetNodeRotationLimitDataTable);

inline void InitMotionOrient(void *self, int a1, int a2, int a3, int a4, int a5)
{
    char *m = *(char **)((char *)self + 0x15C) + 0x470;

    if (a3 >= 0 && a4 >= 0) {
        SetNodeRotationLimitDataTable(self, a3, a4);
    }
    *(int *)(m + 0x4) = a1;
    *(int *)(m + 0x8) = a2;
    shiftMotionData((int)self, a5, a5, 0);
    *(int *)(m + 0x1AC) = soundSeGroupGet();
    *(int *)(m + 0x1B0) = soundSeGroupGet();
}

inline unsigned int GetCurrentMotionDirectionAdjustFlag(char *a0)
{
    char *rec = (char *)D_0055FE58 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194;
    return *(unsigned int *)(rec + 0x188) >> 30;
}

inline int ExecuteSlipProc(char *a0)
{
    char *e = *(char **)(a0 + 0x15C);
    if (*(int *)(e + 0x628) != *(int *)(e + 0x624)) {
        StopSEPackageWithGroupVariation(a0, 1);
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x624) & 0x100000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x72, 1);
        }
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x624) & 0x200000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x74, 1);
        }
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x624) & 0x400000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x76, 1);
        }
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x624) & 0x800000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x78, 1);
        }
    }
    return 1;
}

inline int ExecutePauseSlipProc(char *a0)
{
    if (D_0028F4D4[0] != 0) {
        *(int *)(*(char **)(a0 + 0x15C) + 0x628) = 0;
        StopSEPackageWithGroupVariation(a0, 1);
    }
    return 1;
}
