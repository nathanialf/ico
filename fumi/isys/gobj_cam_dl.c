#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_cam_dl", cut_gobj_camera_dl_link);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_cam_dl", isysGObjRemoveCameraDL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_cam_dl", func_001F8E08);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_cam_dl", isysGObjMoveCameraDL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_cam_dl", isysGObjLinkCameraDL);

extern int D_0062A4D4;
extern int D_0062A4D8;

void isysGObjLinkCameraDLAfterGObj(void) {
    D_0062A4D4 = 0;
    D_0062A4D8 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_cam_dl", isysGObjLinkCameraDLBeforeGObj);
