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

void isysGObjProcActiveAll(void *a0);
int isysGObjProcAdd(int a0, int a1, int a2, int a3);
int isysGObjProcAddGOppArg(int a0, int a1, int a2, int a3);
int isysGObjProcAddS(int a0, int a1, int a2, int a3, int a4);
int isysGObjProcAdd_(int a0, int a1, int a2, unsigned char a3, int a4, int a5);
void isysGObjProcPauseAll(int *p);
void isysGObjProcRemove(int *a0);
void isysGObjProcessInit(unsigned int a0);

#endif /* GOBJ_PROCESS_H */
