/* func_001019A8 — varargs forwarder to func_001013E0.
 *
 * Spill area at sp+0x58..0x88 holds $a1..$t3 in 8-byte slots; va_list
 * is intended to point to that area. ee-gcc 2.9 ships no <stdarg.h>
 * and __builtin_va_list is not a recognized typedef in this build —
 * the typedef + __builtin_next_arg pattern below compiles but emits
 * `addu a1, sp, FRAME_SIZE` (post-frame), not the desired `addiu a1,
 * sp, 0x58` (start-of-spill). Permuter / typedef-trick territory.
 */

typedef void *va_list;
#define va_start(ap, last) ((ap) = (void*)__builtin_next_arg(last))
#define va_end(ap) ((void)0)

extern void func_001013E0(int a0, va_list args);

void func_001019A8(int a0, ...)
{
    va_list args;
    va_start(args, a0);
    func_001013E0(a0, args);
    va_end(args);
}
