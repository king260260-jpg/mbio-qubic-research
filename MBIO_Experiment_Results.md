# MBIO Adaptive Parent Selection — Experimental Results

**Project:** Qiner / AntMiner  
**Baseline repository:** `https://github.com/qubic/Qiner`  
**Baseline commit:** `71cfbd66e4b648e2616e89475731d6ddcdf12f63`  
**Experiment:** Adaptive Parent Selection only  
**Compiler:** GNU C++ 13.3.0  
**Build type:** Release  
**Platform:** Linux x86-64  

## Scope

This experiment evaluates the implementation and local behavior of one mechanism only: adaptive parent selection.

The following mechanisms were not added to this experiment:

- Silk-inspired structural memory.
- Genetic inheritance or recombination.
- Selective parent replacement.
- New changes to BPP-9000.
- Changes to nonce validity or solution-validation rules.

The original Qiner source was kept as a separate baseline. MBIO was added behind the CMake option:

```text
-DENABLE_MBIO_PARENT_SELECTION=ON
```

With this option disabled, the original parent-selection path remains active.

## Integration point

The original `AntMiner.cpp` selects the best resolved and extendable node by the lowest score, then performs the existing 1-in-8 exploration behavior.

The MBIO build keeps the same 1-in-8 exploration probability. During exploitation, it selects among resolved and extendable parents using:

```text
quality = 1 / (1 + score)
weight = λ × quality + (1 - λ) × trail
```

The current default configuration is:

```text
exploration_probability = 1/8
quality_weight = 0.75
trail_weight = 0.25
trail_decay = 7/8
maximum_trail = 1.0
```

The trail is updated only after a submitted child is accepted by the existing mining path. The MBIO selector does not modify ANN bytes, nonce construction, BPP-9000 scoring, or validation rules.

## Build results

Both configurations built successfully:

```text
Baseline build: SUCCESS
MBIO build:     SUCCESS
```

The following executables were built in both configurations:

```text
Qiner
AntMiner
qiner_test
```

## Local unit-test results

The MBIO selector was tested with five test cases and 28 assertions.

```text
Passed all 5 test cases with 28 assertions.
```

The tests verified:

1. With empty trails, the selector chooses the same lowest-score parent as the baseline.
2. A validated improvement can reinforce a parent and affect later selection.
3. Unresolved or non-extendable parents are excluded.
4. Exploration is reproducible when the same seed is used.
5. Trail decay is bounded and follows the configured `7/8` decay factor.

## Interpretation

This experiment provides evidence that:

- The adaptive parent-selection module compiles.
- The module can be integrated into `AntMiner.cpp` behind a separate build option.
- The original baseline path remains available.
- The selector passes its current unit tests.
- The selector preserves deterministic behavior when supplied with the same random seed.

This experiment does **not** prove that MBIO improves Qubic mining performance. No live-node mining benchmark was performed in this environment, and no accepted-solution rate comparison is claimed here.

## Required next benchmark

The next experiment must run the two binaries against the same Qubic-compatible environment:

```text
AntMiner baseline
versus
AntMiner with MBIO adaptive parent selection
```

Both runs must use identical:

- Node and epoch context.
- Canonical task file.
- Mining identity and authorized test environment.
- Number of threads.
- Runtime duration.
- Hardware.
- Build configuration.
- Seed policy.

The benchmark should record:

- Accepted solutions.
- Best score.
- Best shift.
- Submitted solutions.
- Stale or rejected submissions.
- Candidates or mining work per second.
- CPU time and memory usage.
- Parent-selection counts by score and depth.
- Any validation or recomputation mismatch.

The actual mining test must be performed only with an authorized node and test setup. Private signing or mining seeds must never be committed to GitHub or shared publicly.

## Current conclusion

The current result is a successful implementation and local verification of the adaptive parent-selection mechanism. The performance hypothesis remains open until the controlled live or authorized testnet comparison is completed.
