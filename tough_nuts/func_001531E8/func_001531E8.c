/* fumi/src/boyact.c — func_001531E8 seed (rc7, §3.3 beql park).
   D_006A45A0[0]=a0?a0->h8:0; D_006A45A0[1]=a1?a1->h8:0 (D_006A45A0 is long long[],
   access via (int*)). Residual: ROM's FIRST conditional is `beql` (branch-likely,
   annulled lui %hi(D) in delay); gcc emits `beq` — §3.3 documents no source fix.
   Plus D-base coloring (ROM reuses a0; gcc uses v0). Park/permuter-class. */
void func_001531E8(int *a0, int *a1) {
    if (a0 != 0) {
        ((int *)D_006A45A0)[0] = a0[2];
    } else {
        ((int *)D_006A45A0)[0] = 0;
    }
    if (a1 != 0) {
        ((int *)D_006A45A0)[1] = a1[2];
    } else {
        ((int *)D_006A45A0)[1] = 0;
    }
}
