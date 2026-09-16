/*
 * ico2/fumi/include/gobj_cam_dl.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gobj_cam_dl.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GOBJ_CAM_DL_H
#define GOBJ_CAM_DL_H

void isysGObjCameraDlInit(void);
void isysGObjLinkCameraDL(char *a0, int a1, int a2, int a3, int a4);

#endif /* GOBJ_CAM_DL_H */
