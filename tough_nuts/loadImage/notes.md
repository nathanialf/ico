# loadImage — parked

VRAM: 0x002398B8 (file_off 0x1398B8)
Asm source: asm/aug6/nonmatchings/ito/mpeg/mv_disp/loadImage.s

## Attempt at 2026-06-04

**Reason parked:** rc5 floor (struct-direct seed is rc6, floats CORRECT). Shape recovered (mirror of matched sibling handler_endimage): LoadImg*p=*(LoadImg**)(a0+0x34); p->f0=D_00629B8C; p->f8=D_00629B90; *(float*)(a0+0x1C)=0.5f; return 1. RESIDUAL = scheduler delay-slot-filler tie-break: gcc fills the lw-v1(p) load-delay with lwc1-f2(start float load early) then addiu-v0; ORIGINAL fills it with addiu-v0(return 1) then both lwc1 consecutive. struct-direct gets float regs right (B8C=f2,B90=f0,0.5=f1) but addiu misplaced (rc6); locals/float* shapes swap floats (rc9). 31 distinct hand shapes, none flips the addiu/lwc1 delay-slot choice. next-verdict park for offline auto_permute.

**TU:** `ito/mpeg/mv_disp.c`

**Seed:** `tough_nuts/loadImage/loadImage.c`

Disassembly:

```
.align 3
nonmatching loadImage, 0x28

glabel loadImage
    /* 1398B8 002398B8 3400838C */  lw         $3, 0x34($4)
    /* 1398BC 002398BC 01000224 */  addiu      $2, $0, 0x1
    /* 1398C0 002398C0 9C8F82C7 */  lwc1       $f2, %gp_rel(D_00629B8C)($28)
    /* 1398C4 002398C4 A08F80C7 */  lwc1       $f0, %gp_rel(D_00629B90)($28)
    /* 1398C8 002398C8 003F013C */  lui        $1, (0x3F000000 >> 16)
    /* 1398CC 002398CC 00088144 */  mtc1       $1, $f1
    /* 1398D0 002398D0 080060E4 */  swc1       $f0, 0x8($3)
    /* 1398D4 002398D4 000062E4 */  swc1       $f2, 0x0($3)
    /* 1398D8 002398D8 0800E003 */  jr         $31
    /* 1398DC 002398DC 1C0081E4 */   swc1      $f1, 0x1C($4)
endlabel loadImage
```

## Resume 2026-06-04 (loop) — stall 8/30 from reset (NOTE: reset cleared prior rc5 best; seed is rc6)
Struct-direct seed measures rc6; floats correct (B8C=f2,B90=f0,0.5=f1). Residual
is purely the addiu(return-1) delay placement: ROM = `addiu v0,1; lwc1 f2; lwc1 f0`
(return-1 fills the lw-p load-delay, both float loads consecutive); built interleaves
`lwc1 f2; addiu v0,1; lwc1 f0`. New forms ruled out: temps-like-sibling (rc9 floats
swap — the extra 0.5f perturbs FP regalloc vs the 2-float matched siblings), rv-temp
first (rc6), 0.5f-store-first (rc11), all-temps (rc9), store-f8-before-f0 (rc8, gcc
honors source order, regresses), int-return (rc6), 0.5f-temp-first (rc6), Disp-typed
a0 fields (rc6). Same FP-scheduler-tie class as func_00239228. The 0.5f lui/mtc1 is
the perturbing extra vs the clean 2-float siblings (setDispEnv/handler_endimage match
with the temps idiom). Continue toward 30 then permuter.
