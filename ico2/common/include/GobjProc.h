/*
 * ico2/common/include/GobjProc.h
 *
 * The declarations of what GobjProc.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GOBJPROC_H
#define GOBJPROC_H

#include "typedef.h"

/* GobjProc.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
GObj *CreateGObjByFuncSet(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
GObj *CreateGObj(ObjKindEnt *kind, int id, int a2, int a3, int a4);
int GetGObjId(int a0);
int GetGObjP(int idx);
int GetMaxGObj(void);
GObj *InitCameraGObjs(int stage, int a1, int a2);
void ResetGObjProc(void);

#endif /* GOBJPROC_H */
