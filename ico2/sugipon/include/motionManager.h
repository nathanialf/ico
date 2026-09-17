/*
 * ico2/sugipon/include/motionManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what motionManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MOTIONMANAGER_H
#define MOTIONMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order motionManager.c's inline tail has. */
void SetHitCollisionDisplay(int a, int b);
int ResetMotionProgramInterpInfo(char *a0, int a1);
int SetDirectMotionProgramInterpInfo(char *a0, int a1, float f);

void GetGeometryOfMotion(void *self, void *m0, void *m1, float *v, float r, char *tbl, int k);
void _checkCliffAndWall(void);
void _getFinalMatrix(int id);
int adjustSideWall(int a0, int a1, int a2);
int checkActPointWithHeight(int kind, float h);
void checkCliffState(int a0);
void checkWallSideState(void);
void checkWallState(int flag);
void clearCollisionStatus(void);
int findActPoint(int *list);
void func_001ECE40();
void getFinalMatrixWithNaturalGeometry(int id);
void rootUpdateY_Rope(int a0);

#endif /* MOTIONMANAGER_H */
