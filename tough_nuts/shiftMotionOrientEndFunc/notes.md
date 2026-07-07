# shiftMotionOrientEndFunc — parked

VRAM: 0x001DE000 (file_off 0x0DE000)
Asm source: asm/aug6/nonmatchings/sugipon/src/motionOrientManager/shiftMotionOrientEndFunc.s

## Attempt at 2026-07-07

**Reason parked:** BODY MATCHES byte-exact at .o level (rc0 via jtbl switch: default-group first + block-address source order + e=D-(-mo*0x190) swap_addu keeps 0x118 as load displacement + ShiftBlk copy + display 5-arg tail). BLOCKED at commit by jtbl-carve infra: carved jtbl_00612010 in 511850.rodata.s references dead .L001DExxx labels; needs yaml carve at ROM 0x512010 so splat stops emitting it and postprocess_split_jtbls places gcc jtbl. Not a matching floor — resume from seed after jtbl-carve.

**TU:** `sugipon/src/motionOrientManager.c`

**Seed:** `tough_nuts/shiftMotionOrientEndFunc/shiftMotionOrientEndFunc.c`

Disassembly:

```
.align 3
nonmatching shiftMotionOrientEndFunc, 0x298

glabel shiftMotionOrientEndFunc
    /* DE000 001DE000 A0FEBD27 */  addiu      $29, $29, -0x160
    /* DE004 001DE004 90010724 */  addiu      $7, $0, 0x190
    /* DE008 001DE008 4001B2FF */  sd         $18, 0x140($29)
    /* DE00C 001DE00C 5600033C */  lui        $3, %hi(D_0055DA10)
    /* DE010 001DE010 3001B1FF */  sd         $17, 0x130($29)
    /* DE014 001DE014 10DA6324 */  addiu      $3, $3, %lo(D_0055DA10)
    /* DE018 001DE018 2001B0FF */  sd         $16, 0x120($29)
    /* DE01C 001DE01C 2D88A000 */  daddu      $17, $5, $0
    /* DE020 001DE020 5001BFFF */  sd         $31, 0x150($29)
    /* DE024 001DE024 2D808000 */  daddu      $16, $4, $0
    /* DE028 001DE028 5C01048E */  lw         $4, 0x15C($16)
    /* DE02C 001DE02C 9004828C */  lw         $2, 0x490($4)
    /* DE030 001DE030 18104700 */  mult       $2, $2, $7
    /* DE034 001DE034 21186200 */  addu       $3, $3, $2
    /* DE038 001DE038 1801638C */  lw         $3, 0x118($3)
    /* DE03C 001DE03C 1500622C */  sltiu      $2, $3, 0x15
    /* DE040 001DE040 08004010 */  beqz       $2, .L001DE064
    /* DE044 001DE044 2D90C000 */   daddu     $18, $6, $0
    /* DE048 001DE048 6100023C */  lui        $2, %hi(jtbl_00612010)
    /* DE04C 001DE04C 80180300 */  sll        $3, $3, 2
    /* DE050 001DE050 10204224 */  addiu      $2, $2, %lo(jtbl_00612010)
    /* DE054 001DE054 21186200 */  addu       $3, $3, $2
    /* DE058 001DE058 0000648C */  lw         $4, 0x0($3)
    /* DE05C 001DE05C 08008000 */  jr         $4
    /* DE060 001DE060 00000000 */   nop
.align 2
  jlabel .L001DE064
    /* DE064 001DE064 6300053C */  lui        $5, %hi(D_0062D5E0)
    /* DE068 001DE068 2D20A003 */  daddu      $4, $29, $0
    /* DE06C 001DE06C 6284090C */  jal        func_00261188
    /* DE070 001DE070 E0D5A524 */   addiu     $5, $5, %lo(D_0062D5E0)
    /* DE074 001DE074 60000010 */  b          .L001DE1F8
    /* DE078 001DE078 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE07C
    /* DE07C 001DE07C 6300053C */  lui        $5, %hi(D_0062D5E8)
    /* DE080 001DE080 2D20A003 */  daddu      $4, $29, $0
    /* DE084 001DE084 6284090C */  jal        func_00261188
    /* DE088 001DE088 E8D5A524 */   addiu     $5, $5, %lo(D_0062D5E8)
    /* DE08C 001DE08C 5A000010 */  b          .L001DE1F8
    /* DE090 001DE090 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE094
    /* DE094 001DE094 6300053C */  lui        $5, %hi(D_0062D5F0)
    /* DE098 001DE098 2D20A003 */  daddu      $4, $29, $0
    /* DE09C 001DE09C 6284090C */  jal        func_00261188
    /* DE0A0 001DE0A0 F0D5A524 */   addiu     $5, $5, %lo(D_0062D5F0)
    /* DE0A4 001DE0A4 54000010 */  b          .L001DE1F8
    /* DE0A8 001DE0A8 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE0AC
    /* DE0AC 001DE0AC 6100053C */  lui        $5, %hi(D_00611F50)
    /* DE0B0 001DE0B0 2D20A003 */  daddu      $4, $29, $0
    /* DE0B4 001DE0B4 6284090C */  jal        func_00261188
    /* DE0B8 001DE0B8 501FA524 */   addiu     $5, $5, %lo(D_00611F50)
    /* DE0BC 001DE0BC 4E000010 */  b          .L001DE1F8
    /* DE0C0 001DE0C0 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE0C4
    /* DE0C4 001DE0C4 6100053C */  lui        $5, %hi(D_00611F60)
    /* DE0C8 001DE0C8 2D20A003 */  daddu      $4, $29, $0
    /* DE0CC 001DE0CC 6284090C */  jal        func_00261188
    /* DE0D0 001DE0D0 601FA524 */   addiu     $5, $5, %lo(D_00611F60)
    /* DE0D4 001DE0D4 48000010 */  b          .L001DE1F8
    /* DE0D8 001DE0D8 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE0DC
    /* DE0DC 001DE0DC 6100053C */  lui        $5, %hi(D_00611F70)
    /* DE0E0 001DE0E0 2D20A003 */  daddu      $4, $29, $0
    /* DE0E4 001DE0E4 6284090C */  jal        func_00261188
    /* DE0E8 001DE0E8 701FA524 */   addiu     $5, $5, %lo(D_00611F70)
    /* DE0EC 001DE0EC 42000010 */  b          .L001DE1F8
    /* DE0F0 001DE0F0 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE0F4
    /* DE0F4 001DE0F4 6100053C */  lui        $5, %hi(D_00611F88)
    /* DE0F8 001DE0F8 2D20A003 */  daddu      $4, $29, $0
    /* DE0FC 001DE0FC 6284090C */  jal        func_00261188
    /* DE100 001DE100 881FA524 */   addiu     $5, $5, %lo(D_00611F88)
    /* DE104 001DE104 3C000010 */  b          .L001DE1F8
    /* DE108 001DE108 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE10C
    /* DE10C 001DE10C 6100053C */  lui        $5, %hi(D_00611FA0)
    /* DE110 001DE110 2D20A003 */  daddu      $4, $29, $0
    /* DE114 001DE114 6284090C */  jal        func_00261188
    /* DE118 001DE118 A01FA524 */   addiu     $5, $5, %lo(D_00611FA0)
    /* DE11C 001DE11C 36000010 */  b          .L001DE1F8
    /* DE120 001DE120 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE124
    /* DE124 001DE124 6100053C */  lui        $5, %hi(D_00611FB8)
    /* DE128 001DE128 2D20A003 */  daddu      $4, $29, $0
    /* DE12C 001DE12C 6284090C */  jal        func_00261188
    /* DE130 001DE130 B81FA524 */   addiu     $5, $5, %lo(D_00611FB8)
    /* DE134 001DE134 30000010 */  b          .L001DE1F8
    /* DE138 001DE138 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE13C
    /* DE13C 001DE13C 6300053C */  lui        $5, %hi(D_0062D5F8)
    /* DE140 001DE140 2D20A003 */  daddu      $4, $29, $0
    /* DE144 001DE144 6284090C */  jal        func_00261188
    /* DE148 001DE148 F8D5A524 */   addiu     $5, $5, %lo(D_0062D5F8)
    /* DE14C 001DE14C 2A000010 */  b          .L001DE1F8
    /* DE150 001DE150 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE154
    /* DE154 001DE154 6100053C */  lui        $5, %hi(D_00611FC8)
    /* DE158 001DE158 2D20A003 */  daddu      $4, $29, $0
    /* DE15C 001DE15C 6284090C */  jal        func_00261188
    /* DE160 001DE160 C81FA524 */   addiu     $5, $5, %lo(D_00611FC8)
    /* DE164 001DE164 24000010 */  b          .L001DE1F8
    /* DE168 001DE168 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE16C
    /* DE16C 001DE16C 6300053C */  lui        $5, %hi(D_0062D600)
    /* DE170 001DE170 2D20A003 */  daddu      $4, $29, $0
    /* DE174 001DE174 6284090C */  jal        func_00261188
    /* DE178 001DE178 00D6A524 */   addiu     $5, $5, %lo(D_0062D600)
    /* DE17C 001DE17C 1E000010 */  b          .L001DE1F8
    /* DE180 001DE180 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE184
    /* DE184 001DE184 6300053C */  lui        $5, %hi(D_0062D608)
    /* DE188 001DE188 2D20A003 */  daddu      $4, $29, $0
    /* DE18C 001DE18C 6284090C */  jal        func_00261188
    /* DE190 001DE190 08D6A524 */   addiu     $5, $5, %lo(D_0062D608)
    /* DE194 001DE194 18000010 */  b          .L001DE1F8
    /* DE198 001DE198 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE19C
    /* DE19C 001DE19C 6300053C */  lui        $5, %hi(D_0062D610)
    /* DE1A0 001DE1A0 2D20A003 */  daddu      $4, $29, $0
    /* DE1A4 001DE1A4 6284090C */  jal        func_00261188
    /* DE1A8 001DE1A8 10D6A524 */   addiu     $5, $5, %lo(D_0062D610)
    /* DE1AC 001DE1AC 12000010 */  b          .L001DE1F8
    /* DE1B0 001DE1B0 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE1B4
    /* DE1B4 001DE1B4 6300053C */  lui        $5, %hi(D_0062D618)
    /* DE1B8 001DE1B8 2D20A003 */  daddu      $4, $29, $0
    /* DE1BC 001DE1BC 6284090C */  jal        func_00261188
    /* DE1C0 001DE1C0 18D6A524 */   addiu     $5, $5, %lo(D_0062D618)
    /* DE1C4 001DE1C4 0C000010 */  b          .L001DE1F8
    /* DE1C8 001DE1C8 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE1CC
    /* DE1CC 001DE1CC 6100053C */  lui        $5, %hi(D_00611FD8)
    /* DE1D0 001DE1D0 2D20A003 */  daddu      $4, $29, $0
    /* DE1D4 001DE1D4 6284090C */  jal        func_00261188
    /* DE1D8 001DE1D8 D81FA524 */   addiu     $5, $5, %lo(D_00611FD8)
    /* DE1DC 001DE1DC 06000010 */  b          .L001DE1F8
    /* DE1E0 001DE1E0 B8A3828F */   lw        $2, %gp_rel(D_0062AFA8)($28)
.align 2
  jlabel .L001DE1E4
    /* DE1E4 001DE1E4 6100053C */  lui        $5, %hi(D_00611FE8)
    /* DE1E8 001DE1E8 2D20A003 */  daddu      $4, $29, $0
    /* DE1EC 001DE1EC 6284090C */  jal        func_00261188
    /* DE1F0 001DE1F0 E81FA524 */   addiu     $5, $5, %lo(D_00611FE8)
    /* DE1F4 001DE1F4 B8A3828F */  lw         $2, %gp_rel(D_0062AFA8)($28)
.align 2
  .L001DE1F8:
    /* DE1F8 001DE1F8 21004010 */  beqz       $2, .L001DE280
    /* DE1FC 001DE1FC 5D00023C */   lui       $2, %hi(D_005C8010)
    /* DE200 001DE200 40191100 */  sll        $3, $17, 5
    /* DE204 001DE204 10804224 */  addiu      $2, $2, %lo(D_005C8010)
    /* DE208 001DE208 5C01048E */  lw         $4, 0x15C($16)
    /* DE20C 001DE20C 21186200 */  addu       $3, $3, $2
    /* DE210 001DE210 90010824 */  addiu      $8, $0, 0x190
    /* DE214 001DE214 07006268 */  ldl        $2, 0x7($3)
    /* DE218 001DE218 0000626C */  ldr        $2, 0x0($3)
    /* DE21C 001DE21C 0F006568 */  ldl        $5, 0xF($3)
    /* DE220 001DE220 0800656C */  ldr        $5, 0x8($3)
    /* DE224 001DE224 17006668 */  ldl        $6, 0x17($3)
    /* DE228 001DE228 1000666C */  ldr        $6, 0x10($3)
    /* DE22C 001DE22C 1F006768 */  ldl        $7, 0x1F($3)
    /* DE230 001DE230 1800676C */  ldr        $7, 0x18($3)
    /* DE234 001DE234 0701A2B3 */  sdl        $2, 0x107($29)
    /* DE238 001DE238 0001A2B7 */  sdr        $2, 0x100($29)
    /* DE23C 001DE23C 0F01A5B3 */  sdl        $5, 0x10F($29)
    /* DE240 001DE240 0801A5B7 */  sdr        $5, 0x108($29)
    /* DE244 001DE244 1701A6B3 */  sdl        $6, 0x117($29)
    /* DE248 001DE248 1001A6B7 */  sdr        $6, 0x110($29)
    /* DE24C 001DE24C 1F01A7B3 */  sdl        $7, 0x11F($29)
    /* DE250 001DE250 1801A7B7 */  sdr        $7, 0x118($29)
    /* DE254 001DE254 5600023C */  lui        $2, %hi(D_0055DAD8)
    /* DE258 001DE258 6100053C */  lui        $5, %hi(D_00611FF8)
    /* DE25C 001DE25C 9004878C */  lw         $7, 0x490($4)
    /* DE260 001DE260 D8DA4224 */  addiu      $2, $2, %lo(D_0055DAD8)
    /* DE264 001DE264 2D204002 */  daddu      $4, $18, $0
    /* DE268 001DE268 F81FA524 */  addiu      $5, $5, %lo(D_00611FF8)
    /* DE26C 001DE26C 1838E800 */  mult       $7, $7, $8
    /* DE270 001DE270 0001A627 */  addiu      $6, $29, 0x100
    /* DE274 001DE274 2D40A003 */  daddu      $8, $29, $0
    /* DE278 001DE278 2C90060C */  jal        display
    /* DE27C 001DE27C 2138E200 */   addu      $7, $7, $2
.align 2
  .L001DE280:
    /* DE280 001DE280 5001BFDF */  ld         $31, 0x150($29)
    /* DE284 001DE284 4001B2DF */  ld         $18, 0x140($29)
    /* DE288 001DE288 3001B1DF */  ld         $17, 0x130($29)
    /* DE28C 001DE28C 2001B0DF */  ld         $16, 0x120($29)
    /* DE290 001DE290 0800E003 */  jr         $31
    /* DE294 001DE294 6001BD27 */   addiu     $29, $29, 0x160
endlabel shiftMotionOrientEndFunc
```
