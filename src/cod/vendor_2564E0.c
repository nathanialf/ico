/* Vendor TU: libmpeg.a(csc.o) - 0x2564E0..0x256BF8. */
#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2564E0", _nextBit);

extern void _waitIpuIdle(void);

void _nextStartCode(void) {
    int v;
    _waitIpuIdle();
    v = (-(*(volatile int *)0x10002020 & 7)) & 7;
    if (v) _flushBuf(v);
    while (_peepBit(0x18) != 1) {
        _flushBuf(8);
    }
}

extern int D_00552700[];
extern int D_00552D80[];
extern void _extrainfo(void);

int _sliceB(void) {
    int *p = D_00552700;
    *p = _nextBit(5);
    if (_nextBit(1)) {
        int *q = D_00552D80;
        *q = _nextBit(1);
        _flushBuf(7);
        _extrainfo();
    } else {
        D_00552D80[0] = 0;
    }
    return 0;
}

extern void *D_005524A4[];
extern int D_0055263C[];
extern long long D_00552D48[];
extern long long D_00552D50[];
extern void *_dispatchMpegCallback(void *a0, void *a1);
extern void _sequenceHeader(void);
extern void _pictureHeader(void);
extern void _groupOfPicturesHeader(void);

int _nextHeader(void) {
    struct { int f0; long long f8; long long f10; } local;

    while (1) {
        _nextStartCode();
        switch ((unsigned int) _nextBit(0x20)) {
        case 0x1B3:
            _sequenceHeader();
            break;
        case 0x1B8:
            _groupOfPicturesHeader();
            break;
        case 0x100:
            _pictureHeader();
            local.f0 = 5;
            local.f8 = -1;
            local.f10 = -1;
            _dispatchMpegCallback(D_005524A4[0], &local);
            D_00552D48[0] = local.f8;
            D_00552D50[0] = local.f10;
            return D_0055263C[0];
        case 0x1B7:
            return 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2564E0", _pictureHeader);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2564E0", _extensionAndUserData);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2564E0", _pictureCodingExtension);

