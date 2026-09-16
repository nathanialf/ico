#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void InitSpiderGroupManager(void);
void EntryRevivedSpiderGroupManager(int a0);
void DispAllSpiderGroups(void);
void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1);
int *getReviveEnemyGObj(int count);
void InitSpiderGroupManager(void);
void EntryRevivedSpiderGroupManager(int a0);
void DispAllSpiderGroups(void);
void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1);
int *getReviveEnemyGObj(int count);
extern int D_0063BAE0;
extern int D_0063BAE4;
extern int D_0063BAE8;
extern int D_0063BAEC;
extern int D_0063BAF0;
extern int D_0063BAF4;
extern int D_0063BAF8;
extern int D_0063BAFC;
extern int D_00723C98[];
extern int D_0028F8F4[];

/* one RGBA tint per spider group, alpha 0x80 throughout */
static int spiderGroupColors[7][4] = {{0x7F, 0x00, 0x00, 0x80}, {0x40, 0x7F, 0x00, 0x80},
                                      {0x00, 0x40, 0x7F, 0x80}, {0x00, 0x7F, 0x00, 0x80},
                                      {0x40, 0x00, 0x7F, 0x80}, {0x7F, 0x40, 0x00, 0x80},
                                      {0x40, 0x40, 0x40, 0x80}};

extern int D_0063BAC4;
extern int D_0063BADC;
extern void DispAllMemberOfSpider();
extern int D_00723F98[];
extern int isysGObjSearchFromObjKindID_begin();
extern int isysGObjSearchFromObjKindID_next();

inline void InitSpiderGroupManager(void)
{
    D_0063BAE4 = 0;
    D_0063BAEC = 0;

    D_0063BAE8 = 0;

    D_0063BAF4 = 0;

    D_0063BAE0 = 0;

    D_0063BAF0 = 0;

    D_0063BAF8 = 0;
    D_0063BAFC = 0;
}

inline int *getReviveEnemyGObj(int count)
{
    int *p = isysGObjSearchFromObjKindID_begin(4);
    int i;
    {
        for (i = 0; i < count; i++) {
            if (p == 0) {
                return 0;
            }
            p = isysGObjSearchFromObjKindID_next(p);
        }
    }
    return p;
}

extern char D_0063BB00[];
extern void LockEnemyGenerate(int *p);
extern void debug_assertMessage(char *file, int line, char *mes);
extern void __assert(char *file, int line, char *expr);
extern void debug_StdPrintfDummy();

inline void EntryRevivedSpiderGroupManager(int a0)
{
    int idx = D_0063BAE4;
    D_0063BAE4 = idx + 1;
    D_00723C98[idx] = a0;
}

typedef struct {
    void *gobj; /* 0x00 */
    int rev;    /* 0x04 */
} SpiderGroupEnt;

extern SpiderGroupEnt D_00723D98[];

/* listing lines 96-103 */
void EntrySpiderGroupManager(int gobj)
{
    int *p;

    D_00723D98[D_0063BAE8].gobj = (void *)gobj;
    p = getReviveEnemyGObj(D_0063BAE4);
    if (p != 0) {
        debug_StdPrintfDummy("LOCK %p for LABEL %d, ID:%d\n", p, p[2], D_0063BAE8);
        LockEnemyGenerate(p);
        *(int *)((char *)p + 0x16C) = 0;
    } else {
        debug_assertMessage(
            "src/spiderGroupManager.c", 85,
            "No valid enemy layout data for spider.\n(Lack of enemy layout for spider revive.)\n");
        __assert("src/spiderGroupManager.c", 85, D_0063BB00);
    }
    D_00723D98[D_0063BAE8].rev = (int)p;
    D_0063BAE8 = D_0063BAE8 + 1;
    EntryRevivedSpiderGroupManager(gobj);
}

inline void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1)
{
    int idx = D_0063BAEC;
    int *p;
    int new_var;
    int *new_var2;
    new_var2 = &a1;
    D_0063BAF4 = *new_var2;
    p = D_00723F98 + idx;
    new_var = idx;
    idx = new_var + 1;
    *p = a0;
    D_0063BAEC = idx;
}

