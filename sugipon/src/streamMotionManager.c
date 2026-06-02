#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _infoUpdate);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", PlayStreamMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", ClearStreamMotionEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _deleteStreamMotionManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", GetStreamMotionData);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _transRingBuf);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", ExecStreamMotionManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", StandbyStreamMotion);

void StopStreamMotion(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", DeleteStreamMotionManager);
