#include "debug.h"
#include "sceneManager.h"
#include "memory.h"
#include "act.h"
#include "boyact.h"
#include "mail-add-data.h"
#include "Matrix.h"
#include "Primitive.h"
#include "frameDependSequence.h"
#include "matrixDrive.h"
#include "weapon.h"
#include <libvu0.h>

/* the colour the debug display draws a boundary sphere in */
static unsigned int acbSphereColor[4] = {0, 128, 255, 128}; /* derived name */

#include "attackCheckBoundary.h"
#include "ios.h"
#include "main.h"
#include "GifPacket.h"
#include "include_asm.h"

static inline GObj *createAttackCheckBoundaryGObj(SObjSimpleSetting *lay) /* derived name */
{
    return CreateLayoutedGObj(63, 75, -1, 0, lay, -1, 7, 1);
}

/* The 12-byte work record this function allocates and the other members
   reach through the sub-object's 0x830: 0x4 is the hit flag AttackCheckBoundaryDL
   tests and the manager reads back and clears, 0x8 the attribute SetAttackCheckBoundaryAttribute stores, and 0x0
   the caller's int that CreateAttackCheckBoundary passed in the layout's
   handle, cleared again through it here. */
typedef struct { /* field names derived */
    int *handle; /* 0x0 */
    int hit;     /* 0x4 */
    int attr;    /* 0x8 */
} AcbWork;       /* derived name */

INCLUDE_ASM_LIT(InitAttackCheckBoundaryGeo);

INCLUDE_ASM(AttackCheckBoundaryBeforeFunc);

/* the manager's 8-byte roster entries and its work block at sub+0x830 */
typedef struct AcbEntry { /* field names derived */
    int obj;              /* 0x00, the boundary object, kept as a word */
    int hit;              /* 0x04 */
} AcbEntry;               /* derived name */

typedef struct AcbMgr { /* field names derived */
    int count;          /* 0x00 */
    int cur;            /* 0x04 */
    int prev;           /* 0x08 */
    AcbEntry *list;     /* 0x0C */
} AcbMgr;               /* derived name */

/* the blank roster entry each slot starts from */
static AcbEntry acbBlankEntry = {0, 0}; /* derived name */

INCLUDE_ASM(InitAttackCheckBoundaryManagerGeo);

INCLUDE_ASM(AttackCheckBoundaryManagerGeo);

void AttackCheckBoundaryManagerDL(void) {}

INCLUDE_ASM(InitAttackCheckBoundaryGeo);

INCLUDE_ASM(AttackCheckBoundaryGeo);

INCLUDE_ASM(AttackCheckBoundaryDL);

INCLUDE_ASM(actAttackCheckBoundaryStart);

INCLUDE_ASM(GetAttackCheckBoundaryRadius);

INCLUDE_ASM(CreateAttackCheckBoundary);

INCLUDE_ASM(GetAttackCheckBoundaryManagerStatus);

INCLUDE_ASM(SetAttackCheckBoundaryAttribute);
