#include "mv_defs.h"
#include "typedef.h"
#include "memory.h"
#include <eekernel.h>
#include "mv_vobuf.h"

static void Free();

/* census free_buf, a file static, `static` keeps its ELF symbol local so it cannot
   collide with the ico2/ito/mpeg/mv_videodec global of the same name */
static void free_buf(VoBuf *self)
{
    Free((int)self->data);
    Free((int)self->tag);
}

int voBufCreate(VoBuf *self)
{
    int data;
    int tag;
    int i;

    data = alloc_zeroed(0x7E9000, 0x40);
    if (data == 0) {
        return -1;
    }
    self->data = (VoData *)uncached_accel_addr(data);
    tag = alloc_zeroed(0x3C1040, 0x40);
    self->tag = (VoTag *)tag;
    if (tag == 0) {
        return -1;
    }
    self->max = 5;
    self->count = 0;
    self->idx = 0;
    for (i = 0; i < self->max; i++) {
        self->tag[i].status = 0;
    }
    return 0;
}

void voBufDelete(VoBuf *self)
{
    free_buf(self);
}

/* census Free, this TU's own copy of the mv_defs.h file static, `static` keeps its
   ELF symbol local so it cannot collide with the mv_videodec global of that name */
static void Free(int a0)
{
    iosFree(phys_addr(a0));
}

void voBufReset(VoBuf *self)
{
    self->count = 0;
    self->idx = 0;
}

/* The listing expands voBufIsFull's line 52 into voBufGetData, so it is a
 * public `inline` of the deferred tail.  Until the tail's asm member (the
 * mv_defs.h file-static Free, this TU's own static copy) is C the copy is emitted here
 * as a plain function, which is its ROM position, and voBufGetData inlines
 * the static stand-in below; the two collapse into one `inline voBufIsFull`
 * at layout time. */
int voBufIsFull(VoBuf *self)
{
    return self->count == self->max;
}

static inline int isFull(VoBuf *self)
{
    return self->count == self->max;
}

void voBufIncCount(VoBuf *self)
{
    DIntr();
    self->tag[self->idx].status = 2;
    self->count++;
    self->idx = (self->idx + 1) % self->max;
    SYNC();
    EI();
}

VoData *voBufGetData(VoBuf *self)
{
    return !isFull(self) ? &self->data[self->idx] : 0;
}

static __inline__ int voBufIsEmpty(VoBuf *self)
{
    return self->count == 0;
}

VoTag *voBufGetTag(VoBuf *self)
{
    return !voBufIsEmpty(self) ? &self->tag[(self->idx - self->count + self->max) % self->max] : 0;
}

void voBufDecCount(VoBuf *self)
{
    if (self->count > 0) {
        --self->count;
    }
}
