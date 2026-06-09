#include "common.h"
#include "ico/types.h"

/* src/box.c — pushable box + interactable lever/switch gameplay (sugipon).
 *
 * SITUATION: box.o is a UNITY build — this file #includes src/switch.c.inc.
 * The shipped function order is plain source order (ee-gcc 2.9 does not
 * reorder functions; no -ffunction-sections, matching parappa2's period
 * model), so the switch and box functions interleave by VMA exactly as the
 * source is laid out here. Each switch block is pulled in at its VMA slot via
 * `#define BOX_SWBLK n` + `#include "switch.c.inc"`; the surrounding
 * `#line "src/switch.c"` / `#line "src/box.c"` directives keep each function's
 * __FILE__ correct ("src/box.c" @ D_00610FB0, "src/switch.c" @ D_00610F40)
 * even though both live in one translation unit. This replaces the former
 * -ffunction-sections + postprocess_box_order.py machinery. */

#undef BOX_SWBLK
#define BOX_SWBLK 0
#include "switch.c.inc"
#line 1 "src/box.c"

typedef struct {
    float f_0;
    float f_4;
    float f_8;
    char _C[0x14];
    float f_20;
    char _24[0xC];
    int f_30;
    char _34[0xC];
} __attribute__((aligned(8))) SEParams;

extern SEParams D_004B8C40;
extern void MoveNextStage_Clear(int a0, int a1, int a2, int a3, void *buf, int a5, int a6, int a7);

void landingSE(void *a0, float f0, float f1, float f2, float f3) {
    SEParams buf = D_004B8C40;
    buf.f_0 = f0;
    buf.f_4 = f1;
    buf.f_8 = f2;
    buf.f_20 = f3;
    buf.f_30 = (int)a0;
    *(int *)a0 = 0;
    MoveNextStage_Clear(0x3D, 0x44, -1, 0, &buf, -1, 7, 1);
}

int fallDownStartSE(void *a0) {
    return GOBJ_SUB(a0)->p_7F0->f_8;
}

#undef BOX_SWBLK
#define BOX_SWBLK 1
#include "switch.c.inc"
#line 32 "src/box.c"

typedef struct { int f_0; int f_4; char _8[0x14]; void (*f_1C)(int, int); } BoxB1B95E0;

extern void func_00102828(void *a0);

extern void *func_00105078(void);
extern void LocalizeDirectionOrient();
extern void func_00104E38(int a0);
extern void func_00105108(float a0, float a1, float a2);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);

void pushStartSE(void *a0, void *a1) {
    void *box = *(void **)((char *)(*(void **)((char *)a1 + 0x15C)) + 0x7F0);
    void *m = func_00105078();
    LocalizeDirectionOrient(m, a1);
    func_00104E38(*(short *)((char *)box + 0x2));
    func_00105108(0.0f, -50.0f, 0.0f);
    MatrixDrive_TurnObjectMatrix(a0, (char *)func_00105078() + 0x30);
}

