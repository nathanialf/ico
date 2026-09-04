# _sprintf_r — parked

VRAM: 0x00261120 (file_off 0x161120)
Asm source: asm/aug6/nonmatchings/common/src/PObj/_sprintf_r.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_sprintf_r/_sprintf_r.c`

Disassembly:

```
.align 3
nonmatching _sprintf_r, 0x68

glabel _sprintf_r
    /* 161120 00261120 20FFBD27 */  addiu      $29, $29, -0xE0
    /* 161124 00261124 2D60A000 */  daddu      $12, $5, $0
    /* 161128 00261128 FF7F023C */  lui        $2, (0x7FFFFFFF >> 16)
    /* 16112C 0026112C 5400A4AF */  sw         $4, 0x54($29)
    /* 161130 00261130 FFFF4234 */  ori        $2, $2, (0x7FFFFFFF & 0xFFFF)
    /* 161134 00261134 2D28C000 */  daddu      $5, $6, $0
    /* 161138 00261138 08020324 */  addiu      $3, $0, 0x208
    /* 16113C 0026113C 6000BFFF */  sd         $31, 0x60($29)
    /* 161140 00261140 B800A7FF */  sd         $7, 0xB8($29)
    /* 161144 00261144 2D20A003 */  daddu      $4, $29, $0
    /* 161148 00261148 C000A8FF */  sd         $8, 0xC0($29)
    /* 16114C 0026114C B800A627 */  addiu      $6, $29, 0xB8
    /* 161150 00261150 C800A9FF */  sd         $9, 0xC8($29)
    /* 161154 00261154 D000AAFF */  sd         $10, 0xD0($29)
    /* 161158 00261158 D800ABFF */  sd         $11, 0xD8($29)
    /* 16115C 0026115C 0C00A3A7 */  sh         $3, 0xC($29)
    /* 161160 00261160 1000ACAF */  sw         $12, 0x10($29)
    /* 161164 00261164 1400A2AF */  sw         $2, 0x14($29)
    /* 161168 00261168 0000ACAF */  sw         $12, 0x0($29)
    /* 16116C 0026116C 408B090C */  jal        func_00262D00
    /* 161170 00261170 0800A2AF */   sw        $2, 0x8($29)
    /* 161174 00261174 0000A38F */  lw         $3, 0x0($29)
    /* 161178 00261178 6000BFDF */  ld         $31, 0x60($29)
    /* 16117C 0026117C 000060A0 */  sb         $0, 0x0($3)
    /* 161180 00261180 0800E003 */  jr         $31
    /* 161184 00261184 E000BD27 */   addiu     $29, $29, 0xE0
endlabel _sprintf_r
```
