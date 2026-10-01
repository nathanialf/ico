#include "DObj.h"
#include "debug.h"
#include "debug_exception.h"
#include "memory.h"
#include "gobj.h"
#include "gobj_dl.h"
#include "gobj_process.h"
#include "Basic.h"
#include "BgAnimation.h"
#include "Light.h"
#include "Matrix.h"
#include "RegistPacket.h"
#include "quaternion.h"
#include "GsBase.h"
#include "main.h"
#include <string.h>
#include <assert.h>

typedef union {
    int i;
    float f;
} AnimWord;

typedef union {
    long l;
    short h;
} PlayWord;

typedef struct {
    char _b[8];
} Blob8;

/* the animation record's packed word: its object count, node count, play
   count and mode.  WHAT THE BYTES PIN: the mode is tested as the word shifted
   down 30 (sra), where a bit-field compare against a constant folds to a
   masked compare, and stage_SetAnimation's loop reads the count as the
   shifted word (as a field its allocation rotates, measured) */
typedef union {
    int i;

    struct {
        int count : 10;
        int nodes : 10;
        int play : 10;
        int mode : 2;
    } b;
} StageFlags;

struct B8 {
    char _b[8];
};

typedef struct AnimNode {
    long field0; /* 0x00 */
    char _pad[12];
    struct AnimNode *next; /* 0x14 */
} AnimNode;

/* RECONSTRUCTION: the 0x290-byte animation record stageAnimTable holds, laid out
   from the offsets this TU reads (kind, object and data tables, the three
   entry pointers, the packed count/mode word). stage_SetScale and
   stage_SetAnimation read the object table as a member of this record:
   expand_expr forces the member's address `e + 0x80` into its own register
   before the index is added, which is the ROM's addiu/addu pair (and in
   stage_SetScale the k-loop test's own copy of it). */
typedef struct {
    short kind[64];   /* 0x000 */
    GObj *obj[64];    /* 0x080 */
    int *data[64];    /* 0x180 */
    int *entry1;      /* 0x280 */
    char *entry2;     /* 0x284 */
    char *entry3;     /* 0x288 */
    StageFlags flags; /* 0x28C */
} StageAnim;

/* RECONSTRUCTION: the play node stage_MakePlayBgAnimation links into
   bgaPlayList and stage_DispBgAnimation walks. The ROM reads its first word as
   int bit-fields in a doubleword unit (ld, then andi 0xFFFF/sll 18/sra 18 for
   the 14-bit animation number, andi 0x8000 for the kill flag, and 0xFFFFBFFF
   for the play flag), which is what gcc 2.9 emits for int bit-fields in a
   16-byte aligned record; the names are this repository's. */
typedef struct {
    int no : 14; /* 0x00 */
    int play : 1;
    int kill : 1;
    short num;   /* 0x02 */
    float frame; /* 0x04 */
    float speed; /* 0x08 */
    float scale; /* 0x0C */
    void *next;  /* 0x10 */
    void *prev;  /* 0x14 */
    int _18[2];
    sceVu0FVECTOR pos; /* 0x20 */
    float rot[4];      /* 0x30 */
} BgaPlayNode;

/* The TU's own .sbss and .bss, in ROM run order (names ours): the number of
   loaded animation records, the head of the play-node list, and the record
   table stage_Init fills, 87 records of 0x290 bytes (0xDEF0, the whole run
   from Shadow's .bss to Texture's). */
static int stageAnimCount;

static int *bgaPlayList;

static StageAnim stageAnimTable[87];

extern GenGeo objLayout[];

/* The layout record a stage object is made with and handed to its init
   function: position, rotation, scale and a flag word (names ours). */
typedef struct {
    sceVu0FVECTOR pos;   /* 0x00 */
    sceVu0FVECTOR rot;   /* 0x10 */
    sceVu0FVECTOR scale; /* 0x20 */
    int flag;            /* 0x30 */
} StageGObjInit;

#include "StageAnimation.h"
#include "ios.h"
#include <stdio.h>

/* objAction's row as this TU reads it: the two stage animations the
   object plays (typedef.h's OaRecB carries them as baseMode and anim2) */
typedef struct { /* field names derived */
    int anim[2]; /* 0x00 */
    char pad8[12];
} StgBgaSet;

extern StgBgaSet objAction[];
extern StageAnimDef stageTable[];

