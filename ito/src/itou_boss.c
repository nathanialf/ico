#include "common.h"

extern unsigned char D_006CCE50[];
extern void func_00260568(void *a0, int a1, int a2);

void effect_end_func(void) {
    func_00260568(D_006CCE50, 0, 0xD50);
}

extern int D_00629C90;

int bossCtrlBeforeFunc(void) {
    int x = D_00629C90;
    int r = 0;
    if (x == 0x54 || x == 3 || x == 0x2E) {
        r = 1;
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_boss", BossEnemyFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_boss", gene_enemy);

extern unsigned char D_006CCE50[];

void BossCtrlGeo(void) {
    D_006CCE50[0] = 1;
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern int clip_floor_1(void *o);
extern signed char D_006CCE60[];

int itou_boss_gflag_init(void) {
    unsigned int s1 = 0;
    int s2 = 0;
    void *o;
    unsigned int i;

    if (isysGObjSearchFromObjLayoutID(0x3F) != 0) {
        i = 0;
        do {
            if (D_006CCE60[i * 0x40 + 4] >= 2) {
                s1++;
            }
            i++;
        } while (i < 0x35);
    }
    o = isysGObjSearchFromObjLayoutID(4);
    if (o != 0) {
        do {
            if (clip_floor_1(o) == 0) {
                s2++;
            }
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
    return s1 >= 0x35 && s2 == 0;
}

void InqCapsuleGhostBossStage(void) {
}
