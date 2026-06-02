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
