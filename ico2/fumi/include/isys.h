/*
 * ico2/fumi/include/isys.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what isys.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ISYS_H
#define ISYS_H

#include "typedef.h"

void isysInitialize(void);
/* MAIN.MAP globals of isys.o (defined in isys.c in this order) */
extern GObj *gobj_link_head[8];
extern GObj *gobj_link_tail[8];
extern int *gobj_dl_link_head[8];
extern int *gobj_dl_link_tail[8];
extern int active_gobj_link;
extern int active_gobj_dl_link;
extern int *gobj_camera_dl_link_head;
extern int *gobj_camera_dl_link_tail;
extern char *isysCurrentGObj;
extern void *isysCurrentGObjProcess;

#endif /* ISYS_H */
