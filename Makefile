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

# Toolchain prefix. Defaults to the EE-specific ps2dev prefix; falls back to
# system mips-linux-gnu-* (in r5900 mode) when the EE toolchain is absent —
# fine for splat-output round-tripping and most matching work, but the EE
# compiler is required for full byte-identical matching of compiler-emitted
# code. Override with `make MIPS_PREFIX=...` if your binaries differ.
ifeq ($(shell command -v mips64r5900el-ps2-elf-as 2>/dev/null),)
  MIPS_PREFIX ?= mips-linux-gnu-
else
  MIPS_PREFIX ?= mips64r5900el-ps2-elf-
endif
AS            := $(MIPS_PREFIX)as
CC            := $(MIPS_PREFIX)gcc
LD            := $(MIPS_PREFIX)ld
OBJCOPY       := $(MIPS_PREFIX)objcopy

BUILD_DIR     := build
ASM_DIR       := asm
SRC_DIR       := src
INCLUDE_DIR   := include

ASM_SRCS      := $(shell find $(ASM_DIR) -name '*.s' 2>/dev/null)
ASM_OBJS      := $(patsubst $(ASM_DIR)/%.s,$(BUILD_DIR)/asm/%.o,$(ASM_SRCS))
C_SRCS        := $(wildcard $(SRC_DIR)/*.c)
C_OBJS        := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/src/%.o,$(C_SRCS))
ALL_OBJS      := $(ASM_OBJS) $(C_OBJS)

# R5900 EE assembly flags. Little-endian, MIPS III base + r5900 extensions.
ASFLAGS       := -EL -march=r5900 -mabi=eabi -G 0 -no-pad-sections -I$(INCLUDE_DIR)

# Placeholder C flags. Real matching CFLAGS will evolve as the compiler is
# identified. ee-gcc / Pro-DG / CodeWarrior all want different flag sets.
CFLAGS        := -c -G 0 -O2 -mips3 -EL -fno-builtin -nostdinc -I$(INCLUDE_DIR)

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
	@echo "==> postprocessing asm (R5900 mnemonic fixups)"
	$(VENV_BIN)/python tools/postprocess_asm.py

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
	find $(ASM_DIR) -mindepth 1 -maxdepth 2 -type f -name '*.s' ! -path '$(ASM_DIR)/nonmatchings/*' -delete
	rm -f $(LDSCRIPT) $(AUTO_FUNCS) $(AUTO_SYMS) config/ico.$(VERSION).d

# ---- Rules -------------------------------------------------------------------

$(BUILD_DIR)/asm/%.o: $(ASM_DIR)/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET_ELF): $(ALL_OBJS) $(LDSCRIPT)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(ALL_OBJS)

$(TARGET_ROM): $(TARGET_ELF)
	$(OBJCOPY) -O binary --gap-fill=0x00 $< $@
