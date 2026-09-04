#include "common.h"



extern void GetRootMatrix();
extern void sceVu0ApplyMatrix();
#include "ico/types.h"

typedef struct { int f_0; char _4[0x1C]; int f_20; char _pad24[0x34]; int f_58; char _pad5C[0xB4]; int f_110; int f_114; char _pad118[0x20]; int f_138; char _pad13C[0x4]; int f_140; } BoxGeo2;
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD408);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD668);

INCLUDE_ASM("asm/nonmatchings/src/box", getNearestPosition);

/* box .rodata run 0x6186A0..0x618808 -- byte-verified against baseelf;
 * defs interleave with INCLUDE_ASM stubs so .o section order == VMA order.
 * (box.c is trace-reordered for .text via INCLUDE_ASM_FS, but these 5
 * functions/defs are already in VMA order in the .c source, so plain
 * interleaving still holds for .rodata here.) */
const char D_006186A0[0x10] = "src/box.c";
INCLUDE_ASM("asm/nonmatchings/src/box", playAnimationCore);

INCLUDE_ASM("asm/nonmatchings/src/box", MoveFloatingBox);

INCLUDE_ASM("asm/nonmatchings/src/box", avoidCharGObj);

INCLUDE_ASM("asm/nonmatchings/src/box", execFloating);

INCLUDE_ASM("asm/nonmatchings/src/box", initFloating);

INCLUDE_ASM("asm/nonmatchings/src/box", _checkItemBreak);

extern int D_00275850[];
extern int D_00276140[];
extern int D_004BF7C0[];
extern void GetInverseQuaternion(void *a0, void *a1);
extern void GetRootPosition(void *a0, void *a1);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void _checkItemBreak(void *a0);
extern void func_00102870(void *self, void *src);
extern int rand(void);

void initLanding(void *self) {
    char *d = (char *)*(int *)((char *)self + 0x15C);
    char *box = (char *)*(int *)(d + 0x800);
    *(int *)(d + 0x70) = *(int *)((char *)*(int *)(box + 0x160) + 0x70);
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x78) = 1;
    GetInverseQuaternion((char *)*(int *)((char *)self + 0x15C) + 0xC0, D_00276140);
    func_00102870(self, D_00276140);
    MatrixDrive_TurnObjectMatrix(box + 0xE0, D_00275850);
    MatrixDrive_TurnObjectMatrix(box + 0xC0, D_00275850);
    MatrixDrive_TurnObjectMatrix(box + 0xD0, D_00275850);
    GetRootPosition(box + 0x100, self);
    MatrixDrive_TurnObjectMatrix((char *)*(int *)((char *)self + 0x15C) + 0x520, D_004BF7C0);
    *(short *)(box + 0x118) = (short)rand();
    _checkItemBreak(self);
}

INCLUDE_ASM("asm/nonmatchings/src/box", execFallDown);

extern void GetPureVerticalPlaneOfCurrentPosition(int a0, void *a1, int a2, void *a3, int a4);
extern void AddVectorXYZ(void *a0, void *a1, void *a2);
extern void execFallDown(void *a0);
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
extern float GetDistanceFromPlane(void *a0, void *a1);
extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);

struct vec4_iner { float x, y, z, w; } __attribute__((aligned(8)));

void inertiaMove(void *self) {
    struct vec4_iner m;
    struct vec4_iner v1;
    struct vec4_iner v2;
    char *box = (char *)*(int *)((char *)*(int *)((char *)self + 0x15C) + 0x800);
    int cond;
    GetRootPosition(&m, self);
    MatrixDrive_TurnObjectMatrix((char *)*(int *)((char *)self + 0x15C) + 0x130, D_00275850);
    cond = *(int *)(box + 0x68);
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x4AC) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x4A0) = 0x43B;
    if (cond != 0) {
        float t;
        GetPureVerticalPlaneOfCurrentPosition(0, &v1, 0, box + 0x60, 1);
        t = GetDistanceFromPlane(&v1, &m);
        *(int *)((char *)&v1 + 0xC) = 0;
        sceVu0ScaleVectorXYZ(&v2, &v1, -(t - 50.0f));
        AddVectorXYZ(&m, &m, &v2);
    }
    execFallDown(&m);
    GetMatrixFromQuaternionPos(box + 0x70, (char *)*(int *)((char *)self + 0x15C) + 0xC0, &m);
}

INCLUDE_ASM("asm/nonmatchings/src/box", action);

INCLUDE_ASM("asm/nonmatchings/src/box", GetBoxHoldPoint);

INCLUDE_ASM("asm/nonmatchings/src/box", _checkItemCollision);

INCLUDE_ASM("asm/nonmatchings/src/box", moveBoxAutoMatic);

INCLUDE_ASM("asm/nonmatchings/src/box", MoveBoxWithHoldPoint);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF7F8);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF918);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BFFE8);

