#!/usr/bin/env python3
"""Supervisor-side state for the COMPLETION-GATED, STICKY decomp-match chain.

The decomp-match loop runs each iteration in a fresh Opus WORKER subagent so every
iteration starts from a clean context; the SUPERVISOR session only spawns ONE
worker, ends its turn, and is re-woken by the worker's completion notification to
spawn the next. There is no timer/cron — the gate is "previous worker finished".

Two correctness properties this script enforces, learned the hard way:

  STICKY RESUME. A worker often cannot drive a hard function all the way to its
  mechanical end (stall=30 -> bounded permuter -> park) within one session; it
  leaves a better-but-non-terminal near-miss body in the TU as the seed. If the
  NEXT worker were free to pick a DIFFERENT function (plain `smallest:1`), TWO
  functions would hold uncommitted bodies in one TU at once, and the second's
  park-commit fails the ninja SHA gate on the first's stray body (this is exactly
  what left func_00167120 half-parked). `nextspec` therefore pins the next spawn to
  the driver's CURRENT in-progress function until it is terminal (matched or
  genuinely parked), only then falling back to the chain's base set-spec.

  SEED-SAFE PREFLIGHT. Between workers, a stray body from an interrupted/abandoned
  function still poisons the next park-commit. `preflight` reverts such strays — but
  NEVER the active function's body (the live seed) and NEVER a pending rc0 match.

Sentinels (under .claude/):
  .decomp_chain_active  - holds the chain's BASE set-spec; its existence = running.
                          The user's off-switch is removing it (tools/loop_stop.sh).
  .decomp_worker.json   - {agent_id, output, spec, spawned_at} of the in-flight
                          worker. `output` is the harness-written transcript; its
                          freshness is the un-fakeable proof a worker is alive (the
                          Stop guard reads it to allow the supervisor's turn-end).

Subcommands:
  start <base_spec>             -> arm the chain with its base set-spec (idempotent)
  status                        -> in_flight | idle | stopped
  nextspec                      -> the set-spec the NEXT spawn must use (sticky)
  preflight                     -> revert foreign strays, protect the active seed
  spawned <agent_id> <out> <sp> -> record the in-flight worker
  clear                         -> remove the worker sentinel (worker done)
  stop                          -> remove chain + worker sentinel (loop_stop)
"""
import glob
import json
import os
import re
import shutil
import subprocess
import sys
import time

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
CLAUDE = os.path.join(ROOT, ".claude")
CHAIN = os.path.join(CLAUDE, ".decomp_chain_active")
WORKER = os.path.join(CLAUDE, ".decomp_worker.json")
STASH = os.path.join(CLAUDE, ".decomp_stash")
STATE_DIR = os.path.join(ROOT, "build", "match_loop")
PERM_RUNS = os.path.join(ROOT, "lib", "decomp-permuter", "runs")
FRESH = 600  # a live worker writes its transcript within 10 min; mirror in the guard


# ---------------------------------------------------------------- worker liveness
def fresh_worker():
    """True iff a delegated worker subagent is genuinely in flight: the sentinel
    points at a harness-created transcript that EXISTS and was either spawned or
    last written within FRESH seconds. Mirrored by decomp_stop_guard.worker_in_flight()."""
    try:
        s = json.load(open(WORKER))
    except Exception:
        return False
    now = time.time()
    out = s.get("output")
    if not out or not os.path.exists(out):
        return False
    if (now - (s.get("spawned_at") or 0)) < FRESH:
        return True
    try:
        return (now - os.path.getmtime(out)) < FRESH
    except OSError:
        return False


def status():
    if not os.path.exists(CHAIN):
        return "stopped"
    return "in_flight" if fresh_worker() else "idle"


# ------------------------------------------------------------------ driver state
def _base_spec():
    try:
        v = open(CHAIN).read().strip()
        return v or "smallest:1"
    except OSError:
        return "smallest:1"


def _current():
    """(func, tu) the driver is currently on, from its own queue sidecar."""
    try:
        q = json.load(open(os.path.join(STATE_DIR, "_drive_queue.json")))
        cur = q.get("current") or {}
        return cur.get("func"), cur.get("tu")
    except Exception:
        return None, None


def _real_run(func):
    d = os.path.join(PERM_RUNS, func)
    if not os.path.isdir(d):
        return False
    if glob.glob(os.path.join(d, "output-*")):
        return True
    try:
        return os.path.getsize(os.path.join(d, "permuter.log")) > 1024
    except OSError:
        return False


