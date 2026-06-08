/* common/src/DObj.c — func_0019CAF0 seed (rc3).
   SetRootMatrixRotOffsetByDObj(a0); *(packed_ll*)(a0->0x15C) = D_0062A6A0 (ldl/ldr
   from gp-rel source, sdl/sdr to dest). Residual rc3: gcc caches &D_0062A6A0 in a
   reg (addiu a2,gp; ldl 7(a2); ldr 0(a2)) where the ROM uses gp+offset directly
   (ldl %gp_rel(D+7)(gp)). Packed STRUCT forces the base computation; aligned(1)
   scalar made it aligned ld/sd (wrong). gp-relative-direct addressing tie. */
typedef struct { long long x; } __attribute__((packed)) PackedLL_19CAF0;
extern PackedLL_19CAF0 D_0062A6A0;
extern void SetRootMatrixRotOffsetByDObj(void *a0);
void func_0019CAF0(void *a0) {
    PackedLL_19CAF0 *p;
    SetRootMatrixRotOffsetByDObj(a0);
    p = *(PackedLL_19CAF0 **)((char *)a0 + 0x15C);
    *p = D_0062A6A0;
}
