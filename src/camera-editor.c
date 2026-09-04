#include "common.h"

typedef struct { int w[23]; } S5C;

typedef struct CamMgr {
    int count;          /* 0x00 */
    char *items;        /* 0x04 */
    char *pool;         /* 0x08 */
    char flags[0x64];   /* 0x0C */
} CamMgr;
typedef struct StageParam {
    char pad0[0x118];
    int camSetId;               /* 0x118 */
    char pad11c[0x184 - 0x11C];
    float rate;                 /* 0x184 */
    char pad188[0x194 - 0x188];
} StageParam;

typedef struct { int w[19]; } S4C;

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", EnterMenu);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", saveEditedDataBinary);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", saveEditedData);
extern void gif_SetGsReg(int code, long data);

void gif_test(int *a0, int *a1, int *a2, unsigned char *a3) {
    gif_SetGsReg(0, 3);
    gif_SetGsReg(1, (long)a3[0] | ((long)a3[1] << 8) | ((long)a3[2] << 16) | ((long)a3[3] << 24));
    gif_SetGsReg(4, (long)a0[0] | ((long)a0[1] << 16) | ((long)a0[2] << 32));
    gif_SetGsReg(4, (long)a1[0] | ((long)a1[1] << 16) | ((long)a1[2] << 32));
    gif_SetGsReg(4, (long)a2[0] | ((long)a2[1] << 16) | ((long)a2[2] << 32));
}
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", DebugDispBox);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", DispCameraGroup);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", drawXZArrow);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", DispAxisArrow);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", dispCameraPinType2);
extern void dispCameraPinType2(int a0, int a1, int a2, int a3);

void CameraEdit_DispPinType2(int a0, int a1, int a2) {
    dispCameraPinType2(a0, a1, a1 + 1, a2);
}
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", dispCameraGroupType2);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", dispBox);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispBoxType2_Plane);
extern void dispCameraGroupType2(int a0, int a1);

void CameraEdit_DispBoxType2(int a0, int a1) {
    dispCameraGroupType2(a0, a1 & 0xFF);
}
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_0018CDC0);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_0018E0D0);
extern void EnterMenu(void *a0, int a1, void *a2);
extern void func_0018CDC0(void);

void test_camedit(void) {
    EnterMenu((void *)func_0018CDC0, 0, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", _CameraEdit_del_box);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", _CameraEdit_del_pin);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_add_box);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_add_pin);
extern int *D_0063AA78;
extern int *D_0063AA7C;
extern void _CameraEdit_del_box(int *a0, void *a1);

void CameraEdit_del_box(void *a0) {
    _CameraEdit_del_box(D_0063AA78, a0);
    _CameraEdit_del_box(D_0063AA7C, a0);
}
extern void _CameraEdit_del_pin(int a0, int a1, int a2);

void CameraEdit_del_pin(int a0, int a1)
{
    _CameraEdit_del_pin(D_0063AA78, a0, a1);
    _CameraEdit_del_pin(D_0063AA7C, a0, a1);
}
extern void DispCameraGroup(int a0, unsigned char a1);

void CameraEdit_DispBox(int a0, unsigned char a1) {
    DispCameraGroup(a0, a1);
}
extern void ReflectCameraSetBinary(int a0, int a1);

void CameraEdit_Reflect(void) {
    int *p = D_0063AA78;
    ReflectCameraSetBinary(p[1], p[0]);
}
extern void saveEditedDataBinary(int a0, int a1, int a2);

void CameraEdit_Save(int a0) {
    int *p = D_0063AA78;
    saveEditedDataBinary(a0, p[1], p[0]);
}
extern void debug_Marker(int *buf, int a1, int a2, int a3, float f12, float f13);
extern void sceVu0ScaleVector(int *buf, int *p, float t);

void debug_NMarker(int *self, int a1, int a2, int a3, float t)
{
    int buf[4];
    sceVu0ScaleVector(buf, self, -1.0f);
    debug_Marker(buf, a1, a2, a3, t, 0.0f);
}
void debug_Marker(int *buf, int a1, int a2, int a3, float f12, float f13) {}
void debug_Arrow(void) {}
extern int D_0063AB38;
extern char D_0063AB40;

void InitCameraEditor(void) {
    D_0063AB38 = 0;
    D_0063AB40 = 0;
}
extern void CameraSetMode(int a0);
extern unsigned char D_0063AB40__pn __asm__("D_0063AB40");
extern int D_0063B13C;
extern void func_0018E0D0(void);
extern void test_camedit(void);

int debug_CameraEditor(void) {
    D_0063B13C = 1;
    if (D_0063AB38 == 0) {
        test_camedit();
    }
    func_0018E0D0();
    CameraSetMode(1);
    if (D_0063AB40__pn == 0) {
        return 0;
    }
    D_0063AB40__pn = 0;
    CameraEdit_Reflect();
    return -1;
}
extern int CameraEdit_BOX(int a0);
extern void CameraEdit_reset_pin(int a0, int a1);

