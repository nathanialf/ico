# =============================================================================
# ico — top-level Makefile
#
# Builds the EE-side ELF for ICO (USA, SCUS-97113) from splat-emitted asm
# and project-written C, then objcopy-flattens to a .rom whose SHA-1 must
# match the recorded baserom/baseelf.rom.
#
# No disc data is stored in this repository; everything under build/ and
# asm/ (except asm/nonmatchings/) is generated from the user-supplied disc
# image extracted into baserom/.
# =============================================================================

# ---- Configuration -----------------------------------------------------------

VERSION       ?= us
BASEROM       := baserom/baseelf.rom
BASEELF       := baserom/baseelf.elf
TARGET_ELF    := build/ico.elf
TARGET_ROM    := build/ico.rom
SPLAT_YAML    := config/ico.$(VERSION).yaml
SHA1SUMS      := config/sha1sums.txt

PYTHON        ?= python3
VENV          := .venv
VENV_BIN      := $(VENV)/bin

# Toolchain prefix for binutils (as / ld / objcopy). Falls back to the
# system mips-linux-gnu- in r5900 mode when no EE-specific binutils is on
# PATH — fine for splat-output round-tripping and most matching work.
# Override with `make MIPS_PREFIX=...` if your binaries differ.
ifeq ($(shell command -v mips64r5900el-ps2-elf-as 2>/dev/null),)
  MIPS_PREFIX ?= mips-linux-gnu-
else
  MIPS_PREFIX ?= mips64r5900el-ps2-elf-
endif
AS            := $(MIPS_PREFIX)as
LD            := $(MIPS_PREFIX)ld
OBJCOPY       := $(MIPS_PREFIX)objcopy

# Matching C compiler: ee-gcc 2.9-991111 (i386 ELF binary fetched by
# tools/setup.sh — same compiler the PAL ICO-decomp project uses).
# Confirmed to reproduce regalloc / encoding shapes (daddu vs or,
# loaded-value-into-$v1 with daddu move-to-$v0) that ee-gcc 2.96 does
# not. Older sibling tarball (ee-gcc2.96) is no longer used; the
# bundled ee-as 2.10 from that tree is still consumed for src/.o.
EEGCC_DIR     ?= tools/cc/ee-gcc2.9-991111
override CC   := $(EEGCC_DIR)/ee-gcc
EEGCC_LIB     := $(EEGCC_DIR)/gcc-lib/ee/2.9-ee-991111-01/

BUILD_DIR     := build
ASM_DIR       := asm
SRC_DIR       := src
INCLUDE_DIR   := include

# Exclude asm/matchings and asm/nonmatchings — those are per-function diff
# targets (no macro.inc, not buildable on their own), not link inputs.
ASM_SRCS      := $(shell find $(ASM_DIR) -name '*.s' \
                  -not -path '$(ASM_DIR)/matchings/*' \
                  -not -path '$(ASM_DIR)/nonmatchings/*' 2>/dev/null)
ASM_OBJS      := $(patsubst $(ASM_DIR)/%.s,$(BUILD_DIR)/asm/%.o,$(ASM_SRCS))
C_SRCS        := $(shell find $(SRC_DIR) -name '*.c' 2>/dev/null)
C_OBJS        := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/src/%.o,$(C_SRCS))
HASM_SRCS     := $(shell find $(SRC_DIR) -name '*.s' 2>/dev/null)
HASM_OBJS     := $(patsubst $(SRC_DIR)/%.s,$(BUILD_DIR)/src/%.o,$(HASM_SRCS))
ALL_OBJS      := $(ASM_OBJS) $(C_OBJS) $(HASM_OBJS)

# R5900 EE assembly flags. Little-endian, MIPS III base + r5900 extensions.
# -G 8: small-data threshold of 8 bytes. Variables declared in .sdata/.sbss
# (or extern with size <= 8) are accessed via %gp_rel($gp) instead of
# lui+lw, matching the original ICO codegen. Must agree with CFLAGS.
ASFLAGS       := -EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -I$(INCLUDE_DIR)

