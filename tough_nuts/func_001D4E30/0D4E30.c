/* src/cod/0D4E30.c — func_001D4E30 */

extern int D_00565060[];
extern int D_004C49A8[];

void func_001D4E30(int target)
{
    int *src = &D_00565060[0x134 / 4];
    int *dst = D_004C49A8;
    int i;
    for (i = 0x43D; i >= 0; i--) {
        if (*src == target) {
            *dst = 0;
        }
        dst++;
        src += 0x190 / 4;
    }
}
