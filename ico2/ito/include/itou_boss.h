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

/* the functions itou_boss.c defines `inline`, in the order the ROM emits
   their out-of-line copies (gcc 2.9 writes deferred functions at the end of
   the file in the order of their first declaration) */
int InqCapsuleGhostBossStage(void);
void actBossCtrlStart(void *a0);
int InitBossCtrlGeo(void *a0);
void CapsuleGhostBossStart(void);
int InqCapsuleGhostBossEnd(void);
void BossCtrlGeo(void *self);
void itou_boss_gflag_init(void);
void gene_eff_end_func(void);

#endif /* ITOU_BOSS_H */
