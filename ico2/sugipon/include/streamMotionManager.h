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

extern int CheckReadyStreamMotion(void);
extern void ClearStreamMotionEntry(char *gobj);
extern void DeleteStreamMotionManager(void);
extern void DisableStreamMotionManagerAutomaticDelete(void);
extern int EntryStreamMotion(char *a0);
extern int GetDataSizeOfStreamMotion(int no);
extern float GetStreamMotionData(char *dst, int no);
extern void GetStreamMotionDataNext(int a0, int a1);
extern void MallocStreamMotionBuffer(void);
extern void PlayStreamMotion(void);
extern void SetStreamMotionFinishCallBackFunc(int a0, int a1);
extern void StandbyStreamMotion(int self);
extern void _deleteStreamMotionManager(void);
extern int _infoUpdate(void);
extern void getStreamMotionData(char *dst, int off, int no);

#endif /* STREAMMOTIONMANAGER_H */
