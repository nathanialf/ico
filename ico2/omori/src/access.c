#include "typedef.h"
#include <stdio.h>
#include "access.h"

extern StgPre stageData[];

/* .bss, owned by access.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the path sprintf builds and this file hands back. */
static char accessPath[528];

/* Callers pass the stage and the DF flag (StageManager.c, icoMisc.c), which
   goes straight through to GetDataFileName2 in $a1.  The DEBUG build reads the
   data from the host instead and builds that path in buf; retail keeps only
   the declaration, which is the ROM's 256-byte frame (the listing's return is
   row 16 and rows 17-30 carry no code).  The host prefix is ours. */
char *GetDataFileName(int no, int isDF)
{
    char buf[256];
    char *name;

    if (no == -1) {
        name = "COMMON";
    } else {
        name = stageData[no].dataFile;
    }
#ifndef DEBUG
    return GetDataFileName2(name, isDF);
#else
    sprintf(buf, "host0:%s", GetDataFileName2(name, isDF));
    sprintf(accessPath, "%s", buf);
    return accessPath;
#endif
}

char *GetDataFileName2(char *name, int isDF)
{
    char dir[128];
    char ext[128];

    if (isDF) {
        sprintf(dir, "DFDATAS");
        sprintf(ext, "DF");
    } else {
        sprintf(dir, "DATAS");
        sprintf(ext, "BIN");
    }

    sprintf(accessPath, "%s/%s.%s", dir, name, ext);

    return accessPath;
}
