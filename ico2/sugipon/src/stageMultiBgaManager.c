#include "StageAnimation.h"
#include "multiBgaManager.h"
#include "quaternion.h"
#include "Matrix.h"
#include "main.h"

/* the thirty multi-BGA slots and the animation each one is playing */
static BgaDisp stageBga[30]; /* derived name */

static BgaPlayNode *stageBgaAnim[30]; /* derived name */

/* the number of stage animations entered */
static int stageBgaCount = 0; /* derived name */

#include "stageMultiBgaManager.h"
#include "include_asm.h"

inline void EntryStageMultiBgaManagerWithStay(int kind, void *pos, void *rot, int stay);

inline void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot, void *vel,
                                                       int stay);

INCLUDE_ASM(InitStageMultiBgaManager);

INCLUDE_ASM(EntryStageMultiBgaManager);

INCLUDE_ASM(EntryStageMultiBgaManagerSensitive);

INCLUDE_ASM(DispStageMultiBgaManager);
