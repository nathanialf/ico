extern void _OrientXZGV(float *a0, int a1, int a2);
extern void dispPlane(void *a0, float *a1);
extern int func_00143DE0(void *a0, int a1, int a2, float *a3, float a4, float a5);
extern int _RotyGV(float *a0, float *a1);
extern int MoveChestForCatchBoy(void *a0);
extern void ACTGameView_Loop(void);
extern void BoxBarSoundOn(void *a0, int a1);
extern unsigned int _ACTWait(int a0);

void func_0015F8A0(int *volatile self) {
    float buf[8];
    int p, r0, r1, mode, ang, r;

    p = *(int *)((char *)self + 0x164) + 0x100;
    r0 = ContinueCorrectPosition(D_00629DE8);
    r1 = ContinueCorrectPosition((int)self);
    _OrientXZGV((float *)p, r0, r1);
    dispPlane((void *)self, (float *)p);

    while (1) {
        r = func_00143DE0((void *)self, D_00629DE8, 45, &buf[4], 170.0f, 100.0f);
        if (r == 0) {
            mode = 0;
        } else {
            ang = _RotyGV(&buf[4], subCommonIdle((void *)D_00629DE8));
            ang = __builtin_abs(ang);
            mode = 2;
            if (ang <= 89) {
                mode = 1;
            }
        }
        if (mode < 3 && mode != 0) {
            if (MoveChestForCatchBoy((void *)self) != 0) {
                ACTGameView_Loop();
                while (1) {
                    BoxBarSoundOn((void *)self, 0x14D);
                    _ACTWait(1);
                }
            }
        }
        BoxBarSoundOn((void *)self, 0x14E);
        _ACTWait(1);
    }
}
extern void _OrientXZGV(float *a0, int a1, int a2);
extern void dispPlane(void *a0, float *a1);

void func_00163830(volatile unsigned int a0)
{
    volatile int local;
    char *m;
    int r0, r1;
    m = (char *)(*(int *)(a0 + 0x164)) + 0x100;
    r0 = ContinueCorrectPosition(D_00629DE8);
    r1 = ContinueCorrectPosition(a0);
    _OrientXZGV((float *)m, r0, r1);
    dispPlane((void *)a0, (float *)m);
    BoxBarSoundOn((void *)a0, 0x142);
    for (;;) {
        int s;