void pullStartSE(void *self) {
    int *d = *(int **)((char *)self + 0x15C);
    BoxB1B95E0 *B = *(BoxB1B95E0 **)((char *)d + 0x7F0);
    int mode = B->f_4;
    if (mode != -1 && mode != 1) {
        void (*fp)(int, int) = B->f_1C;
        if (fp != 0)
            fp(d[0], 0);
    } else {
        void (*fp)(int, int) = B->f_1C;
        if (fp != 0)
            fp(d[0], B->f_4);
    }
    func_00102828(self);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", wallHitSE);

#undef BOX_SWBLK
#define BOX_SWBLK 2
#include "switch.c.inc"
#line 72 "src/box.c"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", initFallDown);

typedef struct { short f_0; short f_2; char _4[0xC]; void *f_10; } BoxC1B9A58;

extern void func_0010F048(void *a0);
extern void func_00104D20(void);
extern void *func_00105078(void);
extern void LocalizeDirectionOrient();
extern void func_00104E38(int a0);
extern void func_00104D48(int a0);
extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern void file_Init(void *a0);
extern void func_00105068(void);

void checkFieldContact(void *a0) {
    BoxC1B9A58 *box = *(BoxC1B9A58 **)((char *)(*(int **)((char *)a0 + 0x15C)) + 0x7F0);
    void *m;
    void *p10;
    func_0010F048(a0);
    func_00104D20();
    m = func_00105078();
    LocalizeDirectionOrient(m, a0);
    func_00104E38(box->f_2);
    func_00104D48(box->f_0);
    p10 = box->f_10;
    m = func_00105078();
    MatrixDrive_TurnXObjectMatrixYZ(*(void **)((char *)p10 + 0xC), m);
    file_Init(box->f_10);
    func_00105068();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", execNormalMove);

#undef BOX_SWBLK
#define BOX_SWBLK 3
#include "switch.c.inc"
#line 108 "src/box.c"

void InitBoxGeo(int a0) {
    playSEConditionID(a0, 0x4);
}

extern void playSEConditionID(int a0, int a1);

void execAutoMove(int a0) {
    playSEConditionID(a0, 0xD);
}

void initWheels(int a0) {
    playSEConditionID(a0, 0x1E);
}

#undef BOX_SWBLK
#define BOX_SWBLK 4
#include "switch.c.inc"
#line 125 "src/box.c"

/* box__1BA660 0x7F0 view (local) */
typedef struct { int f_0; char _4[0x1C]; int f_20; char _pad24[0x34]; int f_58; char _pad5C[0xB4]; int f_110; int f_114; char _pad118[0x20]; int f_138; char _pad13C[0x4]; int f_140; } BoxGeo2;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", dispWheels);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", getNearestPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", onPathInitialize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", onPath);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", playAnimationCore);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", MoveFloatingBox);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", avoidCharGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", execFloating);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", initFloating);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", _checkItemBreak);

extern void GetInverseQuaternion(void *a0, void *a1);
extern void func_00102840(void *self, void *src);
extern int func_002610F0(void);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void _checkItemBreak(void *a0);
extern int D_002724B0[];
extern int D_00271BD0[];
extern int D_004BAAC0[];

void initLanding(void *self) {
    char *d = (char *)*(int *)((char *)self + 0x15C);
    char *box = (char *)*(int *)(d + 0x7F0);
    *(int *)(d + 0x70) = *(int *)((char *)*(int *)(box + 0x160) + 0x70);
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x78) = 1;
    GetInverseQuaternion((char *)*(int *)((char *)self + 0x15C) + 0xC0, D_002724B0);
    func_00102840(self, D_002724B0);
    MatrixDrive_TurnObjectMatrix(box + 0xE0, D_00271BD0);
    MatrixDrive_TurnObjectMatrix(box + 0xC0, D_00271BD0);
    MatrixDrive_TurnObjectMatrix(box + 0xD0, D_00271BD0);
    GetRootMatrixByDObj(box + 0x100, self);
    MatrixDrive_TurnObjectMatrix((char *)*(int *)((char *)self + 0x15C) + 0x510, D_004BAAC0);
    *(short *)(box + 0x118) = (short)func_002610F0();
    _checkItemBreak(self);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", execFallDown);

extern void GetPureVerticalPlaneOfCurrentPosition(int a0, void *a1, int a2, void *a3, int a4);
extern float func_001669D0(void *a0, void *a1);
extern void func_00240968(void *a0, void *a1, float a2);
extern void MatrixDrive_TurnZObjectMatrixXY(void *a0, void *a1, void *a2);
extern void func_0010E250(void *a0, void *a1, void *a2);
extern void execFallDown(void *a0);

struct vec4_iner { float x, y, z, w; } __attribute__((aligned(8)));

void inertiaMove(void *self) {
    struct vec4_iner m;
    struct vec4_iner v1;
    struct vec4_iner v2;
    char *box = (char *)*(int *)((char *)*(int *)((char *)self + 0x15C) + 0x7F0);
    int cond;
    GetRootMatrixByDObj(&m, self);
    MatrixDrive_TurnObjectMatrix((char *)*(int *)((char *)self + 0x15C) + 0x120, D_00271BD0);
    cond = *(int *)(box + 0x68);
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x49C) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x490) = 0x43D;
    if (cond != 0) {
        float t;
        GetPureVerticalPlaneOfCurrentPosition(0, &v1, 0, box + 0x60, 1);
        t = func_001669D0(&v1, &m);
        *(int *)((char *)&v1 + 0xC) = 0;
        func_00240968(&v2, &v1, -(t - 50.0f));
        MatrixDrive_TurnZObjectMatrixXY(&m, &m, &v2);
    }
    execFallDown(&m);
    func_0010E250(box + 0x70, (char *)*(int *)((char *)self + 0x15C) + 0xC0, &m);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", action);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", GetBoxHoldPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", _checkItemCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", moveBoxAutoMatic);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", MoveBoxWithHoldPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", ReInitBoxGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", func_001BCC88);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", BoxGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", GetBoxMode);

