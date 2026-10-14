#include "sceneManager.h"
#include "main.h"
#include "include_asm.h"

/* int (void *, int, int) here, void (struct GObj *, int, int) in flag.h */
extern int SetFlag4PointFixID(void *gobj, int turns, int id);

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

/* the head of the vane's display object, Sub15C's parent link (the object
   and node the vane hangs from), written as words: the owner is held as an
   int, and the slot at 0x15C is read again for each store */
typedef struct { /* field names derived */
    int owner;   /* 0x00, parent.obj */
    int node;    /* 0x04, parent.node */
} WmWork;        /* derived name */

INCLUDE_ASM(InitWindMillGeo);

void WindMillGeo(void) {}

void WindMillDL(void) {}
