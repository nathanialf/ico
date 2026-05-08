extern int D_00633394;
extern int D_006333AC;
extern int D_006325B4;
extern char D_006333B8[];
extern void func_001E8AB8(int x);
extern void func_0018CAA8(int x, int y, int z);
extern void func_001A6E28(char *p);

void func_001CD490(void)
{
    func_001E8AB8(D_00633394);
    D_00633394 = -1;
    func_0018CAA8(D_006333AC, 0, 3);
    D_006325B4 = 0;
    func_001A6E28(D_006333B8);
}
