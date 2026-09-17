/*
 * ico2/common/include/GobjProc.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what GobjProc.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GOBJPROC_H
#define GOBJPROC_H

#include "typedef.h"

/* The game object CreateGObjByFuncSet returns: field offsets are read from the
 * ROM's loads and stores at this TU's call sites. */

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order GobjProc.c's inline tail has. */
PObjGObj *CreateGObjByFuncSet(int a0, int a1, int a2, int a3, int a4, int a5, int a6);

PObjGObj *CreateGObj(PObjGObj *layout, int id, int a2, int a3, int a4);
int GetGObjId(int a0);
int GetGObjP(int idx);
int GetMaxGObj(void);
PObjGObj *InitCameraGObjs(int stage, int a1, int a2);
void ResetGObjProc(void);

#endif /* GOBJPROC_H */
