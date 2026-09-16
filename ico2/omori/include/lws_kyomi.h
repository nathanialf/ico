/*
 * ico2/omori/include/lws_kyomi.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what lws_kyomi.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef LWS_KYOMI_H
#define LWS_KYOMI_H

char *CreateKyomiGObj(int no);
void DebugHintStart(void *gobj);
void FinishHint(int no);
char *GetBuffHintSaveInfo(void);
int GetSizeHintSaveInfo(void);
void Hint_Init(void);
int IsTopHint(void *gobj);
void MakeHintSaveInfo(void);
int ReadHintSaveInfo();
void SleepHint(int no);
void WakeupHint(int no);

#endif /* LWS_KYOMI_H */
