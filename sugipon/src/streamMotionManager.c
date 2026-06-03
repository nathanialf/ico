#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _infoUpdate);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", PlayStreamMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", ClearStreamMotionEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _deleteStreamMotionManager);

extern int D_0062B9EC;

void GetStreamMotionData(void) {
    D_0062B9EC = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _transRingBuf);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", ExecStreamMotionManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", StandbyStreamMotion);

void StopStreamMotion(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", DeleteStreamMotionManager);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
} S_00706DA8;  /* stride 0x18 */

/* end struct shapes */
