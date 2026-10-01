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
GObj *CreateGObjByFuncSet(void (*before)(GObj *), void (*ai)(GObj *), void (*geo)(GObj *),
                          void (*afterGeo)(GObj *), void (*start)(), void (*dl)(GObj *), int key);
GObj *CreateGObj(ObjKindEnt *kind, int id, int a2, int a3, int a4);
int GetGObjId(GObj *gobj);
GObj *GetGObjP(int idx);
int GetMaxGObj(void);
GObj *InitCameraGObjs(int stage, int a1, int a2);
void ResetGObjProc(void);
void PrintGObjID(GObj *gobj);

#endif /* GOBJPROC_H */
