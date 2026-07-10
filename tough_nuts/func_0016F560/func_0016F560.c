extern void *ContinueCorrectPosition(void *a0);
extern void func_00191FD0(void *a0, void *a1, void *a2);
extern float ClearHandCameraCorrect(void *a0, void *a1);
extern float HandyCamera_TargetMoveType(void *a0, void *a1);
extern int func_00191D90(void *a0, void *a1);
extern const float D_006290C0;

typedef struct {
    void *p;          /* 0x00 */
    char _4[0xC];
    char data[0x20];  /* 0x10 */
} GEnt;               /* 0x30 */

int func_0016F560(void *a0, void *a1) {
    float m0[4];
    float m1[4];
    GEnt *ent;
    int j;
    float f20, hc;

    *(float *)((char *)a0 + 0x0) = *(float *)((char *)ContinueCorrectPosition(D_00629DE4) + 0x0);
    *(float *)((char *)a0 + 0x4) = *(float *)((char *)ContinueCorrectPosition(D_00629DE4) + 0x4);
    *(float *)((char *)a0 + 0x8) = *(float *)((char *)ContinueCorrectPosition(D_00629DE4) + 0x8);
    *(float *)((char *)a1 + 0x0) = *(float *)((char *)ContinueCorrectPosition(D_00629DE8) + 0x0);
    *(float *)((char *)a1 + 0x4) = *(float *)((char *)ContinueCorrectPosition(D_00629DE8) + 0x4);
    *(float *)((char *)a1 + 0x8) = *(float *)((char *)ContinueCorrectPosition(D_00629DE8) + 0x8);
    func_00191FD0(m0, a0, a1);
    ent = (GEnt *)D_0027EE30;
    for (j = 0; j < *(int *)((char *)D_0027EE30 + 0x3230); j++) {
        if (*(int *)((char *)ent[j + 268].p + 0xC) == 4) {
            f20 = ClearHandCameraCorrect(a1, ent[j + 268].data);
            if (!(D_006290C0 < f20)) {
                hc = HandyCamera_TargetMoveType(a0, ent[j + 268].data);
                if (hc < (f20 + 100.0f) * (f20 + 100.0f)) {
                    return 0;
                }
                if (f20 < 150.0f) {
                    return 0;
                }
                func_00191FD0(m1, ent[j + 268].data, a1);
                if (func_00191D90(m0, m1) < 0x2D) {
                    return 0;
                }
            }
        }
    }
    return 1;
}


extern float RotateAccordingToStick_PatternThree(void *, void *);
extern int func_0016F560(void *, void *);
extern float D_006290C4;
extern float D_006290C8;

