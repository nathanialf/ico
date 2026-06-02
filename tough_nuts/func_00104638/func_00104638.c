/* func_00104638 (geometryManager) — rc2 seed (permuter, 2026-06-01).
 * Lever: declare `min` and load D_00630908 LOOP-CARRIED (at the loop tail,
 * read-before-assign), which makes gcc treat min as a stable $f1 var AND nops
 * the bc1f delay slot (min not loaded before the branch). Fixes rc3->rc2. The
 * 2 residual diffs are the min-load POSITION: loop-tail (built) vs else-block
 * (expected). Need: min load in the else block keeping the loop-carried reg
 * stability. */
extern float D_00630904;
extern float D_00630908;

int func_00104638(float *a0, int *a1)
{
    int ret = 0;
    int i;
    float min;
    float max = D_00630904;
    for (i = 2; i >= 0; i--) {
        float v = *a0;
        if (v < max) {
            *a0 = max;
            ret = 1;
            *a1 = 0;
        } else if (min < v) {
            *a0 = min;
            ret = 1;
            *a1 = 0;
        }
        a1++;
        min = D_00630908;
        a0++;
    }
    return ret;
}
