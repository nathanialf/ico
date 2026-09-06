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

extern char D_00554CE0[];
extern int D_0063A450;
extern int curmenu;
void EnterMenu(void *a0, int a1, void *a2) {
    char *m = iosMallocDebug(D_0063A450, 0x78, D_00554CE0, 0xD9);
    iosThreadCreateS(m, 1, a0, m, D_0063A450, 0x1000, 0x17);
    *(int *)(m + 0x74) = a1;
    *(void **)(m + 0x70) = a2;
    iosThreadStart(m);
    curmenu = (int)m;
    if (a2 != 0) {
        iosThreadSleep(a2);
    }
}
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
/* dispBox is defined as a nested function inside
 * CameraEdit_DispBoxType2_Plane below (the listing names it dispBox.152). */
/* Box corner, a VU0 quadword: _InterGV / DrawPolygon / DrawLineG all take
 * 16-byte aligned vectors. */
typedef struct {
    float x, y, z, w;
} CamVtx __attribute__((aligned(16)));

typedef struct {
    char pad00[0x20];
    float cx, cy, cz;   /* 0x20 */
    float sx, sy, sz;   /* 0x2C */
    char pad38[0x4C - 0x38];
} CamBoxF;

extern int *D_0063AA7C;
extern char *matrixptr;
extern int D_002A5C20[6][4];
extern int D_002A5C80[12][2];
extern unsigned int D_002A5CE0[4];
extern unsigned int D_002A5CF0[4];
extern unsigned char D_0063AAB8[4];
extern unsigned char D_0063AAC0[4];
extern unsigned char D_0063AAC8[4];
extern unsigned char D_0063AAD0[4];
extern void sceVu0UnitMatrix(void *m);
extern void func_0025D440(void *dst, void *a, void *b);
extern void before_DrawPolygon(void);
extern void after_DrawPolygon(void);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_SetZWrite(int a);
extern void gif_SetZTest(int a);
extern void _InterGV(void *dst, void *a, void *b, float ta, float tb);
extern void DrawPolygon(void *p0, void *p1, void *p2, void *p3, unsigned char *col, void *m);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void gif_StartPacketPri(int prio);
extern void gif_EndPacket(void);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);

void CameraEdit_DispBoxType2_Plane(int box, int sel) {
    int n;
    CamBoxF *b = (CamBoxF *)(D_0063AA7C[1] + box * 0x4C);
    CamVtx v[8] = {
        { b->cx - b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f },
        { b->cx - b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f },
        { b->cx + b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f },
        { b->cx + b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f },
        { b->cx - b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f },
        { b->cx - b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f },
        { b->cx + b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f },
        { b->cx + b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f }
    };
    {
        float m[4][4];
        unsigned int *c0;
        unsigned int *c1;
        int i;

        /* dispBox is a nested function in the ROM: the parent passes it a
         * static chain in $2 (STATIC_CHAIN_REGNUM), which dispBox spills to
         * 0(sp) and uses to reach the parent's v[], m[][], n and sel. */
        void dispBox(unsigned char *ca, unsigned char *cb)
        {
            float e0[4], e1[4], e2[4], e3[4];
            float g0[4], g1[4], g2[4], g3[4];
            unsigned char *col;
            int j;
            int k;

            for (n = 0; n < 6; n++) {
                col = (n != sel) ? cb : ca;
                for (j = 0; j < 3; j++) {
                    _InterGV(e0, &v[D_002A5C20[n][0]], &v[D_002A5C20[n][1]], (float)j, (float)(3 - j));
                    _InterGV(e1, &v[D_002A5C20[n][0]], &v[D_002A5C20[n][1]], (float)(j + 1), (float)(2 - j));
                    _InterGV(e2, &v[D_002A5C20[n][2]], &v[D_002A5C20[n][3]], (float)j, (float)(3 - j));
                    _InterGV(e3, &v[D_002A5C20[n][2]], &v[D_002A5C20[n][3]], (float)(j + 1), (float)(2 - j));
                    for (k = 0; k < 3; k++) {
                        _InterGV(g0, e0, e2, (float)k, (float)(3 - k));
                        _InterGV(g1, e0, e2, (float)(k + 1), (float)(2 - k));
                        _InterGV(g2, e1, e3, (float)k, (float)(3 - k));
                        _InterGV(g3, e1, e3, (float)(k + 1), (float)(2 - k));
                        DrawPolygon(g0, g1, g2, g3, col, m);
                    }
                }
            }
        }

        sceVu0UnitMatrix(m);
        m[0][0] = m[1][1] = m[2][2] = -1.0f;
        func_0025D440(m, matrixptr + 0x80, m);
        func_0025D440(m, matrixptr + 0xC0, m);
        before_DrawPolygon();
        gif_SetAlpha(1, 5, 0);
        gif_SetZWrite(0);
        gif_SetZTest(1);
        dispBox(D_0063AAB8, D_0063AAC8);
        gif_SetZTest(0);
        dispBox(D_0063AAC0, D_0063AAD0);
        after_DrawPolygon();
        c0 = D_002A5CE0;
        c1 = D_002A5CF0;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_ScaleMatrix(-1.0f, -1.0f, -1.0f);
        gif_StartPacketPri(11);
        gif_SetAlpha(1, 5, 0);
        gif_SetZWrite(0);
        gif_SetZTest(0);
        for (i = 0; i < 12; i++) {
            DrawLineG(&v[D_002A5C80[i][0]], c1, &v[D_002A5C80[i][1]], c1, 0);
        }
        gif_SetZTest(1);
        for (i = 0; i < 12; i++) {
            DrawLineG(&v[D_002A5C80[i][0]], c0, &v[D_002A5C80[i][1]], c0, 0);
        }
        gif_EndPacket();
    }
}
extern void dispCameraGroupType2(int a0, int a1);

