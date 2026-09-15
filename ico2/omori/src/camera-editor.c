#include "common.h"

typedef struct {
    int w[23];
} S5C;

typedef struct CamMgr {
    int count;        /* 0x00 */
    char *items;      /* 0x04 */
    char *pool;       /* 0x08 */
    char flags[0x64]; /* 0x0C */
} CamMgr;

typedef struct StageParam {
    char pad0[0x118];
    int camSetId; /* 0x118 */
    char pad11c[0x184 - 0x11C];
    float rate; /* 0x184 */
    char pad188[0x194 - 0x188];
} StageParam;

typedef struct {
    int w[19];
} S4C;

extern char D_00554CE0[];
extern int D_0063A450;
extern int curmenu;

void EnterMenu(void *a0, int a1, void *a2)
{
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

/* the 0x10-byte camera-set binary header */
typedef struct {
    int magic;
    int version;
    int num;
    int pins;
} CamSetBinHdr;

extern char D_00554CF8[];
extern char D_00554D30[];
extern char D_00554D40[];
extern char D_00554D50[];
extern char D_00554D60[];
extern char D_00554D90[];
extern char D_00554CE0[];
extern int GetSizeOfCameraSetBinary(S4C *p, int n);
extern int CameraEdit_PIN_NUMBER_ALL(int *a0, int a1);
extern void MakeCameraSetBinary(S4C *src, int count, S4C *dst);
extern void debug_closeLog(void);
extern void debug_openLog(void);
extern void debug_StdPrintfDummy();
extern void sprintf();
extern int debugSceOpen(void *path, int mode);
extern int debugSceClose(int fd);
extern void sceWrite(int fd, void *buf, int len);
extern void iosFree(void *p);

/* SRCFILE.TXT rows 369-388: saveEditedDataBinary inlines this, which is why
   the ROM folds the path buffer's frame address straight into $a0 at both the
   sprintf and the debugSceOpen instead of holding it in a register */
static inline void writeCameraSetFile(int no, void *buf, int size)
{
    char path[0x80];

    debug_closeLog();
    debug_StdPrintfDummy(D_00554CF8);
    debug_StdPrintfDummy(D_00554D30, no);
    debug_StdPrintfDummy(D_00554D40, size);
    sprintf(path, D_00554D50, no);
    if (debugSceOpen(path, 0x202) < 0) {
        debug_StdPrintfDummy(D_00554D60);
    } else {
        sceWrite(0, buf, size);
        debugSceClose(0);
        debug_StdPrintfDummy(D_00554D90);
    }
    debug_openLog();
}

void saveEditedDataBinary(int no, int a1, int a2)
{
    /* the header record the 2001 source still declared: the body writes the
       four words straight into buf at rows 407-410 and never reads it, but it
       still sets the frame (SRCFILE.TXT rows 364-368, 370, 374, 376, 379, 382
       and 386-387 carry no instructions) */
    CamSetBinHdr hdr;
    int size;
    int *buf;
    S4C *data;

    size = GetSizeOfCameraSetBinary((S4C *)a1, a2) + 0x10;
    buf = (int *)iosMallocDebug(D_0063A450, size, D_00554CE0, 0x194);
    data = (S4C *)(buf + 4);
    buf[2] = a2;
    buf[0] = 0x1234;
    buf[1] = 3;
    buf[3] = CameraEdit_PIN_NUMBER_ALL((int *)a1, a2);
    MakeCameraSetBinary((S4C *)a1, a2, data);
    writeCameraSetFile(no, buf, size);
    iosFree(buf);
}

INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/camera-editor", saveEditedData);

extern void gif_SetGsReg(int code, long data);

void gif_test(int *a0, int *a1, int *a2, unsigned char *a3)
{
    gif_SetGsReg(0, 3);
    gif_SetGsReg(1, (long)a3[0] | ((long)a3[1] << 8) | ((long)a3[2] << 16) | ((long)a3[3] << 24));
    gif_SetGsReg(4, (long)a0[0] | ((long)a0[1] << 16) | ((long)a0[2] << 32));
    gif_SetGsReg(4, (long)a1[0] | ((long)a1[1] << 16) | ((long)a1[2] << 32));
    gif_SetGsReg(4, (long)a2[0] | ((long)a2[1] << 16) | ((long)a2[2] << 32));
}

/* box corner quadword: _InterGV / DrawPolygon / do_DrawLine take 16-byte
   aligned vectors */
typedef struct {
    float x, y, z, w;
} BoxVtx __attribute__((aligned(16)));

typedef struct {
    float x, y, z;
} BoxVec;

/* the two index tables and the line colour are .rodata constructor templates
   the compiler shares with DispCameraGroup, so they are read as objects */
typedef struct {
    int e[6][4];
} BoxIdx6;

typedef struct {
    int e[12][2];
} BoxIdx12;

typedef struct {
    unsigned char r, g, b, a;
} BoxCol;

typedef union {
    unsigned int c[4];
    unsigned long long w[2];
} BoxCol4;

extern const BoxIdx6 D_00554E80;
extern const BoxIdx12 D_00554EE0;
extern const BoxCol4 D_00554F40;
extern BoxCol D_0063AAA0[];
extern char *matrixptr;
extern void sceVu0MulMatrix(void *dst, void *a, void *b);
extern void before_DrawPolygon(void);
extern void _InterGV(void *dst, void *a, void *b, float ta, float tb);
extern void DrawPolygon(void *p0, void *p1, void *p2, void *p3, unsigned char *col, void *m);
extern void after_DrawPolygon(void);
extern void before_DrawLine(void *m);
extern void do_DrawLine(void *p0, void *p1, void *col, int f);
extern void after_DrawLine(void);

void DebugDispBox(BoxVec *c, BoxVec *s)
{
    int n;
    int j;
    int k;
    int i;
    BoxVtx v[8] = {{c->x - s->x, c->y - s->y, c->z - s->z, 1.0f},
                   {c->x - s->x, c->y - s->y, c->z + s->z, 1.0f},
                   {c->x + s->x, c->y - s->y, c->z - s->z, 1.0f},
                   {c->x + s->x, c->y - s->y, c->z + s->z, 1.0f},
                   {c->x - s->x, c->y + s->y, c->z - s->z, 1.0f},
                   {c->x - s->x, c->y + s->y, c->z + s->z, 1.0f},
                   {c->x + s->x, c->y + s->y, c->z - s->z, 1.0f},
                   {c->x + s->x, c->y + s->y, c->z + s->z, 1.0f}};
    BoxIdx6 idx6;
    BoxCol col;
    BoxCol4 col2;
    float m[4][4];
    float e0[4];
    float e1[4];
    float e2[4];
    float e3[4];
    float g0[4];
    float g1[4];
    float g2[4];
    float g3[4];
    BoxIdx12 idx12;
    float m2[4][4];

    idx6 = D_00554E80;
    sceVu0UnitMatrix(m);
    sceVu0MulMatrix(m, matrixptr + 0x80, m);
    sceVu0MulMatrix(m, matrixptr + 0xC0, m);
    before_DrawPolygon();
    for (n = 0; n < 6; n++) {
        col = D_0063AAA0[0];
        col.r = 64;
        col.g = 64;
        col.b = 64;
        col.a = 32;
        for (j = 0; j < 3; j++) {
            _InterGV(e0, &v[idx6.e[n][0]], &v[idx6.e[n][1]], (float)j, (float)(3 - j));
            _InterGV(e1, &v[idx6.e[n][0]], &v[idx6.e[n][1]], (float)(j + 1), (float)(2 - j));
            _InterGV(e2, &v[idx6.e[n][2]], &v[idx6.e[n][3]], (float)j, (float)(3 - j));
            _InterGV(e3, &v[idx6.e[n][2]], &v[idx6.e[n][3]], (float)(j + 1), (float)(2 - j));
            for (k = 0; k < 3; k++) {
                _InterGV(g0, e0, e2, (float)k, (float)(3 - k));
                _InterGV(g1, e0, e2, (float)(k + 1), (float)(2 - k));
                _InterGV(g2, e1, e3, (float)k, (float)(3 - k));
                _InterGV(g3, e1, e3, (float)(k + 1), (float)(2 - k));
                DrawPolygon(g0, g1, g2, g3, (unsigned char *)&col, m);
            }
        }
    }
    after_DrawPolygon();
    idx12 = D_00554EE0;
    col2 = D_00554F40;
    sceVu0UnitMatrix(m2);
    m2[0][0] = m2[1][1] = m2[2][2] = -1.0f;
    before_DrawLine(m);
    for (i = 0; i < 12; i++) {
        do_DrawLine(&v[idx12.e[i][0]], &v[idx12.e[i][1]], &col2, -1);
    }
    after_DrawLine();
}

/* the camera box record: centre and half-size at 0x20 and 0x2C */
typedef struct {
    char pad00[0x20];
    float cx, cy, cz; /* 0x20 */
    float sx, sy, sz; /* 0x2C */
    char pad38[0x4C - 0x38];
} BoxRec;

extern int *D_0063AA7C;

void DispCameraGroup(int box, unsigned char sel)
{
    int n;
    int j;
    int k;
    int i;
    BoxRec *b = (BoxRec *)(D_0063AA7C[1] + box * 0x4C);
    BoxVtx v[8] = {{b->cx - b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f},
                   {b->cx - b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f},
                   {b->cx + b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f},
                   {b->cx + b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f},
                   {b->cx - b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f},
                   {b->cx - b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f},
                   {b->cx + b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f},
                   {b->cx + b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f}};
    BoxIdx6 idx6;
    BoxCol col;
    BoxCol4 col2;
    float m[4][4];
    float e0[4];
    float e1[4];
    float e2[4];
    float e3[4];
    float g0[4];
    float g1[4];
    float g2[4];
    float g3[4];
    BoxIdx12 idx12;
    float m2[4][4];

    idx6 = D_00554E80;
    sceVu0UnitMatrix(m);
    m[0][0] = m[1][1] = m[2][2] = -1.0f;
    sceVu0MulMatrix(m, matrixptr + 0x80, m);
    sceVu0MulMatrix(m, matrixptr + 0xC0, m);
    before_DrawPolygon();
    for (n = 0; n < 6; n++) {
        col = D_0063AAA0[0];
        if (sel == 0) {
            col.r = 64;
            col.g = 64;
            col.b = 64;
            col.a = 32;
        }
        for (j = 0; j < 3; j++) {
            _InterGV(e0, &v[idx6.e[n][0]], &v[idx6.e[n][1]], (float)j, (float)(3 - j));
            _InterGV(e1, &v[idx6.e[n][0]], &v[idx6.e[n][1]], (float)(j + 1), (float)(2 - j));
            _InterGV(e2, &v[idx6.e[n][2]], &v[idx6.e[n][3]], (float)j, (float)(3 - j));
            _InterGV(e3, &v[idx6.e[n][2]], &v[idx6.e[n][3]], (float)(j + 1), (float)(2 - j));
            for (k = 0; k < 3; k++) {
                _InterGV(g0, e0, e2, (float)k, (float)(3 - k));
                _InterGV(g1, e0, e2, (float)(k + 1), (float)(2 - k));
                _InterGV(g2, e1, e3, (float)k, (float)(3 - k));
                _InterGV(g3, e1, e3, (float)(k + 1), (float)(2 - k));
                DrawPolygon(g0, g1, g2, g3, (unsigned char *)&col, m);
            }
        }
    }
    after_DrawPolygon();
    idx12 = D_00554EE0;
    col2 = D_00554F40;
    sceVu0UnitMatrix(m2);
    m2[0][0] = m2[1][1] = m2[2][2] = -1.0f;
    before_DrawLine(m);
    for (i = 0; i < 12; i++) {
        do_DrawLine(&v[idx12.e[i][0]], &v[idx12.e[i][1]], &col2, -1);
    }
    after_DrawLine();
}

/* a VU0 quadword: DrawLineG takes 16-byte aligned vectors */
typedef struct {
    float x, y, z, w;
} ArrowVtx __attribute__((aligned(16)));

extern ArrowVtx D_0028FEF0;
extern ArrowVtx D_002A5A10;
extern ArrowVtx D_002A5A20;
extern ArrowVtx D_002A5A30;
extern ArrowVtx D_002A5A40;
extern ArrowVtx D_002A5A50;
extern ArrowVtx D_002A5A60;

void drawXZArrow(void *col, int f, float z)
{
    ArrowVtx v0 = {-25.0f, 0.0f, -z, 1.0f};
    ArrowVtx v1 = {25.0f, 0.0f, -z, 1.0f};

    DrawLineG(&D_0028FEF0, col, &D_002A5A40, col, f);
    DrawLineG(&D_0028FEF0, col, &D_002A5A10, col, f);
    DrawLineG(&D_002A5A50, col, &D_002A5A40, col, f);
    DrawLineG(&D_002A5A20, col, &D_002A5A10, col, f);
    DrawLineG(&D_002A5A30, col, &v0, col, f);
    DrawLineG(&D_002A5A60, col, &v1, col, f);
    DrawLineG(&v0, col, &v1, col, f);
}

/* one axis of the arrow table: the tip and tail vectors of the arrow */
typedef struct {
    float tip[4];
    float tail[4];
} AxisPair;

extern AxisPair D_002A5A80[];
extern ArrowVtx D_002A5A70;
extern char *matrixptr;
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
extern void MatrixDrive_TransMatrixV(void *v);
extern void MatrixDrive_TurnObjectMatrix(float x, float y, float z);
extern void MatrixDrive_RotMatrixZ(short a);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void sceVu0Normalize(void *dst, void *src);
extern int GetTableArcTan2(float y, float x);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_SetZTest(int a);

void DispAxisArrow(int mask, void *col)
{
    float v[4];
    float m0[4][4];
    float n[4];
    float m1[4][4];
    AxisPair *ax;
    int i;

    if (mask <= 0) {
        return;
    }
    if (mask >= 3) {
        if (mask >= 6) {
            return;
        }
        if (mask < 4) {
            return;
        }
    }
    {
        MatrixDrive_SetTransposeMatrix(m0, matrixptr + 0x80);
        sceVu0ApplyMatrix(v, m0, &D_002A5A70);

        gif_StartPacketPri(11);
        gif_SetAlpha(1, 5, 0);
        gif_SetZTest(0);

        ax = D_002A5A80;
        for (i = 0; i < 3; i++) {
            if ((mask >> i) & 1) {
                sceVu0UnitMatrix(MatrixDrive_GetMatrix());
                MatrixDrive_TransMatrixV(v);
                MatrixDrive_TurnObjectMatrix(-(ax->tip[0] - ax->tail[0]), ax->tip[1] - ax->tail[1],
                                             ax->tip[2] - ax->tail[2]);
                MatrixDrive_SetTransposeMatrix(m1, MatrixDrive_GetMatrix());
                sceVu0ApplyMatrix(n, matrixptr + 0x80, v);
                n[3] = 0.0f;
                sceVu0ApplyMatrix(n, m0, n);
                sceVu0ApplyMatrix(n, m1, n);
                sceVu0Normalize(n, n);
                n[2] = 0.0f;
                sceVu0Normalize(n, n);
                MatrixDrive_RotMatrixZ((short)-GetTableArcTan2(n[0], n[1]));
                MatrixDrive_TransMatrix(0.0f, 0.0f, 200.0f);
                drawXZArrow(col, -1, 400.0f);
            }
            ax++;
        }
        gif_EndPacket();
    }
}

extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void gif_SetZWrite(int a);
extern void CopyIVector(void *dst, void *src);
extern float GetPointDistance(void *a, void *b);
extern int D_002A5AE0[];
extern int D_002A5AF0[];
extern int D_002A5B00[];
extern int D_002A5B10[];

void dispCameraPinType2(int box, int from, int to, int type)
{
    float m0[4][4];
    int *c1;
    int *c2;
    int i;

    c1 = type ? D_002A5AE0 : D_002A5AF0;
    c2 = type ? D_002A5B00 : D_002A5B10;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_ScaleMatrix(-1.0f, -1.0f, -1.0f);
    MatrixDrive_SetTransposeMatrix(m0, matrixptr + 0x80);
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 0);
    gif_SetZWrite(1);
    for (i = from; i < to; i++) {
        int c1v[4];
        int c2v[4];
        ArrowVtx a = {((float *)CameraEdit_PIN(box, i))[0], ((float *)CameraEdit_PIN(box, i))[1],
                      ((float *)CameraEdit_PIN(box, i))[2], 0.0f};
        ArrowVtx b = {((float *)CameraEdit_PIN(box, i))[3], ((float *)CameraEdit_PIN(box, i))[4],
                      ((float *)CameraEdit_PIN(box, i))[5], 0.0f};
        float n[4];
        float m1[4][4];
        float t;

        CopyIVector(c1v, c1);
        CopyIVector(c2v, c2);
        MatrixDrive_TransMatrixV(&b);
        MatrixDrive_TurnObjectMatrix(-(b.x - a.x), b.y - a.y, b.z - a.z);
        {
            ArrowVtx d = {-((float *)CameraEdit_PIN(box, i))[3],
                          -((float *)CameraEdit_PIN(box, i))[4],
                          -((float *)CameraEdit_PIN(box, i))[5], 1.0f};

            MatrixDrive_SetTransposeMatrix(m1, MatrixDrive_GetMatrix());
            sceVu0ApplyMatrix(n, matrixptr + 0x80, &d);
            n[3] = 0.0f;
            sceVu0ApplyMatrix(n, m0, n);
            sceVu0ApplyMatrix(n, m1, n);
            sceVu0Normalize(n, n);
            t = (n[2] < 0.0f ? n[2] + 1.0f : 1.0f - n[2]) * 1000.0f;
            t = 1.0f < t ? 1.0f : t;
            c1v[0] = (int)((float)c1v[0] * t);
            c1v[1] = (int)((float)c1v[1] * t);
            c1v[2] = (int)((float)c1v[2] * t);
            c2v[0] = (int)((float)c2v[0] * t);
            c2v[1] = (int)((float)c2v[1] * t);
            c2v[2] = (int)((float)c2v[2] * t);
            n[2] = 0.0f;
            sceVu0Normalize(n, n);
            MatrixDrive_RotMatrixZ((short)-GetTableArcTan2(n[0], n[1]));
            gif_SetZTest(1);
            drawXZArrow(c1v, 0, GetPointDistance(&a, &b));
            gif_SetZTest(0);
            drawXZArrow(c2v, 0, GetPointDistance(&a, &b));
        }
    }
    gif_EndPacket();
}

