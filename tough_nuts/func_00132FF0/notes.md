# func_00132FF0 — near-miss rc65 (iosCdvdMgrOpen)

VRAM 0x00132FF0  TU ios/cdvd.c  (122 insns, frame 0x250, 15 jal)
Seed: func_00132FF0.c (full TU at rc65). ALGORITHM fully traced & written.

## What it does
strchr(name,'/')->base; sprintf(buf,"DFDATAS/%s",base?base+1:name);
strcpy(name,buf); sprintf(namebuf,D_00631F70,name); normalise namebuf
(D_0062FC79 idiom); strcpy(name,namebuf); clear self[0x158..0x15A],
self[0x24]=0; if(sceCdDiskReady(1)!=2){ copy "SCUS_971.13"(D_005567F0) into disk;
func_00133218(disk); do{printf("wait insert");sceCdDiskReady(0);}
while(func_0024D718()!=0x12 || sceCdSearchFile(namebuf,disk)==0); }
self[0xC]=0; func_001312F0(self); size=self[0x138];
self[0x2C]=((unsigned)(size-1)>>11)+1; got=func_00135EB8(0x120010,"ios/cdvd.c",
0x85C); self[0x160]=got; self[0x164]=(got+0xF)&~0xF; sceCdStInit(0x240,0x24,
rounded); sceCdStStart(self[0x134], self+0x158); self[0x8180]=self[0x138].

## Remaining: multi-register cascade (rc65) — same class as func_001312F0

Frame 0x270 (built) vs 0x250 (ROM): built uses 6 callee-saved, ROM 5. ROM does
HEAVY register reuse the dev's lifetimes produced:
  $16 = namebuf loop-cursor (sp+0x100, spans the sprintf call)
  $17 = self        $18 = name (self+0x34) -> REUSED for %hi(D_00556800)
  $19 = name copy -> REUSED for self+0x158 (sceCdStStart arg)
Built gives self=$16 (one-register shift) and doesn't reuse, needing an extra
callee-saved reg. Also `base?base+1:name` emits movz (ROM branches via bnez+delay).

## Next levers (fresh eyes) — apply the func_001312F0 playbook
- INLINE self+0x34 at call sites (don't hoist one `name`) so gcc makes the two
  copies ($18/$19), as inline-self+0x34 did for func_001312F0.
- Reuse one pointer var for self+0x158 AND have its prior name-use end first
  (q coalesced when assigned the same self+0x34 expr — needs the live ranges to
  not overlap so gcc reuses the reg).
- [[int_return_pushes_v0_to_v1]] for any post-call v0/v1; [[far_global_direct_index_hoists_hi]].
- NOT a floor — algorithm correct; pure regalloc/lifetime grind.
