#include "common.h"

typedef struct CamSetItem {
    char pad[0x48];
    void *end;
} CamSetItem;
typedef struct CamSetHdr {
    char pad0[8];
    int count; /* 0x08 */
    char pad0c[4];
    CamSetItem items[1]; /* 0x10 */
} CamSetHdr;

typedef struct { int w[19]; } S4C;

typedef struct { int w[23]; } S5C;






extern int D_00633D74;
extern int D_00633D64;
extern float D_006326E0;
extern char D_006D04B4[];
extern void chain_simulate_term_simple();
extern void actBoySupportBGBegin();
extern void GetRootMatrixByDObj(void *a0, char *outer);
extern int *D_00631AE4;
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", CameraSetCameraSet);

extern int CameraMove(int a0);
extern int *D_00632610;
extern int *D_00632614;
extern void GetRootPositionForCamera(int a0, int a1);

void CameraSetCameraSet_Default(int a0) {
    struct S4Cx { int w[19]; } *src;
    struct S4Cx *dst;
    void *saved;
    int i;
    src = (struct S4Cx *)(D_00632610[1] + a0 * 0x4C);
    dst = (struct S4Cx *)(D_00632614[1] + a0 * 0x4C);
    saved = *(void **)((char *)dst + 0x48);
    *dst = *src;
    *(void **)((char *)dst + 0x48) = saved;
    i = 0;
    while (i < *(int *)(CameraMove(a0) + 0x3C) - *(int *)(CameraMove(a0) + 0x38)) {
        GetRootPositionForCamera(a0, i);
        i++;
    }
}

