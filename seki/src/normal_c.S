; -----------------------------------------------------------------------
; NormalCMicroProgram — VU1 microprogram (ico2000.a normal_c.o), seki/GS renderer.
;
; One of the 5 per-primitive VU1 microprograms in ICO's .vutext section
; (cluster/mesh/normal_c/normal_l/particle), managed by MicroCode.o
; (mc_TransMicroCode).  Split by the MAIN.MAP .vutext .o boundaries.
;
; Clean-room: bytes re-derived from published VU0/VU1 documentation
; (EE User's Manual, PCSX2 microVU GPL-3.0 opcode dispatch, ps2sdk) via
; tools/assemble_vu0.py — never from extracted disc data.  The whole
; 0x50E0-byte .vutext section is byte-identical across all three known
; builds — the Aug-6-2001 prototype, USA retail (SCUS-971.13) and PAL
; retail (SCES-507.60) — so this one source serves every branch.  In the
; PAL ELF this program lives at 0x0028B380 (5856 bytes); labels below
; are program-relative (VU micromem is loaded at 0).
;
; LABELS.  The uppercase names are the DVP assembler's own labels,
; recovered from the PAL disc's `SRCFILE.TXT` link listing, which carries
; the .vutext symbol table with the microprogram's local labels spelled
; `_$NAME`.  `_$` is the assembler's local-label decoration, so the source
; spelling here drops it (`_$SET_GSREGISTER` -> `SET_GSREGISTER`); the
; full old->new table is in decomp/MATCH_VU.md.  Labels with no listing
; counterpart keep their synthetic hand-typing names (offsets given
; because some of those numeric suffixes are legacy section-relative
; addresses):
; L_06F8 (+0x06F8), L_0808 (+0x0808), L_0820 (+0x0820), L_08D8
; (+0x08D8), sub_2818 (+0x1068), sub_2BB0 (+0x1400), sub_2C00 (+0x1450)
; -----------------------------------------------------------------------
.vu0
.org 0x0000
nop ; .word 0x6000016C                                ; 0x17B0 — FCSET imm24=0x16C
.word 0x4A000000 ; nop                                ; 0x17B8 — upper FMAC-family + lower true-zero

; Program-3 entry-stub dispatch (continuous from here through 0x18E8).
pad ; b SET_GSREGISTER                                ; 0x17C0 — entry → SET_GSREGISTER
pad ; nop_swap                                        ; delay slot
pad ; b SET_UVOFFSET                                  ; 0x17D0 — entry → SET_UVOFFSET
pad ; nop_swap                                        ; delay slot
pad ; nop_swap                                        ; 0x17E0 — reserved slot
pad ; nop_swap                                        ; 0x17E8 — reserved slot
pad ; nop_swap                                        ; 0x17F0 — reserved slot
pad ; nop_swap                                        ; 0x17F8 — reserved slot
pad ; b SET_FONT_OFFSET                               ; 0x1800 — entry → SET_FONT_OFFSET
pad ; nop_swap                                        ; delay slot
pad ; b START_DEBUG_FONT                              ; 0x1810 — entry → START_DEBUG_FONT
pad ; nop_swap                                        ; delay slot
pad ; b SPACE_DEBUG_FONT                              ; 0x1820 — entry → SPACE_DEBUG_FONT
pad ; nop_swap                                        ; delay slot
pad ; nop_swap                                        ; 0x1830 — reserved slot
pad ; nop_swap                                        ; 0x1838 — reserved slot
pad ; b SET_NORMAL_MATRIX                             ; 0x1840 — entry → SET_NORMAL_MATRIX
pad ; nop_swap                                        ; delay slot
pad ; b SET_NORMAL_LIGHT                              ; 0x1850 — entry → SET_NORMAL_LIGHT
pad ; nop_swap                                        ; delay slot
pad ; nop_swap                                        ; 0x1860 — reserved slot
pad ; nop_swap                                        ; 0x1868 — reserved slot
pad ; nop_swap                                        ; 0x1870 — reserved slot
pad ; nop_swap                                        ; 0x1878 — reserved slot
pad ; nop_swap                                        ; 0x1880 — reserved slot
pad ; nop_swap                                        ; 0x1888 — reserved slot
pad ; nop_swap                                        ; 0x1890 — reserved slot
pad ; nop_swap                                        ; 0x1898 — reserved slot
pad ; nop_swap                                        ; 0x18A0 — reserved slot
pad ; nop_swap                                        ; 0x18A8 — reserved slot
pad ; nop_swap                                        ; 0x18B0 — reserved slot
pad ; nop_swap                                        ; 0x18B8 — reserved slot
pad ; b BEGIN_NORMAL_C                                ; 0x18C0 — entry → BEGIN_NORMAL_C
pad ; nop_swap                                        ; delay slot
pad ; b BEGIN_NORMAL_C_NOCLIP                         ; 0x18D0 — entry → BEGIN_NORMAL_C_NOCLIP
pad ; nop_swap                                        ; delay slot
pad ; b sub_2BB0                                      ; 0x18E0 — entry → sub_2BB0  (far target)
pad ; nop_swap                                        ; delay slot

; =======================================================================
; PROGRAM 3 SUBROUTINE BODIES.  Most are direct clones of program 1/2
; routines at new VRAM offsets; the new ones (SET_NORMAL_MATRIX / SET_NORMAL_LIGHT /
; BEGIN_NORMAL_C / START_NORMAL_C) handle bulk-data uploads and another skinned
; transform variant.
; =======================================================================

; -----------------------------------------------------------------------
; SET_GSREGISTER — copy-with-count + xgkick + END (clone of SET_GSREGISTER (mesh)).
; -----------------------------------------------------------------------
SET_GSREGISTER:
pad ; xtop vi12
pad ; ilwr.x vi10, vi12
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; lqi.xyzw vf29, vi12
pad ; iaddiu vi13, vi00, 32767
pad ; iand vi10, vi13, vi10
pad ; sqi.xyzw vf29, vi09
SET_GSREGISTER_LOOP:
pad ; lqi.xyzw vf28, vi12
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, SET_GSREGISTER_LOOP
pad ; sqi.xyzw vf28, vi09                             ; (branch delay slot)
pad ; nop_swap
pad ; xgkick vi07
epad ; nop_swap                                       ; upper: E-bit pad (END)
pad ; nop_swap                                        ; E-bit delay slot

; -----------------------------------------------------------------------
; SET_UVOFFSET — mem[2].xy patch (clone of SET_UVOFFSET (mesh)).
; -----------------------------------------------------------------------
SET_UVOFFSET:
pad ; xtop vi01
pad ; lq.xyzw vf30, 2(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; move.xy vf30, vf31
pad ; sq.xyzw vf30, 2(vi00)
epad ; nop_swap                                       ; upper: E-bit pad (END)
pad ; nop_swap                                        ; E-bit delay slot

; -----------------------------------------------------------------------
; SET_FONT_OFFSET — 4-quad matrix upload to mem[256] (clone of SET_FONT_OFFSET (mesh)).
; -----------------------------------------------------------------------
SET_FONT_OFFSET:
pad ; xtop vi12
pad ; iaddiu vi13, vi00, 256
pad ; lqi.xyzw vf18, vi12
pad ; lqi.xyzw vf19, vi12
pad ; lqi.xyzw vf16, vi12
pad ; lqi.xyzw vf17, vi12
pad ; sqi.xyzw vf18, vi13
pad ; sqi.xyzw vf19, vi13
pad ; sqi.xyzw vf16, vi13
pad ; sqi.xyzw vf17, vi13
epad ; nop_swap                                       ; upper: E-bit pad (END)
pad ; nop_swap                                        ; E-bit delay slot

; -----------------------------------------------------------------------
; BEGIN_DEBUG_FONT — shared E-bit-only stub (clone of BEGIN_DEBUG_FONT (mesh)).
; -----------------------------------------------------------------------
BEGIN_DEBUG_FONT:
epad ; nop_swap                                       ; upper: E-bit pad (END)
pad ; nop_swap                                        ; E-bit delay slot

; -----------------------------------------------------------------------
; START_DEBUG_FONT — palette-indexed vertex transform (clone of START_DEBUG_FONT (mesh)).
; Falls through into SPACE_DEBUG_FONT for terminator.
; -----------------------------------------------------------------------
START_DEBUG_FONT:
pad ; xtop vi12
pad ; iaddiu vi11, vi12, 1
pad ; ilwr.x vi10, vi12
pad ; lq.xyzw vf29, 0(vi12)
pad ; iaddiu vi13, vi00, 32767
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; sqi.xyzw vf29, vi09
pad ; iand vi10, vi13, vi10
pad ; iaddiu vi13, vi00, 1
pad ; lq.xyzw vf09, 0(vi11)
pad ; ilwr.w vi14, vi11
pad ; nop_swap
pad ; iand vi15, vi13, vi14

LOOP_DEBUG_FONT:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)
pad ; move.w vf09, vf00
pad ; iaddiu vi11, vi11, 1
pad ; ilwr.w vi14, vi11
pad ; iaddi vi10, vi10, -1
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09
pad ; lq.xyzw vf09, 0(vi11)
pad ; iand vi15, vi13, vi14
pad ; ibne vi10, vi00, LOOP_DEBUG_FONT
pad ; sqi.xyzw vf10, vi09                             ; (branch delay slot)

pad ; nop_swap
pad ; xgkick vi07
pad ; nop_swap                                        ; falls through into SPACE_DEBUG_FONT

; -----------------------------------------------------------------------
; SPACE_DEBUG_FONT — final palette-step + `b BEGIN_DEBUG_FONT` (clone of SPACE_DEBUG_FONT (mesh)).
; -----------------------------------------------------------------------
SPACE_DEBUG_FONT:
add.xy vf16, vf16, vf17 ; nop_swap
pad ; b BEGIN_DEBUG_FONT
pad ; nop_swap                                        ; (branch delay slot)

; -----------------------------------------------------------------------
; SET_NORMAL_MATRIX — bulk 13-quad copy from VIF input to mem[16..27], plus a
; final `lq mem[3]; sq mem[37]` constant-copy.
;
; The first four quads land in vf01..vf04 (then stored to mem[16..19]);
; the next nine quads all stream through vf31 (each lqi → sq pair),
; landing in mem[20..27].  At the tail, a fixed `lq vf31, 3(vi00)`
; reads mem[3] and writes it to mem[37].
; -----------------------------------------------------------------------
SET_NORMAL_MATRIX:
pad ; xtop vi01
pad ; lqi.xyzw vf01, vi01
pad ; sq.xyzw vf01, 16(vi00)
pad ; lqi.xyzw vf02, vi01
pad ; sq.xyzw vf02, 17(vi00)
pad ; lqi.xyzw vf03, vi01
pad ; sq.xyzw vf03, 18(vi00)
pad ; lqi.xyzw vf04, vi01
pad ; sq.xyzw vf04, 19(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 20(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 21(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 22(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 23(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 24(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 25(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 26(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 27(vi00)
pad ; lq.xyzw vf31, 3(vi00)                           ; vf31 = mem[3]
pad ; sq.xyzw vf31, 37(vi00)                          ; mem[37] = vf31
epad ; nop_swap                                       ; upper: E-bit pad (END)
pad ; nop_swap                                        ; E-bit delay slot

; -----------------------------------------------------------------------
; SET_NORMAL_LIGHT — bulk 8-quad copy from VIF input via vf31 to mem[28..35].
;
; Tail-half of SET_NORMAL_MATRIX's upload pattern; each lqi/sq pair streams
; one quad through vf31 to a fixed mem slot.
; -----------------------------------------------------------------------
SET_NORMAL_LIGHT:
pad ; xtop vi01
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 28(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 29(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 30(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 31(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 32(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 33(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 34(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 35(vi00)
epad ; nop_swap                                       ; upper: E-bit pad (END)
pad ; nop_swap                                        ; E-bit delay slot

; -----------------------------------------------------------------------
; BEGIN_NORMAL_C — I-register setup + small prologue.  Same I-bit pattern
; as SET_MESH_MATRIX (mesh) (two `pad[I]` bundles loading 0x4B7FFFFE and 0x457FF000),
; consumed by `addi.w/.xy vf14, vf00`.  Falls through into START_NORMAL_C.
; -----------------------------------------------------------------------
BEGIN_NORMAL_C:
.word 0x800002FF ; .word 0x4B7FFFFE                   ; pad[I] + I = 0x4B7FFFFE
addi.w vf14, vf00 ; move.xyzw vf13, vf00              ; vf14.w = I; vf13 = 0
.word 0x800002FF ; .word 0x457FF000                   ; pad[I] + I = 0x457FF000 (= 4094.0f)
addi.xy vf14, vf00 ; nop_swap                         ; vf14.xy = I
pad ; lq.xyzw vf23, 2(vi00)                           ; vf23 = mem[2]
epad ; nop_swap                                       ; upper: E-bit pad (END)
pad ; nop_swap                                        ; E-bit delay slot

; -----------------------------------------------------------------------
; START_NORMAL_C — program-3 skinned vertex transform (variant 7).
;
; Restructured variant of START_MESH_LIGHT (mesh) / START_MESH_LIGHT_SPEC (mesh):
;   * Output base is +192 (not +252).
;   * `move.z vf23, vf00` patches vf23.z = 0 mid-setup (mem[2].z mask).
;   * `add.xyz vf21, vf17, vf23` accumulator uses .xyz lanes (not the
;     usual .xy) plus a sub.w guard `sub.w vf00, vf17, vf00`.
;   * `mulw.xyzw vf15, vf24, vf00` / `mulw.xyzw vf28, vf29, vf00` in
;     the loop body (w-broadcast scaled by vf00.w=1).
;   * Two `ibne vi04, vi00, LOOP_NORMAL_C` exit-paths (post-front-face and
;     post-back-face) each kicked by `xgkick vi01` and `b BEGIN_NORMAL_C`
;     back into BEGIN_NORMAL_C's pre-END E-bit.
;   * Uses `ibeq vi15, vi00, CONT_NORMAL_C` to skip a reset of vi05 to 3.
; -----------------------------------------------------------------------
START_NORMAL_C:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192                          ; output base = vi13 + 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddi vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; lq.xyzw vf15, 0(vi02)
sub.w       vf21, vf21, vf21 ; lq.xyzw vf17, 1(vi02)
pad ; lq.xyzw vf18, 2(vi02)
pad ; move.z vf23, vf00                               ; vf23.z = 0 (lane mask)
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
sub.w       vf00, vf17, vf00 ; lq.xyzw vf15, 3(vi02)
add.xyz     vf21, vf17, vf23 ; iaddiu vi07, vi00, 208 ; vi07 = 0xD0 clip mask
pad ; nop_swap
pad ; div Q, vf00.w, vf28.w
pad ; fsand vi15, 0x2
pad ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap

LOOP_NORMAL_C:
maddaz.xyzw vf03, vf15 ; lq.xyzw vf17, 4(vi02)
maddw.xyzw  vf29, vf04, vf00 ; ibeq vi15, vi00, CONT_NORMAL_C
pad ; iaddi vi04, vi04, -1                            ; (delay slot)
pad ; iaddiu vi05, vi00, 3
CONT_NORMAL_C:
mulq.xyz    vf28, vf28 ; iaddi vi05, vi05, -1
mulq.xyz    vf21, vf21 ; iaddiu vi02, vi02, 3
ftoi0.xyzw  vf22, vf18 ; lq.xyzw vf24, 3(vi02)
sub.w       vf00, vf17, vf00 ; div Q, vf00.w, vf29.w
sub.xyw     vf00, vf13, vf28 ; lq.xyzw vf18, 2(vi02)
sub.xyw     vf00, vf28, vf14 ; sq.xyzw vf21, 0(vi03)
ftoi4.xyz   vf19, vf28 ; sq.xyzw vf22, 1(vi03)
ftoi4.xyz   vf20, vf28 ; fsand vi15, 0x2
mulw.xyzw   vf15, vf24, vf00 ; fmand vi14, vi07
mulw.xyzw   vf28, vf29, vf00 ; fmand vi14, vi14
add.xyz     vf21, vf17, vf23 ; ibne vi14, vi07, CLIP_NORMAL_C
pad ; iaddiu vi03, vi03, 3
pad ; ibgtz vi05, CLIP_NORMAL_C_SET
pad ; nop_swap                                        ; (delay slot)
mulax.xyzw  vf01, vf15 ; ibne vi04, vi00, LOOP_NORMAL_C
madday.xyzw vf02, vf15 ; sq.xyzw vf19, -1(vi03)
pad ; xgkick vi01
pad ; nop_swap
pad ; b BEGIN_NORMAL_C                                ; → BEGIN_NORMAL_C's E-bit
pad ; nop_swap                                        ; (branch delay slot)
CLIP_NORMAL_C:
pad ; iaddiu vi05, vi00, 3
CLIP_NORMAL_C_SET:
mulax.xyzw  vf01, vf15 ; ibne vi04, vi00, LOOP_NORMAL_C
madday.xyzw vf02, vf15 ; sq.xyzw vf20, -1(vi03)
pad ; xgkick vi01
pad ; nop_swap
pad ; b BEGIN_NORMAL_C                                ; → BEGIN_NORMAL_C's E-bit
pad ; nop_swap                                        ; (branch delay slot)

; -----------------------------------------------------------------------
; BEGIN_NORMAL_C_NOCLIP — second I-register setup (clone of BEGIN_NORMAL_C), but only
; covers the first 4 bundles in this chunk; the routine extends past
; 0x1F00 into the next batch.  Stopping here at the natural seam.
; -----------------------------------------------------------------------
BEGIN_NORMAL_C_NOCLIP:
.word 0x800002FF ; .word 0x4B7FFFFE                   ; pad[I] + I = 0x4B7FFFFE
L_06F8:
addi.w vf14, vf00 ; move.xyzw vf13, vf00
.word 0x800002FF ; .word 0x457FF000                   ; pad[I] + I = 0x457FF000
addi.xy vf14, vf00 ; nop_swap
pad ; lq.xyzw vf23, 2(vi00)
epad ; nop_swap                                       ; upper: E-bit pad (END)
pad ; nop_swap                                        ; E-bit delay slot
; --- BEGIN_NORMAL_C_NOCLIP transform body (0x1ED8..0x2078) ---
; Reached directly when the EE sets VU0_TPC=0x1ED8 (or a wrapper jumps
; here).  The routine processes a vertex batch and at the loop tail
; branches `b L_06F8` back into BEGIN_NORMAL_C_NOCLIP's I-setup tail, which then
; hits the 0x1EC8 E-bit to terminate.  Same exit-via-branch-into-tail
; pattern as START_NORMAL_C / BEGIN_NORMAL_C in this program.
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddi vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; lq.xyzw vf15, 0(vi02)
sub.w       vf21, vf21, vf21 ; lq.xyzw vf17, 1(vi02)
pad ; lq.xyzw vf18, 2(vi02)
pad ; move.z vf23, vf00
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
sub.w       vf00, vf17, vf00 ; lq.xyzw vf15, 3(vi02)
pad ; iaddiu vi07, vi00, 208
pad ; nop_swap
pad ; div Q, vf00.w, vf28.w
add.xyz     vf21, vf17, vf23 ; fsand vi15, 0x2
pad ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; lq.xyzw vf17, 4(vi02)

L_0808:
maddaz.xyzw vf03, vf15 ; ibeq vi15, vi00, L_0820
.word 0x4A000100 ; nop                                ; upper: `add vf04, vf00, vf00` + flag bits (E/T-ish)
maddw.xyzw  vf29, vf04, vf00 ; iaddiu vi02, vi02, 3
L_0820:
pad ; iaddiu vi05, vi00, 3
mulq.xyz    vf28, vf28 ; iaddi vi05, vi05, -1
mulq.xyz    vf21, vf21 ; lq.xyzw vf24, 3(vi02)
ftoi0.xyzw  vf22, vf18 ; iaddi vi04, vi04, -1
ftoi4.xyz   vf19, vf28 ; div Q, vf00.w, vf29.w
sub.w       vf00, vf17, vf00 ; lq.xyzw vf18, 2(vi02)
ftoi4.xyz   vf20, vf28 ; sqi.xyzw vf21, vi03
mulw.xyzw   vf15, vf24, vf00 ; sqi.xyzw vf22, vi03
mulw.xyzw   vf28, vf29, vf00 ; ibgtz vi05, CLIP_NORMAL_C_NOCLIP_SET
pad ; fsand vi15, 0x2
add.xyz     vf21, vf17, vf23 ; ibne vi04, vi00, L_0808
mulax.xyzw  vf01, vf15 ; sqi.xyzw vf19, vi03
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_06F8                                        ; → BEGIN_NORMAL_C_NOCLIP's E-bit
pad ; nop_swap                                        ; (branch delay slot)
CLIP_NORMAL_C_NOCLIP_SET:
add.xyz     vf21, vf17, vf23 ; ibne vi04, vi00, L_0808
mulax.xyzw  vf01, vf15 ; sqi.xyzw vf20, vi03
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_06F8                                        ; → BEGIN_NORMAL_C_NOCLIP's E-bit
pad ; nop_swap                                        ; (branch delay slot)

; -----------------------------------------------------------------------
; SCISSOR_COMMON — hierarchical LOD mesh subdivision driver.
;
; Top-level dispatcher that walks 6 LOD tiers, each running the same
; per-vertex transform inner loop with different bone-count and
; mip-step parameters.  The inner subroutines are:
;   CLIP_INTER — per-vertex blend + lit-color quantize (called via
;            `bal vi02` from every tier's inner loop).
;   SAVE_LAST_LOOP — 3-quad output flush (called via `bal vi02` at each
;            tier's end).
;   END_ALL — `jr vi15` early-out (taken when vi11 hasn't accumulated
;            anything).
;   INTERPOLATE — front/back-face refinement (called via `bal vi01`).
;   LOOP_ROT_END — perspective-divide + clip-test continuation of INTERPOLATE.
;
; Setup (0x2080..0x2168):
;   - vi08 = mem[104] (input vertex buffer base)
;   - Initial L_08D8 store-pattern: copies vf22 to slots {0,9},
;     vf23 to {3}, vf24 to {6}, then re-loads through stored vi03
;     offsets and applies vf17 .xy fixups before saving back.
;   - Re-loads three quads from vi07-relative slots and integerizes
;     via itof0 (no — actually IEEE float "int-to-float" cast).
;
; Tier loop body (repeats 6 times with different constants):
;   - vi05 = work-quad-count (2048 / 1024 / 512 / 256 / 128 / 64)
;   - vi06 = mip-step          (32 / 16 / 8 / 4 / 2 / 1)
;   - vi07 = bone-row-index    (2 / 2 / 1 / 1 / 0 / 0)
;   - vi10 = inner-loop counter (3) ; vi11 = output cursor (0 initial)
;   - 3 lqi prefetches (vf21/22/23) from vi08-stream
;   - Inner loop @ L_2XXX:  `bal CLIP_INTER` ; isubiu vi10 ; ibne back
;   - `iaddiu vi08, 164 or 104` (swap input buffer)
;   - `bal SAVE_LAST_LOOP` (flush output)
;   - `ibeq vi11, END_ALL` (early-out if nothing accumulated)
;   - subw.x / addw.x toggles the sign of vf30.x for the next tier
;
; Final block (0x2540..0x2568):
;   `bal vi01, sub_2818` — jumps to a save-context subroutine that
;   reads vi10=vi11 and lqi 3 quads, then xgkicks vi02 for output.
;
; END_ALL: `jr vi15` — return-to-caller stub used by all early-out
;   `ibeq vi11, END_ALL` paths.
;
; SAVE_LAST_LOOP: 3-quad flush subroutine.  Reads 3 quads from vi08-relative
;   slots, sqi to vi09-stream, then `jr vi02` returns to caller.
;
; CLIP_INTER: per-vertex blend + lit-color subroutine.  3 add.xyzw
;   bundles produce vf17/vf18/vf19 = vf31 + vfXX (lit-additive blend),
;   then two `.word`-emitted flag-bits-set FMACs at 0x25D8/0x25E0
;   (op6=0x3F .xyz, fd=7 fs=17/21 ft=17/21 — likely partial-mask
;   accumulator collapse), then fcget polls clip flags.  Based on
;   the masked flags, branches between three slot-store paths:
;     - CO_NEXT_IN: 3 sqi (vf25/26/27 only).
;     - CUR_IN → 6 sqi (vf17..vf19 + vf25..vf27) + iaddiu vi11+=2.
;     - CI_NEXT_IN: 3 sqi (vf17..vf19) + iaddiu vi11+=1.
;   All converge at CLIP_INTER_END: `jr vi02` return.
;
; INTERPOLATE: refinement subroutine.  Computes `vf25 = mulx(vf17, vf30)`
;   and `vf26 = mulx(vf21, vf30)`, subtracts to get error vectors,
;   then loop-walks with `mr32` rotate-by-32 to swizzle lanes until
;   the per-bone error counter vi12 hits zero, dropping into LOOP_ROT_END.
;
; LOOP_ROT_END: perspective-divide path.  `div Q = vf25.x/vf27.x` then
;   `addq.x vf29` + `abs.x vf29` yields a magnitude.  Three
;   sub.xyzw bundles produce vf25/vf26/vf27 = (vf21..vf23)-(vf17..vf19),
;   each mulx'd by vf29, and finally added into vf17..vf19.  The
;   routine falls through past 0x27F8 into more code at 0x2800+.
; -----------------------------------------------------------------------
SCISSOR_COMMON:
pad ; iaddiu vi08, vi00, 104                          ; vi08 = mem[104] (input vtx base)
L_08D8:
pad ; sq.xyzw vf22, 0(vi08)                           ; mem[104+0] = vf22
pad ; sq.xyzw vf22, 9(vi08)                           ; mem[104+9] = vf22 (mirror)
pad ; sq.xyzw vf23, 3(vi08)                           ; mem[104+3] = vf23
pad ; iaddiu vi09, vi00, 164                          ; vi09 = mem[164] (output base)
pad ; sq.xyzw vf24, 6(vi08)                           ; mem[104+6] = vf24
pad ; lq.xyzw vf22, -8(vi03)                          ; reload from vi03 stream
add.xy vf22, vf22, vf17 ; lq.xyzw vf23, -5(vi03)
add.xy vf23, vf23, vf17 ; lq.xyzw vf24, -2(vi03)
add.xy vf24, vf24, vf17 ; nop_swap
pad ; sq.xyzw vf22, 2(vi08)
pad ; sq.xyzw vf22, 11(vi08)
pad ; sq.xyzw vf23, 5(vi08)
pad ; sq.xyzw vf24, 8(vi08)
pad ; lq.xyzw vf22, -5(vi07)
itof0.xyzw vf22, vf22 ; lq.xyzw vf23, -2(vi07)
itof0.xyzw vf23, vf23 ; lq.xyzw vf24, 1(vi07)
itof0.xyzw vf24, vf24 ; nop_swap
pad ; sq.xyzw vf22, 1(vi08)
pad ; sq.xyzw vf22, 10(vi08)
pad ; sq.xyzw vf23, 4(vi08)
pad ; sq.xyzw vf24, 7(vi08)

; --- LOD tier 1 ---
pad ; iaddiu vi05, vi00, 2048
pad ; iaddiu vi06, vi00, 32
pad ; iaddiu vi07, vi00, 2
pad ; iaddiu vi10, vi00, 3
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
LOOP_ZM:
pad ; bal vi02, CLIP_INTER
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, LOOP_ZM
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, SAVE_LAST_LOOP
pad ; nop_swap
.word 0x100002FF ; nop_swap                           ; pad with M-bit flag (bit 28)
pad ; ibeq vi11, vi00, END_ALL
pad ; nop_swap

; --- LOD tier 2 ---
pad ; iaddiu vi05, vi00, 1024
pad ; iaddiu vi06, vi00, 16
pad ; iaddiu vi07, vi00, 2
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11                           ; vi10 = previous tier's vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
LOOP_ZP:
pad ; bal vi02, CLIP_INTER
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, LOOP_ZP
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, SAVE_LAST_LOOP
pad ; nop_swap
pad ; ibeq vi11, vi00, END_ALL
pad ; nop_swap

; --- LOD tier 3 ---
pad ; iaddiu vi05, vi00, 128
pad ; iaddiu vi06, vi00, 2
pad ; iaddiu vi07, vi00, 0
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
LOOP_XM:
pad ; bal vi02, CLIP_INTER
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, LOOP_XM
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, SAVE_LAST_LOOP
pad ; nop_swap
pad ; ibeq vi11, vi00, END_ALL
pad ; nop_swap

; --- LOD tier 4 ---
pad ; iaddiu vi05, vi00, 64
pad ; iaddiu vi06, vi00, 1
pad ; iaddiu vi07, vi00, 0
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
LOOP_XP:
pad ; bal vi02, CLIP_INTER
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, LOOP_XP
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, SAVE_LAST_LOOP
pad ; nop_swap
pad ; ibeq vi11, vi00, END_ALL
pad ; nop_swap

; --- LOD tier 5 ---
pad ; iaddiu vi05, vi00, 512
pad ; iaddiu vi06, vi00, 8
pad ; iaddiu vi07, vi00, 1
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
LOOP_YM:
pad ; bal vi02, CLIP_INTER
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, LOOP_YM
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, SAVE_LAST_LOOP
pad ; nop_swap
pad ; ibeq vi11, vi00, END_ALL
pad ; nop_swap

; --- LOD tier 6 ---
pad ; iaddiu vi05, vi00, 256
pad ; iaddiu vi06, vi00, 4
pad ; iaddiu vi07, vi00, 1
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
LOOP_YP:
pad ; bal vi02, CLIP_INTER
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, LOOP_YP
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, SAVE_LAST_LOOP
pad ; nop_swap
pad ; ibeq vi11, vi00, END_ALL
pad ; nop_swap

; --- Final consolidation block: call save-context routine at sub_2818 ---
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
pad ; bal vi01, sub_2818                              ; call save-context routine
pad ; nop_swap

; -----------------------------------------------------------------------
; END_ALL — shared early-out return stub.  `jr vi15` jumps back to
; whatever caller set vi15 to (typically the EE-level VCALLMS).
; -----------------------------------------------------------------------
END_ALL:
pad ; jr vi15
pad ; nop_swap

; -----------------------------------------------------------------------
; SAVE_LAST_LOOP — 3-quad flush subroutine.  Loads 3 quads from mem[vi08+0..2]
; and stores them post-increment into the vi09 output stream.
; Returns via `jr vi02`.
; -----------------------------------------------------------------------
SAVE_LAST_LOOP:
pad ; lq.xyzw vf21, 0(vi08)
pad ; lq.xyzw vf22, 1(vi08)
pad ; lq.xyzw vf23, 2(vi08)
pad ; sqi.xyzw vf21, vi09
pad ; sqi.xyzw vf22, vi09
pad ; sqi.xyzw vf23, vi09
pad ; jr vi02
pad ; nop_swap

; -----------------------------------------------------------------------
; CLIP_INTER — per-vertex blend + clip-flag-driven output selection.
;
; First three FMACs add vf31 (a tier-shared base vertex) to the
; lqi'd vf21/vf22/vf23, producing vf17/vf18/vf19 as lit + position
; pairs (with output prefetch via lqi vf21/22/23 next-iter).
; Two flag-bits-set FMACs at 0x25D8/0x25E0 do partial-mask masked
; accumulator collapses (emitted as `.word`).
; fcget polls clip flags into vi01; two `iand`/`ibeq` tests select
; between three storage paths (front-face-only / both / back-face-only).
; -----------------------------------------------------------------------
CLIP_INTER:
add.xyzw vf17, vf31, vf21 ; lqi.xyzw vf21, vi08
add.xyzw vf18, vf31, vf22 ; lqi.xyzw vf22, vi08
add.xyzw vf19, vf31, vf23 ; lqi.xyzw vf23, vi08
.word 0x01D189FF ; nop_swap                           ; upper op6=0x3F .xyz fd=7 fs=17 ft=17 (FD-dispatch)
.word 0x01D5A9FF ; nop_swap                           ; upper op6=0x3F .xyz fd=7 fs=21 ft=21 (FD-dispatch)
pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
pad ; fcget vi01                                      ; vi01 = clip flag bits
pad ; iand vi04, vi01, vi05                           ; vi04 = vi01 & tier-mask
pad ; nop_swap
pad ; ibeq vi04, vi00, CUR_IN
pad ; nop_swap
pad ; iand vi04, vi01, vi06                           ; vi04 = vi01 & mip-mask
pad ; nop_swap
pad ; ibeq vi04, vi00, CO_NEXT_IN
pad ; nop_swap
pad ; b CLIP_INTER_END
pad ; nop_swap
CO_NEXT_IN:
pad ; bal vi01, INTERPOLATE                           ; refine via subroutine
pad ; nop_swap                                        ; (delay slot)
pad ; sqi.xyzw vf25, vi09                             ; store refined vf25/26/27
pad ; sqi.xyzw vf26, vi09
pad ; sqi.xyzw vf27, vi09
pad ; iaddiu vi11, vi11, 1
pad ; b CLIP_INTER_END
pad ; nop_swap
CUR_IN:
pad ; iand vi04, vi01, vi06
pad ; nop_swap
pad ; ibeq vi04, vi00, CI_NEXT_IN
pad ; nop_swap
pad ; bal vi01, INTERPOLATE                           ; refine (both-path variant)
pad ; nop_swap                                        ; (delay slot)
pad ; sqi.xyzw vf17, vi09                             ; store base vf17/18/19
pad ; sqi.xyzw vf18, vi09
pad ; sqi.xyzw vf19, vi09
pad ; sqi.xyzw vf25, vi09                             ; + refined vf25/26/27
pad ; sqi.xyzw vf26, vi09
pad ; sqi.xyzw vf27, vi09
pad ; iaddiu vi11, vi11, 2
pad ; b CLIP_INTER_END
pad ; nop_swap
CI_NEXT_IN:
pad ; sqi.xyzw vf17, vi09                             ; store base vf17/18/19 only
pad ; sqi.xyzw vf18, vi09
pad ; sqi.xyzw vf19, vi09
pad ; iaddiu vi11, vi11, 1
CLIP_INTER_END:
pad ; jr vi02                                         ; return
pad ; nop_swap

; -----------------------------------------------------------------------
; INTERPOLATE — per-bone refinement subroutine.
;
; Computes mulx-w broadcasts of vf17/vf21 by vf30, then subw.xyzw
; produces vf25/vf26 = vfXX - (vfXX*vf30.w) error vectors.  vi12 =
; vi07 + vi00 (= tier bone-row index from caller).  Loop walks vi12
; iterations, mr32-rotating vf25/vf26 each time (lane-shift trick),
; then falls into LOOP_ROT_END for the perspective-divide path.
; -----------------------------------------------------------------------
INTERPOLATE:
mulx.w vf25, vf17, vf30 ; iadd vi12, vi00, vi07
mulx.w vf26, vf21, vf30 ; nop_swap
subw.xyzw vf25, vf17, vf25 ; nop_swap
subw.xyzw vf26, vf21, vf26 ; nop_swap
pad ; nop_swap
LOOP_ROT:
pad ; ibeq vi12, vi00, LOOP_ROT_END
pad ; nop_swap
pad ; mr32.xyzw vf25, vf25
pad ; mr32.xyzw vf26, vf26
pad ; isubiu vi12, vi12, 1
pad ; b LOOP_ROT
pad ; nop_swap

; -----------------------------------------------------------------------
; LOOP_ROT_END — perspective-divide + clip-test continuation.  Computes
; Q = vf25.x / vf27.x, |Q|, then mixes the per-axis differences by
; abs-Q to produce vf25/vf26/vf27 = vf17/vf18/vf19 + Q*(vfXX-vfYY).
; Bundle 0x27C8 is another flag-bits-set FMAC variant (`.word`).
; -----------------------------------------------------------------------
LOOP_ROT_END:
sub.xyz vf27, vf26, vf25 ; nop_swap
pad ; div Q, vf25.x, vf27.x
addq.x vf29, vf00 ; waitq
abs.x vf29, vf29 ; nop_swap
sub.xyzw vf25, vf21, vf17 ; nop_swap
.word 0x4AD60200 ; nop                                ; upper: `add.yz vf08, vf00, vf22` + flag bits
sub.xyzw vf26, vf22, vf18 ; nop_swap
sub.xyzw vf27, vf23, vf19 ; nop_swap
mulx.xyzw vf25, vf25, vf29 ; nop_swap
mulx.xyzw vf26, vf26, vf29 ; nop_swap
mulx.xyzw vf27, vf27, vf29 ; nop_swap
add.xyzw vf25, vf25, vf17 ; nop_swap
add.xyzw vf26, vf26, vf18 ; nop_swap
add.xyzw vf27, vf27, vf19 ; nop_swap
pad ; jr vi01                                         ; return to INTERPOLATE-call-site

; -----------------------------------------------------------------------
; sub_2818 (= sub_2818) — save-context vertex output subroutine.
;
; Called by SCISSOR_COMMON's `bal vi01, sub_2818`.  Builds a GIF packet via
; mem[vi02], applies matrix transform + perspective divide to vi03-
; stream vertices, ftoi-converts, stores via sq/sqi, then xgkicks the
; final packet.  Two xgkick stages: one with mem[8..11] matrix
; (initial), one with mem[16..19] matrix (post-transform).
; -----------------------------------------------------------------------
sub_2818:
pad ; nop_swap                                        ; (entry — also delay slot from sub_2818 caller)
pad ; iaddiu vi02, vi00, 37                           ; vi02 = mem[37] (GIF tag slot)
pad ; iadd vi03, vi00, vi08                           ; vi03 = vi08 (input cursor)
pad ; iaddiu vi07, vi02, 2                            ; vi07 = vi02 + 2 (output cursor)
pad ; iaddiu vi11, vi00, 32767                        ; vi11 = 0x7FFF
pad ; iaddiu vi11, vi11, 1                            ; vi11 = 0x8000
pad ; isw.x vi11, 0(vi02)                             ; mem[vi02].x = 0x8000 (count word)
pad ; lq.xyzw vf01, 8(vi00)                           ; load matrix M0
pad ; lq.xyzw vf02, 9(vi00)                           ; M1
pad ; lq.xyzw vf03, 10(vi00)                          ; M2
pad ; lq.xyzw vf04, 11(vi00)                          ; M3
pad ; xgkick vi02                                     ; kick initial GIF packet
pad ; iaddiu vi11, vi10, 32767                        ; vi11 = vi10 + 0x7FFF
pad ; iaddiu vi11, vi11, 1                            ; vi11 = vi10 + 0x8000
pad ; isw.x vi11, 0(vi02)                             ; mem[vi02].x = vi11 (count)

LOOP2:
pad ; lq.xyzw vf20, 0(vi03)                           ; vf20 = *vi03 (input vertex)
mulax.xyzw  vf01, vf20 ; nop_swap                     ; ACC = vf01 * vf20.x
madday.xyzw vf02, vf20 ; nop_swap
maddaz.xyzw vf03, vf20 ; nop_swap
maddw.xyzw  vf25, vf04, vf20 ; nop_swap               ; vf25 = ACC + vf04*vf20.w
pad ; div Q, vf00.w, vf25.w                           ; Q = 1/vf25.w
mulq.xyzw   vf25, vf25 ; waitq                        ; vf25 *= Q (perspective)
ftoi4.xyzw  vf26, vf25 ; nop_swap                     ; vf26 = ftoi4(vf25)
pad ; sq.xyzw vf26, 1(vi07)
pad ; lq.xyzw vf20, 2(vi03)                           ; vf20 = mem[vi03+2]
mulq.xyz    vf28, vf20 ; nop_swap                     ; vf28 = vf20 * Q
pad ; sq.xyzw vf28, -1(vi07)
pad ; lq.xyzw vf27, 1(vi03)                           ; vf27 = mem[vi03+1]
ftoi0.xyzw  vf29, vf27 ; nop_swap                     ; vf29 = ftoi0(vf27)
pad ; sq.xyzw vf29, 0(vi07)
pad ; iaddiu vi07, vi07, 3
pad ; iaddiu vi03, vi03, 3
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, LOOP2
pad ; nop_swap                                        ; (branch delay slot)
pad ; xgkick vi02                                     ; kick transformed GIF packet
pad ; lq.xyzw vf01, 16(vi00)                          ; reload matrix M0 from mem[16..19]
pad ; lq.xyzw vf02, 17(vi00)
pad ; lq.xyzw vf03, 18(vi00)
pad ; lq.xyzw vf04, 19(vi00)
pad ; nop_swap
pad ; jr vi01                                         ; return to SCISSOR_COMMON caller
pad ; nop_swap                                        ; (delay slot)

; -----------------------------------------------------------------------
; SCISSOR_COMMON_PUSHREGISTER — VU0 register-bank save routine.
;
; Stores all 15 float registers vf17..vf31 (via sqd post-decrement
; into the vi14 stack), then packs all 14 int registers vi02..vi15
; into 4 quads via iswr (one lane per int).  Used as an interrupt
; save / context-switch primitive.  Caller saves vi14 (= "stack top")
; before calling; this routine returns via `jr vi15`.
; -----------------------------------------------------------------------
SCISSOR_COMMON_PUSHREGISTER:
pad ; sqd.xyzw vf17, vi14
pad ; sqd.xyzw vf18, vi14
pad ; sqd.xyzw vf19, vi14
pad ; sqd.xyzw vf20, vi14
pad ; sqd.xyzw vf21, vi14
pad ; sqd.xyzw vf22, vi14
pad ; sqd.xyzw vf23, vi14
pad ; sqd.xyzw vf24, vi14
pad ; sqd.xyzw vf25, vi14
pad ; sqd.xyzw vf26, vi14
pad ; sqd.xyzw vf27, vi14
pad ; sqd.xyzw vf28, vi14
pad ; sqd.xyzw vf29, vi14
pad ; sqd.xyzw vf30, vi14
pad ; sqd.xyzw vf31, vi14
pad ; isubiu vi14, vi14, 1                            ; vi14--
pad ; iswr.x vi02, vi14                               ; pack vi02..vi05 → quad
pad ; iswr.y vi03, vi14
pad ; iswr.z vi04, vi14
pad ; iswr.w vi05, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi06, vi14                               ; vi06..vi09 → quad
pad ; iswr.y vi07, vi14
pad ; iswr.z vi08, vi14
pad ; iswr.w vi09, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi10, vi14                               ; vi10..vi13 → quad
pad ; iswr.y vi11, vi14
pad ; iswr.z vi12, vi14
pad ; iswr.w vi13, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi14, vi14                               ; vi14, vi15 → quad (vi00/vi01 omitted)
pad ; iswr.y vi15, vi14
pad ; nop_swap
pad ; jr vi15
pad ; nop_swap

; -----------------------------------------------------------------------
; SCISSOR_COMMON_POPREGISTER — VU0 register-bank restore routine.
;
; Reverses SCISSOR_COMMON_PUSHREGISTER: unpacks 4 int-saving quads via ilwr (one lane per
; int), then lqi 15 floats back into vf17..vf31 (in reverse order:
; vf31 first since save order is reverse).  Caller pre-loads vi14
; to the bottom-of-stack slot; routine returns via `jr vi01`.
; -----------------------------------------------------------------------
SCISSOR_COMMON_POPREGISTER:
pad ; iadd vi01, vi00, vi15                           ; vi01 = vi15 (save return target)
pad ; iswr.x vi14, vi14                               ; ?? (write-back vi14/vi15 first)
pad ; iswr.y vi15, vi14
pad ; iaddiu vi14, vi14, 1                            ; vi14++
pad ; ilwr.x vi10, vi14                               ; unpack vi10..vi13 from quad
pad ; ilwr.y vi11, vi14
pad ; ilwr.z vi12, vi14
pad ; ilwr.w vi13, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi06, vi14                               ; vi06..vi09
pad ; ilwr.y vi07, vi14
pad ; ilwr.z vi08, vi14
pad ; ilwr.w vi09, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi02, vi14                               ; vi02..vi05
pad ; ilwr.y vi03, vi14
pad ; ilwr.z vi04, vi14
pad ; ilwr.w vi05, vi14
pad ; iaddiu vi14, vi14, 1
pad ; lqi.xyzw vf31, vi14                             ; restore vf17..vf31 (reverse)
pad ; lqi.xyzw vf30, vi14
pad ; lqi.xyzw vf29, vi14
pad ; lqi.xyzw vf28, vi14
pad ; lqi.xyzw vf27, vi14
pad ; lqi.xyzw vf26, vi14
pad ; lqi.xyzw vf25, vi14
pad ; lqi.xyzw vf24, vi14
pad ; lqi.xyzw vf23, vi14
pad ; lqi.xyzw vf22, vi14
pad ; lqi.xyzw vf21, vi14
pad ; lqi.xyzw vf20, vi14
pad ; lqi.xyzw vf19, vi14
pad ; lqi.xyzw vf18, vi14
pad ; lqi.xyzw vf17, vi14
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_2BB0 — `jr vi01` return stub.  Reachable as a dispatch-table
; entry (TPC=0xE0 → b sub_2BB0 in program 3's table) and as a fall-
; through from SCISSOR_COMMON_POPREGISTER's context-restore tail.
; -----------------------------------------------------------------------
sub_2BB0:
pad ; jr vi01
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_2BC0 — vertex-buffer init / clear.  Sets up vf17/vf31 to known
; values, loads working matrix from mem[20..23], and initializes
; vi14 = 256 (heap base).  Terminates via E-bit.
; -----------------------------------------------------------------------
BEGIN_SCISSOR_C:
sub.xyzw vf31, vf00, vf00 ; lq.xyzw vf17, 2(vi00)     ; vf31 = 0; vf17 = mem[2]
pad ; lq.xyzw vf13, 20(vi00)
pad ; lq.xyzw vf14, 21(vi00)
pad ; lq.xyzw vf15, 22(vi00)
pad ; lq.xyzw vf16, 23(vi00)
mulw.w vf17, vf00, vf00 ; iaddiu vi14, vi00, 256
pad ; move.z vf17, vf00                               ; vf17.z = 0
epad ; nop_swap                                       ; upper: E-bit pad (END)

; -----------------------------------------------------------------------
; sub_2C00 — bone-blended vertex transform with clip-flag culling.
;
; Reads vi01 (VIF top), masks count in vi10, output base vi02 = vi01
; + 192.  Per-vertex loop blends two bones (vf18/vf21/vf20 source +
; vf04/vf03 dest), perspective-divides, ftoi4-converts, and stores
; one of two output paths based on clip-flag testing via fcand /
; fcor against a sequence of magic bit-masks at 0x2DB0..0x2E30.
;
; The clip-mask sequence (0xFDF7DF, 0xFEFBEF, 0xFF7DF7, 0xFFBEFB,
; 0xFFDF7D, 0xFFEFBE) progressively excludes one clip plane per
; iteration; if any of them indicate a fully-visible vertex (ibne
; fires), control falls into the L_1690 path which `bal vi15`s to
; the SCISSOR_COMMON_PUSHREGISTER save-context, L_08D8 hierarchical-driver, and SCISSOR_COMMON_POPREGISTER
; restore-context routines in sequence (effectively recursing into
; the LOD subdivider for that vertex), then `b SCISSOR_C_XYZ2` continues
; the per-vertex loop.  Otherwise (no fall-through), branches to
; SCISSOR_C_XYZ2 directly.
;
; Output kick: `xgkick vi02` + `b BEGIN_SCISSOR_C` returns to the init stub's
; E-bit at 0x2BF8.
;
; Bundles 0x2CD8, 0x2CE0, 0x2CF0 are flag-bits-set FMACs (FD-dispatch
; .xyz variants) emitted via `.word`.
; -----------------------------------------------------------------------
sub_2C00:
pad ; nop_swap                                        ; (entry — also E-bit delay slot of BEGIN_SCISSOR_C)
pad ; xtop vi01                                       ; vi01 = VIF top
pad ; ilwr.x vi10, vi01                               ; vi10 = *(int*)vi01 (count)
pad ; iaddiu vi11, vi00, 32767                        ; vi11 = 0x7FFF
pad ; iand vi10, vi10, vi11                           ; vi10 &= 0x7FFF
pad ; iaddi vi11, vi11, 1                             ; vi11 = 0x8000
pad ; lq.xyzw vf25, 0(vi01)                           ; vf25 = mem[vi01] (header quad)
pad ; iaddiu vi03, vi01, 1                            ; vi03 = vi01 + 1 (input cursor)
pad ; iaddiu vi02, vi01, 192                          ; vi02 = vi01 + 192 (output base)
pad ; sq.xyzw vf25, 0(vi02)                           ; store header
pad ; iaddiu vi07, vi02, 1                            ; vi07 = vi02 + 1 (output cursor)
mulw.xyzw   vf22, vf00, vf00 ; iaddi vi04, vi00, -2   ; vf22 = 0; vi04 = -2
mulw.xyzw   vf23, vf00, vf00 ; iaddi vi05, vi00, -2   ; vf23 = 0; vi05 = -2
mulw.xyzw   vf24, vf00, vf00 ; iaddi vi06, vi00, -2   ; vf24 = 0; vi06 = -2
pad ; lq.xyzw vf18, 0(vi03)                           ; preload vf18
pad ; lq.xyzw vf21, 1(vi03)                           ; preload vf21
pad ; lq.xyzw vf20, 2(vi03)                           ; preload vf20
pad ; nop_swap

SCISSOR_C_LOOP:
mulax.xyzw  vf01, vf18 ; move.xyzw vf22, vf23
madday.xyzw vf02, vf18 ; move.xyzw vf23, vf24
maddaz.xyzw vf03, vf18 ; iaddiu vi03, vi03, 3
maddw.xyzw  vf25, vf04, vf18 ; iaddi vi10, vi10, -1
sub.w       vf00, vf21, vf00 ; iadd vi04, vi00, vi05
mulax.xyzw  vf13, vf18 ; iadd vi05, vi00, vi06
madday.xyzw vf14, vf18 ; nop_swap
maddaz.xyzw vf15, vf18 ; div Q, vf00.w, vf25.w
maddw.xyzw  vf24, vf16, vf18 ; fsand vi08, 0x2
.word 0x01D6B1FF ; lq.xyzw vf18, 0(vi03)              ; upper: op6=0x3F .xyz fd=7 fs=22 ft=22
.word 0x01D7B9FF ; nop_swap                           ; upper: op6=0x3F .xyz fd=7 fs=23 ft=23
add.xyz     vf28, vf21, vf17 ; nop_swap
.word 0x01D8C1FF ; lq.xyzw vf21, 1(vi03)              ; upper: op6=0x3F .xyz fd=7 fs=24 ft=24
ftoi0.xyzw  vf29, vf20 ; nop_swap
mulq.xyzw   vf27, vf25 ; lq.xyzw vf20, 2(vi03)
mulq.xyz    vf28, vf28 ; nop_swap
pad ; fcand vi01, 0x3F                                ; vi01 = clip-flag bits 0..5
pad ; sq.xyzw vf29, 1(vi07)                           ; store vf29
ftoi4.xyzw  vf27, vf27 ; ibeq vi08, vi00, SCISSOR_C_CONT
pad ; iadd vi06, vi00, vi01                           ; (delay slot) vi06 = clip bits
pad ; iaddi vi04, vi00, 1
pad ; iaddi vi05, vi00, 1
pad ; iaddi vi09, vi00, 2
SCISSOR_C_CONT:
pad ; iadd vi01, vi04, vi05
pad ; iadd vi01, vi01, vi06
pad ; sq.xyzw vf28, 0(vi07)
pad ; ibgtz vi01, SCISSOR_C_XYZ3
pad ; sq.xyzw vf27, 2(vi07)                           ; (delay slot)
SCISSOR_C_XYZ2:
pad ; ibne vi10, vi00, SCISSOR_C_LOOP                 ; loop while count != 0
pad ; iaddiu vi07, vi07, 3                            ; (delay slot)
pad ; xgkick vi02                                     ; kick GIF packet
pad ; nop_swap
pad ; b BEGIN_SCISSOR_C                               ; → sub_2BC0's E-bit
pad ; nop_swap                                        ; (branch delay slot)
SCISSOR_C_XYZ3:
pad ; iaddi vi09, vi09, -1
pad ; ibgtz vi09, SCISSOR_C_XYZ3_ONLY
pad ; fcor vi01, 0xFDF7DF
pad ; ibne vi01, vi00, SCISSOR_C_XYZ3_ONLY
pad ; nop_swap
pad ; fcor vi01, 0xFEFBEF
pad ; ibne vi01, vi00, SCISSOR_C_XYZ3_ONLY
pad ; nop_swap
pad ; fcor vi01, 0xFF7DF7
pad ; ibne vi01, vi00, SCISSOR_C_XYZ3_ONLY
pad ; nop_swap
pad ; fcor vi01, 0xFFBEFB
pad ; ibne vi01, vi00, SCISSOR_C_XYZ3_ONLY
pad ; nop_swap
pad ; fcor vi01, 0xFFDF7D
pad ; ibne vi01, vi00, SCISSOR_C_XYZ3_ONLY
pad ; nop_swap
pad ; fcor vi01, 0xFFEFBE
pad ; ibne vi01, vi00, SCISSOR_C_XYZ3_ONLY
pad ; nop_swap
pad ; bal vi15, SCISSOR_COMMON_PUSHREGISTER           ; save context
pad ; nop_swap
pad ; bal vi15, L_08D8                                ; call LOD hierarchical driver
pad ; nop_swap
pad ; bal vi15, SCISSOR_COMMON_POPREGISTER            ; restore context
pad ; nop_swap
SCISSOR_C_XYZ3_ONLY:
pad ; b SCISSOR_C_XYZ2                                ; back into the per-vertex loop
pad ; isw.w vi11, 2(vi07)                             ; (delay slot — also stores vi11.w)

; =======================================================================
; FOURTH VU0 PROGRAM begins here.  Same multi-program concatenation
; pattern as the program-1/2/3 transitions.  FCSET imm this time is
; 0x1C8.  Followed by an entry-stub table at 0x2EA0..0x2FD8 and the
; program-4 routine bodies starting at L_1830.
; =======================================================================

; Program-4 control-flag prologue (parallels 0x0000..0x0008 / 0x0DB0
; / 0x17A0 in earlier programs).
nop ; .word 0x70000000                                ; 0x2E80 — lower op7=0x38
nop ; nop                                             ; 0x2E88 — true-zero filler
.assert_pc 0x16E0
