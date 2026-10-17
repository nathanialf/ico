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

typedef struct AnimNode { /* field names derived */
    long bits;            /* 0x00 */
    char pad08[12];
    struct AnimNode *next; /* 0x14 */
} AnimNode;                /* derived name */

/* The 0x298-byte animation record stageAnimTable holds: the kind, object and
   data tables, a word this build's code never touches, the three entry
   pointers and three halfwords (the stubs read 0x290 as the object count and
   write 0x292 and 0x294) where PAL's 0x290-byte record packs one count/mode
   word. */
typedef struct {          /* field names derived */
    short kind[64];       /* 0x000 */
    GObj *obj[64];        /* 0x080 */
    int *data[64];        /* 0x180 */
    int word280;          /* 0x280 */
    StageAnimDef *entry1; /* 0x284 */
    BgaHeader *entry2;    /* 0x288 */
    char *entry3;         /* 0x28C */
    short count;          /* 0x290 */
    short half292;        /* 0x292 */
    short half294;        /* 0x294 */
    short pad296;         /* 0x296 */
} StageAnim;              /* derived name */

/* The number of loaded animation records, the head and tail of the
   play-node list (stage_Init clears both, stage_MakePlayBgAnimation and
   stage_KillPlayBgAnimation keep them), the running work offset
   stage_PlayBgAnimation advances per node, and the record table stage_Init
   fills, 80 records of 0x298 bytes (the stubs walk it at that stride). */
static int stageAnimCount; /* derived name */

static BgaPlayNode *bgaPlayList; /* derived name */

static BgaPlayNode *bgaPlayTail; /* derived name */

static int bgaWorkOffset; /* derived name */

static StageAnim stageAnimTable[80]; /* derived name */

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

INCLUDE_ASM(stage_SetAnimation);

INCLUDE_ASM_LIT(stage_CheckAnimationFinish);

INCLUDE_ASM(stage_ContinueAnimation);

INCLUDE_ASM(stage_CalcAnimationNoParent);

INCLUDE_ASM(stage_CalcAnimationParent);

INCLUDE_ASM(stage_DispAnimation);

INCLUDE_ASM(stage_PlayBgAnimation);

INCLUDE_ASM(stage_PlayBgAnimationDissolve);

INCLUDE_ASM(stage_MakePlayBgAnimation);

INCLUDE_ASM(stage_KillPlayBgAnimation);

/* PAL's play-node setter (inlined into stage_DispBgAnimation and
   stage_DispBgAnimationNoFinish) has no copy here: its callers are stubbed and
   it read PAL's packed record word. */

INCLUDE_ASM(stage_DispBgAnimation);

INCLUDE_ASM(stage_CheckAnimationFinish);

INCLUDE_ASM(stage_CheckAnimationFrame);

INCLUDE_ASM(stage_SetLoopFlag);

INCLUDE_ASM(stage_SetFrameStep);

INCLUDE_ASM(stage_SetParentOfGObj);

INCLUDE_ASM(stage_SetLocalizeGeometry);

INCLUDE_ASM(stage_SetScale);

INCLUDE_ASM(stage_CheckAnimationFrameIn);
