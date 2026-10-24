#include "DObj.h"
#include "debug.h"
#include "debug_exception.h"
#include "memory.h"
#include "gobj.h"
#include "gobj_dl.h"
#include "gobj_process.h"
#include "Basic.h"
#include "BgAnimation.h"
#include "StageAnimation.h"
#include "Light.h"
#include "Matrix.h"
#include "RegistPacket.h"
#include "quaternion.h"
#include "GsBase.h"
#include "main.h"
#include "gamesys.h"
#include <string.h>
#include <assert.h>

typedef union { /* field names derived */
    int i;
    float f;
} AnimWord; /* derived name */

#ifndef VERSION_JUN26
typedef union { /* field names derived */
    long l;
    short h;
} PlayWord; /* derived name */
#endif

typedef struct { /* field names derived */
    char bytes[8];
} Blob8; /* derived name */

#ifdef VERSION_JUN26
/* The 0x298-byte animation record stageAnimTable holds: the kind (0 for a
   BGA animation, 1 for an SDF camera), the object kinds, objects and data
   tables, the three entry pointers, and the object count, the node count
   and the count of play nodes made from it. */
typedef struct {          /* field names derived */
    signed char mode;     /* 0x000 */
    short kind[64];       /* 0x002 */
    GObj *obj[64];        /* 0x084 */
    int *data[64];        /* 0x184 */
    StageAnimDef *entry1; /* 0x284 */
    BgaHeader *entry2;    /* 0x288 */
    char *entry3;         /* 0x28C */
    int count : 16;       /* 0x290 */
    int nodes : 16;       /* 0x292 */
    int play : 16;        /* 0x294 */
} StageAnim;              /* derived name */
#else
/* the animation record's packed word: its object count, node count, play
   count and mode, read as the shifted word */
typedef union { /* field names derived */
    int i;

    struct {
        int count : 10;
        int nodes : 10;
        int play : 10;
        int mode : 2;
    } b;
} StageFlags; /* derived name */

typedef struct AnimNode { /* field names derived */
    long bits;            /* 0x00 */
    char pad08[12];
    struct AnimNode *next; /* 0x14 */
} AnimNode;                /* derived name */

/* The 0x290-byte animation record stageAnimTable holds: the kind, object and
   data tables, the three entry pointers and the packed count/mode word. */
typedef struct {          /* field names derived */
    short kind[64];       /* 0x000 */
    GObj *obj[64];        /* 0x080 */
    int *data[64];        /* 0x180 */
    StageAnimDef *entry1; /* 0x280 */
    BgaHeader *entry2;    /* 0x284 */
    char *entry3;         /* 0x288 */
    StageFlags flags;     /* 0x28C */
} StageAnim;              /* derived name */
#endif

/* The number of loaded animation records, the head of the play-node list,
   and the record table stage_Init fills, 87 records of 0x290 bytes. */
static int stageAnimCount; /* derived name */

static BgaPlayNode *bgaPlayList; /* derived name */

#ifdef VERSION_NTSC
static StageAnim stageAnimTable[82]; /* derived name */
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
/* the number of play nodes stage_MakePlayBgAnimation has linked and
   stage_KillPlayBgAnimation has not yet freed */
static int bgaPlayCount; /* derived name */

/* the objects stage_PlayBgAnimation and stage_DispAnimation count in a
   frame, printed as "O:%d" and cleared at the end of stage_DispAnimation */
static int stageAnimObjCount; /* derived name */

#ifdef VERSION_JUN26
static StageAnim stageAnimTable[80]; /* derived name */
#else
static StageAnim stageAnimTable[82]; /* derived name */
#endif
#else
static StageAnim stageAnimTable[87]; /* derived name */
#endif
#endif

#include "ios.h"
#include <stdio.h>

/* objAction's row as this file reads it: the two stage animations the
   object plays (typedef.h's OaRecB carries them as baseMode and anim2) */
typedef struct { /* field names derived */
    int anim[2]; /* 0x00 */
    char pad8[12];
} StgBgaSet; /* derived name */

extern StgBgaSet objAction[];
extern StageAnimDef stageTable[];