def _is_terminal(func):
    """True if <func> is resolved (matched, or genuinely permuter-exhausted parked)
    and the chain may move on. False if it is an in-progress near-miss that must be
    RESUMED to its mechanical end first. Mirrors the Stop guard's owes() logic."""
    if not func:
        return True
    try:
        st = json.load(open(os.path.join(STATE_DIR, func + ".json")))
    except Exception:
        return True   # no state -> nothing to resume
    best = st.get("best")
    if best is None:
        return False  # reset/pre-diff resume: owes work
    if best == 0:
        return True   # matched
    stall = st.get("stall") or 0
    if _real_run(func) and (st.get("permuted") or stall >= 30):
        return True   # genuinely parked
    return False      # near-miss in progress


def nextspec():
    """The set-spec the NEXT spawn must use. Sticky: if the driver's current func is
    a non-terminal near-miss, pin to it (drive it to its mechanical end before
    touching another function); otherwise fall back to the chain's base set-spec."""
    cur_func, _ = _current()
    if cur_func and not _is_terminal(cur_func):
        return cur_func
    return _base_spec()


# --------------------------------------------------------------------- preflight
def _file_has_real_body(rel_c, func):
    """True if <func> is present in <rel_c> as a real C definition (NOT an
    INCLUDE_ASM stub)."""
    if not func:
        return False
    try:
        txt = open(os.path.join(ROOT, rel_c), encoding="utf-8", errors="replace").read()
    except OSError:
        return False
    if not re.search(r"\b" + re.escape(func) + r"\b", txt):
        return False
    stub = re.search(r"INCLUDE_ASM(?:_NOAT)?\([^)]*,\s*" + re.escape(func) + r"\b", txt)
    return stub is None


def _holds_pending_match(rel_c):
    """True if <rel_c> holds a function whose json says best==0 (a freshly FOUND
    match) as real C — a pending commit that must never be reverted."""
    stem = rel_c[:-2] if rel_c.endswith(".c") else rel_c
    for jf in glob.glob(os.path.join(STATE_DIR, "*.json")):
        if os.path.basename(jf).startswith("_"):
            continue
        try:
            st = json.load(open(jf))
        except Exception:
            continue
        if st.get("best") != 0 or str(st.get("tu")) != stem:
            continue
        func = st.get("func") or os.path.splitext(os.path.basename(jf))[0]
        if _file_has_real_body(rel_c, func):
            return True
    return False


def preflight():
    """Between-worker cleanliness guard. Revert any dirty tracked .c that is a stray
    from an interrupted/abandoned function (it poisons later park-commits in that TU
    at the ninja SHA gate) — but PROTECT the active near-miss seed (the file holding
    the driver's current in-progress func as a real body) and any pending rc0 match.
    Skips entirely while a worker is in flight."""
    if fresh_worker():
        print("worker in flight — preflight skipped (won't touch a live worker's tree)")
        return
    try:
        out = subprocess.check_output(
            ["git", "diff", "--name-only", "HEAD", "--", "*.c"], cwd=ROOT, text=True)
    except Exception as e:
        print("preflight: git diff failed: %s (skipping)" % e)
        return
    files = [f for f in out.split() if f.endswith(".c")]
    if not files:
        print("preflight: working tree clean — nothing to clean")
        return
    cur_func, cur_tu = _current()
    reverted, kept = [], []
    for f in files:
        stem = f[:-2]
        if cur_func and stem == cur_tu and _file_has_real_body(f, cur_func):
            kept.append("%s (active seed: %s)" % (f, cur_func))
            continue
        if _holds_pending_match(f):
            kept.append("%s (pending rc0 match)" % f)
            continue
        try:
            os.makedirs(STASH, exist_ok=True)
            shutil.copyfile(os.path.join(ROOT, f),
                            os.path.join(STASH, f.replace("/", "__") + ".stray"))
        except OSError:
            pass
        subprocess.call(["git", "checkout", "HEAD", "--", f], cwd=ROOT)
        reverted.append(f)
    # Surface any dirty TOOLING / gate file. Workers must NEVER edit these (the
    # differ/driver/permuter/configs are the correctness oracle); a supervisor fix
    # here is legitimate but must be reviewed and ninja-verified before it rides
    # into a commit. Warn only — do not auto-revert, since the supervisor's own
    # fixes live here too.
    try:
        tout = subprocess.check_output(
            ["git", "diff", "--name-only", "HEAD", "--",
             "tools/", "config/", ".claude/hooks/"], cwd=ROOT, text=True)
        tooling = [t for t in tout.split() if t]
    except Exception:
        tooling = []
    if tooling:
        print("preflight: WARNING — dirty tooling/gate files (a worker must NOT edit "
              "these; review + ninja-verify before trusting): " + ", ".join(tooling))
    if reverted:
        print("preflight: stashed+reverted stray bodies (recoverable in "
              ".claude/.decomp_stash/): " + ", ".join(reverted))
    if kept:
        print("preflight: PROTECTED (not reverted): " + ", ".join(kept))
    if not reverted and not kept and not tooling:
        print("preflight: nothing to do")


