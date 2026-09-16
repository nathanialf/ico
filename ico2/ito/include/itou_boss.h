/*
 * ico2/ito/include/itou_boss.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what itou_boss.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ITOU_BOSS_H
#define ITOU_BOSS_H

void BossCtrlGeo(void *self);
void CapsuleGhostBossStart(void);
int InqCapsuleGhostBossEnd(void);
int InqCapsuleGhostBossStage(void);
void func_001A08F8();
void itou_boss_gflag_init(void);

#endif /* ITOU_BOSS_H */
