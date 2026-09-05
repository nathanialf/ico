#include "common.h"

typedef struct {
    long long w[8];    /* 0x00 */
    int       obj;     /* 0x40 */
    int       stay;    /* 0x44 */
    long long w48;     /* 0x48 */
} MultiBga;
extern MultiBga D_004ECCA0;
extern MultiBga D_007240A0[];
extern char *D_00724A00[];
extern int D_0063BB04;
extern char *stage_MakePlayBgAnimation(int kind);
extern void _CopyVector(void *dst, void *src);
extern void CopyQuaternion(void *dst, void *src);
extern void EntryMultiBgaManager(MultiBga *bga, int no, int kind, void *pos, void *rot);
extern void EntryMultiBgaManagerSensitive(MultiBga *bga, int no, int kind, void *pos, void *rot, int sensitive);
/* prototypes: their order is the inline tail's emission order */
void InitStageMultiBgaManager(void);
void EntryStageMultiBgaManager(int kind, void *pos, void *rot);
void EntryStageMultiBgaManagerSensitive(int kind, void *pos, void *rot, int sensitive);
void EntryStageMultiBgaManagerWithStay(int kind, void *pos, void *rot, int stay);
void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot, int sensitive, int stay);
inline void InitStageMultiBgaManager(void)
{
    int i;

    for (i = 0; i < 30; i++) {
        D_007240A0[i] = D_004ECCA0;
        D_00724A00[i] = 0;
    }
    D_0063BB04 = 0;
}
inline void EntryStageMultiBgaManagerWithStay(int kind, void *pos, void *rot, int stay)
{
    D_00724A00[D_0063BB04] = stage_MakePlayBgAnimation(kind);
    _CopyVector(D_00724A00[D_0063BB04] + 0x20, pos);
    CopyQuaternion(D_00724A00[D_0063BB04] + 0x30, rot);
    EntryMultiBgaManager(D_007240A0, D_0063BB04++, kind, pos, rot);
    D_007240A0[D_0063BB04 - 1].stay = stay;
    if (D_0063BB04 >= 30) {
        D_0063BB04 = 0;
    }
}
inline void EntryStageMultiBgaManager(int kind, void *pos, void *rot)
{
    EntryStageMultiBgaManagerWithStay(kind, pos, rot, 0);
}
inline void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot, int sensitive, int stay)
{
    D_00724A00[D_0063BB04] = stage_MakePlayBgAnimation(kind);
    _CopyVector(D_00724A00[D_0063BB04] + 0x20, pos);
    CopyQuaternion(D_00724A00[D_0063BB04] + 0x30, rot);
    EntryMultiBgaManagerSensitive(D_007240A0, D_0063BB04++, kind, pos, rot, sensitive);
    D_007240A0[D_0063BB04 - 1].stay = stay;
    if (D_0063BB04 >= 30) {
        D_0063BB04 = 0;
    }
}
inline void EntryStageMultiBgaManagerSensitive(int kind, void *pos, void *rot, int sensitive)
{
    EntryStageMultiBgaManagerSensitiveWithStay(kind, pos, rot, sensitive, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", DispStageMultiBgaManager);
