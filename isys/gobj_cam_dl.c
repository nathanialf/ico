#include "common.h"

typedef struct { char p[0x34]; void *f34; void *f38; char p2[4]; unsigned char f40; char p3[3]; int f44; } AdpT;




extern int *D_006321D4;
extern AdpT *D_006321D8;
extern char D_0061AC80[];
extern void debug_StdPrintfDummy();
extern void func_001FBFC8();
INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", cut_gobj_camera_dl_link);

void isysGObjRemoveCameraDL(int a0, int a1)
{
    func_001FBFC8(a0);
    return cut_gobj_camera_dl_link(a0, a1);
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", func_001FC1A0);

void isysGObjMoveCameraDL(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_StdPrintfDummy(D_0061AC80);
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
        D_006321D8 = (AdpT *)t1;
    }
}

void isysGObjLinkCameraDL(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_StdPrintfDummy(D_0061AC80);
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
        D_006321D8 = (AdpT *)t1;
    }
}

void isysGObjLinkCameraDLAfterGObj(void) {
    D_006321D4 = 0;
    D_006321D8 = 0;
}


void isysGObjMoveCameraDLHead(int a0, int a1)
{
    int *self = (int *)a0;
    int key = a1;
    int *head;
    int *tail;
    int *cur;
    int *next;

    func_001FBFC8(self);
    self[0x11] = key;
    head = D_006321D4;
    if (head == 0) {
        *(int *)&D_006321D8 = (int)self;
        self[0xE] = 0;
        self[0xD] = 0;
        *(int *)&D_006321D4 = (int)self;
        return;
    }
    if ((unsigned int)head[0x11] >= (unsigned int)key) {
        self[0xE] = 0;
        self[0xD] = (int)head;
        head[0xE] = (int)self;
        D_006321D4 = self;
        return;
    }
    tail = (int *)D_006321D8;
    if ((unsigned int)tail[0x11] < (unsigned int)key) {
        self[0xE] = (int)tail;
        self[0xD] = 0;
        tail[0xD] = (int)self;
        D_006321D8 = (AdpT *)self;
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

extern void func_001FBFC8(void *a0);

void isysObjMoveCameraDLAfterGObj(AdpT *a0, AdpT *a1) {
    func_001FBFC8(a0);
    a0->f40 = a1->f40;
    a0->f38 = a1;
    a0->f34 = a1->f34;
    a1->f34 = a0;
    a0->f44 = a1->f44;
    if (a0->f34 == 0) {
        D_006321D8 = a0;
    }
}

void isysObjMoveCameraDLBeforeGObj(char *a0, char *a1) {
    int next;
    func_001FBFC8(a0);
    *(unsigned char *)(a0 + 0x40) = *(unsigned char *)(a1 + 0x40);
    next = *(int *)(a1 + 0x38);
    *(int *)(a0 + 0x34) = (int)a1;
    *(int *)(a0 + 0x38) = next;
    *(int *)(a1 + 0x38) = (int)a0;
    *(int *)(a0 + 0x44) = *(int *)(a1 + 0x44);
    if (*(int *)(a0 + 0x38) == 0) {
        D_006321D4 = (int *)a0;
    }
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", func_001FC520);

