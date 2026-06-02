extern int *D_00553244[];
extern int D_0062FC48[];
extern void func_00264060(int a0, int *a1, int a2, int a3, int t0);
extern void func_00268F08(void);

void func_00263FF0(int a0, int a1, int a2) {
    int *p = (int *)D_00553244[0];
    func_00264060(p[0xC/4], D_0062FC48, a2, a0, a1);
    func_00268F08();
}
