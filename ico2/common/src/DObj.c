#include "charFileManager.h"
#include "debug.h"
#include "fieldCollision.h"
#include "memory.h"
#include "gv.h"
#include "Matrix.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "quaternion.h"
#include "ios.h"
#include "DObj.h"

typedef union {
    char *p;
    int i;
    float f;
} DObjWord;

typedef struct {
    char pad[348];
    DObjWord data;
    char pad2[32];
} DObjGObj;

typedef union {
    int i[8];
    long long w[4];
} DObjBlk20;

typedef struct {
    long long w[2];
} DObjBlk10;

/* The unit +Z direction the motion state starts from, with a long long view
   for its 8-byte copy. */
typedef union {
    float f[4];
    long long w[2];
} DObjVec;

typedef union {
    float q[4][4];
    long long w[8];
} DObjBlk40;

typedef struct {
    long long w[24];
} DObjBlkC0;

/* The four DObj templates (names derived).  The record is 0x880 bytes, the
   size CSVSYSTEM_InitDObj allocates before the copy; the slot table pointer
   at 0x840 and the character file id at 0x84 are its named fields.  The long
   long pads give the record the 8-byte alignment its copy loop uses. */
typedef struct {
    int f00;
    int f04;
    long long pad08[13];
    int f70;
    int f74;
    int f78;
    int f7C;
    int f80;
    int charFileId;
    long long pad88[247];
    char *slotTable;
    int f844;
    long long pad848[7];
} DObjRecord;

static DObjRecord emptyDObj = {
    0, -1, {0}, 0, 1, 1, 1, 0, 1552, {0}, 0, -1, {0},
}; /* derived name */

/* One entry of the rotation element array at 0x80c: a zero vector then
   three identity quaternions. */
static DObjBlk40 initialRotElem = {{
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
}}; /* derived name */

/* The 32-byte record at 0x660 that closes initGeometryState. */
static DObjBlk20 initialGeoState = {{1, 0, 0, 0, 0, 0, 0, 0}}; /* derived name */

/* The 192-byte record at 0x680, cleared before the motion buffers. */
static DObjBlkC0 initialGeoWork = {{0}}; /* derived name */

/* One entry of the blend rotation array at 0x818: four identity
   quaternions. */
static DObjBlk40 initialBlendRot = {{
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
}}; /* derived name */

static inline void initGeometryScaleRatio(char *d) /* derived name */
{
    float r;
    float t;

    r = 1.0f;
    if (*(char **)(d + 0x8C) != 0) {
        t = (*(float *)(*(char **)(d + 0x870) + 0x20) + *(float *)(*(char **)(d + 0x870) + 0x24) +
             *(float *)(*(char **)(d + 0x870) + 0x28)) *
            0.333f;
        r = 1.0f / (*(float *)(*(char **)(d + 0x8C) + 0x14) * t * 2.0f * 1.5f);
    }
    *(float *)(d + 0x824) = r;
}