static void stage_MakeGObj(int *dat, int no)
{
    SObjSimpleSetting init = {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
    int i;
    GObj *g;
    Sub15C *d;
#ifndef VERSION_JUN26
    int w;
#endif
    int kind = dat[0];
    int aux = dat[1];
    StageAnim *e = &stageAnimTable[no];

#ifdef VERSION_JUN26
    for (i = 0; i < e->count; i++) {
#else
    for (i = 0; i < e->flags.b.count; i++) {
#endif
        if (e->kind[i] == kind) {
            debug_StdPrintfDummy("Bga Object Already %d %d %d\n", kind, kind, no);
            return;
        }
    }
    g = isysGObjAdd(0, 0, 0);
    if (g == 0) {
        debug_StdPrintfDummy("stage_MakeGObj:can't alloc gobj %d\n", no);
        debug_assert(__FILE__, LN(541, 525, 525, 501, 475, 404));
        __assert(__FILE__, LN(541, 525, 525, 501, 475, 404), "0");
    }
#ifdef VERSION_JUN26
    e->kind[e->count] = kind;
#else
    e->kind[e->flags.b.count] = kind;
#endif
    g->labelType = 1;
    g->labelId = 0;
    isysGObjKindTableAdd(g, aux);
    isysGObjProcAdd(g, 0, 1, 0x16);
    isysGObjProcAdd(g, 0, 1, 0x17);
    isysGObjProcAdd(g, 0, 1, 0x18);
    isysGObjLinkObjDL(g, 0, 0, 7, 0xFFFFFFFF);
    g->word24 = 0;
#ifdef VERSION_JUN26
    e->obj[e->count] = g;
#else
    e->obj[e->flags.b.count] = g;
#endif
    d = CSVSYSTEM_InitDObj(kind, &init);
    *(int *)&g->dobj = (int)d;
    d->colPerNode = 1;
#ifdef VERSION_JUN26
    e->data[e->count] = dat;
    e->count++;
    if (e->count >= 64) {
        debug_Assert("Too much Stage Animation Objects.\n");
        debug_assert(__FILE__, LN(541, 525, 525, 501, 475, 425));
        __assert(__FILE__, LN(541, 525, 525, 501, 475, 425), "0");
#else
    e->data[e->flags.b.count] = dat;
    w = (e->flags.i & ~0x3FF) | ((e->flags.b.count + 1) & 0x3FF);
    e->flags.i = w;
    if (((w << 22) >> 22) >= 64) {
        debug_Assert("Too much Stage Animation Objects.\n");
#ifdef VERSION_NTSC
        debug_assert(__FILE__, LN(522, 522, 522, 522, 522, 522));
        __assert(__FILE__, LN(522, 522, 522, 522, 522, 522), "0");
#else
#ifdef VERSION_AUG6
        debug_assert(__FILE__, LN(541, 525, 525, 501, 496, 541));
        __assert(__FILE__, LN(541, 525, 525, 501, 496, 541), "0");
#else
        debug_assert(__FILE__, LN(562, 546, 546, 562, 562, 562));
        __assert(__FILE__, LN(562, 546, 546, 562, 562, 562), "0");
#endif
#endif
#endif
    }
}

#ifdef VERSION_NTSC
void stage_ApplyData(char *name, char *data)
{
    const int *tbl[2] = {&stageData[stage_no].animLayoutFirst, &stageData[stage_no].labelTop};
    char buf[1024];
    int m;
    int i;
    int j;
    int n;
    int id;
    GenGeo *rec;
    StgBgaSet *ent;
    StageAnimDef *obj;

    for (m = 0; m < 2; m++) {
        for (i = tbl[m][0]; i < tbl[m][1]; i++) {
            rec = &objLayout[i];
            n = rec->action;
            if (n != 0) {
                ent = &objAction[n];
                for (j = 0; j < 2; j++) {
                    id = ent->anim[j];
                    obj = &stageTable[id];
                    if (id != 815) {
                        if (strcmp(name, obj->path) == 0) {
                            if (strncmp(data, "BGA", 3) == 0) {
                                obj->data = bga_InitData(data);
                            } else {
                                obj->data = data;
                            }
                            return;
                        }
                    }
                }
            }
        }
    }
    sprintf(buf, "stage_ApplyData:Data is not registered. \n\n%s\n", name);
    debug_assertMessage(__FILE__, LN(577, 577, 577, 577, 577, 577), buf);
    __assert(__FILE__, LN(577, 577, 577, 577, 577, 577), "e");
}
#else
void stage_ApplyData(char *name, char *data)
{
    const int *tbl[2] = {&stageData[stage_no].animLayoutFirst, &stageData[stage_no].labelTop};
#ifndef VERSION_JUN26
    char buf[1024];
#endif
    int m;
    int i;
    int j;
    int n;
    int id;
    GenGeo *rec;
    StgBgaSet *ent;
    StageAnimDef *obj;

    for (m = 0; m < 2; m++) {
        for (i = tbl[m][0]; i < tbl[m][1]; i++) {
            rec = &objLayout[i];
            n = rec->action;
            if (n != 0) {
                ent = &objAction[n];
                for (j = 0; j < 2; j++) {
                    id = ent->anim[j];
                    obj = &stageTable[id];
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                    if (id != 949) {
#else
#ifdef VERSION_AUG6
                    if (id != 814) {
#else
#ifdef VERSION_JUN26
                    if (id != 763) {
#else
                    if (id != 972) {
#endif
#endif
#endif
                        if (strcmp(name, obj->path) == 0) {
                            if (strncmp(data, "BGA", 3) == 0) {
                                obj->data = bga_InitData(data);
                            } else {
                                obj->data = data;
                            }
                            return;
                        }
                    }
                }
            }
        }
    }
#ifdef VERSION_JUN26
    debug_StdPrintfDummy("stage_ApplyData:Data is not registered. %s\n", name);
    debug_assert(__FILE__, LN(541, 525, 525, 501, 475, 474));
    __assert(__FILE__, LN(541, 525, 525, 501, 475, 474), "0");
#else
    sprintf(buf, "stage_ApplyData:Data is not registered. \n\n%s\n", name);
    debug_assertMessage(__FILE__, LN(617, 601, 601, 617, 551, 617), buf);
    __assert(__FILE__, LN(617, 601, 601, 617, 551, 617), "e");
#endif
}
#endif

/* stage_Init reaches the table's records through a pointer */
#define STG ((StageAnim *)stageAnimTable) /* derived name */
/* an animated object's DObj, its 0x15C word read through AnimWord */
#define STG_SUB(o) ((Sub15C *)((AnimWord *)((char *)(o) + 0x15C))->i) /* derived name */

#ifndef VERSION_JUN26
/* The stage animation TTY trace, built only when DEBUG is defined; the
   retail build leaves the helper without a body. */
static __inline__ void stageAnimDebugHook(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("stage anim %d\n", stageAnimCount);
#endif
}
#endif

#ifdef VERSION_NTSC
int stage_Init(void)
{
    const StgObjDat *p = 0;
    const int *tbl[2] = {&stageData[stage_no].animLayoutFirst, &stageData[stage_no].labelTop};
    SObjSimpleSetting arg;
    int max = 0;
    int m;
    int i;
    int k;
    int t;
    int u;
    int n;
    int id;
    const StgObjDat *q;
    GenGeo *rec;
    ObjKindEnt *kind;
    StageAnimDef *obj;
    GObj *g;
    struct BgaDObjEnt *a;
    void *(*fn)(GObj *, void *);
    StageAnim *e;

    bga_InitBGA();
    for (i = 0; i < 82; i++) {
        for (k = 0; k < 64; k++) {
            STG[i].kind[k] = -1;
        }
    }
    stageAnimCount = 0;
    for (i = 0; i < 82; i++) {
        STG[i].flags.b.count = 0;
    }
    /* the DEBUG-build trace (see stageAnimDebugHook) */
    stageAnimDebugHook();
    bgaPlayList = 0;
    bga_ResetCamera();
    stageAnimDebugHook();
    for (m = 0; m < 2; m++) {
        stageAnimDebugHook();
        for (i = tbl[m][0]; i < tbl[m][1]; i++) {
            rec = &objLayout[i];
            n = rec->action;
            if (n != 0) {
                StgBgaSet *ent = &objAction[n];

                for (k = 0; k < 2; k++) {
                    id = ent->anim[k];
                    obj = &stageTable[id];
                    if (id != 815) {
                        if (strncmp(obj->data, "BGA", 3) == 0) {
                            /* the DEBUG-build trace */
                            stageAnimDebugHook();
                            STG[stageAnimCount].flags.i &= 0x3FFFFFFF;
                            stageAnimTable[stageAnimCount].entry2 = obj->data;
                            ((BgaHeader *)obj->data)->group = obj->group;
                            ((BgaHeader *)obj->data)->cut = obj->cut;
                            stageAnimTable[stageAnimCount].entry2->mode = -1;
                            stageAnimTable[stageAnimCount].entry1 = obj;
                            STG[stageAnimCount].flags.b.play = 0;
                            p = &objTableScene[obj->objFirst];
                            q = &objTableScene[obj->objLast];
                            for (; p != q; p++) {
                                stage_MakeGObj((int *)p, stageAnimCount);
                            }
                        } else {
                            /* the DEBUG-build trace */
                            stageAnimDebugHook();
                            STG[stageAnimCount].flags.i =
                                (STG[stageAnimCount].flags.i & 0x3FFFFFFF) | 0x40000000;
                            stageAnimTable[stageAnimCount].entry3 = obj->data;
                            stageAnimTable[stageAnimCount].entry1 = obj;
                        }
                        /* the DEBUG-build trace */
                        stageAnimDebugHook();
                        stageAnimCount++;
                        if (stageAnimCount >= 83) {
                            /* "stgBgas has %d, over MAX_ANIM_KIND %d" */
                            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n",
                                                 stageAnimCount, 82);
                            /* "too many BgAnimation kinds in one stage" */
                            debug_StdPrintfDummy("1ステージ中の BgAnimation の種類が多すぎます\n");
                            debug_assert(__FILE__, LN(662, 662, 662, 662, 662, 662));
                            __assert(__FILE__, LN(662, 662, 662, 662, 662, 662), "0");
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < stageAnimCount; i++) {
        if (STG[i].flags.b.count >= 64) {
            /* "stgBgas has %d, over MAX_ANIM_GOBJ %d" */
            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました\n",
                                 STG[i].flags.b.count, 64);
            debug_assert(__FILE__, LN(672, 672, 672, 672, 672, 672));
            __assert(__FILE__, LN(672, 672, 672, 672, 672, 672), "0");
        }
        max = max < STG[i].flags.b.count ? STG[i].flags.b.count : max;
    }
    debug_StdPrintfDummy("Max Bga = %d // Max DObj %d\n", stageAnimCount, max);
    if (p != 0) {
        e = stageAnimTable;
        for (i = 0; i < stageAnimCount; i++, e++) {
            if ((e->flags.i >> 30) == 1) {
                continue;
            }
            for (k = 0; k < e->flags.b.count; k++) {
                if (STG_SUB(e->obj[k]) != 0) {
                    STG_SUB(e->obj[k])->nodeNum = 0;
                }
            }
            k = 0;
            for (;;) {
                a = e->entry2->roots[k++];
                if (a == 0) {
                    break;
                }
                bga_ApplyDObject(a, e->obj, e->flags.b.count);
            }
            e->flags.b.nodes = 0;
            for (k = 0; k < e->flags.b.count; k++) {
                if (STG_SUB(e->obj[k])->nodeMtx != 0) {
                    iosFree((void *)(STG_SUB(e->obj[k])->nodeMtx & 0x0FFFFFFF));
                }
                if (STG_SUB(e->obj[k])->nodeQuat != 0) {
                    iosFree((void *)(STG_SUB(e->obj[k])->nodeQuat & 0x0FFFFFFF));
                }
                STG_SUB(e->obj[k])->nodeMtx = 0;
                STG_SUB(e->obj[k])->nodeQuat = 0;
                STG_SUB(e->obj[k])->nodeMtx =
                    (int)iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 6,
                                        __FILE__, LN(716, 716, 716, 716, 716, 716));
                STG_SUB(e->obj[k])->nodeQuat =
                    (int)iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 4,
                                        __FILE__, LN(716, 716, 716, 716, 716, 716));
                /* the reallocation block's count line, as chain.c, boy.c and
                   box.c spell the same block, here passed the count field
                   itself: a store of the field to itself */
                STG_SUB(e->obj[k])->nodeNum = STG_SUB(e->obj[k])->nodeNum;
                if ((int)STG_SUB(e->obj[k])->nodes != 0) {
                    iosFree((void *)((int)STG_SUB(e->obj[k])->nodes & 0x0FFFFFFF));
                }
                STG_SUB(e->obj[k])->nodes =
                    iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum * 80, __FILE__,
                                   LN(716, 716, 716, 716, 716, 716));
                for (t = 0; t < STG_SUB(e->obj[k])->nodeNum; t++) {
                    STG_SUB(e->obj[k])->nodes[t].flags.ll &= ~1;
                    STG_SUB(e->obj[k])->nodes[t].flags.ll &= ~2;
                    STG_SUB(e->obj[k])->nodes[t].pos[0] = 0;
                    STG_SUB(e->obj[k])->nodes[t].pos[1] = 0;
                    STG_SUB(e->obj[k])->nodes[t].pos[2] = 0;
                    STG_SUB(e->obj[k])->nodes[t].pos[3] = 1.0f;
                    STG_SUB(e->obj[k])->nodes[t].flags.ll &= ~4;
                    STG_SUB(e->obj[k])->nodes[t].fade = 0;
                    STG_SUB(e->obj[k])->nodes[t].alpha = 1.0f;
                    *(short *)((char *)&STG_SUB(e->obj[k])->nodes[t] + 0x3A) = 0;
                    STG_SUB(e->obj[k])->nodes[t].scale[0] = 1.0f;
                    STG_SUB(e->obj[k])->nodes[t].scale[1] = 1.0f;
                    STG_SUB(e->obj[k])->nodes[t].scale[2] = 1.0f;
                }
                STG_SUB(e->obj[k])->dispType = 2;
                e->flags.i = (e->flags.i & 0xFFF003FF) |
                             ((e->flags.b.nodes + STG_SUB(e->obj[k])->nodeNum) & 0x3FF) << 10;
                for (u = 0; u < STG_SUB(e->obj[k])->nodeNum; u++) {
                    _UnitMatrix((void *)(STG_SUB(e->obj[k])->nodeMtx + u * 64));
                    SetIdentityQuaternion((void *)(STG_SUB(e->obj[k])->nodeQuat + u * 16));
                }
            }
        }
        e = stageAnimTable;
        for (i = 0; i < stageAnimCount; i++, e++) {
            if ((e->flags.i >> 30) == 1) {
                continue;
            }
            for (k = 0; k < e->flags.b.count; k++) {
                static const SObjSimpleSetting stageGObjArg = /* derived name */
                    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 1};

                g = e->obj[k];
                arg = stageGObjArg;
                kind = &objKindData[e->data[k][1]];
                fn = kind->create;
                if (fn != 0) {
                    STG_SUB(e->obj[k])->work = fn(g, &arg);
                }
                isysGObjProcAdd(g, kind->ai, 1, 0x16);
                isysGObjProcAdd(g, kind->geo, 1, 0x17);
                isysGObjProcAdd(g, kind->afterGeo, 1, 0x18);
                isysGObjLinkObjDL(g, 0, 0, 7, 0xFFFFFFFF);
                g->active = 1;
                STG_SUB(e->obj[k])->disp = 0;
            }
        }
    }
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (e->entry1->loop != 0) {
            stage_SetAnimation(e->entry1->no, 1, 0);
        }
    }
    return stageAnimCount;
}
#else
int stage_Init(void)
{
    const StgObjDat *p = 0;
    const int *tbl[2] = {&stageData[stage_no].animLayoutFirst, &stageData[stage_no].labelTop};
    SObjSimpleSetting arg;
    int max = 0;
    int m;
    int i;
    int k;
    int t;
    int u;
    int n;
    int id;
#ifdef VERSION_JUN26
    const StgObjDat *q = 0;
    GenGeo *rec = 0;
    ObjKindEnt *kind = 0;
    StageAnimDef *obj = 0;
    GObj *g = 0;
    struct BgaDObjEnt *a = 0;
    void *(*fn)(GObj *, void *) = 0;
    StageAnim *e = 0;

    bga_InitBGA();
    for (i = 0; i < 80; i++) {
#else
#ifndef VERSION_AUG6
    int no;
#endif
    const StgObjDat *q;
    GenGeo *rec;
    ObjKindEnt *kind;
    StageAnimDef *obj;
    GObj *g;
    struct BgaDObjEnt *a;
#ifndef VERSION_AUG6
    char *r;
#endif
    void *(*fn)(GObj *, void *);
    StageAnim *e;

    bga_InitBGA();
#ifdef VERSION_AUG6
    for (i = 0; i < 82; i++) {
#else
    for (i = 0; i < 87; i++) {
#endif
#endif
        for (k = 0; k < 64; k++) {
            STG[i].kind[k] = -1;
        }
    }
    stageAnimCount = 0;
#ifdef VERSION_JUN26
    for (i = 0; i < 80; i++) {
        STG[i].count = 0;
    }
    bgaPlayList = 0;
    bgaPlayCount = 0;
    bga_ResetCamera();
    for (m = 0; m < 2; m++) {
#else
#ifdef VERSION_AUG6
    for (i = 0; i < 82; i++) {
#else
    for (i = 0; i < 87; i++) {
#endif
        STG[i].flags.b.count = 0;
    }
    /* the DEBUG-build trace (see stageAnimDebugHook) */
    stageAnimDebugHook();
    bgaPlayList = 0;
#ifdef VERSION_AUG6
    bgaPlayCount = 0;
#endif
    bga_ResetCamera();
    stageAnimDebugHook();
    for (m = 0; m < 2; m++) {
        stageAnimDebugHook();
#endif
        for (i = tbl[m][0]; i < tbl[m][1]; i++) {
            rec = &objLayout[i];
            n = rec->action;
            if (n != 0) {
                StgBgaSet *ent = &objAction[n];

                for (k = 0; k < 2; k++) {
                    id = ent->anim[k];
                    obj = &stageTable[id];
#ifdef VERSION_JUN26
                    if (id != 763) {
                        if (strncmp(obj->data, "BGA", 3) == 0) {
                            STG[stageAnimCount].mode = 0;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                    if (id != 949) {
#else
#ifdef VERSION_AUG6
                    if (id != 814) {
#else
                    if (id != 972) {
#endif
#endif
                        if (strncmp(obj->data, "BGA", 3) == 0) {
                            /* the DEBUG-build trace */
                            stageAnimDebugHook();
                            STG[stageAnimCount].flags.i &= 0x3FFFFFFF;
#endif
                            stageAnimTable[stageAnimCount].entry2 = obj->data;
                            ((BgaHeader *)obj->data)->group = obj->group;
                            ((BgaHeader *)obj->data)->cut = obj->cut;
#ifdef VERSION_JUN26
                            stageAnimTable[stageAnimCount].entry1 = obj;
                            STG[stageAnimCount].play = 0;
#else
                            stageAnimTable[stageAnimCount].entry2->mode = -1;
                            stageAnimTable[stageAnimCount].entry1 = obj;
                            STG[stageAnimCount].flags.b.play = 0;
#endif
                            p = &objTableScene[obj->objFirst];
                            q = &objTableScene[obj->objLast];
                            for (; p != q; p++) {
                                stage_MakeGObj((int *)p, stageAnimCount);
                            }
                        } else {
#ifdef VERSION_JUN26
                            STG[stageAnimCount].mode = 1;
#else
                            /* the DEBUG-build trace */
                            stageAnimDebugHook();
                            STG[stageAnimCount].flags.i =
                                (STG[stageAnimCount].flags.i & 0x3FFFFFFF) | 0x40000000;
#endif
                            stageAnimTable[stageAnimCount].entry3 = obj->data;
                            stageAnimTable[stageAnimCount].entry1 = obj;
                        }
#ifdef VERSION_JUN26
                        stageAnimCount++;
                        if (stageAnimCount >= 81) {
                            /* "stgBgas has %d, over MAX_ANIM_KIND %d" */
                            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n",
                                                 stageAnimCount, 80);
                            /* "too many BgAnimation kinds in one stage" */
                            debug_StdPrintfDummy("1ステージ中の BgAnimation の種類が多すぎます\n");
                            debug_assert(__FILE__, LN(541, 525, 525, 501, 475, 556));
                            __assert(__FILE__, LN(541, 525, 525, 501, 475, 556), "0");
#else
                        /* the DEBUG-build trace */
                        stageAnimDebugHook();
                        stageAnimCount++;
#ifdef VERSION_AUG6
                        if (stageAnimCount >= 83) {
                            /* "stgBgas has %d, over MAX_ANIM_KIND %d" */
                            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n",
                                                 stageAnimCount, 82);
                            /* "too many BgAnimation kinds in one stage" */
                            debug_StdPrintfDummy("1ステージ中の BgAnimation の種類が多すぎます\n");
                            debug_assert(__FILE__, LN(541, 525, 525, 501, 634, 541));
                            __assert(__FILE__, LN(541, 525, 525, 501, 634, 541), "0");
#else
                        if (stageAnimCount >= 88) {
                            /* "stgBgas has %d, over MAX_ANIM_KIND %d" */
                            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n",
                                                 stageAnimCount, 87);
                            /* "too many BgAnimation kinds in one stage" */
                            debug_StdPrintfDummy("1ステージ中の BgAnimation の種類が多すぎます\n");
                            debug_assert(__FILE__, LN(702, 686, 686, 702, 702, 702));
                            __assert(__FILE__, LN(702, 686, 686, 702, 702, 702), "0");
#endif
#endif
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < stageAnimCount; i++) {
#ifdef VERSION_JUN26
        if (STG[i].count >= 64) {
            /* "stgBgas has %d, over MAX_ANIM_GOBJ %d" */
            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました\n", STG[i].count,
                                 64);
            debug_assert(__FILE__, LN(541, 525, 525, 501, 475, 566));
            __assert(__FILE__, LN(541, 525, 525, 501, 475, 566), "0");
        }
        max = max < STG[i].count ? STG[i].count : max;
#else
        if (STG[i].flags.b.count >= 64) {
            /* "stgBgas has %d, over MAX_ANIM_GOBJ %d" */
            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました\n",
                                 STG[i].flags.b.count, 64);
#ifdef VERSION_AUG6
            debug_assert(__FILE__, LN(541, 525, 525, 501, 644, 541));
            __assert(__FILE__, LN(541, 525, 525, 501, 644, 541), "0");
#else
            debug_assert(__FILE__, LN(712, 696, 696, 712, 712, 712));
            __assert(__FILE__, LN(712, 696, 696, 712, 712, 712), "0");
#endif
        }
        max = max < STG[i].flags.b.count ? STG[i].flags.b.count : max;
#endif
    }
    debug_StdPrintfDummy("Max Bga = %d // Max DObj %d\n", stageAnimCount, max);
    if (p != 0) {
        e = stageAnimTable;
        for (i = 0; i < stageAnimCount; i++, e++) {
#ifdef VERSION_JUN26
            if (e->mode == 1) {
                continue;
            }
            for (k = 0; k < e->count; k++) {
#else
            if ((e->flags.i >> 30) == 1) {
                continue;
            }
            for (k = 0; k < e->flags.b.count; k++) {
#endif
                if (STG_SUB(e->obj[k]) != 0) {
                    STG_SUB(e->obj[k])->nodeNum = 0;
                }
            }
            k = 0;
            for (;;) {
                a = e->entry2->roots[k++];
                if (a == 0) {
                    break;
                }
#ifdef VERSION_JUN26
                bga_ApplyDObject(a, e->obj, e->count);
            }
            e->nodes = 0;
            for (k = 0; k < e->count; k++) {
                if (STG_SUB(e->obj[k])->nodeMtx != 0) {
                    iosFree((void *)STG_SUB(e->obj[k])->nodeMtx);
                }
                if (STG_SUB(e->obj[k])->nodeQuat != 0) {
                    iosFree((void *)STG_SUB(e->obj[k])->nodeQuat);
#else
#ifdef VERSION_AUG6
                bga_ApplyDObject(a, e->obj, e->flags.b.count);
#else
                r = (char *)e->entry1;
                no = -1;
                if (r != 0) {
                    no = (r - (char *)stageTable) / 0x5CU;
                }
                bga_ApplyDObject(a, e->obj, e->flags.b.count, no);
#endif
            }
            e->flags.b.nodes = 0;
            for (k = 0; k < e->flags.b.count; k++) {
                if (STG_SUB(e->obj[k])->nodeMtx != 0) {
                    iosFree((void *)(STG_SUB(e->obj[k])->nodeMtx & 0x0FFFFFFF));
                }
                if (STG_SUB(e->obj[k])->nodeQuat != 0) {
                    iosFree((void *)(STG_SUB(e->obj[k])->nodeQuat & 0x0FFFFFFF));
#endif
                }
                STG_SUB(e->obj[k])->nodeMtx = 0;
                STG_SUB(e->obj[k])->nodeQuat = 0;
#ifdef VERSION_AUG6
                STG_SUB(e->obj[k])->nodeMtx =
                    (int)iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 6,
                                        __FILE__, LN(688, 688, 688, 688, 688, 688));
                STG_SUB(e->obj[k])->nodeQuat =
                    (int)iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 4,
                                        __FILE__, LN(688, 688, 688, 688, 688, 688));
#else
#ifdef VERSION_JUN26
                STG_SUB(e->obj[k])->nodeMtx = (int)iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 6, __FILE__, 610);
                STG_SUB(e->obj[k])->nodeQuat = (int)iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 4, __FILE__, 610);
#else
                STG_SUB(e->obj[k])->nodeMtx =
                    (int)iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 6,
                                        __FILE__, LN(761, 745, 745, 761, 761, 761));
                STG_SUB(e->obj[k])->nodeQuat =
                    (int)iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 4,
                                        __FILE__, LN(761, 745, 745, 761, 761, 761));
#endif
#endif
                /* the reallocation block's count line, as chain.c, boy.c and
                   box.c spell the same block, here passed the count field
                   itself: a store of the field to itself */
                STG_SUB(e->obj[k])->nodeNum = STG_SUB(e->obj[k])->nodeNum;
#ifdef VERSION_JUN26
                if (STG_SUB(e->obj[k])->nodes != 0) {
                    iosFree(STG_SUB(e->obj[k])->nodes);
                }
                STG_SUB(e->obj[k])->nodes = iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum * 80, __FILE__, 610);
#else
                if ((int)STG_SUB(e->obj[k])->nodes != 0) {
                    iosFree((void *)((int)STG_SUB(e->obj[k])->nodes & 0x0FFFFFFF));
                }
#ifdef VERSION_AUG6
                STG_SUB(e->obj[k])->nodes =
                    iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum * 80, __FILE__,
                                   LN(688, 688, 688, 688, 688, 688));
#else
                STG_SUB(e->obj[k])->nodes =
                    iosMallocDebug(ios_partition_seki, STG_SUB(e->obj[k])->nodeNum * 80, __FILE__,
                                   LN(761, 745, 745, 761, 761, 761));
#endif
#endif
                for (t = 0; t < STG_SUB(e->obj[k])->nodeNum; t++) {
                    STG_SUB(e->obj[k])->nodes[t].flags.ll &= ~1;
                    STG_SUB(e->obj[k])->nodes[t].flags.ll &= ~2;
                    STG_SUB(e->obj[k])->nodes[t].pos[0] = 0;
                    STG_SUB(e->obj[k])->nodes[t].pos[1] = 0;
                    STG_SUB(e->obj[k])->nodes[t].pos[2] = 0;
                    STG_SUB(e->obj[k])->nodes[t].pos[3] = 1.0f;
                    STG_SUB(e->obj[k])->nodes[t].flags.ll &= ~4;
                    STG_SUB(e->obj[k])->nodes[t].fade = 0;
                    STG_SUB(e->obj[k])->nodes[t].alpha = 1.0f;
                    *(short *)((char *)&STG_SUB(e->obj[k])->nodes[t] + 0x3A) = 0;
                    STG_SUB(e->obj[k])->nodes[t].scale[0] = 1.0f;
                    STG_SUB(e->obj[k])->nodes[t].scale[1] = 1.0f;
                    STG_SUB(e->obj[k])->nodes[t].scale[2] = 1.0f;
                }
                STG_SUB(e->obj[k])->dispType = 2;
#ifdef VERSION_JUN26
                e->nodes += STG_SUB(e->obj[k])->nodeNum;
#else
                e->flags.i = (e->flags.i & 0xFFF003FF) |
                             ((e->flags.b.nodes + STG_SUB(e->obj[k])->nodeNum) & 0x3FF) << 10;
#endif
                for (u = 0; u < STG_SUB(e->obj[k])->nodeNum; u++) {
                    _UnitMatrix((void *)(STG_SUB(e->obj[k])->nodeMtx + u * 64));
                    SetIdentityQuaternion((void *)(STG_SUB(e->obj[k])->nodeQuat + u * 16));
                }
            }
        }
        e = stageAnimTable;
        for (i = 0; i < stageAnimCount; i++, e++) {
#ifdef VERSION_JUN26
            if (e->mode == 1) {
                continue;
            }
            for (k = 0; k < e->count; k++) {
#else
            if ((e->flags.i >> 30) == 1) {
                continue;
            }
            for (k = 0; k < e->flags.b.count; k++) {
#endif
                static const SObjSimpleSetting stageGObjArg = /* derived name */
                    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 1};

                g = e->obj[k];
                arg = stageGObjArg;
                kind = &objKindData[e->data[k][1]];
                fn = kind->create;
                if (fn != 0) {
                    STG_SUB(e->obj[k])->work = fn(g, &arg);
                }
                isysGObjProcAdd(g, kind->ai, 1, 0x16);
                isysGObjProcAdd(g, kind->geo, 1, 0x17);
                isysGObjProcAdd(g, kind->afterGeo, 1, 0x18);
                isysGObjLinkObjDL(g, 0, 0, 7, 0xFFFFFFFF);
                g->active = 1;
                STG_SUB(e->obj[k])->disp = 0;
            }
        }
    }
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (e->entry1->loop != 0) {
            stage_SetAnimation(e->entry1->no, 1, 0);
        }
    }
    return stageAnimCount;
}
#endif

void stage_SetAnimation(int key, int mode, int frame)
{
    int uid = -1;
    int i;
    int k;
    int dbg = 0; /* local debug switch, see the test in case 0 below */
    StageAnim *e;

#ifdef VERSION_JUN26
    debug_StdPrintfDummy("stage_SetAnimation:%d %d\n", key, mode);
#endif
    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key != e->entry1->no) {
            continue;
        }
#ifdef VERSION_JUN26
        switch (e->mode) {
#else
        switch (e->flags.i >> 30) {
#endif
        case 0:
            uid = e->entry2->group;
            /* a local debug switch, off: report a bad group number */
            if (dbg) {
                debug_StdPrintfDummy("Illegal Group No. %d\n", uid);
            }
            bga_SetFrame(e->entry2, frame, mode, e->entry1->loop);
#ifdef VERSION_JUN26
            for (k = 0; k < e->count; k++) {
#else
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
#endif
                e->obj[k]->dobj->disp = 1;
            }
            break;
        case 1:
            bga_SetCamFrame(e->entry3, frame, mode, e->entry1->loop);
            break;
        }
        break;
    }

    if (uid != -1) {
        for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
#ifdef VERSION_JUN26
            if (e->mode != 0) {
#else
            if ((e->flags.i >> 30) != 0) {
#endif
                continue;
            }
            if (uid != e->entry2->group || key == e->entry1->no) {
                continue;
            }
#ifdef VERSION_JUN26
            for (k = 0; k < e->count; k++) {
#else
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
#endif
                if (*(char **)&e->obj[k]->dobj != 0) {
                    e->obj[k]->dobj->disp = 0;
                }
            }
        }
    }
}

inline int stage_CheckAnimationFinish(int key)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        StageAnimDef *entry1 = e->entry1;
        if (key == entry1->no) {
#ifdef VERSION_JUN26
            switch (e->mode) {
#else
            int mode = e->flags.i >> 30;
            switch (mode) {
#endif
            case 0:
                return bga_CheckAnimationFinish(e->entry2);
            case 1:
                return bga_CheckSdfCameraFinish(e->entry3);
            }
        }
    }
    debug_StdPrintfDummy("stage_CheckAnimationFinish:illegal Animation No.\n");
#ifdef VERSION_AUG6
    debug_assert(__FILE__, LN(541, 525, 525, 501, 837, 541));
    __assert(__FILE__, LN(541, 525, 525, 501, 837, 541), "0");
#else
#ifdef VERSION_JUN26
    debug_assert(__FILE__, LN(541, 525, 525, 501, 475, 768));
    __assert(__FILE__, LN(541, 525, 525, 501, 475, 768), "0");
#else
    debug_assert(__FILE__, LN(909, 893, 893, 864, 909, 909));
    __assert(__FILE__, LN(909, 893, 893, 864, 909, 909), "0");
#endif
#endif
    return 0;
}

int stage_ContinueAnimation(int key, int next)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        StageAnimDef *entry1 = e->entry1;
        if (key == entry1->no) {
#ifdef VERSION_JUN26
            switch (e->mode) {
            case 0:
                if (bga_CheckAnimationFinish(e->entry2) != 0) {
                    stage_SetAnimation(key, 0, 0);
#else
            int mode = e->flags.i >> 30;
            switch (mode) {
            case 0:
                if (bga_CheckAnimationFinish(e->entry2) != 0) {
                    stage_SetAnimation(key, 0, -1);
#endif
                    stage_SetAnimation(next, 1, 0);
                    return 1;
                }
                return 0;
            case 1:
                if (bga_CheckSdfCameraFinish(e->entry3) == 0) {
                    return 0;
                }
#ifdef VERSION_JUN26
                stage_SetAnimation(key, 0, 0);
#else
                stage_SetAnimation(key, 0, -1);
#endif
                stage_SetAnimation(next, 1, 0);
                return 1;
            }
        }
    }
    debug_StdPrintfDummy("stage_ContinueAnimation:illegal Animation No.\n");
#ifdef VERSION_NTSC
    debug_assert(__FILE__, LN(909, 909, 909, 909, 909, 909));
    __assert(__FILE__, LN(909, 909, 909, 909, 909, 909), "0");
#else
#ifdef VERSION_AUG6
    debug_assert(__FILE__, LN(541, 525, 525, 501, 882, 541));
    __assert(__FILE__, LN(541, 525, 525, 501, 882, 541), "0");
#else
#ifdef VERSION_JUN26
    debug_assert(__FILE__, LN(541, 525, 525, 501, 475, 808));
    __assert(__FILE__, LN(541, 525, 525, 501, 475, 808), "0");
#else
    debug_assert(__FILE__, LN(954, 938, 938, 954, 954, 954));
    __assert(__FILE__, LN(954, 938, 938, 954, 954, 954), "0");
#endif
#endif
#endif
    return 0;
}

inline int stage_CheckAnimationFrame(int key, int frame, int reset)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        StageAnimDef *entry1 = e->entry1;
        if (key == entry1->no) {
#ifdef VERSION_JUN26
            switch (e->mode) {
#else
            int mode = e->flags.i >> 30;
            switch (mode) {
#endif
            case 0:
                return bga_CheckAnimationFrame(e->entry2, frame, reset);
            case 1:
                return bga_CheckSdfCameraFrame(e->entry3, frame, reset);
            }
        }
    }
    return -1;
}

inline int stage_CheckAnimationFrameIn(int key, int in, int out)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        StageAnimDef *entry1 = e->entry1;
        if (key == entry1->no) {
#ifdef VERSION_JUN26
            switch (e->mode) {
#else
            int mode = e->flags.i >> 30;
            switch (mode) {
#endif
            case 0:
                return bga_CheckAnimationFrameIn(e->entry2, in, out);
            case 1:
                return bga_CheckSdfCameraFrameIn(e->entry3, in, out);
            }
        }
    }
    return -1;
}

#ifndef VERSION_JUN26
void stage_ResetAnimation(void)
{
    bga_ResetAnimation();
#ifndef VERSION_AUG6
    if (systemStatus[5] != 0)
        return;
    light_KillAllFixLight();
#endif
}
#endif

void stage_CalcAnimationNoParent(void)
{
    int i;
    StageAnim *e;

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (lock_execIcoMisc != 0) {
#else
    if (graphics_ready != 0) {
#endif
        return;
    }
    if (stageAnimCount == 0) {
        return;
#ifdef VERSION_AUG6
    }
    if (systemStatus[0x14 / 4] == 0) {
        light_KillAllFixLight();
#endif
    }
#ifdef VERSION_JUN26
    if (systemStatus[0x14 / 4] == 0) {
        light_KillAllFixLight();
    }
#endif
    bga_SetUniqAnimationFlag(1);
    _InitCurrentMatrix();
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
#ifdef VERSION_JUN26
        switch (e->mode) {
        case 0: {
            BgaHeader *entry2 = e->entry2;

            if (entry2->anim->obj != 0) {
                continue;
#else
        switch (e->flags.i >> 30) {
        case 0: {
            BgaHeader *entry2 = e->entry2;
            signed char lock = entry2->cut;

            if (lock == 0) {
                if (entry2->anim->obj != 0) {
                    continue;
                }
#endif
            }
            if (systemStatus[0x14 / 4] != 0) {
                continue;
            }
            switch (entry2->mode) {
            case -1: {
                int k;

#ifdef VERSION_JUN26
                for (k = 0; k < e->count; k++) {
                    e->obj[k]->dobj->disp = 0;
#else
                for (k = 0; k < e->flags.b.count; k++) {
                    char *objs = (char *)e->obj;
                    char *o = *(char **)(objs + (k << 2));

                    GOBJ_SUB(o)->disp = 0;
#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)
#ifndef VERSION_AUG6
                    if (GOBJ_SUB(o)->nodeNum != 0) {
                        *(int *)((int *)*(int *)(o + 0x15C))[0xC / 4] = 0;
                    }
#endif
#endif
#endif
                }
                break;
            }
#ifdef VERSION_JUN26
            case 1:
                _InitCurrentMatrix();
                bga_CalcAnimation(e->entry2, e->entry1->loop, 0);
                break;
            case 0:
                _InitCurrentMatrix();
                bga_CalcAnimation(e->entry2, e->entry1->loop, 1);
#else
            case 0:
                break;
            case 1:
#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)
#ifndef VERSION_AUG6
                if (lock != 0) {
                    if (debug_font_flag & 1) {
                        debug_Printf(0, ScreenHeight / 2 - 28, 0xCCCCCC00,
                                     "\033[32mCamera LWS : %s\033[0m\n", e->entry1->path);
                    }
                }
#endif
#endif
                _InitCurrentMatrix();
                bga_CalcAnimation(e->entry2, e->entry1->loop, 0);
#endif
                break;
            }
            break;
        }
        case 1:
            if (systemStatus[0x14 / 4] != 0) {
                continue;
            }
            if (*(int *)(e->entry3 + 0xC) != 1) {
                continue;
            }
            _InitCurrentMatrix();
            bga_CalcSdfCamera(e->entry3, e->entry1->loop);
            break;
        }
    }
    bga_SetUniqAnimationFlag(0);
}

void stage_CalcAnimationParent(void)
{
    int i;
    StageAnim *e;
    BgaHeader *entry2;

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (lock_execIcoMisc != 0) {
#else
    if (graphics_ready != 0) {
#endif
        return;
    }
    if (stageAnimCount == 0) {
        return;
    }
    bga_SetUniqAnimationFlag(1);
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
#ifdef VERSION_JUN26
        if (e->mode != 0) {
#else
        if ((e->flags.i >> 30) != 0) {
#endif
            continue;
        }
        entry2 = e->entry2;
#ifndef VERSION_JUN26
        if (entry2->cut != 0) {
            continue;
        }
#endif
        if (entry2->anim->obj == 0) {
            continue;
        }
        if (systemStatus[0x14 / 4] != 0) {
            continue;
        }
        switch (entry2->mode) {
        case -1: {
            int k;

#ifdef VERSION_JUN26
            for (k = 0; k < e->count; k++) {
                e->obj[k]->dobj->disp = 0;
#else
            for (k = 0; k < e->flags.b.count; k++) {
                char *objs = (char *)e->obj;
                char *o = *(char **)(objs + (k << 2));
                GOBJ_SUB(o)->disp = 0;
#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)
#ifndef VERSION_AUG6
                if (GOBJ_SUB(o)->nodeNum != 0) {
                    *(int *)((int *)*(int *)(o + 0x15C))[0xC / 4] = 0;
                }
#endif
#endif
#endif
            }
            break;
        }
        case 1:
            _InitCurrentMatrix();
            bga_CalcAnimation(e->entry2, e->entry1->loop, 0);
            break;
        case 0:
            _InitCurrentMatrix();
            bga_CalcAnimation(e->entry2, e->entry1->loop, 1);
            break;
        }
    }
    bga_SetUniqAnimationFlag(0);
}

void stage_DispAnimation(void)
{
    int i;
    StageAnim *e;

    if (stageAnimCount == 0) {
        return;
    }

    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        StageAnimDef *entry1 = e->entry1;
#endif
        signed char lv;
        int k;

#ifdef VERSION_JUN26
        if (e->mode != 0) {
#else
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        if (entry1->no == 62) {
#else
        if (entry1->no == 0x42) {
#endif
            continue;
        }
#endif
        if ((e->flags.i >> 30) != 0) {
#endif
            continue;
        }
        lv = e->entry2->mode;
        if (lv == -1) {
            continue;
        }
        if (lv < -1) {
            continue;
        }
        if (lv >= 2) {
            continue;
        }
#ifdef VERSION_JUN26
        for (k = 0; k < e->count; k++) {
            if (e->obj[k]->dobj->disp != 0) {
                reg_DispObj(e->obj[k]->dobj);
                stageAnimObjCount += e->obj[k]->dobj->nodeNum;
#else
        for (k = 0; k < e->flags.b.count; k++) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            if (e->obj[k]->dobj->disp != 0) {
                reg_DispObj(e->obj[k]->dobj);
                stageAnimObjCount += e->obj[k]->dobj->nodeNum;
#else
            char *objs = (char *)e->obj;
            Sub15C *d = ((GObj *)*(char **)(objs + (k << 2)))->dobj;

            if (d->disp != 0) {
                reg_DispObj(d);
#endif
#endif
            }
        }
    }
    bga_DispLightning();
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (debug_font_flag2 != 0 || (debug_font_flag & 1) != 0) {
        debug_Printf(400, 20, 0xCCCCCC00u, "O:%d", stageAnimObjCount);
    }
    stageAnimObjCount = 0;
#endif
}

inline void stage_SetLoopFlag(int key, int loop)
{
#ifdef VERSION_JUN26
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            e->entry1->loop = loop;
#else
    int count = *(volatile int *)&stageAnimCount;
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < count; i++, e++) {
        /* one int pointer reads the record and then the count; with a record
           pointer and a direct count read the key test becomes a
           branch-likely (measured) */
        int *p = (int *)e->entry1;
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = loop;
            p = &stageAnimCount;
            count = *p;
#endif
        }
    }
}

inline void stage_SetFrameStep(int target, int val)
{
#ifdef VERSION_JUN26
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (target == e->entry1->no) {
            e->entry2->step = (float)val;
        }
    }
#else
    int n = stageAnimCount;
    StageAnim *p = stageAnimTable;
    int i;
    if (n <= 0)
        return;
    i = n;
    do {
        StageAnimDef *entry1 = p->entry1;
        if (target == entry1->no) {
            BgaHeader *entry2 = p->entry2;
            entry2->step = (float)val;
        }
        p++;
    } while (--i);
#endif
}

inline void stage_SetParentOfGObj(int key, void *parent)
{
    int i;
#ifdef VERSION_JUN26
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            *(Blob8 *)&e->entry2->anim->obj = *(Blob8 *)parent;
        }
#else
    int one = 1;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++) {
        if (key == e->entry1->no) {
            *(Blob8 *)&e->entry2->anim->obj = *(Blob8 *)parent;
            e->entry2->anim->root = one;
        }
        e++;
    }
}

inline void stage_SetParentOfGObjWithLocalRotationFlag(int key, void *parent, int localRotation)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++) {
        if (key == e->entry1->no) {
            *(Blob8 *)&e->entry2->anim->obj = *(Blob8 *)parent;
            e->entry2->anim->root = localRotation;
        }
        e++;
#endif
    }
}

#ifdef VERSION_JUN26
inline void stage_SetLocalizeGeometry(int key, float *pos, float *rot)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            _CopyVector(e->entry2->anim->pos, pos);
            CopyQuaternion(e->entry2->anim->quat, rot);
        }
    }
}

inline void stage_SetScale(int key, float scale)
{
    int i;
    int j;
    int k;
    StageAnim *e = stageAnimTable;

    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            if (e->mode == 0) {
                for (j = 0; j < e->count; j++) {
                    for (k = 0; k < STG_SUB(e->obj[j])->nodeNum; k++) {
                        STG_SUB(e->obj[j])->nodes[k].scale[0] =
                            STG_SUB(e->obj[j])->nodes[k].scale[1] =
                                STG_SUB(e->obj[j])->nodes[k].scale[2] = scale;
                    }
                }
            }
        }
    }
}
#else
inline void stage_SetLocalizeGeometry(int key, float *pos, float *rot)
{
    int count = *(volatile int *)&stageAnimCount;
    int i = 0;
    StageAnim *e = stageAnimTable;
    if (count <= 0)
        return;
    do {
        StageAnimDef *entry1 = e->entry1;
        if (key == entry1->no) {
            BgaHeader *entry2;
            BgaAnim *target;
            entry2 = e->entry2;
            target = entry2->anim;
            _CopyVector(target->pos, pos);
            entry2 = e->entry2;
            target = entry2->anim;
            CopyQuaternion(target->quat, rot);
            count = *(volatile int *)&stageAnimCount;
        }
        i++;
        e++;
    } while (i < count);
}

