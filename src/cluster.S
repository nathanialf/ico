; -----------------------------------------------------------------------
; ClusterMicroProgram — VU1 microprogram (ico2000.a cluster.o), seki/GS renderer.
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
; PAL ELF this program lives at 0x00289BD0 (3520 bytes); labels below
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
; sub_0180 (+0x0180), L_0708 (+0x0708), sub_0718_loop (+0x0780),
; sub_0A30 (+0x0A30)
; -----------------------------------------------------------------------
.vu0
.org 0x0000
nop ; .word 0x600000DA                                  ; lower op7=0x30 — FCSET (status-flag clear)

; Bundle 0x0008 — upper carries an unknown FMAC-family encoding;
; lower is true zero.  Both will become symbolic when the encoder
; learns the FMAC and lower-special tables.
.word 0x4A000000 ; nop                                  ; upper op6=0x00 sub-field 0x12 (cross-ref VU0 ref)

; The bundles below are alternating "real branch" and "BIOS-NOP
; padding".  The branch targets land inside .vutext just past this
; entry stub (SET_GSREGISTER, SET_UVOFFSET, SET_FONT_OFFSET etc.) — they'll be named
; properly once we promote those regions to hand-typed source.
pad ; b SET_GSREGISTER                                  ; was '.word 0x4000001F'
pad ; nop_swap                                          ; was 'b L_1A00' (wrong — bytes are 0x8000033C)
pad ; b SET_UVOFFSET                                    ; was '.word 0x4000002E'
pad ; nop_swap                                          ; was 'b L_1A10'
pad ; nop_swap                                          ; was 'b L_1A18'
pad ; nop_swap                                          ; was 'b L_1A20'

.assert_pc 0x40

; -----------------------------------------------------------------------
; Entry-stub dispatch table (continued).  Each `pad ; b L_XXXX` bundle
; is a callable VU0 entry point at its 8-byte slot — the EE selects
; one by setting VU0_TPC to that offset before VCALLMS.  The bundle
; that immediately follows a branch is its delay slot (always
; `pad ; nop_swap`); intervening `pad ; nop_swap` bundles are reserved
; / unused dispatch slots and alignment padding.
; -----------------------------------------------------------------------
pad ; nop_swap                                          ; 0x40 — reserved slot
pad ; nop_swap                                          ; 0x48 — reserved slot
pad ; b SET_FONT_OFFSET                                 ; 0x50 — entry → SET_FONT_OFFSET
pad ; nop_swap                                          ; delay slot
pad ; b START_DEBUG_FONT                                ; 0x60 — entry → START_DEBUG_FONT
pad ; nop_swap                                          ; delay slot
pad ; b SPACE_DEBUG_FONT                                ; 0x70 — entry → SPACE_DEBUG_FONT
pad ; nop_swap                                          ; delay slot

pad ; nop_swap                                          ; 0x80 — reserved slot
pad ; nop_swap                                          ; 0x88 — reserved slot
pad ; b SET_CLUSTER_MATRIX                              ; 0x90 — entry → SET_CLUSTER_MATRIX
pad ; nop_swap                                          ; delay slot
pad ; b SET_CLUSTER_LIGHT                               ; 0xA0 — entry → SET_CLUSTER_LIGHT
pad ; nop_swap                                          ; delay slot
pad ; b BEGIN_CLUSTER_0                                 ; 0xB0 — entry → BEGIN_CLUSTER_0
pad ; nop_swap                                          ; delay slot

pad ; b BEGIN_CLUSTER_0_SPEC                            ; 0xC0 — entry → BEGIN_CLUSTER_0_SPEC
pad ; nop_swap                                          ; delay slot
pad ; b sub_0A30                                        ; 0xD0 — entry → sub_0A30
pad ; nop_swap                                          ; delay slot
pad ; nop_swap                                          ; 0xE0 — reserved slot
pad ; nop_swap                                          ; 0xE8 — reserved slot
pad ; nop_swap                                          ; 0xF0 — reserved slot
pad ; nop_swap                                          ; 0xF8 — reserved slot

pad ; nop_swap                                          ; 0x100 — reserved slot
pad ; nop_swap                                          ; 0x108 — reserved slot

; =======================================================================
; SUBROUTINE BODIES.  These are the targets of the entry-stub branches
; above.  Each routine is callable independently (via VCALLMS with a
; matching VU0_TPC) and terminates via an E-bit upper-half pad followed
; by its implicit one-bundle delay slot.
;
; The E-bit pad (upper=`0x400002FF`, lower=anything) is encoded via
; `.word` until assemble_vu0.py learns it as a symbolic mnemonic; the
; lower halves of those bundles continue to use symbolic `nop_swap`.
; =======================================================================

; -----------------------------------------------------------------------
; SET_GSREGISTER — quad-copy loop with embedded count header.
;
; Reads a 16-bit count from the first int of the VIF unpack buffer
; (`ilwr.x` loads the .x lane of *vi12 into vi10), masks it to 15
; bits, then copies `count` quadwords from input cursor vi12 to output
; cursor vi09 (= vi12 + 191).  Both cursors auto-increment via the
; `lqi`/`sqi` post-increment forms.
;
; Pre-loop unrolls the first iteration so the loop tests after one
; iteration has already completed; the body therefore runs count
; times total (decrement-then-`ibne`-against-zero).
; -----------------------------------------------------------------------
SET_GSREGISTER:
pad ; xtop vi12                                         ; vi12 = VIF unpack top (input ptr)
pad ; ilwr.x vi10, vi12                                 ; vi10 = *(int*)vi12  (count word)
pad ; iaddiu vi07, vi12, 191                            ; vi07 = vi12 + 191   (output base)
pad ; iaddiu vi09, vi07, 0                              ; vi09 = vi07         (output cursor)
pad ; lqi.xyzw vf29, vi12                               ; vf29 = *vi12++      (first quad)
pad ; iaddiu vi13, vi00, 32767                          ; vi13 = 0x7FFF       (count mask)
pad ; iand vi10, vi13, vi10                             ; vi10 &= 0x7FFF
pad ; sqi.xyzw vf29, vi09                               ; *vi09++ = vf29      (store first)

SET_GSREGISTER_LOOP:
pad ; lqi.xyzw vf28, vi12                               ; vf28 = *vi12++
pad ; iaddi vi10, vi10, -1                              ; --count
pad ; nop_swap
pad ; ibne vi10, vi00, SET_GSREGISTER_LOOP              ; loop while count != 0
pad ; sqi.xyzw vf28, vi09                               ; *vi09++ = vf28   (branch delay slot)
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_0180 — finalize GIF kick and end the VU0 program.
;
; xgkick at vi07 triggers the GS write of the GIF packet that previous
; routines built up at the mem[vi07] region.  The E-bit upper on the
; next bundle halts the VU0 after one more bundle (the E-bit's implicit
; delay slot).
; -----------------------------------------------------------------------
sub_0180:
pad ; xgkick vi07                                       ; kick GIF packet at mem[vi07]
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot — VU0 halts after

