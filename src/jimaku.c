#include "common.h"

typedef struct { char _0[0x3A4]; int f_3A4; } JSub678;
typedef struct { char _0[0x30]; int f_30; char _pad34[0x308]; int f_33C; char _pad340[0x338]; JSub678 *p_678; } JimakuState;










extern int D_00274EE8[];
extern int D_0028A4A0[];
extern int iosMsgSend(int *self, int a1, int a2);
extern char D_006CF030[];
extern char D_006CEFC0[];
extern int func_0013DA88(int *self);
extern void iosCdvdBackGroundMgrEntryNum(char *self);
extern char D_006CEFF8[];
extern void func_00132B90();
extern void func_00133500(char *self, int val);
extern int D_00631AE4;
extern char D_00559AE8[];
extern char D_005598F0[];
extern void ACTWay_SetBeginPositionIllegal(char *self);
extern void debug_assertMessage();
extern void Vibration_ShotDecode(int key);
extern void ACTLookTargetSystem_Exec(void);
extern void _ACTWait();
extern void *D_00631AE8;
INCLUDE_ASM("asm/nonmatchings/src/jimaku", display_texture);

INCLUDE_ASM("asm/nonmatchings/src/jimaku", iosCdvdBackGroundReadJimaku);

extern void BoxBarSoundOn(int a0, int a1);
extern void _ACTWait(int a0);
extern void debug_assertMessage(void *a0);
extern void func_00243B18(float *a0, float *a1, float f12);

void func_00175980(volatile int a0) {
    for (;;) {
        BoxBarSoundOn(a0, 0x13E);
        _ACTWait(1);
    }
}

extern char D_00559458[], D_00559470[];
extern void BoxBarSoundOn(int a0, int a1);
extern void CylinderCollision(void *a0, void *a1);
extern int dispPlane(void *a0, void *a1);
extern void func_00175A58(volatile int a0);

void func_001759B0(volatile int a0) {
    float buf[4];
    int *gobj = *(int **)(a0 + 0x164);
    debug_assertMessage(D_00559458);
    func_00243B18(buf, (float *)&gobj[0x4A0 / 4], -1.0f);
    dispPlane((void *)a0, buf);
    CylinderCollision((void *)a0, &gobj[0x580 / 4]);
    gobj[0xD0 / 4] = 0;
    gobj[0x14 / 4] = (int)func_00175A58;
    while ((gobj[0xD0 / 4] & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_assertMessage(D_00559470);
    for (;;) {
        BoxBarSoundOn(a0, 0x59);
        _ACTWait(1);
    }
}

extern char D_00559440[];
extern int D_006321DC;
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);

void func_00175A58(volatile int a0) {
    debug_assertMessage(D_00559440);
    iosOmBeforeFuncStandard(D_00631AE4, 0x59, D_006321DC);
    ACTLookTargetSystem_Exec();
}

extern void BoxBarSoundOn(int a0, int a1);
extern char D_00553790[], D_00559470[];
extern char D_005594A0[];
extern void func_00175B18(volatile int a0);

void jimakuHandler(volatile int a0) {
    int *gobj = *(int **)(a0 + 0x164);
    debug_assertMessage(D_005594A0);
    gobj[0x30 / 4] = 0x50;
    gobj[0x14 / 4] = (int)func_00175B18;
    gobj[0xD0 / 4] = 0;
    while ((gobj[0xD0 / 4] & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_assertMessage(D_00559470);
    for (;;) {
        BoxBarSoundOn(a0, 0x5E);
        _ACTWait(1);
    }
}

extern char D_00559440[];
extern int D_006321DC;
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);

void func_00175B18(volatile int a0) {
    debug_assertMessage(D_00559440);
    iosOmBeforeFuncStandard(D_00631AE4, 0x5E, D_006321DC);
    ACTLookTargetSystem_Exec();
}

INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuMgrBegin);

void func_00175BD8(volatile int a0) {
    debug_assertMessage(D_00559440);
    iosOmBeforeFuncStandard(D_00631AE4, 0x63, D_006321DC);
    ACTLookTargetSystem_Exec();
}

INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuMgrNext);

