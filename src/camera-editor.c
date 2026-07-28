#include "common.h"




extern char D_006326D8;
extern int D_006326D0;
extern int ACTGameView_Init();
extern int D_0028A898[];
void EnterMenu(void) {
    D_0028A898[0] = 1;
}

void saveEditedDataBinary(void) {
    D_0028A898[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", saveEditedData);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", gif_test);

int DebugDispBox(int *a0, int *a1)
{
    if (((unsigned char *)a1)[0x19] != 0) {
        return 1;
    }
    return ACTGameView_Init(*a0, a1[0]) != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", DispCameraGroup);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", drawXZArrow);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", DispAxisArrow);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", dispCameraPinType2);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispPinType2);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", dispCameraGroupType2);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", dispBox);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispBoxType2_Plane);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispBoxType2);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", menuGroupSelect);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", menuGroupEdit);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", menuPinSelect);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", menuPinEdit);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", wakeup_cameraedit);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", test_camedit);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_00186978);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", _CameraEdit_del_box);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", _CameraEdit_del_pin);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_add_box);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_add_pin);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_del_box);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_del_pin);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispBox);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_Reflect);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_Save);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", debug_NMarker);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", debug_Marker);

void debug_Arrow(void) {}

void InitCameraEditor(void) {}

void debug_CameraEditor(void) {
    D_006326D0 = 0;
    D_006326D8 = 0;
}

