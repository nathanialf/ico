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

void InitStageMultiBgaManager(void)
{
    int i;

    for (i = 0; i < 30; i++) {
        stageBga[i] = *(BgaDisp *)&InitialBgaMultiAnimeState;
        stageBgaAnim[i] = 0;
    }
    stageBgaCount = 0;
}

void EntryStageMultiBgaManager(int kind, void *pos, void *rot)
{
    stageBgaAnim[stageBgaCount] = stage_MakePlayBgAnimation(kind);
    _CopyVector(stageBgaAnim[stageBgaCount]->pos, pos);
    CopyQuaternion(stageBgaAnim[stageBgaCount]->rot, rot);
    EntryMultiBgaManager(stageBga, stageBgaCount++, kind, pos, rot);
    if (stageBgaCount >= 30) {
        stageBgaCount = 0;
    }
}

void EntryStageMultiBgaManagerSensitive(int kind, void *pos, void *rot, void *vel)
{
    stageBgaAnim[stageBgaCount] = stage_MakePlayBgAnimation(kind);
    _CopyVector(stageBgaAnim[stageBgaCount]->pos, pos);
    CopyQuaternion(stageBgaAnim[stageBgaCount]->rot, rot);
    EntryMultiBgaManagerSensitive(stageBga, stageBgaCount++, kind, pos, rot, vel);
    if (stageBgaCount >= 30) {
        stageBgaCount = 0;
    }
}

void DispStageMultiBgaManager(void)
{
    int i;

    for (i = 0; i < 30; i++) {
        if (stageBgaAnim[i] == 0) {
            continue;
        }
        if (stage_DispBgAnimation(&stageBgaAnim[i])) {
            stageBgaAnim[i] = 0;
            continue;
        }
        _AddVector(stageBgaAnim[i]->pos, stageBgaAnim[i]->pos, stageBga[i].vel);
    }
}
