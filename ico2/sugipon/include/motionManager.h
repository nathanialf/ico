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

extern void GetGeometryOfMotion(void *self, void *m0, void *m1, float *v, float r, char *tbl, int k);
extern int SetDirectMotionProgramInterpInfo(char *a0, int a1, float f);
extern void SetHitCollisionDisplay(int a, int b);
extern void _checkCliffAndWall(void);
extern void _getFinalMatrix(int id);
extern int adjustSideWall(int a0, int a1, int a2);
extern int checkActPointWithHeight(int kind, float h);
extern void checkCliffState(int a0);
extern void checkWallSideState(void);
extern void checkWallState(int flag);
extern void clearCollisionStatus(void);
extern int findActPoint(int *list);
extern void func_001ECE40();
extern void getFinalMatrixWithNaturalGeometry(int id);
extern void rootUpdateY_Rope(int a0);

#endif /* MOTIONMANAGER_H */
