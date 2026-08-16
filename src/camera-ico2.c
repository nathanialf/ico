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

typedef struct CamMgr {
    int count;          /* 0x00 */
    char *items;        /* 0x04 */
    char *pool;         /* 0x08 */
    char flags[0x64];   /* 0x0C */
} CamMgr;

typedef struct { int w[23]; } S5C;






extern int D_00633D74;
extern int D_00633D64;
extern float D_006326E0;
extern char D_006D04B4[];
extern void chain_simulate_term_simple();
extern void actBoySupportBGBegin();
extern void GetRootMatrixByDObj(void *a0, char *outer);
extern int *D_00631AE4;
extern int D_006326D0;
extern int D_00632CBC;
extern unsigned char D_006326D8;
extern void _CameraEdit_del_box(void);
extern void func_00186978(void);
extern void func_0018CC00(int a0);
extern void CameraEdit_Save(void);

int CameraSetCameraSet(void) {
    D_00632CBC = 1;
    if (D_006326D0 == 0) {
        _CameraEdit_del_box();
    }
    func_00186978();
    func_0018CC00(1);
    if (D_006326D8 == 0) {
        return 0;
    }
    D_006326D8 = 0;
    CameraEdit_Save();
    return -1;
}

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

extern void func_00104F20(void);
extern void func_00104FC0(int a0);
extern void func_00105268(void);
extern void *func_00105278(void);
extern void func_002438B8(void *a0, void *a1, void *a2);
extern void func_00243978(void *a0, void *a1);
extern void func_00243BD8(void *a0);

typedef struct Vec3 { float x, y, z; } Vec3;
typedef union Mat4 { float f[4]; long long q[2]; } Mat4;

extern Mat4 D_0055A750;
extern void gif_SpriteOffset(int a0);
extern void func_001D49C0(Vec3 *a, Vec3 *b, Mat4 *c, int d);
extern void func_0010F630(void);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", InitIco2Camera);

extern int D_00631990;
typedef struct StageParam {
    char pad0[0x118];
    int camSetId;               /* 0x118 */
    char pad11c[0x184 - 0x11C];
    float rate;                 /* 0x184 */
    char pad188[0x194 - 0x188];
} StageParam;

extern StageParam D_005F2FB8[];
extern float D_0028AE48[];
extern void CameraEdit_add_pin(S4C *a0);
extern int CameraEdit_del_box(int a0, char *a1);

void GetTargetOffset(int n, S4C *item, char *groups) {
    CamMgr *m1;
    CamMgr *m2;
    int i;
    int j;
    int a;
    int b;
    char *f;
    D_0028AE48[0] = D_005F2FB8[D_00631990].rate;
    m1 = (CamMgr *)D_00632610;
    m1->items = (char *)m1 + 0x70;
    m1->pool = (char *)m1 + 0x1E20;
    m1->count = 0;
    f = &m1->flags[0x63];
    for (a = 0x63; a >= 0; a--) {
        *f-- = 0;
    }
    m2 = (CamMgr *)D_00632614;
    m2->items = (char *)m2 + 0x70;
    m2->pool = (char *)m2 + 0x1E20;
    m2->count = 0;
    f = &m2->flags[0x63];
    for (b = 0x63; b >= 0; b--) {
        *f-- = 0;
    }
    for (i = 0; i < n; i++) {
        CameraEdit_add_pin(item);
        for (j = item->w[0x38 / 4]; j < item->w[0x3C / 4]; j++) {
            CameraEdit_del_box(i, groups + j * 0x5C);
        }
        item = (S4C *)((char *)item + 0x4C);
    }
}

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

extern char D_0055A8E0[];
extern char D_00275250[];
extern void debug_assertMessage(char *a0, ...);
extern void iosSemaCreate(void *a0);
extern void iosSemaDelete(void *a0);

void ReadCameraSet(void *obj) {
    char *base;
    iosSemaCreate(obj);
    base = D_00275250;
    for (;;) {
        debug_assertMessage(D_0055A8E0, *(void **)((char *)obj + 0x74));
        if (*(int *)(base + 0x5C) & 0x20) {
            D_006326D0 = *(int *)((char *)obj + 0x70);
            iosSemaDelete(obj);
        }
        iosSemaCreate(obj);
    }
}

extern char D_0055A8F0[];
extern void DispCameraGroup(void *a0, int a1, void *a2);

