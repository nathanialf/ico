/*
 * ico2/fumi/include/isys.h
 *
 * The declarations of what isys.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ISYS_H
#define ISYS_H

#include "typedef.h"

void isysInitialize(void);
/* isys.o's globals (defined in isys.c in this order) */
extern GObj *gobj_link_head[8];
extern GObj *gobj_link_tail[8];
extern int *gobj_dl_link_head[8];
extern int *gobj_dl_link_tail[8];
extern int active_gobj_link;
extern int active_gobj_dl_link;
extern int *gobj_camera_dl_link_head;
extern int *gobj_camera_dl_link_tail;
extern GObj *isysCurrentGObj;
extern void *isysCurrentGObjProcess;

#endif /* ISYS_H */
