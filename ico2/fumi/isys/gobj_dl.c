#include "debug.h"
#include "gobj_dl.h"
#include "isys.h"
#include "include_asm.h"

static void add_gobj_to_head(GObj *self, int kind, int key);

/* this list's own add_gobj_to_head; isys/gobj and each gobj list TU have
   their own file-static copy */

inline void isysGObjDlInit(void)
{
    int i;
    for (i = 0; i < 8; i++) {
        gobj_dl_link_head[i] = 0;
        gobj_dl_link_tail[i] = 0;
    }
}

static void cut_gobj_dl_link(GObj *p)
{
    if (p == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }

    if (p->dlPrev == 0 && p->dlNext == 0) {
        /* not linked into a list */
    } else {
        if (p->dlPrev != 0)
            p->dlPrev->dlNext = p->dlNext;

        if (p->dlNext != 0) {
            p->dlNext->dlPrev = p->dlPrev;
        }
    }

    if (p == gobj_dl_link_head[p->dlLinkId]) {
        gobj_dl_link_head[p->dlLinkId] = p->dlNext;
    }
    if (p == gobj_dl_link_tail[p->dlLinkId]) {
        gobj_dl_link_tail[p->dlLinkId] = p->dlPrev;
    }
}

void isysGObjRemoveObjDL(GObj *self)
{
    cut_gobj_dl_link(self);
}

/* this list's own add_gobj_to_tail, as in isys/gobj */
static void add_gobj_to_tail(GObj *self, int kind, int key);

INCLUDE_ASM(add_gobj_to_tail_gobj_dl);

INCLUDE_ASM(add_gobj_to_head_gobj_dl);

INCLUDE_ASM(isysGObjMoveObjDL);

INCLUDE_ASM(isysGObjMoveObjDLHead);

inline void isysGObjMoveObjDLAfterGObj(GObj *self, GObj *obj)
{
    cut_gobj_dl_link(self);
    self->dlLinkId = obj->dlLinkId;
    self->dlPrev = obj;
    self->dlNext = obj->dlNext;
    obj->dlNext = self;
    self->dlKey = obj->dlKey;
    if (self->dlNext == 0) {
        gobj_dl_link_tail[self->dlLinkId] = self;
    }
}

inline void isysGObjMoveObjDLBeforeGObj(GObj *self, GObj *obj)
{
    cut_gobj_dl_link(self);
    self->dlLinkId = obj->dlLinkId;
    self->dlPrev = obj->dlPrev;
    self->dlNext = obj;
    obj->dlPrev = self;
    self->dlKey = obj->dlKey;
    if (self->dlPrev == 0) {
        gobj_dl_link_head[self->dlLinkId] = self;
    }
}

INCLUDE_ASM(isysGObjLinkObjDL);

INCLUDE_ASM(isysGObjLinkObjDLHead);

void isysGObjLinkObjDLAfterGObj(GObj *self, void *dl, int drawMask, GObj *obj)
{
    GObj *t0;
    GObj *v34;
    int v44;
    if (dl == 0)
        return;
    t0 = self;
    if (obj == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }
    t0->drawMask = drawMask;
    t0->dl = dl;
    t0->dlLinkId = obj->dlLinkId;
    t0->dlPrev = obj;
    v34 = obj->dlNext;
    v44 = obj->dlKey;
    t0->dlNext = v34;
    obj->dlNext = t0;
    t0->dlKey = v44;
    if (t0->dlNext == 0) {
        gobj_dl_link_tail[t0->dlLinkId] = t0;
    }
}

void isysGObjLinkObjDLBeforeGObj(GObj *self, void *dl, int drawMask, GObj *obj)
{
    GObj *t0;
    GObj *v34;
    int v44;
    if (dl == 0)
        return;
    t0 = self;
    if (obj == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }
    t0->drawMask = drawMask;
    t0->dl = dl;
    t0->dlLinkId = obj->dlLinkId;
    t0->dlPrev = obj;
    v34 = obj->dlNext;
    v44 = obj->dlKey;
    t0->dlNext = v34;
    obj->dlNext = t0;
    t0->dlKey = v44;
    if (t0->dlNext == 0) {
        gobj_dl_link_tail[t0->dlLinkId] = t0;
    }
}
