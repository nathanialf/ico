#include "mv_defs.h"
#include "debug.h"
#include "mv_sub.h"
#include <string.h>

inline int copy2area(char *dst0, int n0, char *dst1, int n1, char *src0, int m0, char *src1, int m1)
{
    int b = m0 + m1;
    if (n0 + n1 < b) {
        return 0;
    }
    if (m0 >= n0) {
        memcpy(dst0, src0, n0);
        memcpy(dst1, src0 + n0, m0 - n0);
        memcpy(dst1 + m0 - n0, src1, m1);
    } else if (m1 >= n0 - m0) {
        memcpy(dst0, src0, m0);
        memcpy(dst0 + m0, src1, n0 - m0);
        memcpy(dst1, src1 + n0 - m0, m1 - (n0 - m0));
    } else {
        memcpy(dst0, src0, m0);
        memcpy(dst0 + m0, src1, m1);
    }
    return b;
}

void ErrMessage(char *mes)
{
    debug_StdPrintfDummy("[ Error ] %s\n", mes);
}
