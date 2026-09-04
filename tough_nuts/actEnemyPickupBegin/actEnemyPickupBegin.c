void actEnemyPickupBegin(volatile unsigned int a0)
{
    void _ACTWait(int a0);
    void BoxBarSoundOn(void *a0, int a1);
    char *p = *(char **)(a0 + 0x164);
    char *g, *sub;
    void *r0, *r1;
    float b10[4];
    float buf20[4];
    float vec[4];
    float buf40[16];
    float buf80[4];
    float m;
    int flag = 0;

    *(long long *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x208) &= ~4LL;
    r0 = (void *)ContinueCorrectPosition((int)a0);
    _OrientXZGV(b10, (int)&D_0027E900, (int)r0);
    *(char **)(p + 0x14) = makeCollisionBlockTable;
    if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x1DC) != 3) {
        r0 = (void *)ContinueCorrectPosition(D_00629DE4);
        r1 = (void *)ContinueCorrectPosition((int)a0);
        _OrientXZGV((float *)(p + 0x100), (int)r0, (int)r1);
        dispPlane((void *)a0, (float *)(p + 0x100));
    }
    for (;;) {
        *(long long *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x208) &= ~4LL;
        if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x1DC) == 3) {
            if (*(int *)(*(char **)(D_00629DE4 + 0x164) + 0x30) == 0x5B) {
                *(int *)(*(char **)(a0 + 0x15C) + 0x540) = 0;
                *(int *)(*(char **)(a0 + 0x15C) + 0x370) = 0;
            } else {
                func_0015F2A8((int *)a0);
            }
        }
        ActOrientTest(buf20, (void *)a0, 0x16);
        vec[0] = ((float *)ContinueCorrectPosition(D_00629DE4))[0];
        vec[1] = ((float *)ContinueCorrectPosition(D_00629DE4))[1];
        vec[2] = ((float *)ContinueCorrectPosition(D_00629DE4))[2];
        if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x1DC) == 3) {
            r0 = (void *)ContinueCorrectPosition(D_00629DE4);
            sceVu0SubVector(buf80, r0, buf20);
            r0 = (void *)subCommonIdle((void *)a0);
            _OrientGV(buf40, r0);
            buf80[3] = 0.0f;
            sceVu0ApplyMatrix(buf80, buf40, buf80);
            if (buf80[0] < 0.0f) {
                if (!(-buf80[0] < 100.0f)) {
                    goto after;
                }
            } else {
                if (!(buf80[0] < 100.0f)) {
                    goto after;
                }
            }
            if (buf80[1] < 0.0f) {
                if (!(-buf80[1] < 100.0f)) {
                    goto after;
                }
            } else {
                if (!(buf80[1] < 100.0f)) {
                    goto after;
                }
            }
            if (!(-300.0f < buf80[2])) {
                goto after;
            }
            if (buf80[2] < 200.0f) {
                flag = 1;
            }
        } else {
            _DistSqGV((void *)a0, vec);
            m = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x1D8) * 45.0f;
            m *= *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x1D8) * 45.0f;
            if (vec[2] < m) {
                flag = 1;
            }
        }
    after:
        if (GetDifferenceFromWallUpperPlane((void *)a0) && flag) {
            iosOmSendMail(D_00629DE4, 0x150, (void *)a0);
        }
        if (DisableChangeRootUpdateMode((void *)a0)) {
            r0 = (void *)ContinueCorrectPosition(D_00629DE4);
            r1 = (void *)ContinueCorrectPosition((int)a0);
            _OrientXZGV(vec, (int)r0, (int)r1);
            funcCommonFallDircorrect((void *)a0, vec);
        }
        g = *(char **)(D_00629DE4 + 0x164);
        if (*(int *)(g + 0x30) == 0x5B) {
            sub = *(char **)(g + 0x670);
            if (*(int *)(sub + 0x224) == (int)a0) {
                if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x670) + 0x1DC) == 3) {
                    if (*(int *)(sub + 0xCC) > 0) {
                        BoxBarSoundOn((void *)a0, 0x156);
                    } else {
                        BoxBarSoundOn((void *)a0, 0x157);
                    }
                } else {
                    BoxBarSoundOn((void *)a0, 0x154);
                }
            } else {
                BoxBarSoundOn((void *)a0, 0xB4);
            }
        } else {
            BoxBarSoundOn((void *)a0, 0xB4);
        }
        _ACTWait(1);
    }
}
