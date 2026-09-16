/*
 * ico2/fumi/include/vobj.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what vobj.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef VOBJ_H
#define VOBJ_H

extern void DrawVObj(int no, int color);
extern void SetVObjRT(int a0, void *a1);

#endif /* VOBJ_H */