void stage_MakeGObj(int *dat, int no)
{
    StageGObjInit init = {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
    int i;
    GObj *g;
    char *d;
    int w;
    int kind = dat[0];
    int aux = dat[1];
    StageAnim *e = &stageAnimTable[no];

    for (i = 0; i < e->flags.b.count; i++) {
        if (e->kind[i] == kind) {
            debug_StdPrintfDummy("Bga Object Already %d %d %d\n", kind, kind, no);
            return;
        }
    }
    g = isysGObjAdd(0, 0, 0);
    if (g == 0) {
        debug_StdPrintfDummy("stage_MakeGObj:can't alloc gobj %d\n", no);
        debug_assert(__FILE__, 541);
        __assert(__FILE__, 541, "0");
    }
    e->kind[e->flags.b.count] = kind;
    g->labelType = 1;
    g->labelId = 0;
    isysGObjKindTableAdd(g, aux);
    isysGObjProcAdd(g, 0, 1, 0x16);
    isysGObjProcAdd(g, 0, 1, 0x17);
    isysGObjProcAdd(g, 0, 1, 0x18);
    isysGObjLinkObjDL(g, 0, 0, 7, 0xFFFFFFFF);
    *(int *)((char *)g + 0x24) = 0;
    e->obj[e->flags.b.count] = g;
    d = CSVSYSTEM_InitDObj(kind, &init);
    *(int *)&g->dobj = (int)d;
    *(int *)(d + 0x80) = 1;
    e->data[e->flags.b.count] = dat;
    w = (e->flags.i & ~0x3FF) | ((e->flags.b.count + 1) & 0x3FF);
    e->flags.i = w;
    if (((w << 22) >> 22) >= 64) {
        debug_Assert("Too much Stage Animation Objects.\n");
        debug_assert(__FILE__, 562);
        __assert(__FILE__, 562, "0");
    }
}

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
                    if (id != 972) {
                        if (strcmp(name, obj->path) == 0) {
                            if (strncmp(data, "BGA", 3) == 0) {
                                obj->data = (void *)bga_InitData(data);
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
    debug_assertMessage(__FILE__, 617, buf);
    __assert(__FILE__, 617, "e");
}

/* stage_Init reaches the table's records through a pointer: indexing the
   array itself folds the table address into each access and moves gcse's
   expression table (measured) */
#define STG ((StageAnim *)stageAnimTable)

extern char objKindData[];
extern void bga_ApplyDObject(char *a0, GObj **a1, int a2, int a3);

/* an animated object's DObj, its 0x15C word read through AnimWord */
#define STG_SUB(o) ((Sub15C *)((AnimWord *)((char *)(o) + 0x15C))->i) /* derived name */

/* The stage animation TTY trace (our name and text), built only when DEBUG is
   defined; the retail build does not define it, so the preprocessor leaves
   the helper without a body.  A parameterless inline whose body is empty is
   saved as the single (use (const_int 0)) flow.c:count_basic_blocks gives a
   function with no insns, so each call emits no byte but leaves that insn,
   which loop.c and gcse count and flow never deletes (a helper with a
   parameter saves no USE; its parameter move is an insn).
   WHAT THE BYTES PIN in stage_PlayBgAnimationDissolve: the ROM keeps the m
   loop's `li 80` and the `li -1` of the entry2 store inside the second loop,
   and loop.c's move_movables (threshold 64 with a call in the loop) hoists
   both into two more callee-saved registers (frame 0xC0 against the ROM's
   0xA0) unless that loop counts at least 65 real insns at both loop passes.
   Its statements give 63 and 62, so three or more insns that emit no byte sat
   in that loop: three or four calls are byte-identical (before the k loop,
   after the 0x74 store, after the k loop, or two after the store), two let
   the second pass hoist the stride, and one between d and the m loop changes
   five words. The January listing has the gp display counter (lw, lw, addu,
   sw) at line 1453 and no code at 1445, 1452, 1454 and 1455, and the retail
   .sbss has no counter word. WHAT THEY CANNOT PIN: the trace's text, its
   lines, or the count beyond three.
   The same hook at stage_PlayBgAnimation's counter (listing line 1380)
   changes six words there, so these are not that counter's remnant.
   stage_Init's uses carry their own pinned/not-pinned comments; the
   definition sits above stage_Init because gcc 2.9 inlines only a body it
   has already read. */
static __inline__ void stageAnimDebugHook(void)
{
#ifdef DEBUG
    scePrintf("stage anim %d\n", stageAnimCount);
#endif
}

int stage_Init(void)
{
    const StgObjDat *p = 0;
    const int *tbl[2] = {&stageData[stage_no].animLayoutFirst, &stageData[stage_no].labelTop};
    StageGObjInit arg;
    int max = 0;
    int m;
    int i;
    int k;
    int t;
    int u;
    int n;
    int id;
    int no;
    const StgObjDat *q;
    GenGeo *rec;
    char *tbl2;
    StageAnimDef *obj;
    GObj *g;
    char *a;
    char *r;
    int (*fn)(GObj *, StageGObjInit *);
    StageAnim *e;

    bga_InitBGA();
    for (i = 0; i < 87; i++) {
        for (k = 0; k < 64; k++) {
            STG[i].kind[k] = -1;
        }
    }
    stageAnimCount = 0;
    for (i = 0; i < 87; i++) {
        STG[i].flags.b.count = 0;
    }
    /* The DEBUG-build trace (see stageAnimDebugHook), here and at the next two
       code-free runs. The January listing zeroes a gp counter at line 650
       (rows 649, 651 to 654, 656 to 660 and 662 to 666 code-free) and the
       retail build has neither that code nor the .sbss word. WHAT THE BYTES
       PIN: stage_Init reaches gcse with 656 to 659 insns, six to nine more
       than its statements give, so the expression table has 329 buckets and
       puts e + 0x180 ahead of m + 1, which is the ROM's spill slot order
       (dats base 0x78, m + 1 at 0x7C); at 325 buckets the two slots swap.
       Three calls here in a row and one in each of these three runs are the
       same object (cf6, measured). WHAT THEY CANNOT PIN: how many of those
       insns sat in these runs and how many at the code-free rows 679, 692 and
       697 below, or the trace's text. */
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
                    if (id != 972) {
                        if (strncmp(obj->data, "BGA", 3) == 0) {
                            /* Listing row 679, code-free. WHAT THE BYTES PIN: one
                           insn between the stageAnimCount load and the 0x284 store
                           at local-alloc, gone by final; without it the flags
                           address takes $4 and the 0x284 address $3, the
                           ROM's are the other way round. WHAT THEY CANNOT
                           PIN: the statement's text. */
                            stageAnimDebugHook();
                            STG[stageAnimCount].flags.i &= 0x3FFFFFFF;
                            *(int *)((char *)stageAnimTable + stageAnimCount * 0x290 + 0x284) =
                                (int)obj->data;
                            *(int *)((char *)obj->data + 0x4) = obj->word48;
                            ((char *)obj->data)[0xB] = obj->byte4C;
                            *(char *)(*(int *)((char *)stageAnimTable + stageAnimCount * 0x290 +
                                               0x284) +
                                      0xA) = -1;
                            *(int *)((char *)stageAnimTable + stageAnimCount * 0x290 + 0x280) =
                                (int)obj;
                            STG[stageAnimCount].flags.b.play = 0;
                            p = &objTableScene[obj->objFirst];
                            q = &objTableScene[obj->objLast];
                            for (; p != q; p++) {
                                stage_MakeGObj((int *)p, stageAnimCount);
                            }
                        } else {
                            /* listing row 692, code-free: counted in the gcse
                           window above */
                            stageAnimDebugHook();
                            STG[stageAnimCount].flags.i =
                                (STG[stageAnimCount].flags.i & 0x3FFFFFFF) | 0x40000000;
                            stageAnimTable[stageAnimCount].entry3 = obj->data;
                            *(int *)((char *)stageAnimTable + stageAnimCount * 0x290 + 0x280) =
                                (int)obj;
                        }
                        /* listing row 697, code-free: counted in the gcse window
                       above */
                        stageAnimDebugHook();
                        stageAnimCount++;
                        if (stageAnimCount >= 88) {
                            /* "stgBgas has %d, over MAX_ANIM_KIND %d" */
                            debug_StdPrintfDummy("stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n",
                                                 stageAnimCount, 87);
                            /* "too many BgAnimation kinds in one stage" */
                            debug_StdPrintfDummy("1ステージ中の BgAnimation の種類が多すぎます\n");
                            debug_assert(__FILE__, 702);
                            __assert(__FILE__, 702, "0");
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
            debug_assert(__FILE__, 712);
            __assert(__FILE__, 712, "0");
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
                a = ((char **)*(int *)(e->entry2 + 0x10))[k++];
                if (a == 0) {
                    break;
                }
                r = (char *)e->entry1;
                no = -1;
                if (r != 0) {
                    no = (r - (char *)stageTable) / 0x5CU;
                }
                bga_ApplyDObject(a, e->obj, e->flags.b.count, no);
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
                STG_SUB(e->obj[k])->nodeMtx = (int)iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 6, __FILE__, 761);
                STG_SUB(e->obj[k])->nodeQuat = (int)iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum << 4, __FILE__, 761);
                /* The reallocation block's own count line (`X->8 = N;`, as
                   chain.c, boy.c and box.c spell the same block), here passed
                   the count field itself (listing 762; all three allocations
                   pass line 761, one macro invocation). reload_cse deletes it
                   as a no-op and turns the 0x870 test's load into the ROM's
                   register copy. */
                STG_SUB(e->obj[k])->nodeNum = STG_SUB(e->obj[k])->nodeNum;
                if ((int)STG_SUB(e->obj[k])->nodes != 0) {
                    iosFree((void *)((int)STG_SUB(e->obj[k])->nodes & 0x0FFFFFFF));
                }
                STG_SUB(e->obj[k])->nodes = iosMallocDebug(
                    ios_partition_seki, STG_SUB(e->obj[k])->nodeNum * 80, __FILE__, 761);
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
                static const StageGObjInit stageGObjArg = /* derived name */
                    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 1};

                g = e->obj[k];
                arg = stageGObjArg;
                tbl2 = objKindData + *(int *)((char *)e->data[k] + 4) * 100;
                fn = *(int (**)(GObj *, StageGObjInit *))(tbl2 + 0x58);
                if (fn != 0) {
                    STG_SUB(e->obj[k])->work = (void *)fn(g, &arg);
                }
                isysGObjProcAdd(g, *(int *)(tbl2 + 0x5C), 1, 0x16);
                isysGObjProcAdd(g, *(int *)(tbl2 + 0x50), 1, 0x17);
                isysGObjProcAdd(g, *(int *)(tbl2 + 0x4C), 1, 0x18);
                isysGObjLinkObjDL(g, 0, 0, 7, 0xFFFFFFFF);
                g->active = 1;
                STG_SUB(e->obj[k])->disp = 0;
            }
        }
    }
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (e->entry1[0x50 / 4] != 0) {
            stage_SetAnimation(e->entry1[0x58 / 4], 1, 0);
        }
    }
    return stageAnimCount;
}

