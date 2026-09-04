# HANDOFF — relentlessly match ALL of seki/src/Packet.c (jtbls + rodata)

**Status: IN PROGRESS. Do NOT park ANY Packet function. The whole TU must go C.**

## Why this is mandatory (read first)
`pac_continueTag`'s *code* already matches byte-exact (rc1 was only the jump-table
`%lo` **relocation** debug_PrintFontWindow, i.e. a data-PLACEMENT issue, not a codegen issue).
The blocker is purely *where* gcc's jump tables land in `.rodata`. Packet's
`.rodata` is INTERLEAVED between matched-C and still-asm owners, so any *partial*
match forces an ugly placement workaround (a `.jtbl.0x<VMA>` distinct section +
splat carve special-casing). We are NOT doing that workaround. The clean,
dev-faithful, zero-tooling outcome is to match the **whole** TU so the entire
`.rodata` region is one contiguous Packet.o block placed by ordinary carves.

Therefore: grind every remaining function to rc0 + `ninja verify_elf: OK`. If one
stalls, generate new C hypotheses — never park, never per-func cflag/postprocess,
never the `.jtbl` workaround.

## THE RODATA MAP (the crux)
```
0x54F160  jtbl_0054F160   mc_setBaseOffset   (ASM)
0x54F1B0  jtbl_0054F1B0   pac_setVifEndCode     (C, matched)
0x54F1F8  D_0054F1F8…     pac_DumpPac         (ASM)  ← strings between the jtbls
0x54F290  D_0054F290…     pac_continueTag       (C)    ← openLog msg strings
0x54F380  D_0054F380      SHARED by pac_MakePacket / pac_makeStrip / pac_Init /
                          pac_makePacket / func_0011BB00 (all ASM)
0x54F390  jtbl_0054F390   pac_continueTag       (C)
```
When ALL these owners are C, define `D_0054F380` ONCE in Packet.c (shared string),
and the whole 0x54F160–0x54F390 region is a single contiguous Packet.o `.rodata`
block → place with ordinary carves, NO `.jtbl` special-casing. That is the finish
line for the rodata.

## REMAINING INCLUDE_ASM FUNCS (the set — all to rc0, none parked)
mc_setBaseOffset, mc_SetMicroCode, pac_makeClusterStrip, pac_DumpPac,
pac_makeBoundingBox, pac_makeNormalStrip, pac_getWeight, pac_makeStrip,
pac_setGifTag, pac_closeTag, pac_makePacket, pac_MakePacket, pac_countOneVertexPacketSize,
pac_Init, pac_DispVu1Memory, func_0011B2A0, func_0011B468, pac_getTextureInfo,
pac_makeShapeTable, func_0011BB00, and pac_continueTag (do LAST, once the region is
contiguous). Several are VU0/MMI-heavy (pac_MakePacket, pac_countOneVertexPacketSize, pac_DispVu1Memory)
— match in clean C via include/vu0.h + include/r5900.h intrinsics; see the existing
_RotTransCurrentMatrix / _GetRandomVector0 / _GetRandom in Packet.c for the house VU0 idioms.
Suggested order: rodata-critical first (pac_DumpPac, mc_setBaseOffset, the
D_0054F380 sharers), then the pure-code funcs, then pac_continueTag.

## COMMIT STRATEGY (the rodata region CANNOT be committed piecemeal)
- **Pure-code funcs** (no jtbl / no string literals) → commit individually; the
  link stays byte-identical so the pre-commit ninja gate passes.
- **Rodata-producing funcs** (mc_setBaseOffset, pac_DumpPac, pac_continueTag,
  and the D_0054F380 sharers) **cannot** be committed one at a time — each adds a
  non-contiguous Packet.o `.rodata` piece that won't place until the WHOLE region
  is contiguous-C. Iterate them with `match_loop.py diff` (compiles a single `.o`
  and compares — needs NO green link); leave the working tree red between funcs;
  only when ALL rodata owners are rc0 AND the contiguous carve is set, run
  `VERSION=aug6 ninja` → `verify_elf: OK` ONCE and commit the whole rodata cluster
  together. The pre-commit hook enforces this (it runs the full SHA gate), so a
  half-contiguous state simply can't be committed.

## BUILD / GATE FACTS (verify, don't assume)
- aug6 IS main. Use `VERSION=aug6` and full TU stem `seki/src/Packet` for
  match_loop / quick_diff / ninja. Tools are python3: `python3 tools/match_loop.py …`.
