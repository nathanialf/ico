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

extern int DebugDisp1CollisionWithColor(void *a0, int a1);
extern void GetRootMatrixByDObj(float *dst, void *a0);
extern void func_00243AE8(float *dst, void *src, float *mat);
extern void *func_00105278(void);
extern void LocalizeDirectionOrient(void *a0, void *a1);
extern void MatrixDrive_TransMatrix(void *a0, void *a1);
extern void func_002438B8(float *a0, void *a1, float *a2);
extern void MatrixDrive_PushMatrixWithNoCopy(void *a0, void *a1, float x, float y, float z);

void IsWallLeverStatus(void *a0, void *a1, int a2) {
    float buf[4];
    float mat[4];
    WLGeo *q;
    int idx;
    void *t;

    q = *(WLGeo **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    idx = DebugDisp1CollisionWithColor(a1, a2);
    GetRootMatrixByDObj(mat, a0);
    func_00243AE8(buf, (char *)*(int *)(*(int *)((char *)a1 + 0x15C) + 0xC) + (idx << 6) + 0x30, mat);
    *(int *)&buf[3] = 0;
    LocalizeDirectionOrient(func_00105278(), a0);
    t = func_00105278();
    MatrixDrive_TransMatrix(t, func_00105278());
    func_002438B8(buf, func_00105278(), buf);
    MatrixDrive_PushMatrixWithNoCopy(q, &q->f_2, buf[0], -buf[1], buf[2] * 0.0f);
}

int InitWallLeverGeo(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x800);
    return q->f_4 == 0;
}

typedef struct { char b[0x20]; } WLA;
extern WLA D_004BEFD0;
extern char D_00618630[];
extern void *D_00632010;
extern char D_0028CA88[];
extern void *func_0013A0F8(void *heap, int size, char *file, int line);
extern void *UnlinkParentOfDObj(void *a0, void *a1);

void *GetWallLeverAngle(void *a0, void *a1) {
    WLA *p = func_0013A0F8(D_00632010, 0x20, D_00618630, 0x8D);
    void *t;
    *p = D_004BEFD0;
    if (*(int *)((char *)a1 + 0x30) != 0) {
        *(int *)((char *)p + 0x14) = 1;
    } else {
        *(int *)((char *)p + 0x14) = 0;
    }
    t = UnlinkParentOfDObj(
        *(void **)(D_0028CA88 + *(int *)(*(int *)((char *)a0 + 0x15C) + 0x814) * 0x28), a1);
    *(int *)((char *)p + 0xC) = (int)t;
    t = UnlinkParentOfDObj(
        *(void **)(D_0028CA88 + *(int *)(*(int *)((char *)a0 + 0x15C) + 0x814) * 0x28 + 4), a1);
    *(int *)((char *)p + 0x10) = (int)t;
    return p;
}

int initParentize(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x800);
    return q->f_2;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0AE8);

int func_001C0BE0(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x800);
    return q[1] == 0;
}

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

short func_001C0D50(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WLGeo *q = *(WLGeo **)((char *)p + 0x800);
    return q->f_2;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0D60);

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0DE0);

INCLUDE_ASM("asm/nonmatchings/src/switch", BoxMemoryFunc);

INCLUDE_ASM("asm/nonmatchings/src/switch", getAlign);

INCLUDE_ASM("asm/nonmatchings/src/switch", GetDistanceOfGObj);

INCLUDE_ASM("asm/nonmatchings/src/switch", moveXPlus);

INCLUDE_ASM("asm/nonmatchings/src/switch", moveXMinus);

