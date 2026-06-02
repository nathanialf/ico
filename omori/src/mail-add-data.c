#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", InitMailAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", ActSendMail_WithAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", GetMailAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", ClearMailAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_00192628);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001926A8);

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

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_00192A08);

extern void func_0010F9D0(void);

void func_00192A30(void) {
    func_0010F9D0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_00192A38);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_00192B50);
