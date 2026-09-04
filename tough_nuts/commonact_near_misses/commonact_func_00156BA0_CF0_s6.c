extern void *subCommonIdle__56b(int a0) __asm__("subCommonIdle");
extern float _GetDirection(void *a0);
extern int RoundDegGV(int a0);
extern void memset(void *a0, int a1, int a2);
extern void func_001945B8(void *a0, float f);
extern int ContinueCorrectPosition__56b(void *a0) __asm__("ContinueCorrectPosition");
extern void InitCameraEditor(int a0, void *a1, int a2, int a3, int a4, float f);
extern void ChangeMailInLadder__56b(void *buf, void *obj) __asm__("ChangeMailInLadder");
extern void BoxBarSoundOn__56b(void *a0, int a1) __asm__("BoxBarSoundOn");
extern void _ACTWait__56b(int a0) __asm__("_ACTWait");
extern float D_00630C30;
extern float D_00630C34;

static __inline__ void mailDispHelper__56b(void *self) {
    int buf20[4];
    ChangeMailInLadder__56b(buf20, self);
    dispPlane__p4(self, buf20);
}

void func_00156BA0(volatile int a0) {
    int buf10[4];
    int lim = 0x12;
    int j = 0;
    int i = 0;
    float r = _GetDirection(subCommonIdle__56b(a0));
    float A = D_00630C30;
    float k0 = 180.0f;
    float d = A;
    float k = k0;
    int n = (int)(r / A * k0);
    for (;;) {
        float v;
        memset(buf10, 0, 0x10);
        i++;
        *(float *)&buf10[2] = 1.0f;
        v = (float)RoundDegGV(n + j) * d / k;
        j += 5;
        func_001945B8(buf10, v);
        InitCameraEditor(ContinueCorrectPosition__56b((void *)a0), buf10, 0xFF, 0,
                         0xFF, 200.0f);
        dispPlane__p4((void *)a0, buf10);
        if (i % lim == 0) {
            mailDispHelper__56b((void *)a0);
            BoxBarSoundOn__56b((void *)a0, 0x13A);
        }
        _ACTWait__56b(1);
    }
}

void func_00156CF0(volatile int a0) {
    int buf10[4];
    int lim = 0x12;
    int j = 0;
    int i = 0;
    float r = _GetDirection(subCommonIdle__56b(a0));
    float A = D_00630C34;
    float k0 = 180.0f;
    float d = A;
    float k = k0;
    int n = (int)(r / A * k0);
    for (;;) {
        float v;
        memset(buf10, 0, 0x10);
        i++;
        *(float *)&buf10[2] = 1.0f;
        v = (float)RoundDegGV(n + j) * d / k;
        j += 5;
        func_001945B8(buf10, v);
        InitCameraEditor(ContinueCorrectPosition__56b((void *)a0), buf10, 0xFF, 0,
                         0xFF, 200.0f);
        dispPlane__p4((void *)a0, buf10);
        if (i % lim == 0) {
            mailDispHelper__56b((void *)a0);
            BoxBarSoundOn__56b((void *)a0, 0x13A);
        }
        _ACTWait__56b(1);
    }
}
