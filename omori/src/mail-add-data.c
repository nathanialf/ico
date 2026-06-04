#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", InitMailAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", ActSendMail_WithAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", GetMailAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", ClearMailAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_00192628);

extern float D_006CCE30[];

void func_001926A8(float a0, float a1) {
    D_006CCE30[5] = a0;
    D_006CCE30[6] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001926C0);

extern void func_001929A0(void *a0);

void func_001927E8(int **a0, int a1) {
    int *p = a0[0x59];
    p[0x19D] = a1;
    func_001929A0(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001927F8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001928F8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001929A0);

extern void gif_SpriteOffset(int a0);
extern void gsb_SetFrame(int a0, int a1, int a2);

void func_00192A08(void) {
    gif_SpriteOffset(0xB);
    gsb_SetFrame(1, 2, 0x40);
}

extern void func_0010F9D0(void);

void func_00192A30(void) {
    func_0010F9D0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_00192A38);

extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern char D_00287300[];

void func_00192B50(void *a0) {
    MatrixDrive_TurnXObjectMatrixYZ(D_00287300, a0);
    gif_SpriteOffset(0xB);
}
