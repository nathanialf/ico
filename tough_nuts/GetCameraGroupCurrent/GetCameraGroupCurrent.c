#include "common.h"

extern int D_0062A9B0;
extern int D_0062AF84;
extern unsigned char D_0062A9B8;
extern void _CameraEdit_del_box(void);
extern void func_00183E90(void);
extern void CameraSetMode(int a0);
extern void CameraEdit_Save(void);

int CameraSetCameraSet(void) {
    D_0062AF84 = 1;
    if (D_0062A9B0 == 0) {
        _CameraEdit_del_box();
    }
    func_00183E90();
    CameraSetMode(1);
    if (D_0062A9B8 == 0) {
        return 0;
    }
    D_0062A9B8 = 0;
    CameraEdit_Save();
    return -1;
}

extern int *D_0062A8F0;
extern int *D_0062A8F4;
extern int CameraEdit_BOX(int a0);
extern void GetRootPositionForCamera(int a0, int a1);

void CameraEdit_reset_box(int a0) {
    struct S4Cx { int w[19]; } *src;
    struct S4Cx *dst;
    void *saved;
    int i;
    src = (struct S4Cx *)(D_0062A8F0[1] + a0 * 0x4C);
    dst = (struct S4Cx *)(D_0062A8F4[1] + a0 * 0x4C);
    saved = *(void **)((char *)dst + 0x48);
    *dst = *src;
    *(void **)((char *)dst + 0x48) = saved;
    i = 0;
    while (i < *(int *)(CameraEdit_BOX(a0) + 0x3C) - *(int *)(CameraEdit_BOX(a0) + 0x38)) {
        GetRootPositionForCamera(a0, i);
        i++;
    }
}


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
extern int CameraEdit_BOX(int a0);

void CameraEdit_reflect_box(int a0) {
    S4C *dst = (S4C *)(D_0062A8F0[1] + a0 * 0x4C);
    S4C *src = (S4C *)(D_0062A8F4[1] + a0 * 0x4C);
    void *saved = *(void **)((char *)dst + 0x48);
    int i;
    *dst = *src;
    *(void **)((char *)dst + 0x48) = saved;
    i = 0;
    while (i < *(int *)(CameraEdit_BOX(a0) + 0x3C) - *(int *)(CameraEdit_BOX(a0) + 0x38)) {
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

int CameraEdit_BOX_NUMBER(void) {
    return *D_0062A8F4;
}

int CameraEdit_PIN_NUMBER(int a0) {
    int r1 = CameraEdit_BOX(a0);
    int r2 = CameraEdit_BOX(a0);
    return *(int *)(r1 + 0x3C) - *(int *)(r2 + 0x38);
}

int CameraEdit_PIN_NUMBER_ALL(int *a0, int a1) {
    int sum = 0;
    int i;
    for (i = 0; i < a1; i++) {
        sum += a0[15] - a0[14];
    }
    return sum;
}

int CameraEdit_BOX(int a0) {
    return D_0062A8F4[1] + a0 * 0x4C;
}

int CameraEdit_PIN(int a0, int a1) {
    return *(int *)(D_0062A8F4[1] + a0 * 0x4C + 0x48) + a1 * 0x5C;
}

extern void *func_00105078(void);
extern void sceVu0UnitMatrix(void *a0);
extern void gif_SpriteOffset(int a0);
extern void func_001D1D58(void *a0, void *a1, void *a2, int a3);
extern void func_0010F9D0(void);
extern long long D_00554910[2];

struct V3 { float x, y, z; };

static inline void InitIco2Camera_body(int a0, int i, long long *quat) {
    struct V3 v0 = {
        *(float *)(CameraEdit_PIN(a0, i) + 0x0),
        *(float *)(CameraEdit_PIN(a0, i) + 0x4),
        *(float *)(CameraEdit_PIN(a0, i) + 0x8),
    };
    struct V3 v1 = {
        *(float *)(CameraEdit_PIN(a0, i) + 0xC),
        *(float *)(CameraEdit_PIN(a0, i) + 0x10),
        *(float *)(CameraEdit_PIN(a0, i) + 0x14),
    };
    func_001D1D58(&v0, &v1, quat, -1);
}

void CameraEdit_DispPin(int a0, int a1) {
    long long quat[2];
    void *p0;
    void *pA;
    void *pB;
    void *pC;
    int i;
    int end = a1 + 1;
    quat[0] = D_00554910[0];
    quat[1] = D_00554910[1];
    p0 = func_00105078();
    sceVu0UnitMatrix(p0);
    pA = func_00105078();
    pB = func_00105078();
    pC = func_00105078();
    *(float *)((char *)pC + 0x28) = -1.0f;
    *(float *)((char *)pB + 0x14) = -1.0f;
    *(float *)((char *)pA + 0x0) = -1.0f;
    gif_SpriteOffset(0xB);
    for (i = a1; i < end; i++) {
        InitIco2Camera_body(a0, i, quat);
    }
    func_0010F9D0();
}


extern int D_00629C90;
extern float D_005EBC48_gtf[][0x64] __asm__("D_005EBC48");
extern float D_00287048_x[4] __asm__("D_00287048");
extern void CameraEdit_add_pin(int *a0);
extern void CameraEdit_del_box(int a0, int a1);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetTargetOffset);


extern void func_00104D20(void);
extern void MatrixDrive_RotMatrixY(int a0);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void MatrixDrive_PopMatrix(void);

void StickToTrans(int a0, int a1, int a2, int a3, float *out, int a5) {
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
        sceVu0UnitMatrix(func_00105078());
        func_00104D20();
        vec[0] = (float)a1;
        vec[1] = zero;
        vec[2] = (float)a0;
        vec[3] = zero;
        sceVu0UnitMatrix(func_00105078());
        MatrixDrive_RotMatrixY((short)a3);
        p = func_00105078();
        sceVu0ApplyMatrix(vec, p, vec);
        sceVu0Normalize(out, vec);
        MatrixDrive_PopMatrix();
        out[0] = out[0] * (float)(-a5);
        out[2] = out[2] * (float)a5;
    }
}


