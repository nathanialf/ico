# GetFlyPosition — parked

VRAM: 0x00160EE8 (file_off 0x060EE8)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/GetFlyPosition.s

## Attempt at 2026-06-30

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=42). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/GetFlyPosition/GetFlyPosition.c`

Disassembly:

```
.align 3
nonmatching GetFlyPosition, 0x150

glabel GetFlyPosition
    /* 60EE8 00160EE8 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 60EEC 00160EEC 1000B0FF */  sd         $16, 0x10($29)
    /* 60EF0 00160EF0 4000BFFF */  sd         $31, 0x40($29)
    /* 60EF4 00160EF4 2D804000 */  daddu      $16, $2, $0
    /* 60EF8 00160EF8 3000B2FF */  sd         $18, 0x30($29)
    /* 60EFC 00160EFC 2000B1FF */  sd         $17, 0x20($29)
    /* 60F00 00160F00 4E4A050C */  jal        actBoyDitch3mReady
    /* 60F04 00160F04 0000A2AF */   sw        $2, 0x0($29)
    /* 60F08 00160F08 46004010 */  beqz       $2, .L00161024
    /* 60F0C 00160F0C 4000BFDF */   ld        $31, 0x40($29)
    /* 60F10 00160F10 0000048E */  lw         $4, 0x0($16)
    /* 60F14 00160F14 02000524 */  addiu      $5, $0, 0x2
    /* 60F18 00160F18 6401828C */  lw         $2, 0x164($4)
    /* 60F1C 00160F1C 7006438C */  lw         $3, 0x670($2)
    /* 60F20 00160F20 E001648C */  lw         $4, 0x1E0($3)
    /* 60F24 00160F24 2E008514 */  bne        $4, $5, .L00160FE0
    /* 60F28 00160F28 F491878F */   lw        $7, %gp_rel(D_00629DE4)($28)
    /* 60F2C 00160F2C F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* 60F30 00160F30 00B49227 */  addiu      $18, $28, %gp_rel(D_0062BFF0)
    /* 60F34 00160F34 809A918F */  lw         $17, %gp_rel(D_0062A670)($28)
    /* 60F38 00160F38 A463040C */  jal        pac_DispQW
    /* 60F3C 00160F3C 00B482AF */   sw        $2, %gp_rel(D_0062BFF0)($28)
    /* 60F40 00160F40 2041013C */  lui        $1, (0x41200000 >> 16)
    /* 60F44 00160F44 00088144 */  mtc1       $1, $f1
    /* 60F48 00160F48 64000524 */  addiu      $5, $0, 0x64
    /* 60F4C 00160F4C 0100A050 */  beql       $5, $0, .L00160F54
    /* 60F50 00160F50 CD010000 */   break     0, 7
.align 2
  .L00160F54:
    /* 60F54 00160F54 0000028E */  lw         $2, 0x0($16)
    /* 60F58 00160F58 02000146 */  mul.s      $f0, $f0, $f1
    /* 60F5C 00160F5C 6401438C */  lw         $3, 0x164($2)
    /* 60F60 00160F60 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 60F64 00160F64 00080444 */  mfc1       $4, $f1
    /* 60F68 00160F68 7006668C */  lw         $6, 0x670($3)
    /* 60F6C 00160F6C 1A008500 */  div        $0, $4, $5
    /* 60F70 00160F70 F401C38C */  lw         $3, 0x1F4($6)
    /* 60F74 00160F74 10100000 */  mfhi       $2
    /* 60F78 00160F78 2A104300 */  slt        $2, $2, $3
    /* 60F7C 00160F7C 09004010 */  beqz       $2, .L00160FA4
    /* 60F80 00160F80 00000000 */   nop
    /* 60F84 00160F84 0000058E */  lw         $5, 0x0($16)
    /* 60F88 00160F88 0C000224 */  addiu      $2, $0, 0xC
    /* 60F8C 00160F8C 6401A38C */  lw         $3, 0x164($5)
    /* 60F90 00160F90 7006648C */  lw         $4, 0x670($3)
    /* 60F94 00160F94 09004016 */  bnez       $18, .L00160FBC
    /* 60F98 00160F98 000282AC */   sw        $2, 0x200($4)
    /* 60F9C 00160F9C 0D000010 */  b          .L00160FD4
    /* 60FA0 00160FA0 6401A28C */   lw        $2, 0x164($5)