# ----------------------------------------------------------------- chain sentinels
def _rm(*paths):
    for p in paths:
        try:
            os.remove(p)
        except OSError:
            pass


def start(base):
    os.makedirs(CLAUDE, exist_ok=True)
    if os.path.exists(CHAIN):
        return "already running (base=%s)" % _base_spec()
    with open(CHAIN, "w") as fh:
        fh.write(base + "\n")
    return "started (base=%s)" % base


def spawned(agent_id, output, spec):
    # SINGLE-WORKER INVARIANT: never register a second worker while one is still
    # in flight. A blind overwrite here is exactly how an untracked duplicate
    # worker (two agents grinding the same func, double token burn, TU clobber)
    # slips in. Refuse hard; the supervisor must `clear` a genuinely-finished
    # worker first (CASE B does), and TaskStop it to be sure it is dead.
    if fresh_worker():
        try:
            prev = json.load(open(WORKER)).get("agent_id")
        except Exception:
            prev = "?"
        sys.stderr.write(
            "REFUSED: a worker (%s) is still in flight — will NOT register a "
            "second. TaskStop it and `clear` before spawning the next.\n" % prev)
        sys.exit(3)
    os.makedirs(CLAUDE, exist_ok=True)
    if not os.path.exists(CHAIN):          # fallback; normally `start` created it
        with open(CHAIN, "w") as fh:
            fh.write(spec + "\n")
    with open(WORKER, "w") as fh:
        json.dump({"agent_id": agent_id, "output": output, "spec": spec,
                   "spawned_at": int(time.time())}, fh)


def main():
    a = sys.argv[1:]
    if not a:
        sys.stderr.write("usage: decomp_chain.py "
                         "start|status|guard|nextspec|preflight|warnings|spawned|clear|stop\n")
        sys.exit(2)
    cmd = a[0]
    if cmd == "status":
        print(status())
    elif cmd == "guard":
        # Pre-spawn gate: run IMMEDIATELY BEFORE the Agent call. Exits non-zero if
        # a worker is still in flight so the supervisor never launches a second
        # one. Enforces the SINGLE-WORKER invariant at the only point that matters.
        if fresh_worker():
            try:
                prev = json.load(open(WORKER)).get("agent_id")
            except Exception:
                prev = "?"
            print("BLOCKED: worker %s still in flight — do NOT spawn; "
                  "TaskStop it and `clear` first." % prev)
            sys.exit(3)
        print("clear-to-spawn")
    elif cmd == "nextspec":
        print(nextspec())
    elif cmd == "preflight":
        preflight()
    elif cmd == "start":
        if len(a) < 2:
            sys.stderr.write("usage: decomp_chain.py start <base_spec>\n")
            sys.exit(2)
        print(start(a[1]))
    elif cmd == "spawned":
        if len(a) < 4:
            sys.stderr.write("usage: decomp_chain.py spawned <agent_id> <output> <spec>\n")
            sys.exit(2)
        spawned(a[1], a[2], a[3])
        print("armed")
    elif cmd == "warnings":
        log = os.path.join(STATE_DIR, "_volatile_warnings.log")
        try:
            lines = [l for l in open(log).read().splitlines() if l.strip()]
        except OSError:
            lines = []
        if lines:
            for l in lines:
                parts = l.split("\t")
                print("VOLATILE-COMMIT (review, §2.7 do-not-ship): " + " ".join(parts))
            _rm(log)
        else:
            print("(no volatile-commit warnings)")
    elif cmd == "clear":
        _rm(WORKER)
        print("cleared")
    elif cmd == "stop":
        _rm(CHAIN, WORKER)
        print("stopped")
    else:
        sys.stderr.write("unknown subcommand: " + cmd + "\n")
        sys.exit(2)


if __name__ == "__main__":
    main()
