#include "common.h"

/* switch__1BDB18 0x7F0 view (local) */
typedef struct { char _0[2]; short f_2; int f_4; char _pad8[0x14]; int f_1C; } WLGeo;

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
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    q->f_1C = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", CanWallLeverPull);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", IsWallLeverStatus);

int InitWallLeverGeo(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    return q->f_4 == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", GetWallLeverAngle);

int initParentize(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    return q->f_2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BDE70);

int func_001BDF68(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    return q->f_4 == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BDF80);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BDFC8);

int func_001BE0D8(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    return q->f_2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BE0E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/switch__1BDB18", func_001BE168);
