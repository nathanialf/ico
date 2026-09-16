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

void ExecMotionOrient(void *self);
int ExecutePauseSlipProc(char *a0);
int ExecuteSlipProc(char *a0);
float GetMotionPlaySpeedRatio(int id);
int GetNbMotionFrames(int id);
void InitMotionOrient(void *self, int a1, int a2, int a3, int a4, int a5);
char *SetMotionRequest(int self, int mot, char *work);
void SetNodeRotationLimitDataTable(void *self, int a1, int a2);
void SetParallelMotionTable(void *self, int a1, int a2, int a3, int a4);
void SetParallelMotionTableWithNoRequest(void *self, int a1, int a2);
void getMotionGeometry(void *self);
void getShapeGeometry(void *self);
void getStreamBlendShapeGeometry(void *self, void *m0, void *m1, float t);
void getStreamShapeGeometry(void *self, void *sm);
void normalMotionShift(void *self, int a1);
void orientDebug(void *self, int mode, int col);
int parallelMotionShift(void *self);
void shiftMotionData(int a0, int a1, int a2, int a3);

#endif /* MOTIONORIENTMANAGER_H */