# Placeholder C flags. Real matching CFLAGS will evolve as the compiler is
# identified. ee-gcc / Pro-DG / CodeWarrior all want different flag sets.
# -G 8 must agree with ASFLAGS — see comment above. -S because ee-gcc
# 2.96's bundled `as` is too old to parse modern flags; we re-assemble
# the .s output with mips-linux-gnu-as in a second step.
# -fno-optimize-sibling-calls doesn't exist in 2.9 — sibling-call
# optimization in this gcc is hardcoded ON at -O2. Defeat per-function
# at the source level via __asm__ volatile("") after the wrapped call
# (see decomp/NOTES.md "Defeating tail-call in ee-gcc 2.9").
CFLAGS        := -S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -I$(INCLUDE_DIR)

LDSCRIPT      := config/ico.$(VERSION).ld
LDSCRIPT_EXTRA:= config/ico.$(VERSION).linker_script_extra.ld
AUTO_FUNCS    := config/undefined_funcs_auto.$(VERSION).txt
AUTO_SYMS     := config/undefined_syms_auto.$(VERSION).txt
EXTRA_SYMS    := config/undefined_funcs_extra.$(VERSION).txt
LDFLAGS       := -EL -T $(LDSCRIPT) \
                 $(if $(wildcard $(LDSCRIPT_EXTRA)),-T $(LDSCRIPT_EXTRA),) \
                 $(if $(wildcard $(AUTO_FUNCS)),-T $(AUTO_FUNCS),) \
                 $(if $(wildcard $(AUTO_SYMS)),-T $(AUTO_SYMS),) \
                 $(if $(wildcard $(EXTRA_SYMS)),-T $(EXTRA_SYMS),) \
                 --no-check-sections --no-warn-mismatch \
                 -Map $(BUILD_DIR)/ico.$(VERSION).map

# ---- Phony targets -----------------------------------------------------------

.PHONY: all setup split clean distclean progress verify-baserom verify-target

all: $(TARGET_ROM) verify-target

# `make setup` — verify the .rom SHA-1, run splat, post-process asm.
setup: verify-baserom split

split:
	@echo "==> running splat against $(SPLAT_YAML)"
	$(VENV_BIN)/splat split $(SPLAT_YAML)
	@echo "==> postprocessing linker script (sbss/bss alignment fix)"
	$(VENV_BIN)/python tools/postprocess_ld.py
	@echo "==> postprocessing asm (R5900 mnemonic fixups)"
	$(VENV_BIN)/python tools/postprocess_asm.py
	@echo "==> regenerating docs/candidates.md (matching shortlist)"
	@$(VENV_BIN)/python tools/gen_candidates.py || \
	  echo "WARN: gen_candidates.py failed; continuing"

verify-baserom:
	@echo "==> verifying base ROM SHA-1"
	$(VENV_BIN)/python tools/verify_elf.py --target $(BASEROM)

verify-target: $(TARGET_ROM)
	@echo "==> verifying built ROM SHA-1"
	$(VENV_BIN)/python tools/verify_elf.py --target $(TARGET_ROM) --name baseelf.rom

progress:
	$(VENV_BIN)/python tools/progress.py

clean:
	rm -rf $(BUILD_DIR)

distclean: clean
	find $(ASM_DIR) -type f -name '*.s' ! -path '$(ASM_DIR)/nonmatchings/*' -delete
	find $(ASM_DIR) -type d -empty ! -path $(ASM_DIR) ! -path '$(ASM_DIR)/nonmatchings*' -delete 2>/dev/null || true
	rm -f $(LDSCRIPT) $(AUTO_FUNCS) $(AUTO_SYMS) config/ico.$(VERSION).d

# ---- Rules -------------------------------------------------------------------