void func_00187EA0(void *obj) {
    char *base;
    iosSemaCreate(obj);
    base = D_00275250;
    for (;;) {
        debug_assertMessage(D_0055A8F0, *(void **)((char *)obj + 0x74));
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

extern char D_0055A900[];

int GetCameraGroupCurrent(CamMgr *mgr, S4C *src) {
    int result = -1;
    int i;
    char *p;
    S4C *dst;
    if (mgr->count < 0x64) {
        for (i = 0; i < 0x64; i++) {
            if (mgr->flags[i] == 0) {
                mgr->flags[i] = 1;
                p = mgr->pool + i * 0x23F0;
                goto have;
            }
        }
        p = 0;
    have:
        if (p != 0) {
            dst = (S4C *)(mgr->items + mgr->count * 0x4C);
            result = mgr->count;
            *dst = *src;
            dst->w[0x38 / 4] = 0;
            dst->w[0x3C / 4] = 0;
            *(char **)((char *)dst + 0x48) = p;
            mgr->count = mgr->count + 1;
        }
        return result;
    }
    debug_assertMessage(D_0055A900);
    return -1;
}

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


void InitPluralCameraSet(void) {
    AddPluralCameraSet(D_005F2FB8[D_00631990].camSetId);
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
extern void func_00243B18(void *a, void *b, float s);
extern float D_006D0520[3];
extern float D_006D0530[3];
extern float D_006D0540[3];
extern float D_006D0550[3];
extern float D_006D05E0[3];
extern float D_006D05F0[3];

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
        func_00243B18(A, A, -1.0f);
        func_00243B18(B, B, -1.0f);
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
        func_00243B18(C, C, -1.0f);
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
        D_006D0550[0] = v2[0];
        D_006D0550[1] = v2[1];
        D_006D0550[2] = v2[2];
    }
    if (flag != 0) {
        float a0 = v0[0];
        float a1 = v0[1];
        float a2 = v0[2];
        D_006D0520[0] = a0;
        D_006D0520[1] = a1;
        D_006D0520[2] = a2;
        D_006D05E0[0] = a0;
        D_006D05E0[1] = a1;
        D_006D05E0[2] = a2;
        D_006D05F0[0] = v1[0];
        D_006D05F0[1] = v1[1];
        D_006D05F0[2] = v1[2];
    }
    for (i = 0; i < 3; i++) {
        D_006D0530[i] = (v0[i] + D_006D05E0[i] * 3.0f) * 0.25f;
        D_006D0540[i] = (v1[i] + D_006D05F0[i] * 3.0f) * 0.25f;
    }
    D_006D05E0[0] = D_006D0530[0];
    D_006D05E0[1] = D_006D0530[1];
    D_006D05E0[2] = D_006D0530[2];
    D_006D05F0[0] = D_006D0540[0];
    D_006D05F0[1] = D_006D0540[1];
    D_006D05F0[2] = D_006D0540[2];
}

extern char *D_00633D58;
extern float D_006326E4[];
extern int D_00633D60;
extern void func_002641D8(float *a0, int a1, int a2);

int GetSizeOfCameraSetBinary(float *query) {
    int result = -1;
    float min = D_006326E4[0];
    int i;
    for (i = 0; i < D_00633D60; i++) {
            float buf[4];
            char *entry = D_00633D58 + i * 0x4C;
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
    /* The two block-local quantities here are the %hi address of D_006D04B4 and
     * the constant 1.  local-alloc orders them by QTY_CMP_PRI =
     * floor_log2(n_refs)*n_refs*size / (death-birth); both have 2 refs and one
     * word, so it reduces to 1/lifetime, and whichever is born LAST wins $2.
     * The ROM has the address in $2 AND emits its `lui` first, which the two
     * orderings cannot both give: writing the constant into a local before the
     * store (`char flag = 1; D_006D04B4[0] = flag;`) fixes the registers but
     * then emits `li` first (2 diffs), and the plain `D_006D04B4[0] = 1;` emits
     * `lui` first but puts the constant in $2 (3 diffs).  Not retired. */
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

extern void func_00243AE8(void *dst, void *a, void *b);
extern float MatrixDrive_GetTurnYAngleXZ(float v);
extern Mat4 D_0055A930;
extern int D_00632734;
extern float D_00630ECC;
extern void *subCommonIdle(int a0);
extern float func_00194630(void *a0);
extern void func_001945B8(void *a0, float v);
extern void func_00243AD0(void *dst, void *a, void *b);
extern void _OrientXZGV(void *a0, void *a1, void *a2, float f12, float f13);

void func_00188C98(float *a0, float *a1) {
    Mat4 v0;
    Mat4 v1;
    Mat4 mat;
    Mat4 v3;
    float t;
    mat = D_0055A930;
    t = func_00194630(subCommonIdle(D_00632734));
    func_001945B8(&mat, (float)(int)(t / D_00630ECC * 180.0f) * D_00630ECC / 180.0f);
    func_00243AD0(&v0, a0, &mat);
    func_00243AE8(&v3, a1, a0);
    v3.f[1] = 0.0f;
    MatrixDrive_GetTurnYAngleXZ(v3.f[0] * v3.f[0] + v3.f[1] + v3.f[2] * v3.f[2]);
    func_00243978(&v3, &v3);
    func_00243B18(&v3, &v3, -500.0f);
    func_00243AD0(&v1, &v3, a0);
    v1.f[1] = a0[1] + 200.0f;
    _OrientXZGV(a1, &v0, &v1, 4.0f, 5.0f);
    a1[0] = v0.f[0];
    a1[1] = v0.f[1];
    a1[2] = v0.f[2];
    a1[4] = a0[0];
    a1[5] = a0[1];
    a1[6] = a0[2];
    a1[8] = 50.0f;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00188E30);

extern int D_00633D54;
extern unsigned char D_00633D70;
extern float D_00633D68;
extern float D_00633D6C;
extern int D_00274EC0[];
extern void func_00194E28(void);

extern char D_0055A940[];
extern int D_00633D5C;
extern int D_00632028;
extern void iosMallocCheckLeak2(int a0);
extern char *func_0013A0F8(int a0, int a1, char *a2, int a3);

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

int func_0018B0A8(void *obj) {
    float buf[4];
    float *bp;
    int result;
    int i;
    GetRootMatrixByDObj(buf, obj);
    func_00243B18(buf, buf, -1.0f);
    bp = buf;
    result = -1;
    for (i = 0; i < D_00633D60; i++) {
        int k = 0;
        char *entry = D_00633D58 + i * 0x4C;
        float *range = (float *)(entry + 0x2C);
        float *center = (float *)(entry + 0x20);
        float *p = bp;
        do {
            if (*p < *center - *range) {
                break;
            }
            if (*center + *range < *p) {
                break;
            }
            p++;
            range++;
            center++;
        } while (++k < 3);
        if (k == 3) {
            result = i;
            break;
        }
    }
    return result;
}

int func_0018B180(float *pos) {
    float buf[4];
    float *bp;
    int result;
    int i;
    func_00243B18(buf, pos, -1.0f);
    bp = buf;
    result = -1;
    for (i = 0; i < D_00633D60; i++) {
        int k = 0;
        char *entry = D_00633D58 + i * 0x4C;
        float *range = (float *)(entry + 0x2C);
        float *center = (float *)(entry + 0x20);
        float *p = bp;
        do {
            if (*p < *center - *range) {
                break;
            }
            if (*center + *range < *p) {
                break;
            }
            p++;
            range++;
            center++;
        } while (++k < 3);
        if (k == 3) {
            result = i;
            break;
        }
    }
    return result;
}

typedef struct CamSetEnt {
    int key;
    int val;
} CamSetEnt;

extern CamSetEnt D_006D0600[];
extern char D_0055A970[];
extern char D_006326F0[];
extern void func_001AD768(char *a0, int a1);
extern void func_00263FF0(char *a0, int a1, char *a2);
extern int func_0018A400(int a0, int a1);

void func_0018B248(int key, int a1) {
    CamSetEnt *e;
    if (D_00633D74 >= 0xA) {
        debug_assertMessage(D_0055A970, (void *)0xA);
        func_001AD768(D_0055A940, 0x7C0);
        func_00263FF0(D_0055A940, 0x7C0, D_006326F0);
    }
    e = &D_006D0600[D_00633D74];
    e->key = key;
    e->val = func_0018A400(a1, D_00631990);
    D_00633D74 = D_00633D74 + 1;
}

void func_0018B2F8(void) {
    D_00633D74 = 0;
}

extern char D_002919D0[];
extern char D_0055A958[];

int func_0018B300(int key) {
    int i;
    for (i = 0; i < D_00633D74; i++) {
        if (D_006D0600[i].key == key) {
            return D_006D0600[i].val;
        }
    }
    debug_assertMessage(D_0055A958, D_002919D0 + key * 0x20);
    func_001AD768(D_0055A940, 0x7B7);
    func_00263FF0(D_0055A940, 0x7B7, D_006326F0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B3A8);

int func_0018B620(S4C *p, int n) {
    int size = n * 0x4C;
    int i;
    for (i = 0; i < n; i++) {
        size += (p->w[15] - p->w[14]) * 0x5C;
        p++;
    }
    return size;
}

extern float D_006D04C0[];

void func_0018B668(float *a0, float *a1, float v) {
    func_00243B18(D_006D04C0, a1, -1.0f);
    func_00243B18(&D_006D04C0[4], a0, -1.0f);
    func_00243B18(D_006D05E0, a0, -1.0f);
    func_00243B18(D_006D05F0, a0, -1.0f);
    D_006D04C0[8] = v;
}

typedef union Mtx3 { float f[12]; long long q[6]; } Mtx3;

typedef struct Ico2Cam {
    float pos[3];      /* 0x00 */
    char pad0c[4];     /* 0x0C */
    short angX;        /* 0x10 */
    short angY;        /* 0x12 */
    float fov;         /* 0x14 */
    char pad18[4];     /* 0x18 */
    short roll;        /* 0x1C */
} Ico2Cam;

extern Ico2Cam D_006D0680;
extern void func_0018B738(Ico2Cam *a0, Mtx3 *a1);
extern void func_0018B880(Ico2Cam *a0);

void func_0018B700(void *a0)
{
    func_0018B738(&D_006D0680, a0);
    func_0018B880(&D_006D0680);
}

extern float D_00630EF0;
extern float func_0025E5D8(float y, float x);

void func_0018B738(Ico2Cam *cam, Mtx3 *src) {
    Mtx3 m;
    float v[4];
    float rad = D_00630EF0;
    m = *src;
    cam->pos[0] = m.f[0];
    cam->pos[1] = m.f[1];
    cam->pos[2] = m.f[2];
    func_002641D8(v, 0, 0x10);
    v[3] = 1.0f;
    func_00243AE8(v, &m.f[4], &m.f[0]);
    MatrixDrive_GetTurnYAngleXZ(v[0] * v[0] + v[2] * v[2]);
    cam->angY = func_0025E5D8(v[0], v[2]) * 32768.0f / rad;
    cam->angX = func_0025E5D8(v[1], MatrixDrive_GetTurnYAngleXZ(v[0] * v[0] + v[2] * v[2])) * -32768.0f / rad;
    cam->fov = m.f[8];
}

extern void func_00104F48(int a0);
extern void func_00105038(int a0);
extern void func_002439B0(void *a0, void *a1);
extern void func_00105308(float x, float y, float z);
extern float func_0010E9A0(int a0);
extern float p2o_SetDefaultEnviroment(int a0);
extern int D_00631C5C;
extern int D_00631C60;
extern void light_killLinkLight(int a0, int a1, float v);
extern char *D_00631970;
extern void func_00243B70(void *a0, void *a1);
extern void gsb_SetVSMatrixSub(void);

void func_0018B880(Ico2Cam *cam) {
    void *m0;
    void *m1;
    float scale;
    float aspect;
    func_00104F20();
    func_00243BD8(func_00105278());
    func_00104FC0(cam->angY);
    func_00104F48(cam->angX);
    func_00105038(cam->roll);
    m0 = func_00105278();
    m1 = func_00105278();
    func_002439B0(m0, m1);
    func_00105308(-cam->pos[0], -cam->pos[1], -cam->pos[2]);
    scale = func_0010E9A0((short)(cam->fov * 32768.0f / 180.0f));
    aspect = p2o_SetDefaultEnviroment((short)(cam->fov * 32768.0f / 180.0f));
    light_killLinkLight(D_00631C5C, D_00631C60, scale * 1024.0f / aspect);
    func_00243B70(D_00631970 + 0x80, func_00105278());
    func_00105268();
    gsb_SetVSMatrixSub();
}

