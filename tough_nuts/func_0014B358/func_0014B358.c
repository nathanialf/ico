/* func_0014B358 — float array index, stride 4.
 *   return D_002924B0[a0];   // (float[])
 *
 * Same la-macro 64-bit failure as func_00105278. The leaf returns the
 * loaded float in $f0 via `lwc1`.
 */
extern float D_002924B0[];

float func_0014B358(int a0)
{
    return D_002924B0[a0];
}