# mips-linux-gnu-as defaults .text section alignment to 2**4 (16) regardless
# of the actual `.align` directives in the source (which max at 2**3 here).
# When the linker concatenates multiple .text inputs into the merged .cod
# section, that 16-byte alignment forces padding at every input-section
# boundary — breaking byte-identity. Lower it to the alignment implied by
# the file's offset within .cod (encoded in the basename, e.g.
# cod/041044.o starts at offset 0x41044 — needs alignment 4, not 8).
# Helper: pick max power-of-two ≤ 8 that divides the basename hex offset.
ALIGN_FOR = $(shell python3 -c "import re; \
  m=re.match(r'^[0-9A-Fa-f]+$$', '$(basename $(notdir $@))'.split('.')[0]); \
  n=int('$(basename $(notdir $@))'.split('.')[0],16) if m else 0; \
  a=8; \
  exec('while a>1 and n%a:a//=2') if n else None; \
  print(a)")
$(BUILD_DIR)/asm/%.o: $(ASM_DIR)/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<
	$(OBJCOPY) --set-section-alignment .text=$(ALIGN_FOR) $@

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<
	$(OBJCOPY) --set-section-alignment .text=$(ALIGN_FOR) $@

EXTRA_CFLAGS_TXT := config/extra_cflags.txt
EXTRA_CFLAGS_LOOKUP := tools/extra_cflags.sh

# Bundled assembler from ee-gcc 2.96 (GNU as 2.10-ee from 2000, the
# vintage SCEI fork). Use it for src/ output instead of mips-linux-gnu-as
# because it expands the `la $X, sym($Y)` macro to 32-bit `lui+addiu+addu`
# (matching the original ICO codegen) rather than the 64-bit `lui+daddiu+
# daddu` that modern binutils picks under -mabi=eabi for r5900.
EE_AS         := tools/cc/ee-gcc2.96/bin/as
EE_ASFLAGS    := -EL -mcpu=5900 -G 8

# Per-file opt-out: src files containing R5900 VU0/MMI instructions that
# postdate ee-as 2.10 (e.g. vrnext, vrxor) must be assembled with
# mips-linux-gnu-as instead. config/use_modern_as.txt lists the file_offs.
USE_MODERN_AS_TXT := config/use_modern_as.txt

