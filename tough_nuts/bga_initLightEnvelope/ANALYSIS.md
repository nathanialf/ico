# bga_initLightEnvelope (0x001F4510) — resume analysis

182 insns, frame=0x480 (1KB stack buffer + saved regs at 0x400-0x470),
14 jal, jump table `jtbl_006134D0`. seki/src/BgAnimation.

## Signature
`void bga_initLightEnvelope(LightEnv *obj /*$4=s18*/, void **list /*$5=s22*/, int count /*$6=s21*/)`

## Dispatch — switch (obj->type @0x0, u16); range check `< 0xE` else → tail
jtbl_006134D0 mapping (index → target):
- 0,4,0xA → LOOP case (.L466C)
- 1,2,5   → `obj->unk24 = 0` (.L4664), fall to tail
- 3,6,0xB → nothing (.L4778), tail
- 7 → `obj->unk24 = func_00117C48(0); bga_InitData(obj);`  (.L473C→.L4750)
- 8 → `obj->unk24 = func_00117C48(2); bga_InitData(obj);`  (.L4744)
- 9 → `obj->unk24 = func_00117C48(1); bga_InitData(obj);`  (.L474C)
- 0xC → `obj->unk24 = setGIFad();`  (.L476C)
- 0xD → PARTICLE case (.L4568)
JTBL carve needed: match the switch (dense cases 0..0xD) so gcc emits a
table, then carve `[off, .rodata, seki/src/BgAnimation]` for 0x6134D0 so
gcc's jtbl replaces the blob's (see reference_aug6_match_tooling /
aug6_data_carve_findings memories). rodata src:
asm/aug6/data/src/cod/513290.rodata.s:285.

## PARTICLE case (.L4568, index 0xD) — the hard part (64-bit bitfields @ particle+0x20)
```
s19 = ParticleLayoutDL(&obj->unk4);
if (s19 == -1) { obj->unk24 = 0; goto tail; }          // .L4664
particle = iosFree(D_0062A324/*gp*/, 0x30, D_006133E0, 0x407);
obj->unk24 = (int)particle;
// field @ +0x20 is u64. Set bits [31:17] = s19 & 0x7FFF:
//   mask = 0xFFFF0001_0000FFFF ; field = (field & mask) | ((u64)(s19&0x7FFF) << 17)
{ u64 f = P(particle); f = (f & 0xFFFF00010000FFFFULL) | ((u64)(s19 & 0x7FFF) << 17); P(particle)=f; }
// extract signed [31:17], call GetParticleLoopFlag, store low2 = ret&3:
int e = (int)((s32)(P(particle)) >> 17);   // dsll32/dsra32 (sign-ext low32) then sra 17
int r = GetParticleLoopFlag(e);
P(particle) = (P(particle) & ~3ULL) | (r & 3);
// branch on low2:
f = P(particle);
if ((f & 3) != 0) {
    int e2 = (int)((s32)f >> 17);
    int dr = DeleteParticleEffectsByPackage(e2, D_004C3740, D_002724B0);
    P(particle) = (P(particle) & 0xFFFE0003ULL) | ((u64)(dr & 0x7FFF) << 2);   // set [16:2]
} else {
    P(particle) = f | 0x1FFFC;   // set bits [16:2] all... (0x1FFFC = bits 2..16)
}
// goto tail
```
where `P(p)` = `*(unsigned long*)((char*)p + 0x20)`.
NOTE the §5.11 sign-ext canonicalization (dsll32;dsra32;sra17) is the
permuter-risk; keep the field 64-bit, extract via `(int)((long)(int)f >> 17)`.