; -----------------------------------------------------------------------
; SET_UVOFFSET — patch the .xy lanes of VU mem[2] from a VIF input quad.
;
; Reads the persistent constant at mem[2] (likely a view-translate
; quad), copies the .xy lanes from the next VIF input over it, and
; writes the result back.  The .zw lanes of mem[2] are preserved.
; -----------------------------------------------------------------------
SET_UVOFFSET:
pad ; xtop vi01                                         ; vi01 = VIF top
pad ; lq.xyzw vf30, 2(vi00)                             ; vf30 = mem[2]
pad ; lqi.xyzw vf31, vi01                               ; vf31 = *vi01++
pad ; move.xy vf30, vf31                                ; vf30.xy = vf31.xy
pad ; sq.xyzw vf30, 2(vi00)                             ; mem[2] = vf30
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot

; -----------------------------------------------------------------------
; SET_FONT_OFFSET — bulk 4-quad upload to mem[256..259].
;
; Loads four quads from VIF unpack into vf18, vf19, vf16, vf17 (note
; non-sequential destination order) and writes them out to mem[256+]
; in the same order.  Looks like a 4-row matrix upload into the
; persistent matrix slot at mem[256].
; -----------------------------------------------------------------------
SET_FONT_OFFSET:
pad ; xtop vi12                                         ; vi12 = VIF top
pad ; iaddiu vi13, vi00, 256                            ; vi13 = mem[256] base
pad ; lqi.xyzw vf18, vi12                               ; vf18 = *vi12++   (row 0)
pad ; lqi.xyzw vf19, vi12                               ; vf19 = *vi12++   (row 1)
pad ; lqi.xyzw vf16, vi12                               ; vf16 = *vi12++   (row 2)
pad ; lqi.xyzw vf17, vi12                               ; vf17 = *vi12++   (row 3)
pad ; sqi.xyzw vf18, vi13                               ; mem[256] = vf18
pad ; sqi.xyzw vf19, vi13                               ; mem[257] = vf19
pad ; sqi.xyzw vf16, vi13                               ; mem[258] = vf16
pad ; sqi.xyzw vf17, vi13                               ; mem[259] = vf17
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot

; -----------------------------------------------------------------------
; BEGIN_DEBUG_FONT — shared "end immediately" stub.
;
; Branched-to by routines (e.g. SPACE_DEBUG_FONT) that need to bail out without
; doing further work.  The E-bit halts the VU0 program after the
; implicit delay slot.
; -----------------------------------------------------------------------
BEGIN_DEBUG_FONT:
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot

; -----------------------------------------------------------------------
; START_DEBUG_FONT — palette-indexed vertex transform with GS kick.
;
; Reads a 16-bit count from *(int*)vi12, then iterates `count` times:
;   - load vertex quad from the vi11 stream (vi11 = vi12 + 1)
;   - extract the .w lane as an int, mask bit 0 → palette index 0/1
;   - load the chosen palette entry from mem[256 + idx]
;   - add palette to vf09.xy, zero vf09.w
;   - ftoi4 convert and store via sqi to the output cursor (vi09)
; After the loop, `xgkick` triggers GS output.  The routine then
; falls through into SPACE_DEBUG_FONT's final-add tail, which branches to
; BEGIN_DEBUG_FONT to terminate.
; -----------------------------------------------------------------------
START_DEBUG_FONT:
pad ; xtop vi12                                         ; vi12 = VIF top
pad ; iaddiu vi11, vi12, 1                              ; vi11 = vi12 + 1     (vertex stream)
pad ; ilwr.x vi10, vi12                                 ; vi10 = *(int*)vi12  (count)
pad ; lq.xyzw vf29, 0(vi12)                             ; vf29 = *vi12        (header quad)
pad ; iaddiu vi13, vi00, 32767                          ; vi13 = 0x7FFF
pad ; iaddiu vi07, vi12, 191                            ; vi07 = vi12 + 191   (output base)
pad ; iaddiu vi09, vi07, 0                              ; vi09 = vi07
pad ; sqi.xyzw vf29, vi09                               ; *vi09++ = vf29      (store header)
pad ; iand vi10, vi13, vi10                             ; vi10 &= 0x7FFF
pad ; iaddiu vi13, vi00, 1                              ; vi13 = 1            (palette bit mask)
pad ; lq.xyzw vf09, 0(vi11)                             ; vf09 = *vi11        (first vertex)
pad ; ilwr.w vi14, vi11                                 ; vi14 = (int)vi11.w
pad ; nop_swap
pad ; iand vi15, vi13, vi14                             ; vi15 = vi14 & 1

LOOP_DEBUG_FONT:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)       ; vf09.xy += palette; load palette[idx]
pad ; move.w vf09, vf00                                 ; vf09.w = 0
pad ; iaddiu vi11, vi11, 1                              ; vi11++
pad ; ilwr.w vi14, vi11                                 ; vi14 = (int)vi11.w
pad ; iaddi vi10, vi10, -1                              ; --count
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09             ; ftoi4 vf09→vf10; *vi09++ = palette
pad ; lq.xyzw vf09, 0(vi11)                             ; vf09 = next vertex
pad ; iand vi15, vi13, vi14                             ; vi15 = vi14 & 1
pad ; ibne vi10, vi00, LOOP_DEBUG_FONT                  ; loop while count != 0
pad ; sqi.xyzw vf10, vi09                               ; *vi09++ = vf10      (delay slot)

pad ; nop_swap                                          ; (0x300) post-loop pad
pad ; xgkick vi07                                       ; (0x308) kick GIF packet
pad ; nop_swap                                          ; (0x310) — falls through into SPACE_DEBUG_FONT

; -----------------------------------------------------------------------
; SPACE_DEBUG_FONT — final palette-step + exit.  Reachable as its own entry
; (TPC=0x70 → b SPACE_DEBUG_FONT) OR by fall-through from START_DEBUG_FONT.  The single
; FMAC bumps vf16.xy by vf17.xy (i.e. advances the palette base by
; one palette stride), then branches to BEGIN_DEBUG_FONT to end the program.
; -----------------------------------------------------------------------
SPACE_DEBUG_FONT:
add.xy vf16, vf16, vf17 ; nop_swap                      ; vf16.xy += vf17.xy
pad ; b BEGIN_DEBUG_FONT                                ; → BEGIN_DEBUG_FONT (END)
pad ; nop_swap                                          ; branch delay slot

