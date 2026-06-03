#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", SetSwitchTriggerFunc);

int SetSwitchState(void) {
    return 1;
}

int SetFloorLeverWithNodePoint(void) {
    return 1;
}

int CanFloorLeverPull(void) {
    return 0;
}

void InitFloorLeverGeo(void) {
}

void GetFloorLeverAngle(void) {
}

void SetWallLeverWithNodePoint(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[7] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", CanWallLeverPull);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", IsWallLeverStatus);

int InitWallLeverGeo(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[1] == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", GetWallLeverAngle);

int initParentize(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    return *(short *)((char *)q + 0x2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BDE70);

int func_001BDF68(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[1] == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BDF80);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BDFC8);

int func_001BE0D8(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    return *(short *)((char *)q + 0x2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BE0E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BE168);