void CameraEdit_DispBoxType2(int a0, int a1) {
    dispCameraGroupType2(a0, a1 & 0xFF);
}
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_0018CDC0);
extern int print_y;
extern int D_0028F94C[];
extern char D_002AD010[];
extern StageParam D_005F5D50[];
extern int stage_no;
extern int *D_0063AA7C;
extern void iosThreadWakeup(void *thread);
extern void saveEditedDataBinary(int a0, int a1, int a2);

void wakeup_cameraedit(void) {
    print_y = 50;
    if (curmenu != 0) {
        iosThreadWakeup((void *)curmenu);
        if (D_0028F94C[0] & 0x400) {
            saveEditedDataBinary(
                (int)&D_002AD010[D_005F5D50[stage_no].camSetId * 0x20],
                D_0063AA7C[1],
                D_0063AA7C[0]);
        }
    }
}
extern void EnterMenu(void *a0, int a1, void *a2);
extern void func_0018CDC0(void);

void test_camedit(void) {
    EnterMenu((void *)func_0018CDC0, 0, 0);
}
extern char D_00555038[];
extern void debug_StdPrintfDummy();

static inline void _CameraEdit_free_box_pool(CamMgr *mgr, int idx) {
    S4C *box = (S4C *)(idx * 0x4C + (int)mgr->items);
    char *p = mgr->pool;
    int i;
    for (i = 0; i < 0x64; i++) {
        if (p == *(char **)&box->w[0x48 / 4]) {
            mgr->flags[i] = 0;
        }
        p += 0x23F0;
    }
}

void _CameraEdit_del_box(CamMgr *mgr, int idx) {
    if (mgr->count <= 0) {
        debug_StdPrintfDummy(D_00555038);
        return;
    }
    _CameraEdit_free_box_pool(mgr, idx);
    while (idx < mgr->count) {
        *(S4C *)(mgr->items + idx * 0x4C) = *(S4C *)(mgr->items + idx * 0x4C + 0x4C);
        idx++;
    }
    mgr->count = mgr->count - 1;
}
static inline S4C *_CameraEdit_BOX_p(CamMgr *mgr, int i) {
    return (S4C *)(i * 0x4C + (int)mgr->items);
}
static inline S5C *_CameraEdit_PIN_p(CamMgr *mgr, int i, int j) {
    return (S5C *)(_CameraEdit_BOX_p(mgr, i)->w[0x48 / 4] + j * 0x5C);
}

void _CameraEdit_del_pin(CamMgr *mgr, int box, int pin) {
    S5C *p;
    if (_CameraEdit_BOX_p(mgr, box)->w[0x3C / 4] <= 0) {
        debug_StdPrintfDummy(D_00555038);
        return;
    }
    for (p = _CameraEdit_PIN_p(mgr, box, pin);
         p < _CameraEdit_PIN_p(mgr, box, _CameraEdit_BOX_p(mgr, box)->w[0x3C / 4]);
         p++) {
        *p = p[1];
    }
    _CameraEdit_BOX_p(mgr, box)->w[0x3C / 4] = _CameraEdit_BOX_p(mgr, box)->w[0x3C / 4] - 1;
}
extern char D_00555020[];
extern int *D_0063AA78;
extern int *D_0063AA7C;

