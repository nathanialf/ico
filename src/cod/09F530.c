#include "matching.h"
#include "ico/types.h"

extern void func_00103018(int *self);

/* 8-byte constant at D_006323C0 (uint 0, with a 0xFF top byte at +7).
 * Modelled as its real binary layout { uint; uchar[3]; uchar } so ee-gcc
 * folds the gp_rel symbol into the unaligned ldl/ldr (ldl %gp_rel(D+7);
 * ldr %gp_rel(D)) instead of materialising the base — a single packed
 * long long member would drive the base-materialising DI-load path. */
typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } FcBlk8;
extern FcBlk8 D_006323C0;

void func_0019F530(int *self)
{
    func_00103018(self);
    *(FcBlk8 *)(int)((GObj *)self)->p_15C = D_006323C0;
}
