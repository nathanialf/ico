/*
 * ico2/omori/include/mail-add-data.h
 *
 * The declarations of what mail-add-data.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MAIL_ADD_DATA_H
#define MAIL_ADD_DATA_H

struct GObj;
int ActSendMail_WithAdditionalData(struct GObj *gop, int msg, void *sender, void *data);
void *GetMailAdditionalData(struct GObj *gop, int mail);
inline void ClearMailAdditionalData(struct GObj *gop);

struct MailAdditionalData;
void InitMailAdditionalData(struct GObj *gop, struct MailAdditionalData *table);

#endif /* MAIL_ADD_DATA_H */
