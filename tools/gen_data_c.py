#!/usr/bin/env python3
"""tools/gen_data_c.py -- write a data-only member as C from the base ELF.

The members config/data_schema.pal.txt lists are written in the form the
developers compiled: one C translation unit per member, an initialized array
of the member's record type, which ninja compiles with the game's flags
(tools/compile_c.sh). The values come from the user's own
baserom/pal/baseelf.elf at build time and are never committed (docs/LEGAL.md);
the schema row and the record's header hold only types.

Four modes, one member each (MEMBER is the name in the schema):

  --stub MEMBER --out F.s
      a zero-filled stand-in of the member's ROM range carrying its symbols,
      for the layout link (build/ico.layout.elf) that fixes every other
      object's address before the C exists
  --alias MEMBER --labels build/data_labels.txt --out F.ld
      the linker assignments that bind each placeholder label a source spells
      inside the member (D_<VMA>) to the member's symbol plus its offset
  --c MEMBER --layout build/ico.layout.elf --out F.c
      the member's C: every pointer word resolved to the symbol the layout
      link places at that address, floats as the shortest decimal that reads
      back to the same bits, strings as literals
  --check MEMBER --obj F.o --layout build/ico.layout.elf --out STAMP
      the compiled object's section, with its relocations applied against the
      layout link, must equal the member's ROM range (zero fill after it);
      otherwise the first differing offset and the field there are reported

The record type is read from the header the schema row names: a typedef of a
struct whose fields are integers, floats, pointers (object or function),
arrays and nested structs, laid out by the EE's rules (4-byte pointers and
ints, 8-byte long long and double).
"""

import argparse
import re
import struct
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import extract_data  # noqa: E402  (the member table's parser and ROM reader)

SCHEMA = ROOT / "config/data_schema.pal.txt"
TABLE = ROOT / "config/data_members.pal.txt"
BASE_ELF = ROOT / "baserom/pal/baseelf.elf"


def fail(msg):
    sys.exit(f"gen_data_c: {msg}")


# ---------------------------------------------------------------- schema ----

def parse_schema(path=SCHEMA):
    rows = {}
    for n, line in enumerate(path.read_text().splitlines(), 1):
        f = line.split("#", 1)[0].split()
        if not f:
            continue
        if len(f) not in (6, 7) or f[1] not in ("data", "rodata"):
            fail(f"{path}:{n}: expected '<member> <section> <type> <header> <count> <symbols> [hex=...]'")
        syms = []
        for s in f[5].split(","):
            name, idx = s.split("@")
            syms.append((name, int(idx)))
        if syms[0][1] != 0 or any(b[1] <= a[1] for a, b in zip(syms, syms[1:])):
            fail(f"{path}:{n}: symbols must start at element 0 and ascend")
        hexf = set()
        if len(f) == 7:
            if not f[6].startswith("hex="):
                fail(f"{path}:{n}: bad column '{f[6]}'")
            hexf = set(f[6][4:].split(","))
        rows[f[0]] = dict(member=f[0], section=f[1], type=f[2], header=f[3], count=int(f[4]),
                          syms=syms, hex=hexf, line=n)
    return rows


def member_row(name):
    sch = parse_schema()
    if name not in sch:
        fail(f"{name} is not in {SCHEMA.relative_to(ROOT)}")
    s = sch[name]
    rows = [r for r in extract_data.parse_table(TABLE) if r["member"] == name]
    if len(rows) != 1 or rows[0]["section"] != s["section"]:
        fail(f"{name}: needs exactly one .{s['section']} row in {TABLE.relative_to(ROOT)}")
    return s, rows[0]


# ------------------------------------------------------------ C types -------

class T:
    """A C type: kind is int, float, ptr, fptr, array or struct."""

    def __init__(self, kind, size, align, **kw):
        self.kind, self.size, self.align = kind, size, align
        self.__dict__.update(kw)


BASE_WORDS = {"unsigned", "signed", "char", "short", "int", "long", "float", "double",
              "void", "const", "volatile"}

