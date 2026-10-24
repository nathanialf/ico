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
#include "DisplayP2O.h"
#include "Light.h"

/* The object initGeometryState builds on its stack to hand SetMotionDirection
   the display object at 0x15C.  The word there is a union, so each read of it
   follows the stores made through it; as a GObj with its Sub15C * field the
   reads merge and initGeometryState is 0x58 bytes shorter (measured). */
typedef union { /* field names derived */
    Sub15C *d;
    int i;
    float f;
} DObjWord; /* derived name */

typedef struct { /* field names derived */
    char pad[348];
    DObjWord data;
    char pad2[32];
} DObjGObj; /* derived name */

typedef union { /* field names derived */
    int i[8];
    long long w[4];
} DObjBlk20; /* derived name */

typedef struct { /* field names derived */
    long long w[2];
} DObjBlk10; /* derived name */

/* The unit +Z direction the motion state starts from, with a long long view
   for its 8-byte copy. */
typedef union { /* field names derived */
    float f[4];
    long long w[2];
} DObjVec; /* derived name */

typedef union { /* field names derived */
    float q[4][4];
    long long w[8];
} DObjBlk40; /* derived name */

#ifdef VERSION_NTSC
/* The four DObj templates (names derived).  The record is 0x850 bytes, the
   size CSVSYSTEM_InitDObj allocates before the copy; its named fields are the
   words the template sets.  The slot table pointer at 0x810 and the character
   file id at 0x84 are named from this file; the parent link at 0x00, the
   collision words at 0x70 to 0x80 and the accessary row at 0x814.  The long long pads give the record the
   8-byte alignment its copy loop uses. */
typedef struct { /* field names derived */
    ObjNode parent;
    long long pad08[13];
    int colData;
    int disp;
    int colRotate;
    int cylinderOn;
    int colPerNode;
    int charFileId;
    long long pad88[241];
    char *slotTable;
    int accessary;
    long long pad818[7];
} DObjRecord; /* derived name */

static DObjRecord emptyDObj = {
    {0, -1}, {0}, 0, 1, 1, 1, 0, 1515, {0}, 0, -1, {0},
}; /* derived name */
#else
#ifdef VERSION_AUG6
/* The four DObj templates (names derived).  The record is 0x840 bytes, the
   size CSVSYSTEM_InitDObj allocates before the copy; its named fields are the
   words the template sets.  The slot table pointer at 0x800 and the character
   file id at 0x84 are named from this file; the parent link at 0x00, the
   collision words at 0x70 to 0x80 and the accessary row at 0x804 as Sub15C
   (typedef.h) names them (this build's record is 0x40 bytes shorter than the
   one Sub15C describes, whose slot table sits at 0x840).  The long long pads give the record the
   8-byte alignment its copy loop uses. */
typedef struct { /* field names derived */
    ObjNode parent;
    long long pad08[13];
    int colData;
    int disp;
    int colRotate;
    int cylinderOn;
    int colPerNode;
    int charFileId;
    long long pad88[239];
    char *slotTable;
    int accessary;
    long long pad808[7];
} DObjRecord; /* derived name */

static DObjRecord emptyDObj = {
    {0, -1}, {0}, 0, 1, 1, 1, 0, 1510, {0}, 0, -1, {0},
}; /* derived name */
#else
/* The four DObj templates (names derived).  The record is 0x880 bytes, the
   size CSVSYSTEM_InitDObj allocates before the copy; its named fields are the
   words the template sets.  The slot table pointer at 0x840 and the character
   file id at 0x84 are named from this file; the parent link at 0x00, the
   collision words at 0x70 to 0x80 and the accessary row at 0x844 as Sub15C
   (typedef.h) names the same offsets.  The long long pads give the record the
   8-byte alignment its copy loop uses. */
typedef struct { /* field names derived */
    ObjNode parent;
    long long pad08[13];
    int colData;
    int disp;
    int colRotate;
    int cylinderOn;
    int colPerNode;
    int charFileId;
    long long pad88[247];
    char *slotTable;
    int accessary;
    long long pad848[7];
} DObjRecord; /* derived name */

