extern void func_001AD768(char *buf, int sz);
extern void func_00263FF0(char *buf, int sz, int *list);
extern char D_00558E10[];
extern int D_00632398[];

void func_00164FD0(volatile unsigned int a0)
{
    volatile int local;
    func_001AD768(D_00558E10, 0xAF3);
    func_00263FF0(D_00558E10, 0xAF3, D_00632398);
}
