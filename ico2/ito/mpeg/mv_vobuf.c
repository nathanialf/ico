#include "mv_defs.h"
#include "typedef.h"
#include "memory.h"
#include <eekernel.h>
#include "mv_vobuf.h"
#include "include_asm.h"

static void Free(int addr);

/* this file's own free_buf; mv_videodec.c and mv_vibuf.c have theirs */
static void free_buf(VoBuf *self)
{
    Free((int)self->data);
    Free((int)self->tag);
}

INCLUDE_ASM(voBufCreate);

void voBufDelete(VoBuf *self)
{
    free_buf(self);
}

/* this file's own Free (mv_defs.h) */
static void Free(int addr)
{
    /* the buffers are kept as addresses (alloc_zeroed), some at their
       uncached-accelerated alias; the heap takes the block back with the
       segment bits off */
    iosFree((void *)phys_addr(addr));
}

void voBufReset(VoBuf *self)
{
    self->count = 0;
    self->idx = 0;
}

/* Whether all of the ring's slots are in use.  isFull below is
 * the same test, for voBufGetData. */
int voBufIsFull(VoBuf *self)
{
    return self->count == self->max;
}

static inline int isFull(VoBuf *self) /* derived name */
{
    return self->count == self->max;
}

INCLUDE_ASM(voBufIncCount);

INCLUDE_ASM(voBufGetData);

static __inline__ int voBufIsEmpty(VoBuf *self) /* derived name */
{
    return self->count == 0;
}

INCLUDE_ASM(voBufGetTag);

void voBufDecCount(VoBuf *self)
{
    if (self->count > 0) {
        --self->count;
    }
}