void stage_SetAnimation(int key, int p1, int p2)
{
    int uid = -1;
    int i;
    int k;
    int dbg = 0; /* local debug switch, see the test in case 0 below */
    StageAnim *e;

    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key != e->entry1[0x58 / 4]) {
            continue;
        }
        switch (e->flags.i >> 30) {
        case 0:
            uid = *(int *)(e->entry2 + 4);
            /* Local debug switch, off. What the bytes pin: the ROM's .rodata
               keeps "Illegal Group No. %d\n" at 0x550190 with no reference
               anywhere in the ROM, between stage_Init's data and
               stage_CheckAnimationFinish's string, so a print of it stood in
               this function and the optimizer deleted it; and the ROM's
               allocation needs gcse to see a count outside 96 to 99 insns here
               (106 with this block, 97 without, whose expression table of 49
               buckets puts the flags word's PRE register ahead of the object
               table's and rotates $7/$8/$9). A switch set
               to 0 outside the loop does both: cse cannot carry the constant
               across the loop label, gcse's last constant propagation folds
               the test and the next jump pass deletes the call. The listing
               leaves rows 847 to 852 code-free around the group number read.
               What the bytes cannot pin: the switch's name, the test's exact
               form and which value the line printed. */
            if (dbg) {
                debug_StdPrintfDummy("Illegal Group No. %d\n", uid);
            }
            bga_SetFrame(e->entry2, p2, p1, e->entry1[0x50 / 4]);
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
                e->obj[k]->dobj->disp = 1;
            }
            break;
        case 1:
            bga_SetCamFrame(e->entry3, p2, p1, e->entry1[0x50 / 4]);
            break;
        }
        break;
    }

    if (uid != -1) {
        for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
            if ((e->flags.i >> 30) != 0) {
                continue;
            }
            if (uid != *(int *)(e->entry2 + 4) || key == e->entry1[0x58 / 4]) {
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

inline int stage_CheckAnimationFinish(int a0)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        int *entry1 = e->entry1;
        if (a0 == entry1[0x58 / 4]) {
            int mode = e->flags.i >> 30;
            switch (mode) {
            case 0:
                return bga_CheckAnimationFinish(e->entry2);
            case 1:
                return bga_CheckSdfCameraFinish(e->entry3);
            }
        }
    }
    debug_StdPrintfDummy("stage_CheckAnimationFinish:illegal Animation No.\n");
    debug_assert(__FILE__, 909);
    __assert(__FILE__, 909, "0");
    return 0;
}

