/* src/cod/081FB0.c — func_00181FB0 */

extern char D_0055A568[];
extern void func_001A6E28(char *a0);

void func_00181FB0(char *self, int key, float f12, float f13, float f14)
{
    int i = 0;
    int *p = (int *)(self + 0x28);
    do {
        if (*p == key) {
            char *slot = self + (i * 0x1C + 0x28);
            *(float *)(slot + 0x8) = f12;
            *(float *)(slot + 0xC) = f14;
            *(float *)(slot + 0x10) = f13;
            *(int *)(slot + 0x4) = 0;
            return;
        }
        i++;
        p = (int *)((char *)p + 0x1C);
    } while (i < 0x14);
    return func_001A6E28(D_0055A568);
}