INTS = {
    "char": (1, True), "signed char": (1, True), "unsigned char": (1, False),
    "short": (2, True), "short int": (2, True), "signed short": (2, True),
    "unsigned short": (2, False), "unsigned short int": (2, False),
    "int": (4, True), "signed int": (4, True), "signed": (4, True),
    "unsigned int": (4, False), "unsigned": (4, False),
    "long long": (8, True), "long long int": (8, True),
    "unsigned long long": (8, False), "unsigned long long int": (8, False),
}


def strip_c(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    text = re.sub(r"//[^\n]*", " ", text)
    return "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#"))


def tokenize(text):
    return re.findall(r"0[xX][0-9a-fA-F]+|\d+|[A-Za-z_]\w*|\.\.\.|[{}()\[\];,*:=+\-/]", text)


class Header:
    def __init__(self, path):
        self.path = path
        self.toks = tokenize(strip_c((ROOT / path).read_text(encoding="latin-1")))
        self.cache = {}

    def typedef(self, name):
        if name in self.cache:
            return self.cache[name]
        t = self.toks
        for i, tok in enumerate(t):
            if tok != name or i == 0:
                continue
            j = i + 1
            # `} name [attrs] ;` closing a typedef struct/union
            if t[i - 1] == "}" or t[i - 1] == ")":
                k = i - 1
                while t[k] == ")":  # an __attribute__ before the name
                    k = self._skip_back_parens(k)
                    k -= 1  # the __attribute__ token
                    k -= 1
                if t[k] != "}":
                    continue
                start = self._match_back(k)
                kw = start - 1
                while t[kw] not in ("struct", "union"):
                    kw -= 1
                if t[kw - 1] != "typedef":
                    continue
                ty = self._aggregate(kw, start)
                ty.name = name
                while t[j] == "__attribute__":
                    j, al = self._attribute(j)
                    if al:
                        ty.align = max(ty.align, al)
                        ty.size = -(-ty.size // ty.align) * ty.align
                self.cache[name] = ty
                return ty
            # `typedef <type> name;`
            if t[j] == ";":
                k = i - 1
                while k >= 0 and t[k] not in (";", "}", "{"):
                    k -= 1
                if t[k + 1] == "typedef" and t[k + 2] not in ("struct", "union"):
                    ty = self.base_type(t[k + 2:i])
                    self.cache[name] = ty
                    return ty
        fail(f"{self.path}: no typedef {name}")

    def _match_back(self, k):
        depth = 0
        while True:
            if self.toks[k] == "}":
                depth += 1
            elif self.toks[k] == "{":
                depth -= 1
                if depth == 0:
                    return k
            k -= 1

    def _skip_back_parens(self, k):
        depth = 0
        while True:
            if self.toks[k] == ")":
                depth += 1
            elif self.toks[k] == "(":
                depth -= 1
                if depth == 0:
                    return k
            k -= 1

    def _attribute(self, j):
        """__attribute__((...)) at j: the index after it and any aligned(N)."""
        t = self.toks
        depth, k, al = 0, j + 1, 0
        while True:
            if t[k] == "(":
                depth += 1
            elif t[k] == ")":
                depth -= 1
                if depth == 0:
                    break
            elif t[k] in ("aligned", "__aligned__"):
                al = int(t[k + 2], 0)
            elif t[k] in ("packed", "__packed__"):
                fail(f"{self.path}: packed records are not supported")
            k += 1
        return k + 1, al

    def base_type(self, toks):
        toks = [x for x in toks if x not in ("const", "volatile", "signed") or len(toks) == 1]
        key = " ".join(toks)
        if key in INTS:
            n, sg = INTS[key]
            return T("int", n, n, signed=sg, name=key)
        if key == "float":
            return T("float", 4, 4, name=key)
        if key == "double":
            return T("float", 8, 8, name=key)
        if key == "void":
            return T("void", 0, 1, name=key)
        if len(toks) == 2 and toks[0] in ("struct", "union"):
            return T("opaque", 0, 1, name=key)
        if len(toks) == 1:
            ty = self.typedef(toks[0])
            return ty
        fail(f"{self.path}: unknown type '{key}'")

    def _aggregate(self, kw, start):
        """Parse struct/union at keyword index kw, body opening at start."""
        t = self.toks
        is_union = t[kw] == "union"
        k = start + 1
        fields = []
        while t[k] != "}":
            if t[k] in ("struct", "union") and (t[k + 1] == "{" or t[k + 2] == "{"):
                ob = k + 1 if t[k + 1] == "{" else k + 2
                end = ob
                depth = 0
                while True:
                    if t[end] == "{":
                        depth += 1
                    elif t[end] == "}":
                        depth -= 1
                        if depth == 0:
                            break
                    end += 1
                base = self._aggregate(k, ob)
                k = end + 1
            else:
                b = k
                if t[k] in ("struct", "union"):
                    k += 2
                elif t[k] in BASE_WORDS:
                    while t[k] in BASE_WORDS:
                        k += 1
                else:
                    k += 1
                base = self.base_type(t[b:k])
            # declarators up to ';'
            while True:
                d0 = k
                depth = 0
                while not (depth == 0 and t[k] in (",", ";")):
                    if t[k] in ("(", "["):
                        depth += 1
                    elif t[k] in (")", "]"):
                        depth -= 1
                    k += 1
                name, ty = self._declarator(t[d0:k], base)
                fields.append((name, ty))
                k += 1
                if t[k - 1] == ";":
                    break
        off = 0
        size = 0
        align = 1
        laid = []
        for name, ty in fields:
            align = max(align, ty.align)
            if is_union:
                laid.append((name, ty, 0))
                size = max(size, ty.size)
            else:
                off = -(-off // ty.align) * ty.align
                laid.append((name, ty, off))
                off += ty.size
                size = off
        size = -(-size // align) * align
        return T("struct", size, align, fields=laid, union=is_union)

    def _declarator(self, toks, base):
        if ":" in toks:
            fail(f"{self.path}: bit-fields are not supported ({' '.join(toks)})")
        attrs = [i for i, x in enumerate(toks) if x == "__attribute__"]
        if attrs:
            toks = toks[:attrs[0]]
        if "(" in toks and toks[0] == "(" and toks[1] == "*":
            # function pointer: ( * name ) ( params )
            name = toks[2]
            close = toks.index(")")
            params = " ".join(toks[close + 2:-1])
            return name, T("fptr", 4, 4, ret=base, params=params)
        ptr = 0
        while toks and toks[0] == "*":
            ptr += 1
            toks = toks[1:]
        name = toks[0]
        dims = []
        rest = toks[1:]
        while rest:
            if rest[0] != "[":
                fail(f"{self.path}: cannot read declarator '{' '.join(toks)}'")
            e = rest.index("]")
            dims.append(int(eval(" ".join(rest[1:e]), {"__builtins__": {}})))
            rest = rest[e + 1:]
        ty = base
        for _ in range(ptr):
            ty = T("ptr", 4, 4, target=ty)
        for n in reversed(dims):
            ty = T("array", ty.size * n, ty.align, elem=ty, n=n)
        return name, ty


# ------------------------------------------------------------ symbols -------

PLACEHOLDER = re.compile(r"^(D_|func_|jtbl_)[0-9A-F]{8}$")


class Layout:
    """Addresses of the layout link: every defined symbol, by address."""

    def __init__(self, path):
        self.by_addr = {}
        self.by_name = {}
        with open(path, "rb") as fh:
            e = ELFFile(fh)
            for s in e.get_section_by_name(".symtab").iter_symbols():
                info = s["st_info"]
                if s["st_shndx"] == "SHN_UNDEF" or info["type"] in ("STT_SECTION", "STT_FILE"):
                    continue
                if not s.name or s.name.startswith(("$", ".")):
                    continue
                rec = (s.name, info["bind"], info["type"], s["st_shndx"])
                self.by_addr.setdefault(s["st_value"], []).append(rec)
                if info["bind"] == "STB_GLOBAL":
                    self.by_name[s.name] = s["st_value"]

    def name_at(self, addr, func):
        """The global a source can name at addr: a function when func, else an object."""
        cands = self.by_addr.get(addr, [])
        glob = [c for c in cands if c[1] == "STB_GLOBAL" and c[3] != "SHN_ABS"
                and not PLACEHOLDER.match(c[0])]
        want = "STT_FUNC" if func else "STT_OBJECT"
        typed = [c for c in glob if c[2] == want] or glob
        names = sorted({c[0] for c in typed})
        if len(names) == 1:
            return names[0], None
        if not names:
            local = sorted({c[0] for c in cands})
            return None, (f"no global symbol at 0x{addr:08X}" +
                          (f" (only {', '.join(local)}, not visible to another file)" if local else ""))
        return None, f"several globals at 0x{addr:08X}: {', '.join(names)}"


# ----------------------------------------------------------- spelling -------

def float_text(bits, double=False):
    if double:
        v = struct.unpack("<d", bits)[0]
        r = repr(v)
        return r if ("e" in r or "." in r or "n" in r) else r + ".0"
    v = struct.unpack("<f", bits)[0]
    if v != v or v in (float("inf"), float("-inf")):
        return None
    for d in range(1, 10):
        s = f"{v:.{d}g}"
        if struct.pack("<f", float(s)) == bits:
            break
    m, _, e = s.partition("e")
    if e:
        exp = int(e)
        if -5 <= exp < 9:
            s = f"{float(s):.{max(0, len(m.replace('-', '').replace('.', '')) - 1 - exp)}f}"
        else:
            s = f"{m}e{exp}"
    if "." not in s and "e" not in s:
        s += ".0"
    return s + "f"


def int_text(v, ty, hexed):
    if hexed:
        v &= (1 << (8 * ty.size)) - 1
        return f"0x{v:X}" if v else "0"
    if ty.signed and v >= 1 << (8 * ty.size - 1):
        v -= 1 << (8 * ty.size)
    if ty.size == 8:
        return f"{v}LL"
    return str(v)


def c_decl(ty, name):
    """The declaration of an object of type ty named name, or None for void."""
    if ty.kind == "void" or ty.kind == "opaque":
        return None
    if ty.kind in ("int", "float"):
        return f"{ty.name} {name}"
    if ty.kind == "ptr":
        inner = c_decl(ty.target, "*" + name)
        return inner if inner is not None else f"void *{name}"
    if ty.kind == "struct" and getattr(ty, "name", None):
        return f"{ty.name} {name}"
    return None


def c_string(bs):
    out = []
    for b in bs:
        c = chr(b)
        if c == '"' or c == "\\":
            out.append("\\" + c)
        elif 0x20 <= b < 0x7F or b >= 0xA1:
            out.append(c)  # ASCII, or an EUC-JP byte as the developer typed it
        else:
            out.append(f"\\{b:03o}")
    return '"' + "".join(out) + '"'


class Writer:
    def __init__(self, data, base, layout, hexf, relocs=None):
        self.data, self.base, self.layout, self.hexf = data, base, layout, hexf
        self.funcs, self.objs, self.errors = set(), {}, []

    def value(self, ty, off, path):
        d = self.data
        if ty.kind == "int":
            v = int.from_bytes(d[off:off + ty.size], "little")
            return int_text(v, ty, path in self.hexf)
        if ty.kind == "float":
            s = float_text(d[off:off + ty.size], ty.size == 8)
            if s is None:
                self.errors.append(f"0x{self.base + off:08X} {path}: NaN or infinity in a float field")
                return "0.0f"
            return s
        if ty.kind in ("ptr", "fptr"):
            v = int.from_bytes(d[off:off + 4], "little")
            if v == 0:
                return "0"
            func = ty.kind == "fptr"
            name, err = self.layout.name_at(v, func)
            if name is None:
                self.errors.append(f"0x{self.base + off:08X} {path}: {err}")
                return f"0 /* 0x{v:08X} */"
            if func:
                self.funcs.add(name)
                return name
            decl = c_decl(ty.target, name)
            if decl is None:
                self.objs[name] = f"char {name}[]"
                return name
            self.objs[name] = decl
            return "&" + name
        if ty.kind == "array":
            el = ty.elem
            if el.kind == "int" and el.size == 1:
                bs = d[off:off + ty.n]
                nul = bs.find(0)
                if nul < 0 or not any(bs[nul:]):
                    return c_string(bs[:nul] if nul >= 0 else bs)
            return "{" + ", ".join(self.value(el, off + i * el.size, f"{path}[]")
                                   for i in range(ty.n)) + "}"
        if ty.kind == "struct":
            if ty.union:
                name, f, o = ty.fields[0]
                return "{" + self.value(f, off + o, f"{path}.{name}" if path else name) + "}"
            parts = []
            end = 0
            for name, f, o in ty.fields:
                if any(d[off + end:off + o]):
                    self.errors.append(f"0x{self.base + off + end:08X} {path}: nonzero padding before {name}")
                parts.append(self.value(f, off + o, f"{path}.{name}" if path else name))
                end = o + f.size
            if any(d[off + end:off + ty.size]):
                self.errors.append(f"0x{self.base + off + end:08X} {path}: nonzero tail padding")
            return "{" + ", ".join(parts) + "}"
        fail(f"cannot write a value of kind {ty.kind} ({path})")


def write_c(s, row, data, layout):
    hdr = Header(s["header"])
    ty = hdr.typedef(s["type"])
    size = ty.size * s["count"]
    span = row["hi"] - row["lo"]
    if size > span or any(data[size:]):
        fail(f"{s['member']}: {s['count']} x {s['type']} ({ty.size} B) = {size} B, "
             f"but the ROM range holds {span} B" + (" with nonzero bytes after it" if size <= span else ""))
    w = Writer(data, row["lo"], layout, s["hex"])
    bounds = [i for _, i in s["syms"]] + [s["count"]]
    arrays = []
    for (name, first), last in zip(s["syms"], bounds[1:]):
        lines = [f"    {w.value(ty, i * ty.size, '')}," for i in range(first, last)]
        arrays.append((name, last - first, lines))
    if w.errors:
        fail(f"{s['member']}: the record {s['type']} does not hold the ROM's bytes:\n  " +
             "\n  ".join(w.errors[:20]) + (f"\n  ... {len(w.errors) - 20} more" if len(w.errors) > 20 else ""))
    inc = Path("../..") / s["header"]
    out = [
        f"/* {s['member']}.o .{row['section']}, written by tools/gen_data_c.py from",
        " * baserom/pal/baseelf.elf and config/data_schema.pal.txt. Generated: do not commit. */",
        "",
        f'#include "{inc.as_posix()}"',
        "",
    ]
    for f in sorted(w.funcs):
        out.append(f"extern void {f}();")
    for o in sorted(w.objs):
        out.append(f"extern {w.objs[o]};")
    if w.funcs or w.objs:
        out.append("")
    const = "const " if s["section"] == "rodata" else ""
    for name, n, lines in arrays:
        out.append(f"{const}{s['type']} {name}[{n}] = {{")
        out.extend(lines)
        out.append("};")
        out.append("")
    return "\n".join(out)


# --------------------------------------------------------- stub / alias -----

def write_stub(s, row):
    lo, hi = row["lo"], row["hi"]
    align = extract_data.natural_align(lo)
    out = [f"# layout stand-in for {s['member']}.o .{row['section']} (zeros); generated.",
           f"    .section .{row['section']}", f"    .align {align.bit_length() - 1}"]
    out += [f"    .globl {n}" for n, _ in s["syms"]]
    hdr = Header(s["header"])
    size = hdr.typedef(s["type"]).size
    a = 0
    for n, i in s["syms"]:
        if i * size > a:
            out.append(f"    .space {i * size - a}")
            a = i * size
        out.append(f"{n}:")
    out.append(f"    .space {hi - lo - a}")
    return "\n".join(out) + "\n"


def write_alias(s, row, labels_path):
    lo, hi = row["lo"], row["hi"]
    first = s["syms"][0][0]
    own = {n for n, _ in s["syms"]}
    out = [f"/* {s['member']}: placeholder labels sources spell inside it; generated. */"]
    for line in Path(labels_path).read_text().splitlines():
        if not line.strip():
            continue
        name, addr = line.split()
        a = int(addr, 16)
        if lo <= a < hi and name not in own:
            out.append(f"{name} = {first} + {a - lo};")
    return "\n".join(out) + "\n"


# --------------------------------------------------------------- check ------

def check(s, row, data, obj, layout):
    sec = "." + ("rodata" if s["section"] == "rodata" else "data")
    with open(obj, "rb") as fh:
        e = ELFFile(fh)
        target = e.get_section_by_name(sec)
        if target is None:
            fail(f"{obj}: no {sec}")
        for other in (".data", ".rodata", ".sdata", ".sbss", ".bss", ".text"):
            t = e.get_section_by_name(other)
            if other != sec and t is not None and t["sh_size"]:
                fail(f"{obj}: {t['sh_size']} B in {other}; the member is all {sec}")
        got = bytearray(target.data())
        symtab = e.get_section_by_name(".symtab")
        for rs in e.iter_sections():
            if not isinstance(rs, RelocationSection) or e.get_section(rs["sh_info"]).name != sec:
                continue
            for r in rs.iter_relocations():
                if r["r_info_type"] != 2:  # R_MIPS_32
                    fail(f"{obj}: relocation type {r['r_info_type']} at 0x{r['r_offset']:x}")
                sym = symtab.get_symbol(r["r_info_sym"])
                if sym["st_shndx"] == "SHN_UNDEF":
                    if sym.name not in layout.by_name:
                        fail(f"{obj}: {sym.name} is not defined by the layout link")
                    v = layout.by_name[sym.name]
                elif e.get_section(sym["st_shndx"]).name == sec:
                    v = row["lo"] + sym["st_value"]
                else:
                    fail(f"{obj}: relocation against {e.get_section(sym['st_shndx']).name}")
                o = r["r_offset"]
                v += int.from_bytes(got[o:o + 4], "little")
                got[o:o + 4] = (v & 0xFFFFFFFF).to_bytes(4, "little")
    want = data
    if len(got) > len(want) or any(want[len(got):]) or bytes(got) != want[:len(got)]:
        n = min(len(got), len(want))
        diff = next((i for i in range(n) if got[i] != want[i]), n)
        ty = Header(s["header"]).typedef(s["type"])
        el, within = divmod(diff, ty.size)
        fail(f"{obj}: {sec} differs from the ROM at 0x{row['lo'] + diff:08X} "
             f"(element {el}, offset 0x{within:x} of {s['type']}; object {len(got)} B, ROM {len(want)} B)")
    return len(got)


def write_if_changed(path, text):
    """Write text (bytes 0..255 as themselves) unless the file already holds
    it, so ninja's restat skips the compile and link that depend on it."""
    raw = text.encode("latin-1")
    if path.exists() and path.read_bytes() == raw:
        return
    path.write_bytes(raw)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--stub")
    g.add_argument("--alias")
    g.add_argument("--c")
    g.add_argument("--check")
    ap.add_argument("--elf", type=Path, default=BASE_ELF)
    ap.add_argument("--layout", type=Path)
    ap.add_argument("--labels", type=Path)
    ap.add_argument("--obj", type=Path)
    ap.add_argument("--out", type=Path, required=True)
    a = ap.parse_args()
    member = a.stub or a.alias or a.c or a.check
    s, row = member_row(member)
    a.out.parent.mkdir(parents=True, exist_ok=True)
    if a.stub:
        write_if_changed(a.out, write_stub(s, row))
        return 0
    if a.alias:
        write_if_changed(a.out, write_alias(s, row, a.labels))
        return 0
    with open(a.elf, "rb") as fh:
        data = extract_data.rom_bytes(ELFFile(fh), row["lo"], row["hi"], row["section"])
    layout = Layout(a.layout)
    if a.c:
        write_if_changed(a.out, write_c(s, row, data, layout))
        return 0
    n = check(s, row, data, a.obj, layout)
    a.out.write_text(f"{member} {n} B equal to 0x{row['lo']:08X}..0x{row['lo'] + n:08X}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
