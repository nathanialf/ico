/* src/cod/14E760.c — func_0024E760 */

extern int D_005523B0[];
extern unsigned char D_0062EB68[16];
extern void func_00265168(unsigned char *ptr, int value);

void func_0024E760(unsigned int idx, unsigned char *ptr)
{
    if (idx < 4) {
        return func_00265168(ptr, D_005523B0[idx]);
    }
    *ptr = D_0062EB68[0];
}
