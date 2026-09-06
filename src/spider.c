#include "common.h"
#include "sugiCommon.h"

ASM_LIT4_SLOT(D_006396A0, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/spider", InitSpiderLayoutGeo);
INCLUDE_ASM("asm/nonmatchings/src/spider", WakeUpLayoutedSpiders);
INCLUDE_ASM("asm/nonmatchings/src/spider", CallSpidersToReviveEnemy);
INCLUDE_ASM("asm/nonmatchings/src/spider", SpiderLayoutGeo);
INCLUDE_ASM("asm/nonmatchings/src/spider", DispAllMemberOfSpider);
extern char D_0063BAC8[];
void SetSpiderGroupReviveStatus(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(int *)(p + 0x3C) = 1;
    gamesysObjInfoUniqDataSet(a0);
    debug_StdPrintfDummy(D_0063BAC8, *(int *)(a0 + 8));
}
extern void iosOmSendMail(void *gop, int msg, void *sender);

int DeadAllSpiders(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            iosOmSendMail(o, 0x26, o);
        }
    }
    return 0;
}
extern int IsActCharDead(void *gop);

/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 148-151) shared by
   GetAliveSpiders and MemorySpiderLayout; it has no out-of-line copy. */
static inline int CountAliveSpiders(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    int n = 0;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            if (IsActCharDead(o) == 0) {
                n++;
            }
        }
    }
    return n;
}

int GetAliveSpiders(char *gp)
{
    char *oi = *(char **)(gp + 0x15C);
    char *sg = *(char **)(oi + 0x830);
    char *own = *(char **)oi;

    if (own != 0 && *(int *)(own + 0xC) != 0x21 && IsActCharDead(own) == 0) {
        return *(int *)(sg + 0x20);
    }
    if (*(char **)(sg + 0x28)) {
        return CountAliveSpiders(gp);
    }
    return -1;
}
char *DeleteSpiderFromLayoutGroup(char *a0, int a1) {
    char **arr = *(char ***)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x24);
    char *r = arr[a1];
    arr[a1] = 0;
    return r;
}
/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 219-222) that
   clears the dead members out of a spider group; it has no out-of-line copy. */
static inline void RemoveDeadLayoutSpiders(char *sg)
{
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            if (IsActCharDead(o)) {
                (*(char ***)(sg + 0x24))[i] = 0;
            }
        }
    }
}

int GetNearestOfLayoutSpiders(float *dist, char *gp, void *center)
{
    float pos[4];
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int nearest = -1;
    int i;

    RemoveDeadLayoutSpiders(sg);

    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            float d;

            GetRootPosition(pos, o);
            d = distance_squared(center, pos);
            if (d < *dist) {
                nearest = i;
                *dist = d;
            }
        }
    }
    return nearest;
}
extern void GetRootPosition(void *out, void *obj);

int CheckSpidersInsideOfReviveRange(int *out, char *gp, void *center)
{
    float pos[4];
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    char **p = *(char ***)(sg + 0x24);
    int i;
    int n = 0;

    for (i = 0; i < *(int *)(sg + 0x20); i++, p++) {
        if (*p != 0) {
            if (IsActCharDead(*p) == 0) {
                GetRootPosition(pos, *p);

                if (distance_squared(pos, center) < 10000.0f) {
                    out[n] = i;
                    n++;
                }
            }
        }
    }
    return n;
}
int RestoreSpiderLayoutGeo(void)
{
    return 1;
}
extern char D_00620CB8[];
extern char D_00620CC8[];
extern char D_0063BAD0[];
extern char D_0063BAD8[];
extern char D_00620CD8[];
extern char D_00620CE8[];

int RestoreSpiderLayoutExtGeo(char *a0, char *a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int *ex = (int *)(a1 + 0x30);

    if (*(int *)(a1 + 0x30)) {
        *(int *)(p + 0x38) = ex[1];
    }
    if (ex[2]) {
        *(int *)(p + 0x3C) = 1;
    }
    debug_StdPrintfDummy(D_00620CB8, a0);
    debug_StdPrintfDummy(D_00620CC8, *(int *)(a1 + 0x30) ? D_0063BAD0 : D_0063BAD8);
    debug_StdPrintfDummy(D_00620CD8, ex[1]);
    debug_StdPrintfDummy(D_00620CE8, ex[2]);
    return 1;
}
int MemorySpiderLayout(char *dst, char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    char *lay = *(char **)(sg + 0x28);

    *(char **)dst = lay;
    if (lay) {
        *(int *)(dst + 4) = CountAliveSpiders(gp);
    } else {
        *(int *)(dst + 4) = 0;
    }
    *(int *)(dst + 8) = *(int *)(sg + 0x3C);
    return 1;
}
extern char D_00620B70[];
extern char D_00620BB0[];
extern void GetGeneratorSafePosition(void *pos, void *gen);
extern void SetDirectRootPosition(void *obj, void *pos);
extern void WakeUpLayoutedSpiders(void *gp);

/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 71-74) shared by
   WakeUpSpidersFromGenerator and SpiderLayoutGeo; it has no out-of-line copy. */
static inline void SetLayoutedSpidersRootPosition(char *gp, void *pos)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int num = *(int *)(sg + 0x20);
    int i;
    for (i = 0; i < num; i++) {
        SetDirectRootPosition((*(char ***)(sg + 0x24))[i], pos);
    }
}

void WakeUpSpidersFromGenerator(char *gp)
{
    float pos[4];
    char *gen = *(char **)(*(char **)(gp + 0x15C));

    if (gen != 0) {
        if (*(int *)(gen + 0xC) != 0x21) {
            debug_StdPrintfDummy(D_00620B70);
            return;
        }
    } else {
        debug_StdPrintfDummy(D_00620BB0);
        return;
    }
    GetGeneratorSafePosition(pos, gen);
    SetLayoutedSpidersRootPosition(gp, pos);
    WakeUpLayoutedSpiders(gp);
}
extern void SetAP1DeadStatus(void *gop);

/* INTERIM: stand-in for the TU's own DeleteSpiderFromLayoutGroup, which ROM
   inlines here (listing rows 257-259 inside this function).  The plain
   definition above stays until the TU's inline tail is laid out. */
static inline char *DeleteSpiderFromLayoutGroup_inl(char *gp, int idx)
{
    char **arr = *(char ***)(*(char **)(*(char **)(gp + 0x15C) + 0x830) + 0x24);
    char *r = arr[idx];
    arr[idx] = 0;
    return r;
}

void DeleteAllSpidersOfLayoutGroup(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            SetAP1DeadStatus(o);
            DeleteSpiderFromLayoutGroup_inl(gp, i);
        }
    }
    *(int *)(sg + 0x20) = 0;
}
extern void iosOmSendMail(void *gop, int msg, void *sender);

void SleepSpiderGroup(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            iosOmSendMail(o, 0x20, o);
        }
    }
}
void WakeupSpiderGroup(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            iosOmSendMail(o, 0x1F, o);
        }
    }
}
