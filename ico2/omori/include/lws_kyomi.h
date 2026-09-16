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

extern char *CreateKyomiGObj(int no);
extern void DebugHintStart(void *gobj);
extern void FinishHint(int no);
extern char *GetBuffHintSaveInfo(void);
extern int GetSizeHintSaveInfo(void);
extern void Hint_Init(void);
extern int IsTopHint(void *gobj);
extern void MakeHintSaveInfo(void);
extern int ReadHintSaveInfo();
extern void SleepHint(int no);
extern void WakeupHint(int no);

#endif /* LWS_KYOMI_H */
