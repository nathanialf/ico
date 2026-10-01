#include "sceneManager.h"
#include "main.h"

/* int (void *, int, int) here, void (char *, int, int) in flag.h */
extern int SetFlag4PointFixID(void *gobj, int idx, int a2);

/* The 0x40-byte layout record CreateLayoutedGObj takes: three 16-byte vectors
   and the model id the loader resolves (sceneManager.h's SObjSimpleSetting
   with its alignment tail as a pad).  The vectors are copied as two
   doublewords each. */
typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} WmVec; /* derived name */

typedef struct { /* field names derived */
    WmVec pos;   /* 0x00 */
    WmVec rot;   /* 0x10 */
    WmVec scale; /* 0x20 */
    int id;      /* 0x30 */
    char pad34[12];
} WmLayout; /* derived name */

/* the windmill's work record, reached through the GObj's 0x15C slot read as
   an int handle, so each store below reads the slot again */
typedef struct { /* field names derived */
    int owner;   /* 0x00 */
    int flag;    /* 0x04 */
} WmWork;        /* derived name */

int InitWindMillGeo(int owner, WmLayout *src)
{
    WmLayout lay;
    GObj *gobj;
    GObj *gobj2;
    int i;

    lay = *src;
    for (i = 0; i < 4; i++) {
        if (stage_no == 101) {
            lay.id = 20;
        } else {
            lay.id = 18;
        }
        gobj = CreateLayoutedGObj(46, 0x290, -1, 0, &lay, -1, 7, 0);
        ((WmWork *)GOBJ_SUB(gobj))->owner = owner;
        ((WmWork *)GOBJ_SUB(gobj))->flag = 0;
        SetFlag4PointFixID(gobj, i, 0);

        if (stage_no == 101) {
            lay.id = 21;
        } else {
            lay.id = 19;
        }
        gobj2 = CreateLayoutedGObj(46, 0x290, -1, 0, &lay, -1, 7, 0);
        ((WmWork *)GOBJ_SUB(gobj2))->owner = owner;
        ((WmWork *)GOBJ_SUB(gobj2))->flag = 0;
        SetFlag4PointFixID(gobj2, i, 1);
    }
    return 0;
}

void WindMillGeo(void) {}

void WindMillDL(void) {}
