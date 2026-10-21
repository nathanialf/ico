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

typedef struct { /* field names derived */
    char bytes[8];
} Blob8; /* derived name */

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

/* The number of loaded animation records, the head of the play-node list
   and the number of nodes on it, the count of nodes stage_DispAnimation
   reports, and the record table stage_Init fills, 80 records of 0x298
   bytes. */
static int stageAnimCount; /* derived name */

static BgaPlayNode *bgaPlayList; /* derived name */

static int bgaPlayCount; /* derived name */

static int bgaDispNodeCount; /* derived name */

static StageAnim stageAnimTable[80]; /* derived name */

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
    int kind = dat[0];
    int aux = dat[1];
    StageAnim *e = &stageAnimTable[no];

    for (i = 0; i < e->count; i++) {
        if (e->kind[i] == kind) {
            debug_StdPrintfDummy("Bga Object Already %d %d %d\n", kind, kind, no);
            return;
        }
    }
    g = isysGObjAdd(0, 0, 0);
    if (g == 0) {
        debug_StdPrintfDummy("stage_MakeGObj:can't alloc gobj %d\n", no);
        debug_assert(__FILE__, 404);
        __assert(__FILE__, 404, "0");
    }
    e->kind[e->count] = kind;
    g->labelType = 1;
    g->labelId = 0;
    isysGObjKindTableAdd(g, aux);
    isysGObjProcAdd(g, 0, 1, 0x16);
    isysGObjProcAdd(g, 0, 1, 0x17);
    isysGObjProcAdd(g, 0, 1, 0x18);
    isysGObjLinkObjDL(g, 0, 0, 7, 0xFFFFFFFF);
    g->word24 = 0;
    e->obj[e->count] = g;
    d = CSVSYSTEM_InitDObj(kind, &init);
    *(int *)&g->dobj = (int)d;
    d->colPerNode = 1;
    e->data[e->count] = dat;
    e->count++;
    if (e->count >= 64) {
        debug_Assert("Too much Stage Animation Objects.\n");
        debug_assert(__FILE__, 425);
        __assert(__FILE__, 425, "0");
    }
}

