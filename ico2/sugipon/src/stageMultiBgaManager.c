#include "common.h"
#include "StageAnimation.h"
#include "multiBgaManager.h"
#include "quaternion.h"

extern MultiBga D_004ECCA0;

/* .bss, owned by stageMultiBgaManager.o and reached only from this file
   (MAIN.MAP names no symbol in the run), in the ROM's run order: the thirty
   multi-BGA slots and the animation each one is playing. */
static MultiBga stageBga[30];

static char *stageBgaAnim[30];

extern int D_0063BB04;
/* kept local: this TU's uses of _CopyVector do not fit the prototype in Matrix.h */
extern void _CopyVector(void *dst, void *src);
extern int D_0028F4C0[];
/* kept local: this TU's uses of _AddVector do not fit the prototype in Matrix.h */
extern void _AddVector(void *dst, void *a, void *b);
extern void EntryMultiBgaManagerSensitive(MultiBga *bga, int no, int kind, void *pos, void *rot,
                                          int sensitive);

#include "stageMultiBgaManager.h"

void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot, int sensitive,
                                                int stay);

inline void InitStageMultiBgaManager(void)
{
    int i;

    for (i = 0; i < 30; i++) {
        stageBga[i] = D_004ECCA0;
        stageBgaAnim[i] = 0;
    }
    D_0063BB04 = 0;
}

inline void EntryStageMultiBgaManagerWithStay(int kind, void *pos, void *rot, int stay)
{
    stageBgaAnim[D_0063BB04] = stage_MakePlayBgAnimation(kind);
    _CopyVector(stageBgaAnim[D_0063BB04] + 0x20, pos);
    CopyQuaternion(stageBgaAnim[D_0063BB04] + 0x30, rot);
    EntryMultiBgaManager(stageBga, D_0063BB04++, kind, pos, rot);
    stageBga[D_0063BB04 - 1].stay = stay;
    if (D_0063BB04 >= 30) {
        D_0063BB04 = 0;
    }
}

inline void EntryStageMultiBgaManager(int kind, void *pos, void *rot)
{
    EntryStageMultiBgaManagerWithStay(kind, pos, rot, 0);
}

inline void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot,
                                                       int sensitive, int stay)
{
    stageBgaAnim[D_0063BB04] = stage_MakePlayBgAnimation(kind);
    _CopyVector(stageBgaAnim[D_0063BB04] + 0x20, pos);
    CopyQuaternion(stageBgaAnim[D_0063BB04] + 0x30, rot);
    EntryMultiBgaManagerSensitive(stageBga, D_0063BB04++, kind, pos, rot, sensitive);
    stageBga[D_0063BB04 - 1].stay = stay;
    if (D_0063BB04 >= 30) {
        D_0063BB04 = 0;
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
        if (D_0028F4C0[5] == 0) {
            _AddVector(stageBgaAnim[i] + 0x20, stageBgaAnim[i] + 0x20, &stageBga[i].w[4]);
        }
    }
}
