/* func_00264060 — varargs forwarder to func_00265C28.
 *
 * Spill area at sp+0x50..0x78 holds $a2..$t3 in 8-byte slots; va_list
 * is intended to point to that area. Same ee-gcc 2.9 limitation as
 * cod/0019A8.c: __builtin_next_arg(last) emits a post-frame pointer,
 * target wants `addiu a2, sp, 0x50`. Park for permuter / typedef-
 * trick exploration once a working varargs idiom is found.
 */

typedef void *va_list;
#define va_start(ap, last) ((ap) = (void*)__builtin_next_arg(last))
#define va_end(ap) ((void)0)

extern void func_00265C28(int a0, int a1, va_list args);

void func_00264060(int a0, int a1, ...)
{
    va_list args;
    va_start(args, a1);
    func_00265C28(a0, a1, args);
    va_end(args);
}
