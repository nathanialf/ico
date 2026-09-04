/* Vendor TU: libmpeg.a(bit.o) - 0x256BF8..0x256DF8. */
#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

void _extrainfo(void) {
    while (_nextBit(1)) {
        _flushBuf(8);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_256BF8", func_00256C30);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_256BF8", _groupOfPicturesHeader);

