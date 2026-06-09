#include "common.h"

extern void *InitParticleLayoutGeo(void);

void itouGFlagInit(void) {
    void *r = InitParticleLayoutGeo();
    **(int **)((char *)r + 0x60) = 1;
}

extern void effect_end_func(void);

void itouGflagLoad(void) {
    effect_end_func();
}

void itouGflagSave(void) {
    effect_end_func();
}

void func_00195B80(void) {
}

extern float func_00118048(float a0);

void func_00195B88(float *quat, float m[4][4]) {
    float tr, s, t;

    tr = m[0][0] + m[1][1] + m[2][2];
    if (tr > 0.0f) {
        s = func_00118048(tr + 1.0f);
        quat[3] = s * 0.5f;
        t = 0.5f / s;
        quat[0] = (m[1][2] - m[2][1]) * t;
        quat[1] = (m[2][0] - m[0][2]) * t;
        quat[2] = (m[0][1] - m[1][0]) * t;
    } else {
        int nxt[3] = {1, 2, 0};
        int i, j, k;
        i = 0;
        if (m[1][1] > m[0][0]) i = 1;
        if (m[2][2] > m[i][i]) i = 2;
        j = nxt[i];
        k = nxt[j];
        s = func_00118048((m[i][i] - (m[j][j] + m[k][k])) + 1.0f);
        quat[i] = s * 0.5f;
        if (s != 0.0f) {
            t = 0.5f / s;
        } else {
            t = 0.0f;
        }
        quat[3] = (m[j][k] - m[k][j]) * t;
        quat[j] = (m[i][j] + m[j][i]) * t;
        quat[k] = (m[i][k] + m[k][i]) * t;
    }
}