static void initGeometryState(char *self, SObjSimpleSetting *lay)
{
    DObjGObj g;
    DObjGObj *p;
    int i;
    int j;
    int k;
    int m;
    int n;

    p = &g;
    g.data.p = self;
    InitMotionGeoInfo(self + 0xA0, lay->pos[0], lay->pos[1], lay->pos[2], lay->rot[0], lay->rot[1],
                      lay->rot[2]);
    InitMotionStateInfo(p->data.p + 0x470);
    InitFrameDependSequence(p->data.p + 0x740);
    *(DObjBlkC0 *)(p->data.p + 0x680) = initialGeoWork;

    if (*(char **)(p->data.p + 0x8C) != 0) {
        *(float *)(p->data.p + 0x1DC) =
            *(float *)(p->data.p + 0x1DC) + *(float *)(*(char **)(p->data.p + 0x8C) + 0x14) *
                                                *(float *)(*(char **)(self + 0x870) + 0x20);
        *(void **)(p->data.p + 0x7D0) =
            iosMallocDebug(ios_partition_sugipon, *(int *)(p->data.p + 0x88) << 5, __FILE__, 125);
        *(void **)(p->data.p + 0x7B4) =
            iosMallocDebug(ios_partition_sugipon, *(int *)(p->data.p + 0x88) << 5, __FILE__, 127);
        InitMotionRotElem(*(void **)(p->data.p + 0x7D0), *(int *)(p->data.p + 0x88));
        InitMotionRotElem(*(void **)(p->data.p + 0x7B4), *(int *)(p->data.p + 0x88));
        CopyVector(p->data.p + 0x7E0, ZeroPoint);
        CopyVector(p->data.p + 0x7E0, ZeroPoint);
        CopyVector(p->data.p + 0x7F0, ZeroVector);
        *(int *)(p->data.p + 0x808) = 0;
        *(ObjNode *)(p->data.p + 0x800) = InitialObjPointer;
        *(void **)(p->data.p + 0x80C) =
            iosMallocDebug(ios_partition_sugipon, *(int *)(p->data.p + 0x88) << 6, __FILE__, 137);
        for (i = 0; i < *(int *)(p->data.p + 0x88); i++) {
            *(DObjBlk40 *)(*(char **)(p->data.p + 0x80C) + i * 64) = initialRotElem;
        }
        *(void **)(p->data.p + 0x810) =
            iosMallocDebug(ios_partition_sugipon, *(int *)(p->data.p + 0x88) << 2, __FILE__, 145);
        for (j = 0; j < *(int *)(p->data.p + 0x88); j++) {
            *(int *)(*(char **)(p->data.p + 0x810) + j * 4) = 0;
        }
        *(void **)(p->data.p + 0x814) =
            iosMallocDebug(ios_partition_sugipon, *(int *)(p->data.p + 0x88) << 4, __FILE__, 153);
        for (k = 0; k < *(int *)(p->data.p + 0x88); k++) {
            CopyVector(*(char **)(p->data.p + 0x814) + k * 16, ZeroVector);
        }
        *(void **)(p->data.p + 0x818) =
            iosMallocDebug(ios_partition_sugipon, *(int *)(p->data.p + 0x88) << 6, __FILE__, 161);
        for (m = 0; m < *(int *)(p->data.p + 0x88); m++) {
            *(DObjBlk40 *)(*(char **)(p->data.p + 0x818) + m * 64) = initialBlendRot;
        }
        *(void **)(p->data.p + 0x820) =
            iosMallocDebug(ios_partition_sugipon, *(int *)(p->data.p + 0x88), __FILE__, 169);
        for (n = 0; n < *(int *)(p->data.p + 0x88); n++) {
            *(char *)(*(char **)(p->data.p + 0x820) + n) = 0;
        }

        {
            DObjVec dir = {{0.0f, 0.0f, 1.0f, 1.0f}};
            _ApplyRyGV(&dir, -lay->rot[1]);
            SetMotionDirection(p, &dir);
        }
    } else {
        *(void **)(p->data.p + 0x7D0) = 0;
        *(void **)(p->data.p + 0x80C) = 0;
        *(void **)(p->data.p + 0x810) = 0;
        *(void **)(p->data.p + 0x814) = 0;
        *(void **)(p->data.p + 0x818) = 0;
        *(void **)(p->data.p + 0x820) = 0;
    }
    *(void **)(p->data.p + 0x81C) = 0;
    *(DObjBlk20 *)(p->data.p + 0x660) = initialGeoState;
    initGeometryScaleRatio(p->data.p);
}

static void initMatrixDObj(char *self, SObjSimpleSetting *lay)
{
    float v[4];
    float d;

    MatrixDrive_PushMatrix();
    CopyVector(v, lay->pos);
    d = 3.1415927f;
    v[3] = 1.0f;
    _UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(v);
    MatrixDrive_RotMatrixY((short)(lay->rot[1] * 32768.0f / d));
    MatrixDrive_RotMatrixX((short)(lay->rot[0] * 32768.0f / d));
    MatrixDrive_RotMatrixZ((short)(lay->rot[2] * 32768.0f / d));
    CopyMatrix(self + 0x20, MatrixDrive_GetMatrix());

    SetIdentityQuaternion(self + 0x60);
    RotQuaternionY(self + 0x60, (short)(lay->rot[1] * 32768.0f / d));
    RotQuaternionX(self + 0x60, (short)(lay->rot[0] * 32768.0f / d));
    RotQuaternionZ(self + 0x60, (short)(lay->rot[2] * 32768.0f / d));
    MatrixDrive_PopMatrix();
}

typedef struct DObjNode DObjNode;

typedef union {
    long long ll;
    int i[2];
} DObjFlags;

