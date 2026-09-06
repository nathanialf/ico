#define MV_DEFS_WANT_ALLOC
#include "common.h"

#include "mv_defs.h"

#include "r5900.h"

void func_001A7180(a0, a1)
int *a0;
int a1;
{
    func_001A7318(a0[0]);
    func_001A7318(a0[1]);
}
typedef struct VoBuf {
    void *data;
    void *tag;
    volatile int idx;
    volatile int count;
    int max;
} VoBuf;

int voBufCreate(VoBuf *self)
{
    int data;
    int tag;
    int i;

    data = alloc_zeroed(0x7E9000, 0x40);
    if (data == 0) {
        return -1;
    }
    self->data = (void *)uncached_accel_addr(data);
    tag = alloc_zeroed(0x3C1040, 0x40);
    self->tag = (void *)tag;
    if (tag == 0) {
        return -1;
    }
    self->max = 5;
    self->count = 0;
    self->idx = 0;
    for (i = 0; i < self->max; i++) {
        *(int *)(tag + i * 0xC0340) = 0;
    }
    return 0;
}
extern void func_001A7180();

void voBufDelete(void) {
    func_001A7180();
}
extern void iosFree();

void func_001A7318(int a0)
{
    iosFree(phys_addr(a0));
}
void voBufReset(volatile int *self)
{
    self[3] = 0;
    self[2] = 0;
}
/* The listing expands voBufIsFull's line 52 into voBufGetData, so it is a
 * public `inline` of the deferred tail.  Until the tail's asm member (the
 * mv_defs.h file-static Free, func_001A7318) is C the copy is emitted here
 * as a plain function, which is its ROM position, and voBufGetData inlines
 * the static stand-in below; the two collapse into one `inline voBufIsFull`
 * at layout time. */
int voBufIsFull(int *self) {
    return self[3] == self[4];
}
static inline int isFull(int *self) {
    return self[3] == self[4];
}
extern void DIntr(void);

void voBufIncCount(int *self)
{
    DIntr();
    *(int *)(self[1] + *(volatile int *)(self + 2) * 0xC0340) = 2;
    *(volatile int *)(self + 3) = *(volatile int *)(self + 3) + 1;
    *(volatile int *)(self + 2) = (*(volatile int *)(self + 2) + 1) % self[4];
    SYNC();
    EI();
}
void *voBufGetData(int *self)
{
    return !isFull(self) ? (void *)(self[0] + *(volatile int *)(self + 2) * 0x195000) : 0;
}
static __inline__ int voBufIsEmpty(int *self)
{
    return *(volatile int *)(self + 3) == 0;
}
void *voBufGetTag(int *self)
{
    return !voBufIsEmpty(self)
        ? (void *)(self[1] + (*(volatile int *)(self + 2) - *(volatile int *)(self + 3) + self[4]) % self[4] * 0xC0340)
        : 0;
}
void voBufDecCount(int *p) {
    if (*(volatile int *)(p + 3) > 0) {
        --(*(volatile int *)(p + 3));
    }
}