void stage_ApplyData(char *name, char *data)
{
    const int *tbl[2] = {&stageData[stage_no].animLayoutFirst, &stageData[stage_no].labelTop};
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
                    if (id != 763) {
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
    debug_StdPrintfDummy("stage_ApplyData:Data is not registered. %s\n", name);
    debug_assert(__FILE__, 474);
    __assert(__FILE__, 474, "0");
}

/* stage_Init reaches the table's records through a pointer */
#define STG ((StageAnim *)stageAnimTable) /* derived name */
/* an animated object's DObj, its 0x15C word read through AnimWord */
#define STG_SUB(o) ((Sub15C *)((AnimWord *)((char *)(o) + 0x15C))->i) /* derived name */

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
        for (k = 0; k < 64; k++) {
            STG[i].kind[k] = -1;
        }
    }
    stageAnimCount = 0;
    for (i = 0; i < 80; i++) {
        STG[i].count = 0;
    }
    bgaPlayList = 0;
    bgaPlayCount = 0;
    bga_ResetCamera();
    for (m = 0; m < 2; m++) {
        for (i = tbl[m][0]; i < tbl[m][1]; i++) {
            rec = &objLayout[i];
            n = rec->action;
            if (n != 0) {
                StgBgaSet *ent = &objAction[n];

                for (k = 0; k < 2; k++) {
                    id = ent->anim[k];
                    obj = &stageTable[id];
                    if (id != 763) {
                        if (strncmp(obj->data, "BGA", 3) == 0) {
                            STG[stageAnimCount].mode = 0;
                            stageAnimTable[stageAnimCount].entry2 = obj->data;
                            ((BgaHeader *)obj->data)->group = obj->group;
                            ((BgaHeader *)obj->data)->cut = obj->cut;
                            stageAnimTable[stageAnimCount].entry1 = obj;
                            STG[stageAnimCount].play = 0;
                            p = &objTableScene[obj->objFirst];
                            q = &objTableScene[obj->objLast];
                            for (; p != q; p++) {
                                stage_MakeGObj((int *)p, stageAnimCount);
                            }
                        } else {
                            STG[stageAnimCount].mode = 1;
                            stageAnimTable[stageAnimCount].entry3 = obj->data;
                            stageAnimTable[stageAnimCount].entry1 = obj;
                        }
                        stageAnimCount++;
                        if (stageAnimCount >= 81) {
                            /* "stgBgas has %d, over MAX_ANIM_KIND %d" */
                            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n",
                                                 stageAnimCount, 80);
                            /* "too many BgAnimation kinds in one stage" */
                            debug_StdPrintfDummy("1ステージ中の BgAnimation の種類が多すぎます\n");
                            debug_assert(__FILE__, 556);
                            __assert(__FILE__, 556, "0");
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < stageAnimCount; i++) {
        if (STG[i].count >= 64) {
            /* "stgBgas has %d, over MAX_ANIM_GOBJ %d" */
            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました\n", STG[i].count,
                                 64);
            debug_assert(__FILE__, 566);
            __assert(__FILE__, 566, "0");
        }
        max = max < STG[i].count ? STG[i].count : max;
    }
    debug_StdPrintfDummy("Max Bga = %d // Max DObj %d\n", stageAnimCount, max);
    if (p != 0) {
        e = stageAnimTable;
        for (i = 0; i < stageAnimCount; i++, e++) {
            if (e->mode == 1) {
                continue;
            }
            for (k = 0; k < e->count; k++) {
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
                bga_ApplyDObject(a, e->obj, e->count);
            }
            e->nodes = 0;
            for (k = 0; k < e->count; k++) {
                if (STG_SUB(e->obj[k])->nodeMtx != 0) {
                    iosFree((void *)STG_SUB(e->obj[k])->nodeMtx);
                }
                if (STG_SUB(e->obj[k])->nodeQuat != 0) {
                    iosFree((void *)STG_SUB(e->obj[k])->nodeQuat);
                }
                STG_SUB(e->obj[k])->nodeMtx = 0;
                STG_SUB(e->obj[k])->nodeQuat = 0;
                STG_SUB(e->obj[k])->nodeMtx = (int)iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 6, __FILE__, 610);
                STG_SUB(e->obj[k])->nodeQuat = (int)iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 4, __FILE__, 610);
                /* the reallocation block's count line, as chain.c, boy.c and
                   box.c spell the same block, here passed the count field
                   itself: a store of the field to itself */
                STG_SUB(e->obj[k])->nodeNum = STG_SUB(e->obj[k])->nodeNum;
                if (STG_SUB(e->obj[k])->nodes != 0) {
                    iosFree(STG_SUB(e->obj[k])->nodes);
                }
                STG_SUB(e->obj[k])->nodes = iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum * 80, __FILE__, 610);
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
                e->nodes += STG_SUB(e->obj[k])->nodeNum;
                for (u = 0; u < STG_SUB(e->obj[k])->nodeNum; u++) {
                    _UnitMatrix((void *)(STG_SUB(e->obj[k])->nodeMtx + u * 64));
                    SetIdentityQuaternion((void *)(STG_SUB(e->obj[k])->nodeQuat + u * 16));
                }
            }
        }
        e = stageAnimTable;
        for (i = 0; i < stageAnimCount; i++, e++) {
            if (e->mode == 1) {
                continue;
            }
            for (k = 0; k < e->count; k++) {
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

void stage_SetAnimation(int key, int mode, int frame)
{
    int uid = -1;
    int i;
    int k;
    int dbg = 0; /* local debug switch, see the test in case 0 below */
    StageAnim *e;

    debug_StdPrintfDummy("stage_SetAnimation:%d %d\n", key, mode);
    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key != e->entry1->no) {
            continue;
        }
        switch (e->mode) {
        case 0:
            uid = e->entry2->group;
            /* a local debug switch, off: report a bad group number */
            if (dbg) {
                debug_StdPrintfDummy("Illegal Group No. %d\n", uid);
            }
            bga_SetFrame(e->entry2, frame, mode, e->entry1->loop);
            for (k = 0; k < e->count; k++) {
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
            if (e->mode != 0) {
                continue;
            }
            if (uid != e->entry2->group || key == e->entry1->no) {
                continue;
            }
            for (k = 0; k < e->count; k++) {
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
            switch (e->mode) {
            case 0:
                return bga_CheckAnimationFinish(e->entry2);
            case 1:
                return bga_CheckSdfCameraFinish(e->entry3);
            }
        }
    }
    debug_StdPrintfDummy("stage_CheckAnimationFinish:illegal Animation No.\n");
    debug_assert(__FILE__, 768);
    __assert(__FILE__, 768, "0");
    return 0;
}

int stage_ContinueAnimation(int key, int next)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        StageAnimDef *entry1 = e->entry1;
        if (key == entry1->no) {
            switch (e->mode) {
            case 0:
                if (bga_CheckAnimationFinish(e->entry2) != 0) {
                    stage_SetAnimation(key, 0, 0);
                    stage_SetAnimation(next, 1, 0);
                    return 1;
                }
                return 0;
            case 1:
                if (bga_CheckSdfCameraFinish(e->entry3) == 0) {
                    return 0;
                }
                stage_SetAnimation(key, 0, 0);
                stage_SetAnimation(next, 1, 0);
                return 1;
            }
        }
    }
    debug_StdPrintfDummy("stage_ContinueAnimation:illegal Animation No.\n");
    debug_assert(__FILE__, 808);
    __assert(__FILE__, 808, "0");
    return 0;
}

inline int stage_CheckAnimationFrame(int key, int frame, int reset)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        StageAnimDef *entry1 = e->entry1;
        if (key == entry1->no) {
            switch (e->mode) {
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
            switch (e->mode) {
            case 0:
                return bga_CheckAnimationFrameIn(e->entry2, in, out);
            case 1:
                return bga_CheckSdfCameraFrameIn(e->entry3, in, out);
            }
        }
    }
    return -1;
}

