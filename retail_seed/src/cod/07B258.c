/* src/cod/07B258.c — func_0017B258 */

extern unsigned char D_0028A520[];

void func_0017B258(int bit_idx)
{
    D_0028A520[bit_idx >> 3] |= 1 << (bit_idx & 7);
}
