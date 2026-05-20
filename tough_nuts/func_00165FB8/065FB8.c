/* file_off 0x065FB8 — func_00165FB8: dispatch self->_164->_670->_1DC==3 */
#include "matching.h"
#include "regpin.h"

extern void func_00163B40(int *self, int a1, int a2, int a3, unsigned int t0);
extern void func_00163EB8(int *self, int a1, int a2, int a3, unsigned int t0);

void func_00165FB8(int *self, int a1, int a2, int a3, unsigned int t0)
{
    int *p;
    int *q;
    p = (int *)self[0x164 / 4];
    q = (int *)p[0x670 / 4];
    {
        register int three REG("$3") = 3;
        if (q[0x1DC / 4] == three) {
            func_00163B40(self, a1, a2, a3, t0 & 0xFF);
        } else {
            func_00163EB8(self, a1, a2, a3, t0 & 0xFF);
        }
    }
    DEFEAT_TCO();
}
