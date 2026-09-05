#include "common.h"

/* PAL listing (omori/src/mail-add-data.c): two static inline helpers,
 * lines 48-57 (send the mail, return its index or -1) and lines 68-74
 * (assert the actor has a work block, return its additional-data table),
 * expand into the three inline tail members; InitMailAdditionalData is
 * the TU's only plain function and calls ClearMailAdditionalData out of
 * line because that body is defined after it. */
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern int iosOmSendMail(char *gop, int msg, void *sender);
extern char D_005556B8[];
extern char D_005556D0[];
extern char D_005556E0[];

typedef struct MailAddEntry {
    /* 0x0 */ int mail;
    /* 0x4 */ void *data;
} MailAddEntry;

typedef struct MailAdditionalData {
    /* 0x00 */ int num;
    /* 0x04 */ MailAddEntry e[10];
} MailAdditionalData;

static inline int sendMailAndGetIndex(char *gop, int msg, void *sender)
{
    if (iosOmSendMail(gop, msg, sender) < 0) {
        return -1;
    }
    return *(int *)(gop + 0x58) - 1;
}

static inline MailAdditionalData *getMailAdditionalDataTable(char *gop)
{
    if (*(int *)(gop + 0x164) == 0) {
        debug_assert(D_005556B8, 71);
        __assert(D_005556B8, 71, D_005556D0);
    }
    return *(MailAdditionalData **)(*(char **)(gop + 0x164) + 0x684);
}

/* prototypes: their order is the inline tail's emission order */
int ActSendMail_WithAdditionalData(char *gop, int msg, void *sender, void *data);
void *GetMailAdditionalData(char *gop, int mail);
void ClearMailAdditionalData(char *gop);

inline int ActSendMail_WithAdditionalData(char *gop, int msg, void *sender, void *data) {
    int idx;
    MailAdditionalData *p;

    idx = sendMailAndGetIndex(gop, msg, sender);
    if (idx < 0) {
        return -1;
    }
    p = getMailAdditionalDataTable(gop);
    if (p->num >= 10) {
        debug_assert(D_005556B8, 95);
        __assert(D_005556B8, 95, D_005556E0);
    }
    p->e[p->num].mail = idx;
    p->e[p->num].data = data;
    p->num++;
    return 0;
}
inline void *GetMailAdditionalData(char *gop, int mail) {
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
void InitMailAdditionalData(char *a0, int a1) {
    *(int *)(*(char **)(a0 + 0x164) + 0x684) = a1;
    ClearMailAdditionalData(a0);
}
inline void ClearMailAdditionalData(char *gop) {
    MailAdditionalData *p;

    p = getMailAdditionalDataTable(gop);
    p->num = 0;
}