extern void dispCameraPinType2(int a0, int a1, int a2, int a3);

void CameraEdit_DispPinType2(int a0, int a1, int a2)
{
    dispCameraPinType2(a0, a1, a1 + 1, a2);
}

extern unsigned char D_0063AAA8[4];
extern unsigned char D_0063AAB0[4];
extern int D_002A5B20[6][4];
extern int D_002A5B80[12][2];
extern unsigned int D_002A5BE0[4];
extern unsigned int D_002A5BF0[4];
extern unsigned int D_002A5C00[4];
extern unsigned int D_002A5C10[4];

void dispCameraGroupType2(int box, unsigned char sel)
{
    int n;
    int j;
    int k;
    int i;
    unsigned char *col;
    unsigned int *c0;
    unsigned int *c1;
    BoxRec *b = (BoxRec *)(D_0063AA7C[1] + box * 0x4C);
    BoxVtx v[8] = {{b->cx - b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f},
                   {b->cx - b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f},
                   {b->cx + b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f},
                   {b->cx + b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f},
                   {b->cx - b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f},
                   {b->cx - b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f},
                   {b->cx + b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f},
                   {b->cx + b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f}};
    float m[4][4];
    float e0[4];
    float e1[4];
    float e2[4];
    float e3[4];
    float g0[4];
    float g1[4];
    float g2[4];
    float g3[4];

    sceVu0UnitMatrix(m);
    m[0][0] = m[1][1] = m[2][2] = -1.0f;
    sceVu0MulMatrix(m, matrixptr + 0x80, m);
    sceVu0MulMatrix(m, matrixptr + 0xC0, m);
    before_DrawPolygon();
    gif_SetAlpha(1, 5, 0);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    for (n = 0; n < 6; n++) {
        col = sel == 0 ? D_0063AAB0 : D_0063AAA8;
        for (j = 0; j < 3; j++) {
            _InterGV(e0, &v[D_002A5B20[n][0]], &v[D_002A5B20[n][1]], (float)j, (float)(3 - j));
            _InterGV(e1, &v[D_002A5B20[n][0]], &v[D_002A5B20[n][1]], (float)(j + 1),
                     (float)(2 - j));
            _InterGV(e2, &v[D_002A5B20[n][2]], &v[D_002A5B20[n][3]], (float)j, (float)(3 - j));
            _InterGV(e3, &v[D_002A5B20[n][2]], &v[D_002A5B20[n][3]], (float)(j + 1),
                     (float)(2 - j));
            for (k = 0; k < 3; k++) {
                _InterGV(g0, e0, e2, (float)k, (float)(3 - k));
                _InterGV(g1, e0, e2, (float)(k + 1), (float)(2 - k));
                _InterGV(g2, e1, e3, (float)k, (float)(3 - k));
                _InterGV(g3, e1, e3, (float)(k + 1), (float)(2 - k));
                DrawPolygon(g0, g1, g2, g3, col, m);
            }
        }
    }
    after_DrawPolygon();
    c0 = D_002A5BE0;
    c1 = D_002A5BF0;
    if (sel == 0) {
        c0 = D_002A5C00;
        c1 = D_002A5C10;
    }
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_ScaleMatrix(-1.0f, -1.0f, -1.0f);
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 0);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    for (i = 0; i < 12; i++) {
        DrawLineG(&v[D_002A5B80[i][0]], c1, &v[D_002A5B80[i][1]], c1, 0);
    }
    gif_SetZTest(1);
    for (i = 0; i < 12; i++) {
        DrawLineG(&v[D_002A5B80[i][0]], c0, &v[D_002A5B80[i][1]], c0, 0);
    }
    gif_EndPacket();
}

