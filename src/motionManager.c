#include "common.h"



extern int D_00633438;
extern int D_0063343C;
extern int D_0063347C;
extern int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6);
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern int D_00633F3C;
INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispSquare2);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", findActPoint);

extern void ClipWallBoxStop(void *a0);
extern char D_004C5B60[];
extern char D_004C5B70[];
extern int D_00633F40;
extern float MatrixDrive_GetTurnZAngleYX(void *a0, void *a1);
extern int func_00104F20(void);
extern void func_00105268(void);
extern int func_00105278(void);
extern void func_001052A8(void *a0);
extern void func_002438B8(int *a0, int a1, char *a2);
extern void func_002641D8(void *a0, int a1, int a2);

void checkActPointWithHeight(void) {
    char buf[0xC0];
    func_002641D8(buf, 0, 0xC0);
    func_00104F20();
    func_001052A8(D_004C5B60);
    MatrixDrive_TurnObjectMatrix((void *)buf, (void *)(func_00105278() + 0x30));
    func_002438B8((int *)(buf + 0x10), func_00105278(), D_004C5B70);
    func_00105268();
    ClipWallBoxStop(buf);
    if (*(int *)(buf + 0x88) != 0) {
        float a;
        int *D;
        a = MatrixDrive_GetTurnZAngleYX(buf + 0x20, buf);
        D = (int *)D_00633F40;
        *(float *)((char *)D + 0x170) = a;
        *(int *)((char *)D + 0x108) = 1;
        *(int *)((char *)D + 0x14) = *(int *)((char *)D + 0x14) | 0x1000;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager", clearCollisionStatus);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkUpperWallState);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkWallSideState);

/* motionManager .rodata run 0x619220..0x619620 -- byte-verified against
 * baseelf; defs interleave with INCLUDE_ASM stubs so .o section order ==
 * VMA order */
const unsigned int D_00619220[0x30] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x42480000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
const char D_006192E0[0x18] = "src/motionManager.c\0\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkWallState);

const char D_00619328[0x78] = "PLANE¥ê¥ß¥Ã¥È¤Ç¤¹ %f µÞ¤Ê¤Î¤ÇÍî²¼¤µ¤»¤Þ¤¹\n\0\0\0\0\0\0¤³¤Î¥á¥Ã¥»¡¼¥¸¤ò¸«¤¿¿Í¤ÏÄ¾¤Á¤Ë¤¹¤®¤ä¤Þ¤ËÊó¹ð¤·¤Æ¤¯¤ì¡¼:NOWALLHITPROC\n\0\0\0";
const char D_006193A0[0x18] = "ÊÉ¤Î³ÑÅÙ¤¬µÞ¤Ê¤Î¤ÇÍî²¼\n\0";
const char D_006193B8[0x18] = "ÊÉÂ°À­¤Ë¤è¤êÍî²¼\n\0\0\0\0\0\0\0";
const char D_006193D0[0x10] = "ÊÉ¤¬¤Ê¤¯¤ÆÍî²¼\n\0";
const char D_006193E0[0x28] = "ÊÉ¤Î¤Ä¤«¤Þ¤êÀè¤¬¤Ê¤¯¤ÆÍî²¼ (ÃÊº¹:%f)\n\0\0\0";
const char D_00619408[0x20] = "¶¯À©Íî²¼¤ÎÊÉ¤ËÅö¤¿¤Ã¤¿¤Î¤ÇÍî²¼\n\0";
const char D_00619428[0x60] = "²¼¤ËDWATER¤Î¿åÄì¤¬¤Ê¤¤¤Ç¤¹¡£¤³¤Î¥á¥Ã¥»¡¼¥¸¤¬Ï¢Â³¤Ç\n½Ð¤Æ¤ë¤Ê¤é¡¢±Ë¤®¤«¤éÁ«°Ü¤·¤Æ¤¤¤Ê¤¤¾õÂÖ¤Ç¤¹\n\n\0";
const unsigned int D_00619488[0x4] = { 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000 };
const char D_00619498[0x18] = "³ÈÄ¥ÊÉ¤ËÅö¤¿¤Ã¤¿\n\0\0\0\0\0\0\0";

extern void checkWallState(void);
extern void clearCollisionStatus(void);
extern void func_00105308(float, float, float);
extern void func_0010DF70(char *p);
extern void func_00118678(int a0);
extern float func_00168C18(int a0, int a1);

void checkCliffState(void)
{
    func_00118678(func_00105278());
    {
        register float *p = (float *)D_00633F3C;
        float r = func_00168C18(D_00633F3C + 0x130, D_00633F3C);
        func_00105308(p[0], r, *(float *)(D_00633F3C + 8));
    }
    func_0010DF70((char *)D_00633F3C + 0x30);
    func_00104F20();
    checkWallState();
    func_00105268();
    if (*(int *)(D_00633F40 + 0xE4) != 0) {
        func_00104F20();
        clearCollisionStatus();
        func_00105268();
    }
}

extern void checkWallState(void);
extern void func_00105308(float, float, float);
extern void func_0010DF70(char *p);
extern void func_00118678(int a0);

void _checkCliffAndWall(void)
{
    func_00118678(func_00105278());
    {
        register float *p = (float *)D_00633F3C;
        func_00105308(p[0], p[1] + p[116] + 10.0f, p[2]);
    }
    func_0010DF70((char *)D_00633F3C + 0x30);
    checkWallState();
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkCliffAndWallStateOfLastPlane);

extern void InitMotionMemorySize(int);
extern void func_00243BD8(int);
extern void func_001050B0(float, float, float);
extern void func_0010F630();
extern void gif_SpriteOffset();
extern void gsb_SetFrame();

void checkCliffAndWallStateAtJump(void)
{
    register float *p;
    int v;
    gif_SpriteOffset(0xB);
    gsb_SetFrame(1, 5, 0x80);
    func_00104F20();
    v = func_00105278();
    func_00243BD8(v);
    p = (float *)D_00633F3C;
    func_00105308(p[108], p[109], p[110]);
    func_001050B0(8.0f, 8.0f, 8.0f);
    InitMotionMemorySize(0xFF);
    func_00105268();
    func_0010F630();
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispActNode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispLastNode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", _getGeometryOfMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", execPositionReserver);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetGeometryOfMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetMatrixOfMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DB000);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", getInitialMatrix);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispSkelton);

extern int D_00633F3C;
extern char D_004C5BD0[];
extern void ClipWallCheckCB(void *a0);
extern void ClipWallBoxStop(void *a0);
extern int fzMagnitudeByLine(void *a0);
extern int dispSkelton(int a0, int a1, int a2);
extern void func_002438B8(int *a0, int a1, char *a2);
extern void func_00118648(void *a0, int a1, char *a2);
extern void _RotTransPersCurrentMatrix(int a0, int a1, void *a2);

int SkelTest(int a0, int a1, int p, int a3, int a4) {
    char buf[0x10];
    int flag;
    int mag;
    int mask;

    *(int *)(p + 0x70) = 0;
    MatrixDrive_TurnObjectMatrix((void *)p, (void *)a3);
    func_002438B8((int *)(p + 0x10), a1, (char *)a0);
    ClipWallBoxStop((void *)p);

    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    if (*(int *)(D_00633F3C + 0x324) != 0) {
        ClipWallCheckCB((void *)p);
        if (*(int *)(p + 0x88) != 0) {
            flag = 0;
            mag = fzMagnitudeByLine((void *)p);
            switch (*(int *)(D_00633F3C + 0x324)) {
            default:
            case 1:
                mask = 0x20000000;
                break;
            case 2:
                mask = 0x10000000;
                break;
            }
            if (mag & mask) {
                flag = 1;
                if (mag & 0x0FFFFFFF) {
                    return -1;
                }
            }
            if (flag != 0) {
                return dispSkelton(p, 0, a4);
            }
            goto block12;
        }
    }
block12:
    func_00118648(buf, a1, D_004C5BD0);
    MatrixDrive_TurnObjectMatrix((void *)p, (void *)(p + 0x10));
    _RotTransPersCurrentMatrix(p + 0x10, p, buf);
    ClipWallBoxStop((void *)p);
    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    MatrixDrive_TurnObjectMatrix((void *)p, (void *)(p + 0x10));
    MatrixDrive_TurnObjectMatrix((void *)(p + 0x10), (void *)(a3 + 0x10));
    ClipWallBoxStop((void *)p);
    if (*(int *)(p + 0x88) != 0) {
disp_one:
        return dispSkelton(p, 1, a4);
    }
    return 0;
}

void SkelTestGeo(void)
{
    iosOmBeforeFuncStandard(D_0063347C, 0x18, D_0063347C);
    MatrixDrive_TurnObjectMatrix(D_00633F3C + 0x150, D_00633F3C);
}

void SetHitCollisionDisplay(void)
{
    iosOmBeforeFuncStandard(D_0063347C, 0xF3, D_0063347C);
    MatrixDrive_TurnObjectMatrix(D_00633F3C + 0x150, D_00633F3C);
}

extern float D_007097C4[];
extern void func_00105308(float, float, float);
extern void func_0010DF70(char *p);

void GetWallVector(void)
{
    int v;
    func_00104F20();
    v = func_00105278();
    func_00243BD8(v);
    {
        register float *p = (float *)D_00633F3C;
        func_00105308(p[0], p[1] - D_007097C4[0], p[2]);
    }
    func_0010DF70((char *)D_00633F3C + 0x30);
    checkActPointWithHeight();
    func_00105268();
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager", getGeometryOfMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DCAC8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DD1F0);

extern char D_004C5C40[];
extern char D_004C5C50[];
extern float D_00631358;
extern void ClipFloorR(void *a0);
extern void func_0010DEC0(void *a0, void *a1, void *a2);
extern void _PushVu0Registers(void *a0, void *a1, float f);
extern void _TransposeRotationCurrentMatrix(void *a0, void *a1, void *a2);

/* Move the player position onto the floor point the clip box reported:
   v = plane point + plane normal * 40; v = (v - pos) * D_00631358; pos += v. */
static inline void pullToFloor(char *buf)
{
    float v[4];
    _PushVu0Registers(v, buf + 0xA0, 40.0f);
    _RotTransPersCurrentMatrix((int)v, (int)(buf + 0x20), v);
    _TransposeRotationCurrentMatrix(v, v, (void *)D_00633F3C);
    _PushVu0Registers(v, v, D_00631358);
    _RotTransPersCurrentMatrix(D_00633F3C, D_00633F3C, v);
}

/* Run the floor clip and report the hit, gated by the enable flag. */
static inline int clipFloor(char *buf, int enable)
{
    ClipFloorR(buf);
    return *(int *)(buf + 0x88) && enable;
}

int func_001DD668(void)
{
    char m[0x40];
    char buf[0xD0];
    int enable = 1;

    func_002641D8(buf, 0, 0xC0);
    func_0010DEC0(m, (char *)D_00633F3C + 0x30, (void *)D_00633F3C);
    func_00118648(buf, (int)m, D_004C5C40);
    func_00118648(buf + 0x10, (int)m, D_004C5C50);
    if (clipFloor(buf, enable) == 0) {
        /* nothing under the first plane pair - retry with them swapped */
        func_00118648(buf, (int)m, D_004C5C50);
        func_00118648(buf + 0x10, (int)m, D_004C5C40);
        if (clipFloor(buf, enable) == 0) return 0;
    }
    pullToFloor(buf);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DD7A8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE250);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE338);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE428);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE588);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE6B8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE8D0);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DED10);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DEF20);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DF150);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DF368);

