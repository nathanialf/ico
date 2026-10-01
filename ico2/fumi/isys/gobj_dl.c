#include "debug.h"
#include "gobj_dl.h"
#include "isys.h"

static void add_gobj_to_head(DLN *self, int kind, int key);

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

static void cut_gobj_dl_link(DLN *p)
{
    if (p == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }

    if (p->prev == 0 && p->next == 0) {
        /* not linked into a list */
    } else {
        if (p->prev != 0)
            p->prev->next = p->next;

        if (p->next != 0) {
            p->next->prev = p->prev;
        }
    }

    if (p == ((DLN **)gobj_dl_link_head)[p->id]) {
        ((DLN **)gobj_dl_link_head)[p->id] = p->next;
    }
    if (p == ((DLN **)gobj_dl_link_tail)[p->id]) {
        ((DLN **)gobj_dl_link_tail)[p->id] = p->prev;
    }
}

void isysGObjRemoveObjDL(DLN *self)
{
    cut_gobj_dl_link(self);
}

/* this list's own add_gobj_to_tail, as in isys/gobj */
static void add_gobj_to_tail(DLN *self, int kind, int key)
{
    unsigned char idx = kind & 0xFF;
    DLN *head;
    DLN *tail;
    DLN *cur;

    debug_StdPrintfDummy("gobj dl added to tail\n");
    self->id = idx;
    self->key = key;
    head = ((DLN **)gobj_dl_link_head)[idx];
    if (head == 0) {
        ((DLN **)gobj_dl_link_head)[idx] = self;
        self->prev = 0;
        self->next = 0;
        ((DLN **)gobj_dl_link_tail)[idx] = self;
        debug_StdPrintfDummy("no_entry %p\n", self->next);
        return;
    }
    if ((unsigned int)key < (unsigned int)head->key) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        ((DLN **)gobj_dl_link_head)[idx] = self;
        debug_StdPrintfDummy("add to head %p\n", self->next);
        return;
    }
    tail = ((DLN **)gobj_dl_link_tail)[idx];
    if ((unsigned int)key >= (unsigned int)tail->key) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        ((DLN **)gobj_dl_link_tail)[idx] = self;
        debug_StdPrintfDummy("add to tail %p\n", self->next);
        return;
    }
    cur = head;
    while ((unsigned int)cur->next->key <= (unsigned int)key) {
        cur = cur->next;
    }
    self->prev = cur;
    self->next = cur->next;
    cur->next = self;
    self->next->prev = self;
}

static void add_gobj_to_head(DLN *self, int kind, int key)
{
    unsigned char idx = kind & 0xFF;
    DLN *head;
    DLN *tail;
    DLN *cur;
    self->id = idx;
    self->key = key;
    head = ((DLN **)gobj_dl_link_head)[idx];
    if (head == 0) {
        ((DLN **)gobj_dl_link_head)[idx] = self;
        self->prev = 0;
        self->next = 0;
        ((DLN **)gobj_dl_link_tail)[idx] = self;
        return;
    }
    if ((unsigned int)head->key >= (unsigned int)key) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        ((DLN **)gobj_dl_link_head)[idx] = self;
        return;
    }
    tail = ((DLN **)gobj_dl_link_tail)[idx];
    if ((unsigned int)tail->key < (unsigned int)key) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        ((DLN **)gobj_dl_link_tail)[idx] = self;
        return;
    }
    cur = head;
    while ((unsigned int)cur->next->key < (unsigned int)key) {
        cur = cur->next;
    }
    self->prev = cur;
    self->next = cur->next;
    cur->next = self;
    self->next->prev = self;
}

void isysGObjMoveObjDL(DLN *self, unsigned char kind, int key)
{
    cut_gobj_dl_link(self);
    return add_gobj_to_tail(self, kind, key);
}

void isysGObjMoveObjDLHead(DLN *self, unsigned char kind, int key)
{
    cut_gobj_dl_link(self);
    return add_gobj_to_head(self, kind, key);
}

inline void isysGObjMoveObjDLAfterGObj(DLN *self, DLN *obj)
{
    cut_gobj_dl_link(self);
    self->id = obj->id;
    self->prev = obj;
    self->next = obj->next;
    obj->next = self;
    self->key = obj->key;
    if (self->next == 0) {
        ((DLN **)gobj_dl_link_tail)[self->id] = self;
    }
}

inline void isysGObjMoveObjDLBeforeGObj(DLN *self, DLN *obj)
{
    cut_gobj_dl_link(self);
    self->id = obj->id;
    self->prev = obj->prev;
    self->next = obj;
    obj->prev = self;
    self->key = obj->key;
    if (self->prev == 0) {
        ((DLN **)gobj_dl_link_head)[self->id] = self;
    }
}

void isysGObjLinkObjDL(void *self, void *dl, unsigned char kind, int key, unsigned int drawMask)
{
    debug_StdPrintfDummy("GObjLinkDL in\n");
    if (dl != 0) {
        ((DLN *)self)->dl = dl;
        ((DLN *)self)->drawMask = drawMask;
        add_gobj_to_tail(self, kind, key);
        debug_StdPrintfDummy("GObjLinkDL out\n");
    }
}

void isysGObjLinkObjDLHead(void *self, void *dl, unsigned char kind, int key, unsigned int drawMask)
{
    if (dl != 0) {
        ((DLN *)self)->dl = dl;
        ((DLN *)self)->drawMask = drawMask;
        add_gobj_to_head(self, kind, key);
    }
}

void isysGObjLinkObjDLAfterGObj(DLN *self, void *dl, int drawMask, DLN *obj)
{
    DLN *t0;
    DLN *v34;
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
    t0->id = obj->id;
    t0->prev = obj;
    v34 = obj->next;
    v44 = obj->key;
    t0->next = v34;
    obj->next = t0;
    t0->key = v44;
    if (t0->next == 0) {
        ((DLN **)gobj_dl_link_tail)[t0->id] = t0;
    }
}

void isysGObjLinkObjDLBeforeGObj(DLN *self, void *dl, int drawMask, DLN *obj)
{
    DLN *t0;
    DLN *v34;
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
    t0->id = obj->id;
    t0->prev = obj;
    v34 = obj->next;
    v44 = obj->key;
    t0->next = v34;
    obj->next = t0;
    t0->key = v44;
    if (t0->next == 0) {
        ((DLN **)gobj_dl_link_tail)[t0->id] = t0;
    }
}