extern char D_00554AA0[];
extern char D_002715D0[];
extern void iosSemaCreate(void *obj);
extern void iosSemaDelete(void *obj);
extern void debug_StdPrintfDummy(char *a0, void *a1);

void ReadCameraSet(void *obj) {
    char *base;
    iosSemaCreate(obj);
    base = D_002715D0;
    for (;;) {
        debug_StdPrintfDummy(D_00554AA0, *(void **)((char *)obj + 0x74));
        if (*(int *)(base + 0x5C) & 0x20) {
            D_0062A9B0 = *(int *)((char *)obj + 0x70);
            iosSemaDelete(obj);
        }
        iosSemaCreate(obj);
    }
}


extern char D_00554AB0[];
extern void DispCameraGroup(void *a0, int a1, void *a2);

void func_001853B8(void *obj) {
    char *base;
    iosSemaCreate(obj);
    base = D_002715D0;
    for (;;) {
        debug_StdPrintfDummy(D_00554AB0, *(void **)((char *)obj + 0x74));
        if (*(int *)(base + 0x5C) & 0x20) {
            DispCameraGroup(ReadCameraSet, 3, obj);
        }
        iosSemaCreate(obj);
    }
}


int func_00185428(void *a0, int a1) {
    return *(int *)((char *)a0 + 4) + a1 * 0x4C;
}



int _CameraEdit_PIN(void *a0, int a1, int a2) {
    int base = *(int *)((char *)a0 + 0x4);
    return *(int *)(base + a1 * 0x4C + 0x48) + a2 * 0x5C;
}

extern char D_00554AC0[];

int _CameraEdit_add_box(void *hdr, S4C *src) {
    int ret = -1;
    char *flags;
    int i;
    int slot;
    if (*(int *)hdr >= 0x64) {
        debug_StdPrintfDummy(D_00554AC0, src);
        return -1;
    }
    flags = (char *)hdr + 0xC;
    for (i = 0; i < 0x64; i++) {
        if (flags[i] == 0) goto found;
    }
    slot = 0;
check:
    if (slot != 0) {
        S4C *dest = (S4C *)(*(int *)((char *)hdr + 4) + *(int *)hdr * 0x4C);
        ret = *(int *)hdr;
        *dest = *src;
        *(int *)((char *)dest + 0x38) = 0;
        *(int *)((char *)dest + 0x3C) = 0;
        *(int *)((char *)dest + 0x48) = slot;
        *(int *)hdr = *(int *)hdr + 1;
    }
    return ret;
found:
    flags[i] = 1;
    slot = *(int *)((char *)hdr + 8) + i * 0x23F0;
    goto check;
}


extern void debug_StdPrintfDummy(char *a0, void *a1);
extern char D_00554AC0[];

