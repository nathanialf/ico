#include "StageAnimation.h"
#include "multiBgaManager.h"
#include "quaternion.h"
#include "Matrix.h"
#include "main.h"

/* .bss, owned by stageMultiBgaManager.o and reached only from this file
   (MAIN.MAP names no symbol in the run), in the ROM's run order: the thirty
   multi-BGA slots and the animation each one is playing. */
static MultiBga stageBga[30];

static char *stageBgaAnim[30];

/* the TU's one .sdata word (MAIN.MAP stageMultiBgaManager.o .sdata 0x4, no
   symbol): the number of stage animations entered */
static int stageBgaCount = 0; /* derived name */

extern void EntryMultiBgaManagerSensitive(MultiBga *bga, int no, int kind, void *pos, void *rot,
                                          int sensitive);

#include "stageMultiBgaManager.h"

void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot, int sensitive,
                                                int stay);

inline void InitStageMultiBgaManager(void)
{
    int i;

    for (i = 0; i < 30; i++) {
        stageBga[i] = *(MultiBga *)&InitialBgaMultiAnimeState;
        stageBgaAnim[i] = 0;
    }
    stageBgaCount = 0;
}

inline void EntryStageMultiBgaManagerWithStay(int kind, void *pos, void *rot, int stay)
{
    stageBgaAnim[stageBgaCount] = stage_MakePlayBgAnimation(kind);
    _CopyVector(stageBgaAnim[stageBgaCount] + 0x20, pos);
    CopyQuaternion(stageBgaAnim[stageBgaCount] + 0x30, rot);
    EntryMultiBgaManager(stageBga, stageBgaCount++, kind, pos, rot);
    stageBga[stageBgaCount - 1].stay = stay;
    if (stageBgaCount >= 30) {
        stageBgaCount = 0;
    }
}

inline void EntryStageMultiBgaManager(int kind, void *pos, void *rot)
{
    EntryStageMultiBgaManagerWithStay(kind, pos, rot, 0);
}

inline void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot,
                                                       int sensitive, int stay)
{
    stageBgaAnim[stageBgaCount] = stage_MakePlayBgAnimation(kind);
    _CopyVector(stageBgaAnim[stageBgaCount] + 0x20, pos);
    CopyQuaternion(stageBgaAnim[stageBgaCount] + 0x30, rot);
    EntryMultiBgaManagerSensitive(stageBga, stageBgaCount++, kind, pos, rot, sensitive);
    stageBga[stageBgaCount - 1].stay = stay;
    if (stageBgaCount >= 30) {
        stageBgaCount = 0;
    }
}

inline void EntryStageMultiBgaManagerSensitive(int kind, void *pos, void *rot, int sensitive)
{
    EntryStageMultiBgaManagerSensitiveWithStay(kind, pos, rot, sensitive, 0);
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
            _AddVector(stageBgaAnim[i] + 0x20, stageBgaAnim[i] + 0x20, &stageBga[i].w[4]);
        }
    }
}
