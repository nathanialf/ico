#include "common.h"
#include "debug.h"
#include "motionFileManager.h"

extern int D_0063C46C;
extern int D_0063C470;

typedef struct {
    char pad[0x134];
    int node_id;
    char pad2[0x194 - 0x138];
} MotFileRec;

extern MotFileRec D_0055FE58[];
extern int D_004EB758[];

inline void ResetDynamicMotionManager(void)
{
    int i;
    for (i = 0; i <= 0x47A; i++) {
        if (D_0055FE58[i].node_id == 4) {
            D_004EB758[i] = 0;
        }
    }
    D_0063C470 = 0;
}

inline void ResetStatic2MotionManager(int a0)
{
    int i;
    for (i = 0; i <= 0x47A; i++) {
        if (D_0055FE58[i].node_id == a0) {
            D_004EB758[i] = 0;
        }
    }
}

extern int D_0063B8F0;
extern char D_0061FB60[];
extern char D_0061FB80[];

typedef struct {
    int f0; /* 0x00 */
    int f4; /* 0x04 */
} NodeRec;

/* listing rows sugipon/src/motionFileManager.c:32-86 */
void pursueNodeList(void **node, unsigned char *type)
{
    int i;
    int ofs;

    i = 0;
    while (*node != 0) {
        ofs = (int)*node;
        switch (type[i]) {
        default:
            debug_StdPrintfDummy(D_0061FB60, type[i]);
            debug_StdPrintfDummy(D_0061FB80);
            break;
        case 1:
        case 4:
            *node = (void *)(D_0063B8F0 + ofs);
            break;
        case 2:
        case 5: {
            int *q = (int *)(D_0063B8F0 + ofs);
            int r = D_0063B8F0 + *q;
            *node = (void *)q;
            *q = r;
        } break;
        case 3:
        case 6: {
            NodeRec *q = (NodeRec *)(D_0063B8F0 + ofs);
            q->f0 = D_0063B8F0 + q->f0;
            q->f4 = D_0063B8F0 + q->f4;
            *node = (void *)q;
        } break;
        }
        node++;
        i++;
    }
}

inline int CheckMotionIncludeFacialData(unsigned int *self)
{
    int r;
    unsigned int p = (unsigned int)self + 0x10;
    if (p < self[2])
        r = 0;
    else
        r = -1;
    return r;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionFileManager", InitMotionFile);

void InitMotionMemorySize(void)
{
    D_0063C46C = 0;
    D_0063C470 = 0;
}

int AddMotionMemorySize(int a0, int a1)
{
    int v0;
    if (a1 != 0) {
        v0 = D_0063C470 + a0;
        D_0063C470 = v0;
    } else {
        v0 = D_0063C46C + a0;
        D_0063C46C = v0;
    }
    return v0;
}

int GetMotionMemorySize(int a0)
{
    return a0 ? D_0063C470 : D_0063C46C;
}
