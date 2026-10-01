/*
 * ico2/omori/include/lws_kyomi.h
 *
 * The declarations of what lws_kyomi.c defines, for the files that use
 * them.  The file name is derived.
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
void ReadHintSaveInfo(void);
void SleepHint(int no);
void WakeupHint(int no);

#endif /* LWS_KYOMI_H */
