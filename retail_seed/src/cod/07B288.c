/* src/cod/07B288.c — func_0017B288 */

extern unsigned char D_0028A520[];

void func_0017B288(int bit_idx)
{
    D_0028A520[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
}
