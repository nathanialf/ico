/*
 * ico2/fumi/include/gobj_process.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gobj_process.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GOBJ_PROCESS_H
#define GOBJ_PROCESS_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order gobj_process.c's inline tail has. */
void isysGObjProcessAlloc(unsigned int a0);
int isysGObjProcAdd(int a0, int a1, int a2, int a3);
int isysGObjProcAddS(int a0, int a1, int a2, int a3, int a4);
int isysGObjProcAddGOppArg(int a0, int a1, int a2, int a3);
void isysGObjProcPause(char *self);
void isysGObjProcPauseAll(int *p);
void isysGObjProcPausePtr(void *a0, int a1);
void isysGObjProcActive(char *self);
void isysGObjProcActiveAll(void *a0);
void isysGObjProcRemoveAll(void *a0);
void isysGObjProcThreadSleep(int a0);
int isysGObjProcAddSGOppArg(int a, int b, int c, int d, int e);
void isysGObjProcActivePtr(void *a0, int a1);
void free_gobj_process_resource(char *self);

int isysGObjProcAdd_(int a0, int a1, int a2, unsigned char a3, int a4, int a5);
void isysGObjProcRemove(int *a0);
void isysGObjProcessInit(unsigned int a0);

#endif /* GOBJ_PROCESS_H */
