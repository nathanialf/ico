#include "common.h"


extern void func_001BC0A8();
INCLUDE_ASM("asm/nonmatchings/src/switch", SetSwitchTriggerFunc);

int SetSwitchState(void) { return 1; }

int SetFloorLeverWithNodePoint(void) { return 1; }

int CanFloorLeverPull(void) { return 0; }

void InitFloorLeverGeo(void) {}

void GetFloorLeverAngle(void) {}

typedef struct { char _0[2]; short f_2; int f_4; char _pad8[0x14]; int f_1C; } WLGeo;

void SetWallLeverWithNodePoint(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x800);
    q->f_1C = a1;
}

void CanWallLeverPull(char *self, int a1)
{
    int *sub = *(int **)((char *)self + 0x15C);
    int *p = *(int **)((char *)sub + 0x800);
    int cur = p[1];
    unsigned char ne;
    int tmp;
    tmp = cur;
    ne = tmp != a1;
    p++;
    p--;
    if (ne) { func_001BC0A8(); p[1] = a1; }
    else { p[1] = a1; }
}

INCLUDE_ASM("asm/nonmatchings/src/switch", IsWallLeverStatus);

int InitWallLeverGeo(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x800);
    return q->f_4 == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", GetWallLeverAngle);

int initParentize(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x800);
    return q->f_2;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0AE8);

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0BE0);

int func_001C0BF8(char *self)
{
    short *p = (short *)*(int *)(*(int *)(self + 0x15C) + 0x800);
    int ret = 0;
    if (__builtin_abs(p[1]) < 0xBB9)
    {
        if (__builtin_abs(p[0]) < 0xBB9)
        {
            goto end;
        }
    }
    ret = 1;
end:
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0C40);

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0D50);

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0D60);

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0DE0);

INCLUDE_ASM("asm/nonmatchings/src/switch", BoxMemoryFunc);

INCLUDE_ASM("asm/nonmatchings/src/switch", getAlign);

INCLUDE_ASM("asm/nonmatchings/src/switch", GetDistanceOfGObj);

INCLUDE_ASM("asm/nonmatchings/src/switch", moveXPlus);

INCLUDE_ASM("asm/nonmatchings/src/switch", moveXMinus);

