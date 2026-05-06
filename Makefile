# =============================================================================
# ico — top-level Makefile
#
# Builds the EE-side ELF for ICO (USA, SLUS-20218) from splat-emitted asm
# and project-written C. Verifies the SHA-1 against config/sha1sums.txt.
#
# No disc data is stored in this repository; everything under build/ and
# asm/ (except asm/nonmatchings/) is generated from the user-supplied disc
# image extracted into baserom/.
# =============================================================================

# ---- Configuration -----------------------------------------------------------

VERSION       ?= us
BASEELF       := baserom/baseelf.elf
TARGET_ELF    := build/baseelf.elf
SPLAT_YAML    := config/ico.$(VERSION).yaml
SHA1SUMS      := config/sha1sums.txt

PYTHON        ?= python3
VENV          := .venv
VENV_BIN      := $(VENV)/bin

# EE toolchain prefix. Defaults to ps2dev's `mips64r5900el-ps2-elf-`. Override
# with `make MIPS_PREFIX=...` if your binaries use a different name.
MIPS_PREFIX   ?= mips64r5900el-ps2-elf-
AS            := $(MIPS_PREFIX)as
CC            := $(MIPS_PREFIX)gcc
LD            := $(MIPS_PREFIX)ld
OBJCOPY       := $(MIPS_PREFIX)objcopy
OBJDUMP       := $(MIPS_PREFIX)objdump

BUILD_DIR     := build
ASM_DIR       := asm
SRC_DIR       := src
INCLUDE_DIR   := include

# Object lists are derived at parse time from whatever splat has emitted.
# 'make setup' must have run first; otherwise these are empty and link fails
# with a clear "no input files" error.
ASM_SRCS      := $(wildcard $(ASM_DIR)/*.s)
ASM_OBJS      := $(patsubst $(ASM_DIR)/%.s,$(BUILD_DIR)/asm/%.o,$(ASM_SRCS))
C_SRCS        := $(wildcard $(SRC_DIR)/*.c)
C_OBJS        := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/src/%.o,$(C_SRCS))
ALL_OBJS      := $(ASM_OBJS) $(C_OBJS)

# R5900 EE assembly flags. -EL for little-endian, -mips3 because the EE is
# MIPS III with R5900-specific extensions (MMI, VU). spimdisasm output
# typically uses the standard EE mnemonics.
ASFLAGS       := -EL -march=r5900 -mabi=eabi -G 0 -no-pad-sections \
                 -I$(INCLUDE_DIR)

# Placeholder C flags. The matching compiler for ICO is most likely Sony
# Pro-DG (wcc) or Metrowerks CodeWarrior for PS2, not ee-gcc — these flags
# will evolve as the compiler is identified. Keep -O2 -G0 as starting points.
CFLAGS        := -c -G 0 -O2 -mips3 -EL \
                 -fno-builtin -nostdinc -I$(INCLUDE_DIR)

LDSCRIPT      := config/ico.$(VERSION).ld
AUTO_FUNCS    := config/undefined_funcs_auto.$(VERSION).txt
AUTO_SYMS     := config/undefined_syms_auto.$(VERSION).txt
EXTRA_SYMS    := config/undefined_funcs_extra.$(VERSION).txt
LDFLAGS       := -EL -T $(LDSCRIPT) \
                 $(if $(wildcard $(AUTO_FUNCS)),-T $(AUTO_FUNCS),) \
                 $(if $(wildcard $(AUTO_SYMS)),-T $(AUTO_SYMS),) \
                 $(if $(wildcard $(EXTRA_SYMS)),-T $(EXTRA_SYMS),) \
                 --no-check-sections --no-warn-mismatch \
                 -Map $(BUILD_DIR)/ico.$(VERSION).map

# ---- Phony targets -----------------------------------------------------------

.PHONY: all setup split clean distclean progress check-elf verify-elf

all: $(TARGET_ELF) verify-elf

# `make setup` — verify the ELF SHA-1, run splat, post-process asm.
setup: verify-baseelf split

# Run splat against the seed yaml. Re-run after any yaml edit.
split:
	@echo "==> running splat against $(SPLAT_YAML)"
	$(VENV_BIN)/splat split $(SPLAT_YAML)
	@echo "==> postprocessing asm (R5900 mnemonic fixups)"
	$(VENV_BIN)/python tools/postprocess_asm.py

verify-baseelf:
	@echo "==> verifying base ELF SHA-1"
	$(VENV_BIN)/python tools/verify_elf.py --target $(BASEELF)

verify-elf: $(TARGET_ELF)
	@echo "==> verifying built ELF SHA-1"
	$(VENV_BIN)/python tools/verify_elf.py --target $(TARGET_ELF)

progress:
	$(VENV_BIN)/python tools/progress.py

clean:
	rm -rf $(BUILD_DIR)

distclean: clean
	rm -rf $(ASM_DIR)/*.s $(LDSCRIPT) $(AUTO_FUNCS) $(AUTO_SYMS)

# ---- Rules -------------------------------------------------------------------

$(BUILD_DIR)/asm/%.o: $(ASM_DIR)/%.s | $(BUILD_DIR)/asm
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/src
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET_ELF): $(ALL_OBJS) $(LDSCRIPT)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(ALL_OBJS)

$(BUILD_DIR)/asm $(BUILD_DIR)/src:
	mkdir -p $@
