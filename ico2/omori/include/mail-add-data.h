/*
 * ico2/omori/include/mail-add-data.h
 *
 * The declarations of what mail-add-data.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MAIL_ADD_DATA_H
#define MAIL_ADD_DATA_H

int ActSendMail_WithAdditionalData(char *gop, int msg, void *sender, void *data);
void *GetMailAdditionalData(char *gop, int mail);
void ClearMailAdditionalData(char *gop);

void InitMailAdditionalData(char *a0, int a1);

#endif /* MAIL_ADD_DATA_H */
