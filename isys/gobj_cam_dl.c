#include "common.h"

typedef struct EnNode { char pad[0x34]; struct EnNode *prev; struct EnNode *next; } EnNode;

typedef struct { char p[0x34]; void *f34; void *f38; char p2[4]; unsigned char f40; char p3[3]; int f44; } AdpT;

extern char D_00621970[];
extern EnNode *D_0063A614__pn __asm__("D_0063A614");
extern EnNode *D_0063A618__pn __asm__("D_0063A618");
extern void debug_StdPrintfDummy();

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", cut_gobj_camera_dl_link);
extern void cut_gobj_camera_dl_link__pn(void *a0) __asm__("cut_gobj_camera_dl_link");

void isysGObjRemoveCameraDL(void *a0)
{
    cut_gobj_camera_dl_link__pn(a0);
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", func_0020BFD8);
extern void cut_gobj_camera_dl_link();
extern int func_0020BFD8();

void isysGObjMoveCameraDL(int a0, int a1)
{
    cut_gobj_camera_dl_link(a0);
    return func_0020BFD8(a0, a1);
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", isysGObjLinkCameraDL);
extern char D_00621970[];
extern AdpT *D_0063A618;
extern void debug_StdPrintfDummy();

void isysGObjLinkCameraDLAfterGObj(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_StdPrintfDummy(D_00621970);
        return;
    }

    t1[0x13] = a2;
    t1[0x14] = a3;
    t1[0x12] = a1;
    *((unsigned char *)t1 + 0x40) = *((unsigned char *)t0 + 0x40);
    t1[0xE] = (int)t0;
    v34 = t0[0xD];
    v44 = t0[0x11];
    t1[0xD] = v34;
    t0[0xD] = (int)t1;
    t1[0x11] = v44;
    if (t1[0xD] == 0) {
        D_0063A618 = (AdpT *)t1;
    }
}
void isysGObjLinkCameraDLBeforeGObj(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_StdPrintfDummy(D_00621970);
        return;
    }

    t1[0x13] = a2;
    t1[0x14] = a3;
    t1[0x12] = a1;
    *((unsigned char *)t1 + 0x40) = *((unsigned char *)t0 + 0x40);
    t1[0xE] = (int)t0;
    v34 = t0[0xD];
    v44 = t0[0x11];
    t1[0xD] = v34;
    t0[0xD] = (int)t1;
    t1[0x11] = v44;
    if (t1[0xD] == 0) {
        D_0063A618 = (AdpT *)t1;
    }
}
extern int *D_0063A614;

void isysGObjCameraDlInit(void) {
    D_0063A614 = 0;
    D_0063A618 = 0;
}
extern int *D_0063A614;
extern AdpT *D_0063A618;

void isysGObjMoveCameraDLHead(int a0, int a1)
{
    int *self = (int *)a0;
    int key = a1;
    int *head;
    int *tail;
    int *cur;
    int *next;

    cut_gobj_camera_dl_link(self);
    self[0x11] = key;
    head = D_0063A614;
    if (head == 0) {
        *(int *)&D_0063A618 = (int)self;
        self[0xE] = 0;
        self[0xD] = 0;
        *(int *)&D_0063A614 = (int)self;
        return;
    }
    if ((unsigned int)head[0x11] >= (unsigned int)key) {
        self[0xE] = 0;
        self[0xD] = (int)head;
        head[0xE] = (int)self;
        D_0063A614 = self;
        return;
    }
    tail = (int *)D_0063A618;
    if ((unsigned int)tail[0x11] < (unsigned int)key) {
        self[0xE] = (int)tail;
        self[0xD] = 0;
        tail[0xD] = (int)self;
        D_0063A618 = (AdpT *)self;
        return;
    }
    cur = head;
    next = (int *)cur[0xD];
    while ((unsigned int)next[0x11] < (unsigned int)key) {
        cur = next;
        next = (int *)cur[0xD];
    }
    self[0xE] = (int)cur;
    self[0xD] = cur[0xD];
    cur[0xD] = (int)self;
    ((int *)self[0xD])[0xE] = (int)self;
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", isysGObjLinkCameraDLHead);
void isysObjMoveCameraDLAfterGObj(AdpT *a0, AdpT *a1) {
    cut_gobj_camera_dl_link(a0);
    a0->f40 = a1->f40;
    a0->f38 = a1;
    a0->f34 = a1->f34;
    a1->f34 = a0;
    a0->f44 = a1->f44;
    if (a0->f34 == 0) {
        D_0063A618 = a0;
    }
}
void isysObjMoveCameraDLBeforeGObj(char *a0, char *a1) {
    int next;
    cut_gobj_camera_dl_link__pn(a0);
    *(unsigned char *)(a0 + 0x40) = *(unsigned char *)(a1 + 0x40);
    next = *(int *)(a1 + 0x38);
    *(int *)(a0 + 0x34) = (int)a1;
    *(int *)(a0 + 0x38) = next;
    *(int *)(a1 + 0x38) = (int)a0;
    *(int *)(a0 + 0x44) = *(int *)(a1 + 0x44);
    if (*(int *)(a0 + 0x38) == 0) {
        D_0063A614__pn = (int)a0;
    }
}