void stage_SetScale(int key, float scale)
{
    int i;
    int j;
    int k;
    StageAnim *e = stageAnimTable;

    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            if ((e->flags.i >> 30) == 0) {
                for (j = 0; j < e->flags.b.count; j++) {
                    for (k = 0; k < STG_SUB(e->obj[j])->nodeNum; k++) {
                        STG_SUB(e->obj[j])->nodes[k].scale[0] =
                            STG_SUB(e->obj[j])->nodes[k].scale[1] =
                                STG_SUB(e->obj[j])->nodes[k].scale[2] = scale;
                    }
                }
            }
        }
    }
}
#endif

float stage_PlayBgAnimation(int key, float t, void *v, void *q)
{
    int i;
    int k;
    int n = stageAnimCount;
    float r = t;
#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
    float f;
#endif
#endif
    StageAnim *e;

    if (n == 0) {
        return 0.0f;
    }
    e = stageAnimTable;
    for (i = 0; i < n; i++, e++) {
        if (key != e->entry1->no) {
            continue;
        }
#ifdef VERSION_JUN26
        if (e->mode != 0) {
#else
        if ((e->flags.i >> 30) != 0) {
#endif
            continue;
        }
        _CopyVector(e->entry2->anim->pos, v);
        CopyQuaternion(e->entry2->anim->quat, q);
        bga_SetFrame(e->entry2, (int)r, 1, e->entry1->loop);
#ifdef VERSION_JUN26
        for (k = 0; k < e->count; k++) {
            e->obj[k]->dobj->disp = 1;
        }
        e->entry2->mode = 1;
        _InitCurrentMatrix();
#else
        for (k = 0; k < e->flags.b.count; k++) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            e->obj[k]->dobj->disp = 1;
        }
        e->entry2->mode = 1;
        _InitCurrentMatrix();
#else
            char *objs = (char *)e->obj;

            *(int *)(*(int *)(*(char **)(objs + (k << 2)) + 0x15C) + 0x74) = 1;
        }
#endif
#endif
        if (systemStatus[0x14 / 4] != 0) {
            break;
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC)
        r = t + e->entry2->step * (30.0f / ((60 - systemStatus[0] * 10) / systemStatus[1]));
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        bga_CalcAnimation(e->entry2, e->entry1->loop, 0);
        r = t + e->entry2->step * (30.0f / ((60 - systemStatus[0] * 10) / systemStatus[1]));
#else
        f = e->entry2->step;
        if (systemStatus[0] != 0) {
            r = t + f * 1.2075409f;
        } else {
            r = t + f;
        }
#endif
#endif
        if (e->entry2->end <= r) {
            r = e->entry1->loop != 0 ? e->entry2->start : -1.0f;
        }
        break;
    }
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key != e->entry1->no) {
            continue;
        }
