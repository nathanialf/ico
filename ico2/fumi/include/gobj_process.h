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

extern void isysGObjProcActiveAll(void *a0);
extern int isysGObjProcAdd(int a0, int a1, int a2, int a3);
extern int isysGObjProcAddGOppArg(int a0, int a1, int a2, int a3);
extern int isysGObjProcAddS(int a0, int a1, int a2, int a3, int a4);
extern int isysGObjProcAdd_(int a0, int a1, int a2, unsigned char a3, int a4, int a5);
extern void isysGObjProcPauseAll(int *p);
extern void isysGObjProcRemove(int *a0);
extern void isysGObjProcessInit(unsigned int a0);

#endif /* GOBJ_PROCESS_H */
