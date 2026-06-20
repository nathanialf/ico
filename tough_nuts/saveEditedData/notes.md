# saveEditedData — parked

VRAM: 0x00180130 (file_off 0x080130)
Asm source: asm/aug6/nonmatchings/omori/src/camera-editor/saveEditedData.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=2). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `omori/src/camera-editor.c`

**Seed:** `tough_nuts/saveEditedData/saveEditedData.c`

Disassembly:

```
.align 3
nonmatching saveEditedData, 0x4C

glabel saveEditedData
    /* 80130 00180130 100080C4 */  lwc1       $f0, 0x10($4)
    /* 80134 00180134 040081C4 */  lwc1       $f1, 0x4($4)
    /* 80138 00180138 02000C46 */  mul.s      $f0, $f0, $f12
    /* 8013C 0018013C 00108044 */  mtc1       $0, $f2
    /* 80140 00180140 40080046 */  add.s      $f1, $f1, $f0
    /* 80144 00180144 34080246 */  c.lt.s     $f1, $f2
    /* 80148 00180148 00000000 */  nop
    /* 8014C 0018014C 03000045 */  bc1f       .L0018015C
    /* 80150 00180150 040081E4 */   swc1      $f1, 0x4($4)
    /* 80154 00180154 07000010 */  b          .L00180174
    /* 80158 00180158 06100046 */   mov.s     $f0, $f2
.align 2
  .L0018015C:
    /* 8015C 0018015C 2041013C */  lui        $1, (0x41200000 >> 16)
    /* 80160 00180160 00008144 */  mtc1       $1, $f0
    /* 80164 00180164 34000146 */  c.lt.s     $f0, $f1
    /* 80168 00180168 00000000 */  nop
    /* 8016C 0018016C 01000245 */  bc1fl      .L00180174
    /* 80170 00180170 06080046 */   mov.s     $f0, $f1
.align 2
  .L00180174:
    /* 80174 00180174 0800E003 */  jr         $31
    /* 80178 00180178 040080E4 */   swc1      $f0, 0x4($4)
endlabel saveEditedData
    /* 8017C 0018017C 00000000 */  nop
```
