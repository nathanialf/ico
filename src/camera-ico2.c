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

extern char D_0055A8F0[];
extern char D_00275250[];
extern void ReadCameraSet(void);
extern void DispCameraGroup(void *a0, int a1, void *a2);
extern void debug_assertMessage__c2(char *a0, void *a1) __asm__("debug_assertMessage");
extern void iosSemaCreate(void *a0);

void func_00187EA0(void *obj) {
    char *base;
    iosSemaCreate(obj);
    base = D_00275250;
    for (;;) {
        debug_assertMessage__c2(D_0055A8F0, *(void **)((char *)obj + 0x74));
        if (*(int *)(base + 0x5C) & 0x20) {
            DispCameraGroup(ReadCameraSet, 3, obj);
        }
        iosSemaCreate(obj);
    }
}

int func_00187F10(void *a0, int a1) {
    return *(int *)((char *)a0 + 4) + a1 * 0x4C;
}

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

extern int D_00631990;
extern int D_005F2FB8_arr[][0x65] __asm__("D_005F2FB8");

void InitPluralCameraSet(void) {
    AddPluralCameraSet(D_005F2FB8_arr[D_00631990][0x46]);
}

void GetPluralCameraSet(int a0, int a1)
{
    if (a1 == D_00631AE4) {
        actBoySupportBGBegin(a0, a1);
    } else {
        GetRootMatrixByDObj(a0, a1);
    }
}

extern void InitCameraSetManager(int *a0, int *a1);
extern void func_00240038_v(void *a, void *b, float s) __asm__("func_00243B18");
extern float g_E00[3] __asm__("D_006D0520");
extern float g_E10[3] __asm__("D_006D0530");
extern float g_E20[3] __asm__("D_006D0540");
extern float g_E30[3] __asm__("D_006D0550");
extern float g_EC0[3] __asm__("D_006D05E0");
extern float g_ED0[3] __asm__("D_006D05F0");

void MakeCameraSetBinary(int a0) {
    unsigned char flag = a0;
    int p1;
    int p2;
    float v0[4];
    float v1[4];
    float v2[4];
    float A[4];
    float B[4];
    float C[4];
    int i;

    InitCameraSetManager(&p1, &p2);
    if (p1 == 0) {
        return;
    }
    if (p2 != 0) {
        GetPluralCameraSet(A, p1);
        GetPluralCameraSet(B, p2);
        func_00240038_v(A, A, -1.0f);
        func_00240038_v(B, B, -1.0f);
        v1[0] = A[0];
        v1[1] = A[1];
        v1[2] = A[2];
        v0[0] = B[0];
        v0[1] = B[1];
        v0[2] = B[2];
        v2[0] = A[0];
        v2[1] = A[1];
        v2[2] = A[2];
    } else {
        GetPluralCameraSet(C, p1);
        func_00240038_v(C, C, -1.0f);
        v0[0] = C[0];
        v0[1] = C[1];
        v0[2] = C[2];
        v1[0] = C[0];
        v1[1] = C[1];
        v1[2] = C[2];
        v2[0] = C[0];
        v2[1] = C[1];
        v2[2] = C[2];
    }
    {
        g_E30[0] = v2[0];
        g_E30[1] = v2[1];
        g_E30[2] = v2[2];
    }
    if (flag != 0) {
        float a0 = v0[0];
        float a1 = v0[1];
        float a2 = v0[2];
        g_E00[0] = a0;
        g_E00[1] = a1;
        g_E00[2] = a2;
        g_EC0[0] = a0;
        g_EC0[1] = a1;
        g_EC0[2] = a2;
        g_ED0[0] = v1[0];
        g_ED0[1] = v1[1];
        g_ED0[2] = v1[2];
    }
    for (i = 0; i < 3; i++) {
        g_E10[i] = (v0[i] + g_EC0[i] * 3.0f) * 0.25f;
        g_E20[i] = (v1[i] + g_ED0[i] * 3.0f) * 0.25f;
    }
    g_EC0[0] = g_E10[0];
    g_EC0[1] = g_E10[1];
    g_EC0[2] = g_E10[2];
    g_ED0[0] = g_E20[0];
    g_ED0[1] = g_E20[1];
    g_ED0[2] = g_E20[2];
}

extern char *D_0062C048_arr __asm__("D_00633D58");
extern float D_0062C844_f[] __asm__("D_006326E4");
extern int D_00633D60;
extern void func_002641D8(float *a0, int a1, int a2);

int GetSizeOfCameraSetBinary(float *query) {
    int result = -1;
    float min = D_0062C844_f[0];
    int i;
    for (i = 0; i < D_00633D60; i++) {
            float buf[4];
            char *entry = D_0062C048_arr + i * 0x4C;
            float *center = (float *)(entry + 0x20);
            float *range = (float *)(entry + 0x2C);
            int k;
            func_002641D8(buf, 0, 0x10);
            for (k = 0; k < 3; k++) {
                float d = query[k] - center[k];
                float r;
                float t;
                if (d < 0.0f) d = -d;
                r = range[k];
                if (r < 0.0f) r = -r;
                if (r < 0.0f) t = 0.0f;
                else if (d < r) t = d;
                else t = r;
                buf[k] = d - t;
            }
            {
                float sum = buf[0] * buf[0] + buf[1] * buf[1] + buf[2] * buf[2];
                if (sum < min) {
                    result = i;
                    min = sum;
                }
            }
    }
    return result;
}

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

