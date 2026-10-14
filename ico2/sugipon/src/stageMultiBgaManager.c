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

inline void InitStageMultiBgaManager(void)
{
    int i;

    for (i = 0; i < 30; i++) {
        stageBga[i] = *(BgaDisp *)&InitialBgaMultiAnimeState;
        stageBgaAnim[i] = 0;
    }
    stageBgaCount = 0;
}

inline void EntryStageMultiBgaManager(int kind, void *pos, void *rot)
{
    EntryStageMultiBgaManagerWithStay(kind, pos, rot, 0);
}

inline void EntryStageMultiBgaManagerSensitive(int kind, void *pos, void *rot, void *vel)
{
    EntryStageMultiBgaManagerSensitiveWithStay(kind, pos, rot, vel, 0);
}

void DispStageMultiBgaManager(void)
{
    int i;

    for (i = 0; i < 30; i++) {
        if (stageBgaAnim[i] == 0) {
            continue;
        }
        if (stageBga[i].stay) {
            stage_DispBgAnimationNoFinish(&stageBgaAnim[i]);
        } else {
            if (stage_DispBgAnimation(&stageBgaAnim[i])) {
                stageBgaAnim[i] = 0;
                continue;
            }
        }
        if (systemStatus[5] == 0) {
            _AddVector(stageBgaAnim[i]->pos, stageBgaAnim[i]->pos, stageBga[i].vel);
        }
    }
}
