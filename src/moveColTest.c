/* src/moveColTest.c — __FILE__ anchor at .rodata 0x00619D98
 *
 * TU range: single function at 0x001E6968 (size 0x6C).
 * The 4-byte gap before the next TU at 0x001E69D8 is alignment padding
 * supplied by the linker --gap-fill.
 */

const char D_00619D98[24] = "src/moveColTest.c";
const char D_00619DB0[24] = "PUSH R3 TO BORN SPIDER.";

extern int D_00632010;
extern short *func_0013A0F8(int handle, int size, char *file, int line);
extern int func_00264D60(void);

short *func_001E6968(int a0, int *self)
{
    short *r = func_0013A0F8(D_00632010, 12, (char *)D_00619D98, 0x1C);
    *(int *)r = self[0x30 / 4];
    r[2] = (short)func_00264D60();
    r[3] = (short)func_00264D60();
    r[4] = (short)func_00264D60();
    r[5] = 0;
    return r;
}