static inline char *_CameraEdit_alloc_pool(CamMgr *mgr) {
    int i;
    for (i = 0; i < 0x64; i++) {
        if (mgr->flags[i] == 0) {
            mgr->flags[i] = 1;
            return mgr->pool + i * 0x23F0;
        }
    }
    return 0;
}

inline int _CameraEdit_add_box(CamMgr *mgr, S4C *src) {
    int result = -1;
    char *p;
    S4C *dst;
    if (mgr->count < 0x64) {
        p = _CameraEdit_alloc_pool(mgr);
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

int CameraEdit_add_box(S4C *src) {
    _CameraEdit_add_box((CamMgr *)D_0063AA78, src);
    return _CameraEdit_add_box((CamMgr *)D_0063AA7C, src);
}
extern char D_00555020[];
extern int *D_0063AA78;
extern int *D_0063AA7C;

inline int _CameraEdit_add_pin(void *a0, int a1, S5C *src) {
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
        debug_StdPrintfDummy(D_00555020);
    }
    return result;
}

int CameraEdit_add_pin(int box, char *src) {
    _CameraEdit_add_pin(D_0063AA78, box, (S5C *)src);
    return _CameraEdit_add_pin(D_0063AA7C, box, (S5C *)src);
}
extern int *D_0063AA78;
extern int *D_0063AA7C;
extern void _CameraEdit_del_box(CamMgr *mgr, int idx);

void CameraEdit_del_box(int a0) {
    _CameraEdit_del_box((CamMgr *)D_0063AA78, a0);
    _CameraEdit_del_box((CamMgr *)D_0063AA7C, a0);
}
extern void _CameraEdit_del_pin(CamMgr *mgr, int box, int pin);

void CameraEdit_del_pin(int a0, int a1)
{
    _CameraEdit_del_pin((CamMgr *)D_0063AA78, a0, a1);
    _CameraEdit_del_pin((CamMgr *)D_0063AA7C, a0, a1);
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
extern int curmenu;
extern char exit_f;

void InitCameraEditor(void) {
    curmenu = 0;
    exit_f = 0;
}
extern void CameraSetMode(int a0);
extern unsigned char D_0063AB40__pn __asm__("exit_f");
extern int D_0063B13C;
extern void wakeup_cameraedit(void);
extern void test_camedit(void);

int debug_CameraEditor(void) {
    D_0063B13C = 1;
    if (curmenu == 0) {
        test_camedit();
    }
    wakeup_cameraedit();
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
typedef union {
    unsigned int c[4];
    unsigned long long w[2];
} CamColor;

extern CamColor D_00554E70;
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void gif_StartPacketPri(int prio);
extern void gif_EndPacket(void);
extern void DrawLine(float *from, float *to, CamColor *color, int z);

static inline void dispPinRange(int box, int from, int to) {
    CamColor col = D_00554E70;
    int i;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    ((float (*)[4])MatrixDrive_GetMatrix())[0][0] =
        ((float (*)[4])MatrixDrive_GetMatrix())[1][1] =
            ((float (*)[4])MatrixDrive_GetMatrix())[2][2] = -1.0f;
    gif_StartPacketPri(11);
    for (i = from; i < to; i++) {
        float a[3] = { ((float *)CameraEdit_PIN(box, i))[0],
                       ((float *)CameraEdit_PIN(box, i))[1],
                       ((float *)CameraEdit_PIN(box, i))[2] };
        float b[3] = { ((float *)CameraEdit_PIN(box, i))[3],
                       ((float *)CameraEdit_PIN(box, i))[4],
                       ((float *)CameraEdit_PIN(box, i))[5] };
        DrawLine(a, b, &col, -1);
    }
    gif_EndPacket();
}

void CameraEdit_DispPin(int box, int pin) {
    dispPinRange(box, pin, pin + 1);
}
extern int CameraEdit_add_box(S4C *a0);
extern int CameraEdit_add_pin(int a0, char *a1);
extern float D_002A5D68[];
extern StageParam D_005F5D50[];
extern int stage_no;

void ConvertCameraSetBuffer(int n, S4C *item, char *groups) {
    CamMgr *m1;
    CamMgr *m2;
    int i;
    int j;
    int a;
    int b;
    char *f;
    D_002A5D68[0] = D_005F5D50[stage_no].rate;
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

inline void CameraEdit_Enter(void) {}
