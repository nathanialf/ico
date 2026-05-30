#include "regpin.h"
extern void func_0017B258(int x);

typedef void (*Fn)(int *buf, int a2);

void func_001AE948(int **self, int a1, int a2)
{
    int buf[2];
    register Fn fn;  /* v1 */
    register Fn next; /* v0 */
    buf[0] = a1;
    buf[1] = 0;
    fn = (Fn)self[0];
    if (fn == 0) goto out;
    do {
        fn(buf, a2);
        self += 2;
        next = (Fn)self[0];
        fn = next;
    } while (next);
out:
    func_0017B258(0x169);
}
