/* switch.c — interactable lever/switch module, #included by box.c into one box.o
 * (dev unity; the shipped build trace-reorders the merged functions). */
INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", switchOnSE);

extern int *actInitialize(int *self);
extern void actInitialize_ext_charcter(int *self);
extern void _ACTWait(int x);

void switchReleaseSE(int *self)
{
    int *p = actInitialize(self);
    long long v;
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    v = *(long long *)((char *)p + 0x18);
    v |= 1LL << 32;
    *(long long *)((char *)p + 0x18) = v;
}

float GetFloorLeverGlobalHoldPoint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x830);
    return *(float *)((char *)q + 0x20);
}

/* switch__1B95C0 0x7F0 view (local) */
typedef struct { char _0[8]; int f_8; } SwGeo;

void FloorLeverTriStateGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    SwGeo *q = *(SwGeo **)((char *)p + 0x7F0);
    q->f_8 = a1;
}

extern void playSEConditionID(int a0, int a1);

void FloorLeverGeo(int a0) {
    playSEConditionID(a0, 0x3D);
}

void FloorLeverDL(int a0) {
    playSEConditionID(a0, 0x3E);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", GetWallLeverGlobalHoldPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", WallLeverGeo);

extern void playSEConditionID(int a0, int a1);

void WallLeverDL(int a0) {
    playSEConditionID(a0, 0x2);
}

void CheckReadyAllSwitches(int a0) {
    playSEConditionID(a0, 0x24);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", InitSwitchGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", SwitchGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", SwitchDL);

/* switch__1BDB18 0x7F0 view (local) */
typedef struct { char _0[2]; short f_2; int f_4; char _pad8[0x14]; int f_1C; } WLGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", SetSwitchTriggerFunc);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", CanWallLeverPull);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", IsWallLeverStatus);

int InitWallLeverGeo(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    return q->f_4 == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", GetWallLeverAngle);

int initParentize(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    return q->f_2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", func_001BDE70);

int func_001BDF68(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    return q->f_4 == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", func_001BDF80);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", func_001BDFC8);

int func_001BE0D8(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x7F0);
    return q->f_2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", func_001BE0E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", func_001BE168);
