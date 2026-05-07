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

# Matching C compiler: ee-gcc 2.96 (i386 ELF binary fetched into tools/cc/
# by tools/setup.sh — same source as SOTC and other PS2 decomp projects).
# Override CC to use a different compiler (e.g. wcc / CodeWarrior) if the
# matching compiler turns out to be different.
EEGCC_DIR     ?= tools/cc/ee-gcc2.96
# `override` is required: CC is a built-in Make variable (defaults to `cc`),
# so `?=` won't reassign it. Use `override CC := ...` to force ee-gcc.
override CC   := $(EEGCC_DIR)/bin/gcc
# ee-gcc 2.96 looks for cc1 at the path it was built against — point -B at
# the bundled gcc-lib so it finds the in-tree cc1.
EEGCC_LIB     := $(EEGCC_DIR)/gcc-lib/ee/2.96-ee-001003-1/

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
ALL_OBJS      := $(ASM_OBJS) $(C_OBJS)

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
CFLAGS        := -S -G 8 -O2 -mips3 -EL -fno-builtin -fno-optimize-sibling-calls -nostdinc -I$(INCLUDE_DIR)

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

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -B $(EEGCC_LIB) $(CFLAGS) -o $(@:.o=.s) $<
	@# ee-gcc 2.96 emits `move $X, $0` for register-zero materialization,
	@# which mips-linux-gnu-as expands to `or $X, $0, $0` (opcode 0x25).
	@# Original PS2 codegen uses `daddu $X, $0, $0` (opcode 0x2D); same
	@# value, different bytes. Rewrite the macro on the way in so the
	@# whole src/ pipeline lines up with the original encoding. Targets
	@# only the zero-source form; non-zero `move` is left alone.
	@sed -i -E 's/^([[:space:]]+)move[[:space:]]+(\$$[0-9]+),[[:space:]]*\$$0[[:space:]]*$$/\1daddu \2,$$0,$$0/' $(@:.o=.s)
	$(AS) $(ASFLAGS) -o $@ $(@:.o=.s)
	$(OBJCOPY) --set-section-alignment .text=$(ALIGN_FOR) $@

$(TARGET_ELF): $(ALL_OBJS) $(LDSCRIPT)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(ALL_OBJS)

$(TARGET_ROM): $(TARGET_ELF)
	$(OBJCOPY) -O binary --gap-fill=0x00 $< $@
