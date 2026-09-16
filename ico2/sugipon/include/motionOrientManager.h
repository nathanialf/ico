/*
 * ico2/sugipon/include/motionOrientManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what motionOrientManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MOTIONORIENTMANAGER_H
#define MOTIONORIENTMANAGER_H

extern void ExecMotionOrient(void *self);
extern int ExecutePauseSlipProc(char *a0);
extern int ExecuteSlipProc(char *a0);
extern float GetMotionPlaySpeedRatio(int id);
extern int GetNbMotionFrames(int id);
extern void InitMotionOrient(void *self, int a1, int a2, int a3, int a4, int a5);
extern char *SetMotionRequest(int self, int mot, char *work);
extern void SetNodeRotationLimitDataTable(void *self, int a1, int a2);
extern void SetParallelMotionTable(void *self, int a1, int a2, int a3, int a4);
extern void SetParallelMotionTableWithNoRequest(void *self, int a1, int a2);
extern void getMotionGeometry(void *self);
extern void getShapeGeometry(void *self);
extern void getStreamBlendShapeGeometry(void *self, void *m0, void *m1, float t);
extern void getStreamShapeGeometry(void *self, void *sm);
extern void normalMotionShift(void *self, int a1);
extern void orientDebug(void *self, int mode, int col);
extern int parallelMotionShift(void *self);
extern void shiftMotionData(int a0, int a1, int a2, int a3);

#endif /* MOTIONORIENTMANAGER_H */
