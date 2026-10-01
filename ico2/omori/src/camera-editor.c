#include "camera-editor.h"
#include "debug.h"
#include "memory.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "gv.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "tableSin.h"
#include <stdio.h>
#include <sifdev.h>
#include <string.h>
#include "typedef.h"
#include "ios.h"
#include "main.h"
#include "debug_exception.h"
#include "GifPacket.h"
#include "poly-flat.h"
#include <libvu0.h>

/* ios/thread.c's entry points as the menus call them, each with the menu's
   thread (thread.h declares Sleep with no argument, Destroy with an int and
   Wakeup with an int *, so it is not included) */
extern void iosThreadSleep(void *th);
extern void iosThreadDestroy(void *th);
extern void iosThreadWakeup(void *thread);
extern void iosThreadMessage(int a0);

typedef struct CamMgr {
    int count;        /* 0x00 */
    char *items;      /* 0x04 */
    char *pool;       /* 0x08 */
    char flags[0x64]; /* 0x0C */
} CamMgr;

int curmenu;

void EnterMenu(void *a0, int a1, void *a2)
{
    MenuThread *m = iosMallocDebug(ios_partition_oomori, sizeof(MenuThread), __FILE__, 217);
    iosThreadCreateS(m, 1, a0, m, ios_partition_oomori, 0x1000, 0x17);
    m->arg = a1;
    m->parent = a2;
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

inline void StickToTrans(int a0, int a1, int a2, int a3, float *out, int a5)
{
    out[0] = out[1] = out[2] = 0.0f;
    if ((a0 < 0 ? -a0 : a0) < 50 && (a1 < 0 ? -a1 : a1) < 50) {
        return;
    }
    if (a2 != 0) {
        if (a0 > 0) {
            out[1] = (float)a5;
        }
        if (a0 < 0) {
            out[1] = (float)(-a5);
        }
    } else {
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_PushMatrix();
        {
            float vec[4] = {(float)a1, 0.0f, (float)a0, 0.0f};
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            MatrixDrive_RotMatrixY((short)a3);
            sceVu0ApplyMatrix(vec, MatrixDrive_GetMatrix(), vec);
            sceVu0Normalize(out, vec);
        }
        MatrixDrive_PopMatrix();
        out[0] = out[0] * (float)(-a5);
        out[2] = out[2] * (float)a5;
    }
}

inline void debug_Arrow(float len, void *from, void *to, int r, int g, int b) {}

inline void debug_NMarker(float *pos, int r, int g, int b, float size)
{
    float buf[4];
    sceVu0ScaleVector(buf, pos, -1.0f);
    debug_Marker(buf, r, g, b, size, 0.0f);
}

inline void debug_Marker(float *pos, int r, int g, int b, float size, float pulse) {}

static inline void writeCameraSetFile(int no, void *buf, int size)
{
    char path[0x80];

    debug_closeLog();
    debug_StdPrintfDummy("==== Save camera data start ========================\n");
    debug_StdPrintfDummy("\tfilename[%s]\n", no);
    debug_StdPrintfDummy("\t    size[%d]\n", size);
    sprintf(path, "ico2Data/%s", no);
    if (debugSceOpen(path, 0x202) < 0) {
        debug_StdPrintfDummy("Save Camera Data: host file open error.\n");
    } else {
        sceWrite(0, buf, size);
        debugSceClose(0);
        debug_StdPrintfDummy("==== Save camera data end ==========================\n");
    }
    debug_openLog();
}

void saveEditedDataBinary(int no, int a1, int a2)
{
    /* the header record: the body writes the four words straight into buf,
       and only the DEBUG build reads them back through it after the file
       write */
    CamSetBinHdr hdr;
    int size;
    int *buf;
    S4C *data;

    size = GetSizeOfCameraSetBinary((S4C *)a1, a2) + 0x10;
    buf = (int *)iosMallocDebug(ios_partition_oomori, size, __FILE__, 404);
    data = (S4C *)(buf + 4);
    buf[2] = a2;
    buf[0] = 0x1234;
    buf[1] = 3;
    buf[3] = CameraEdit_PIN_NUMBER_ALL((int *)a1, a2);
    MakeCameraSetBinary((S4C *)a1, a2, data);
    writeCameraSetFile(no, buf, size);
#ifdef DEBUG
    hdr = *(CamSetBinHdr *)buf;
    scePrintf("camera set %x v%d num %d pins %d\n", hdr.magic, hdr.version, hdr.num, hdr.pins);
#endif
    iosFree(buf);
}

/* the camera set the stage plays and the copy the editor edits: two fixed
   buffers in the development kit's extra memory */
static int *cameraSetOrg = (int *)0x3000000; /* derived name */

static int *cameraSetEdit = (int *)0x30E27E0; /* derived name */

/* the line buffer every row of the dump is formatted into before it is
   written and echoed */
static char dumpLine[2048]; /* derived name */

extern void __assert(char *file, int line, char *expr);

void saveEditedData(int *range)
{
    char path[0x70];
    int from = range[0];
    int to = range[1];
    int i;
    int j;
    int fd;

    sprintf(path, "a.txt");
    fd = debugSceOpen(path, 0x202);
    if (fd < 0) {
        debug_StdPrintfDummy("error---cannot open save camera data");
        debug_assert(__FILE__, 435);
        __assert(__FILE__, 435, "0");
    }
    for (i = from; i < to; i++) {
        BoxRec *b = (BoxRec *)(cameraSetEdit[1] + i * 0x4C);

        sprintf(dumpLine, "group[%s]\n%d\t\t%d\t%d\t%d\t\t\t%d\t%d\t%d\n", b, b->kind, (int)b->cx,
                (int)b->cy, (int)b->cz, (int)b->sx, (int)b->sy,
                (int)((BoxRec *)(i * 0x4C + cameraSetEdit[1]))->sz);
        sceWrite(fd, dumpLine, strlen(dumpLine));
        debug_StdPrintfDummy(dumpLine);
    }
    for (i = from; i < to; i++) {
        sprintf(dumpLine, "group[%s]'s pin\n", (BoxRec *)(cameraSetEdit[1] + i * 0x4C));
        sceWrite(fd, dumpLine, strlen(dumpLine));
        for (j = ((BoxRec *)(i * 0x4C + cameraSetEdit[1]))->pinFirst;
             j < ((BoxRec *)(i * 0x4C + cameraSetEdit[1]))->pinLast; j++) {
            PinRec *p = CameraEdit_PIN(i, j);

            /* the pin flag prints as a maru when set and a batsu when clear */
            sprintf(dumpLine, "%s\t%d\t\t%d\t%d\t%d\t\t\t%d\t%d\t%d\n", p->on ? "○" : "×",
                    (int)p->fov, (int)p->pos[0], (int)p->pos[1], (int)p->pos[2], (int)p->look[0],
                    (int)p->look[1], (int)p->look[2]);
            sceWrite(fd, dumpLine, strlen(dumpLine));
        }
    }
    debugSceClose(fd);
    iosThreadMessage(2);
}

/* the report for a message the editor does not handle; nothing calls it */
static inline void illegalMessage(int msg) /* derived name */
{
    debug_StdPrintfDummy("illegal message %d\n", msg);
}

void gif_test(int *a0, int *a1, int *a2, unsigned char *a3)
{
    gif_SetGsReg(0, 3);
    gif_SetGsReg(1, (long)a3[0] | ((long)a3[1] << 8) | ((long)a3[2] << 16) | ((long)a3[3] << 24));
    gif_SetGsReg(4, (long)a0[0] | ((long)a0[1] << 16) | ((long)a0[2] << 32));
    gif_SetGsReg(4, (long)a1[0] | ((long)a1[1] << 16) | ((long)a1[2] << 32));
    gif_SetGsReg(4, (long)a2[0] | ((long)a2[1] << 16) | ((long)a2[2] << 32));
}

static inline void dispPinRange(int box, int from, int to)
{
    sceVu0IVECTOR col = {255, 255, 255, 128};
    int i;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    ((float (*)[4])MatrixDrive_GetMatrix())[0][0] = ((float (*)[4])MatrixDrive_GetMatrix())[1][1] =
        ((float (*)[4])MatrixDrive_GetMatrix())[2][2] = -1.0f;
    gif_StartPacketPri(11);
    for (i = from; i < to; i++) {
        float a[3] = {CameraEdit_PIN(box, i)->pos[0], CameraEdit_PIN(box, i)->pos[1],
                      CameraEdit_PIN(box, i)->pos[2]};
        float b[3] = {CameraEdit_PIN(box, i)->look[0], CameraEdit_PIN(box, i)->look[1],
                      CameraEdit_PIN(box, i)->look[2]};
        DrawLine(a, b, (int)col, -1);
    }
    gif_EndPacket();
}

/* box corner quadword: _InterGV / DrawPolygon / do_DrawLine take 16-byte
   aligned vectors */
typedef struct {
    float x, y, z, w;
} BoxVtx __attribute__((aligned(16)));

typedef struct {
    float x, y, z;
} BoxVec;

/* the box's two index tables and its line colour, initialised as whole
   objects here and in DispCameraGroup */
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
    BoxIdx6 idx6 = {
        {{0, 1, 2, 3}, {1, 3, 5, 7}, {2, 3, 6, 7}, {0, 2, 4, 6}, {5, 4, 7, 6}, {1, 0, 5, 4}}};
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

    sceVu0UnitMatrix(m);
    sceVu0MulMatrix(m, matrixptr + 0x80, m);
    sceVu0MulMatrix(m, matrixptr + 0xC0, m);
    before_DrawPolygon();
    for (n = 0; n < 6; n++) {
        col = (BoxCol){128, 64, 64, 64};
        col.r = 64;
        col.g = 64;
        col.b = 64;
        col.a = 32;
        for (j = 0; j < 3; j++) {
            _InterGV(e0, &v[idx6.e[n][0]].x, &v[idx6.e[n][1]].x, (float)j, (float)(3 - j));
            _InterGV(e1, &v[idx6.e[n][0]].x, &v[idx6.e[n][1]].x, (float)(j + 1), (float)(2 - j));
            _InterGV(e2, &v[idx6.e[n][2]].x, &v[idx6.e[n][3]].x, (float)j, (float)(3 - j));
            _InterGV(e3, &v[idx6.e[n][2]].x, &v[idx6.e[n][3]].x, (float)(j + 1), (float)(2 - j));
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
    idx12 = (BoxIdx12){{{0, 1},
                        {1, 3},
                        {3, 2},
                        {2, 0},
                        {0, 4},
                        {1, 5},
                        {2, 6},
                        {3, 7},
                        {4, 5},
                        {5, 7},
                        {7, 6},
                        {6, 4}}};
    col2 = (BoxCol4){{255, 255, 255, 255}};
    sceVu0UnitMatrix(m2);
    m2[0][0] = m2[1][1] = m2[2][2] = -1.0f;
    before_DrawLine(m);
    for (i = 0; i < 12; i++) {
        do_DrawLine(&v[idx12.e[i][0]], &v[idx12.e[i][1]], col2.c, -1);
    }
    after_DrawLine();
}

void DispCameraGroup(int box, unsigned char sel)
{
    int n;
    int j;
    int k;
    int i;
    BoxRec *b = (BoxRec *)(cameraSetEdit[1] + box * 0x4C);
    BoxVtx v[8] = {{b->cx - b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f},
                   {b->cx - b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f},
                   {b->cx + b->sx, b->cy - b->sy, b->cz - b->sz, 1.0f},
                   {b->cx + b->sx, b->cy - b->sy, b->cz + b->sz, 1.0f},
                   {b->cx - b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f},
                   {b->cx - b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f},
                   {b->cx + b->sx, b->cy + b->sy, b->cz - b->sz, 1.0f},
                   {b->cx + b->sx, b->cy + b->sy, b->cz + b->sz, 1.0f}};
    BoxIdx6 idx6 = {
        {{0, 1, 2, 3}, {1, 3, 5, 7}, {2, 3, 6, 7}, {0, 2, 4, 6}, {5, 4, 7, 6}, {1, 0, 5, 4}}};
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

    sceVu0UnitMatrix(m);
    m[0][0] = m[1][1] = m[2][2] = -1.0f;
    sceVu0MulMatrix(m, matrixptr + 0x80, m);
    sceVu0MulMatrix(m, matrixptr + 0xC0, m);
    before_DrawPolygon();
    for (n = 0; n < 6; n++) {
        col = (BoxCol){128, 64, 64, 64};
        if (sel == 0) {
            col.r = 64;
            col.g = 64;
            col.b = 64;
            col.a = 32;
        }
        for (j = 0; j < 3; j++) {
            _InterGV(e0, &v[idx6.e[n][0]].x, &v[idx6.e[n][1]].x, (float)j, (float)(3 - j));
            _InterGV(e1, &v[idx6.e[n][0]].x, &v[idx6.e[n][1]].x, (float)(j + 1), (float)(2 - j));
            _InterGV(e2, &v[idx6.e[n][2]].x, &v[idx6.e[n][3]].x, (float)j, (float)(3 - j));
            _InterGV(e3, &v[idx6.e[n][2]].x, &v[idx6.e[n][3]].x, (float)(j + 1), (float)(2 - j));
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
    idx12 = (BoxIdx12){{{0, 1},
                        {1, 3},
                        {3, 2},
                        {2, 0},
                        {0, 4},
                        {1, 5},
                        {2, 6},
                        {3, 7},
                        {4, 5},
                        {5, 7},
                        {7, 6},
                        {6, 4}}};
    col2 = (BoxCol4){{255, 255, 255, 255}};
    sceVu0UnitMatrix(m2);
    m2[0][0] = m2[1][1] = m2[2][2] = -1.0f;
    before_DrawLine(m);
    for (i = 0; i < 12; i++) {
        do_DrawLine(&v[idx12.e[i][0]], &v[idx12.e[i][1]], col2.c, -1);
    }
    after_DrawLine();
}

/* a VU0 quadword: DrawLineG takes 16-byte aligned vectors */
typedef struct {
    float x, y, z, w;
} ArrowVtx __attribute__((aligned(16)));

/* The head, barb and shaft ends of the arrow drawXZArrow draws: the head runs from the origin out to +-50, the barbs join +-25 to
   the head, and the shaft runs from +-25 back to the caller's length. */
static ArrowVtx arrowHeadLeft = {-50.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static ArrowVtx arrowBarbLeft = {-25.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static ArrowVtx arrowShaftLeft = {-25.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static ArrowVtx arrowHeadRight = {50.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static ArrowVtx arrowBarbRight = {25.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static ArrowVtx arrowShaftRight = {25.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

void drawXZArrow(void *col, int f, float z)
{
    ArrowVtx v0 = {-25.0f, 0.0f, -z, 1.0f};
    ArrowVtx v1 = {25.0f, 0.0f, -z, 1.0f};

    DrawLineG(&ZeroVector, col, &arrowHeadRight, col, f);
    DrawLineG(&ZeroVector, col, &arrowHeadLeft, col, f);
    DrawLineG(&arrowBarbRight, col, &arrowHeadRight, col, f);
    DrawLineG(&arrowBarbLeft, col, &arrowHeadLeft, col, f);
    DrawLineG(&arrowShaftLeft, col, &v0, col, f);
    DrawLineG(&arrowShaftRight, col, &v1, col, f);
    DrawLineG(&v0, col, &v1, col, f);
}

/* one axis of the arrow table: the tip and tail vectors of the arrow */
typedef struct {
    float tip[4];
    float tail[4];
} AxisPair;

/* the point the axis widget is drawn at, 2000 units down the view axis */
static ArrowVtx axisArrowOrigin = {0.0f, 0.0f, 2000.0f, 1.0f};

/* the three axis arrows, each from -200 to +200 along one axis */
static AxisPair axisArrows[3] = {
    {{-200.0f, 0.0f, 0.0f, 1.0f}, {200.0f, 0.0f, 0.0f, 1.0f}},
    {{0.0f, -200.0f, 0.0f, 1.0f}, {0.0f, 200.0f, 0.0f, 1.0f}},
    {{0.0f, 0.0f, -200.0f, 1.0f}, {0.0f, 0.0f, 200.0f, 1.0f}},
};

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
        sceVu0ApplyMatrix(v, m0, &axisArrowOrigin);

        gif_StartPacketPri(11);
        gif_SetAlpha(1, 5, 0);
        gif_SetZTest(0);

        ax = axisArrows;
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

/* the pin arrow colours: the first pair is drawn depth-tested (the part in
   front of the level), the second pair through it, and each pair has a colour
   for a typed pin and one for a plain one */
static int pinArrowColorTyped[4] = {255, 128, 128, 128};

static int pinArrowColorPlain[4] = {64, 64, 64, 128};

static int pinArrowHiddenColorTyped[4] = {64, 32, 32, 128};

static int pinArrowHiddenColorPlain[4] = {16, 16, 16, 128};

void dispCameraPinType2(int box, int from, int to, int type)
{
    float m0[4][4];
    int *c1;
    int *c2;
    int i;

    c1 = type ? pinArrowColorTyped : pinArrowColorPlain;
    c2 = type ? pinArrowHiddenColorTyped : pinArrowHiddenColorPlain;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_ScaleMatrix(-1.0f, -1.0f, -1.0f);
    MatrixDrive_SetTransposeMatrix(m0, matrixptr + 0x80);
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 0);
    gif_SetZWrite(1);
    for (i = from; i < to; i++) {
        int c1v[4];
        int c2v[4];
        ArrowVtx a = {CameraEdit_PIN(box, i)->pos[0], CameraEdit_PIN(box, i)->pos[1],
                      CameraEdit_PIN(box, i)->pos[2], 0.0f};
        ArrowVtx b = {CameraEdit_PIN(box, i)->look[0], CameraEdit_PIN(box, i)->look[1],
                      CameraEdit_PIN(box, i)->look[2], 0.0f};
        float n[4];
        float m1[4][4];
        float t;

        CopyIVector(c1v, c1);
        CopyIVector(c2v, c2);
        MatrixDrive_TransMatrixV(&b);
        MatrixDrive_TurnObjectMatrix(-(b.x - a.x), b.y - a.y, b.z - a.z);
        {
            ArrowVtx d = {-CameraEdit_PIN(box, i)->look[0], -CameraEdit_PIN(box, i)->look[1],
                          -CameraEdit_PIN(box, i)->look[2], 1.0f};

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

void CameraEdit_DispPinType2(int a0, int a1, int a2)
{
    dispCameraPinType2(a0, a1, a1 + 1, a2);
}

static unsigned char boxFaceColorSel[4] = {128, 64, 64, 64}; /* derived name */

static unsigned char boxFaceColor[4] = {32, 32, 32, 64}; /* derived name */

/* the eight box corners in face order: each row is the two corner pairs the
   face is interpolated between */
static int boxFaceCorner[6][4] = {
    {0, 1, 2, 3}, {1, 3, 5, 7}, {2, 3, 6, 7}, {0, 2, 4, 6}, {5, 4, 7, 6}, {1, 0, 5, 4},
};

/* the twelve box edges as corner pairs */
static int boxEdgeCorner[12][2] = {
    {0, 1}, {1, 3}, {3, 2}, {2, 0}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 7}, {7, 6}, {6, 4},
};

/* the camera box edge colours, bright pair while the box is selected and dim
   pair while it is not; the second of each pair is the part behind geometry */
static unsigned int boxEdgeColorSel[4] = {224, 224, 224, 128};

static unsigned int boxHiddenEdgeColorSel[4] = {32, 32, 32, 128};

static unsigned int boxEdgeColor[4] = {64, 64, 64, 128};

static unsigned int boxHiddenEdgeColor[4] = {16, 16, 16, 128};

void dispCameraGroupType2(int box, unsigned char sel)
{
    int n;
    int j;
    int k;
    int i;
    unsigned char *col;
    unsigned int *c0;
    unsigned int *c1;
    BoxRec *b = (BoxRec *)(cameraSetEdit[1] + box * 0x4C);
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
        col = sel == 0 ? boxFaceColor : boxFaceColorSel;
        for (j = 0; j < 3; j++) {
            _InterGV(e0, &v[boxFaceCorner[n][0]].x, &v[boxFaceCorner[n][1]].x, (float)j,
                     (float)(3 - j));
            _InterGV(e1, &v[boxFaceCorner[n][0]].x, &v[boxFaceCorner[n][1]].x, (float)(j + 1),
                     (float)(2 - j));
            _InterGV(e2, &v[boxFaceCorner[n][2]].x, &v[boxFaceCorner[n][3]].x, (float)j,
                     (float)(3 - j));
            _InterGV(e3, &v[boxFaceCorner[n][2]].x, &v[boxFaceCorner[n][3]].x, (float)(j + 1),
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
    c0 = boxEdgeColorSel;
    c1 = boxHiddenEdgeColorSel;
    if (sel == 0) {
        c0 = boxEdgeColor;
        c1 = boxHiddenEdgeColor;
    }
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_ScaleMatrix(-1.0f, -1.0f, -1.0f);
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 0);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    for (i = 0; i < 12; i++) {
        DrawLineG(&v[boxEdgeCorner[i][0]], c1, &v[boxEdgeCorner[i][1]], c1, 0);
    }
    gif_SetZTest(1);
    for (i = 0; i < 12; i++) {
        DrawLineG(&v[boxEdgeCorner[i][0]], c0, &v[boxEdgeCorner[i][1]], c0, 0);
    }
    gif_EndPacket();
}

/* dispBox is defined as a nested function inside
 * CameraEdit_DispBoxType2_Plane below. */
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

/* the plane editor's own copy of the face and edge tables; the faces are in a
   different order from boxFaceCorner above */
static int planeFaceCorner[6][4] = {
    {2, 3, 6, 7}, {1, 0, 5, 4}, {1, 3, 5, 7}, {0, 2, 4, 6}, {5, 4, 7, 6}, {0, 1, 2, 3},
};

static int planeEdgeCorner[12][2] = {
    {0, 1}, {1, 3}, {3, 2}, {2, 0}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 7}, {7, 6}, {6, 4},
};

/* the plane editor's edge colours.  It always draws the bright pair; the dim
   pair after it is the same pair as boxEdgeColor / boxHiddenEdgeColor above
   and nothing reads it. */
static unsigned int planeEdgeColorSel[4] = {224, 224, 224, 128};

static unsigned int planeHiddenEdgeColorSel[4] = {32, 32, 32, 128};

static unsigned int planeEdgeColor[4] = {64, 64, 64, 128};

static unsigned int planeHiddenEdgeColor[4] = {16, 16, 16, 128};

static unsigned char planeFaceColorSel[4] = {128, 64, 64, 64}; /* derived name */

static unsigned char planeHiddenFaceColorSel[4] = {32, 8, 8, 64}; /* derived name */

static unsigned char planeFaceColor[4] = {32, 32, 32, 64}; /* derived name */

static unsigned char planeHiddenFaceColor[4] = {2, 2, 2, 64}; /* derived name */

void CameraEdit_DispBoxType2_Plane(int box, int sel)
{
    int n;
    CamBoxF *b = (CamBoxF *)(cameraSetEdit[1] + box * 0x4C);
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

        /* dispBox is nested: it reaches the parent's v[], m[][], n and sel
         * directly. */
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
                    _InterGV(e0, &v[planeFaceCorner[n][0]].x, &v[planeFaceCorner[n][1]].x, (float)j,
                             (float)(3 - j));
                    _InterGV(e1, &v[planeFaceCorner[n][0]].x, &v[planeFaceCorner[n][1]].x,
                             (float)(j + 1), (float)(2 - j));
                    _InterGV(e2, &v[planeFaceCorner[n][2]].x, &v[planeFaceCorner[n][3]].x, (float)j,
                             (float)(3 - j));
                    _InterGV(e3, &v[planeFaceCorner[n][2]].x, &v[planeFaceCorner[n][3]].x,
                             (float)(j + 1), (float)(2 - j));
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
        dispBox(planeFaceColorSel, planeFaceColor);
        gif_SetZTest(0);
        dispBox(planeHiddenFaceColorSel, planeHiddenFaceColor);
        after_DrawPolygon();
        c0 = planeEdgeColorSel;
        c1 = planeHiddenEdgeColorSel;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_ScaleMatrix(-1.0f, -1.0f, -1.0f);
        gif_StartPacketPri(11);
        gif_SetAlpha(1, 5, 0);
        gif_SetZWrite(0);
        gif_SetZTest(0);
        for (i = 0; i < 12; i++) {
            DrawLineG(&v[planeEdgeCorner[i][0]], c1, &v[planeEdgeCorner[i][1]], c1, 0);
        }
        gif_SetZTest(1);
        for (i = 0; i < 12; i++) {
            DrawLineG(&v[planeEdgeCorner[i][0]], c0, &v[planeEdgeCorner[i][1]], c0, 0);
        }
        gif_EndPacket();
    }
}

void CameraEdit_DispBoxType2(int a0, int a1)
{
    dispCameraGroupType2(a0, a1 & 0xFF);
}

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4 */

/* the pad table (main.h's pad), read through the Pad view with the stick
   bytes at 0x54 */
extern Pad D_0028F8F0[];

int print_y;

unsigned char exit_f;

void menuGroupSelect(MenuThread *m)
{
    Pad *pad;
    int *box = &m->arg;
    int i;
    int n;
    int start;
    int end;

    iosThreadSleep(m);

    pad = D_0028F8F0;
    while (1) {
        if (pad[1].trg & 0x1000) {
            m->arg--;
        }
        if (pad[1].trg & 0x4000) {
            m->arg++;
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
                if (debug_font_flag & 1) {
                    print_y += 10;
                    debug_Printf(40, print_y, 0xFFFFFF00, ">> %s", cameraSetEdit[1] + i * 0x4C);
                }
            } else {
                if (debug_font_flag & 1) {
                    print_y += 10;
                    debug_Printf(40, print_y, 0xFFFFFF00, "   %s", cameraSetEdit[1] + i * 0x4C);
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

void menuGroupEdit(MenuThread *m)
{
    EditRec *rec = (EditRec *)(cameraSetEdit[1] + m->arg * 0x4C);
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
            DispCameraGroup(i, i == m->arg);
        }
        {
            EditItem item[7] = {
                {rec->type, 1, 1, "group"},        {(int)rec->cx, 10, 0, "center-x"},
                {(int)rec->cy, 10, 0, "center-y"}, {(int)rec->cz, 10, 0, "center-z"},
                {(int)rec->sx, 10, 0, "width-x"},  {(int)rec->sy, 10, 0, "width-y"},
                {(int)rec->sz, 10, 0, "width-z"}};
            int d = 0;

            if (item[cur].mode) {
                if (D_0028F8F0[1].trg & 0x2000) {
                    d = 1;
                }
                if (D_0028F8F0[1].trg & 0x8000) {
                    d = -1;
                }
            } else {
                if (D_0028F8F0[1].now & 0x2000) {
                    d = 1;
                }
                if (D_0028F8F0[1].now & 0x8000) {
                    d = -1;
                }
            }
            d = d * item[cur].step;
            item[cur].val += d;
            for (i = 0; i < 7; i++) {
                if (i == cur) {
                    if (debug_font_flag & 1) {
                        print_y += 10;
                        debug_Printf(40, print_y, 0xFFFFFF00, ">>%8s = %d\n", item[i].name,
                                     item[i].val);
                    }
                } else {
                    if (debug_font_flag & 1) {
                        print_y += 10;
                        debug_Printf(40, print_y, 0xFFFFFF00, "  %8s = %d\n", item[i].name,
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
            curmenu = (int)m->parent;
            iosThreadDestroy(m);
        }
        iosThreadSleep(m);
    }
}

/* the camera work SetWSMatrix converts: eye at 0x00, look-at at 0x10 and the
   field of view at 0x20, the same record camera-ico2.c hands it */
typedef struct CamWork {
    float eye[4]; /* 0x00 */
    float at[4];  /* 0x10 */
    float fov;    /* 0x20 */
} __attribute__((aligned(16))) CamWork;

/* the group record CameraEdit_BOX hands back, as the pin menus read it: the
   first and the last pin index of the group */
typedef struct BoxPins {
    char pad00[0x38];
    int first; /* 0x38 */
    int last;  /* 0x3C */
} BoxPins;

/* the pin the pin editor was opened on */
static int editPinNo; /* derived name */

/* The DEBUG build's trace of the pin window the list shows; retail builds it
   empty. */
#ifdef DEBUG
#define PIN_WINDOW_TRACE(from, to) scePrintf("pin window %d..%d\n", (from), (to))
#else
#define PIN_WINDOW_TRACE(from, to)
#endif

void menuPinSelect(MenuThread *m)
{
    int no = m->arg;
    int cur = ((BoxPins *)(cameraSetEdit[1] + no * 0x4C))->first;
    int min;
    int max;
    int i;
    int n;
    /* start and end are the window the list shows; the DEBUG build traces
       it at the top of every pass, so the first pass reads these zeros. */
    int start = 0;
    int end = 0;

    iosThreadSleep(m);

    while (1) {
        PIN_WINDOW_TRACE(start, end);
        min = ((BoxPins *)(cameraSetEdit[1] + no * 0x4C))->first;
        max = ((BoxPins *)(cameraSetEdit[1] + no * 0x4C))->last;
        if (D_0028F8F0[1].trg & 0x1000) {
            cur--;
        }
        if (D_0028F8F0[1].trg & 0x4000) {
            cur++;
        }
        cur = (cur < min) ? max - 1 : ((cur < max) ? cur : min);

        dispPinRange(no, min, max);

        n = cur - 5;
        start = (n < min) ? min : ((max < n) ? max : n);
        n = start + 10;
        end = (n < min) ? min : ((max < n) ? max : n);
        for (i = start; i < end; i++) {
            int k = i - min;

            if (i == cur) {
                if (debug_font_flag & 1) {
                    debug_Printf(40, print_y += 10, 0xFFFFFF00, ">>%s %d",
                                 CameraEdit_PIN(no, cur)->on ? "ON " : "OFF", k);
                }
            } else {
                if (debug_font_flag & 1) {
                    debug_Printf(40, print_y += 10, 0xFFFFFF00, "  %s %d",
                                 CameraEdit_PIN(no, i)->on ? "ON " : "OFF", k);
                }
            }
        }
        if (CameraEdit_PIN(no, cur)->range != 0.0f) {
            debug_Marker(CameraEdit_PIN(no, cur)->pos, 0, 0, 255, CameraEdit_PIN(no, cur)->range,
                         0.0f);
        } else {
            debug_Marker(CameraEdit_PIN(no, cur)->pos, 255, 0, 0, 100.0f, 0.0f);
        }
        {
            PinRec *p = CameraEdit_PIN(no, cur);
            CamWork cw = {
                {p->pos[0], p->pos[1], p->pos[2]}, {p->look[0], p->look[1], p->look[2]}, p->fov};

            sceVu0ScaleVector(&cw, &cw, -1.0f);
            sceVu0ScaleVector(cw.at, cw.at, -1.0f);
            SetWSMatrix(&cw);
        }
        if (D_0028F8F0[1].trg & 0x10) {
            curmenu = (int)m->parent;
            iosThreadDestroy(m);
        } else if (D_0028F8F0[1].trg & 0x20) {
            editPinNo = no;
            EnterMenu(menuPinEdit, cur, m);
        }
        iosThreadSleep(m);
    }
}

/* the heading from the camera's eye to its look-at point, which is the angle
   the pin editor turns the pad stick vector by */
static inline int camHeading(float *at, float *eye) /* derived name */
{
    float v[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float len;

    sceVu0SubVector(v, at, eye);
    sceVu0Normalize(v, v);
    len = FSqrt(v[0] * v[0] + v[2] * v[2]);
    return GetTableArcTan2(v[0], -v[2] / len);
}

void menuPinEdit(MenuThread *m)
{
    PinRec *pin = CameraEdit_PIN(editPinNo, m->arg);
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
        {
            EditItem item[8] = {{pin->on, 1, 1, "onoff"},
                                {(int)pin->fov, 1, 1, "view"},
                                {(int)pin->pos[0], 10, 0, "camera-x"},
                                {(int)pin->pos[1], 10, 0, "camera-y"},
                                {(int)pin->pos[2], 10, 0, "camera-z"},
                                {(int)pin->look[0], 10, 0, "target-x"},
                                {(int)pin->look[1], 10, 0, "target-y"},
                                {(int)pin->look[2], 10, 0, "target-z"}};
            int d = 0;

            if (item[cur].mode) {
                if (D_0028F8F0[1].trg & 0x2000) {
                    d = 1;
                }
                if (D_0028F8F0[1].trg & 0x8000) {
                    d = -1;
                }
            } else {
                if (D_0028F8F0[1].now & 0x2000) {
                    d = 1;
                }
                if (D_0028F8F0[1].now & 0x8000) {
                    d = -1;
                }
            }
            d = d * item[cur].step;
            item[cur].val += d;
            for (i = 0; i < 8; i++) {
                if (i == cur) {
                    if (debug_font_flag & 1) {
                        print_y += 10;
                        debug_Printf(40, print_y, 0xFFFFFF00, ">>%8s = %d\n", item[i].name,
                                     item[i].val);
                    }
                } else {
                    if (debug_font_flag & 1) {
                        print_y += 10;
                        debug_Printf(40, print_y, 0xFFFFFF00, "  %8s = %d\n", item[i].name,
                                     item[i].val);
                    }
                }
            }
            pin->on = item[0].val;

            pin->fov = (float)item[1].val;
            pin->pos[0] = (float)item[2].val;
            pin->pos[1] = (float)item[3].val;
            pin->pos[2] = (float)item[4].val;
            pin->look[0] = (float)item[5].val;
            pin->look[1] = (float)item[6].val;
            pin->look[2] = (float)item[7].val;
            {
                CamWork cw = {{pin->pos[0], pin->pos[1], pin->pos[2]},
                              {pin->look[0], pin->look[1], pin->look[2]},
                              pin->fov};
                float out[4];

                sceVu0ScaleVector(&cw, &cw, -1.0f);
                sceVu0ScaleVector(cw.at, cw.at, -1.0f);
                SetWSMatrix(&cw);

                StickToTrans(D_0028F8F0[1].ana[1] - 128, D_0028F8F0[1].ana[0] - 128,
                             D_0028F8F0[1].now & 2, camHeading(cw.at, cw.eye), out, 20);
                sceVu0ScaleVector(out, out, -1.0f);
                pin->pos[0] = pin->pos[0] + out[0];
                pin->pos[1] = pin->pos[1] + out[1];
                pin->pos[2] = pin->pos[2] + out[2];

                StickToTrans(D_0028F8F0[1].ana[3] - 128, D_0028F8F0[1].ana[2] - 128,
                             D_0028F8F0[1].now & 2, camHeading(cw.at, cw.eye), out, 20);
                sceVu0ScaleVector(out, out, -1.0f);
                pin->look[0] = pin->look[0] + out[0];
                pin->look[1] = pin->look[1] + out[1];
                pin->look[2] = pin->look[2] + out[2];

                debug_Marker(pin->look, 255, 0, 0, 100.0f, 0.0f);
            }
        }
        if (D_0028F8F0[1].trg & 0x10) {
            curmenu = (int)m->parent;
            iosThreadDestroy(m);
        }
        iosThreadSleep(m);
    }
}

inline void menu_2(MenuThread *m)
{
    Pad *pad;

    iosThreadSleep(m);

    pad = D_0028F8F0;
    while (1) {
        debug_StdPrintfDummy("menu_2, arg=%d\n", m->arg);
        if (pad[1].trg & 0x20) {
            curmenu = (int)m->parent;
            iosThreadDestroy(m);
        }
        iosThreadSleep(m);
    }
}

/* the global group_select; way_tool.c has a static of the same name, reached
   through its own menu table */
inline void group_select(MenuThread *m)
{
    Pad *pad;

    iosThreadSleep(m);

    pad = D_0028F8F0;
    while (1) {
        debug_StdPrintfDummy("menu_1, arg=%d\n", m->arg);
        if (pad[1].trg & 0x20) {
            EnterMenu(menu_2, 3, m);
        }
        iosThreadSleep(m);
    }
}

extern StgPre stageData[];

void wakeup_cameraedit(void)
{
    print_y = 50;
    if (curmenu != 0) {
        iosThreadWakeup((void *)curmenu);
        if (pad[1].flags & 0x400) {
            saveEditedDataBinary((int)cameraSetList[stageData[stage_no].camSetId], cameraSetEdit[1],
                                 cameraSetEdit[0]);
        }
    }
}

void test_camedit(void)
{
    EnterMenu((void *)menuGroupSelect, 0, 0);
}

inline int _CameraEdit_BOX(int *a0, int a1)
{
    return a0[1] + (a1 * 0x4C);
}

inline int _CameraEdit_PIN(int *a0, int a1, int a2)
{
    return ((int *)(a0[1] + (a1 * 0x4C)))[0x48 / 4] + (a2 * 0x5C);
}

static inline char *_CameraEdit_alloc_pool(CamMgr *mgr)
{
    int i;
    for (i = 0; i < 100; i++) {
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
            dst->first = 0;
            dst->end = 0;
            *(char **)&dst->items = p;
            mgr->count = mgr->count + 1;
        }
        return result;
    }
    /* "cannot add any more" */
    debug_StdPrintfDummy("これ以上追加できません");
    return -1;
}

inline int _CameraEdit_add_pin(void *a0, int a1, PinRec *src)
{
    int base = a1 * 0x4C + *(int *)((char *)a0 + 4);
    int n = ((S4C *)base)->end;
    int result = -1;
    if (n < 0x64) {
        int base2;
        *(PinRec *)(((S4C *)base)->items + n * 0x5C) = *src;
        base2 = a1 * 0x4C + *(int *)((char *)a0 + 4);
        result = ((S4C *)base2)->end;
        ((S4C *)base2)->end = result + 1;
    } else {
        /* "cannot add any more" */
        debug_StdPrintfDummy("これ以上追加できません");
    }
    return result;
}

static inline void _CameraEdit_free_box_pool(CamMgr *mgr, int idx)
{
    S4C *box = (S4C *)(idx * 0x4C + (int)mgr->items);
    char *p = mgr->pool;
    int i;
    for (i = 0; i < 100; i++) {
        if (p == *(char **)&box->items) {
            mgr->flags[i] = 0;
        }
        p += 0x23F0;
    }
}

void _CameraEdit_del_box(CamMgr *mgr, int idx)
{
    if (mgr->count <= 0) {
        /* "cannot delete any more" */
        debug_StdPrintfDummy("これ以上削除できません");
        return;
    }
    _CameraEdit_free_box_pool(mgr, idx);
    while (idx < mgr->count) {
        ((S4C *)mgr->items)[idx] = ((S4C *)mgr->items)[idx + 1];
        idx++;
    }
    mgr->count = mgr->count - 1;
}

static inline S4C *_CameraEdit_BOX_p(CamMgr *mgr, int i)
{
    return (S4C *)(i * 0x4C + (int)mgr->items);
}

static inline PinRec *_CameraEdit_PIN_p(CamMgr *mgr, int i, int j)
{
    return (PinRec *)(_CameraEdit_BOX_p(mgr, i)->items + j * 0x5C);
}

void _CameraEdit_del_pin(CamMgr *mgr, int box, int pin)
{
    PinRec *p;
    if (_CameraEdit_BOX_p(mgr, box)->end <= 0) {
        /* "cannot delete any more" */
        debug_StdPrintfDummy("これ以上削除できません");
        return;
    }
    for (p = _CameraEdit_PIN_p(mgr, box, pin);
         p < _CameraEdit_PIN_p(mgr, box, _CameraEdit_BOX_p(mgr, box)->end); p++) {
        *p = p[1];
    }
    _CameraEdit_BOX_p(mgr, box)->end = _CameraEdit_BOX_p(mgr, box)->end - 1;
}

int CameraEdit_add_box(S4C *src)
{
    _CameraEdit_add_box((CamMgr *)cameraSetOrg, src);
    return _CameraEdit_add_box((CamMgr *)cameraSetEdit, src);
}

int CameraEdit_add_pin(int box, char *src)
{
    _CameraEdit_add_pin(cameraSetOrg, box, (PinRec *)src);
    return _CameraEdit_add_pin(cameraSetEdit, box, (PinRec *)src);
}

void CameraEdit_del_box(int a0)
{
    _CameraEdit_del_box((CamMgr *)cameraSetOrg, a0);
    _CameraEdit_del_box((CamMgr *)cameraSetEdit, a0);
}

void CameraEdit_del_pin(int a0, int a1)
{
    _CameraEdit_del_pin((CamMgr *)cameraSetOrg, a0, a1);
    _CameraEdit_del_pin((CamMgr *)cameraSetEdit, a0, a1);
}

void CameraEdit_DispBox(int a0, unsigned char a1)
{
    DispCameraGroup(a0, a1);
}

void CameraEdit_Reflect(void)
{
    int *p = cameraSetOrg;
    ReflectCameraSetBinary((S4C *)p[1], p[0]);
}

void CameraEdit_Save(int a0)
{
    int *p = cameraSetOrg;
    saveEditedDataBinary(a0, p[1], p[0]);
}

inline void InitCameraEditor(void)
{
    curmenu = 0;
    exit_f = 0;
}

inline int debug_CameraEditor(void)
{
    debug_font_flag = 1;
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

inline void CameraEdit_reset_box(int a0)
{
    S4C *src;
    S4C *dst;
    int saved;
    int i;
    src = (S4C *)(cameraSetOrg[1] + a0 * 0x4C);
    dst = (S4C *)(cameraSetEdit[1] + a0 * 0x4C);
    saved = dst->items;
    *dst = *src;
    dst->items = saved;
    i = 0;
    while (i < ((S4C *)CameraEdit_BOX(a0))->end - ((S4C *)CameraEdit_BOX(a0))->first) {
        CameraEdit_reset_pin(a0, i);
        i++;
    }
}

inline void CameraEdit_reset_pin(int a0, int a1)
{
    PinRec *dst = (PinRec *)(((S4C *)(cameraSetEdit[1] + a0 * 0x4C))->items + a1 * 0x5C);
    PinRec *src = (PinRec *)(((S4C *)(cameraSetOrg[1] + a0 * 0x4C))->items + a1 * 0x5C);
    *dst = *src;
}

inline void CameraEdit_reflect_box(int a0)
{
    S4C *dst = (S4C *)(cameraSetOrg[1] + a0 * 0x4C);
    S4C *src = (S4C *)(cameraSetEdit[1] + a0 * 0x4C);
    int saved = dst->items;
    int i;
    *dst = *src;
    dst->items = saved;
    i = 0;
    while (i < ((S4C *)CameraEdit_BOX(a0))->end - ((S4C *)CameraEdit_BOX(a0))->first) {
        CameraEdit_reflect_pin(a0, i);
        i++;
    }
}

inline void CameraEdit_reflect_pin(int a0, int a1)
{
    PinRec *dst = (PinRec *)(((S4C *)(cameraSetOrg[1] + a0 * 0x4C))->items + a1 * 0x5C);
    PinRec *src = (PinRec *)(((S4C *)(cameraSetEdit[1] + a0 * 0x4C))->items + a1 * 0x5C);
    *dst = *src;
}

inline int CameraEdit_BOX_NUMBER(void)
{
    return *cameraSetEdit;
}

inline int CameraEdit_PIN_NUMBER(int a0)
{
    int r1 = CameraEdit_BOX(a0);
    int r2 = CameraEdit_BOX(a0);
    return ((S4C *)r1)->end - ((S4C *)r2)->first;
}

inline int CameraEdit_PIN_NUMBER_ALL(int *a0, int a1)
{
    int sum = 0;
    int i;
    for (i = 0; i < a1; i++) {
        sum += a0[15] - a0[14];
    }
    return sum;
}

inline int CameraEdit_BOX(int a0)
{
    return cameraSetEdit[1] + a0 * 0x4C;
}

inline PinRec *CameraEdit_PIN(int a0, int a1)
{
    return (PinRec *)((S4C *)(cameraSetEdit[1] + a0 * 0x4C))->items + a1;
}

inline void CameraEdit_DispPin(int box, int pin)
{
    dispPinRange(box, pin, pin + 1);
}

/* the pin a new pin starts from; ConvertCameraSetBuffer gives it the stage's
   hand-camera rate */
PinRec cameraPinDefault = {{0.0f, -500.0f, 0.0f},
                           {0.0f, 300.0f, 300.0f},
                           {300.0f},
                           0,
                           0.0f,
                           0,
                           0.0f,
                           1,
                           60.0f,
                           0.0f,
                           0.0f,
                           0.0f,
                           10.0f,
                           10.0f,
                           {120.0f, 80.0f}};

/* sixteen zero bytes between the two defaults; nothing reads them */
static float cameraEditVec[4] = {0.0f}; /* derived name */

/* the group a new group starts from: named "0", a 100-unit box at the
   origin */
BoxRec cameraGroupDefault = {"0", 0.0f, 0.0f, 0.0f, 100.0f, 100.0f, 100.0f};

/* a 128-byte record after the group default, -1 at 0x40, 50.0 at 0x64 and
   1 at 0x68; nothing reads it */
static struct { /* field names derived */
    int pad00[16];
    int word40;
    int pad44[8];
    float float64;
    int word68;
    int pad6C[5];
} cameraEditRec = {{0}, -1, {0}, 50.0f, 1}; /* derived name */

inline void ConvertCameraSetBuffer(int n, S4C *item, char *groups)
{
    CamMgr *m1;
    CamMgr *m2;
    int i;
    int j;
    int a;
    int b;
    char *f;
    cameraPinDefault.handCameraRate = stageData[stage_no].handCameraRate;
    m1 = (CamMgr *)cameraSetOrg;
    m1->items = (char *)m1 + 0x70;
    m1->pool = (char *)m1 + 0x1E20;
    m1->count = 0;
    f = &m1->flags[99];
    for (a = 99; a >= 0; a--) {
        *f-- = 0;
    }
    m2 = (CamMgr *)cameraSetEdit;
    m2->items = (char *)m2 + 0x70;
    m2->pool = (char *)m2 + 0x1E20;
    m2->count = 0;
    f = &m2->flags[99];
    for (b = 99; b >= 0; b--) {
        *f-- = 0;
    }
    for (i = 0; i < n; i++) {
        CameraEdit_add_box(item);
        for (j = item->first; j < item->end; j++) {
            CameraEdit_add_pin(i, groups + j * 0x5C);
        }
        item++;
    }
}

inline void CameraEdit_Enter(void) {}
