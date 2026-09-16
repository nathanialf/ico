#include "common.h"

typedef struct {
    float f0;        /* 0x00 */
    char pad04[0xC]; /* 0x04 */
    char m10[0x10];  /* 0x10 */
    char m20[0x10];  /* 0x20 */
    char m30[0x10];  /* 0x30 */
    int obj;         /* 0x40 */
    int x44;         /* 0x44 */
    char pad48[0x8]; /* 0x48 */
} BgaDisp;

typedef struct {
    long long w[10];
} MultiBga;

extern MultiBga D_004ECCA0;
extern int D_0063A438;
extern int D_0028F4C0[];
extern void _AddVector(void *a0, void *a1, void *a2);
extern float stage_PlayBgAnimation(int obj, void *a1, void *a2, float f);
extern void CopyVector(void *dst, void *src);
extern void CopyQuaternion(void *dst, void *src);
extern char ZeroVector[];
extern char D_002907E0[];
/* prototypes: their order is the inline tail's emission order */
void EntryMultiBgaManagerNoKind(BgaDisp *bga, int no, void *pos);
void DispMultiBgaManagerWithKind(int kind, BgaDisp *base, int n);

static inline void entryMultiBga(BgaDisp *bga, int no, int kind, void *pos, void *rot)
{
    BgaDisp *p = &bga[no];

    p->obj = kind;
    p->x44 = 0;
    CopyVector(p->m10, pos);
    CopyVector(p->m20, ZeroVector);
    CopyQuaternion(p->m30, rot);
    p->f0 = 0.0f;
}

void *InitMultiBgaManager(int n)
{
    MultiBga *base = (MultiBga *)iosMallocDebug(D_0063A438, n * 0x50, "src/multiBgaManager.c", 11);
    int i;
    for (i = 0; i < n; i++) {
        base[i] = D_004ECCA0;
    }
    return base;
}

void EntryMultiBgaManager(BgaDisp *bga, int no, int kind, void *pos, void *rot)
{
    entryMultiBga(bga, no, kind, pos, rot);
}

inline void EntryMultiBgaManagerNoKind(BgaDisp *bga, int no, void *pos)
{
    entryMultiBga(bga, no, -1, pos, D_002907E0);
}

void EntryMultiBgaManagerSensitive(BgaDisp *bga, int no, int kind, void *pos, void *rot, void *sens)
{
    BgaDisp *p = &bga[no];

    p->obj = kind;
    p->x44 = 0;
    CopyVector(p->m10, pos);
    CopyVector(p->m20, sens);
    CopyQuaternion(p->m30, rot);
    p->f0 = 0.0f;
}

void DispMultiBgaManager(BgaDisp *base, int n)
{
    int i;
    int ri;
    float f;
    for (i = 0; i < n; i++) {
        BgaDisp *e = &base[i];
        f = e->f0;
        if (f < 0.0f) {
            continue;
        }
        ri = (int)stage_PlayBgAnimation(e->obj, e->m10, e->m30, f);
        if (D_0028F4C0[5] != 0) {
            continue;
        }
        e->f0 = (float)ri;
        _AddVector(e->m10, e->m10, e->m20);
    }
}

inline void DispMultiBgaManagerWithKind(int kind, BgaDisp *base, int n)
{
    int i;
    int ri;
    float f;
    for (i = 0; i < n; i++) {
        BgaDisp *e = &base[i];
        f = e->f0;
        if (f < 0.0f) {
            continue;
        }
        ri = (int)stage_PlayBgAnimation(kind, e->m10, e->m30, f);
        if (D_0028F4C0[5] != 0) {
            continue;
        }
        e->f0 = (float)ri;
    }
}