; -----------------------------------------------------------------------
; SET_CLUSTER_MATRIX — VIF-driven .w-lane patch of mem[2] + bulk copy + load
;   four working-constants from low mem.
;
; Like SET_UVOFFSET but patches the .w lane instead of .xy, then runs a
; `count`-iteration quad-copy from VIF into mem[16+], and finally
; loads four scratch quads (vf09..vf12) from the fixed slots mem[4..7]
; that are presumably needed by the next VU0 program.
; -----------------------------------------------------------------------
SET_CLUSTER_MATRIX:
pad ; xtop vi12                                         ; vi12 = VIF top
pad ; ilwr.x vi06, vi12                                 ; vi06 = *(int*)vi12  (count)
pad ; lq.xyzw vf30, 2(vi00)                             ; vf30 = mem[2]
pad ; lqi.xyzw vf31, vi12                               ; vf31 = *vi12++
pad ; move.w vf30, vf31                                 ; vf30.w = vf31.w
pad ; sq.xyzw vf30, 2(vi00)                             ; mem[2] = vf30
pad ; iaddiu vi13, vi00, 16                             ; vi13 = mem[16] base

LOOP:
pad ; iaddi vi06, vi06, -1                              ; --count
pad ; lqi.xyzw vf28, vi12                               ; vf28 = *vi12++
pad ; ibne vi06, vi00, LOOP                             ; loop
pad ; sqi.xyzw vf28, vi13                               ; *vi13++ = vf28       (delay slot)

pad ; lq.xyzw vf09, 4(vi00)                             ; vf09 = mem[4]
pad ; lq.xyzw vf10, 5(vi00)                             ; vf10 = mem[5]
pad ; lq.xyzw vf11, 6(vi00)                             ; vf11 = mem[6]
pad ; lq.xyzw vf12, 7(vi00)                             ; vf12 = mem[7]
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot

; -----------------------------------------------------------------------
; SET_CLUSTER_LIGHT — bulk 8-quad load from VIF into vf13..vf20.
;
; Loads eight contiguous quads (a 2x4-matrix block, or two 4x1 vectors,
; or a small bone palette) into a contiguous register block.  No
; stores — the loaded data remains live for the next VU0 program.
; -----------------------------------------------------------------------
SET_CLUSTER_LIGHT:
pad ; xtop vi12                                         ; vi12 = VIF top
pad ; lqi.xyzw vf13, vi12                               ; vf13 = *vi12++
pad ; lqi.xyzw vf14, vi12                               ; vf14 = *vi12++
pad ; lqi.xyzw vf15, vi12                               ; vf15 = *vi12++
pad ; lqi.xyzw vf16, vi12                               ; vf16 = *vi12++
pad ; lqi.xyzw vf17, vi12                               ; vf17 = *vi12++
pad ; lqi.xyzw vf18, vi12                               ; vf18 = *vi12++
pad ; lqi.xyzw vf19, vi12                               ; vf19 = *vi12++
pad ; lqi.xyzw vf20, vi12                               ; vf20 = *vi12++
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot

; -----------------------------------------------------------------------
; BEGIN_CLUSTER_0 — trivial no-op entry (callable empty routine).  Also the
; shared return target of START_CLUSTER_0 (`b BEGIN_CLUSTER_0` to terminate).
; -----------------------------------------------------------------------
BEGIN_CLUSTER_0:
pad ; nop_swap                                          ; do nothing
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot

; -----------------------------------------------------------------------
; START_CLUSTER_0 — skinned vertex transform with perspective divide,
;   color quantization, and front-face/back-face slot selection.
;
; Top-level shape:
;   Prologue (0x428..0x480):
;     - Read count and header quad from VIF input at vi13.
;     - Initialize input cursor vi02 = vi13+1 and output cursor
;       vi01 = vi02+192; mirror the post-header cursor in vi03.
;     - Seed vf26.w = 0, vf27.w = 0x8000 (sign-bit float — used as
;       the "back-face" position-slot marker).
;
;   Per-vertex loop body (LOOP_CLUSTER_0):
;     1. Load two weight quads vf21,vf22 from the vi02 stream and
;        two matrix-index ints (vi10 from .x lane, vi11 from .z
;        lane) — these select two source matrices M, N from the
;        constant pool at low mem.
;     2. Compute M*vf21 → vf28, N*vf21 → vf29; M*vf22 → vf30,
;        N*vf22 → vf31 (standard mulax / madday / maddaz / maddw
;        accumulator chains, four times).
;     3. Blend the two pairs by the bone-weights in vf23.y/.w:
;          vf28 = M*vf21*vf23.y + N*vf21*vf23.w
;          vf22 = M*vf22*vf23.y + N*vf22*vf23.w
;     4. Transform skinned position by the model matrix
;        [vf09..vf12]: vf28 = [vf09..vf12] * vf28.
;     5. Transform skinned vector by [vf13..vf16]: vf30 = ... * vf22.
;        Concurrently fire `div Q, vf00.w, vf28.w` to start the
;        perspective-divide reciprocal.
;     6. Clamp negatives, waitq, then mulq.xyz vf28 *= Q (perspective
;        divide) and re-transform by [vf17..vf20]: vf30 = ... * vf30
;        (post-divide screen-space position).
;     7. Convert vf28 to fixed-point colors (ftoi4) into vf26, vf27;
;        load I-register with 255.0 (via I-bit on a mul.xyz bundle)
;        and use minii to saturate the post-mul color vf25 to 255.
;        ftoi0 truncates to int.
;     8. Use fmand to derive clip-flags into vi14; compare against
;        a clip-mask in vi09 to select front-face vs back-face
;        position slot (vf26 vs vf27).  vi07 is a 3-slot rotating
;        decimator (skip 2 out of 3 back-face writes?).
;     9. Store one output triplet (color, normal, position) at
;        mem[vi03..vi03+2]; advance vi03 by 3.
;
;   Loop tail (0x6D0..0x6F8):
;     - `ibne vi06, ..., LOOP_CLUSTER_0` continues while count != 0.
;     - After the loop: `xgkick vi01` kicks the GIF packet, then
;       `b BEGIN_CLUSTER_0` branches to the shared no-op terminator.
;
; The bundle at 0x0618 has the upper-half I-bit set (bit 31):
;   upper = 0x81DECE6A  (mul.xyz vf25, vf25, vf30 with I-bit)
;   lower = 0x437F0000  (= IEEE-754 255.0f, the I-register immediate)
; assemble_vu0.py has no I-bit suffix yet, so the bundle is emitted
; as two raw `.word`s with the byte sequence above.  The disassembler
; mis-decodes the immediate as `bal vi31, L_0620` because it doesn't
; track the I-bit — the iaddiu at 0x0620 is NOT a branch target.
; -----------------------------------------------------------------------
START_CLUSTER_0:
pad ; xtop vi13                                         ; vi13 = VIF top
pad ; iaddiu vi14, vi00, 32767                          ; vi14 = 0x7FFF
pad ; iaddiu vi02, vi13, 1                              ; vi02 = vi13 + 1     (vertex-stream ptr)
pad ; ilwr.x vi06, vi13                                 ; vi06 = *(int*)vi13  (count)
pad ; lq.xyzw vf28, 0(vi13)                             ; vf28 = mem[vi13]    (header quad)
pad ; iand vi06, vi14, vi06                             ; vi06 &= 0x7FFF
pad ; iaddiu vi01, vi02, 192                            ; vi01 = vi02 + 192   (output base)
pad ; sq.xyzw vf28, 0(vi01)                             ; mem[vi01] = vf28    (store header)
pad ; iaddi vi14, vi14, 1                               ; vi14 = 0x8000       (sign-bit pattern)
pad ; iaddiu vi03, vi01, 1                              ; vi03 = vi01 + 1     (output cursor)
pad ; mfir.w vf26, vi00                                 ; vf26.w = 0          (front-face marker)
pad ; mfir.w vf27, vi14                                 ; vf27.w = 0x8000     (back-face marker)

