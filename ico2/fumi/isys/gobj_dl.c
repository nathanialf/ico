#include "debug.h"
#include "gobj_dl.h"
#include "isys.h"

static void add_gobj_to_head(int a0, int a1, int a2);

/* a file-static add_gobj_to_head, distinct from the isys/gobj global of the
   same name; every gobj list TU has its own copy */

inline void isysGObjDlInit(void)
{
    int i;
    for (i = 0; i < 8; i++) {
        gobj_dl_link_head[i] = 0;
        gobj_dl_link_tail[i] = 0;
    }
}

void cut_gobj_dl_link(int *self)
{
    DLN *p = (DLN *)self;

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

void isysGObjRemoveObjDL(int *self)
{
    cut_gobj_dl_link(self);
}

/* a file-static add_gobj_to_tail, distinct from the isys/gobj global of the
   same name */
static void add_gobj_to_tail(int a0, int a1, int a2)
{
    DLN *self = (DLN *)a0;
    unsigned char idx = a1 & 0xFF;
    DLN *head;
    DLN *tail;
    DLN *cur;

    debug_StdPrintfDummy("gobj dl added to tail\n");
    self->id = idx;
    self->key = a2;
    head = ((DLN **)gobj_dl_link_head)[idx];
    if (head == 0) {
        ((DLN **)gobj_dl_link_head)[idx] = self;
        self->prev = 0;
        self->next = 0;
        ((DLN **)gobj_dl_link_tail)[idx] = self;
        debug_StdPrintfDummy("no_entry %p\n", self->next);
        return;
    }
    if ((unsigned int)a2 < (unsigned int)head->key) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        ((DLN **)gobj_dl_link_head)[idx] = self;
        debug_StdPrintfDummy("add to head %p\n", self->next);
        return;
    }
    tail = ((DLN **)gobj_dl_link_tail)[idx];
    if ((unsigned int)a2 >= (unsigned int)tail->key) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        ((DLN **)gobj_dl_link_tail)[idx] = self;
        debug_StdPrintfDummy("add to tail %p\n", self->next);
        return;
    }
    cur = head;
    while ((unsigned int)cur->next->key <= (unsigned int)a2) {
        cur = cur->next;
    }
    self->prev = cur;
    self->next = cur->next;
    cur->next = self;
    self->next->prev = self;
}

static void add_gobj_to_head(int a0, int a1, int a2)
{
    DLN *self = (DLN *)a0;
    unsigned char idx = a1 & 0xFF;
    DLN *head;
    DLN *tail;
    DLN *cur;
    self->id = idx;
    self->key = a2;
    head = ((DLN **)gobj_dl_link_head)[idx];
    if (head == 0) {
        ((DLN **)gobj_dl_link_head)[idx] = self;
        self->prev = 0;
        self->next = 0;
        ((DLN **)gobj_dl_link_tail)[idx] = self;
        return;
    }
    if ((unsigned int)head->key >= (unsigned int)a2) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        ((DLN **)gobj_dl_link_head)[idx] = self;
        return;
    }
    tail = ((DLN **)gobj_dl_link_tail)[idx];
    if ((unsigned int)tail->key < (unsigned int)a2) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        ((DLN **)gobj_dl_link_tail)[idx] = self;
        return;
    }
    cur = head;
    while ((unsigned int)cur->next->key < (unsigned int)a2) {
        cur = cur->next;
    }
    self->prev = cur;
    self->next = cur->next;
    cur->next = self;
    self->next->prev = self;
}

void isysGObjMoveObjDL(int a0, unsigned char a1, int a2)
{
    cut_gobj_dl_link(a0);
    return add_gobj_to_tail(a0, a1, a2);
}

void isysGObjMoveObjDLHead(int a0, unsigned char a1, int a2)
{
    cut_gobj_dl_link(a0);
    return add_gobj_to_head(a0, a1, a2);
}

inline void isysGObjMoveObjDLAfterGObj(DLN *self, DLN *obj)
{
    cut_gobj_dl_link((int *)self);
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
    cut_gobj_dl_link((int *)self);
    self->id = obj->id;
    self->prev = obj->prev;
    self->next = obj;
    obj->prev = self;
    self->key = obj->key;
    if (self->prev == 0) {
        ((DLN **)gobj_dl_link_head)[self->id] = self;
    }
}

void isysGObjLinkObjDL(void *a0, void *a1, unsigned char a2, void *a3, void *a4)
{
    debug_StdPrintfDummy("GObjLinkDL in\n");
    if (a1 != 0) {
        ((DLN *)a0)->dl = a1;
        ((DLN *)a0)->drawMask = a4;
        add_gobj_to_tail(a0, a2, a3);
        debug_StdPrintfDummy("GObjLinkDL out\n");
    }
}

void isysGObjLinkObjDLHead(void *a0, void *a1, unsigned char a2, void *a3, void *a4)
{
    if (a1 != 0) {
        ((DLN *)a0)->dl = a1;
        ((DLN *)a0)->drawMask = a4;
        add_gobj_to_head(a0, a2, a3);
    }
}

void isysGObjLinkObjDLAfterGObj(DLN *self, void *a1, void *a2, DLN *a3)
{
    DLN *t0;
    DLN *v34;
    int v44;
    if (a1 == 0)
        return;
    t0 = self;
    if (a3 == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }
    t0->drawMask = a2;
    t0->dl = a1;
    t0->id = a3->id;
    t0->prev = a3;
    v34 = a3->next;
    v44 = a3->key;
    t0->next = v34;
    a3->next = t0;
    t0->key = v44;
    if (t0->next == 0) {
        ((DLN **)gobj_dl_link_tail)[t0->id] = t0;
    }
}

void isysGObjLinkObjDLBeforeGObj(DLN *self, void *a1, void *a2, DLN *a3)
{
    DLN *t0;
    DLN *v34;
    int v44;
    if (a1 == 0)
        return;
    t0 = self;
    if (a3 == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }
    t0->drawMask = a2;
    t0->dl = a1;
    t0->id = a3->id;
    t0->prev = a3;
    v34 = a3->next;
    v44 = a3->key;
    t0->next = v34;
    a3->next = t0;
    t0->key = v44;
    if (t0->next == 0) {
        ((DLN **)gobj_dl_link_tail)[t0->id] = t0;
    }
}
