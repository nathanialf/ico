/* src/worm.c — __FILE__ anchor at .rodata 0x0061A880 */

const char D_0061A880[16] = "src/worm.c";

#include "include_asm.h"

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;

typedef struct {              /* 0x50 capsule */
    char  _0[0x20];
    float f20, f24, f28;
    char  _2c[4];
    int   f30;
    float f34;
    union { long long ll; void *p; } f38;   /* 0x38 flags (alias pointer base) */
    int   f40, f44, f48;
    float f4C;
} Cap;

struct Sub {
    char  _0[8];
    int   f8;     /* 0x8 */
    int   fC;     /* 0xC */
    int   f10;    /* 0x10 */
    char  _14[0x804];
    short f818;   /* 0x818 */
    char  _81a[0x26];
    Cap  *f840;   /* 0x840 */
};


extern int  *func_0013A0F8(int handle, int size, const char *file, int line);
extern float func_00118A68(void);
extern void  func_00105F00(int *out, int *src);
extern int   func_001C58C0(void *p);
extern void  func_00139598(int x);

extern int D_00632010;
extern int D_00632024;

struct Cfg {
    float x, y, z;   /* 0x0,0x4,0x8 base pos */
    char  _c[4];
    float f10;       /* 0x10 nSeg */
    float f14;       /* 0x14 */
    float f18;       /* 0x18 nCap */
};

int *func_001F62E8(int *a0, struct Cfg *cfg) {
    struct Sub *mgr = *(struct Sub **)((char *)a0 + 0x15C);
    int  *ctl;
    char *segs;
    char *seg;
    char *e;
    int   i, j;
    int   nx, ny;
    float v;

    ctl  = func_0013A0F8(D_00632010, 0x10,  D_0061A880, 0x148);
    segs = (char *)func_0013A0F8(D_00632010, 0x370, D_0061A880, 0x149);

    nx = (int)cfg->f10;
    if (nx == 0) nx = 10;
    ny = (int)cfg->f18;
    if (ny == 0) ny = 20;

    *(int *)((char *)ctl + 0x4) = (int)func_0013A0F8(D_00632010, nx * 4, D_0061A880, 0x14E);

    {
        for (i = 0; i < nx; i++) {
            Vec4 pos;
            Vec4 tmp;
            tmp.x = cfg->x + (func_00118A68() * 2.0f - 1.0f) * 50.0f;
            tmp.y = cfg->y + (func_00118A68() * 2.0f - 1.0f) * 50.0f;
            tmp.z = cfg->z + (func_00118A68() * 2.0f - 1.0f) * 50.0f;
            tmp.w = 1.0f;
            pos = tmp;
            seg = segs + i * 0x50;
            *(int *)(seg + 0x0)  = ny;
            *(int *)(seg + 0x10) = -1;
            func_00105F00((int *)(seg + 0x20), (int *)&pos);
            v = 20.0f;
            if ((int)cfg->f14 != 0) v = cfg->f14;
            *(float *)(seg + 0x14) = v;
            *(float *)(seg + 0x40) = 10.0f;
            ((int **)(*(int *)((char *)ctl + 0x4)))[i] =
                func_0013A0F8(D_00632010, 0xA0, D_0061A880, 0x15E);
        }
    }

    *(float *)((char *)ctl + 0x8) = 1.0f;
    *(float *)((char *)ctl + 0xC) = 1.0f;
    *(int *)(segs + nx * 0x50) = -1;
    {
        int   r58 = func_001C58C0(segs);
        char *p840 = (char *)mgr->f840;
        int   oldc = mgr->fC;
        *(int *)((char *)ctl + 0x0) = r58;
        *(float *)(p840 + 0x20) = 1.0f;
        *(int *)(p840 + 0x8) = 0;
        *(int *)(p840 + 0x4) = 0;
        *(int *)(p840 + 0x0) = 0;
        *(float *)(p840 + 0x24) = 1.0f;
        *(float *)(p840 + 0x28) = 1.0f;
        if (oldc != 0) func_00139598(oldc & 0x0FFFFFFF);
    }
    {
        int oldten = mgr->f10;
        if (oldten != 0) func_00139598(oldten & 0x0FFFFFFF);
    }
    mgr->fC = 0;
    mgr->f10 = 0;
    mgr->fC  = (int)func_0013A0F8(D_00632024, ny * 64, D_0061A880, 0x16F);
    mgr->f10 = (int)func_0013A0F8(D_00632024, ny * 16, D_0061A880, 0x16F);
    mgr->f8  = ny;
    if (mgr->f840 != 0) func_00139598((int)mgr->f840 & 0x0FFFFFFF);
    mgr->f840 = (Cap *)func_0013A0F8(D_00632024, ny * 0x50, D_0061A880, 0x16F);

    j = 0;
    if (ny > 0) do {
        mgr->f840[j].f38.ll &= ~1L;
        mgr->f840[j].f38.ll &= ~2L;
        {
            long long t = mgr->f840[j].f38.ll;
            mgr->f840[j].f40 = 0;
            t &= ~4L;
            mgr->f840[j].f48 = (mgr->f840[j].f44 = 0);
            mgr->f840[j].f38.ll = t;
        }
        mgr->f840[j].f4C = 1.0f;
        mgr->f840[j].f28 = 1.0f;
        mgr->f840[j].f30 = 0;
        mgr->f840[j].f34 = 1.0f;
        *(short *)((char *)&mgr->f840[j] + 0x3A) = 0;
        mgr->f840[j].f20 = 1.0f;
        mgr->f840[j].f24 = 1.0f;
    } while (++j < ny);

    mgr->f818 = 2;
    return ctl;
}
