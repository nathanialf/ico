/* func_00170CB8 — near-miss rc30 (from rc59-ish). Structure recovered.
 * Residual: gcc CSEs the object-chain base (*(*(obj+0x15C)+0xC)+n) into ONE
 * reg + offsets 0x30/0x34/0x38; ROM RECOMPUTES the 0x15C+0xC derefs per float.
 * points-to keeps local b1[]/b2[] stores from aliasing the global-object loads
 * even under -fno-strict-aliasing, so gcc won't reload. Tried: cache d temp,
 * inline D_00629DE8 direct, float* pointer stores (rc50 worse). Need a
 * CSE-defeat that forces per-float reload of the 0x15C/0xC chain.
 * §2.7 dead-home self=uninit -> sw $2,0(sp). abs via if(t<0)t=-t (bc1tl). */
extern int DebugDisp1CollisionWithColor(void *, int);
extern float ClearHandCameraCorrect(void *, void *);
extern void *D_00629DE8, *D_00629DE4;
void func_00170CB8(float *a0, float *a1) {
    volatile int self;
    int uninit;
    float b1[4];
    float b2[4];
    int n;
    float t;
    self = uninit;
    n = DebugDisp1CollisionWithColor(D_00629DE8, 0x12) << 6;
    b1[0] = *(float *)((char *)*(int *)((char *)*(void **)((char *)D_00629DE8 + 0x15C) + 0xC) + n + 0x30);
    b1[1] = *(float *)((char *)*(int *)((char *)*(void **)((char *)D_00629DE8 + 0x15C) + 0xC) + n + 0x34);
    b1[2] = *(float *)((char *)*(int *)((char *)*(void **)((char *)D_00629DE8 + 0x15C) + 0xC) + n + 0x38);
    n = DebugDisp1CollisionWithColor(D_00629DE4, 0x2) << 6;
    b2[0] = *(float *)((char *)*(int *)((char *)*(void **)((char *)D_00629DE4 + 0x15C) + 0xC) + n + 0x30);
    b2[1] = *(float *)((char *)*(int *)((char *)*(void **)((char *)D_00629DE4 + 0x15C) + 0xC) + n + 0x34);
    b2[2] = *(float *)((char *)*(int *)((char *)*(void **)((char *)D_00629DE4 + 0x15C) + 0xC) + n + 0x38);
    *a0 = ClearHandCameraCorrect(b1, b2);
    t = b1[1] - (b2[1] - 40.0f);
    if (t < 0.0f) t = -t;
    *a1 = t;
}