#if defined(VERSION_JPN) || defined(VERSION_KOR)
static DObjRecord emptyDObj = {
    {0, -1}, {0}, 0, 1, 1, 1, 0, 1548, {0}, 0, -1, {0},
}; /* derived name */
#else
static DObjRecord emptyDObj = {
    {0, -1}, {0}, 0, 1, 1, 1, 0, 1552, {0}, 0, -1, {0},
}; /* derived name */
#endif
#endif
#endif

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

/* The motion record at 0x680, cleared before the motion buffers. */
static DObjMotion initialGeoWork = {{0}}; /* derived name */

/* One entry of the blend rotation array at 0x818: four identity
   quaternions. */
static DObjBlk40 initialBlendRot = {{
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
}}; /* derived name */

static inline void initGeometryScaleRatio(Sub15C *d) /* derived name */
{
    float r;
    float t;

    r = 1.0f;
    if (d->skel != 0) {
        t = (d->nodes->scale[0] + d->nodes->scale[1] + d->nodes->scale[2]) * 0.333f;
        r = 1.0f / (d->skel->pos[1] * t * 2.0f * 1.5f);
    }
    d->scaleRatio = r;
}

static void initGeometryState(Sub15C *self, SObjSimpleSetting *lay)
{
    DObjGObj g;
    DObjGObj *p;
    int i;
    int j;
    int k;
    int m;
    int n;

    p = &g;
    g.data.d = self;
    InitMotionGeoInfo(&self->root, lay->pos[0], lay->pos[1], lay->pos[2], lay->rot[0], lay->rot[1],
                      lay->rot[2]);
    InitMotionStateInfo(&p->data.d->ctrl);
    InitFrameDependSequence(p->data.d->fdsFlags);
    p->data.d->motion = initialGeoWork;

    if (p->data.d->skel != 0) {
        p->data.d->root.plane.f[3] =
            p->data.d->root.plane.f[3] + p->data.d->skel->pos[1] * self->nodes->scale[0];
#ifdef VERSION_NTSC
        p->data.d->blendBuf =
            iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 5, __FILE__, 124);
        p->data.d->motionBuf =
            iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 5, __FILE__, 126);
#else
        p->data.d->blendBuf = iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 5,
                                             __FILE__, LN(125, 125, 125, 125, 124));
        p->data.d->motionBuf = iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 5,
                                              __FILE__, LN(127, 127, 127, 127, 126));
#endif
        InitMotionRotElem(p->data.d->blendBuf, p->data.d->skelNodeNum);
        InitMotionRotElem(p->data.d->motionBuf, p->data.d->skelNodeNum);
        CopyVector(p->data.d->localPos, ZeroPoint);
        CopyVector(p->data.d->localPos, ZeroPoint);
        CopyVector(p->data.d->localMove, ZeroVector);
        p->data.d->localHeight = 0.0f;
        p->data.d->local = InitialObjPointer;
#ifdef VERSION_NTSC
        p->data.d->nodeRotElem =
            iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 6, __FILE__, 136);
#else
        p->data.d->nodeRotElem = iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 6,
                                                __FILE__, LN(137, 137, 137, 137, 136));
#endif
        for (i = 0; i < p->data.d->skelNodeNum; i++) {
            *(DObjBlk40 *)&p->data.d->nodeRotElem[i] = initialRotElem;
        }
#ifdef VERSION_NTSC
        p->data.d->nodeLimit =
            iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 2, __FILE__, 144);
#else
        p->data.d->nodeLimit = iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 2,
                                              __FILE__, LN(145, 145, 145, 145, 144));
#endif
        for (j = 0; j < p->data.d->skelNodeNum; j++) {
            p->data.d->nodeLimit[j] = 0;
        }
#ifdef VERSION_NTSC
        p->data.d->nodeVec =
            iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 4, __FILE__, 152);
#else
        p->data.d->nodeVec = iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 4,
                                            __FILE__, LN(153, 153, 153, 153, 152));
#endif
        for (k = 0; k < p->data.d->skelNodeNum; k++) {
            CopyVector(p->data.d->nodeVec[k], ZeroVector);
        }
#ifdef VERSION_NTSC
        p->data.d->blendRot =
            iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 6, __FILE__, 160);
