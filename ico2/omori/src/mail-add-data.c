#include "typedef.h"
#include "obj_manager.h"
#include "debug_exception.h"

/* Two static helpers, one sending the mail and returning its index or -1,
 * the other asserting the actor has a work block and returning its
 * additional-data table.  InitMailAdditionalData calls
 * ClearMailAdditionalData, which is defined after it. */
extern void __assert(char *file, int line, char *expr);

typedef struct MailAddEntry {
    /* 0x0 */ int mail;
    /* 0x4 */ void *data;
} MailAddEntry;

typedef struct MailAdditionalData {
    /* 0x00 */ int num;
    /* 0x04 */ MailAddEntry e[10];
} MailAdditionalData;

static inline int sendMailAndGetIndex(char *gop, int msg, void *sender) /* derived name */
{
    if (iosOmSendMail(gop, msg, sender) < 0) {
        return -1;
    }
    return ((GObj *)gop)->f58 - 1;
}

static inline MailAdditionalData *getMailAdditionalDataTable(char *gop) /* derived name */
{
    if (((GObj *)gop)->act == 0) {
        debug_assert("src/mail-add-data.c", 71);
        __assert("src/mail-add-data.c", 71, "GOBJ_VAL(gop)");
    }
    /* Act's 0x684 holds this table's address, an int in typedef.h's Act */
    return (MailAdditionalData *)GOBJ_ACT(gop)->f_684;
}

#include "mail-add-data.h"

inline int ActSendMail_WithAdditionalData(char *gop, int msg, void *sender, void *data)
{
    int idx;
    MailAdditionalData *p;

    idx = sendMailAndGetIndex(gop, msg, sender);
    if (idx < 0) {
        return -1;
    }
    p = getMailAdditionalDataTable(gop);
    if (p->num >= 10) {
        debug_assert("src/mail-add-data.c", 95);
        __assert("src/mail-add-data.c", 95, "mad_all->current_count<MAIL_ADDITIONAL_DATA_MAX");
    }
    p->e[p->num].mail = idx;
    p->e[p->num].data = data;
    p->num++;
    return 0;
}

inline void *GetMailAdditionalData(char *gop, int mail)
{
    MailAdditionalData *p;
    int i;

    p = getMailAdditionalDataTable(gop);
    for (i = 0; i < p->num; i++) {
        MailAddEntry *e = &p->e[i];
        if (e->mail == mail) {
            return e->data;
        }
    }
    return 0;
}

void InitMailAdditionalData(char *a0, int a1)
{
    GOBJ_ACT(a0)->f_684 = a1;
    ClearMailAdditionalData(a0);
}

inline void ClearMailAdditionalData(char *gop)
{
    MailAdditionalData *p;

    p = getMailAdditionalDataTable(gop);
    p->num = 0;
}
