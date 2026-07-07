extern void debug_assertMessage();
extern void func_001AAD00(char *a0, int a1);
extern void execEff(void *a0, int a1);
extern void CopyMotionWithNodeHrc(void *a0);
extern char D_00612130[], D_0062D650[];

void getMotionGeometry(void *a0) {
    char *s = *(char **)((char *)a0 + 0x15C) + 0x460;
    int m;
    if (*(int *)(s + 0x1AC) == -1) {
        debug_assertMessage(D_00612130);
        func_001AAD00(D_00612100, 0x2E3);
        func_00260380(D_00612100, 0x2E3, D_0062D650);
    }
    execEff(a0, 0);
    execEff(a0, 1);
    m = *(int *)(s + 0x68);
    *(int *)(s + 0x1B8) = 0;
    if (m < 9) {
        if (m < 7) {
            return;
        }
    } else if (m != 0x10) {
        return;
    }
    {
        char *e = D_0055DA10 - (-(*(int *)(s + 0x30) * 0x190));
        if (*(int *)(e + 0x130) == 0) {
            return;
        }
    }
    CopyMotionWithNodeHrc(a0);
}


