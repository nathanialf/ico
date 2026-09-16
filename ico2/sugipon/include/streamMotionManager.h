/*
 * ico2/sugipon/include/streamMotionManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what streamMotionManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STREAMMOTIONMANAGER_H
#define STREAMMOTIONMANAGER_H

int CheckReadyStreamMotion(void);
void ClearStreamMotionEntry(char *gobj);
void DeleteStreamMotionManager(void);
void DisableStreamMotionManagerAutomaticDelete(void);
int EntryStreamMotion(char *a0);
int GetDataSizeOfStreamMotion(int no);
float GetStreamMotionData(char *dst, int no);
void GetStreamMotionDataNext(int a0, int a1);
void MallocStreamMotionBuffer(void);
void PlayStreamMotion(void);
void SetStreamMotionFinishCallBackFunc(int a0, int a1);
void StandbyStreamMotion(int self);
void _deleteStreamMotionManager(void);
int _infoUpdate(void);
void getStreamMotionData(char *dst, int off, int no);

#endif /* STREAMMOTIONMANAGER_H */