LOOP_CLUSTER_0:
pad ; lqi.xyzw vf21, vi02                               ; vf21 = *vi02++       (weight quad 0)
pad ; lqi.xyzw vf22, vi02                               ; vf22 = *vi02++       (weight quad 1)
pad ; ilwr.x vi10, vi02                                 ; vi10 = (int)mem[vi02].x  (matrix M base)
pad ; ilwr.z vi11, vi02                                 ; vi11 = (int)mem[vi02].z  (matrix N base)
pad ; lq.xyzw vf01, 0(vi10)                             ; vf01..vf04 = M
pad ; lq.xyzw vf02, 1(vi10)
pad ; lq.xyzw vf03, 2(vi10)
pad ; lq.xyzw vf04, 3(vi10)

; ACC = M * vf21 → vf28
mulax.xyzw  vf01, vf21 ; lq.xyzw vf05, 0(vi11)          ; ACC.xyzw = vf01 * vf21.x; load N[0]
madday.xyzw vf02, vf21 ; lq.xyzw vf06, 1(vi11)          ; ACC += vf02 * vf21.y;   load N[1]
maddaz.xyzw vf03, vf21 ; lq.xyzw vf07, 2(vi11)          ; ACC += vf03 * vf21.z;   load N[2]
maddw.xyzw  vf28, vf04, vf00 ; lq.xyzw vf08, 3(vi11)    ; vf28 = ACC + vf04 * vf00.w; load N[3]

; ACC = N * vf21 → vf29
mulax.xyzw  vf05, vf21 ; iaddi vi06, vi06, -1           ; ACC.xyzw = vf05 * vf21.x; --count
madday.xyzw vf06, vf21 ; lqi.xyzw vf23, vi02            ; ACC += vf06 * vf21.y; vf23 = *vi02++ (bone weights)
maddaz.xyzw vf07, vf21 ; nop_swap                       ; ACC += vf07 * vf21.z
maddw.xyzw  vf29, vf08, vf00 ; move.xyzw vf04, vf00     ; vf29 = ACC + vf08*vf00.w; vf04 = (0,0,0,1)

; ACC = M * vf22 → vf30   (note: maddw uses vf22.w here, not vf00.w)
mulax.xyzw  vf01, vf22 ; nop_swap                       ; ACC = vf01 * vf22.x
madday.xyzw vf02, vf22 ; nop_swap                       ; ACC += vf02 * vf22.y
maddaz.xyzw vf03, vf22 ; nop_swap                       ; ACC += vf03 * vf22.z
maddw.xyzw  vf30, vf04, vf22 ; move.xyzw vf08, vf00     ; vf30 = ACC + (0,0,0,1)*vf22.w; vf08 = (0,0,0,1)

; ACC = N * vf22 → vf31
mulax.xyzw  vf05, vf22 ; move.w vf28, vf00              ; ACC = vf05 * vf22.x; vf28.w = 1
madday.xyzw vf06, vf22 ; nop_swap                       ; ACC += vf06 * vf22.y
maddaz.xyzw vf07, vf22 ; nop_swap                       ; ACC += vf07 * vf22.z
maddw.xyzw  vf31, vf08, vf22 ; nop_swap                 ; vf31 = ACC + vf08*vf22.w

; Bone-weight blend by vf23.y / vf23.w → vf28 (from vf28, vf29) and vf22 (from vf30, vf31)
mulay.xyz   vf28, vf23 ; move.w vf22, vf00              ; ACC.xyz = vf28 * vf23.y;  vf22.w = 1
maddw.xyz   vf28, vf29, vf23 ; nop_swap                 ; vf28.xyz = ACC + vf29*vf23.w
mulay.xyz   vf30, vf23 ; nop_swap                       ; ACC.xyz = vf30 * vf23.y
maddw.xyz   vf22, vf31, vf23 ; nop_swap                 ; vf22.xyz = ACC + vf31*vf23.w

; Apply per-model matrix [vf09..vf12] to vf28 (skinned color/light vector)
mulax.xyzw  vf09, vf28 ; nop_swap                       ; ACC = vf09 * vf28.x
madday.xyzw vf10, vf28 ; nop_swap                       ; ACC += vf10 * vf28.y
maddaz.xyzw vf11, vf28 ; nop_swap                       ; ACC += vf11 * vf28.z
maddw.xyzw  vf28, vf12, vf28 ; nop_swap                 ; vf28 = ACC + vf12 * vf28.w

; Apply [vf13..vf16] to vf22 (skinned position pre-divide) + start perspective divide
mulax.xyzw  vf13, vf22 ; lqi.xyzw vf24, vi02            ; ACC = vf13*vf22.x; vf24 = *vi02++ (alt-color quad)
madday.xyzw vf14, vf22 ; nop_swap                       ; ACC += vf14*vf22.y
maddaz.xyzw vf15, vf22 ; nop_swap                       ; ACC += vf15*vf22.z
maddw.xyzw  vf30, vf16, vf22 ; div Q, vf00.w, vf28.w    ; vf30 = ACC + vf16*vf22.w; Q = 1.0/vf28.w

; Cycle-pad while Q divides; meanwhile set up clip-flag accumulator
sub.w       vf00, vf24, vf00 ; nop_swap                 ; flag-set: vf24.w - 0
pad ; nop_swap
pad ; nop_swap
maxx.xyzw   vf30, vf30, vf00 ; nop_swap                 ; vf30 = max(vf30, vf00.x=0)  (clamp negatives)
sub.w       vf24, vf24, vf24 ; fsand vi15, 0x2          ; vf24.w = 0; vi15 = MAC.flags & 0x02
mulq.xyz    vf28, vf28 ; waitq                          ; vf28.xyz *= Q (perspective divide)

; Apply [vf17..vf20] to vf30 (post-divide screen-space transform)
mulax.xyzw  vf17, vf30 ; nop_swap                       ; ACC = vf17 * vf30.x
madday.xyzw vf18, vf30 ; nop_swap                       ; ACC += vf18 * vf30.y
maddaz.xyzw vf19, vf30 ; iaddiu vi13, vi00, 0           ; ACC += vf19*vf30.z; vi13 = 0 (clip slot)
maddw.xyzw  vf30, vf20, vf30 ; lqi.xyzw vf25, vi02      ; vf30 = ACC + vf20*vf30.w; vf25 = *vi02++ (color)
maxx.xyzw   vf30, vf30, vf00 ; nop_swap                 ; clamp vf30 to ≥ 0