extern void _checkItemCollision(void *a0);
extern void func_00102828(void *a0);
extern void func_001AB9F8(void *a0);

void AlignBox(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    _checkItemCollision(a0);
    func_00102828(a0);
    if (q->f_0++ >= 0x1F) {
        q->f_0 = 0;
        func_001AB9F8(a0);
    }
}

int CanHoldBox(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    return q->f_20;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", BoxDL);

int GetBoxGlobalHoldPoint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    return q->f_20 == 0;
}

extern void func_0010F068(void *a0);
extern void func_0010F048(void *a0);
extern void onPathInitialize(void *a0);
extern void execEff(void *a0, int a1);
extern int D_00271254[];

void IsThisBoxTruck(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    func_0010F068(a0);
    func_0010F048(a0);
    if (q->f_58 != 0)
        onPathInitialize(a0);
    if (D_00271254[0] != 0) {
        BoxGeo2 *q2;
        execEff(a0, 1);
        q2 = *(BoxGeo2 **)((char *)(*(int **)((char *)a0 + 0x15C)) + 0x7F0);
        q2->f_138 = 0;
    }
}

extern void LocalizeDirectionOrient();
extern void func_0023FDD8(int a, int *buf, int c);

void ExecBoxMoveStartReaction(int a0, int a1, int a2)
{
    int buf[16];
    LocalizeDirectionOrient(buf);
    func_0023FDD8(a0, buf, a2);
}

int ExecBoxMoveEndReaction(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    return q->f_58;
}

extern void InitBoxGeo(int a0);
extern void execAutoMove(int a0);

void BoxGeoRestore(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    if (q->f_58 != 0) {
        if (q->f_110 != 0) {
            goto end;
        }
    }
    if (a1 >= 0) {
        InitBoxGeo(a0);
        q->f_114 = 0;
    } else {
        execAutoMove(a0);
        q->f_114 = 0;
    }
end:
    q->f_110 = 1;
}

extern void ExecFrameDependSequence(void *a0);
extern void playSEConditionID(int a0, int a1);
extern void initWheels(int a0);

void BoxExtGeoRestore(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    if (q->f_58 == 0 || q->f_110 != 0) {
        ExecFrameDependSequence(self);
        execEff(self, 1);
        playSEConditionID(self, 0x16);
        if (q->f_140 != 0) {
            initWheels(self);
            q->f_140 = 0;
        }
    }
    q->f_110 = 0;
}

#undef BOX_SWBLK
#define BOX_SWBLK 5
#include "switch.c.inc"
#line 364 "src/box.c"

/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
} S_00288C88;  /* stride 0x28 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004BA770;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00610FF0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611030;  /* stride 0x4 */

/* end struct shapes */

extern void GetRootMatrixByDObj(void *dst, void *src);
extern void func_00240008(void *a0, void *a1, void *a2);
extern float func_0023FE70(void *a0, void *a1);
extern float MatrixDrive_GetTurnYAngleXZ(float a0);

struct vec4_BE1D0 { float x, y, z, w; } __attribute__((aligned(8)));

float BoxMemoryFunc(void *a0, void *a1) {
    struct vec4_BE1D0 buf1;
    struct vec4_BE1D0 buf2;
    GetRootMatrixByDObj(&buf1, a1);
    GetRootMatrixByDObj(&buf2, a0);
    func_00240008(&buf1, &buf1, &buf2);
    return MatrixDrive_GetTurnYAngleXZ(func_0023FE70(&buf1, &buf1));
}

int getAlign(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[0])) { rv = 0; goto end; }
    if (a0[0] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}

int GetDistanceOfGObj(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < -a0[0])) { rv = 0; goto end; }
    if (-a0[0] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}

int moveXPlus(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[0];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[2])) { rv = 0; goto end; }
    if (a0[2] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}

int moveXMinus(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[0];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < -a0[2])) { rv = 0; goto end; }
    if (-a0[2] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}

