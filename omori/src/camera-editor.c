#include "common.h"

extern int D_00286A98[];

void EnterMenu(void) {
    D_00286A98[0] = 1;
}

extern int D_00286A98[];

void saveEditedDataBinary(void) {
    D_00286A98[0] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", saveEditedData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", gif_test);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", DebugDispBox);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", DispCameraGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", drawXZArrow);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", DispAxisArrow);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", dispCameraPinType2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_DispPinType2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", dispCameraGroupType2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", dispBox);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_DispBoxType2_Plane);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_DispBoxType2);

extern void CameraEdit_DispBoxType2(int a0, int a1, int a2, int a3);

void menuGroupSelect(int a0, int a1, int a2) {
    CameraEdit_DispBoxType2(a0, a1, a1 + 1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", menuGroupEdit);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", menuPinSelect);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", menuPinEdit);

extern void menuGroupEdit(int a0, int a1);

void wakeup_cameraedit(int a0, int a1) {
    menuGroupEdit(a0, a1 & 0xFF);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", test_camedit);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", _CameraEdit_del_box);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", _CameraEdit_del_pin);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_add_box);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_add_pin);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_del_box);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_del_pin);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_DispBox);

extern void dispCameraGroupType2(int a0, unsigned char a1);

void CameraEdit_Reflect(int a0, unsigned char a1) {
    dispCameraGroupType2(a0, a1);
}

extern int *D_0062A8F0;
extern void func_00186CA8(int a0, int a1);

void CameraEdit_Save(void) {
    int *p = D_0062A8F0;
    func_00186CA8(p[1], p[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", debug_NMarker);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", debug_Marker);

void debug_Arrow(void) {
}

void InitCameraEditor(void) {
}

extern int D_0062A9B0;
extern unsigned char D_0062A9B8;

void debug_CameraEditor(void) {
    D_0062A9B0 = 0;
    D_0062A9B8 = 0;
}