; Quantize colors / set up clip-flag bits
ftoi4.xyz   vf26, vf28 ; lq.xyzw vf29, 0(vi13)          ; vf26.xyz = float→fix4(vf28); vf29 = mem[0] (clip-x bounds)
ftoi4.xyz   vf27, vf28 ; lq.xyzw vf31, 1(vi13)          ; vf27.xyz = float→fix4(vf28); vf31 = mem[1] (clip-y bounds)
mulq.xyz    vf24, vf24 ; nop_swap                       ; vf24.xyz *= Q (perspective on alt-color)
; I-bit bundle: upper = mul.xyz vf25,vf25,vf30 with I-bit set; lower = 255.0f → I reg.
; (disasm shows lower as `bal vi31, L_0620` — a misread.  The iaddiu at 0x0620 is
;  the next sequential bundle, NOT a branch target.)
.word 0x81DECE6A ; .word 0x437F0000                     ; mul.xyz[I] vf25,vf25,vf30 + I = 255.0f

pad ; iaddiu vi09, vi00, 208                            ; vi09 = 0xD0  (clip-mask: bits .y/.z/.w?)
sub.xyw     vf00, vf29, vf28 ; nop_swap                 ; flag-set: clip(vf29 - vf28) on xyw
sub.xyw     vf00, vf28, vf31 ; nop_swap                 ; flag-set: clip(vf28 - vf31) on xyw
minii.xyzw  vf25, vf25 ; sq.xyzw vf24, 0(vi03)          ; saturate vf25 ≤ I(=255); store alt-color
pad ; nop_swap
pad ; fmand vi14, vi09                                  ; vi14 = MAC.flags & vi09 (clip bits)
pad ; fmand vi14, vi14                                  ; vi14 = MAC.flags & vi14 (combine)
ftoi0.xyzw  vf25, vf25 ; ibeq vi15, vi00, CONT_CLUSTER_0 ; ftoi0 (round-to-int); if vi15==0 skip-reset
pad ; nop_swap                                          ; (branch delay slot)
pad ; iaddiu vi07, vi00, 3                              ; vi07 = 3 (back-face slot counter)

CONT_CLUSTER_0:
pad ; iaddi vi07, vi07, -1                              ; --vi07
pad ; sq.xyzw vf25, 1(vi03)                             ; mem[vi03+1] = vf25 (quantized color)
pad ; ibne vi14, vi09, CLIP_CLUSTER_0                   ; if clip-flags don't match, use back-face slot
pad ; nop_swap                                          ; (branch delay slot)
pad ; ibgtz vi07, CLIP_CLUSTER_0_SET                    ; if vi07 > 0, also use back-face slot
pad ; sq.xyzw vf26, 2(vi03)                             ; mem[vi03+2] = vf26 (front-face position)  (delay slot)
pad ; b CLIP_CLUSTER_0_END                              ; skip back-face write
pad ; nop_swap                                          ; (branch delay slot)
CLIP_CLUSTER_0:
pad ; iaddiu vi07, vi00, 3                              ; reset vi07 = 3 (back-face slot triggered)
CLIP_CLUSTER_0_SET:
pad ; sq.xyzw vf27, 2(vi03)                             ; mem[vi03+2] = vf27 (back-face position)
CLIP_CLUSTER_0_END:
pad ; iaddiu vi03, vi03, 3                              ; vi03 += 3 (advance output by 3 quads)
pad ; nop_swap
pad ; ibne vi06, vi00, LOOP_CLUSTER_0                   ; loop while count != 0
pad ; nop_swap                                          ; (branch delay slot)
pad ; xgkick vi01                                       ; kick GIF packet at vi01
pad ; nop_swap
pad ; b BEGIN_CLUSTER_0                                 ; → BEGIN_CLUSTER_0 (shared END stub)
pad ; nop_swap                                          ; (branch delay slot)

; -----------------------------------------------------------------------
; BEGIN_CLUSTER_0_SPEC — second shared no-op terminator (TPC=0xC0 dispatch target).
; Identical 3-bundle layout to BEGIN_CLUSTER_0 at a different VRAM slot; the
; START_CLUSTER_0_SPEC routine `b sub_0708` returns to L_0708 here for END.
; -----------------------------------------------------------------------
BEGIN_CLUSTER_0_SPEC:
pad ; nop_swap                                          ; do nothing (entry)
L_0708:
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot

; -----------------------------------------------------------------------
; START_CLUSTER_0_SPEC — second skinned vertex transform routine.
;
; Near-clone of START_CLUSTER_0 (see that routine's docstring for the full
; algorithm).  Differences from START_CLUSTER_0:
;   * Loop-relative: the first `lqi vf21, vi02` is unrolled above the
;     loop start label (sub_0718_loop = sub_0718_loop); subsequent iterations
;     only re-load vf22.  This means vf21 stays constant per call.
;   * Bundle at 0x0810 has flag bits set (E-bit / T-bit / bit 25);
;     the FMAC underneath is `add.yw vf04, vf00, vf19`.  Emitted via
;     `.word` because the assembler has no upper-flag suffix yet.
;   * Bundle at 0x0950 mirrors START_CLUSTER_0's I-bit immediate trick:
;     upper 0x81DECE6A (mul.xyz vf25,vf25,vf30 with I-bit) + lower
;     0x437F0000 (= 255.0f → I-register).  disasm reads the lower as
;     `bal vi31, L_0958`; that is a misread.
;   * Two extra `mul.xyz vf30, vf30, vf30` bundles at 0x0910 / 0x0930
;     square vf30 twice (likely a specular-power approximation).
;   * The `maddw vf30, vf00, vf30` at 0x08E8 uses vf00 (not vf20) as
;     the .w-broadcast source; combined with the squaring it implies
;     this routine doesn't apply the screen-space matrix in vf17..20.
;   * Loop tail branches to sub_0708 (L_0708) instead of BEGIN_CLUSTER_0.
; -----------------------------------------------------------------------
START_CLUSTER_0_SPEC:
pad ; xtop vi13                                         ; vi13 = VIF top
pad ; iaddiu vi14, vi00, 32767                          ; vi14 = 0x7FFF
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi06, vi13                                 ; vi06 = count
pad ; lq.xyzw vf28, 0(vi13)
pad ; iand vi06, vi14, vi06
pad ; iaddiu vi01, vi02, 192                            ; output base = vi02 + 192
pad ; sq.xyzw vf28, 0(vi01)
pad ; iaddi vi14, vi14, 1                               ; vi14 = 0x8000
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf26, vi00                                 ; vf26.w = 0
pad ; mfir.w vf27, vi14                                 ; vf27.w = 0x8000
pad ; lqi.xyzw vf21, vi02                               ; vf21 = *vi02++ (loaded ONCE — not in loop)

