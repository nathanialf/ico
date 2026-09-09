#include "common.h"

extern unsigned char D_002A50C0[];
extern int D_0028F4CC[];
extern int D_0029B9D0[];
extern int D_0063AA00;
extern int D_0063AA04;
extern int before_stage_no;
extern int gamesysVersionDiff;
extern int stage_no;
extern void memset(void *dst, int c, int n);
extern int func_001B6CA0(void *, void *, int);
extern int gamesysMemoryHandlerRead(void *, void *, int);
extern void Boy_Init(void);
extern void Hint_Init(void);
extern void StageOrientInit(void);
extern void gamesysObjInfoInit(void);
extern void Generator_Init(void);
extern void warpGirlInit(void);
extern void itouGFlagInit();
int gflagChk(int bit_idx);
void gflagOn(int bit_idx);

void gflagInit(void)
{
    int keep = gflagChk(0x17B);

    memset(D_002A50C0, 0, 0x32);
    before_stage_no = 0;
    if (keep != 0) {
        gflagOn(0x17B);
    }
    Boy_Init();
    Hint_Init();
    StageOrientInit();
    gamesysObjInfoInit();
    Generator_Init();
    warpGirlInit();
    D_0028F4CC[0] = 0;
    memset(D_0029B9D0, 0, 0x14);
    gamesysVersionDiff = 0;
    itouGFlagInit();
}

void gflagSave(void *fp)
{
    D_0063AA04 = stage_no;
    func_001B6CA0(fp, &D_0063AA04, 4);
    func_001B6CA0(fp, &D_0063AA00, 4);
    func_001B6CA0(fp, D_002A50C0, 0x32);
}

void gflagLoad(void *fp)
{
    gamesysMemoryHandlerRead(fp, &D_0063AA04, 4);
    gamesysMemoryHandlerRead(fp, &D_0063AA00, 4);
    gamesysMemoryHandlerRead(fp, D_002A50C0, 0x32);
}

int gflagChk(int bit_idx)
{
    return (D_002A50C0[bit_idx >> 3] >> (bit_idx & 7)) & 1;
}

void gflagOn(int bit_idx)
{
    D_002A50C0[bit_idx >> 3] |= 1 << (bit_idx & 7);
}

void gflagOff(int bit_idx)
{
    D_002A50C0[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
}