void stage_CalcAnimationNoParent(void)
{
    int i;
    StageAnim *e;

    if (lock_execIcoMisc != 0) {
        return;
    }
    if (stageAnimCount == 0) {
        return;
    }
    if (systemStatus[0x14 / 4] == 0) {
        light_KillAllFixLight();
    }
    bga_SetUniqAnimationFlag(1);
    _InitCurrentMatrix();
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        switch (e->mode) {
        case 0: {
            BgaHeader *entry2 = e->entry2;

            if (entry2->anim->obj != 0) {
                continue;
            }
            if (systemStatus[0x14 / 4] != 0) {
                continue;
            }
            switch (entry2->mode) {
            case -1: {
                int k;

                for (k = 0; k < e->count; k++) {
                    e->obj[k]->dobj->disp = 0;
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

    if (lock_execIcoMisc != 0) {
        return;
    }
    if (stageAnimCount == 0) {
        return;
    }
    bga_SetUniqAnimationFlag(1);
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (e->mode != 0) {
            continue;
        }
        entry2 = e->entry2;
        if (entry2->anim->obj == 0) {
            continue;
        }
        if (systemStatus[0x14 / 4] != 0) {
            continue;
        }
        switch (entry2->mode) {
        case -1: {
            int k;

            for (k = 0; k < e->count; k++) {
                e->obj[k]->dobj->disp = 0;
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
        signed char lv;
        int k;

        if (e->mode != 0) {
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
        for (k = 0; k < e->count; k++) {
            if (e->obj[k]->dobj->disp != 0) {
                reg_DispObj(e->obj[k]->dobj);
                bgaDispNodeCount += e->obj[k]->dobj->nodeNum;
            }
        }
    }
    bga_DispLightning();
    if (debug_font_flag2 != 0 || (debug_font_flag & 1) != 0) {
        debug_Printf(400, 20, 0xCCCCCC00u, "O:%d", bgaDispNodeCount);
    }
    bgaDispNodeCount = 0;
}

inline void stage_SetLoopFlag(int key, int loop)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            e->entry1->loop = loop;
        }
    }
}

inline void stage_SetFrameStep(int target, int val)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (target == e->entry1->no) {
            e->entry2->step = (float)val;
        }
    }
}

inline void stage_SetParentOfGObj(int key, void *parent)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            *(Blob8 *)&e->entry2->anim->obj = *(Blob8 *)parent;
        }
    }
}

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