## LOOP case (.L466C, indices 0/4/0xA)
```
obj->unk24 = 0;
if (count > 0) {
  int i = 0;
  do {                                    // s17 = &list[i]; e=list[i]; p=e->unk15C
    void *e = list[i];
    void *p = e->unk15C;                   // +0x15C
    if (*(int*)((char*)p + 0x810) == 0) {  // assert branch (bnel skips when !=0)
        sprintf(&buf /*$sp*/, D_00613488, &obj->unk4);   // buf = 1KB stack
        debug_StdPrintfDummy(D_006134A8);
        func_001AACE0(D_006133E0, 0x41F, &buf);
        __assert(D_006133E0, 0x41F, D_0062D948);
        e = list[i]; p = e->unk15C;        // reload after assert
    }
    int r = strcmp(*(int*)((char*)p + 0x810));
    i++;
    if (r == 0) {                          // bnez skips
        obj->unk24 = list[i-1]->unk15C;    // uses s17 (pre-incr ptr): lw $2,0($17)
        void *p2 = list[i-1]->unk15C;
        obj->unk2 = (short)*(int*)((char*)p2 + 0x8);   // sh
        *(int*)((char*)p2 + 0x8) += 1;
    }
  } while (i < count);
}
// goto tail
```
Stack buffer: frame 0x480, buffer at sp+0 (~0x400 bytes) passed to
sprintf ($4=$sp) and func_001AACE0 ($6=$sp). Declare e.g.
`int buf[N] __attribute__((aligned(16)))` sized to land saved-regs at 0x400.

## Recursive tail (.L4778/.L477C/.L478C) — like bga_CalcObject
```
if (obj->unk2C) bga_initLightEnvelope(obj->unk2C, list, count);  // +0x2C
if (obj->unk30) bga_initLightEnvelope(obj->unk30, list, count);  // +0x30
```

## Globals/structs
D_006133E0 (assert file str), D_00613488/D_006134A8 (assert msgs),
D_0062D948, D_0062A324 (gp, heap id), D_004C3740, D_002724B0, jtbl_006134D0.
LightEnv: u16 type@0, short@2, sub-data@4, int unk24@0x24, child@0x2C, child@0x30.
Particle (list[i]->unk15C): int@0x810, int@0x8; iosFree-particle: u64@0x20.

## PROGRESS (2026-06-20 session)
Full reconstruction written & driving: **rc214 → rc192**. Structure CONFIRMED:
- jump-table dispatch matches EXACTLY (`lhu;sltiu 14;sll 2;addu;lw;jr a0`) — the
  switch with dense cases 0..0xD emits the table. JTBL CARVE still TODO (gcc emits
  its own local table; carve 0x6134D0 so gcc's table = ROM's).
- case 13 (particle): RELOAD `obj->unk24` each use (`LE_PARTICLE(obj->unk24)`),
  do NOT hold particle in a var — ROM does `lw $2,0x24($18); ld $3,0x20($2)` each
  time. This dropped rc214→192 and is correct dev shape.

### REMAINING ROOT (the rc192 cascade): assert-string LICM hoist
gcc -O2 hoists the 3 cold-path assert string addresses (D_006133E0, D_00613488,
D_006134A8) into callee-saved regs s7/s8 in the LOOP-CASE preheader → 9 saved regs
(s0-s8), frame -1184. ROM uses only 7 (s0-s6), frame -1152, and loads the strings
INLINE inside the cold `if(p->unk810==0)` assert block (reusing s0 for the
3×-used D_006133E0). The +32-byte frame cascades into ~dozens of offset/branch
diffs (ONE root, cf. COOKBOOK §5.10). NEXT SESSION: defeat the LICM hoist of the
conditional cold-block invariant string addrs (ee-gcc 2.9). Tried: particle-reload
(helped, unrelated). Untried: raise hot-path reg pressure so no callee-saved free
to hoist into; assert as macro w/ different string-ref form; verify whether ROM's
loop genuinely keeps obj+4 in s20 only. Seed saved by driver (best=192).

## Strategy
1. Write switch dispatch (dense 0..0xD) + simple cases + recursive tail first → get to a low rc.
2. Add LOOP case (watch the reload-after-assert + stack buffer size for frame 0x480).
3. Add PARTICLE bitfield case last (the §5.11 sign-ext is the permuter-risk).
4. JTBL carve once the switch matches structurally.
