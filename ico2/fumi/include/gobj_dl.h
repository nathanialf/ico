/*
 * ico2/fumi/include/gobj_dl.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gobj_dl.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GOBJ_DL_H
#define GOBJ_DL_H

extern void cut_gobj_dl_link(int *self);
extern void isysGObjDlInit(void);
extern void isysGObjLinkObjDL(void *a0, void *a1, unsigned char a2, void *a3, void *a4);

#endif /* GOBJ_DL_H */
