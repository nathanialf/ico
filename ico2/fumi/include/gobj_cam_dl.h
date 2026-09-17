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

typedef struct {
    char p[0x34];
    void *f34;
    void *f38;
    char p2[4];
    unsigned char f40;
    char p3[3];
    int f44;
} AdpT;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order gobj_cam_dl.c's inline tail has. */
void isysGObjCameraDlInit(void);
void isysGObjMoveCameraDLHead(int a0, int a1);
void isysGObjLinkCameraDLHead(int *self, int a1, int key, int a3, int a4);
void isysObjMoveCameraDLAfterGObj(AdpT *a0, AdpT *a1);
void isysObjMoveCameraDLBeforeGObj(char *a0, char *a1);

void isysGObjLinkCameraDL(char *a0, int a1, int a2, int a3, int a4);

#endif /* GOBJ_CAM_DL_H */
