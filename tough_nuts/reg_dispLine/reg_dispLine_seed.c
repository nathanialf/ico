extern void dpk_SwapBuffer(void);
extern void dpk_Init(int a0, void *a1, int a2);
extern int dl_GetPri(void);
extern int D_0054FBE0[];

int reg_dispLine(void) {
    dpk_SwapBuffer();
    dpk_Init(2, D_0054FBE0, 4);
    return dl_GetPri();
}
