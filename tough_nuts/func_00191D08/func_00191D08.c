/* func_00191D08 — initialise three sdata words and return 0.
 *
 * Honest C of the original asm:
 *   D_00633DB4 = 0;
 *   D_00633DB8 = -1;
 *   D_00633DBC = 0;
 *   return 0;
 *
 * The "set $v0 to zero" step is emitted as `daddu $v0, $zero, $zero`
 * by the original toolchain; ee-gcc 2.96 -O2 emits `or $v0, $zero,
 * $zero` for the same intent. Same semantics, different encoding.
 */
extern int D_00633DB4;
extern int D_00633DB8;
extern int D_00633DBC;

int func_00191D08(void)
{
    D_00633DB4 = 0;
    D_00633DB8 = -1;
    D_00633DBC = 0;
    return 0;
}