int stage_ContinueAnimation(int a0, int a1)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        int *entry1 = e->entry1;
        if (a0 == entry1[0x58 / 4]) {
            int mode = e->flags.i >> 30;
            switch (mode) {
            case 0:
                if (bga_CheckAnimationFinish(e->entry2) != 0) {
                    stage_SetAnimation(a0, 0, -1);
                    stage_SetAnimation(a1, 1, 0);
                    return 1;
                }
                return 0;
            case 1:
                if (bga_CheckSdfCameraFinish(e->entry3) == 0) {
                    return 0;
                }
                stage_SetAnimation(a0, 0, -1);
                stage_SetAnimation(a1, 1, 0);
                return 1;
            }
        }
    }
    debug_StdPrintfDummy("stage_ContinueAnimation:illegal Animation No.\n");
    debug_assert(__FILE__, 954);
    __assert(__FILE__, 954, "0");
    return 0;
}

inline int stage_CheckAnimationFrame(int a0, int a1, int a2)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        int *entry1 = e->entry1;
        if (a0 == entry1[0x58 / 4]) {
            int mode = e->flags.i >> 30;
            switch (mode) {
            case 0:
                return bga_CheckAnimationFrame(e->entry2, a1, a2);
            case 1:
                return bga_CheckSdfCameraFrame(e->entry3, a1, a2);
            }
        }
    }
    return -1;
}

