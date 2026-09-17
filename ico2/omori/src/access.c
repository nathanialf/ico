#include "common.h"
#include "typedef.h"
#include <stdio.h>

extern StgPre D_005F5D50[];
extern char D_0063C090[];
/* kept local: this TU's uses of GetDataFileName2 do not fit the prototype in access.h */
extern char *GetDataFileName2();
extern char D_0063C098[]; /* "DFDATAS" */
extern char D_0063C0A0[]; /* "DF" */
extern char D_0063C0A8[]; /* "DATAS" */
extern char D_0063C0B0[]; /* "BIN" */

/* .bss, owned by access.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the path sprintf builds and this file hands back. */
static char accessPath[528];

int GetDataFileName(int a0)
{
    /* CRUTCH: zero-code frame reservation. Nothing in the emitted body touches
       these 256 bytes, but ROM's frame carries them; the name-building debug
       block that used them compiled out. Deleting it changes the object. See
       docs/crutch_ledger.md. */
    int buf[0x40];
    void *p;
    if (a0 == -1) {
        p = D_0063C090;
    } else {
        p = (void *)D_005F5D50[a0].dataFile;
    }
    return GetDataFileName2(p);
}

char *GetDataFileName2(char *name, int isDF)
{
    char dir[128];
    char ext[128];

    if (isDF) {
        sprintf(dir, D_0063C098);
        sprintf(ext, D_0063C0A0);
    } else {
        sprintf(dir, D_0063C0A8);
        sprintf(ext, D_0063C0B0);
    }

    sprintf(accessPath, "%s/%s.%s", dir, name, ext);

    return accessPath;
}
