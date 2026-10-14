#include "typedef.h"
#include "obj_manager.h"
#include "debug_exception.h"
#include <assert.h>

/* Two static helpers, one sending the mail and returning its index or -1,
 * the other asserting the actor has a work block and returning its
 * additional-data table.  InitMailAdditionalData calls
 * ClearMailAdditionalData, which is defined after it. */

/* the entries a table holds; the name and current_count are the assert's */
#define MAIL_ADDITIONAL_DATA_MAX 10

typedef struct MailAddEntry { /* field names derived */
    /* 0x0 */ int mail;
    /* 0x4 */ void *data;
} MailAddEntry; /* derived name */

typedef struct MailAdditionalData { /* field names derived */
    /* 0x00 */ int current_count;
    /* 0x04 */ MailAddEntry e[MAIL_ADDITIONAL_DATA_MAX];
} MailAdditionalData; /* derived name */

static inline int sendMailAndGetIndex(GObj *gop, int msg, void *sender) /* derived name */
{
    if (iosOmSendMail(gop, msg, sender) < 0) {
        return -1;
    }
    return gop->mailBox.num - 1;
}

static inline MailAdditionalData *getMailAdditionalDataTable(GObj *gop) /* derived name */
{
    if (gop->act == 0) {
        debug_assert("src/mail-add-data.c", 71);
        __assert("src/mail-add-data.c", 71, "GOBJ_VAL(gop)");
    }
    /* Act's 0x684 holds this table's address, an int in typedef.h's Act */
    return GOBJ_ACT(gop)->mailAddData;
}

#include "mail-add-data.h"
#include "include_asm.h"

INCLUDE_ASM_LIT(ActSendMail_WithAdditionalData);

INCLUDE_ASM(InitMailAdditionalData);

INCLUDE_ASM(ActSendMail_WithAdditionalData);

INCLUDE_ASM(GetMailAdditionalData);

INCLUDE_ASM(ClearMailAdditionalData);
