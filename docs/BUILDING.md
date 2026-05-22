# Building ico

End-to-end walkthrough from a fresh clone to a byte-identical EE ELF.

## 0. Prerequisites

- Linux or macOS host (the toolchain script targets Debian/Ubuntu apt
  package names; macOS and other distros may need manual steps).
- `git`, `python3` ≥ 3.10, `make`, `bash`, `gh` (GitHub CLI).
- Optional but recommended: `docker` (for the pinned ps2dev EE toolchain
  image — avoids a long source build).
- A legally-owned copy of *ICO* (PlayStation 2, USA release, SCUS-97113)
  as a `.bin` + `.cue` pair.

## 1. Run the host setup script

```sh
./tools/setup.sh
```

Idempotent. Performs:

1. Creates `.venv/` and installs `tools/requirements.txt` (capstone,
   spimdisasm, splat64, pyyaml, …).
2. `git submodule update --init --recursive` — populates `lib/splat/`,
   `lib/asm-differ/`, `lib/decomp-permuter/`, `lib/m2c/`.
3. Fetches the matching C compiler **ee-gcc 2.9-991111-01** (~2 MB) into
   `tools/cc/ee-gcc2.9-991111/`, plus **ee-gcc 2.96** (~18 MB) into
   `tools/cc/ee-gcc2.96/` solely for its bundled `ee-as 2.10` (used by
   the src/.o assembler step). Both are sourced from `decompme/compilers`.
   The binaries are 32-bit i386, so on a 64-bit host you need multilib
   / 32-bit libc:

   ```sh
   sudo dpkg --add-architecture i386
   sudo apt-get update
   sudo apt-get install libc6:i386 libstdc++6:i386 zlib1g:i386
   ```

   `tools/setup.sh` warns if the binary is present but won't execute.
4. Downloads a pinned Ghidra release into `tools/ghidra/`.
5. `pip install -e lib/m2c` for `m2c` on `PATH`.
6. Best-effort `apt-get install pcsx2` (or notes the AppImage path).
7. Installs the IP-safety pre-commit hook via `tools/install_hooks.sh`.

Skip flags: `SKIP_TOOLCHAIN=1`, `SKIP_GHIDRA=1`, `SKIP_PCSX2=1`.

## 2. Provide the disc image

The disc image must live at `baserom/Ico_USA.bin` and `baserom/Ico_USA.cue`
(both gitignored). Copy them in by hand:

```sh
cp "/path/to/Ico (USA).bin" baserom/Ico_USA.bin
cp "/path/to/Ico (USA).cue" baserom/Ico_USA.cue
```

## 3. Extract the EE ELF

```sh
./tools/extract_elf.sh
```

Reads the ISO9660 filesystem from the disc image, extracts the boot ELF
named in `SYSTEM.CNF` (`SCUS_971.13`), writes it to `baserom/baseelf.elf`,
and records its SHA-1 to `config/sha1sums.txt` if the file is empty
(otherwise verifies against the existing entry).

## 4. Verify and split

```sh
make setup
```

- Verifies `baserom/baseelf.elf` SHA-1 against `config/sha1sums.txt`.
- Runs splat against `config/ico.us.yaml`, emitting `asm/*.s`,
  `config/ico.us.ld`, and the auto symbol files.
- Runs `tools/postprocess_asm.py` for any R5900-specific asm fixups.

## 5. Build

```sh
make
```

- Assembles every `asm/*.s` with the EE assembler.
- Compiles every `src/*.c` with the EE compiler.
- Links via the splat-generated linker script.
- SHA-1-verifies the produced `build/baseelf.elf` against the recorded
  hash. The build fails loudly if the bytes diverge.

A first-time build with everything as `asm` should round-trip — the
re-linked ELF is byte-identical to the extracted one. If it isn't,
that's a tooling bug, not a matching bug — escalate to maintainer.

## 6. Test (optional)

```sh
pcsx2 build/baseelf.elf
```

PCSX2 will boot the rebuilt ELF directly. Useful sanity-check after
matching a function that touches input/render/audio.

## Known wrinkles

- **Compiler identification is open.** ICO predates ee-gcc adoption at
  Sony first parties; the matching compiler is most likely Sony Pro-DG
  (wcc) or Metrowerks CodeWarrior for PS2. The Makefile's `CFLAGS`
  default to ee-gcc-ish flags as a starting point. Confirm by inspecting
  `baseelf.elf`'s `.comment` section after extraction; record findings
  in `decomp/NOTES.md`.
- **splat PS2 support.** Recent splat versions handle R5900 / ELF input,
  but the path is less battle-tested than N64 ROM. If splat panics on
  the seed yaml, file an issue against `lib/splat/` and pin to a known-
  good fork in `.gitmodules`.
- **R5900 multimedia instructions (MMI, VU).** `m2c` may surface
  unsupported opcodes. Track in `decomp/NOTES.md`; hand-decompile or use
  Ghidra for those functions.