- Oracle = `baserom/aug6/baseelf.rom`, sha1 `2b4d7de41966ff38d061b4c985de45fc212e2fb2`,
  size 5430606. WARNING: `baserom/baseelf.rom` (repo ROOT) is a STALE DIFFERENT
  file (fbf50c75, 5454790 bytes) — never cmp against it.
- Authoritative gate = `VERSION=aug6 ninja` → `verify_elf: OK`. quick_diff /
  match_diff PHANTOM-diff on (a) in-TU symbol/jtbl `%lo` relocs and (b) VU0-fallback
  TUs (period-as can't parse a VU0 sibling → modern-as fallback inserts a nop the
  real build doesn't). On an rc1-with-sole-reloc/extra-nop, confirm via ninja.
- Per-func cflags and per-func `.s` postprocess allowlists are RETIRED — not allowed.

## CURRENT UNCOMMITTED STATE (build is RED; clean it up first)
The tree currently holds a half-applied jtbl-placement workaround (the thing we are
ABANDONING). Build is RED (sha 504b5c79, +128 bytes). Recommended first step —
revert to green HEAD, then grind forward:
```
git checkout config/ico.aug6.yaml seki/src/Packet.c
rm -f config/jtbl_distinct_section.txt
# then re-apply ONLY the split_jtbls FUNC_LABEL_RE one-liner (see below); revert the
# rest of tools/postprocess_split_jtbls.py:
git checkout tools/postprocess_split_jtbls.py
```
- `config/ico.aug6.yaml` — dict-form `linker_section` carves + a 0x44F390 carve (workaround; revert).
- `config/jtbl_distinct_section.txt` — NEW workaround config (delete).
- `seki/src/Packet.c` — pac_continueTag converted to C (re-apply LAST, see below).
- `tools/postprocess_split_jtbls.py` — TWO changes: (1) **FUNC_LABEL_RE broadened**
  to any C identifier guarded by `== last_globl` — this is a CORRECT, NEEDED fix
  (named-symbol funcs like `pac_*` never had their `$L` jtbl labels mapped, so
  split_jtbls couldn't place their jtbls; without it the contiguous-region jtbls
  won't split). KEEP/re-apply this. (2) the `.jtbl` distinct-section logic +
  `_load_distinct_funcs` — that's the workaround; drop it.

  The FUNC_LABEL_RE fix is just:
  `FUNC_LABEL_RE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*:")`
  (was `r"^\s*(func_[0-9A-Fa-f]{8})\s*:"`). Safe because the existing
  `if m and m.group(1) == last_globl:` guard restricts it to the .globl'd entry.

## pac_continueTag — ALREADY RECOVERED (re-apply LAST, with contiguous rodata)
rc1, sole diff = jtbl `%lo` reloc (placement only); code is byte-exact.
```c
extern char D_0066CB50[];
extern char D_0054F290[], D_0054F2C0[], D_0054F2F0[], D_0054F320[], D_0054F358[], D_0054F380[];
extern char D_0062BE78[];
extern void debug_openLog(char *msg, char *ctx, void *obj);
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
void pac_continueTag(void *a0, int a1) {
    switch (a1) {
    case 1: debug_openLog(D_0054F290, D_0066CB50, a0); break;
    case 2: debug_openLog(D_0054F2C0, D_0066CB50, a0); break;
    case 3: debug_openLog(D_0054F2F0, D_0066CB50, a0); break;
    case 4: debug_openLog(D_0054F320, D_0066CB50, a0); break;
    case 5: debug_openLog(D_0054F358, D_0066CB50, a0); break;
    }
    func_001AAD00(D_0054F380, 0x2A9);
    __assert(D_0054F380, 0x2A9, D_0062BE78);
}
```
**VOID return is essential**: __assert's args are an arg-reshuffle (none are
caller params) so gcc sibcalls with `j` only when the return is void (see the
`void_return_reshuffle_tco` memory). int-return → frame+jal mismatch.

## STANDING INSTRUCTIONS
- No AI co-author trailer in commits.
- Remove each matched func's line from `config/sweep_parked.txt` as you go.
- Do NOT edit `config/sha1sums.txt`.
- Already committed this session (leave them): func_00230C10 (st22a),
  GetTableArcCos (seki/DisplayP2O). Task #3 (pac_continueTag) is in_progress; the
  Stop-hook guard tracks build/match_loop/*.json — resolve by real rc0, not by
  releasing the marker.
```
```