extern int D_0063BAF4;
extern int D_00723AE0[];
extern int D_0028FF30[];
extern void GetRootPosition(float *pos, int gobj);
extern int CheckSpidersInsideOfReviveRange(int *out, int group, float *pos);
extern void UnlockEnemyGenerate(void *p);
extern int DirectCallEnemy(void *p, int a1, float *pos, int *tbl, int a4);
extern void ExecuteSEPackage(void *p, int id);
extern int DeleteSpiderFromLayoutGroup(int a, int b);
extern void SetAP1DeadStatus(int x);
extern void SetSpiderGroupReviveStatus(void *gobj);

typedef struct {
    int group;    /* 0x00 */
    void *spider; /* 0x04 */
} SpiderPair;

extern SpiderPair D_00723C70[];

/* listing lines 124-171 */
int tryToRevive(void)
{
    float pos[4];
    int k = 0;
    int i;
    int j;
    int n;
    void *p;

    if (D_0063BAF4 != 0) {
        GetRootPosition(pos, D_0063BAF4);
        pos[1] -= *(float *)(*(int *)(D_0063BAF4 + 0x15C) + 0x160);
        for (i = 0; i < D_0063BAEC; i++) {
            n = CheckSpidersInsideOfReviveRange(D_00723AE0, D_00723F98[i], pos);
            if (n != 0) {
                for (j = 0; j < n; j++) {
                    D_00723C70[k].group = D_00723F98[i];
                    D_00723C70[k].spider = D_00723AE0[j];
                    k++;
                    if (k == 5) {
                        if (D_0063BAE0 < D_0063BAE8) {
                            int m;

                            p = D_00723D98[D_0063BAE0].rev;
                            UnlockEnemyGenerate(p);
                            debug_StdPrintfDummy("UNLOCK %p: (id:%d)\n", p, D_0063BAE0);
                            *(int *)((char *)p + 0x16C) = 1;
                            if (DirectCallEnemy(p, 0, pos, D_0028FF30, 0) == 0) {
                                return 0;
                            }
                            ExecuteSEPackage(p, 107);
                            for (m = 0; m < 5; m++) {
                                SetAP1DeadStatus(DeleteSpiderFromLayoutGroup(D_00723C70[m].group,
                                                                             D_00723C70[m].spider));
                            }
                            SetSpiderGroupReviveStatus(D_00723D98[D_0063BAE0].gobj);
                            D_0063BAE0++;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

extern int D_0063B138;
extern int D_0028F4C0[];
extern int tryToRevive(void);
extern int GetAliveSpiders(int gobj);
extern void DeadAllSpiders(int gobj);
extern void debug_PrintfDummy(int x, int y, unsigned int col, char *fmt, ...);

void ExecSpiderGroupManager(void)
{
    int i;
    int total;
    int groups;

    if ((D_0063BAF0 & 0xF) == 0) {
        tryToRevive();
    }

    if (D_0063BAE4 != 0 && D_0063BAFC == 0) {
        groups = 0;
        total = 0;
        for (i = 0; i < D_0063BAE4; i++) {
            int n = GetAliveSpiders(D_00723C98[i]);
            if (n >= 0) {
                total += n;
                groups++;
            }
        }

        if (groups != 0 && total > 0 && total < 5) {
            D_0063BAF8 = D_0063BAF8 + 1;
            if (D_0063B138 != 0) {
                debug_PrintfDummy(400, 120, 0xFFFFFFFF, "COUNTER %d/%d", D_0063BAF8,
                                  (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 45);
            }
        }

        if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 45 < D_0063BAF8) {
            for (i = 0; i < D_0063BAE4; i++) {
                if (GetAliveSpiders(D_00723C98[i]) >= 0) {
                    DeadAllSpiders(D_00723C98[i]);
                }
            }
            D_0063BAFC = 1;
        }

        if (D_0063B138 != 0) {
            if (groups != 0) {
                debug_PrintfDummy(400, 110, 0xFFFFFFFF, "REMAIN %d", total);
            } else {
                debug_PrintfDummy(400, 110, 0xFFFFFFFF, "NO GROUP WAKEUPED");
            }
        }
    }

    D_0063BAF0 = D_0063BAF0 + 1;
}

inline void DispAllSpiderGroups(void)
{
    int v = D_0028F8F4[0];
    D_0063BADC = 0;
    if (v & 0x1000) {
        D_0063BAC4 = D_0063BAC4 - 1;
    }
    if (v & 0x4000) {
        D_0063BAC4 = D_0063BAC4 + 1;
    }
    {
        int i;
        for (i = 0; i < D_0063BAE4; i++) {
            DispAllMemberOfSpider(D_00723C98[i], spiderGroupColors[i]);
        }
    }
}
