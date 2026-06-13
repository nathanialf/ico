typedef struct { char pad0[0x10]; int f10; char pad14[0x8]; } PObjA8B8Ent; /* 0x1C */
extern PObjA8B8Ent D_007112D0[][4];
extern int func_0024B0E8(int a0);

int func_0024B250(int a0, int a1) {
    int ret = 0;
    if (D_007112D0[a0][a1].f10 == 0) {
        return ret;
    }
    return func_0024B0E8(a0) == 0x3FFFF;
}