inline int stage_CheckAnimationFrameIn(int a0, int a1, int a2)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        int *entry1 = e->entry1;
        if (a0 == entry1[0x58 / 4]) {
            int mode = e->flags.i >> 30;
            switch (mode) {
            case 0:
                return bga_CheckAnimationFrameIn(e->entry2, a1, a2);
            case 1:
                return bga_CheckSdfCameraFrameIn(e->entry3, a1, a2);
            }
        }
    }
    return -1;
}

void stage_ResetAnimation(void)
{
    bga_ResetAnimation();
    if (systemStatus[5] != 0)
        return;
    light_KillAllFixLight();
}

void stage_CalcAnimationNoParent(void)
{
    int i;
    StageAnim *e;

    if (graphics_ready != 0) {
        return;
    }
    if (stageAnimCount == 0) {
        return;
    }
    bga_SetUniqAnimationFlag(1);
    _InitCurrentMatrix();
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        switch (e->flags.i >> 30) {
        case 0: {
            char *entry2 = e->entry2;
            signed char lock = *(signed char *)(entry2 + 0xB);

            if (lock == 0) {
                if (*(int *)(*(char **)(entry2 + 0x24) + 0x20) != 0) {
                    continue;
                }
            }
            if (systemStatus[0x14 / 4] != 0) {
                continue;
            }
            switch (*(signed char *)(entry2 + 0xA)) {
            case -1: {
                int k;

                for (k = 0; k < e->flags.b.count; k++) {
                    char *objs = (char *)e->obj;
                    char *o = *(char **)(objs + (k << 2));

                    GOBJ_SUB(o)->disp = 0;
                    if (GOBJ_SUB(o)->nodeNum != 0) {
                        *(int *)((int *)*(int *)(o + 0x15C))[0xC / 4] = 0;
                    }
                }
                break;
            }
            case 0:
                break;
            case 1:
                if (lock != 0) {
                    if (debug_font_flag & 1) {
                        debug_Printf(0, ScreenHeight / 2 - 28, 0xCCCCCC00,
                                     "\033[32mCamera LWS : %s\033[0m\n", e->entry1);
                    }
                }
                _InitCurrentMatrix();
                bga_CalcAnimation(e->entry2, e->entry1[0x50 / 4], 0);
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
            bga_CalcSdfCamera(e->entry3, e->entry1[0x50 / 4]);
            break;
        }
    }
    bga_SetUniqAnimationFlag(0);
}

void stage_CalcAnimationParent(void)
{
    int i;
    StageAnim *e;
    char *entry2;

    if (graphics_ready != 0) {
        return;
    }
    if (stageAnimCount == 0) {
        return;
    }
    bga_SetUniqAnimationFlag(1);
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        entry2 = e->entry2;
        if (*(signed char *)(entry2 + 0xB) != 0) {
            continue;
        }
        if (*(int *)(*(char **)(entry2 + 0x24) + 0x20) == 0) {
            continue;
        }
        if (systemStatus[0x14 / 4] != 0) {
            continue;
        }
        switch (*(signed char *)(entry2 + 0xA)) {
        case -1: {
            int k;

            for (k = 0; k < e->flags.b.count; k++) {
                char *objs = (char *)e->obj;
                char *o = *(char **)(objs + (k << 2));
                GOBJ_SUB(o)->disp = 0;
                if (GOBJ_SUB(o)->nodeNum != 0) {
                    *(int *)((int *)*(int *)(o + 0x15C))[0xC / 4] = 0;
                }
            }
            break;
        }
        case 1:
            _InitCurrentMatrix();
            bga_CalcAnimation(e->entry2, e->entry1[0x50 / 4], 0);
            break;
        case 0:
            _InitCurrentMatrix();
            bga_CalcAnimation(e->entry2, e->entry1[0x50 / 4], 1);
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
        int *entry1 = e->entry1;
        signed char lv;
        int k;

        if (entry1[0x58 / 4] == 0x42) {
            continue;
        }
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        lv = *(signed char *)(e->entry2 + 0xA);
        if (lv == -1) {
            continue;
        }
        if (lv < -1) {
            continue;
        }
        if (lv >= 2) {
            continue;
        }
        for (k = 0; k < e->flags.b.count; k++) {
            char *objs = (char *)e->obj;
            Sub15C *d = ((GObj *)*(char **)(objs + (k << 2)))->dobj;

            if (d->disp != 0) {
                reg_DispObj(d);
            }
        }
    }
    bga_DispLightning();
}

inline void stage_SetLoopFlag(int key, int a1)
{
    int count = *(volatile int *)&stageAnimCount;
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < count; i++, e++) {
        int *p = e->entry1;
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = a1;
            p = &(*((volatile int *)(&stageAnimCount)));
            count = *p;
        }
    }
}

