# func_001D1C78 — parked

VRAM: 0x001D1C78 (file_off 0x0D1C78)
Asm source: asm/nonmatchings/src/girlForceField/func_001D1C78.s

## Attempt at 2026-05-31

**Reason parked:** rc15 alloc+FP-init, structure RECOVERED. r=(float*)func_0013A0F8(D_00632010,0xC,file,0x17); v=a1->0x28; r[0]=v; r[2]=0; r[1]=1.0/v; y=a0->0x15C->0x840; y->0x20=y->0x28=y->0x24=1.0f. Residual is MULTI-WALL FP regalloc/scheduling: (1) v->f1 vs ROM f0 + 1.0f->f0 vs f1 (the long-lived 1.0f const for div+3 y-stores); (2) div result f2 vs ROM reusing v's f0 (1.0/v overwrites v); (3) the func_0013A0F8 retval r copied v0->v1 then stored via v1 — the KEEP_LIVE non-coalesce class (same as parked func_001F22E0); (4) y-store order 0x20/0x28/0x24 reordered by gcc. gp-arg fix dropped 18->15. explicit one/v decl order no change. FP regalloc + call-result-coalesce; permuter territory. NOT a floor, stall 1.

**TU:** `src/girlForceField.c`

**Seed:** `tough_nuts/func_001D1C78/func_001D1C78.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632010, 1

.align 3
nonmatching func_001D1C78, 0x80

glabel func_001D1C78
    /* D1C78 001D1C78 D0FFBD27 */  addiu      $29, $29, -0x30
    /* D1C7C 001D1C7C 6200063C */  lui        $6, %hi(D_00618F08)
    /* D1C80 001D1C80 1000B1FF */  sd         $17, 0x10($29)
    /* D1C84 001D1C84 088FC624 */  addiu      $6, $6, %lo(D_00618F08)
    /* D1C88 001D1C88 2D888000 */  daddu      $17, $4, $0
    /* D1C8C 001D1C8C 0000B0FF */  sd         $16, 0x0($29)
    /* D1C90 001D1C90 2D80A000 */  daddu      $16, $5, $0
    /* D1C94 001D1C94 2097848F */  lw         $4, (D_00632010) /* gp_rel: (D_00632010) */
    /* D1C98 001D1C98 2000BFFF */  sd         $31, 0x20($29)
    /* D1C9C 001D1C9C 0C000524 */  addiu      $5, $0, 0xC
    /* D1CA0 001D1CA0 3EE8040C */  jal        func_0013A0F8
    /* D1CA4 001D1CA4 17000724 */   addiu     $7, $0, 0x17
    /* D1CA8 001D1CA8 280000C6 */  lwc1       $f0, 0x28($16)
    /* D1CAC 001D1CAC 2D184000 */  daddu      $3, $2, $0
    /* D1CB0 001D1CB0 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D1CB4 001D1CB4 00088144 */  mtc1       $1, $f1
    /* D1CB8 001D1CB8 000060E4 */  swc1       $f0, 0x0($3)
    /* D1CBC 001D1CBC 00000000 */  nop
    /* D1CC0 001D1CC0 00000000 */  nop
    /* D1CC4 001D1CC4 03080046 */  div.s      $f0, $f1, $f0
    /* D1CC8 001D1CC8 080060AC */  sw         $0, 0x8($3)
    /* D1CCC 001D1CCC 2000BFDF */  ld         $31, 0x20($29)
    /* D1CD0 001D1CD0 0000B0DF */  ld         $16, 0x0($29)
    /* D1CD4 001D1CD4 040060E4 */  swc1       $f0, 0x4($3)
    /* D1CD8 001D1CD8 5C01248E */  lw         $4, 0x15C($17)
    /* D1CDC 001D1CDC 1000B1DF */  ld         $17, 0x10($29)
    /* D1CE0 001D1CE0 4008838C */  lw         $3, 0x840($4)
    /* D1CE4 001D1CE4 200061E4 */  swc1       $f1, 0x20($3)
    /* D1CE8 001D1CE8 280061E4 */  swc1       $f1, 0x28($3)
    /* D1CEC 001D1CEC 240061E4 */  swc1       $f1, 0x24($3)
    /* D1CF0 001D1CF0 0800E003 */  jr         $31
    /* D1CF4 001D1CF4 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001D1C78
```