#else
        p->data.d->blendRot = iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum << 6,
                                             __FILE__, LN(161, 161, 161, 161, 160));
#endif
        for (m = 0; m < p->data.d->skelNodeNum; m++) {
            *(DObjBlk40 *)p->data.d->blendRot[m] = initialBlendRot;
        }
#ifdef VERSION_NTSC
        p->data.d->blendless =
            iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum, __FILE__, 168);
#else
        p->data.d->blendless = iosMallocDebug(ios_partition_sugipon, p->data.d->skelNodeNum,
                                              __FILE__, LN(169, 169, 169, 169, 168));
#endif
        for (n = 0; n < p->data.d->skelNodeNum; n++) {
            p->data.d->blendless[n] = 0;
        }

        {
            DObjVec dir = {{0.0f, 0.0f, 1.0f, 1.0f}};
            _ApplyRyGV(dir.f, -lay->rot[1]);
            SetMotionDirection((GObj *)p, dir.f);
        }
    } else {
        p->data.d->blendBuf = 0;
        p->data.d->nodeRotElem = 0;
        p->data.d->nodeLimit = 0;
        p->data.d->nodeVec = 0;
        p->data.d->blendRot = 0;
        p->data.d->blendless = 0;
    }
    p->data.d->rideFunc = 0;
    *(DObjBlk20 *)&p->data.d->streamScale = initialGeoState;
    initGeometryScaleRatio(p->data.d);
}

static void initMatrixDObj(Sub15C *self, SObjSimpleSetting *lay)
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
    CopyMatrix(self->matrix, MatrixDrive_GetMatrix());

    SetIdentityQuaternion(self->quat);
    RotQuaternionY(self->quat, (short)(lay->rot[1] * 32768.0f / d));
    RotQuaternionX(self->quat, (short)(lay->rot[0] * 32768.0f / d));
    RotQuaternionZ(self->quat, (short)(lay->rot[2] * 32768.0f / d));
    MatrixDrive_PopMatrix();
}

typedef struct DObjNode DObjNode; /* derived name */

/* A block's node is addressed as an int sum, the index first: the ROM adds
   in that order, and &nodes[i] or nodes + i put the base first (measured). */
static void allocObjectData(Sub15C *self, SObjSimpleSetting *lay, int n)
{
    int i;
    int j;
    int k;

#ifdef VERSION_NTSC
    self->nodes = iosMallocDebug(ios_partition_seki, n * 80, __FILE__, 298);
#else
    self->nodes = iosMallocDebug(ios_partition_seki, n * 80, __FILE__, LN(299, 299, 299, 299, 298));
#endif
    for (i = 0; i < n; i++) {
        self->nodes[i].flags.ll &= ~1;
        self->nodes[i].flags.ll &= ~2;
        {
            DObjNode *e = (DObjNode *)(i * 80 + (int)self->nodes);
            e->flags.ll &= ~4;
            e->pos[1] = 0.0f;
            e->pos[2] = 0.0f;
            e->pos[3] = 1.0f;
            e->pos[0] = 0.0f;
        }
        {
            DObjNode *e = (DObjNode *)(i * 80 + (int)self->nodes);
            e->fade = 0.0f;
            e->alpha = 1.0f;
            *(short *)((char *)e + 0x3A) = 0;
            e->scale[0] = 1.0f;
            e->scale[1] = 1.0f;
            e->scale[2] = 1.0f;
        }
    }
    for (j = 0; j < n; j++) {
        for (k = 0; k < 4; k++) {
            self->nodes[j].rot[k] = 0;
            self->nodes[j].word10[k] = 0;
        }
        self->nodes[j].flags.ll &= ~2;
        {
            DObjNode *e = (DObjNode *)(j * 80 + (int)self->nodes);
            e->pos[0] = e->pos[1] = e->pos[2] = 0.0f;
            e->pos[3] = 1.0f;
            e->flags.ll &= ~4;
        }
        self->nodes[j].flags.ll &= ~1;
        {
            DObjNode *e = (DObjNode *)(j * 80 + (int)self->nodes);
            e->fade = 0.0f;
            e->alpha = 1.0f;
            *(short *)((char *)e + 0x3A) = 0;
            _CopyVector(e->scale, lay->scale);
        }
    }
}