float stage_PlayBgAnimation(int key, float t, void *v, void *q)
{
    int i;
    int k;
    int n = stageAnimCount;
    float r = t;
    StageAnim *e;

    if (n == 0) {
        return 0.0f;
    }
    e = stageAnimTable;
    for (i = 0; i < n; i++, e++) {
        if (key != e->entry1->no) {
            continue;
        }
        if (e->mode != 0) {
            continue;
        }
        _CopyVector(e->entry2->anim->pos, v);
        CopyQuaternion(e->entry2->anim->quat, q);
        bga_SetFrame(e->entry2, (int)r, 1, e->entry1->loop);
        for (k = 0; k < e->count; k++) {
            e->obj[k]->dobj->disp = 1;
        }
        e->entry2->mode = 1;
        _InitCurrentMatrix();
        if (systemStatus[0x14 / 4] != 0) {
            break;
        }
        bga_CalcAnimation(e->entry2, e->entry1->loop, 0);
        r = t + e->entry2->step * (30.0f / ((60 - systemStatus[0] * 10) / systemStatus[1]));
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
        if (e->mode != 0) {
            continue;
        }
        for (k = 0; k < e->count; k++) {
            Sub15C *d = e->obj[k]->dobj;

            bgaDispNodeCount += d->nodeNum;
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
    int n = stageAnimCount;
    float r = t;
    StageAnim *e;

    if (n == 0) {
        return 0.0f;
    }
    e = stageAnimTable;
    for (i = 0; i < n; i++, e++) {
        if (key != e->entry1->no) {
            continue;
        }
        if (e->mode != 0) {
            continue;
        }
        _CopyVector(e->entry2->anim->pos, v);
        CopyQuaternion(e->entry2->anim->quat, q);
        bga_SetFrame(e->entry2, (int)r, 1, e->entry1->loop);
        for (k = 0; k < e->count; k++) {
            e->obj[k]->dobj->disp = 1;
        }
        e->entry2->mode = 1;
        _InitCurrentMatrix();
        if (systemStatus[0x14 / 4] != 0) {
            break;
        }
        bga_CalcAnimation(e->entry2, e->entry1->loop, 0);
        r = t + e->entry2->step * (30.0f / ((60 - systemStatus[0] * 10) / systemStatus[1]));
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
        if (e->mode != 0) {
            continue;
        }
        for (k = 0; k < e->count; k++) {
            Sub15C *d = e->obj[k]->dobj;

            for (m = 0; m < d->nodeNum; m++) {
                d->nodes[m].alpha = dv;
            }
            bgaDispNodeCount += d->nodeNum;
            reg_DispObj(d);
            d->disp = 0;
        }
        e->entry2->mode = -1;
    }
    return r;
}

BgaPlayNode *stage_MakePlayBgAnimation(int key)
{
    int i;
    int found = -1;
    float f = 1.0f;
    unsigned short num = 0;
    StageAnim *e = stageAnimTable;
    BgaPlayNode *p;

    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            found = i;
            num = e->play++;
            f = e->entry2->start;
            break;
        }
    }

    if (found == -1) {
        /* "the given ID does not exist, or its animation is not loaded" */
        debug_StdPrintfDummy("指定したIDが存在しないか、アニメーションが読み込まれていません.\n");
        return 0;
    }

    p = iosMallocDebug(ios_partition_seki, 64, __FILE__, 1312);
    if (p == 0) {
        /* "cannot allocate memory for the stage segment (heap exhausted)" */
        debug_StdPrintfDummy("ステージセグメントにメモリが確保できません.(ヒープメモリ不足)\n");
        return 0;
    }

    p->no = key;
    p->play = 1;
    p->num = num;
    p->frame = f;
    p->speed = 1.0f;
    p->scale = 1.0f;
    if (bgaPlayList != 0) {
        bgaPlayList->prev = p;
    }
    p->prev = 0;
    p->next = bgaPlayList;
    bgaPlayCount++;
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
    bgaPlayCount--;
    freeseki(*self);
}

/* Inlined twice in stage_DispBgAnimation. */
static inline void stage_SetBgAnimationPlayNode(BgaPlayNode *node, int key) /* derived name */
{
    int i;
    int k;
    StageAnim *e;

    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            if (e->mode == 0) {
                for (k = 0; k < e->count; k++) {
                    e->obj[k]->dobj->lineHdr = (char *)node;
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
    if ((*self)->no == -1) {
        return 0;
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
