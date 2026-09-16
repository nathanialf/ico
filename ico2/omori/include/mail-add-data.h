/*
 * ico2/omori/include/mail-add-data.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mail-add-data.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MAIL_ADD_DATA_H
#define MAIL_ADD_DATA_H

int ActSendMail_WithAdditionalData(char *gop, int msg, void *sender, void *data);
void ClearMailAdditionalData(char *gop);
void *GetMailAdditionalData(char *gop, int mail);
void InitMailAdditionalData(char *a0, int a1);

#endif /* MAIL_ADD_DATA_H */
