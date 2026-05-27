# func_001F34C8 (src/weapon.c) — near-match, NOT byte-matched

VRAM 0x001F34C8, 0x228 (138 insns). FP + 64-byte struct copy.
asm/nonmatchings/src/weapon/func_001F34C8.s

## Status: skill-run draft compiles at real_count 73 (match_diff). Structure
roughly correct; needs reasoning, NOT the permuter.

Seed: func_001F34C8.c (apply into src/weapon.c replacing the INCLUDE_ASM, but
DROP the externs weapon.c already has — struct E36, D_006124F8, D_004C6330,
D_0061A850; ADD forward externs for D_00632010 / func_0013A0F8 / func_00105F00
since weapon.c declares them AFTER this function). Args: (self=$4, a1=$5,
a2=$6→src). req = {self, i, pad[2], WBody body}; body = *(WBody*)src then
body[0x30]=flag; flag = (src[0x30]&0xFF00)?5:4 (movn). Loop n=0..0 builds an
object via func_001B7FE8(0xA,0x45,-1,n==0,&req.body,-1,7,0); a 2nd object via
func_001B7FE8(0x2D,9,...). FP: D_004C6330[2] = D_006124F8[idx].f0 * (float)n /
$f20(=0).

## THE ROOT (drives most of the 73 — one cascade, per the match-loop principle)
The 64-byte `WBody` copy `req.body = *(WBody*)src`: the ORIGINAL loads all 8
longlongs into DISTINCT regs (ld $10,$13,$14,$12,$11,$9,$3,$2) THEN stores all
(sd ...) — a batched load-all/store-all. The build SERIALIZES (`ld v0;sd v0;…`
reusing v0/v1). Fixing the copy strategy collapses the prologue cascade.
NEXT to try (playbook): (1) the two copies (req.body AND body2 = *(WBody*)src)
may force gcc to serialize — try a single copy + reuse, or distinct struct vars;
(2) WBody as `long long d[8]` vs a different aggregate may change the copy
lowering; (3) the src $18 / n $17 REG pins may add pressure that serializes —
try without; (4) ensure req.body[0x30]=flag is a single `sw` after the copy.
Residual tags after the copy: fp-licm ($f20 scale) + far-global §5.7.

This is a reason-it-down function (do NOT early-permute — regalloc/struct-copy
shapes are hand-fixable here). A fresh /decomp-match session with full token
budget should take it. Cousins: §6.x (qword/aggregate copy), the playbook in
.claude/skills/decomp-match/SKILL.md.