void GetRootPositionForCamera(int a0, int a1) {
    S5C *dst = (S5C *)(*(int *)(D_00632614[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    S5C *src = (S5C *)(*(int *)(D_00632610[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    *dst = *src;
}

/* 0x4C, 4-byte aligned */ extern void ico2camera_GetGroupNearest(int a0, int a1);

void ico2camera_GetTargetPos(int a0) {
    S4C *dst = (S4C *)(D_00632610[1] + a0 * 0x4C);
    S4C *src = (S4C *)(D_00632614[1] + a0 * 0x4C);
    void *saved = *(void **)((char *)dst + 0x48);
    int i;
    *dst = *src;
    *(void **)((char *)dst + 0x48) = saved;
    i = 0;
    while (i < *(int *)(CameraMove(a0) + 0x3C) - *(int *)(CameraMove(a0) + 0x38)) {
        ico2camera_GetGroupNearest(a0, i);
        i++;
    }
}

void ico2camera_GetGroupNearest(int a0, int a1) {
    S5C *dst = (S5C *)(*(int *)(D_00632610[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    S5C *src = (S5C *)(*(int *)(D_00632614[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    *dst = *src;
}

int initMonitorCamera(void) {
    return *D_00632614;
}

int monitorMonitorCamera(int a0) {
    int r1 = CameraMove(a0);
    int r2 = CameraMove(a0);
    return *(int *)(r1 + 0x3C) - *(int *)(r2 + 0x38);
}

int ChaseCamera(int *a0, int a1) {
    int sum = 0;
    int i;
    for (i = 0; i < a1; i++) {
        sum += a0[15] - a0[14];
    }
    return sum;
}

int CameraMove(int a0) {
    return D_00632614[1] + a0 * 0x4C;
}

int ReflectCameraSetBinary(int a0, int a1) {
    return *(int *)(D_00632614[1] + a0 * 0x4C + 0x48) + a1 * 0x5C;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", InitIco2Camera);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetTargetOffset);

extern void func_00104F20(void);
extern void func_00104FC0(int a0);
extern void func_00105268(void);
extern void *func_00105278(void);
extern void func_002438B8(void *a0, void *a1, void *a2);
extern void func_00243978(void *a0, void *a1);
extern void func_00243BD8(void *a0);

void SetCameraMatrix_Ico2(int a0, int a1, int a2, int a3, float *out, int a5) {
    float zero = 0.0f;
    int absA0 = a0 < 0 ? -a0 : a0;
    out[2] = zero;
    out[1] = zero;
    out[0] = zero;
    if (absA0 < 0x32) {
        int absA1 = a1 < 0 ? -a1 : a1;
        if (absA1 < 0x32) {
            return;
        }
    }
    if (a2 != 0) {
        if (a0 > 0) {
            out[1] = (float)a5;
        }
        if (a0 < 0) {
            out[1] = (float)(-a5);
        }
    } else {
        float vec[4];
        void *p;
        func_00243BD8(func_00105278());
        func_00104F20();
        vec[0] = (float)a1;
        vec[1] = zero;
        vec[2] = (float)a0;
        vec[3] = zero;
        func_00243BD8(func_00105278());
        func_00104FC0((short)a3);
        p = func_00105278();
        func_002438B8(vec, p, vec);
        func_00243978(out, vec);
        func_00105268();
        out[0] = out[0] * (float)(-a5);
        out[2] = out[2] * (float)a5;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ReadCameraSet);

int SetCameraZoomOffsetRatio(int *a0, int a1, int a2)
{
  int *p;
  return ((int *) (a0[1] + (a1 * 0x4C)))[0x48 / 4] + (a2 * 0x5C);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetCameraGroupCurrent);

extern char D_0055A900[];
extern void debug_assertMessage(char *a0, void *a1);

int GetCameraGroupFromGObj(void *a0, int a1, S5C *src) {
    int base = a1 * 0x4C + *(int *)((char *)a0 + 4);
    int n = *(int *)(base + 0x3C);
    int result = -1;
    if (n < 0x64) {
        int base2;
        *(S5C *)(*(int *)(base + 0x48) + n * 0x5C) = *src;
        base2 = a1 * 0x4C + *(int *)((char *)a0 + 4);
        result = *(int *)(base2 + 0x3C);
        *(int *)(base2 + 0x3C) = result + 1;
    } else {
        debug_assertMessage(D_0055A900, (void *)a1);
    }
    return result;
}

void GetCameraGroupFromPosition(void) {}

extern void *D_00632744;
extern int D_00632748;
extern void func_001897A8(S4C *src, int count);
extern int func_0018B300(int key);

void AddPluralCameraSet(int a0) {
    CamSetHdr *p = (CamSetHdr *)func_0018B300(a0);
    CamSetItem *items = p->items;
    int n = p->count;
    CamSetItem *end = &items[n];
    int i;
    D_00632744 = p;
    D_00632748 = n;
    if (n > 0) {
        void **fp = &items[0].end;
        i = n;
        do {
            *fp = end;
            fp = (void **)((char *)fp + sizeof(CamSetItem));
        } while (--i);
    }
    func_001897A8((S4C *)items, n);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", InitPluralCameraSet);

void GetPluralCameraSet(int a0, int a1)
{
    if (a1 == D_00631AE4) {
        actBoySupportBGBegin(a0, a1);
    } else {
        GetRootMatrixByDObj(a0, a1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", MakeCameraSetBinary);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetSizeOfCameraSetBinary);

void SetCameraTargetPosition(int a0)
{
    register char *p = D_006D04B4;
    register int one __asm__("$3") = 1;
    int masked = a0 & 0xFF;
    *p = (char)one;
    if (masked == 0) {
        return;
    }
    chain_simulate_term_simple(masked);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001886F4);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001886F8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00188C98);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00188E30);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001897A8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189AC8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189B88);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189D68);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018A400);

void func_0018B098(float val) {
    D_006326E0 = val;
}

int func_0018B0A0(void) {
    return D_00633D64;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B0A8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B180);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B248);

void func_0018B2F8(void) {
    D_00633D74 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B300);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B3A8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B620);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B668);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B700);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B738);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B880);