sub_0718_loop:
pad ; lqi.xyzw vf22, vi02                               ; vf22 = *vi02++
pad ; ilwr.x vi10, vi02
pad ; ilwr.z vi11, vi02
pad ; lq.xyzw vf01, 0(vi10)
pad ; lq.xyzw vf02, 1(vi10)
pad ; lq.xyzw vf03, 2(vi10)
pad ; lq.xyzw vf04, 3(vi10)

mulax.xyzw  vf01, vf21 ; lq.xyzw vf05, 0(vi11)
madday.xyzw vf02, vf21 ; lq.xyzw vf06, 1(vi11)
maddaz.xyzw vf03, vf21 ; lq.xyzw vf07, 2(vi11)
maddw.xyzw  vf28, vf04, vf00 ; lq.xyzw vf08, 3(vi11)

mulax.xyzw  vf05, vf21 ; iaddi vi06, vi06, -1
madday.xyzw vf06, vf21 ; lqi.xyzw vf23, vi02
maddaz.xyzw vf07, vf21 ; nop_swap
maddw.xyzw  vf29, vf08, vf00 ; move.xyzw vf04, vf00

mulax.xyzw  vf01, vf22 ; nop_swap
madday.xyzw vf02, vf22 ; nop_swap
maddaz.xyzw vf03, vf22 ; nop_swap
.word 0x4AB30100 ; nop                                  ; upper: `add.yw vf04,vf00,vf19` + flag bits (E/T/25)
maddw.xyzw  vf30, vf04, vf22 ; move.xyzw vf08, vf00

mulax.xyzw  vf05, vf22 ; move.w vf28, vf00
madday.xyzw vf06, vf22 ; nop_swap
maddaz.xyzw vf07, vf22 ; nop_swap
maddw.xyzw  vf31, vf08, vf22 ; nop_swap

mulay.xyz   vf28, vf23 ; move.w vf22, vf00
maddw.xyz   vf28, vf29, vf23 ; nop_swap
mulay.xyz   vf30, vf23 ; nop_swap
maddw.xyz   vf22, vf31, vf23 ; nop_swap

mulax.xyzw  vf09, vf28 ; nop_swap
madday.xyzw vf10, vf28 ; nop_swap
maddaz.xyzw vf11, vf28 ; nop_swap
maddw.xyzw  vf28, vf12, vf28 ; nop_swap

mulax.xyzw  vf13, vf22 ; lqi.xyzw vf24, vi02
madday.xyzw vf14, vf22 ; nop_swap
maddaz.xyzw vf15, vf22 ; nop_swap
maddw.xyzw  vf30, vf16, vf22 ; div Q, vf00.w, vf28.w

sub.w       vf00, vf24, vf00 ; nop_swap
pad ; nop_swap
pad ; nop_swap
maxx.xyzw   vf30, vf30, vf00 ; nop_swap
sub.w       vf24, vf24, vf24 ; fsand vi15, 0x2
mulq.xyz    vf28, vf28 ; waitq

mulax.xyzw  vf17, vf30 ; nop_swap
madday.xyzw vf18, vf30 ; nop_swap
maddaz.xyzw vf19, vf30 ; iaddiu vi13, vi00, 0
maddw.xyzw  vf30, vf00, vf30 ; lqi.xyzw vf25, vi02      ; vf30.w-broadcast from vf30 itself
maxx.xyzw   vf30, vf30, vf00 ; nop_swap

pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
mul.xyz     vf30, vf30, vf30 ; nop_swap                 ; vf30² (specular power step 1)
pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
mul.xyz     vf30, vf30, vf30 ; nop_swap                 ; vf30⁴ (specular power step 2)

ftoi4.xyz   vf26, vf28 ; lq.xyzw vf29, 0(vi13)
ftoi4.xyz   vf27, vf28 ; lq.xyzw vf31, 1(vi13)
mulq.xyz    vf24, vf24 ; nop_swap
.word 0x81DECE6A ; .word 0x437F0000                     ; mul.xyz[I] vf25,vf25,vf30 + I = 255.0f

pad ; iaddiu vi09, vi00, 208
sub.xyw     vf00, vf29, vf28 ; nop_swap
sub.xyw     vf00, vf28, vf31 ; nop_swap
minii.xyzw  vf25, vf25 ; sq.xyzw vf24, 0(vi03)
pad ; nop_swap
pad ; fmand vi14, vi09
pad ; fmand vi14, vi14
ftoi0.xyzw  vf25, vf25 ; ibeq vi15, vi00, CONT_CLUSTER_0_SPEC
pad ; nop_swap
pad ; iaddiu vi07, vi00, 3

CONT_CLUSTER_0_SPEC:
pad ; iaddi vi07, vi07, -1
pad ; sq.xyzw vf25, 1(vi03)
pad ; ibne vi14, vi09, CLIP_CLUSTER_0_SPEC
pad ; nop_swap
pad ; ibgtz vi07, CLIP_CLUSTER_0_SPEC_SET
pad ; sq.xyzw vf26, 2(vi03)
pad ; b CLIP_CLUSTER_0_SPEC_END
pad ; nop_swap
CLIP_CLUSTER_0_SPEC:
pad ; iaddiu vi07, vi00, 3
CLIP_CLUSTER_0_SPEC_SET:
pad ; sq.xyzw vf27, 2(vi03)
CLIP_CLUSTER_0_SPEC_END:
pad ; iaddiu vi03, vi03, 3
pad ; nop_swap
pad ; ibne vi06, vi00, sub_0718_loop
pad ; nop_swap
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_0708                                          ; → BEGIN_CLUSTER_0_SPEC / L_0708 (END)
; branch delay slot of `b L_0708` is the next bundle in source —
; which is sub_0A30's entry bundle at 0x0A30 (a `pad ; nop_swap`).