# Per-file `addu` operand-pair swap. ee-gcc 2.9-991111 canonicalizes
# `dst = rhs + dst` to `addu $dst, $rhs, $dst` (rt == rd). Some original
# ICO functions have the commutatively-equivalent `addu $dst, $dst, $rhs`
# (rs == rd). Same operation, different encoding bytes. Files listed in
# config/swap_addu_operands.txt get a targeted sed that rewrites the
# rt==rd form to rs==rd. Safe because the operation is commutative.
SWAP_ADDU_TXT := config/swap_addu_operands.txt
COALESCE_V1_V0_TXT := config/coalesce_v1_v0.txt
SWAP_SW_PAIR_TXT := config/swap_sw_pair.txt
NO_TRAILING_NOP_TXT := config/no_trailing_nop.txt
SHARED_SP_RESTORE_TXT := config/shared_sp_restore.txt
SHARED_JR_RESTORE_TXT := config/shared_jr_restore.txt
LA_SD_INTERLEAVE_TXT := config/la_sd_interleave.txt
EARLY_BODY_SWAP_TXT := config/early_body_swap.txt
FCC_NOP_TXT := config/fcc_nop.txt

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c $(EXTRA_CFLAGS_TXT) $(EXTRA_CFLAGS_LOOKUP) $(USE_MODERN_AS_TXT) $(SWAP_ADDU_TXT) $(COALESCE_V1_V0_TXT) $(SWAP_SW_PAIR_TXT) $(NO_TRAILING_NOP_TXT) $(LA_SD_INTERLEAVE_TXT) $(EARLY_BODY_SWAP_TXT) $(FCC_NOP_TXT)
	@mkdir -p $(@D)
	$(CC) -B $(EEGCC_LIB) $(CFLAGS) $$($(EXTRA_CFLAGS_LOOKUP) $<) -o $(@:.o=.s) $<
	@# If listed in $(NO_TRAILING_NOP_TXT), wrap the final `j $$31` with
	@# `.set noreorder` so gas doesn't auto-fill the jr ra delay slot
	@# with a nop. Used for fall-through-into-next-function patterns
	@# where the original codegen leaves the delay slot empty.
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(NO_TRAILING_NOP_TXT) 2>/dev/null; then \
	    .venv/bin/python tools/postprocess_no_trailing_nop.py $(@:.o=.s); \
	fi
	@# If listed in $(SHARED_SP_RESTORE_TXT), strip the `addu $$sp, $$sp, N`
	@# (sp restore) emitted in the delay slot of the final `j $$31`. The
	@# next adjacent function in the linker script is a 4-byte shared
	@# `addiu sp, +N` stub that fills the delay slot at link time.
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(SHARED_SP_RESTORE_TXT) 2>/dev/null; then \
	    .venv/bin/python tools/postprocess_shared_sp_restore.py --sp-only $(@:.o=.s); \
	fi
	@# If listed in $(SHARED_JR_RESTORE_TXT), strip the entire `j $$31; addu $$sp`
	@# epilogue (both the jr and the sp restore). Function ends at the
	@# preceding `ld $$31` and falls through into an 8-byte
	@# `jr ra; addiu sp, +N` shared stub.
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(SHARED_JR_RESTORE_TXT) 2>/dev/null; then \
	    .venv/bin/python tools/postprocess_shared_sp_restore.py --jr-and-sp $(@:.o=.s); \
	fi
	@# If listed in $(LA_SD_INTERLEAVE_TXT), interleave `sd $$31, OFF($$sp)`
	@# between the lui and addiu halves of the la-macro emission.  Used
	@# for original 5-arg-via-$$tN wrappers whose prologue ra-save was
	@# scheduled inside the la pair rather than after it.
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(LA_SD_INTERLEAVE_TXT) 2>/dev/null; then \
	    .venv/bin/python tools/postprocess_la_sd_interleave.py $(@:.o=.s); \
	fi
	@# If listed in $(FCC_NOP_TXT), promote the `#nop` after c.{lt,le,eq}.{s,d}
	@# to a real `nop` (ee-as 2.10 doesn't insert FCC delay-slot nops).
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(FCC_NOP_TXT) 2>/dev/null; then \
	    .venv/bin/python tools/postprocess_fcc_nop.py $(@:.o=.s); \
	fi
	@# If listed in $(EARLY_BODY_SWAP_TXT), swap `sd $$31, OFF($$sp)` with the
	@# immediately-following inline-asm `#APP` first instruction.  Used when
	@# the original codegen interleaves a single body op (e.g. a register
	@# copy) BEFORE the prologue ra-save.
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(EARLY_BODY_SWAP_TXT) 2>/dev/null; then \
	    .venv/bin/python tools/postprocess_early_body_swap.py $(@:.o=.s); \
	fi
	@# If listed in $(SWAP_ADDU_TXT), swap addu rs/rt where rt==rd.
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(SWAP_ADDU_TXT) 2>/dev/null; then \
	    sed -i -E 's/(addu[[:space:]]+\$$([0-9]+),)\$$([0-9]+),\$$\2\b/\1$$\2,$$\3/g' $(@:.o=.s); \
	fi
	@# If listed in $(COALESCE_V1_V0_TXT), drop the redundant `move $2, $3`
	@# and rename $3 → $2 throughout the function (load-modify-store-return
	@# pattern that ee-gcc 2.9 wastefully splits across two regs).
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(COALESCE_V1_V0_TXT) 2>/dev/null; then \
	    sed -i -E -e '/^[[:space:]]*move[[:space:]]+\$$2,\$$3[[:space:]]*$$/d' \
	              -e 's/\$$3\b/$$2/g' $(@:.o=.s); \
	fi
	@# If listed in $(SWAP_SW_PAIR_TXT), swap two `sw` stores around the
	@# `j $31` epilogue (handles getset-pair store-reorder cases).
	@.venv/bin/python tools/postprocess_sw_pair.py $(@:.o=.s)
	@# ee-as 2.10 doesn't recognize MIPS register name aliases ($zero,
	@# $sp, $ra, etc.) — only numbered ($0, $29, $31). Translate them
	@# all. (Float regs $f0-$f31 and VU regs $vfN are accepted as-is.)
	@sed -i -E -e 's/\$$zero\b/$$0/g'  -e 's/\$$at\b/$$1/g' \
	           -e 's/\$$v0\b/$$2/g'    -e 's/\$$v1\b/$$3/g' \
	           -e 's/\$$a0\b/$$4/g'    -e 's/\$$a1\b/$$5/g' \
	           -e 's/\$$a2\b/$$6/g'    -e 's/\$$a3\b/$$7/g' \
	           -e 's/\$$t0\b/$$8/g'    -e 's/\$$t1\b/$$9/g' \
	           -e 's/\$$t2\b/$$10/g'   -e 's/\$$t3\b/$$11/g' \
	           -e 's/\$$t4\b/$$12/g'   -e 's/\$$t5\b/$$13/g' \
	           -e 's/\$$t6\b/$$14/g'   -e 's/\$$t7\b/$$15/g' \
	           -e 's/\$$s0\b/$$16/g'   -e 's/\$$s1\b/$$17/g' \
	           -e 's/\$$s2\b/$$18/g'   -e 's/\$$s3\b/$$19/g' \
	           -e 's/\$$s4\b/$$20/g'   -e 's/\$$s5\b/$$21/g' \
	           -e 's/\$$s6\b/$$22/g'   -e 's/\$$s7\b/$$23/g' \
	           -e 's/\$$t8\b/$$24/g'   -e 's/\$$t9\b/$$25/g' \
	           -e 's/\$$k0\b/$$26/g'   -e 's/\$$k1\b/$$27/g' \
	           -e 's/\$$gp\b/$$28/g'   -e 's/\$$sp\b/$$29/g' \
	           -e 's/\$$fp\b/$$30/g'   -e 's/\$$ra\b/$$31/g' \
	           $(@:.o=.s)
	@# Pick assembler: prefer ee-as for la-macro / regname / generic
	@# r5900 fidelity. If config/use_modern_as.txt lists this file_off,
	@# OR ee-as fails (typically on a VU0/MMI instruction it doesn't
	@# know), fall back to mips-linux-gnu-as. The fallback path takes
	@# the explicit list as authoritative — if a file isn't listed but
	@# ee-as fails on it anyway, the build still succeeds and the
	@# file_off is appended to the txt as a hint for the next pass.
	@if grep -qE "^[[:space:]]*$(notdir $(basename $<))([[:space:]]|$$|#)" $(USE_MODERN_AS_TXT) 2>/dev/null; then \
	    echo "$(AS) $(ASFLAGS) -o $@ $(@:.o=.s)  # modern-as listed"; \
	    $(AS) $(ASFLAGS) -o $@ $(@:.o=.s); \
	    $(OBJCOPY) --set-section-alignment .text=$(ALIGN_FOR) $@; \
	elif $(EE_AS) $(EE_ASFLAGS) -o $@ $(@:.o=.s) 2>/dev/null; then \
	    echo "$(EE_AS) $(EE_ASFLAGS) -o $@ $(@:.o=.s)"; \
	    $(OBJCOPY) $@ $@; \
	else \
	    echo "$(AS) $(ASFLAGS) -o $@ $(@:.o=.s)  # ee-as rejected, fell back"; \
	    echo "  → consider adding $(notdir $(basename $<)) to $(USE_MODERN_AS_TXT)" >&2; \
	    $(AS) $(ASFLAGS) -o $@ $(@:.o=.s); \
	    $(OBJCOPY) --set-section-alignment .text=$(ALIGN_FOR) $@; \
	fi

$(TARGET_ELF): $(ALL_OBJS) $(LDSCRIPT)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(ALL_OBJS)

$(TARGET_ROM): $(TARGET_ELF)
	$(OBJCOPY) -O binary --gap-fill=0x00 $< $@