void CameraEdit_reset_box(int a0) {
    struct S4Cx { int w[19]; } *src;
    struct S4Cx *dst;
    void *saved;
    int i;
    src = (struct S4Cx *)(D_0063AA78[1] + a0 * 0x4C);
    dst = (struct S4Cx *)(D_0063AA7C[1] + a0 * 0x4C);
    saved = *(void **)((char *)dst + 0x48);
    *dst = *src;
    *(void **)((char *)dst + 0x48) = saved;
    i = 0;
    while (i < *(int *)(CameraEdit_BOX(a0) + 0x3C) - *(int *)(CameraEdit_BOX(a0) + 0x38)) {
        CameraEdit_reset_pin(a0, i);
        i++;
    }
}
void CameraEdit_reset_pin(int a0, int a1) {
    S5C *dst = (S5C *)(*(int *)(D_0063AA7C[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    S5C *src = (S5C *)(*(int *)(D_0063AA78[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    *dst = *src;
}
extern void CameraEdit_reflect_pin(int a0, int a1);

void CameraEdit_reflect_box(int a0) {
    S4C *dst = (S4C *)(D_0063AA78[1] + a0 * 0x4C);
    S4C *src = (S4C *)(D_0063AA7C[1] + a0 * 0x4C);
    void *saved = *(void **)((char *)dst + 0x48);
    int i;
    *dst = *src;
    *(void **)((char *)dst + 0x48) = saved;
    i = 0;
    while (i < *(int *)(CameraEdit_BOX(a0) + 0x3C) - *(int *)(CameraEdit_BOX(a0) + 0x38)) {
        CameraEdit_reflect_pin(a0, i);
        i++;
    }
}
void CameraEdit_reflect_pin(int a0, int a1) {
    S5C *dst = (S5C *)(*(int *)(D_0063AA78[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    S5C *src = (S5C *)(*(int *)(D_0063AA7C[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    *dst = *src;
}
int CameraEdit_BOX_NUMBER(void) {
    return *D_0063AA7C;
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
    return D_0063AA7C[1] + a0 * 0x4C;
}
int CameraEdit_PIN(int a0, int a1) {
    return *(int *)(D_0063AA7C[1] + a0 * 0x4C + 0x48) + a1 * 0x5C;
}
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispPin);
extern void CameraEdit_add_box(S4C *a0);
extern int CameraEdit_add_pin(int a0, char *a1);
extern float D_002A5D68[];
extern StageParam D_005F5D50[];
extern int D_00639D10;

void ConvertCameraSetBuffer(int n, S4C *item, char *groups) {
    CamMgr *m1;
    CamMgr *m2;
    int i;
    int j;
    int a;
    int b;
    char *f;
    D_002A5D68[0] = D_005F5D50[D_00639D10].rate;
    m1 = (CamMgr *)D_0063AA78;
    m1->items = (char *)m1 + 0x70;
    m1->pool = (char *)m1 + 0x1E20;
    m1->count = 0;
    f = &m1->flags[0x63];
    for (a = 0x63; a >= 0; a--) {
        *f-- = 0;
    }
    m2 = (CamMgr *)D_0063AA7C;
    m2->items = (char *)m2 + 0x70;
    m2->pool = (char *)m2 + 0x1E20;
    m2->count = 0;
    f = &m2->flags[0x63];
    for (b = 0x63; b >= 0; b--) {
        *f-- = 0;
    }
    for (i = 0; i < n; i++) {
        CameraEdit_add_box(item);
        for (j = item->w[0x38 / 4]; j < item->w[0x3C / 4]; j++) {
            CameraEdit_add_pin(i, groups + j * 0x5C);
        }
        item = (S4C *)((char *)item + 0x4C);
    }
}
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_RotMatrixY(int a0);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0UnitMatrix(void *a0);

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
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_PushMatrix();
        vec[0] = (float)a1;
        vec[1] = zero;
        vec[2] = (float)a0;
        vec[3] = zero;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_RotMatrixY((short)a3);
        p = MatrixDrive_GetMatrix();
        sceVu0ApplyMatrix(vec, p, vec);
        sceVu0Normalize(out, vec);
        MatrixDrive_PopMatrix();
        out[0] = out[0] * (float)(-a5);
        out[2] = out[2] * (float)a5;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_0018F590);
int _CameraEdit_PIN(int *a0, int a1, int a2)
{
  int *p;
  return ((int *) (a0[1] + (a1 * 0x4C)))[0x48 / 4] + (a2 * 0x5C);
}
extern char D_00555020[];
extern void debug_StdPrintfDummy();

int _CameraEdit_add_box(CamMgr *mgr, S4C *src) {
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
    debug_StdPrintfDummy(D_00555020);
    return -1;
}
extern void debug_StdPrintfDummy__pn(char *a0, ...) __asm__("debug_StdPrintfDummy");

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
        debug_StdPrintfDummy__pn(D_00555020, (void *)a1);
    }
    return result;
}
void CameraEdit_Enter(void) {}
