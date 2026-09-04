extern void debug_ClearFontWindow(void);
extern void func_001A3C38(int a0);
extern int D_00632C90;
extern int D_00632C94;
extern int D_00632C98;
extern int D_00632C9C;
extern int D_00632CA0;
extern int D_00632CA4;
extern int D_00632D44;

void func_001A3340(void)
{
    debug_ClearFontWindow();
    D_00632C90 = 0;
    D_00632C94 = 0;
    D_00632C98 = 0;
    D_00632C9C = 0;
    D_00632CA0 = 0;
    D_00632CA4 = 0;
    D_00632D44 = 0;
    {
        int v = 0x82;
        *(volatile int *)0x10000010 = v;
        *(volatile int *)0x10000810 = v;
        func_001A3C38(v);
    }
}