.align 2
  .L00160FA4:
    /* 60FA4 00160FA4 0000058E */  lw         $5, 0x0($16)
    /* 60FA8 00160FA8 09000224 */  addiu      $2, $0, 0x9
    /* 60FAC 00160FAC 6401A38C */  lw         $3, 0x164($5)
    /* 60FB0 00160FB0 7006648C */  lw         $4, 0x670($3)
    /* 60FB4 00160FB4 06004012 */  beqz       $18, .L00160FD0
    /* 60FB8 00160FB8 000282AC */   sw        $2, 0x200($4)
.align 2
  .L00160FBC:
    /* 60FBC 00160FBC 6401A28C */  lw         $2, 0x164($5)
    /* 60FC0 00160FC0 00B4848F */  lw         $4, %gp_rel(D_0062BFF0)($28)
    /* 60FC4 00160FC4 7006438C */  lw         $3, 0x670($2)
    /* 60FC8 00160FC8 15000010 */  b          .L00161020
    /* 60FCC 00160FCC 0C0264AC */   sw        $4, 0x20C($3)
.align 2
  .L00160FD0:
    /* 60FD0 00160FD0 6401A28C */  lw         $2, 0x164($5)
.align 2
  .L00160FD4:
    /* 60FD4 00160FD4 7006438C */  lw         $3, 0x670($2)
    /* 60FD8 00160FD8 11000010 */  b          .L00161020
    /* 60FDC 00160FDC 0C0271AC */   sw        $17, 0x20C($3)
.align 2
  .L00160FE0:
    /* 60FE0 00160FE0 09000524 */  addiu      $5, $0, 0x9
    /* 60FE4 00160FE4 809A888F */  lw         $8, %gp_rel(D_0062A670)($28)
    /* 60FE8 00160FE8 00B48427 */  addiu      $4, $28, %gp_rel(D_0062BFF0)
    /* 60FEC 00160FEC 00B487AF */  sw         $7, %gp_rel(D_0062BFF0)($28)
    /* 60FF0 00160FF0 0000068E */  lw         $6, 0x0($16)
    /* 60FF4 00160FF4 6401C28C */  lw         $2, 0x164($6)
    /* 60FF8 00160FF8 7006438C */  lw         $3, 0x670($2)
    /* 60FFC 00160FFC 05008010 */  beqz       $4, .L00161014
    /* 61000 00161000 000265AC */   sw        $5, 0x200($3)
    /* 61004 00161004 6401C28C */  lw         $2, 0x164($6)
    /* 61008 00161008 7006438C */  lw         $3, 0x670($2)
    /* 6100C 0016100C 04000010 */  b          .L00161020
    /* 61010 00161010 0C0267AC */   sw        $7, 0x20C($3)
.align 2
  .L00161014:
    /* 61014 00161014 6401C28C */  lw         $2, 0x164($6)
    /* 61018 00161018 7006438C */  lw         $3, 0x670($2)
    /* 6101C 0016101C 0C0268AC */  sw         $8, 0x20C($3)
.align 2
  .L00161020:
    /* 61020 00161020 4000BFDF */  ld         $31, 0x40($29)
.align 2
  .L00161024:
    /* 61024 00161024 3000B2DF */  ld         $18, 0x30($29)
    /* 61028 00161028 2000B1DF */  ld         $17, 0x20($29)
    /* 6102C 0016102C 1000B0DF */  ld         $16, 0x10($29)
    /* 61030 00161030 0800E003 */  jr         $31
    /* 61034 00161034 5000BD27 */   addiu     $29, $29, 0x50
endlabel GetFlyPosition
```