; -----------------------------------------------------------------------
; sub_0A30 — third shared no-op terminator (TPC=0xD0 dispatch target).
; Same 4-bundle shape as BEGIN_CLUSTER_0 / BEGIN_CLUSTER_0_SPEC, with an extra `nop_swap`
; bundle (BEGIN_CLUSTER_1_SPEC) at +8 so START_CLUSTER_1_SPEC's loop tail has a `b BEGIN_CLUSTER_1_SPEC`
; target with the E-bit one bundle later.
; -----------------------------------------------------------------------
sub_0A30:
pad ; nop_swap                                          ; do nothing (entry / also START_CLUSTER_0_SPEC's branch delay slot)
BEGIN_CLUSTER_1_SPEC:
pad ; nop_swap                                          ; START_CLUSTER_1_SPEC's branch target
epad ; nop_swap                                         ; upper: E-bit pad (END)
pad ; nop_swap                                          ; E-bit delay slot

; -----------------------------------------------------------------------
; START_CLUSTER_1_SPEC — third skinned vertex transform routine.
;
; Near-clone of START_CLUSTER_0 / START_CLUSTER_0_SPEC; same overall shape (per-vertex
; matrix×weight skinning with perspective divide, fmand-driven
; front/back face slot selection, and `xgkick`-then-`b BEGIN_CLUSTER_1_SPEC`
; termination).  Key differences from START_CLUSTER_0:
;   * Setup phase additionally computes `vi12 = vi02 + 2` and loads
;     all four weight quads vf21/vf22/vf23/vf24 from low-mem-relative
;     `lq` (non-incrementing), with matrix indices read from vi12
;     instead of vi02.
;   * Setup also adds a one-shot `add.xy vf24, vf24, mem[2]` (FMAC
;     in upper of the lq vf03 bundle at 0x0B00).
;   * Loop body is restructured: the LOOP_CLUSTER_1_SPEC label is after a full
;     pre-loop matrix-mul prologue (M*vf22, N*vf22, M*vf21, N*vf21
;     all happen ONCE before the loop), and per-iteration only the
;     blends, divide, and per-vertex transforms re-execute.  Stream
;     advance is `iaddiu vi02, vi02, 5` (5 quads per vertex).
;   * Bundle 0x0C70 is the I-bit immediate trick (upper sub.xyw
;     vf00,vf29,vf28 with I-bit; lower 0x437F0000 = 255.0f → I).
;   * `mul.w vf25, vf25, vf23` at 0x0C68 — per-vertex alpha mod via
;     bone-weight .w.
;   * The clip-mismatch path at CLIP_CLUSTER_1_SPEC/CLIP_CLUSTER_1_SPEC_SET branches back to
;     LOOP_CLUSTER_1_SPEC (loop) WITHOUT going through the "common" tail —
;     there are TWO `xgkick` exits (post-front-face and post-back-
;     face), each followed by `b BEGIN_CLUSTER_1_SPEC`.
; -----------------------------------------------------------------------
START_CLUSTER_1_SPEC:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi06, vi13
pad ; lq.xyzw vf28, 0(vi13)
pad ; iand vi06, vi14, vi06
pad ; iaddiu vi01, vi02, 192
pad ; sq.xyzw vf28, 0(vi01)
pad ; iaddi vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf26, vi00
pad ; mfir.w vf27, vi14
pad ; iaddiu vi12, vi02, 2                              ; vi12 = vi02 + 2 (matrix-index ptr)
pad ; lq.xyzw vf21, 0(vi02)                             ; vf21 = mem[vi02+0] (weight quad A)
pad ; lq.xyzw vf22, 1(vi02)                             ; vf22 = mem[vi02+1] (weight quad B)
pad ; ilwr.x vi10, vi12                                 ; vi10 = (int)mem[vi12].x (matrix M idx)
pad ; ilwr.z vi11, vi12                                 ; vi11 = (int)mem[vi12].z (matrix N idx)
pad ; lq.xyzw vf23, 2(vi02)                             ; vf23 = mem[vi02+2] (bone weights)
pad ; lq.xyzw vf24, 3(vi02)                             ; vf24 = mem[vi02+3] (alt-color)
pad ; lq.xyzw vf28, 2(vi00)                             ; vf28 = mem[2] (view-translate?)
pad ; lq.xyzw vf01, 0(vi10)                             ; M[0]
pad ; lq.xyzw vf02, 1(vi10)                             ; M[1]
add.xy      vf24, vf24, vf28 ; lq.xyzw vf03, 2(vi10)    ; vf24.xy += mem[2].xy; M[2]
pad ; lq.xyzw vf04, 3(vi10)                             ; M[3]

; M*vf22 → vf30 + load N
mulax.xyzw  vf01, vf22 ; lq.xyzw vf05, 0(vi11)
madday.xyzw vf02, vf22 ; lq.xyzw vf06, 1(vi11)
maddaz.xyzw vf03, vf22 ; lq.xyzw vf07, 2(vi11)
maddw.xyzw  vf30, vf00, vf22 ; lq.xyzw vf08, 3(vi11)

; N*vf22 → vf31  (with one iaddiu fold-in)
mulax.xyzw  vf05, vf22 ; nop_swap
madday.xyzw vf06, vf22 ; iaddiu vi09, vi00, 208         ; vi09 = 0xD0 clip-mask
maddaz.xyzw vf07, vf22 ; nop_swap
maddw.xyzw  vf31, vf00, vf22 ; nop_swap

; M*vf21 → vf28
mulax.xyzw  vf01, vf21 ; nop_swap
madday.xyzw vf02, vf21 ; nop_swap
maddaz.xyzw vf03, vf21 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap

; N*vf21 → vf29
mulax.xyzw  vf05, vf21 ; nop_swap
madday.xyzw vf06, vf21 ; nop_swap
maddaz.xyzw vf07, vf21 ; nop_swap
maddw.xyzw  vf29, vf08, vf00 ; nop_swap

LOOP_CLUSTER_1_SPEC:
mulay.xyz   vf30, vf23 ; move.w vf22, vf00              ; ACC = vf30*vf23.y; vf22.w = 1
maddw.xyz   vf22, vf31, vf23 ; iaddiu vi02, vi02, 5     ; vf22 = ACC + vf31*vf23.w; vi02 += 5
mulay.xyz   vf28, vf23 ; move.w vf28, vf00              ; ACC = vf28*vf23.y; vf28.w = 1
maddw.xyz   vf28, vf29, vf23 ; iaddi vi06, vi06, -1     ; vf28 = ACC + vf29*vf23.w; --count
sub.w       vf00, vf24, vf00 ; iaddiu vi13, vi00, 0     ; flag-set; vi13 = 0 (clip-mem slot)
mulax.xyzw  vf13, vf22 ; iaddiu vi12, vi02, 2           ; ACC = vf13*vf22.x; vi12 = vi02+2 (next-iter matrix idx)
madday.xyzw vf14, vf22 ; lq.xyzw vf21, 0(vi02)          ; ACC += vf14*vf22.y; vf21 = next vf21
maddaz.xyzw vf15, vf22 ; ilwr.x vi10, vi12              ; ACC += vf15*vf22.z; vi10 = next M idx
maddw.xyzw  vf30, vf16, vf22 ; fsand vi15, 0x2          ; vf30 = ACC + vf16*vf22.w; vi15 = MAC.flag & 0x2

; Per-vertex matrix transform of vf28 (color/light) + prefetch next-iter matrix
mulax.xyzw  vf09, vf28 ; lq.xyzw vf29, 0(vi13)          ; ACC = vf09*vf28.x; vf29 = mem[0]
madday.xyzw vf10, vf28 ; lq.xyzw vf31, 1(vi13)          ; ACC += vf10*vf28.y; vf31 = mem[1]
maddaz.xyzw vf11, vf28 ; lq.xyzw vf22, 1(vi02)          ; ACC += vf11*vf28.z; vf22 = next vf22
maddw.xyzw  vf28, vf12, vf28 ; ilwr.z vi11, vi12        ; vf28 = ACC + vf12*vf28.w; vi11 = next N idx
maxx.xyzw   vf30, vf30, vf00 ; lq.xyzw vf01, 0(vi10)    ; clamp vf30 ≥ 0; M[0] next-iter
sub.w       vf24, vf24, vf24 ; lq.xyzw vf02, 1(vi10)    ; vf24.w = 0; M[1] next
pad ; lq.xyzw vf03, 2(vi10)                             ; M[2] next
pad ; div Q, vf00.w, vf28.w                             ; Q = 1/vf28.w
mulax.xyzw  vf17, vf30 ; lq.xyzw vf04, 3(vi10)          ; ACC = vf17*vf30.x; M[3] next
madday.xyzw vf18, vf30 ; lq.xyzw vf05, 0(vi11)          ; ACC += vf18*vf30.y; N[0] next
maddaz.xyzw vf19, vf30 ; lq.xyzw vf06, 1(vi11)          ; ACC += vf19*vf30.z; N[1] next
maddw.xyzw  vf30, vf20, vf30 ; lq.xyzw vf07, 2(vi11)    ; vf30 = ACC + vf20*vf30.w; N[2] next
mulax.xyzw  vf01, vf22 ; lq.xyzw vf08, 3(vi11)          ; (next-iter M*vf22 start); N[3] next
madday.xyzw vf02, vf22 ; lq.xyzw vf23, 2(vi00)          ; ACC += vf02*vf22.y; vf23 = mem[2]
mulq.xyz    vf28, vf28 ; lq.xyzw vf25, -1(vi02)         ; vf28 *= Q; vf25 = mem[vi02-1] (color quad)
maxx.xyzw   vf30, vf30, vf00 ; nop_swap                 ; clamp vf30 ≥ 0
mulq.xyz    vf24, vf24 ; nop_swap                       ; vf24 *= Q
maddaz.xyzw vf03, vf22 ; nop_swap                       ; ACC += vf03*vf22.z (next-iter M*vf22)
mul.w       vf25, vf25, vf23 ; nop_swap                 ; vf25.w *= vf23.w (alpha by bone-weight-w)

; I-bit immediate bundle: upper = sub.xyw vf00,vf29,vf28 + I-bit; lower = 255.0f → I
; (disasm reads lower as `bal vi31, L_0C78` — misread; the next bundle at 0x0C78 is sequential.)
.word 0x81BCE82C ; .word 0x437F0000

mul.xyz     vf29, vf30, vf30 ; lq.xyzw vf23, 2(vi02)    ; vf29 = vf30² (specular-pow); vf23 = next bone weights
sub.xyw     vf00, vf28, vf31 ; sq.xyzw vf24, 0(vi03)    ; clip-flag; store alt-color
ftoi4.xyz   vf26, vf28 ; nop_swap                       ; vf26 = ftoi4(vf28)
ftoi4.xyz   vf27, vf28 ; fmand vi14, vi09               ; vf27 = ftoi4(vf28); vi14 = MAC & 0xD0
maddw.xyzw  vf30, vf00, vf22 ; nop_swap                 ; vf30 += vf00*vf22.w (cont next-iter)
mul.xyz     vf25, vf25, vf29 ; fmand vi14, vi14         ; vf25 *= vf30²; combine MAC flags
mulax.xyzw  vf05, vf22 ; lq.xyzw vf24, 3(vi02)          ; (cont N*vf22 next-iter); vf24 = next alt-color
madday.xyzw vf06, vf22 ; nop_swap
maddaz.xyzw vf07, vf22 ; nop_swap
minii.xyzw  vf25, vf25 ; nop_swap                       ; saturate vf25 ≤ I(=255)
maddw.xyzw  vf31, vf00, vf22 ; iaddi vi07, vi07, -1     ; vf31 cont; --vi07
mulax.xyzw  vf01, vf21 ; nop_swap                       ; (cont M*vf21 next-iter)
madday.xyzw vf02, vf21 ; nop_swap
ftoi0.xyzw  vf25, vf25 ; nop_swap                       ; vf25 = ftoi0(vf25)
maddaz.xyzw vf03, vf21 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
mulax.xyzw  vf05, vf21 ; nop_swap                       ; (cont N*vf21 next-iter)
madday.xyzw vf06, vf21 ; sq.xyzw vf25, 1(vi03)          ; store vf25 color
maddaz.xyzw vf07, vf21 ; ibeq vi15, vi00, CONT_CLUSTER_1_SPEC ; if vi15==0 skip-reset
maddw.xyzw  vf29, vf08, vf00 ; lq.xyzw vf25, 2(vi00)    ; vf25 = mem[2] (alpha reset?)  (delay slot)
pad ; iaddiu vi07, vi00, 2                              ; vi07 = 2

CONT_CLUSTER_1_SPEC:
pad ; ibne vi14, vi09, CLIP_CLUSTER_1_SPEC              ; clip-mismatch → back-face path
pad ; nop_swap                                          ; (delay slot)
pad ; ibgtz vi07, CLIP_CLUSTER_1_SPEC_SET               ; vi07 > 0 → back-face path
pad ; sq.xyzw vf26, 2(vi03)                             ; front-face position  (delay slot)
add.xy      vf24, vf24, vf25 ; ibne vi06, vi00, LOOP_CLUSTER_1_SPEC ; vf24.xy += vf25.xy; loop
pad ; iaddiu vi03, vi03, 3                              ; vi03 += 3            (delay slot)
pad ; xgkick vi01
pad ; nop_swap
pad ; b BEGIN_CLUSTER_1_SPEC                            ; → END
pad ; nop_swap                                          ; (branch delay slot)
CLIP_CLUSTER_1_SPEC:
pad ; iaddiu vi07, vi00, 3                              ; reset vi07 = 3
CLIP_CLUSTER_1_SPEC_SET:
pad ; sq.xyzw vf27, 2(vi03)                             ; back-face position
add.xy      vf24, vf24, vf25 ; ibne vi06, vi00, LOOP_CLUSTER_1_SPEC ; vf24.xy += vf25.xy; loop
pad ; iaddiu vi03, vi03, 3                              ; vi03 += 3            (delay slot)
pad ; xgkick vi01
pad ; nop_swap
pad ; b BEGIN_CLUSTER_1_SPEC                            ; → END
pad ; nop_swap                                          ; (branch delay slot)

; =======================================================================
; SECOND VU0 PROGRAM begins here.  ICO's `.vutext` blob is a
; concatenation of multiple VU0 programs (each ≤ 4 KB of micro
; memory); the EE DMAs the appropriate slice into VU0 RAM before
; VCALLMS.  Bundle 0x0DB0 mirrors program 1's bundle 0x0000:
; nop-upper paired with a special-class lower (here a different op
; with op7=0x38), and bundle 0x0DC8 mirrors program 1's 0x0008
; FMAC-family `.word 0x4A000000` upper.
; =======================================================================

; Program-2 control-flag prologue (parallels 0x0000..0x0008 in program 1).
nop ; .word 0x70000000                                  ; lower op7=0x38 (special class, not yet decoded)
nop ; nop                                               ; literal-zero bundle (both halves true zero)
.assert_pc 0xDC0
