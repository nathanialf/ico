#include "isys.h"
#include "obj_manager.h"

/* isys.o's globals, used by the gobj, gobj_dl, gobj_cam_dl and obj_manager
   members and the act TUs: the kind-indexed list ends in .data, the active
   masks, the camera display list ends and the current object and process in
   .sdata.  All are tentative definitions. */
GObj *gobj_link_head[8];

GObj *gobj_link_tail[8];

int *gobj_dl_link_head[8];

int *gobj_dl_link_tail[8];

int active_gobj_link;

int active_gobj_dl_link;

struct DLN *gobj_camera_dl_link_head;

struct DLN *gobj_camera_dl_link_tail;

GObj *isysCurrentGObj;

void *isysCurrentGObjProcess;

void isysInitialize(void)
{
    iosOmInit();
}
