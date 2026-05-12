/* src/cod/14E670.c — func_0024E670 */

extern int D_00552390[];
extern unsigned char D_0062EB68[16];
extern void func_00265168(unsigned char *ptr, int value);

void func_0024E670(unsigned int idx, unsigned char *ptr)
{
    if (idx < 8) {
        return func_00265168(ptr, D_00552390[idx]);
    }
    *ptr = D_0062EB68[0];
}
