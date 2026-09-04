#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", InitMailAdditionalData);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", ActSendMail_WithAdditionalData);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", GetMailAdditionalData);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", ClearMailAdditionalData);
