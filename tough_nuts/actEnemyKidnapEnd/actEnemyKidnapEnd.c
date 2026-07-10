extern int iosPadStickCameraCoord(void *a0, int a1, int a2, void *a3);
extern int EntryEnemyFootPrint(void *a0);
extern void iosPadNormalizeStick(void *a0);
extern void iosPadActRequest(void *a0, void *a1, int a2, int a3, int a4, int a5);
extern int GetOrientOfWallOfGObj(void *a0, void *a1);
extern void actBoyRun(void *a0, void *a1);
extern void BeforeFunc2(void *a0, void *a1);
extern void BoxBarSoundOff(void *a0, int a1, int a2, int a3);
extern int ForMotionViewer_GetCurrentAnimationFrame(void *a0, int a1);
extern void *D_00629E00;
extern void *D_00629E10;
extern float D_00628FDC, D_00628FE0, D_00628FE4, D_00628FE8, D_00628FEC, D_00628FF0, D_00628FF4;

void actEnemyKidnapEnd(volatile unsigned int a0)
{
    void _ACTWait(int a0);
    void BoxBarSoundOn(void *a0, int a1);
    int i, n;
    char *p = *(char **)(a0 + 0x164);
    char *pca = p + 0x2C8;
    int c21 = 0;
    char *prq = p + 0x328;
    char *pwl = p + 0x1D8;
    int c30 = 0;
    float vec[3];
    int buf[4];
    int timer = 0;
    float f2;

    iosPadStickCameraCoord(pca, 0, 1, pwl);
    for (;;) {
        void *self = (void *)a0;
        n = *(int *)(*(int *)((char *)self + 0x15C) + 0x88);
        c21++;
        i = 0;
        if (i < n) {
            do {
                EntryEnemyFootPrint(self);
                i++;
            } while (i < n);
        }
        if ((unsigned int)(*(unsigned long long *)(p + 0x18) >> 43) & 1) {
            if ((void *)a0 == D_00629E00) {
                iosPadStickCameraCoord(pca, 0, 0, pwl);
                iosPadNormalizeStick(pca);
                iosPadActRequest(pca, prq, 0, 2, 2, 0);
                *(int *)(p + 0x330) = GetOrientOfWallOfGObj(buf, (void *)a0);
                actBoyRun(buf, prq);
                if (D_00628FDC < *(float *)(p + 0x33C)) {
                    BeforeFunc2(vec, prq);
                    *(float *)(p + 0x100) = vec[0];
                    *(float *)(p + 0x104) = vec[1];
                    *(float *)(p + 0x108) = vec[2];
                }
            } else if ((void *)a0 == D_00629E10) {
                iosPadStickCameraCoord(pca, 0, 1, pwl);
            } else {
                iosPadStickCameraCoord(pca, 0, 1, pwl);
            }
        }
        f2 = *(float *)(p + 0x33C);
        if (D_00628FE0 < f2) {
            c21 = 0;
        }
        if (!(D_00628FE0 < f2)) {
            c30 = 0;
        } else {
            c30++;
            if (!(f2 < D_00628FE4) && !(*(int *)(p + 0x2D0) & 0x20)) {
                c30 = 0;
            }
        }
        if (!(D_00628FE8 < f2)) {
            timer = 0;
        } else if (f2 < D_00628FEC) {
            timer = 0;
        } else if (*(int *)(p + 0x2D0) & 0x20) {
            timer = 0;
        } else {
            timer++;
        }
        vec[0] = *(float *)(p + 0x100);
        vec[1] = *(float *)(p + 0x104);
        vec[2] = *(float *)(p + 0x108);
        BoxBarSoundOff((void *)a0, c21, c30, timer);
        switch (*(int *)(p + 0x30)) {
        case 1:
            BoxBarSoundOn((void *)a0, 0xB4);
            break;
        case 2:
            if (D_00628FF0 < *(float *)(p + 0x33C)) {
                if (*(float *)(p + 0x33C) < D_00628FF4 || (*(int *)(p + 0x2D0) & 0x20)) {
                    if (c30 >= 4) {
                        if (ForMotionViewer_GetCurrentAnimationFrame((void *)a0, 0x200)) {
                            BoxBarSoundOn((void *)a0, 0xA7);
                        } else {
                            BoxBarSoundOn((void *)a0, 0xA6);
                        }
                    }
                }
            }
            break;
        case 3:
            BoxBarSoundOn((void *)a0, 0xAB);
            break;
        case 38: {
            int v = *(int *)(p + 0x32C) - 0x80;
            if (v > 100) {
                BoxBarSoundOn((void *)a0, 0x131);
            } else if (v < -100) {
                BoxBarSoundOn((void *)a0, 0x130);
            } else {
                BoxBarSoundOn((void *)a0, 0x136);
            }
            break;
        }
        default:
            break;
        }
        _ACTWait(1);
    }
}
