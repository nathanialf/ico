/* src/cod/13A8E8.c */

#include "matching.h"

extern void func_00202208(int);
extern void func_00203AA0(int);
extern void func_00193848(int);
extern int func_0017B230(int);
extern void func_00193860(int);
extern void func_00193818(int);

void func_0023A8E8(volatile int a0) {
    int x = a0;
    VOLATILE_RELOAD_CALL(a0, func_00202208);
    func_00203AA0(1);
    func_00193848(a0);
    while (func_0017B230(0x32) == 0) {
        func_00203AA0(1);
    }
    func_00203AA0(0xB4);
    func_00193860(a0);
    VOLATILE_RELOAD_CALL(a0, func_00193818);
    func_00203AA0(0x3C);
    func_00193818(a0);
}
