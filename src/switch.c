#include "common.h"


extern void func_001BC0A8();
INCLUDE_ASM("asm/nonmatchings/src/switch", SetSwitchTriggerFunc);

int SetSwitchState(void) { return 1; }

int SetFloorLeverWithNodePoint(void) { return 1; }

int CanFloorLeverPull(void) { return 0; }

void InitFloorLeverGeo(void) {}

void GetFloorLeverAngle(void) {}

INCLUDE_ASM("asm/nonmatchings/src/switch", SetWallLeverWithNodePoint);

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

INCLUDE_ASM("asm/nonmatchings/src/switch", InitWallLeverGeo);

INCLUDE_ASM("asm/nonmatchings/src/switch", GetWallLeverAngle);

INCLUDE_ASM("asm/nonmatchings/src/switch", initParentize);

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

