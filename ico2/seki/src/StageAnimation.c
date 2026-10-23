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

typedef union { /* field names derived */
    long l;
    short h;
} PlayWord; /* derived name */

typedef struct { /* field names derived */
    char bytes[8];
} Blob8; /* derived name */

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

/* The number of loaded animation records, the head of the play-node list,
   and the record table stage_Init fills, 82 records of 0x290 bytes. */
static int stageAnimCount; /* derived name */

static BgaPlayNode *bgaPlayList; /* derived name */

/* the number of play nodes stage_MakePlayBgAnimation has linked and
   stage_KillPlayBgAnimation has not yet freed */
static int bgaPlayCount; /* derived name */

/* the objects stage_PlayBgAnimation and stage_DispAnimation count in a
   frame, printed as "O:%d" and cleared at the end of stage_DispAnimation */
static int stageAnimObjCount; /* derived name */

static StageAnim stageAnimTable[82]; /* derived name */

#include "ios.h"
#include <stdio.h>
#include "include_asm.h"

/* objAction's row as this file reads it: the two stage animations the
   object plays (typedef.h's OaRecB carries them as baseMode and anim2) */
typedef struct { /* field names derived */
    int anim[2]; /* 0x00 */
    char pad8[12];
} StgBgaSet; /* derived name */

extern StgBgaSet objAction[];
extern StageAnimDef stageTable[];

INCLUDE_ASM(stage_MakeGObj);

INCLUDE_ASM(stage_ApplyData);

/* stage_Init reaches the table's records through a pointer */
#define STG ((StageAnim *)stageAnimTable) /* derived name */
/* an animated object's DObj, its 0x15C word read through AnimWord */
#define STG_SUB(o) ((Sub15C *)((AnimWord *)((char *)(o) + 0x15C))->i) /* derived name */

/* The stage animation TTY trace, built only when DEBUG is defined; the
   retail build leaves the helper without a body. */
static __inline__ void stageAnimDebugHook(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("stage anim %d\n", stageAnimCount);
#endif
}

INCLUDE_ASM(stage_Init);

void stage_SetAnimation(int key, int mode, int frame)
{
    int uid = -1;
    int i;
    int k;
    int dbg = 0; /* local debug switch, see the test in case 0 below */
    StageAnim *e;

    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key != e->entry1->no) {
            continue;
        }
        switch (e->flags.i >> 30) {
        case 0:
            uid = e->entry2->group;
            /* a local debug switch, off: report a bad group number */
            if (dbg) {
                debug_StdPrintfDummy("Illegal Group No. %d\n", uid);
            }
            bga_SetFrame(e->entry2, frame, mode, e->entry1->loop);
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
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
            if ((e->flags.i >> 30) != 0) {
                continue;
            }
            if (uid != e->entry2->group || key == e->entry1->no) {
                continue;
            }
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
                if (*(char **)&e->obj[k]->dobj != 0) {
                    e->obj[k]->dobj->disp = 0;
                }
            }
        }
    }
}

INCLUDE_ASM_LIT(stage_CheckAnimationFinish);

INCLUDE_ASM(stage_ContinueAnimation);

inline int stage_CheckAnimationFrame(int key, int frame, int reset)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        StageAnimDef *entry1 = e->entry1;
        if (key == entry1->no) {
            int mode = e->flags.i >> 30;
            switch (mode) {
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
            int mode = e->flags.i >> 30;
            switch (mode) {
            case 0:
                return bga_CheckAnimationFrameIn(e->entry2, in, out);
            case 1:
                return bga_CheckSdfCameraFrameIn(e->entry3, in, out);
            }
        }
    }
    return -1;
}

INCLUDE_ASM(stage_ResetAnimation);

INCLUDE_ASM(stage_CalcAnimationNoParent);

INCLUDE_ASM(stage_CalcAnimationParent);

INCLUDE_ASM(stage_DispAnimation);

inline void stage_SetLoopFlag(int key, int loop)
{
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
            p = &(*((volatile int *)(&stageAnimCount)));
            count = *p;
        }
    }
}

inline void stage_SetFrameStep(int target, int val)
{
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
}

inline void stage_SetParentOfGObj(int key, void *parent)
{
    int i;
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
    }
}

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

INCLUDE_ASM(stage_SetScale);

INCLUDE_ASM(stage_PlayBgAnimation);

INCLUDE_ASM(stage_PlayBgAnimationDissolve);

INCLUDE_ASM(stage_MakePlayBgAnimation);

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

/* Inlined twice in stage_DispBgAnimation and twice in
 * stage_DispBgAnimationNoFinish. */
static inline void stage_SetBgAnimationPlayNode(BgaPlayNode *node, int key) /* derived name */
{
    int i;
    int k;
    StageAnim *e;

    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key == e->entry1->no) {
            if ((e->flags.i >> 30) == 0) {
                for (k = 0; k < e->flags.b.count; k++) {
                    *(void **)(*(char **)&e->obj[k]->dobj + 0x850) = node;
                }
            }
        }
    }
}

INCLUDE_ASM(stage_DispBgAnimation);

static void stage_SetCameraForceOff(void)
{
    bga_SetCameraForceOff();
}

INCLUDE_ASM(stage_CheckAnimationFinish);
