#include "matching.h"
#include "regpin.h"

extern int func_0018B0A0(void);

int func_0023C17C(void)
{
    register int v1;
    int v0_local;
    v1 = func_0018B0A0();
    if (v1 == 3) goto L1;
    if (v1 != 9) {
        v1 = 0;
        goto L2;
    }
    v1 = 0;
L1:
    v1 = -1;
L2:
    v0_local = -1;
    if (v1 != 0) v0_local = 0;
    return v0_local;
}
