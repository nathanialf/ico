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
#include <libvu0.h>

extern MotionOrientEntry D_002ADD60[];
extern MotionOrientEntry D_002BC4A8;
/* kept local: this TU's uses of CopyMotion do not fit the prototype in motionManager2.h */
extern void CopyMotion(void *dst, void *src, int n);

struct MotOriHead8 {
    long long v;
} __attribute__((packed));

struct MotOriFloat {
    float f;
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

extern MotOriTrigEnt D_0055FE58[];
extern int D_0028F4D4[];

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", orientDebug);

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

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", UpdateFrameCounter);

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

    if (p == 0) {
        p = &D_002BC4A8;
    }
    return p;
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

/* The motion-name row the debug line prints: 32 bytes the ROM copies with
 * ldl/ldr, so a 4-aligned record and not an 8-aligned one. */
typedef struct MotOriName {
    char s[0x20];
} MotOriName;

extern MotOriName D_005D1278[];
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

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", normalMotionShift);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", parallelMotionShift);

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
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getShapeGeometry);

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

/* kept local: this TU's uses of GetBlendedMotion do not fit the prototype in motionManager2.h */
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

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getStreamBlendShapeGeometry);

/* kept local: this TU's uses of GetStreamShapeMotion do not fit the prototype in motionManager2.h */
extern int GetStreamShapeMotion(float *dst, void *sm);

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
