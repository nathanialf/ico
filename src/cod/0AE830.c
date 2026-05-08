extern void func_00105F00(int a0, int *p);
extern unsigned short D_004B3D50[];
extern char D_00275860[];

int func_001AE830(int a0)
{
    if (D_004B3D50[1] != 0) {
        func_00105F00(a0, (int *)((char *)D_004B3D50 + 0x10));
        return D_004B3D50[2];
    }
    func_00105F00(a0, (int *)D_00275860);
    return 4;
}
