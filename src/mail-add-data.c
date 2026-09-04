#include "common.h"

extern void ClearMailAdditionalData(char *a0);
void InitMailAdditionalData(char *a0, int a1) {
    *(int *)(*(char **)(a0 + 0x164) + 0x684) = a1;
    ClearMailAdditionalData(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", ActSendMail_WithAdditionalData);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", GetMailAdditionalData);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", ClearMailAdditionalData);
