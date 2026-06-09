#include "common.h"
#include "r5900.h"

extern int func_0023CCE0(int *a, int *b);

int func_0019B8E0(int a0_unused, int *a1, char *a2) {
    long long buf[4];
    func_0023CCE0((int *)(a2 + 0x50), (int *)buf);
    *(long long *)((char *)a1 + 0x8) = buf[0];
    *(long long *)((char *)a1 + 0x10) = buf[1];
    return 1;
}

extern void voBufIsFull(int a0);

void voBufCreate(a0)
int *a0;
{
    voBufIsFull(a0[0]);
    voBufIsFull(a0[1]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufDelete);

void voBufReset(void) {
    voBufCreate();
}

extern int iosMallocCheckLeak2(int a0);

void voBufIsFull(int a0) {
    iosMallocCheckLeak2(a0 & 0xFFFFFFF);
}

/* voBufIncCount — hand-written assembly in Ito's movie/IPU buffer layer. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel voBufIncCount\n"
    "    sw         $0, 0xC($4)\n"
    "    sw         $0, 0x8($4)\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel voBufIncCount\n"
    "    .set reorder\n"
    "    .set at\n"
);

int voBufGetData(int *a0) {
    return a0[3] == a0[4];
}

extern void func_00101A40(volatile int *a0);

/* voBufGetTag — critical-section update of the shared (volatile) movie output
 * ring: tags the current frame, bumps writeIdx, advances readIdx mod numFrames,
 * then SYNC + EI. The volatile struct pointer orders the field accesses to match
 * Ito's hand-scheduled IPU code. */
void voBufGetTag(volatile int *a0) {
    int w, n;
    func_00101A40(a0);
    *(int *)(a0[1] + a0[2] * 0xA0A40) = 2;
    w = a0[3];
    n = a0[4];
    a0[3] = w + 1;
    a0[2] = (a0[2] + 1) % n;
    SYNC();
    EI();
}
