# findActPoint — parked

VRAM: 0x001D5F40 (file_off 0x0D5F40)
Asm source: asm/aug6/nonmatchings/sugipon/src/motionManager/findActPoint.s

## Attempt at 2026-07-07

**Reason parked:** rc21 near-miss. Init leaf resetting D_0062C234 base fields + D_0062C230->0x134=0; f=FLT_MAX(0x7F7FFFFF, lit4 %hi/%lo) to 0x170/0x110/0x114/0x138/0x130/0x134/0x174; many int=0; 0x1B8=old 0x1B4. CORE FLOOR: p->0x14 &= ~0x10 (store A), &= ~0x20, &= ~0x1000 (store B) = 2 stores/3 ands in ROM. My ee-gcc DSE-eliminates store A in clean local-temp form (collapses to 1 store); only ((p[0x14]&=~0x10)&~0x20)&~0x1000 single-expr compound keeps store A but folds the last two ands to one (0xFFFFEFDF) -> cascades scheduling = rc21. volatile store-A keeps+unfolds but over-constrains sched (rc30). C230 ambiguous barrier keeps A but pins C230 between A/B while ROM schedules it after B (rc28). Store-A is a dev-compiler non-DSE divergence. RESUME: permuter on compound rc21 seed, or find non-constraining anti-DSE lever.

**TU:** `sugipon/src/motionManager.c`

**Seed:** `tough_nuts/findActPoint/findActPoint.c`

Disassembly:

```
.align 3
nonmatching findActPoint, 0x98

glabel findActPoint
    /* D5F40 001D5F40 44B6828F */  lw         $2, %gp_rel(D_0062C234)($28)
    /* D5F44 001D5F44 FFFF043C */  lui        $4, (0xFFFFFFEF >> 16)
    /* D5F48 001D5F48 EFFF8434 */  ori        $4, $4, (0xFFFFFFEF & 0xFFFF)
    /* D5F4C 001D5F4C FFFF053C */  lui        $5, (0xFFFFFFDF >> 16)
    /* D5F50 001D5F50 1400438C */  lw         $3, 0x14($2)
    /* D5F54 001D5F54 DFFFA534 */  ori        $5, $5, (0xFFFFFFDF & 0xFFFF)
    /* D5F58 001D5F58 040140AC */  sw         $0, 0x104($2)
    /* D5F5C 001D5F5C 6300063C */  lui        $6, %hi(D_0062D5BC)
    /* D5F60 001D5F60 24186400 */  and        $3, $3, $4
    /* D5F64 001D5F64 F80040AC */  sw         $0, 0xF8($2)
    /* D5F68 001D5F68 140043AC */  sw         $3, 0x14($2)
    /* D5F6C 001D5F6C FFFF043C */  lui        $4, (0xFFFFEFFF >> 16)
    /* D5F70 001D5F70 24186500 */  and        $3, $3, $5
    /* D5F74 001D5F74 FFEF8434 */  ori        $4, $4, (0xFFFFEFFF & 0xFFFF)
    /* D5F78 001D5F78 FC0040AC */  sw         $0, 0xFC($2)
    /* D5F7C 001D5F7C 24186400 */  and        $3, $3, $4
    /* D5F80 001D5F80 000140AC */  sw         $0, 0x100($2)
    /* D5F84 001D5F84 B401458C */  lw         $5, 0x1B4($2)
    /* D5F88 001D5F88 BCD5C0C4 */  lwc1       $f0, %lo(D_0062D5BC)($6)
    /* D5F8C 001D5F8C 40B6848F */  lw         $4, %gp_rel(D_0062C230)($28)
    /* D5F90 001D5F90 140043AC */  sw         $3, 0x14($2)
    /* D5F94 001D5F94 340180AC */  sw         $0, 0x134($4)
    /* D5F98 001D5F98 700140E4 */  swc1       $f0, 0x170($2)
    /* D5F9C 001D5F9C B80145AC */  sw         $5, 0x1B8($2)
    /* D5FA0 001D5FA0 CC0140AC */  sw         $0, 0x1CC($2)
    /* D5FA4 001D5FA4 100140E4 */  swc1       $f0, 0x110($2)
    /* D5FA8 001D5FA8 140140E4 */  swc1       $f0, 0x114($2)
    /* D5FAC 001D5FAC F40040AC */  sw         $0, 0xF4($2)
    /* D5FB0 001D5FB0 380140E4 */  swc1       $f0, 0x138($2)
    /* D5FB4 001D5FB4 300140E4 */  swc1       $f0, 0x130($2)
    /* D5FB8 001D5FB8 340140E4 */  swc1       $f0, 0x134($2)
    /* D5FBC 001D5FBC 0C0140AC */  sw         $0, 0x10C($2)
    /* D5FC0 001D5FC0 740140E4 */  swc1       $f0, 0x174($2)
    /* D5FC4 001D5FC4 780140AC */  sw         $0, 0x178($2)
    /* D5FC8 001D5FC8 080140AC */  sw         $0, 0x108($2)
    /* D5FCC 001D5FCC B40140AC */  sw         $0, 0x1B4($2)
    /* D5FD0 001D5FD0 0800E003 */  jr         $31
    /* D5FD4 001D5FD4 D40140AC */   sw        $0, 0x1D4($2)
endlabel findActPoint
```