int _CameraEdit_add_pin(void *a0, int a1, S5C *src) {
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
        debug_StdPrintfDummy(D_00554AC0, (void *)a1);
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

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", ico2camera_GetTargetPos);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetSizeOfCameraSetBinary);

extern unsigned char D_006C9D94[];
extern void chain_simulate_term_simple(void);

void SetCameraTargetPosition(void) {
    D_006C9D94[0] = 1;
    chain_simulate_term_simple();
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00185BF8);

extern long long D_00554AF0[2];
extern int D_0062AA14;
extern float D_006291B8;
extern void *subCommonIdle(int a0);
extern float _GetDirection(void *a0);
extern void func_00191DB8(void *q, float angle);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0SubVector(float *a0, float *a1, float *a2);
extern float FSqrt(float a0);
extern void sceVu0Normalize(void *a, void *b);
extern void func_00240038_v(void *a, void *b, float s) __asm__("sceVu0ScaleVector");
extern void _InterGV(void *a0, void *a1, void *a2, float a3, float a4);

void ChaseCamera(float *a0, float *a1) {
    float v0[4];
    float v10[4];
    long long q[2];
    float v30[4];
    void *p;
    float f;
    int n;
    q[0] = D_00554AF0[0];
    q[1] = D_00554AF0[1];
    p = subCommonIdle(D_0062AA14);
    f = _GetDirection(p) / D_006291B8 * 180.0f;
    n = (int)f;
    func_00191DB8(q, (float)n * D_006291B8 / 180.0f);
    sceVu0AddVector(v0, a0, q);
    sceVu0SubVector(v30, a1, a0);
    v30[1] = 0.0f;
    FSqrt(v30[0] * v30[0] + v30[1] * v30[1] + v30[2] * v30[2]);
    sceVu0Normalize(v30, v30);
    func_00240038_v(v30, v30, -500.0f);
    sceVu0AddVector(v10, v30, a0);
    v10[1] = a0[1] + 200.0f;
    _InterGV(a1, v0, v10, 4.0f, 5.0f);
    a1[0] = v0[0];
    a1[1] = v0[1];
    a1[2] = v0[2];
    a1[4] = a0[0];
    a1[5] = a0[1];
    a1[6] = a0[2];
    a1[8] = 50.0f;
}


INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", CameraMove);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00186CA8);

extern int D_0062C044;
extern int D_0062C054;
extern int D_00271240[]; /* [0], [1] */
extern unsigned char D_0062C060;
extern float D_0062C058;
extern float D_0062C05C;
extern float D_005EBC48_farr[][0x64] __asm__("D_005EBC48");
extern void InitHandCameraCorrect(void);

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
    InitHandCameraCorrect();
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

typedef struct {
    char pad20[0x20];
    float c[3]; /* 0x20 */
    float h[3]; /* 0x2C */
    char pad38[0x14]; /* to 0x4C */
} CamBox; /* 0x4C */
extern CamBox *D_0062C048;
extern int D_0062C050;
extern void func_00240038_3(float *pt, void *a0, float s) __asm__("sceVu0ScaleVector");
extern void GetRootMatrixByDObj_p(float *pt, void *a0) __asm__("GetRootMatrixByDObj");

int GetCameraGroupFromGObj(void *a0) {
    float pt[4];
    float *pt_start;
    int result;
    int i;
    int n;
    GetRootMatrixByDObj_p(pt, a0);
    func_00240038_3(pt, pt, -1.0f);
    pt_start = pt;
    n = D_0062C050;
    result = -1;
    for (i = 0; i < n; i++) {
        float *c = D_0062C048[i].c;
        float *h = D_0062C048[i].h;
        int j = 0;
        do {
            if (pt_start[j] < c[j] - h[j]) {
                break;
            }
            if (c[j] + h[j] < pt_start[j]) {
                break;
            }
            j++;
        } while (j < 3);
        if (j == 3) {
            result = i;
            break;
        }
    }
    return result;
}

int func_00188660(void *a0) {
    float pt[4];
    float *pt_start;
    int result;
    int i;
    int n;
    int found;
    func_00240038_3(pt, a0, -1.0f);
    pt_start = pt;
    n = D_0062C050;
    result = -1;
    (void)found;
    for (i = 0; i < n; i++) {
        float *c = D_0062C048[i].c;
        float *h = D_0062C048[i].h;
        int j = 0;
        do {
            if (pt_start[j] < c[j] - h[j]) {
                break;
            }
            if (c[j] + h[j] < pt_start[j]) {
                break;
            }
            j++;
        } while (j < 3);
        if (j == 3) {
            result = i;
            break;
        }
    }
    return result;
}



extern int D_0062C064;
extern int D_00629C90;
extern char D_0062C850[];
extern char D_00554B00[];
extern char D_00554B30[];
extern void debug_StdPrintfDummy(char *a0, void *a1);
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, void *a2);
extern int func_001878E0(void *a0, int a1);
typedef struct { void *key; int f_4; } RegEntry;
extern RegEntry D_006C9EE0_arr[] __asm__("D_006C9EE0");

