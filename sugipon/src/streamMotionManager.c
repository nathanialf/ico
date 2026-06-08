#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _infoUpdate);

extern void func_002604B8(char *dst, char *src, int n);

void PlayStreamMotion(int *idx_p, char *dst, int size, char *src, int amt)
{
    int old_idx = *idx_p;
    int new_idx = old_idx + amt;
    *idx_p = new_idx;
    if (new_idx >= size) {
        int overflow = new_idx - size;
        int first_chunk = amt - overflow;
        *idx_p = overflow;
        func_002604B8(dst + old_idx, src, first_chunk);
        func_002604B8(dst, src + first_chunk, *idx_p);
        return;
    }
    func_002604B8(dst + old_idx, src, amt);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", ClearStreamMotionEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _deleteStreamMotionManager);

extern int D_0062B9EC;

void GetStreamMotionData(void) {
    D_0062B9EC = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _transRingBuf);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", ExecStreamMotionManager);

extern unsigned char D_00706DA8[];
extern char D_00612F68[];
extern void debug_assertMessage(char *p);

int StandbyStreamMotion(int idx)
{
  int *entry;
  entry = ((char *) D_00706DA8) - (-(idx * 0x18));
  if (((int *) entry)[0xC / 4] < 0)
  {
    debug_assertMessage(D_00612F68);
    return 4;
  }
  return ((int *) (((char *) D_00706DA8) + (idx * 0x18)))[0x8 / 4];
}

void StopStreamMotion(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", DeleteStreamMotionManager);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
} S_00706DA8;  /* stride 0x18 */

/* end struct shapes */
