#include "common.h"

extern int D_0062A9B0;
extern int D_0062AF84;
extern unsigned char D_0062A9B8;
extern void _CameraEdit_del_box(void);
extern void func_00183E90(void);
extern void func_0018A0D8(int a0);
extern void CameraEdit_Save(void);

int CameraSetCameraSet(void) {
    D_0062AF84 = 1;
    if (D_0062A9B0 == 0) {
        _CameraEdit_del_box();
    }
    func_00183E90();
    func_0018A0D8(1);
    if (D_0062A9B8 == 0) {
        return 0;
    }
    D_0062A9B8 = 0;
    CameraEdit_Save();
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", CameraSetCameraSet_Default);

extern int *D_0062A8F0;
extern int *D_0062A8F4;
typedef struct { int w[23]; } S5C; /* 0x5C, 4-byte aligned */

void GetRootPositionForCamera(int a0, int a1) {
    S5C *dst = (S5C *)(*(int *)(D_0062A8F4[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    S5C *src = (S5C *)(*(int *)(D_0062A8F0[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    *dst = *src;
}


typedef struct { int w[19]; } S4C; /* 0x4C, 4-byte aligned */
extern void ico2camera_GetGroupNearest(int a0, int a1);
extern int CameraMove(int a0);

void ico2camera_GetTargetPos(int a0) {
    S4C *dst = (S4C *)(D_0062A8F0[1] + a0 * 0x4C);
    S4C *src = (S4C *)(D_0062A8F4[1] + a0 * 0x4C);
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
    S5C *dst = (S5C *)(*(int *)(D_0062A8F0[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    S5C *src = (S5C *)(*(int *)(D_0062A8F4[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    *dst = *src;
}


extern int *D_0062A8F4;

int initMonitorCamera(void) {
    return *D_0062A8F4;
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
    return D_0062A8F4[1] + a0 * 0x4C;
}

int ReflectCameraSetBinary(int a0, int a1) {
    return *(int *)(D_0062A8F4[1] + a0 * 0x4C + 0x48) + a1 * 0x5C;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", InitIco2Camera);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetTargetOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", SetCameraMatrix_Ico2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", ReadCameraSet);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_001853B8);

int SetCameraZoomOffsetRatio(void *a0, int a1, int a2) {
    int base = *(int *)((char *)a0 + 0x4);
    return *(int *)(base + a1 * 0x4C + 0x48) + a2 * 0x5C;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetCameraGroupCurrent);

extern void debug_assertMessage(char *a0, void *a1);
extern char D_00554AC0[];

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
        debug_assertMessage(D_00554AC0, (void *)a1);
    }
    return result;
}


void GetCameraGroupFromPosition(void) {
}

typedef struct CamSetItem {
    char pad[0x48];
    void *end;
} CamSetItem; /* 0x4C */

typedef struct CamSetHdr {
    char pad0[8];
    int count; /* 0x08 */
    char pad0c[4];
    CamSetItem items[1]; /* 0x10 */
} CamSetHdr;

extern void *D_0062AA20;
extern int D_0062AA24;
extern void func_00186CA8(int a0, int a1);
extern int func_001887E0(int key);

void AddPluralCameraSet(int a0) {
    CamSetHdr *p = (CamSetHdr *)func_001887E0(a0);
    CamSetItem *items = p->items;
    int n = p->count;
    CamSetItem *end = &items[n];
    int i;
    D_0062AA20 = p;
    D_0062AA24 = n;
    if (n > 0) {
        void **fp = &items[0].end;
        i = n;
        do {
            *fp = end;
            fp = (void **)((char *)fp + sizeof(CamSetItem));
        } while (--i);
    }
    func_00186CA8((int)items, n);
}


extern int D_00629C90;
extern unsigned char D_005EBC48[];
extern void AddPluralCameraSet(int a0);

extern int D_005EBC48_arr[][0x64] __asm__("D_005EBC48");
void InitPluralCameraSet(void) {
    AddPluralCameraSet(D_005EBC48_arr[D_00629C90][0x46]);
}

extern int D_00629DE4;
extern void actBoySupportBGBegin(void *a0, int a1);
extern void GetRootMatrixByDObj(void *a0, int a1);

void GetPluralCameraSet(void *a0, int a1) {
    if (a1 == D_00629DE4) {
        actBoySupportBGBegin(a0, a1);
        return;
    }
    GetRootMatrixByDObj(a0, a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", MakeCameraSetBinary);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetSizeOfCameraSetBinary);

extern unsigned char D_006C9D94[];
extern void chain_simulate_term_simple(void);

void SetCameraTargetPosition(void) {
    D_006C9D94[0] = 1;
    chain_simulate_term_simple();
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00185BF8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00186198);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00186330);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00186CA8);

extern int D_0062C044;
extern int D_0062C054;
extern int D_00271240[]; /* [0], [1] */
extern unsigned char D_0062C060;
extern float D_0062C058;
extern float D_0062C05C;
extern float D_005EBC48_farr[][0x64] __asm__("D_005EBC48");
extern void func_00192628(void);

void func_00186FC8(void) {
    int idx;
    int q;
    float f;
    float qf;
    D_0062C044 = 0;
    InitPluralCameraSet();
    SetCameraTargetPosition();
    idx = D_00629C90;
    D_0062C054 = -1;
    f = D_005EBC48_farr[idx][0x5F] * 60.0f;
    D_0062C060 = 1;
    q = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
    D_0062C05C = 600.0f / (float)q;
    D_0062C058 = f / (float)q;
    __asm__ __volatile__("");
    func_00192628();
}


INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00187088);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00187268);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_001878E0);

extern float D_0062A9C0;

void func_00188578(float a0) {
    D_0062A9C0 = a0;
}

extern int D_0062C054;

int func_00188580(void) {
    return D_0062C054;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188588);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188660);


extern int D_0062C064;
extern int D_00629C90;
extern char D_0062C850[];
extern char D_00554B00[];
extern char D_00554B30[];
extern void debug_assertMessage(char *a0, void *a1);
extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, void *a2);
extern int func_001878E0(void *a0, int a1);
typedef struct { void *key; int f_4; } RegEntry;
extern RegEntry D_006C9EE0_arr[] __asm__("D_006C9EE0");

void func_00188728(void *a0, void *a1) {
    RegEntry *slot;
    if (D_0062C064 >= 10) {
        debug_assertMessage(D_00554B30, (void *)10);
        func_001AAD00(D_00554B00, 0x7BE);
        func_00260380(D_00554B00, 0x7BE, D_0062C850);
    }
    slot = &D_006C9EE0_arr[D_0062C064];
    slot->key = a0;
    slot->f_4 = func_001878E0(a1, D_00629C90);
    D_0062C064 = D_0062C064 + 1;
}

extern int D_0062C064;

void func_001887D8(void) {
    D_0062C064 = 0;
}

extern void debug_assertMessage(char *a0, void *a1);
extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, void *a2);
typedef struct { int key; int f_4; } Lookup;
extern Lookup D_006C9EE0[];
extern char D_0028DB10[];
extern char D_0062C850[];
extern char D_00554B18[];
extern char D_00554B00[];

int func_001887E0(int key) {
    int n = D_0062C064;
    int i;
    for (i = 0; i < n; i++) {
        if (D_006C9EE0[i].key == key) {
            return D_006C9EE0[i].f_4;
        }
    }
    debug_assertMessage(D_00554B18, D_0028DB10 + key * 0x20);
    func_001AAD00(D_00554B00, 0x7B5);
    func_00260380(D_00554B00, 0x7B5, D_0062C850);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188888);

int func_00188B00(char *p, int n)
{
    int acc = n * 0x4C;
    int i = n;
    if (i > 0) {
        do {
            acc += (*(int *)(p + 0x3C) - *(int *)(p + 0x38)) * 0x5C;
            p += 0x4C;
            i--;
        } while (i != 0);
    }
    return acc;
}

extern void func_00240038(void *a0, float f);
extern void func_00240038_p(void *a0, void *a1, float f) __asm__("func_00240038");
extern char D_006C9DA0[];
extern char D_006C9EC0[];
extern char D_006C9ED0[];

void func_00188B48(void *a0, float a1) {
    func_00240038(D_006C9DA0, -1.0f);
    func_00240038_p(D_006C9DA0 + 0x10, a0, -1.0f);
    func_00240038_p(D_006C9EC0, a0, -1.0f);
    func_00240038_p(D_006C9ED0, a0, -1.0f);
    *(float *)(D_006C9DA0 + 0x20) = a1;
}

extern int D_006C9F60[];
extern void func_00188C18(int *a0, void *a1);
extern void func_00188D60(int *a0);

void func_00188BE0(void *a0) {
    func_00188C18(D_006C9F60, a0);
    func_00188D60(D_006C9F60);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188C18);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188D60);


/* recovered struct shapes */
typedef struct {
    unsigned char      f_44;  /* 0x44 */
    unsigned long long f_50;  /* 0x50 */
    unsigned long long f_58;  /* 0x58 */
    unsigned long long f_60;  /* 0x60 */
    unsigned long long f_68;  /* 0x68 */
    unsigned long long f_70;  /* 0x70 */
    unsigned long long f_78;  /* 0x78 */
    unsigned int       f_80;  /* 0x80 */
    unsigned int       f_84;  /* 0x84 */
    unsigned int       f_88;  /* 0x88 */
    unsigned int       f_90;  /* 0x90 */
    unsigned int       f_94;  /* 0x94 */
    unsigned int       f_98;  /* 0x98 */
    unsigned int       f_A0;  /* 0xA0 */
    unsigned int       f_A4;  /* 0xA4 */
} S_006C9D50;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_00287140;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_006C9EE0;  /* stride 0x8 */

/* end struct shapes */
