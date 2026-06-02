#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmInit);

extern void iosOmInit(void);

void _iosOmMain(void) {
    iosOmInit();
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmMain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmCreateDL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmExeEachGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmExeEachGObjAll);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmReturnExeEachGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmGetGObjStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmSearchGObjId);

void iosOmSearchGObjIdAll(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmBeforeFuncStandard);
