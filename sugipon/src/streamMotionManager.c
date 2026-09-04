#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _infoUpdate);

extern void memcpy(char *dst, char *src, int n);

void PlayStreamMotion(int *idx_p, char *dst, int size, char *src, int amt)
{
    int old_idx = *idx_p;
    int new_idx = old_idx + amt;
    *idx_p = new_idx;
    if (new_idx >= size) {
        int overflow = new_idx - size;
        int first_chunk = amt - overflow;
        *idx_p = overflow;
        memcpy(dst + old_idx, src, first_chunk);
        memcpy(dst, src + first_chunk, *idx_p);
        return;
    }
    memcpy(dst + old_idx, src, amt);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", ClearStreamMotionEntry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _deleteStreamMotionManager);

extern int D_0062B9EC;

void GetStreamMotionData(void) {
    D_0062B9EC = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/streamMotionManager", _transRingBuf);

/* m2c scaffold from asm/aug6/nonmatchings/sugipon/src/streamMotionManager/ExecStreamMotionManager.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern unsigned int D_0062B9E8;
extern unsigned char D_00706DA8[];

typedef struct StreamMotionEntry {
    char _pad[0x10];
    int f10;
    char _tail[4];
} StreamMotionEntry;

extern StreamMotionEntry sm_table[] __asm__("D_00706DA8");

int ExecStreamMotionManager(void *a0)
{
    int v = D_0062B9E8;
    sm_table[v].f10 = (int)a0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x460) = v;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x4E0) = 0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x4DC) = 0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x540) = 0;
    D_0062B9E8 = v + 1;
    return v;
}


extern unsigned char D_00706DA8[];
extern char D_00612F68[];
extern void debug_StdPrintfDummy(char *p);

int StandbyStreamMotion(int idx)
{
  int *entry;
  entry = ((char *) D_00706DA8) - (-(idx * 0x18));
  if (((int *) entry)[0xC / 4] < 0)
  {
    debug_StdPrintfDummy(D_00612F68);
    return 4;
  }
  return ((int *) (((char *) D_00706DA8) + (idx * 0x18)))[0x8 / 4];
}

void StopStreamMotion(void) {
}

extern unsigned int D_0062B9F8;
extern unsigned int D_0062B9FC;

int CheckReadyStreamMotion(void) {
    unsigned int a = D_0062B9F8;
    unsigned int b = D_0062B9FC;
    int lim = a + 0x1000;
    int ret;
    int c = b < a;
    if (c) {
        b += 0x28000;
        c = b < a;
    }
    if (c)
        ret = 1;
    else {
        ret = 1;
        if ((int)b < lim)
            ret = 0;
    }
    return ret;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
} S_00706DA8;  /* stride 0x18 */

/* end struct shapes */
