#include "common.h"

typedef struct {
    char pad[0x194];
} DispBuf;

extern DispBuf D_005F5DD0[];
extern char D_0063C090[];
extern char *GetDataFileName2();
extern int sprintf(char *buf, char *fmt, ...);
extern char D_0063C098[]; /* "DFDATAS" */
extern char D_0063C0A0[]; /* "DF" */
extern char D_0063C0A8[]; /* "DATAS" */
extern char D_0063C0B0[]; /* "BIN" */
extern char D_00623150[]; /* "%s/%s.%s" */
extern char D_00729E30[];

int GetDataFileName(int a0)
{
    int buf[0x40];
    void *p;
    if (a0 == -1) {
        p = D_0063C090;
    } else {
        p = (void *)&D_005F5DD0[a0];
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

    sprintf(D_00729E30, D_00623150, dir, name, ext);

    return D_00729E30;
}