inline void stage_SetFrameStep(int target, int val)
{
    int n = stageAnimCount;
    char *p = (char *)stageAnimTable;
    int i;
    if (n <= 0)
        return;
    i = n;
    do {
        int *entry1 = *(int **)(p + 0x280);
        if (target == entry1[0x58 / 4]) {
            int *entry2 = *(int **)(p + 0x284);
            *(float *)((char *)entry2 + 0x1C) = (float)val;
        }
        p += 0x290;
    } while (--i);
}

inline void stage_SetParentOfGObj(int a0, void *a1)
{
    int i;
    int one = 1;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++) {
        if (a0 == e->entry1[0x58 / 4]) {
            *(struct B8 *)(*(char **)(e->entry2 + 0x24) + 0x20) = *(struct B8 *)a1;
            *(int *)(*(char **)(e->entry2 + 0x24) + 0x28) = one;
        }
        e++;
    }
}

inline void stage_SetParentOfGObjWithLocalRotationFlag(int a0, void *a1, int a2)
{
    int i;
    StageAnim *e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++) {
        if (a0 == e->entry1[0x58 / 4]) {
            *(Blob8 *)(*(char **)(e->entry2 + 0x24) + 0x20) = *(Blob8 *)a1;
            *(int *)(*(char **)(e->entry2 + 0x24) + 0x28) = a2;
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
        int *entry1 = e->entry1;
        if (key == entry1[0x58 / 4]) {
            char *entry2;
            char *target;
            entry2 = e->entry2;
            target = *(char **)(entry2 + 0x24);
            _CopyVector(target, pos);
            entry2 = e->entry2;
            target = *(char **)(entry2 + 0x24);
            CopyQuaternion(target + 0x10, rot);
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
        if (key == e->entry1[0x58 / 4]) {
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

float stage_PlayBgAnimation(int key, float t, void *v, void *q)
{
    int i;
    int k;
    int n = stageAnimCount;
    float r = t;
    float f;
    StageAnim *e;

    if (n == 0) {
        return 0.0f;
    }
    e = stageAnimTable;
    for (i = 0; i < n; i++, e++) {
        if (key != e->entry1[0x58 / 4]) {
            continue;
        }
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        _CopyVector(*(void **)(e->entry2 + 0x24), v);
        CopyQuaternion(*(char **)(e->entry2 + 0x24) + 0x10, q);
        bga_SetFrame(e->entry2, (int)r, 1, e->entry1[0x50 / 4]);
        for (k = 0; k < e->flags.b.count; k++) {
            char *objs = (char *)e->obj;

            *(int *)(*(int *)(*(char **)(objs + (k << 2)) + 0x15C) + 0x74) = 1;
        }
        if (systemStatus[0x14 / 4] != 0) {
            break;
        }
        f = *(float *)(e->entry2 + 0x1C);
        if (systemStatus[0] != 0) {
            r = t + f * 1.2075409f;
        } else {
            r = t + f;
        }
        if (*(float *)(e->entry2 + 0x18) <= r) {
            r = e->entry1[0x50 / 4] != 0 ? *(float *)(e->entry2 + 0x14) : -1.0f;
        }
        break;
    }
    e = stageAnimTable;
    for (i = 0; i < stageAnimCount; i++, e++) {
        if (key != e->entry1[0x58 / 4]) {
            continue;
        }
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        for (k = 0; k < e->flags.b.count; k++) {
            char *objs = (char *)e->obj;
            Sub15C *d = ((GObj *)*(char **)(objs + (k << 2)))->dobj;

            reg_DispObj(d);
            d->disp = 0;
        }
        *(signed char *)(e->entry2 + 0xA) = -1;
    }
    return r;
}

/* This TU's .lit4 holds 1.2075409f twice, one word per owner and no
   deduplication: stage_PlayBgAnimation's literal above is the first, and
   this function's own is the second. */
float stage_PlayBgAnimationDissolve(int key, void *v, void *q, float t, float dv)
{
    int i;
    int k;
    int m;
    float r = t;
    float f;
    StageAnim *e;

    if (stageAnimCount == 0) {
        return 0.0f;
    }
    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key != e->entry1[0x58 / 4]) {
            continue;
        }
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        _CopyVector(*(void **)(e->entry2 + 0x24), v);
        CopyQuaternion(*(char **)(e->entry2 + 0x24) + 0x10, q);
        bga_SetFrame(e->entry2, (int)r, 1, e->entry1[0x50 / 4]);
        for (k = 0; k < e->flags.b.count; k++) {
            e->obj[k]->dobj->disp = 1;
        }
        if (systemStatus[0x14 / 4] != 0) {
            break;
        }
        f = *(float *)(e->entry2 + 0x1C);
        if (systemStatus[0] != 0) {
            r = t + f * 1.2075409f;
        } else {
            r = t + f;
        }
        if (*(float *)(e->entry2 + 0x18) <= r) {
            r = e->entry1[0x50 / 4] != 0 ? *(float *)(e->entry2 + 0x14) : -1.0f;
        }
        break;
    }
    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key != e->entry1[0x58 / 4]) {
            continue;
        }
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        stageAnimDebugHook();
        for (k = 0; k < e->flags.b.count; k++) {
            Sub15C *d = e->obj[k]->dobj;

            for (m = 0; m < d->nodeNum; m++) {
                d->nodes[m].alpha = dv;
            }
            reg_DispObj(d);
            d->disp = 0;
            stageAnimDebugHook();
        }
        stageAnimDebugHook();
        *(signed char *)(e->entry2 + 0xA) = -1;
    }
    return r;
}

