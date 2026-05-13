/* src/cod/0E8598.c — func_001E8598 */

extern void func_001E6D68(int a0);
extern void func_001A6E28(int a0);
extern unsigned char D_007097F0[];
extern unsigned char D_00619E40[];

void func_001E8598(int idx)
{
    int *entry;
    if (idx < 0) return;
    entry = (int *)((char *)&D_007097F0[0] + idx * 0x18);
    if (*entry != 0) {
        func_001E6D68(entry[5]);
        return;
    }
    func_001A6E28((int)D_00619E40);
}