static void initInitialInverseMatrix(Sub15C *d)
{
#ifdef VERSION_NTSC
    char *m = iosMallocDebug(ios_partition_sugipon, d->skelNodeNum << 6, __FILE__, 332);
#else
    char *m = iosMallocDebug(ios_partition_sugipon, d->skelNodeNum << 6, __FILE__,
                             LN(333, 333, 333, 333, 332));
#endif
    d->clusterMtx = m;
    GetInitialInverseMatrixByDObj(m, d);
}

static inline void initPolyHead(Sub15C *d) /* derived name */
{
    PObjModel *h;
    Sub15C *q;

    h = d->model;
    q = h->dobj;
#ifdef VERSION_NTSC
    d->lightMtx = iosMallocDebug(ios_partition_seki, 256, __FILE__, 237);
#else
    d->lightMtx = iosMallocDebug(ios_partition_seki, 256, __FILE__, LN(238, 238, 238, 238, 237));
#endif
    d->lightMtx->mode = q->lightMtx->mode;
    if (d->lightMtx->mode == 4) {
        h->mode.s.type = 3;
    } else {
        h->mode.s.type = h->disp > 0;
        if (h->parts->lineCount != 0) {
            h->mode.s.type = 2;
        }
    }
}

static inline void allocMatrixArrays(Sub15C *d, int n) /* derived name */
{
    int i;

#ifdef VERSION_NTSC
    *(char **)&d->nodeMtx = iosMallocDebug(ios_partition_seki, n * 64, __FILE__, 258);
    *(char **)&d->nodeQuat = iosMallocDebug(ios_partition_seki, n * 16, __FILE__, 258);
#else
    *(char **)&d->nodeMtx =
        iosMallocDebug(ios_partition_seki, n * 64, __FILE__, LN(259, 259, 259, 259, 258));
    *(char **)&d->nodeQuat =
        iosMallocDebug(ios_partition_seki, n * 16, __FILE__, LN(259, 259, 259, 259, 258));
#endif
    d->nodeNum = n;
    for (i = 0; i < n; i++) {
        _CopyMatrix(*(char **)&d->nodeMtx + i * 64, d->matrix);
        CopyQuaternion(*(char **)&d->nodeQuat + i * 16, d->quat);
    }
}

static inline void applySkeltonMatrices(Sub15C *d) /* derived name */
{
    int i;

    GetInitialSkeltonMatrixByDObj(d);
    for (i = 0; i < d->skelNodeNum; i++) {
        _MulMatrix(*(char **)&d->nodeMtx + i * 64, d->matrix, *(char **)&d->nodeMtx + i * 64);
    }
}

static inline void allocMorphWeights(Sub15C *d, int n) /* derived name */
{
    int i;

#ifdef VERSION_NTSC
    d->morphWeight = iosMallocDebug(ios_partition_seki, n * 4, __FILE__, 282);
#else
    d->morphWeight =
        iosMallocDebug(ios_partition_seki, n * 4, __FILE__, LN(283, 283, 283, 283, 282));
#endif
    for (i = 0; i < n; i++) {
        d->morphWeight[i] = 0.0f;
    }
}

static void initPolygonState(Sub15C *d, SObjSimpleSetting *lay)
{
    PObjModel *p;
    PObjPart *e;
    unsigned int mx;
    int j;
    int k;

    mx = 0;
    p = d->model;
    initMatrixDObj(d, lay);
    initPolyHead(d);

    k = p->mode.s.type;
    switch (k) {
    case 1:
        d->dispType = k;
        d->nodeNum = d->skelNodeNum;
        allocMatrixArrays(d, d->skelNodeNum);
        allocObjectData(d, lay, p->partCount);
        applySkeltonMatrices(d);
        break;
    case 0:
    case 2:
    case 3:
        d->dispType = 0;
        d->nodeNum = d->skelNodeNum < p->partCount ? p->partCount : d->skelNodeNum;
        allocMatrixArrays(d, d->nodeNum);
        allocObjectData(d, lay, p->partCount);
        break;
    }

    for (j = 0; j < p->partCount; j++) {
        e = &p->parts[j];
        if (mx < e->morphCount) {
            mx = e->morphCount;
        }
    }

    if (p->mode.s.type == 1) {
        if (mx != 0) {
            allocMorphWeights(d, mx);
        }
        d->morphNum = mx;
    } else {
        if (mx != 0) {
            allocMorphWeights(d, 6);
        }
        d->morphNum = mx;
    }
}