void jimakuMgrJump(int x) {
    char *p = (char *)D_00631AE8;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        char *q = *(char **)(sub + 0x678);
        *(int *)(q + 0x3C0) = x;
    }
}

void jimakuMgrEnd(void) {
    char *p = (char *)D_00631AE8;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        char *q = *(char **)(sub + 0x678);
        *(int *)(q + 0x3C0) = 0;
    }
}

void jimakuBegin(int a0)
{
    volatile int local = a0;
    int v0 = local;
    int v1 = *(int *)(v0 + 0x164);
    *(int *)(v1 + 0x33C) = 0;
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuNext);

void func_00175D90(volatile int a0) {
    JimakuState *p = *(JimakuState **)(a0 + 0x164);
    p->f_33C = 0;
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuJump);

extern int D_006ABE00[];
extern void ACTGame_GirlBeforeFunc(int a0);
extern void DebugDispAutoEscort(int a0);
extern void actGirlSupportGBBegin(int a0);

void func_00175EC8(volatile int a0) {
    switch (D_006ABE00[0]) {
    case 1:
        DebugDispAutoEscort(a0);
        break;
    case 2:
        ACTGame_GirlBeforeFunc(a0);
        break;
    case 3:
        actGirlSupportGBBegin(a0);
        break;
    }
    _ACTWait(0);
}

int jimakuEnd(int a0, int a1)
{
    float diff = *(float *)(a0 + 0x20) - *(float *)(a1 + 0x20);
    return (int)diff;
}

INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuDisp);

void jimakuManager(unsigned int a0)
{
  volatile unsigned int local = a0;
 do { ACTLookTargetSystem_Exec(); debug_assertMessage(D_005598F0); Vibration_ShotDecode(7); ACTWay_SetBeginPositionIllegal(local); } while (0);
}

void jimakuUndisp(void *a0) {
    void *volatile q = a0;
    int *p = *(int **)((char *)q + 0x15C);
    *(int *)((char *)p + 0x634) = 0;
}

void func_00176150(volatile unsigned int a0)
{
  int *new_var;
  int *s0;
  new_var = *((int **) (a0 + 0x164));
  debug_assertMessage(D_00559AE8);
  s0 = new_var;
  s0[0x30 / 4] = 0x4;
  _ACTWait(0);
}

void func_00176198(unsigned int a0)
{
    volatile unsigned int local = a0;
    ACTLookTargetSystem_Exec();
}

int func_001761B8(int a0, int a1)
{
    int p = D_00631AE4;
    int q = D_00631AE8;
    if ((a0 == p && a1 == q) || (a0 == q && a1 == p)) {
        int *obj = *(int **)(q + 0x164);
        if (*(int *)((int)obj + 0x30) == 0x4E)
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_00176200);

void func_00176398(int self, int a1, int size)
{
    int large = size + 0x7FE;
    int v1 = size - 1;
    int neg_one = -1;
    if (neg_one < v1) large = v1;
    large = ((large >> 11) + 1) << 11;
    func_00132B90(self, a1, large);
    func_00133500(self, *(int *)((char *)self + 0x110) + size);
}

INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_001763F8);

INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_00176600);

INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_00176808);

INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_001769D0);

void func_00176AA0(int *p)
{
    int val = p[0x4C / 4];
    if (val != 0) {
        iosCdvdBackGroundMgrEntryNum(val);
    }
    func_0013DA88(D_006CF030);
    func_0013DA88(D_006CEFF8);
    func_0013DA88(D_006CEFC0);
}

void func_00176AE8(int a0)
{
    *(int *)a0 = 0;
    iosMsgSend(D_0028A4A0, a0, 1);
}

void func_00176B08(int *p) {
    if (D_00274EE8[0] != 0) {
        *p = 1;
        iosMsgSend(D_0028A4A0, p, 0);
    }
}

