extern int DebugDisp1CollisionWithColor(void *a0, int code);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);

void GetEyeDirection(float *out, char *obj) {
    int c = DebugDisp1CollisionWithColor(obj, 0x23);
    int k = *(int *)(obj + 0xC);
    *(int *)&out[0] = 0;
    if (k == 4) {
        out[1] = -1.0f;
    } else {
        out[1] = 1.0f;
    }
    *(int *)&out[2] = 0;
    *(int *)&out[3] = 0;
    sceVu0ApplyMatrix(out, (void *)(*(int *)(*(int *)(obj + 0x15C) + 0xC) + (c << 6)), out);
}

