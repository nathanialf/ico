#include "common.h"

extern int stage_no;
extern char *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
extern int SetFlag4PointFixID(void *gobj, int idx, int a2);

/* The 0x40-byte layout record CreateLayoutedGObj takes: three 16-byte vectors
   and the model id the loader resolves. 8-byte aligned (the copy is ld/sd). */
typedef union {
    float f[4];
    long long ll[2];
} WmVec;

typedef struct {
    WmVec pos;    /* 0x00 */
    WmVec rot;    /* 0x10 */
    WmVec scale;  /* 0x20 */
    int id;       /* 0x30 */
    int unk34[3]; /* 0x34 */
} WmLayout;

/* The GObj's 0x15C slot is read as an INT handle (types.h GOBJ_SUB): the int
   view may-alias the int stores below, so each store reloads it. */
typedef struct {
    int owner; /* 0x00 */
    int flag;  /* 0x04 */
} WmWork;

int InitWindMillGeo(int owner, WmLayout *src)
{
    WmLayout lay;
    char *gobj;
    char *gobj2;
    int i;

    lay = *src;
    for (i = 0; i < 4; i++) {
        if (stage_no == 101) {
            lay.id = 20;
        } else {
            lay.id = 18;
        }
        gobj = CreateLayoutedGObj(0x2E, 0x290, -1, 0, &lay, -1, 7, 0);
        ((WmWork *)*(int *)(gobj + 0x15C))->owner = owner;
        ((WmWork *)*(int *)(gobj + 0x15C))->flag = 0;
        SetFlag4PointFixID(gobj, i, 0);

        if (stage_no == 101) {
            lay.id = 21;
        } else {
            lay.id = 19;
        }
        gobj2 = CreateLayoutedGObj(0x2E, 0x290, -1, 0, &lay, -1, 7, 0);
        ((WmWork *)*(int *)(gobj2 + 0x15C))->owner = owner;
        ((WmWork *)*(int *)(gobj2 + 0x15C))->flag = 0;
        SetFlag4PointFixID(gobj2, i, 1);
    }
    return 0;
}

void WindMillGeo(void) {}

void WindMillDL(void) {}
