/*
 * ico2/sugipon/include/streamMotionManager.h
 *
 * The declarations of what streamMotionManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef STREAMMOTIONMANAGER_H
#define STREAMMOTIONMANAGER_H

/* stream-motion-def: one stream motion file, 0x30 bytes. Readers:
 * ico2/script/src/st04a.c, st25a.c, e3.c (StandbyStreamMotion's file). */
typedef struct {    /* field names derived */
    char path[48];  /* 0x00 */
} StreamMotionFile; /* derived name */

struct GObj;

struct CdvdBgReq;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order streamMotionManager.c's inline tail has. */
void StandbyStreamMotion(char *file);
void StopStreamMotion(void);
void DeleteStreamMotionManager(void);
int EntryStreamMotion(struct GObj *gobj);
int GetDataSizeOfStreamMotion(int no);
float GetStreamMotionData(char *dst, int no);
void InitStreamMotionManager(void);
int CheckReadyStreamMotion(void);
void SetStreamMotionFinishCallBackFunc(int no, void (*func)(struct GObj *));
void FreeStreamMotionBuffer(void);
void ClearAllStreamMotionEntry(void);
void ClearStreamMotionEntry(struct GObj *gobj);
void DisableStreamMotionManagerAutomaticDelete(void);
void ExecStreamMotionManager(void);
void GetStreamMotionDataNext(char *dst, int no);
void MallocStreamMotionBuffer(void);
void PlayStreamMotion(void);

#endif /* STREAMMOTIONMANAGER_H */