inline void FreeDObj(void) {}

/* the skeleton node of kind id, or -1 */
static inline int findSlot(Sub15C *d, int id) /* derived name */
{
    SkelNode *p;
    int k;

    p = d->skel;
    k = 0;
    while (p[k].mirror != -1) {
        if (p[k].kind == id) {
            return k;
        }
        k++;
    }
    return -1;
}

/* the 53-entry focus node table */
static inline void makeSlotTable(Sub15C *d) /* derived name */
{
    int i;

#ifdef VERSION_NTSC
    d->focusNodes = iosMallocDebug(ios_partition_sugipon, 53, __FILE__, 439);
#else
    d->focusNodes =
        iosMallocDebug(ios_partition_sugipon, 53, __FILE__, LN(440, 440, 440, 440, 439));
#endif
    for (i = 0; i < 53; i++) {
        d->focusNodes[i] = findSlot(d, i);
    }
}

#ifdef VERSION_NTSC
Sub15C *CSVSYSTEM_InitDObj(int id, SObjSimpleSetting *lay)
{
    Sub15C *d;

    d = iosMallocDebug(ios_partition_seki, sizeof(DObjRecord), __FILE__, 462);
    *(DObjRecord *)d = emptyDObj;
    if (id != 1515) {
        CSVSYSTEM_ReadCharFiles(d, id);
    }
    debug_StdPrintfDummy("\x1b[35mALLOCED DOBJ\x1b[m\n");
    if (d->model != 0 || d->skel != 0) {
        initPolygonState(d, lay);
    }
    debug_StdPrintfDummy("\x1b[35mINITED POLYGONSTATE\x1b[m\n");
    initGeometryState(d, lay);
    debug_StdPrintfDummy("\x1b[35mINITED GEOMETRYSTATE\x1b[m\n");
    if (d->skel != 0) {
        initInitialInverseMatrix(d);
        makeSlotTable(d);
    }
    debug_StdPrintfDummy("\x1b[35mEND OF INIT DOBJ\x1b[m\n");
    return d;
}
#else
Sub15C *CSVSYSTEM_InitDObj(int id, SObjSimpleSetting *lay)
{
    Sub15C *d;

    d = iosMallocDebug(ios_partition_seki, sizeof(DObjRecord), __FILE__,
                       LN(463, 463, 463, 463, 462));
    *(DObjRecord *)d = emptyDObj;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    if (id != 1548) {
#else
#ifdef VERSION_AUG6
    if (id != 1510) {
#else
    if (id != 1552) {
#endif
#endif
        CSVSYSTEM_ReadCharFiles(d, id);
    }
    debug_StdPrintfDummy("\x1b[35mALLOCED DOBJ\x1b[m\n");
    if (d->model != 0 || d->skel != 0) {
        initPolygonState(d, lay);
    }
#ifndef VERSION_AUG6
    debug_StdPrintfDummy(" ------------------ allocate DOBJ %p: POBJ: %p\n", d, d->model);
#endif
    debug_StdPrintfDummy("\x1b[35mINITED POLYGONSTATE\x1b[m\n");
    initGeometryState(d, lay);
    debug_StdPrintfDummy("\x1b[35mINITED GEOMETRYSTATE\x1b[m\n");
    if (d->skel != 0) {
        initInitialInverseMatrix(d);
        makeSlotTable(d);
    }
    debug_StdPrintfDummy("\x1b[35mEND OF INIT DOBJ\x1b[m\n");
    return d;
}
#endif

inline void LinkParentOfDObj(void *obj, ObjNode *link)
{
    LocalizeGeometry(obj, link);
    GOBJ_SUB(obj)->parent = *link;
}

inline void UnlinkParentOfDObj(void *obj)
{
    GlobalizeGeometry(obj);
    GOBJ_SUB(obj)->parent = InitialObjPointer;
}