int *stage_MakePlayBgAnimation(int key)
{
    int i;
    int found = -1;
    float f = 1.0f;
    short num = 0;
    StageAnim *e = stageAnimTable;
    int *p;

    for (i = 0; i < stageAnimCount; i++, e++) {
        int *entry1 = e->entry1;

        if (key == entry1[0x58 / 4]) {
            found = i;
            {
                int w = e->flags.i;

                int t = (w << 2) >> 22;

                e->flags.i = (w & 0xC00FFFFF) | (((t + 1) & 0x3FF) << 20);
                num = (short)t;
            }
            f = ((AnimWord *)(e->entry2 + 0x14))->f;
            break;
        }
    }

    if (found == -1) {
        /* "the given ID does not exist, or its animation is not loaded" */
        debug_StdPrintfDummy("指定したIDが存在しないか、アニメーションが読み込まれていません.\n");
        return 0;
    }

    p = (int *)iosMallocDebug(ios_partition_seki, 0x40, __FILE__, 1494);
    if (p == 0) {
        /* "cannot allocate memory for the stage segment (heap exhausted)" */
        debug_StdPrintfDummy("ステージセグメントにメモリが確保できません.(ヒープメモリ不足)\n");
        return 0;
    }

    ((PlayWord *)p)->l = ((((PlayWord *)p)->l & ~0x3FFF) | (key & 0x3FFF) | 0x4000) & ~0x8000;
    ((PlayWord *)((char *)p + 2))->h = num;
    *(float *)((char *)p + 4) = f;
    *(float *)((char *)p + 8) = 1.0f;
    *(float *)((char *)p + 0xC) = 1.0f;
    if (bgaPlayList != 0) {
        bgaPlayList[0x10 / 4] = (int)p;
    }
    p[0x10 / 4] = 0;
    p[0x14 / 4] = (int)bgaPlayList;
    bgaPlayList = p;
    return p;
}