const char D_00618770[0x78] = "\033[36mÈ¢¤¬ÃÏÌÌ¤ÎÌµ¤¤¤È¤³¤í¤Ë½é´üÇÛÃÖ¤µ¤ì¤Æ¤¤¤Þ¤¹¡£\nÆ°ºî¤¬ÊÝ¾Ú¤Ç¤­¤Þ¤»¤ó(¥³¥ê¥¸¥ç¥óÄêµÁ¤è¤êÁ°¤ËÈ¢¤¬¤¢¤ê¤Þ¤»¤ó¤«?)\033[m\n\0\0\0\0\0";
const char D_006187E8[0x10] = "È¢½é´ü¿åÄìÇÛÃÖ\n\0";
const char D_006187F8[0x10] = "È¢½é´üÄÌ¾ïÇÛÃÖ\n\0";

INCLUDE_ASM("asm/nonmatchings/src/box", func_001C00C0);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001C0538);

int func_001C05A8(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(int *)(p + 0x20);
}

int func_001C05B8(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(int *)(p + 0x20) == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/box", func_001C05D0);

void GetBoxGlobalHoldPoint(int a0, int a1, int a2)
{
    int buf[16];
    GetRootMatrix(buf);
    sceVu0ApplyMatrix(a0, buf, a2);
}

int ExecBoxMoveEndReaction(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x800);
    return q->f_58;
}

extern void pushStartSE(int a0);
extern void pullStartSE(int a0);

void BoxGeoRestore(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x800);
    if (q->f_58 != 0) {
        if (q->f_110 != 0) {
            goto end;
        }
    }
    if (a1 >= 0) {
        pushStartSE(a0);
        q->f_114 = 0;
    } else {
        pullStartSE(a0);
        q->f_114 = 0;
    }
end:
    q->f_110 = 1;
}

extern void ExecFrameDependSequence(void *a0);
extern void StopSEPackageWithGroupVariation(void *a0, int a1);
extern void wallHitSE(int a0);
extern void ExecuteSEPackage(int a0, int a1);

void BoxExtGeoRestore(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x800);
    if (q->f_58 == 0 || q->f_110 != 0) {
        ExecFrameDependSequence(self);
        StopSEPackageWithGroupVariation(self, 1);
        ExecuteSEPackage(self, 0x16);
        if (q->f_140 != 0) {
            wallHitSE(self);
            q->f_140 = 0;
        }
    }
    q->f_110 = 0;
}


/* .data â€” carved VMA 0X4BF460..0X4BF7C0 (10 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_004BF460[32] = {
    0x00000000, 0x004BEFF0, 0x004BF070, 0x004BF0C0,
    0x004BF0F0, 0x004BF120, 0x004BF150, 0x004BF180,
    0x004BF1E0, 0x004BF210, 0x004BF220, 0x004BF250,
    0x004BF280, 0x004BF2B0, 0x004BF2E0, 0x004BF310,
    0x004BF340, 0x004BF370, 0x004BF3A0, 0x004BF3B0,
    0x004BF3C0, 0x004BF3D0, 0x004BF3E0, 0x004BF3F0,
    0x004BF400, 0x004BF410, 0x004BF420, 0x004BF430,
    0x004BF440, 0x004BF450, 0x00000000, 0x00000000,
};
unsigned int D_004BF4E0[16] = {
    0x00000000, 0x00000000, 0x42480000, 0x3F800000,
    0x42480000, 0x00000000, 0x00000000, 0x3F800000,
    0x00000000, 0x00000000, 0xC2480000, 0x3F800000,
    0xC2480000, 0x00000000, 0x00000000, 0x3F800000,
};
unsigned int D_004BF520[16] = {
    0x00000000, 0x00000000, 0x41200000, 0x3F800000,
    0x41200000, 0x00000000, 0x00000000, 0x3F800000,
    0x00000000, 0x00000000, 0xC1200000, 0x3F800000,
    0xC1200000, 0x00000000, 0x00000000, 0x3F800000,
};
unsigned int D_004BF560[100] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x3F800000,
    0x00000000, 0x3F800000, 0x3F800000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000002, 0x00000001, 0x00000000, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x3F800000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x41200000, 0x41F00000, 0x42480000,
    0xC2480000, 0x3F666666, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x3F800000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x3F800000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004BF6F0[4] = {
    0x00000000, 0x3F800000, 0x00000000, 0x00000000,
};
unsigned int D_004BF700[4] = {
    0x00000000, 0x00000080, 0x000000FF, 0x00000080,
};
unsigned int D_004BF710[4] = {
    0x000000FF, 0x00000080, 0x00000000, 0x00000080,
};
unsigned int D_004BF720[4] = {
    0x00000000, 0x00000000, 0x3F800000, 0x00000000,
};
unsigned int D_004BF730[32] = {
    0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    0x00000000, 0x00000000, 0xBF800000, 0x3F800000,
    0x3F800000, 0x00000000, 0x00000000, 0x3F800000,
    0xBF800000, 0x00000000, 0x00000000, 0x3F800000,
    0xBF800000, 0x00000000, 0xBF800000, 0x3F800000,
    0x3F800000, 0x00000000, 0xBF800000, 0x3F800000,
    0x3F800000, 0x00000000, 0x3F800000, 0x3F800000,
    0xBF800000, 0x00000000, 0x3F800000, 0x3F800000,
};
unsigned int D_004BF7B0[4] = {
    0x00000000, 0x3F800000, 0x00000000, 0x00000000,
};
