# actCommonRope — parked

VRAM: 0x00156900 (file_off 0x056900)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/actCommonRope.s

## Attempt at 2026-07-07

**Reason parked:** rc3; STRUCTURE 100% CORRECT (_GetRandom()*10.0f cvt, n%15 early r-temp cracked rc37->3, volatile a0 double-deref 0x164->0x670 read 0x214/write 0x218, ACTParaStatus_Exec(a0), func_00156750(r,val,&a0) 3-arg reuses a0-home as buf, _ACTWait(0)). Residual=2 diffs: (1) ROM fills ACTParaStatus_Exec jal DELAY with the 0x218 store; built schedules store early+nop-in-delay (sched2 store-vs-mfhi priority tie); (2) buf &a0/sp -> v0 (ROM) vs a2 (built) regalloc coloring. 5 distinct attempts (3-arg rc3, 2-arg rc5, store-after rc19, self-snapshot rc10, inline-mod rc37). permuter-class dbr/regalloc.

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/actCommonRope/actCommonRope.c`

Disassembly:

```
.align 3
nonmatching actCommonRope, 0x98

glabel actCommonRope
    /* 56900 00156900 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 56904 00156904 2000B1FF */  sd         $17, 0x20($29)
    /* 56908 00156908 1000B0FF */  sd         $16, 0x10($29)
    /* 5690C 0015690C 0000A4AF */  sw         $4, 0x0($29)
    /* 56910 00156910 3000BFFF */  sd         $31, 0x30($29)
    /* 56914 00156914 A463040C */  jal        _GetRandom
    /* 56918 00156918 00000000 */   nop
    /* 5691C 0015691C 2041013C */  lui        $1, (0x41200000 >> 16)
    /* 56920 00156920 00088144 */  mtc1       $1, $f1
    /* 56924 00156924 0F000324 */  addiu      $3, $0, 0xF
    /* 56928 00156928 01006050 */  beql       $3, $0, .L00156930
    /* 5692C 0015692C CD010000 */   break     0, 7
.align 2
  .L00156930:
    /* 56930 00156930 0000A28F */  lw         $2, 0x0($29)
    /* 56934 00156934 02000146 */  mul.s      $f0, $f0, $f1
    /* 56938 00156938 0000A58F */  lw         $5, 0x0($29)
    /* 5693C 0015693C 6401468C */  lw         $6, 0x164($2)
    /* 56940 00156940 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 56944 00156944 00080444 */  mfc1       $4, $f1
    /* 56948 00156948 6401A28C */  lw         $2, 0x164($5)
    /* 5694C 0015694C 7006C78C */  lw         $7, 0x670($6)
    /* 56950 00156950 1A008300 */  div        $0, $4, $3
    /* 56954 00156954 7006458C */  lw         $5, 0x670($2)
    /* 56958 00156958 1402F08C */  lw         $16, 0x214($7)
    /* 5695C 0015695C 0000A48F */  lw         $4, 0x0($29)
    /* 56960 00156960 10880000 */  mfhi       $17
    /* 56964 00156964 2022050C */  jal        ACTParaStatus_Exec
    /* 56968 00156968 1802B0AC */   sw        $16, 0x218($5)
    /* 5696C 0015696C 2D280002 */  daddu      $5, $16, $0
    /* 56970 00156970 2D202002 */  daddu      $4, $17, $0
    /* 56974 00156974 D459050C */  jal        func_00156750
    /* 56978 00156978 2D10A003 */   daddu     $2, $29, $0
    /* 5697C 0015697C 6004080C */  jal        _ACTWait
    /* 56980 00156980 2D200000 */   daddu     $4, $0, $0
    /* 56984 00156984 3000BFDF */  ld         $31, 0x30($29)
    /* 56988 00156988 2000B1DF */  ld         $17, 0x20($29)
    /* 5698C 0015698C 1000B0DF */  ld         $16, 0x10($29)
    /* 56990 00156990 0800E003 */  jr         $31
    /* 56994 00156994 4000BD27 */   addiu     $29, $29, 0x40
endlabel actCommonRope
```
