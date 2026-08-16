#include "common.h"







extern int D_00633718;
extern int D_0063371C;
extern int D_00633728;
extern int D_00633724;
extern int D_00633720;
extern char D_0061A598[];
extern void debug_assertMessage();
struct Slot {
    int unk0, unk4, f_8, f_C;
    int self_ptr;
    int unk14;
};
extern int D_00633708;
extern struct Slot D_0070D4D8[];
extern int D_0063370C;
extern void func_00264128();
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", _infoUpdate);

void PlayStreamMotion(int *idx_p, char *dst, int size, char *src, int amt)
{
    int old_idx = *idx_p;
    int new_idx = old_idx + amt;
    *idx_p = new_idx;
    if (new_idx >= size) {
        int overflow = new_idx - size;
        int first_chunk = amt - overflow;
        *idx_p = overflow;
        func_00264128(dst + old_idx, src, first_chunk);
        func_00264128(dst, src + first_chunk, *idx_p);
        return;
    }
    func_00264128(dst + old_idx, src, amt);
}

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", func_001F0BC8);

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", func_001F0DA8);

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", func_001F0E40);

void GetStreamMotionData(void) {
    D_0063370C = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", _transRingBuf);

int ExecStreamMotionManager(volatile int *self)
{
    int slot = D_00633708;
    D_0070D4D8[slot].self_ptr = (int)self;
    ((int *)self[0x57])[0x11C] = slot;
    ((int *)self[0x57])[0x13C] = 0;
    ((int *)self[0x57])[0x13B] = 0;
    ((int *)self[0x57])[0x154] = 0;
    D_00633708 = slot + 1;
    return slot;
}

int StandbyStreamMotion(int idx)
{
  if (D_0070D4D8[idx].f_C < 0)
  {
    debug_assertMessage(D_0061A598);
    return 4;
  }
  return D_0070D4D8[idx].f_8;
}

void StopStreamMotion(void) {
    D_00633728 = 0;
    D_00633720 = 0;
    D_00633724 = 0;
}

int DeleteStreamMotionManager(void)
{
    unsigned int p = D_00633718;
    unsigned int q = D_0063371C;
    unsigned int end = p + 0x1000;
    int r;
    if (q < p)
        q += 0x28000;
    r = 1;
    if (!(q < p) && (int)q < (int)end)
        r = 0;
    return r;
}

