# func_00194960 — parked

VRAM: 0x00194960 (file_off 0x094960)
Asm source: asm/nonmatchings/src/mail-add-data/func_00194960.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (ANCHOR,REG)

**TU:** `src/mail-add-data.c`

**Seed:** `tough_nuts/func_00194960/func_00194960.c`

Disassembly:

```
.align 3
nonmatching func_00194960, 0x58

glabel func_00194960
    /* 94960 00194960 07008018 */  blez       $4, .L00194980
    /* 94964 00194964 68010224 */   addiu     $2, $0, 0x168
    /* 94968 00194968 1A008200 */  div        $0, $4, $2
    /* 9496C 0019496C 01004050 */  beql       $2, $0, .L00194974
    /* 94970 00194970 CD010000 */   break     0, 7
.align 2
  .L00194974:
    /* 94974 00194974 10180000 */  mfhi       $3
    /* 94978 00194978 0B000010 */  b          .L001949A8
    /* 9497C 0019497C 2D206000 */   daddu     $4, $3, $0
.align 2
  .L00194980:
    /* 94980 00194980 02008104 */  bgez       $4, .L0019498C
    /* 94984 00194984 2D188000 */   daddu     $3, $4, $0
    /* 94988 00194988 23180300 */  negu       $3, $3
.align 2
  .L0019498C:
    /* 9498C 0019498C 1A006200 */  div        $0, $3, $2
    /* 94990 00194990 01004050 */  beql       $2, $0, .L00194998
    /* 94994 00194994 CD010000 */   break     0, 7
.align 2
  .L00194998:
    /* 94998 00194998 12180000 */  mflo       $3
    /* 9499C 0019499C 18286200 */  mult       $5, $3, $2
    /* 949A0 001949A0 2118A200 */  addu       $3, $5, $2
    /* 949A4 001949A4 21208300 */  addu       $4, $4, $3
.align 2
  .L001949A8:
    /* 949A8 001949A8 B5008328 */  slti       $3, $4, 0xB5
    /* 949AC 001949AC 98FE8224 */  addiu      $2, $4, -0x168
    /* 949B0 001949B0 0800E003 */  jr         $31
    /* 949B4 001949B4 0B108300 */   movn      $2, $4, $3
endlabel func_00194960
```