#ifdef VERSION_JUN26
        if (e->mode != 0) {
            continue;
        }
        for (k = 0; k < e->count; k++) {
            Sub15C *d = e->obj[k]->dobj;

            stageAnimObjCount += d->nodeNum;
#else
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        for (k = 0; k < e->flags.b.count; k++) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            Sub15C *d = e->obj[k]->dobj;

            stageAnimObjCount += d->nodeNum;
#else
            char *objs = (char *)e->obj;
            Sub15C *d = ((GObj *)*(char **)(objs + (k << 2)))->dobj;

#endif
#endif
            reg_DispObj(d);
            d->disp = 0;
        }
        e->entry2->mode = -1;
    }
    return r;
}

float stage_PlayBgAnimationDissolve(int key, void *v, void *q, float t, float dv)
{
    int i;
    int k;
    int m;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    int n = stageAnimCount;
    float r = t;
    StageAnim *e;

    if (n == 0) {
        return 0.0f;
    }
    e = stageAnimTable;
    for (i = 0; i < n; i++, e++) {
#else
    float r = t;
#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)
    float f;
#endif
    StageAnim *e;

    if (stageAnimCount == 0) {
        return 0.0f;
    }
    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
#endif
        if (key != e->entry1->no) {
            continue;
        }
#ifdef VERSION_JUN26
        if (e->mode != 0) {
#else
        if ((e->flags.i >> 30) != 0) {
#endif
            continue;
        }
        _CopyVector(e->entry2->anim->pos, v);
        CopyQuaternion(e->entry2->anim->quat, q);
        bga_SetFrame(e->entry2, (int)r, 1, e->entry1->loop);
#ifdef VERSION_JUN26
        for (k = 0; k < e->count; k++) {
            e->obj[k]->dobj->disp = 1;
        }
        e->entry2->mode = 1;
        _InitCurrentMatrix();
#else
        for (k = 0; k < e->flags.b.count; k++) {
            e->obj[k]->dobj->disp = 1;
        }
#endif
#ifdef VERSION_AUG6
        e->entry2->mode = 1;
        _InitCurrentMatrix();
#endif
        if (systemStatus[0x14 / 4] != 0) {
            break;
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC)
        r = t + e->entry2->step * (30.0f / ((60 - systemStatus[0] * 10) / systemStatus[1]));
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        bga_CalcAnimation(e->entry2, e->entry1->loop, 0);
        r = t + e->entry2->step * (30.0f / ((60 - systemStatus[0] * 10) / systemStatus[1]));
#else
        f = e->entry2->step;
        if (systemStatus[0] != 0) {
            r = t + f * 1.2075409f;
        } else {
            r = t + f;
        }
#endif
#endif
        if (e->entry2->end <= r) {
            r = e->entry1->loop != 0 ? e->entry2->start : -1.0f;
        }
        break;
    }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
#else
    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
#endif
        if (key != e->entry1->no) {
            continue;
        }
#ifdef VERSION_JUN26
        if (e->mode != 0) {
            continue;
        }
        for (k = 0; k < e->count; k++) {
#else
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
#ifndef VERSION_AUG6
        stageAnimDebugHook();
#endif
        for (k = 0; k < e->flags.b.count; k++) {
#endif
            Sub15C *d = e->obj[k]->dobj;

            for (m = 0; m < d->nodeNum; m++) {
                d->nodes[m].alpha = dv;
            }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            stageAnimObjCount += d->nodeNum;
            reg_DispObj(d);
            d->disp = 0;
        }
#else
            reg_DispObj(d);
            d->disp = 0;
            stageAnimDebugHook();
        }
        stageAnimDebugHook();
#endif
        e->entry2->mode = -1;
    }
    return r;
}