void stage_KillPlayBgAnimation(int **self)
{
    int *node = *self;
    int *next;
    int *prev;
    if (node == 0)
        return;
    next = (int *)node[0x10 / 4];
    if (next != 0) {
        next[0x14 / 4] = node[0x14 / 4];
    } else {
        bgaPlayList = (int *)node[0x14 / 4];
        node = *self;
    }
    prev = (int *)node[0x14 / 4];
    if (prev != 0) {
        prev[0x10 / 4] = node[0x10 / 4];
    }
    if (bgaPlayList != 0) {
        bgaPlayList[0x10 / 4] = 0;
    }
    freeseki(*self);
}

inline void stage_KillPlayBgAnimationIfOverMaxCount(int a0, int a1)
{
    AnimNode *p = (AnimNode *)bgaPlayList;
    int count = 0;
    while (p != 0) {
        long v = p->field0;
        if ((((unsigned short)v << 18) >> 18) == a0) {
            if (!(v & 0x8000)) {
                count++;
                if (a1 < count) {
                    p->field0 = v | 0x8000;
                }
            }
        }
        p = p->next;
    }
}

/* File-static helper the January listing shows at src/StageAnimation.c:1588-1592,
 * inlined twice in stage_DispBgAnimation and twice in stage_DispBgAnimationNoFinish.
 * It has no symbol in MAIN.MAP and no census row: INTERIM, the name below is
 * ours, not the developer's. */
static inline void stage_SetBgAnimationPlayNode(BgaPlayNode *node, int key)
{
    int i;
    int k;
    StageAnim *e;

    for (i = 0, e = stageAnimTable; i < stageAnimCount; i++, e++) {
        if (key == e->entry1[0x58 / 4]) {
            if ((e->flags.i >> 30) == 0) {
                for (k = 0; k < e->flags.b.count; k++) {
                    *(void **)(*(char **)&e->obj[k]->dobj + 0x850) = node;
                }
            }
        }
    }
}

int stage_DispBgAnimation(void *p)
{
    BgaPlayNode **self = (BgaPlayNode **)p;

    if (*self == 0) {
        return -1;
    }
    if ((*self)->kill) {
        stage_KillPlayBgAnimation((int **)self);
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
        stage_KillPlayBgAnimation((int **)self);
        *self = 0;
        return -1;
    }
    return 0;
}

int stage_DispBgAnimationNoFinish(char **slot)
{
    BgaPlayNode **self = (BgaPlayNode **)slot;
    int i;
    StageAnim *e;

    if (*self == 0) {
        return -1;
    }
    if ((*self)->kill) {
        stage_KillPlayBgAnimation((int **)self);
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
            if ((*self)->no == e->entry1[0x58 / 4]) {
                if ((e->flags.i >> 30) == 0) {
                    /* A jump to the function's exit, the way Light.c leaves
                       its loops (goto found): the ROM keeps this store in a
                       block loop.c moved out of the loop, with the key and
                       the bound hoisted, and jumps to the shared `return 0`.
                       A break (the loop's own exit label) is rolled into the
                       loop's exit test by stmt.c's expand_end_loop, which
                       jump then duplicates into a second loop entry; a
                       return gets its own $2 = 0 before the store. The bytes
                       pin the target, not the label's name. */
                    (*self)->frame = *(float *)(e->entry2 + 0x18);
                    goto end;
                }
            }
        }
    }
end:
    return 0;
}

void stage_SetCameraForceOff(int a0, int a1, int a2, int a3)
{
    bga_SetCameraForceOff();
}
