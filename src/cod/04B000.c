#include "matching.h"

extern int func_001F40C8(int a0);
extern char D_006124F8[];

int func_0014B000(int a0)
{
    char *base;
    int idx;
    int rv;
    if (a0 == 0) goto done;
    base = D_006124F8;
    MATERIALIZE(base);
    idx = func_001F40C8(a0);
    base += idx * 0x24;
    rv = *(int *)(base + 0x1C);
    goto end;
done:
    rv = 0;
end:
    return rv;
}