BgaPlayNode *stage_MakePlayBgAnimation(int key)
{
    int i;
    int found = -1;
    float f = 1.0f;
#ifdef VERSION_JUN26
    unsigned short num = 0;
#else
    short num = 0;
#endif
    StageAnim *e = stageAnimTable;
    BgaPlayNode *p;

    for (i = 0; i < stageAnimCount; i++, e++) {
#ifdef VERSION_JUN26
        if (key == e->entry1->no) {
            found = i;
            num = e->play++;
#else
        StageAnimDef *entry1 = e->entry1;

        if (key == entry1->no) {
            found = i;
            {
                int w = e->flags.i;

                int t = (w << 2) >> 22;

                e->flags.i = (w & 0xC00FFFFF) | (((t + 1) & 0x3FF) << 20);
                num = (short)t;
            }
#endif
            f = e->entry2->start;
            break;
        }
    }

    if (found == -1) {
        /* "the given ID does not exist, or its animation is not loaded" */
        debug_StdPrintfDummy("指定したIDが存在しないか、アニメーションが読み込まれていません.\n");
        return 0;
    }

    p = iosMallocDebug(ios_partition_seki, 64, __FILE__, LN(1494, 1481, 1481, 1450, 1429, 1312));
    if (p == 0) {
        /* "cannot allocate memory for the stage segment (heap exhausted)" */
        debug_StdPrintfDummy("ステージセグメントにメモリが確保できません.(ヒープメモリ不足)\n");
        return 0;
    }

#ifdef VERSION_JUN26
    p->no = key;
    p->play = 1;
#else
    ((PlayWord *)p)->l = ((((PlayWord *)p)->l & ~0x3FFF) | (key & 0x3FFF) | 0x4000) & ~0x8000;
#endif
    p->num = num;
    p->frame = f;
    p->speed = 1.0f;
    p->scale = 1.0f;
    if (bgaPlayList != 0) {
        bgaPlayList->prev = p;
    }
    p->prev = 0;
    p->next = bgaPlayList;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    bgaPlayCount++;
#endif
    bgaPlayList = p;
    return p;
}

void stage_KillPlayBgAnimation(BgaPlayNode **self)
{
    BgaPlayNode *node = *self;
    BgaPlayNode *next;
    BgaPlayNode *prev;
    if (node == 0)
        return;
    next = node->prev;
    if (next != 0) {
        next->next = node->next;
    } else {
        bgaPlayList = node->next;
        node = *self;
    }
    prev = node->next;
    if (prev != 0) {
        prev->prev = node->prev;
    }
    if (bgaPlayList != 0) {
        bgaPlayList->prev = 0;
    }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    bgaPlayCount--;
#endif
    freeseki(*self);
}

#ifndef VERSION_JUN26
inline void stage_KillPlayBgAnimationIfOverMaxCount(int key, int maxCount)
{
    AnimNode *p = (AnimNode *)bgaPlayList;
    int count = 0;
    while (p != 0) {
        long v = p->bits;
        if ((((unsigned short)v << 18) >> 18) == key) {
            if (!(v & 0x8000)) {
                count++;
                if (maxCount < count) {
                    p->bits = v | 0x8000;
                }
            }
        }
        p = p->next;
    }
}
#endif

/* Inlined twice in stage_DispBgAnimation and twice in
 * stage_DispBgAnimationNoFinish. */
static inline void stage_SetBgAnimationPlayNode(BgaPlayNode *node, int key) /* derived name */
{
    int i;
    int k;
    StageAnim *e;

    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
#ifdef VERSION_JUN26
            if (e->mode == 0) {
                for (k = 0; k < e->count; k++) {
                    e->obj[k]->dobj->lineHdr = (char *)node;
#else
            if ((e->flags.i >> 30) == 0) {
                for (k = 0; k < e->flags.b.count; k++) {
#ifdef VERSION_NTSC
                    *(void **)(*(char **)&e->obj[k]->dobj + 0x81C) = node;
#else
#ifdef VERSION_AUG6
                    *(void **)(*(char **)&e->obj[k]->dobj + 0x80C) = node;
#else
                    *(void **)(*(char **)&e->obj[k]->dobj + 0x850) = node;
#endif
#endif
#endif
                }
            }
        }
    }
}

int stage_DispBgAnimation(BgaPlayNode **self)
{
    if (*self == 0) {
        return -1;
    }
#ifdef VERSION_JUN26
    if ((*self)->no == -1) {
        return 0;
#else
    if ((*self)->kill) {
        stage_KillPlayBgAnimation(self);
        *self = 0;
        return -1;
#endif
    }
    if ((*self)->scale != 1.0f) {
        stage_SetScale((*self)->no, (*self)->scale);
    }
    if ((*self)->speed == 1.0f) {
        stage_SetBgAnimationPlayNode(*self, (*self)->no);
        (*self)->frame =
            stage_PlayBgAnimation((*self)->no, (*self)->frame, (*self)->pos, (*self)->rot);
    } else {
        stage_SetBgAnimationPlayNode(*self, (*self)->no);
        (*self)->frame = stage_PlayBgAnimationDissolve((*self)->no, (*self)->pos, (*self)->rot,
                                                       (*self)->frame, (*self)->speed);
    }
    (*self)->play = 0;
    if ((*self)->frame == -1.0f) {
        stage_KillPlayBgAnimation(self);
        *self = 0;
        return -1;
    }
    return 0;
}

#ifndef VERSION_JUN26
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
int stage_DispBgAnimationNoFinish(BgaPlayNode **self)
{
    int i;
    StageAnim *e;

    if (*self == 0) {
        return -1;
    }
    if ((*self)->kill) {
        stage_KillPlayBgAnimation(self);
        *self = 0;
        return -1;
    }
    if ((*self)->scale != 1.0f) {
        stage_SetScale((*self)->no, (*self)->scale);
    }
    if ((*self)->speed == 1.0f) {
        stage_SetBgAnimationPlayNode(*self, (*self)->no);
        (*self)->frame =
            stage_PlayBgAnimation((*self)->no, (*self)->frame, (*self)->pos, (*self)->rot);
    } else {
        stage_SetBgAnimationPlayNode(*self, (*self)->no);
        (*self)->frame = stage_PlayBgAnimationDissolve((*self)->no, (*self)->pos, (*self)->rot,
                                                       (*self)->frame, (*self)->speed);
    }
    (*self)->play = 0;
    if ((*self)->frame == -1.0f) {
        for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
            if ((*self)->no == e->entry1->no) {
                if ((e->flags.i >> 30) == 0) {
                    /* a jump to the function's exit, the way Light.c leaves
                       its loops (goto found) */
                    (*self)->frame = e->entry2->end;
                    goto end;
                }
            }
        }
    }
end:
    return 0;
}
#endif

static void stage_SetCameraForceOff(void)
{
    bga_SetCameraForceOff();
}
#endif