const unsigned int D_00619588[0x4] = { 0x00000000, 0x40A00000, 0x00000000, 0x00000000 };
const unsigned int D_00619598[0x4] = { 0x00000000, 0x00000000, 0x40A00000, 0x00000000 };
const unsigned int D_006195A8[0x6] = { 0x40A00000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
const unsigned int D_006195C0[0x4] = { 0x00000040, 0x00000040, 0x00000040, 0x00000080 };
const unsigned int D_006195D0[0x4] = { 0x00000000, 0x000000FF, 0x00000000, 0x00000080 };
const unsigned int D_006195E0[0x4] = { 0x00000000, 0x00000080, 0x000000FF, 0x00000080 };
const unsigned int D_006195F0[0x4] = { 0x000000FF, 0x00000000, 0x00000000, 0x00000080 };
const unsigned int D_00619600[0x4] = { 0x41200000, 0x00000000, 0x00000000, 0x00000000 };
const unsigned int D_00619610[0x4] = { 0x000000FF, 0x000000FF, 0x000000FF, 0x00000080 };

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DF8C0);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DFBC8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E00F8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E0438);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E0708);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E0808);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E0860);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E08B8);

void func_001E0978(int a, int b) {
    D_00633438 = a;
    D_0063343C = b;
}

/* .data â€” carved VMA 0x4C5AA0..0x4C5AE0 (4 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_004C5AA0[4] = {
    0xC0400000, 0x00000000, 0xC0400000, 0x00000000,
};
unsigned int D_004C5AB0[4] = {
    0x40400000, 0x00000000, 0x40400000, 0x00000000,
};
unsigned int D_004C5AC0[4] = {
    0xC0400000, 0x00000000, 0x40400000, 0x00000000,
};
unsigned int D_004C5AD0[4] = {
    0x40400000, 0x00000000, 0xC0400000, 0x00000000,
};

/* .sdata â€” carved VMA 0x63345C..0x633478 (5 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_0063345C = 0x7F7FFFFF;
unsigned int D_00633460 = 0x00000065;
unsigned int D_00633464 = 0x7F7FFFFF;
unsigned int D_00633468[2] = {
    0x7F7FFFFF, 0x00000000,
};
unsigned int D_00633470[2] = {
    0x00000000, 0xFFFFFFFF,
};

