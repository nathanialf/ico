extern float _DistSqGV(void *a0, void *a1);
extern float D_006A5560[];
extern const float D_00629094;

int func_0016CF18(float *a0, float *a1, int n) {
    volatile int home;
    int uninit;
    int out;
    float *cur;
    float *op;

    out = 0;
    home = uninit;
    if (n <= 0) {
        goto copyback;
    }
    cur = a0;
    op = D_006A5560;
    do {
        float d = a1[1] - cur[1];
        int skip;
        if (d < 0.0f ? -d < 100.0f : d < 100.0f) {
            skip = _DistSqGV(a1, cur) < D_00629094;
        } else {
            skip = 0;
        }
        n--;
        if ((skip & 0xFF) == 0) {
            op[0] = cur[0];
            op[1] = cur[1];
            op[2] = cur[2];
            out++;
            op += 4;
        }
        cur += 4;
    } while (n != 0);
copyback:
    for (n = 0; n < out; n++) {
        a0[n * 4 + 0] = D_006A5560[n * 4 + 0];
        a0[n * 4 + 1] = D_006A5560[n * 4 + 1];
        a0[n * 4 + 2] = D_006A5560[n * 4 + 2];
    }