static void allocObjectData(char *self, SObjSimpleSetting *lay, int n)
{
    int i;
    int j;
    int k;

    *(DObjNode **)(self + 0x870) =
        (DObjNode *)iosMallocDebug(ios_partition_seki, n * 80, __FILE__, 299);
    for (i = 0; i < n; i++) {
        {
            char *e = (char *)(i * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~1;
        }
        {
            char *e = (char *)(i * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~2;
        }
        {
            char *e = (char *)(i * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~4;
            *(float *)(e + 0x44) = 0.0f;
            *(float *)(e + 0x48) = 0.0f;
            *(float *)(e + 0x4C) = 1.0f;
            *(float *)(e + 0x40) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(DObjNode **)(self + 0x870));
            *(int *)(e + 0x30) = 0;
            *(float *)(e + 0x34) = 1.0f;
            *(short *)(e + 0x3A) = 0;
            *(float *)(e + 0x20) = 1.0f;
            *(float *)(e + 0x24) = 1.0f;
            *(float *)(e + 0x28) = 1.0f;
        }
    }
    for (j = 0; j < n; j++) {
        for (k = 0; k < 4; k++) {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            *(int *)(e + k * 4) = 0;
            *(int *)(e + 0x10 + k * 4) = 0;
        }
        {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~2;
        }
        {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            *(float *)(e + 0x40) = *(float *)(e + 0x44) = *(float *)(e + 0x48) = 0.0f;
            *(float *)(e + 0x4C) = 1.0f;
            ((DObjFlags *)(e + 0x38))->ll &= ~4;
        }
        {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~1;
        }
        {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            *(float *)(e + 0x30) = 0.0f;
            *(float *)(e + 0x34) = 1.0f;
            *(short *)(e + 0x3A) = 0;
            _CopyVector(e + 0x20, lay->scale);
        }
    }
}

static void initInitialInverseMatrix(char *d)
{
    char *m = iosMallocDebug(ios_partition_sugipon, *(int *)(d + 0x88) << 6, __FILE__, 333);
    *(char **)(d + 0x90) = m;
    GetInitialInverseMatrixByDObj(m, d);
}

typedef struct {
    unsigned long long lo : 16;
    unsigned long long kind : 2;
} PolyFlags;

static inline void initPolyHead(char *d) /* derived name */
{
    char *h;
    char *q;

    h = *(char **)(d + 0x854);
    q = *(char **)(h + 0x28);
    *(char **)(d + 0x874) = iosMallocDebug(ios_partition_seki, 0x100, __FILE__, 238);
    *(int *)(*(char **)(d + 0x874) + 0xF0) = *(int *)(*(char **)(q + 0x874) + 0xF0);
    if (*(int *)(*(char **)(d + 0x874) + 0xF0) == 4) {
        ((PolyFlags *)(h + 0x30))->kind = 3;
    } else {
        ((PolyFlags *)(h + 0x30))->kind = *(signed char *)(h + 0x2F) > 0;
        if (*(int *)(*(char **)(h + 0x40) + 0x114) != 0) {
            ((PolyFlags *)(h + 0x30))->kind = 2;
        }
    }
}

static inline void allocMatrixArrays(char *d, int n) /* derived name */
{
    int i;

    *(char **)(d + 0xC) = iosMallocDebug(ios_partition_seki, n * 64, __FILE__, 259);
    *(char **)(d + 0x10) = iosMallocDebug(ios_partition_seki, n * 16, __FILE__, 259);
    *(int *)(d + 0x8) = n;
    for (i = 0; i < n; i++) {
        _CopyMatrix(*(char **)(d + 0xC) + i * 64, d + 0x20);
        CopyQuaternion(*(char **)(d + 0x10) + i * 16, d + 0x60);
    }
}

static inline void applySkeltonMatrices(char *d) /* derived name */
{
    int i;

    GetInitialSkeltonMatrixByDObj(d);
    for (i = 0; i < *(int *)(d + 0x88); i++) {
        _MulMatrix(*(char **)(d + 0xC) + i * 64, d + 0x20, *(char **)(d + 0xC) + i * 64);
    }
}

static inline void allocIntTable(char *d, int n) /* derived name */
{
    int i;

    *(char **)(d + 0x838) = iosMallocDebug(ios_partition_seki, n * 4, __FILE__, 283);
    for (i = 0; i < n; i++) {
        *(int *)(*(char **)(d + 0x838) + i * 4) = 0;
    }
}

static void initPolygonState(char *d, SObjSimpleSetting *lay)
{
    char *p;
    char *e;
    unsigned int mx;
    int j;
    int k;

    mx = 0;
    p = *(char **)(d + 0x854);
    initMatrixDObj(d, lay);
    initPolyHead(d);

    k = (unsigned short)(*(unsigned long long *)(p + 0x30) >> 16) & 3;
    switch (k) {
    case 1:
        *(short *)(d + 0x84C) = k;
        *(int *)(d + 0x8) = *(int *)(d + 0x88);
        allocMatrixArrays(d, *(int *)(d + 0x88));
        allocObjectData(d, lay, *(signed char *)(p + 0x2E));
        applySkeltonMatrices(d);
        break;
    case 0:
    case 2:
    case 3:
        *(short *)(d + 0x84C) = 0;
        *(int *)(d + 0x8) = *(int *)(d + 0x88) < *(signed char *)(p + 0x2E)
                                ? *(signed char *)(p + 0x2E)
                                : *(int *)(d + 0x88);
        allocMatrixArrays(d, *(int *)(d + 0x8));
        allocObjectData(d, lay, *(signed char *)(p + 0x2E));
        break;
    }

    for (j = 0; j < *(signed char *)(p + 0x2E); j++) {
        e = *(char **)(p + 0x40) + j * 384;
        if (mx < *(unsigned int *)(e + 0x124)) {
            mx = *(unsigned int *)(e + 0x124);
        }
    }

    if ((*(unsigned long long *)(p + 0x30) & 0x30000) == 0x10000) {
        if (mx != 0) {
            allocIntTable(d, mx);
        }
        *(int *)(d + 0x834) = mx;
    } else {
        if (mx != 0) {
            allocIntTable(d, 6);
        }
        *(int *)(d + 0x834) = mx;
    }
}

inline void FreeDObj(void) {}

/* the slot index of the entry tagged id, or -1 */
static inline int findSlot(char *d, int id) /* derived name */
{
    char *p;
    int k;

    p = *(char **)(d + 0x8C);
    k = 0;
    while (*(int *)(p + k * 64) != -1) {
        if (*(int *)(p + k * 64 + 4) == id) {
            return k;
        }
        k++;
    }
    return -1;
}

/* the 53-entry slot lookup table */
static inline void makeSlotTable(char *d) /* derived name */
{
    int i;

    *(char **)(d + 0x840) = iosMallocDebug(ios_partition_sugipon, 53, __FILE__, 440);
    for (i = 0; i < 53; i++) {
        (*(char **)(d + 0x840))[i] = findSlot(d, i);
    }
}

Sub15C *CSVSYSTEM_InitDObj(int id, SObjSimpleSetting *lay)
{
    char *d;

    d = iosMallocDebug(ios_partition_seki, sizeof(DObjRecord), __FILE__, 463);
    *(DObjRecord *)d = emptyDObj;
    if (id != 0x610) {
        CSVSYSTEM_ReadCharFiles(d, id);
    }
    debug_StdPrintfDummy("\x1b[35mALLOCED DOBJ\x1b[m\n");
    if (*(int *)(d + 0x854) != 0 || *(int *)(d + 0x8C) != 0) {
        initPolygonState(d, lay);
    }
    debug_StdPrintfDummy(" ------------------ allocate DOBJ %p: POBJ: %p\n", d,
                         *(int *)(d + 0x854));
    debug_StdPrintfDummy("\x1b[35mINITED POLYGONSTATE\x1b[m\n");
    initGeometryState(d, lay);
    debug_StdPrintfDummy("\x1b[35mINITED GEOMETRYSTATE\x1b[m\n");
    if (*(int *)(d + 0x8C) != 0) {
        initInitialInverseMatrix(d);
        makeSlotTable(d);
    }
    debug_StdPrintfDummy("\x1b[35mEND OF INIT DOBJ\x1b[m\n");
    return (Sub15C *)d;
}

inline void LinkParentOfDObj(void *obj, PackedLL_19CAF0 *link)
{
    PackedLL_19CAF0 *p;
    LocalizeGeometry(obj, link);
    p = (PackedLL_19CAF0 *)GOBJ_SUB(obj);
    *p = *link;
}

inline void UnlinkParentOfDObj(void *obj)
{
    GlobalizeGeometry(obj);
    GOBJ_SUB(obj)->parent = InitialObjPointer;
}
