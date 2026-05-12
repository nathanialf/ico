/* src/cod/0D4E30.c — func_001D4E30 */

extern unsigned char D_00565060[];
extern int D_004C49A8[];

void func_001D4E30(int target)
{
    int *entries = (int *)((char *)&D_00565060[0] + 0x134);
    int *slots = D_004C49A8;
    int i = 0x43D;
    do {
        if (*entries == target) {
            *slots = 0;
        }
        slots++;
        i--;
        entries = (int *)((char *)entries + 0x190);
    } while (i >= 0);
}