void func_00188728(void *a0, void *a1) {
    RegEntry *slot;
    if (D_0062C064 >= 10) {
        debug_StdPrintfDummy(D_00554B30, (void *)10);
        func_001AAD00(D_00554B00, 0x7BE);
        __assert(D_00554B00, 0x7BE, D_0062C850);
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

extern void debug_StdPrintfDummy(char *a0, void *a1);
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, void *a2);
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
    debug_StdPrintfDummy(D_00554B18, D_0028DB10 + key * 0x20);
    func_001AAD00(D_00554B00, 0x7B5);
    __assert(D_00554B00, 0x7B5, D_0062C850);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", MakeCameraSetBinary);

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

extern void sceVu0ScaleVector(void *a0, float f);
extern void func_00240038_p(void *a0, void *a1, float f) __asm__("sceVu0ScaleVector");
extern char D_006C9DA0[];
extern char D_006C9EC0[];
extern char D_006C9ED0[];

void func_00188B48(void *a0, float a1) {
    sceVu0ScaleVector(D_006C9DA0, -1.0f);
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

extern float D_006291DC;
extern void memset(float *m, int a1, int a2);
extern void sceVu0SubVector(float *a0, float *a1, float *a2);
extern float FSqrt(float a0);
extern float atan2f(float a0, float a1);
typedef struct { double d[6]; } Mat30; /* 0x30, 8-byte aligned */

void func_00188C18(int *dst, void *src) {
    Mat30 m;
    float loc[4];
    float f20 = D_006291DC;
    float *mf = (float *)&m;
    m = *(Mat30 *)src;
    ((float *)dst)[0] = mf[0];
    ((float *)dst)[1] = mf[1];
    ((float *)dst)[2] = mf[2];
    memset(loc, 0, 16);
    loc[3] = 1.0f;
    sceVu0SubVector(loc, &mf[4], &mf[0]);
    FSqrt(loc[0] * loc[0] + loc[2] * loc[2]);
    *(short *)((char *)dst + 0x12) = (short)(atan2f(loc[0], loc[2]) * 32768.0f / f20);
    *(short *)((char *)dst + 0x10) = (short)(atan2f(loc[1], FSqrt(loc[0] * loc[0] + loc[2] * loc[2])) * -32768.0f / f20);
    *(float *)((char *)dst + 0x14) = mf[8];
}


extern void func_00104D20(void);
extern void *func_00105078(void);
extern void sceVu0UnitMatrix(void *a0);
extern void MatrixDrive_RotMatrixY(int a0);
extern void MatrixDrive_RotMatrixX(int a0);
extern void MatrixDrive_RotMatrixZ(int a0);
extern void sceVu0TransposeMatrix(void *a0, void *a1);
extern void func_00105108(float a, float b, float c);
extern float GetTableCos(short a0);
extern float p2o_SetDefaultEnviroment(short a0);
extern void light_killLinkLight(int a0, int a1, float f);
extern void sceVu0CopyMatrix(void *a0, void *a1);
extern void MatrixDrive_PopMatrix(void);
extern void gsb_MakeCommonMatrix(void);
extern int D_00629F5C;
extern int D_00629F60;
extern int D_00629C70;

void func_00188D60(int *s) {
    void *A;
    void *B;
    float f20;
    float p;
    func_00104D20();
    sceVu0UnitMatrix(func_00105078());
    MatrixDrive_RotMatrixY(*(short *)((char *)s + 0x12));
    MatrixDrive_RotMatrixX(*(short *)((char *)s + 0x10));
    MatrixDrive_RotMatrixZ(*(short *)((char *)s + 0x1C));
    A = func_00105078();
    B = func_00105078();
    sceVu0TransposeMatrix(A, B);
    func_00105108(-((float *)s)[0], -((float *)s)[1], -((float *)s)[2]);
    f20 = GetTableCos((short)(((float *)s)[5] * 32768.0f / 180.0f));
    p = p2o_SetDefaultEnviroment((short)(((float *)s)[5] * 32768.0f / 180.0f));
    light_killLinkLight(D_00629F5C, D_00629F60, f20 * 1024.0f / p);
    sceVu0CopyMatrix((void *)(D_00629C70 + 0x80), func_00105078());
    MatrixDrive_PopMatrix();
    gsb_MakeCommonMatrix();
}



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
