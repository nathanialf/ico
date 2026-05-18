#include "matching.h"

typedef struct {
    char _0[0x8];
    int field_8;
    char _c[0x28];
} R34;

extern R34 D_004CAEC0[];

int func_00205A98(int *self)
{
    R34 *entry = &D_004CAEC0[self[8]];
    int result;
    MATERIALIZE(entry);
    if (self == 0) {
        result = 0;
    } else {
        int t = self[3];
        result = t;
        if (t == entry->field_8) result = 0;
    }
    return result;
}
