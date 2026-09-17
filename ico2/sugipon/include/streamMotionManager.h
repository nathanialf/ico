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

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order streamMotionManager.c's inline tail has. */
void StandbyStreamMotion(int self);
void StopStreamMotion(void);
void DeleteStreamMotionManager(void);
int EntryStreamMotion(char *a0);
int GetDataSizeOfStreamMotion(int no);
float GetStreamMotionData(char *dst, int no);
void InitStreamMotionManager(void);
int CheckReadyStreamMotion(void);
void SetStreamMotionFinishCallBackFunc(int a0, int a1);
void FreeStreamMotionBuffer(void);
void ClearAllStreamMotionEntry(void);
int _closeHander(void);
int _handler(int self);

void ClearStreamMotionEntry(char *gobj);
void DisableStreamMotionManagerAutomaticDelete(void);
void GetStreamMotionDataNext(int a0, int a1);
void MallocStreamMotionBuffer(void);
void PlayStreamMotion(void);
void _deleteStreamMotionManager(void);
int _infoUpdate(void);
void getStreamMotionData(char *dst, int off, int no);

#endif /* STREAMMOTIONMANAGER_H */
