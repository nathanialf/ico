/* src/cod/164D60.c — func_00264D60 */

extern int *D_00553244;

int func_00264D60(void)
{
    int *p = D_00553244;
    int seed = p[0x58 / 4];
    seed = seed * 0x41C64E6D + 0x3039;
    p[0x58 / 4] = seed;
    return seed & 0x7FFFFFFF;
}