/* dispBox is defined as a nested function inside
 * CameraEdit_DispBoxType2_Plane below (the listing names it dispBox.152). */
/* Box corner, a VU0 quadword: _InterGV / DrawPolygon / DrawLineG all take
 * 16-byte aligned vectors. */
typedef struct {
    float x, y, z, w;
} CamVtx __attribute__((aligned(16)));

typedef struct {
    char pad00[0x20];
    float cx, cy, cz; /* 0x20 */
    float sx, sy, sz; /* 0x2C */
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
extern void sceVu0MulMatrix(void *dst, void *a, void *b);
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

void CameraEdit_DispBoxType2_Plane(int box, int sel)
{
    int n;
    CamBoxF *b = (CamBoxF *)(D_0063AA7C[1] + box * 0x4C);
    CamVtx v[8] = {{b->cx - b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f},
                   {b->cx - b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f},
                   {b->cx + b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f},
                   {b->cx + b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f},
                   {b->cx - b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f},
                   {b->cx - b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f},
                   {b->cx + b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f},
                   {b->cx + b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f}};
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
                    _InterGV(e0, &v[D_002A5C20[n][0]], &v[D_002A5C20[n][1]], (float)j,
                             (float)(3 - j));
                    _InterGV(e1, &v[D_002A5C20[n][0]], &v[D_002A5C20[n][1]], (float)(j + 1),
                             (float)(2 - j));
                    _InterGV(e2, &v[D_002A5C20[n][2]], &v[D_002A5C20[n][3]], (float)j,
                             (float)(3 - j));
                    _InterGV(e3, &v[D_002A5C20[n][2]], &v[D_002A5C20[n][3]], (float)(j + 1),
                             (float)(2 - j));
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
        sceVu0MulMatrix(m, matrixptr + 0x80, m);
        sceVu0MulMatrix(m, matrixptr + 0xC0, m);
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

extern void dispCameraGroupType2(int a0, unsigned char a1);

void CameraEdit_DispBoxType2(int a0, int a1)
{
    dispCameraGroupType2(a0, a1 & 0xFF);
}

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4 */
typedef struct Pad {
    int unk00;
    int trg;
    int unk08;
    int rep;
    char unk10[0x44];
    unsigned char ana[4];
} Pad;

extern Pad D_0028F8F0[];
extern char D_0063AAD8[];
extern char D_0063AAE0[];
extern int D_0063B13C;
extern int print_y;
extern unsigned char exit_f;
extern int *D_0063AA7C;
extern int CameraEdit_BOX_NUMBER(void);
extern void DispCameraGroup(int box, unsigned char sel);
extern void debug_Printf(int x, int y, unsigned int col, char *fmt, ...);
extern void iosThreadSleep(void *th);
extern void EnterMenu(void *a0, int a1, void *a2);
extern void menuGroupEdit(char *m);
extern void menuPinSelect(char *m);

void menuGroupSelect(char *m)
{
    Pad *pad;
    int *box = (int *)(m + 0x74);
    int i;
    int n;
    int start;
    int end;

    iosThreadSleep(m);

    pad = D_0028F8F0;
    while (1) {
        if (pad[1].trg & 0x1000) {
            (*(int *)(m + 0x74))--;
        }
        if (pad[1].trg & 0x4000) {
            (*(int *)(m + 0x74))++;
        }
        for (i = 0; i < CameraEdit_BOX_NUMBER(); i++) {
            DispCameraGroup(i, i == *box);
        }
        *box = (*box < 0) ? CameraEdit_BOX_NUMBER() - 1
                          : ((*box < CameraEdit_BOX_NUMBER()) ? *box : 0);
        n = *box - 5;
        start = (n < 0) ? 0 : ((CameraEdit_BOX_NUMBER() < n) ? CameraEdit_BOX_NUMBER() : n);
        n = start + 10;
        end = (n < 0) ? 0 : ((CameraEdit_BOX_NUMBER() < n) ? CameraEdit_BOX_NUMBER() : n);
        for (i = start; i < end; i++) {
            if (i == *box) {
                if (D_0063B13C & 1) {
                    print_y += 10;
                    debug_Printf(40, print_y, 0xFFFFFF00, D_0063AAD8, D_0063AA7C[1] + i * 0x4C);
                }
            } else {
                if (D_0063B13C & 1) {
                    print_y += 10;
                    debug_Printf(40, print_y, 0xFFFFFF00, D_0063AAE0, D_0063AA7C[1] + i * 0x4C);
                }
            }
        }
        if (pad[1].trg & 0x20) {
            EnterMenu(menuGroupEdit, *box, m);
        } else if (pad[1].trg & 0x80) {
            EnterMenu(menuPinSelect, *box, m);
        } else if (pad[1].trg & 0x10) {
            exit_f = 1;
        }
        iosThreadSleep(m);
    }
}

/* one row of the group editor: the live value, the step the pad applies to it,
   and whether the row steps on the trigger edge or on the held level */
typedef struct {
    int val;
    int step;
    int mode;
    char *name;
} EditItem;

/* the camera box record as the group editor sees it: the centre and half-size
   floats DispCameraGroup also reads, plus the type word at 0x44 */
typedef struct {
    char pad00[0x20];
    float cx, cy, cz; /* 0x20 */
    float sx, sy, sz; /* 0x2C */
    char pad38[0x44 - 0x38];
    int type; /* 0x44 */
    char pad48[0x4C - 0x48];
} EditRec;

extern char D_00554F50[];
extern char D_00554F60[];
extern char D_00554F70[];
extern char D_00554F80[];
extern char D_00554F90[];
extern char D_0063AAE8[];
extern char D_0063AAF0[];
extern char D_0063AAF8[];
extern char D_0063AB00[];
extern int curmenu;
extern void iosThreadDestroy(void *th);

void menuGroupEdit(char *m)
{
    EditRec *rec = (EditRec *)(D_0063AA7C[1] + *(int *)(m + 0x74) * 0x4C);
    int cur = 0;
    int i;

    iosThreadSleep(m);

    while (1) {
        if (D_0028F8F0[1].trg & 0x1000) {
            cur--;
        }
        if (D_0028F8F0[1].trg & 0x4000) {
            cur++;
        }
        cur = (cur < 0) ? 7 : ((cur > 7) ? 0 : cur);

        for (i = 0; i < CameraEdit_BOX_NUMBER(); i++) {
            DispCameraGroup(i, i == *(int *)(m + 0x74));
        }
        {
            EditItem item[7] = {
                {rec->type, 1, 1, D_0063AAE8},     {(int)rec->cx, 10, 0, D_00554F50},
                {(int)rec->cy, 10, 0, D_00554F60}, {(int)rec->cz, 10, 0, D_00554F70},
                {(int)rec->sx, 10, 0, D_0063AAF0}, {(int)rec->sy, 10, 0, D_0063AAF8},
                {(int)rec->sz, 10, 0, D_0063AB00}};
            int d;

            if (item[cur].mode) {
                if (D_0028F8F0[1].trg & 0x2000) {
                    d = 1;
                } else {
                    d = 0;
                }
                if (D_0028F8F0[1].trg & 0x8000) {
                    d = -1;
                }
            } else {
                if (D_0028F8F0[1].unk00 & 0x2000) {
                    d = 1;
                } else {
                    d = 0;
                }
                if (D_0028F8F0[1].unk00 & 0x8000) {
                    d = -1;
                }
            }
            d = d * item[cur].step;
            item[cur].val += d;
            for (i = 0; i < 7; i++) {
                if (i == cur) {
                    if (D_0063B13C & 1) {
                        print_y += 10;
                        debug_Printf(40, print_y, 0xFFFFFF00, D_00554F80, item[i].name,
                                     item[i].val);
                    }
                } else {
                    if (D_0063B13C & 1) {
                        print_y += 10;
                        debug_Printf(40, print_y, 0xFFFFFF00, D_00554F90, item[i].name,
                                     item[i].val);
                    }
                }
            }
            rec->type = item[0].val;

            rec->cx = (float)item[1].val;
            rec->cy = (float)item[2].val;
            rec->cz = (float)item[3].val;
            rec->sx = (float)item[4].val;
            rec->sy = (float)item[5].val;
            rec->sz = (float)item[6].val;
        }
        if (D_0028F8F0[1].trg & 0x10) {
            curmenu = *(int *)(m + 0x70);
            iosThreadDestroy(m);
        }
        iosThreadSleep(m);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/camera-editor", menuPinSelect);
INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/camera-editor", menuPinEdit);

extern int print_y;
extern int D_0028F94C[];
extern char D_002AD010[];
extern StageParam D_005F5D50[];
extern int stage_no;
extern int *D_0063AA7C;
extern void iosThreadWakeup(void *thread);
extern void saveEditedDataBinary(int a0, int a1, int a2);

void wakeup_cameraedit(void)
{
    print_y = 50;
    if (curmenu != 0) {
        iosThreadWakeup((void *)curmenu);
        if (D_0028F94C[0] & 0x400) {
            saveEditedDataBinary((int)&D_002AD010[D_005F5D50[stage_no].camSetId * 0x20],
                                 D_0063AA7C[1], D_0063AA7C[0]);
        }
    }
}

extern void EnterMenu(void *a0, int a1, void *a2);
extern void menuGroupSelect(char *m);

void test_camedit(void)
{
    EnterMenu((void *)menuGroupSelect, 0, 0);
}

extern char D_00555038[];
extern void debug_StdPrintfDummy();

static inline void _CameraEdit_free_box_pool(CamMgr *mgr, int idx)
{
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

void _CameraEdit_del_box(CamMgr *mgr, int idx)
{
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

static inline S4C *_CameraEdit_BOX_p(CamMgr *mgr, int i)
{
    return (S4C *)(i * 0x4C + (int)mgr->items);
}

static inline S5C *_CameraEdit_PIN_p(CamMgr *mgr, int i, int j)
{
    return (S5C *)(_CameraEdit_BOX_p(mgr, i)->w[0x48 / 4] + j * 0x5C);
}

void _CameraEdit_del_pin(CamMgr *mgr, int box, int pin)
{
    S5C *p;
    if (_CameraEdit_BOX_p(mgr, box)->w[0x3C / 4] <= 0) {
        debug_StdPrintfDummy(D_00555038);
        return;
    }
    for (p = _CameraEdit_PIN_p(mgr, box, pin);
         p < _CameraEdit_PIN_p(mgr, box, _CameraEdit_BOX_p(mgr, box)->w[0x3C / 4]); p++) {
        *p = p[1];
    }
    _CameraEdit_BOX_p(mgr, box)->w[0x3C / 4] = _CameraEdit_BOX_p(mgr, box)->w[0x3C / 4] - 1;
}

extern char D_00555020[];
extern int *D_0063AA78;
extern int *D_0063AA7C;

static inline char *_CameraEdit_alloc_pool(CamMgr *mgr)
{
    int i;
    for (i = 0; i < 0x64; i++) {
        if (mgr->flags[i] == 0) {
            mgr->flags[i] = 1;
            return mgr->pool + i * 0x23F0;
        }
    }
    return 0;
}

inline int _CameraEdit_add_box(CamMgr *mgr, S4C *src)
{
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

int CameraEdit_add_box(S4C *src)
{
    _CameraEdit_add_box((CamMgr *)D_0063AA78, src);
    return _CameraEdit_add_box((CamMgr *)D_0063AA7C, src);
}

extern char D_00555020[];
extern int *D_0063AA78;
extern int *D_0063AA7C;

inline int _CameraEdit_add_pin(void *a0, int a1, S5C *src)
{
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

int CameraEdit_add_pin(int box, char *src)
{
    _CameraEdit_add_pin(D_0063AA78, box, (S5C *)src);
    return _CameraEdit_add_pin(D_0063AA7C, box, (S5C *)src);
}

extern int *D_0063AA78;
extern int *D_0063AA7C;
extern void _CameraEdit_del_box(CamMgr *mgr, int idx);

void CameraEdit_del_box(int a0)
{
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

void CameraEdit_DispBox(int a0, unsigned char a1)
{
    DispCameraGroup(a0, a1);
}

extern void ReflectCameraSetBinary(int a0, int a1);

void CameraEdit_Reflect(void)
{
    int *p = D_0063AA78;
    ReflectCameraSetBinary(p[1], p[0]);
}

extern void saveEditedDataBinary(int a0, int a1, int a2);

void CameraEdit_Save(int a0)
{
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
extern unsigned char exit_f;

void InitCameraEditor(void)
{
    curmenu = 0;
    exit_f = 0;
}

extern void CameraSetMode(int a0);
extern unsigned char exit_f;
extern int D_0063B13C;
extern void wakeup_cameraedit(void);
extern void test_camedit(void);

int debug_CameraEditor(void)
{
    D_0063B13C = 1;
    if (curmenu == 0) {
        test_camedit();
    }
    wakeup_cameraedit();
    CameraSetMode(1);
    if (exit_f == 0) {
        return 0;
    }
    exit_f = 0;
    CameraEdit_Reflect();
    return -1;
}

extern int CameraEdit_BOX(int a0);
extern void CameraEdit_reset_pin(int a0, int a1);

void CameraEdit_reset_box(int a0)
{
    struct S4Cx {
        int w[19];
    } *src;
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

void CameraEdit_reset_pin(int a0, int a1)
{
    S5C *dst = (S5C *)(*(int *)(D_0063AA7C[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    S5C *src = (S5C *)(*(int *)(D_0063AA78[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    *dst = *src;
}

extern void CameraEdit_reflect_pin(int a0, int a1);

void CameraEdit_reflect_box(int a0)
{
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

void CameraEdit_reflect_pin(int a0, int a1)
{
    S5C *dst = (S5C *)(*(int *)(D_0063AA78[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    S5C *src = (S5C *)(*(int *)(D_0063AA7C[1] + a0 * 0x4C + 0x48) + a1 * 0x5C);
    *dst = *src;
}

int CameraEdit_BOX_NUMBER(void)
{
    return *D_0063AA7C;
}

int CameraEdit_PIN_NUMBER(int a0)
{
    int r1 = CameraEdit_BOX(a0);
    int r2 = CameraEdit_BOX(a0);
    return *(int *)(r1 + 0x3C) - *(int *)(r2 + 0x38);
}

int CameraEdit_PIN_NUMBER_ALL(int *a0, int a1)
{
    int sum = 0;
    int i;
    for (i = 0; i < a1; i++) {
        sum += a0[15] - a0[14];
    }
    return sum;
}

int CameraEdit_BOX(int a0)
{
    return D_0063AA7C[1] + a0 * 0x4C;
}

int CameraEdit_PIN(int a0, int a1)
{
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

static inline void dispPinRange(int box, int from, int to)
{
    CamColor col = D_00554E70;
    int i;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    ((float (*)[4])MatrixDrive_GetMatrix())[0][0] = ((float (*)[4])MatrixDrive_GetMatrix())[1][1] =
        ((float (*)[4])MatrixDrive_GetMatrix())[2][2] = -1.0f;
    gif_StartPacketPri(11);
    for (i = from; i < to; i++) {
        float a[3] = {((float *)CameraEdit_PIN(box, i))[0], ((float *)CameraEdit_PIN(box, i))[1],
                      ((float *)CameraEdit_PIN(box, i))[2]};
        float b[3] = {((float *)CameraEdit_PIN(box, i))[3], ((float *)CameraEdit_PIN(box, i))[4],
                      ((float *)CameraEdit_PIN(box, i))[5]};
        DrawLine(a, b, &col, -1);
    }
    gif_EndPacket();
}

void CameraEdit_DispPin(int box, int pin)
{
    dispPinRange(box, pin, pin + 1);
}

extern int CameraEdit_add_box(S4C *a0);
extern int CameraEdit_add_pin(int a0, char *a1);
extern float D_002A5D68[];
extern StageParam D_005F5D50[];
extern int stage_no;

void ConvertCameraSetBuffer(int n, S4C *item, char *groups)
{
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

void StickToTrans(int a0, int a1, int a2, int a3, float *out, int a5)
{
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

extern Pad D_0028F8F0[];
extern char D_00555000[];
extern char D_00555010[];
extern int curmenu;
extern void iosThreadSleep(void *th);
extern void iosThreadDestroy(void *th);
extern void debug_StdPrintfDummy();

void menu_2(char *m)
{
    Pad *pad;

    iosThreadSleep(m);

    pad = D_0028F8F0;
    while (1) {
        debug_StdPrintfDummy(D_00555000, *(int *)(m + 0x74));
        if (pad[1].trg & 0x20) {
            curmenu = *(int *)(m + 0x70);
            iosThreadDestroy(m);
        }
        iosThreadSleep(m);
    }
}

/* group_select: MAIN.MAP puts the only global of the name in camera-editor.o at
   base+0x5180, this address; ico2/fumi/src/way_tool holds a file static of the
   same name, reached through its own menu table. */
void group_select(char *m)
{
    Pad *pad;

    iosThreadSleep(m);

    pad = D_0028F8F0;
    while (1) {
        debug_StdPrintfDummy(D_00555010, *(int *)(m + 0x74));
        if (pad[1].trg & 0x20) {
            EnterMenu(menu_2, 3, m);
        }
        iosThreadSleep(m);
    }
}

int _CameraEdit_BOX(int *a0, int a1)
{
    return a0[1] + (a1 * 0x4C);
}

int _CameraEdit_PIN(int *a0, int a1, int a2)
{
    int *p;
    return ((int *)(a0[1] + (a1 * 0x4C)))[0x48 / 4] + (a2 * 0x5C);
}

extern char D_00555020[];
extern void debug_StdPrintfDummy();

inline void CameraEdit_Enter(void) {}
