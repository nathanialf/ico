#include "common.h"




extern int D_006321D4;
extern int *D_006321D8;
extern char D_0061AC80[];
extern void debug_assertMessage();
extern void func_001FBFC8();
INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", cut_gobj_camera_dl_link);

void isysGObjRemoveCameraDL(int a0, int a1)
{
    func_001FBFC8(a0);
    return cut_gobj_camera_dl_link(a0, a1);
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", func_001FC1A0);

void isysGObjMoveCameraDL(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_assertMessage(D_0061AC80);
        return;
    }

    t1[0x13] = a2;
    t1[0x14] = a3;
    t1[0x12] = a1;
    *((unsigned char *)t1 + 0x40) = *((unsigned char *)t0 + 0x40);
    t1[0xE] = (int)t0;
    v34 = t0[0xD];
    v44 = t0[0x11];
    t1[0xD] = v34;
    t0[0xD] = (int)t1;
    t1[0x11] = v44;
    if (t1[0xD] == 0) {
        D_006321D8 = t1;
    }
}

void isysGObjLinkCameraDL(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_assertMessage(D_0061AC80);
        return;
    }

    t1[0x13] = a2;
    t1[0x14] = a3;
    t1[0x12] = a1;
    *((unsigned char *)t1 + 0x40) = *((unsigned char *)t0 + 0x40);
    t1[0xE] = (int)t0;
    v34 = t0[0xD];
    v44 = t0[0x11];
    t1[0xD] = v34;
    t0[0xD] = (int)t1;
    t1[0x11] = v44;
    if (t1[0xD] == 0) {
        D_006321D8 = t1;
    }
}

void isysGObjLinkCameraDLAfterGObj(void) {
    D_006321D4 = 0;
    D_006321D8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", isysGObjLinkCameraDLBeforeGObj);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", AdpcmStreamInit);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", adpcmTickProc2);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", adpcmDataSet);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", func_001FC520);

