# MBIO – Mubarak Bio-Inspired Optimization
## A Theoretical and Scientific Research Proposal for Adaptive Collective Intelligence in Qubic-Related Systems

**Author:** Mubarak  
**Date:** November 2026  
**Prototype:** MBIO v0.1; revised research plan v0.2  
**Implementation language:** C++17

---

## Letter to the Qubic Team

Dear Qubic Team,

Please excuse any language mistakes in this document. English is not my first language, and I am not a technical expert. However, I am very interested in the Qubic project and highly motivated to learn and contribute in any way I can.

I am sharing this work as an attempt to make a useful contribution, not as a claim of expertise or as a finished technical solution. The project began as a theoretical research idea and has now developed into an independent C++ prototype for experimental evaluation.

I would greatly appreciate feedback on the feasibility of these ideas, the terminology used, and the most appropriate direction for further research. I would also be grateful for guidance on how this work could be improved or aligned with the priorities and technical requirements of the Qubic team.

Thank you for your time and consideration.

Respectfully,  
**Mubarak**

---

## Abstract

This document proposes MBIO (Mubarak Bio-Inspired Optimization), an independent research project that explores whether biological collective-intelligence principles can improve adaptive search, resource allocation, and cooperation among computational agents in Qubic-related systems.

The research defines several computational models, while the current MBIO v0.1 prototype focuses only on the first three:

1. **Slime mold:** adaptive path selection and feedback-driven reinforcement.
2. **Termite colonies:** cumulative memory of successful paths and structural patterns.
3. **Wolf packs:** dynamic specialization of computational roles.
4. **Silk-inspired memory:** persistent but decaying links between successful structures.
5. **Genetic inheritance and selective replacement:** controlled variation and retirement or down-weighting of weaker parents when better offspring are validated.

A first standalone prototype, MBIO v0.1, has been implemented in C++17. The prototype currently provides adaptive path and parent selection, cumulative path memory, and dynamic roles for exploration, refinement, and structural exploration.

The silk-inspired memory, genetic inheritance, and selective parent-replacement mechanisms are currently proposed extensions. They are deliberately excluded from the v0.1 implementation until the initial three mechanisms have been measured independently. This staged scope prevents unsupported claims and makes it possible to identify the contribution and cost of each mechanism.

The prototype has passed initial unit tests. It has not yet been integrated into a complete Qiner implementation, tested on a live Qubic node, or shown to outperform the existing baseline. The purpose of this research is therefore to establish a reproducible experimental framework and evaluate the idea objectively.

---

## 1. Research Motivation

Qubic’s Ant Colony Mining provides an interesting basis for decentralized computation by allowing miners to build on previously discovered solutions rather than repeatedly starting from scratch.

This creates a possible opportunity to investigate additional biologically inspired mechanisms for:

- Adaptive exploration of the solution space.
- Selection and refinement of promising parents or paths.
- Allocation of computational resources.
- Reduction of redundant exploration.
- Cooperation among independent computational agents.
- Evolutionary development of useful structures.

The central research question is:

> Can simple, decentralized, and measurable biological principles improve search efficiency without compromising determinism, decentralization, protocol compatibility, or computational performance?

No performance improvement is assumed in advance. The answer must be determined through controlled experiments against a clearly defined baseline.

---

## 2. Research Objectives

The project has five primary objectives:

1. Develop a standalone implementation of biologically inspired adaptive search mechanisms.
2. Evaluate each mechanism independently before combining them.
3. Compare MBIO with an appropriate Qiner or Ant Colony Mining baseline.
4. Measure both potential benefits and additional computational or communication costs.
5. Produce open, reproducible, and reviewable experimental results.

The immediate practical objective is not to modify consensus rules or the BPP-9000 mechanism. The immediate objective is to test whether a search strategy can improve mining-related exploration while preserving the existing solution-validation process.

---

## 3. Biological Models and Computational Interpretation

### 3.1 Slime Mold: Adaptive Search and Trail Optimization

Slime molds, including *Physarum polycephalum*, can form efficient networks through local feedback, reinforcement, and adaptation.

In MBIO, this principle is interpreted computationally as follows:

- Reinforce paths associated with promising solutions.
- Reduce the influence of persistently unproductive paths.
- Explore alternative branches dynamically.
- Allocate computational effort according to measured historical performance.

The biological analogy is not intended to be a literal simulation. It is used as inspiration for a feedback-driven search algorithm.

### 3.2 Termite Colonies: Cumulative Memory and Stigmergic Construction

Termites can collectively construct complex structures through local interactions and environmental modifications, without relying on a centralized blueprint.

In MBIO, this principle is represented by a cumulative memory of successful paths and structural patterns:

- Successful patterns leave a measurable trace.
- The trace decays gradually over time.
- Useful patterns can be reused across later search iterations.
- Ineffective patterns gradually lose influence.

This mechanism may be relevant to evolutionary structural search, but the initial prototype focuses on its use as adaptive computational memory.

### 3.3 Wolf Packs: Dynamic Role Specialization

Wolf packs provide a conceptual model for cooperation, differentiated behavior, and adaptation to changing conditions.

In MBIO, this idea is translated into dynamic computational roles:

- **Explorer:** searches new regions of the solution space.
- **Refiner:** improves promising existing solutions.
- **Architect:** investigates structural or initialization changes.

The roles are computational abstractions. They do not claim to reproduce animal behavior literally. Role weights may be adjusted according to measured performance rather than assigned through permanent hierarchical authority.

### 3.4 Silk-Inspired Structural Memory

Silk production provides an additional metaphor for creating persistent but adaptable links between useful structures. In MBIO, a silk-inspired mechanism can represent stable links between promising parents, solution patterns, and regions of the search space.

Unlike a short-term ant trail, a structural link would remain useful for a longer period and would decay only when it repeatedly fails to produce improvements. This mechanism could help preserve valuable patterns without permanently freezing the search.

Possible uses include:

- Linking successful parents to the solution patterns they produced.
- Preserving reusable structural configurations across generations.
- Creating a temporary local search region around a promising solution.
- Providing a diversity bonus when a stable link leads to a new and different improvement.

The link must remain reversible and bounded. If it becomes too strong, the algorithm may converge prematurely and stop exploring better regions.

### 3.5 Genetic Inheritance and Variation

Genetic algorithms provide a natural computational model for inheritance, variation, and selection. In MBIO, a parent solution can produce one or more offspring through controlled mutation or recombination, where supported by the search architecture.

The proposed process is:

1. Select one or more parents according to adaptive path weights.
2. Generate offspring through a permitted mutation or recombination operation.
3. Evaluate the offspring using the same objective and validation rules as the baseline.
4. Preserve useful traits or patterns in the cumulative memory.
5. Compare the offspring with its parent or parent group.

This mechanism must not change the underlying validity rules. Genetic operations would only control how candidate solutions are explored; they would not change the rules used to validate an accepted result.

### 3.6 Selective Parent Replacement

The project originally described this concept using the metaphor of a “death” mechanism: an older parent is removed when a better offspring is produced. For a technical research project, the more precise term is **Selective Parent Replacement**, **Generational Replacement**, or **Parent Retirement**.

The computational rule is:

```text
if offspring_score > parent_score:
    preserve(offspring)
    retire_or_downweight(parent)
else:
    preserve(parent)
    reduce_or_reject(offspring)
```

The parent is not literally destroyed. It is either removed from the active population, assigned a lower selection weight, or moved to an archive. This allows the best offspring to inherit the parent’s search position while preventing poor or obsolete solutions from consuming unlimited resources.

To preserve diversity, replacement should not always be immediate. Possible safeguards include:

- Keeping a small archive of historically strong parents.
- Applying replacement only after repeated evidence of improvement.
- Retaining diverse solutions even when they are not currently the best.
- Using an age limit or inactivity threshold.
- Reserving a fixed percentage of resources for exploration.

The hypothesis is that selective parent replacement may improve convergence and resource allocation, but it may also cause premature convergence. This trade-off must be measured experimentally.

---

## 4. Mathematical Model

### 4.1 Adaptive Path Weight

For each candidate path or parent `p`, MBIO calculates an adaptive weight:

```text
W_p = Q_p + τ_p
```

Where:

- `Q_p` is the measured quality of the previous solution or parent associated with path `p`.
- `τ_p` is the accumulated adaptive memory or trail strength associated with path `p`.
- `W_p` is the resulting selection weight.

In a production implementation, `Q_p` and `τ_p` should be normalized or scaled to comparable ranges. This is necessary to prevent one term from dominating the other.

### 4.2 Probability of Selection

The basic probability of selecting path `p` is:

```text
P_base(p) = W_p / Σ_j W_j
```

To preserve exploration, MBIO can reserve an exploration probability `ε`. The final probability can be expressed as:

```text
P(p) = (1 - ε) × P_base(p) + ε / N
```

Where:

- `ε` is the exploration probability.
- `N` is the number of eligible paths.

The default prototype value is:

```text
ε = 0.125
```

This corresponds to 12.5% uniform exploration, subject to implementation details and experimental validation.

### 4.3 Adaptive Memory Update

The initial memory update is:

```text
τ_(t+1) = (7/8) × τ_t + Δτ
```

Where:

- `τ_t` is the current memory value.
- `7/8` is the initial retention or decay factor.
- `Δτ` is the reinforcement added after a meaningful improvement.

The reinforcement rule should be defined explicitly in experiments. A possible rule is:

```text
Δτ = α × improvement_score
```

where `α` is a configurable reinforcement coefficient.

The implementation should also define minimum and maximum bounds for `τ` to avoid underflow, overflow, or unbounded accumulation.

### 4.4 Dynamic Role Weights

Each role receives a performance score based on measurable outcomes, such as:

- Improvement achieved.
- Number of useful solutions discovered.
- Computational cost.
- Time required to produce an improvement.
- Diversity contribution.

Role weights can then be updated using a bounded rule such as:

```text
R_(t+1) = clamp((1 - β) × R_t + β × performance_t, R_min, R_max)
```

Where:

- `R_t` is the previous role weight.
- `β` is the adaptation rate.
- `performance_t` is the measured role performance.
- `clamp` keeps the value within safe limits.

This formula is a research starting point, not a final protocol specification.

---

## 5. MBIO Prototype v0.1

A first independent prototype has been implemented in C++17. The prototype is designed as a research module rather than as a replacement for Qiner or a modification of Qubic consensus rules.

### 5.1 Implemented Components

| Biological model | Prototype interpretation |
|---|---|
| Slime mold | Adaptive path and parent selection based on solution quality and accumulated trail memory |
| Termite colonies | Cumulative memory of successful paths and patterns with gradual decay |
| Wolf packs | Dynamic computational roles for exploration, refinement, and structural exploration |
| Silk-inspired memory | Persistent but bounded links between successful parents, patterns, and search regions |
| Genetic inheritance | Controlled mutation or recombination, subject to the baseline search and validation rules |
| Selective parent replacement | Retiring, archiving, or down-weighting weaker parents after validated improvement by offspring |

### 5.2 Current Project Files

The prototype package contains:

- `mbio_strategy.hpp` — core MBIO strategy.
- `mbio_tests.cpp` — initial unit tests.
- `CMakeLists.txt` — C++17 build configuration.
- `INTEGRATION.md` — preliminary integration guidance.
- `README.md` — project overview and usage instructions.

### 5.3 Current Status

The current prototype has:

- Been implemented in C++17.
- Passed the initial build process.
- Passed initial unit tests.
- Implemented adaptive path selection.
- Implemented parent-selection logic.
- Implemented cumulative memory reinforcement and decay.
- Implemented preliminary dynamic role assignment.

The following mechanisms remain proposed extensions and are not yet claimed as implemented in MBIO v0.1:

- Silk-inspired structural memory.
- Genetic inheritance or recombination.
- Selective parent replacement and parent retirement.

The prototype has **not** yet:

- Been integrated into the complete Qiner implementation.
- Been tested on a live Qubic node.
- Been validated against a production mining environment.
- Demonstrated a statistically significant performance improvement.
- Changed BPP-9000 or the rules for accepting valid solutions.

These limitations are intentional and should be made clear in any technical review.

---

## 6. Potential Integration Points

Based on the preliminary review of the reference mining implementation, possible integration points may include:

1. Parent selection before the search process.
2. Selection of a mutation mode.
3. Selection of `L` and `K` values inside the nonce-search process, where permitted by the implementation.
4. Retention or ranking of successful ANN-related results.

These points require confirmation against the exact Qiner version, branch, and commit used for testing.

MBIO is not intended to change:

- The BPP-9000 mechanism.
- Existing rules for accepting solutions.
- The validity requirements for nonces.
- Consensus behavior.
- The deterministic verification process.

Any integration must be reviewed carefully to ensure that random-byte consumption, nonce construction, result recomputation, and node-side validation remain compatible.

---

## 7. Experimental Methodology

The scientific evaluation should proceed in stages.

### Stage 1: Independent Algorithm Tests

Test each mechanism separately:

- Adaptive parent selection only.
- Cumulative trail memory only.
- Dynamic role specialization only.
- Silk-inspired structural memory only.
- Genetic variation and selective parent replacement only.
- Combined MBIO strategy.

This will identify which component contributes value and which component creates unnecessary overhead.

### Stage 2: Baseline Comparison

Compare the following configurations:

1. Original Qiner or Ant Colony Mining baseline.
2. Baseline plus adaptive parent selection.
3. Baseline plus cumulative memory.
4. Baseline plus dynamic roles.
5. Baseline plus the complete MBIO strategy.

### Stage 3: Controlled Execution

Each configuration should use the same:

- Task or problem data.
- Runtime duration.
- Number of CPU cores.
- Hardware environment.
- Number of search attempts.
- Input conditions.
- Random-seed policy.
- Build configuration.

The exact Qiner repository, branch, and commit hash must be recorded.

### Stage 4: Repeated Trials

Because mining and search may be probabilistic, one run is not sufficient. Each configuration should be executed repeatedly using either:

- A fixed, documented set of random seeds; or
- An explicitly documented independent-seed policy.

The results should include averages, ranges, and uncertainty estimates where possible.

---

## 8. Performance Metrics

The following metrics should be collected:

- Number of accepted solutions.
- Best score.
- Best shift, where applicable.
- Improvements per second of processing.
- Number of candidate evaluations.
- Solution-discovery rate.
- Computational efficiency.
- CPU and memory consumption.
- Search diversity.
- Redundant computation reduction.
- Communication or coordination overhead.
- Scalability as the number of agents or threads increases.
- Stability across repeated experiments.
- Sensitivity to parameter changes.
- Preservation of deterministic recomputation and validation.

The primary metric should be defined before testing. For example, accepted solutions per unit of computational work may be more informative than accepted solutions per wall-clock second when hardware utilization differs.

---

## 9. Unit Testing and Validation Requirements

The initial unit tests verify basic behavior such as:

- Correct ordering of evaluated solutions.
- Valid parent selection.
- Expected nonce construction behavior.
- Preservation of search-randomness bytes.
- Memory reinforcement after an improvement.

Further testing is required before claiming production readiness. Recommended tests include:

- Empty-path and single-path cases.
- Zero and negative-quality handling.
- Extremely large and small trail values.
- Overflow and underflow protection.
- Probability normalization.
- No `NaN` or infinite values.
- Repeated-seed reproducibility.
- No-solution-found conditions.
- Thread-safety and race-condition testing.
- Serialization and state-restoration testing, if state is persisted.
- Validation of results against the appropriate node-side recomputation process.

The initial test result of `1/1` indicates that the current test target passed. It does not establish superiority over the baseline or protocol-level correctness.

---

## 10. Risks and Limitations

The main research risks are:

1. **Additional overhead:** calculating adaptive weights may cost more than the benefit it produces.
2. **Premature convergence:** excessive reinforcement may cause the search to focus too quickly on a narrow region.
3. **Parameter sensitivity:** results may depend heavily on decay, exploration, and reinforcement values.
4. **Reduced reproducibility:** uncontrolled randomness can make comparisons unreliable.
5. **Determinism concerns:** integration must not interfere with expected verification behavior.
6. **Coordination cost:** dynamic roles may add complexity without improving results.
7. **Weak biological analogy:** a biological metaphor does not guarantee a useful algorithm.
8. **Baseline uncertainty:** an unfair or incomplete baseline can produce misleading conclusions.
9. **Hardware dependence:** results on one CPU or system may not generalize to another.

The research should report negative or neutral results honestly. A component that does not improve performance may still provide useful information by identifying an ineffective direction.

---

## 11. Expected Contributions

This research aims to provide:

- A standalone C++17 implementation of biologically inspired adaptive search mechanisms.
- A mathematical framework for adaptive path selection and cumulative memory.
- A preliminary model for dynamic computational roles.
- A reproducible comparison methodology.
- An assessment of computational benefits and costs.
- Open documentation that can be reviewed by developers and researchers.
- Evidence about which mechanisms are practically useful and which are not.

The broader objective is to determine whether biological collective-intelligence principles can provide measurable and protocol-compatible value in decentralized computational and evolutionary systems related to Qubic.

---

## 12. Recommended Next Steps

The recommended next phase is:

1. Obtain or identify the exact Qiner version to be used as the baseline.
2. Record the repository URL, branch, commit hash, compiler, and build configuration.
3. Integrate only one MBIO component first, preferably adaptive parent selection.
4. Preserve the original nonce, mutation, validation, and random-byte behavior unless explicitly approved for change.
5. Build the original baseline and MBIO version using the same environment.
6. Run controlled benchmark trials.
7. Add logging without changing the computational behavior being measured.
8. Compare accepted solutions, scores, shifts, work performed, and resource usage.
9. Repeat the experiments across multiple seeds and durations.
10. Decide whether the memory and role-specialization components justify a second experiment.

The first scientific milestone should be a fair, reproducible comparison between:

```text
Qiner baseline
versus
Qiner with one isolated MBIO mechanism
```

Only after that comparison should the complete MBIO strategy be evaluated.

---

## 13. Conclusion

MBIO is an independent research prototype that translates three biological principles into computational mechanisms for adaptive search:

- Slime mold inspires feedback-driven path selection.
- Termite colonies inspire cumulative memory and gradual decay.
- Wolf packs inspire dynamic role specialization.

The current prototype represents a transition from theoretical design to executable research. However, it should not yet be described as a proven improvement to Qubic mining. Its current status is that of an early, testable, and reviewable prototype.

The decisive next step is a controlled comparison with the original Qiner or Ant Colony Mining baseline. The outcome may be positive, neutral, or negative. Any of these outcomes can be scientifically valuable if the methodology is fair, the implementation is documented, and the results are reproducible.

The project is therefore presented as an invitation for technical feedback and collaborative evaluation, not as a claim that the proposed mechanisms are already production-ready.

---

## Appendix A: Critical Review and Revised Research Plan

This appendix records the main limitations of the expanded proposal and converts them into testable research requirements. The purpose is to reduce scope, separate hypotheses, and avoid presenting untested mechanisms as demonstrated improvements.

### A.1 Current Maturity Level

MBIO v0.1 is an independent prototype, not a validated Qiner extension. It currently implements the initial three mechanisms:

1. Adaptive path and parent selection.
2. Cumulative trail or pattern memory.
3. Preliminary dynamic role assignment.

Silk-inspired structural memory, genetic inheritance, and selective parent replacement are deferred extensions. They must not be described as implemented until source code, unit tests, and benchmark results exist for each one.

### A.2 Revised Scope: One Mechanism at a Time

The project will use a staged ablation design rather than introducing six mechanisms simultaneously:

| Experiment | Configuration | Purpose |
|---|---|---|
| E0 | Original baseline | Establish reference performance |
| E1 | Baseline + adaptive parent selection | Measure the value of path selection |
| E2 | Baseline + cumulative memory | Measure the value of historical information |
| E3 | Baseline + role assignment | Measure the value of specialization |
| E4 | Best single mechanism only | Confirm the strongest isolated result |
| E5 | Best two mechanisms | Measure interaction and added cost |
| E6 | Full combination, only if justified | Test whether combined value exceeds complexity |

The silk, genetic, and replacement extensions will enter this table only after the first three mechanisms have produced reproducible results.

### A.3 Explicit Anti-Convergence Safeguards

The risk of premature convergence will be treated as a design constraint rather than only a theoretical limitation. The experiment must record diversity and stagnation, not only the best score.

Candidate safeguards include:

- A minimum exploration probability that cannot fall below a documented lower bound.
- A maximum trail or memory weight.
- Periodic memory decay or reset after a stagnation window.
- A diversity threshold preventing all active agents from selecting the same parent.
- An archive of historically strong but structurally different solutions.
- A stagnation detector that temporarily increases exploration.
- Delayed parent replacement requiring repeated or statistically credible improvement.

A possible stagnation rule is:

```text
if no_improvement_for >= T:
    increase_exploration()
    decay_or_reset_memory()
```

These safeguards are hypotheses to be tested, not guarantees. Each one adds potential overhead and must be compared with a simpler baseline.

### A.4 Revised Mathematical Model

The initial rule `W_p = Q_p + τ_p` is retained only as a conceptual starting point. The experimental implementation should normalize the quality and memory terms before combining them:

```text
q_p = normalize(Q_p)
t_p = normalize(τ_p)
W_p = λq_p + (1 - λ)t_p
```

Where `λ` is a documented parameter in `[0, 1]`. The selection rule can then include bounded exploration:

```text
P(p) = (1 - ε) × W_p / Σ_j W_j + ε / N
```

The value `ε = 0.125` must not be treated as evidence of improvement. Since it may overlap with an existing Qiner ratio or behavior, the experiment must compare:

- The original Qiner behavior.
- The original behavior with the same nominal exploration ratio.
- MBIO with a documented range of exploration values.

The research should perform a small sensitivity analysis over `λ`, `ε`, the decay factor, and the reinforcement coefficient. Parameters must be selected without tuning exclusively to a favorable test result.

### A.5 Interaction Analysis

The interaction between mechanisms will be measured explicitly. If two mechanisms are combined, the result should be compared with the sum of their isolated effects:

```text
interaction(E1, E2) = performance(E1+E2)
                     - performance(E1)
                     - performance(E2)
                     + performance(E0)
```

This does not prove causality by itself, but it provides a useful first estimate of whether the mechanisms complement or interfere with each other.

### A.6 Computational Cost Model

Every experiment must report the overhead introduced by MBIO. At minimum, measure:

- Nanoseconds or CPU cycles per candidate-selection decision.
- Additional memory per path, parent, and role.
- Number of memory updates per evaluated candidate.
- Number of random-number calls.
- Branches or synchronization points added to the hot path.
- Cache and allocation behavior where practical.
- Throughput change in candidates evaluated per second.

A simple cost ratio can be reported as:

```text
overhead_ratio = (baseline_work - MBIO_work) / baseline_work
```

where `work` may be represented by candidates evaluated per second or another predeclared unit. A mechanism should be considered promising only if its measurable search benefit is weighed against this cost.

### A.7 Integration Confidence Levels

Integration statements will be classified into three levels:

- **Level 0 — Conceptual:** a possible research location has been identified, but no source-level confirmation exists.
- **Level 1 — Source-reviewed:** the location has been checked against a named repository, branch, and commit.
- **Level 2 — Prototype-integrated:** the mechanism builds and runs inside the selected Qiner version without changing validation rules.

The current proposal should describe the integration points as Level 0 until the exact repository version and commit are documented. No claim of Qiner compatibility should be made before reaching Level 2.

### A.8 Reframing the Biological Analogies

Biological systems are used as inspiration, not as evidence of algorithmic superiority. The technical description should always come first:

- “Adaptive feedback-weighted parent selection” is the algorithm; slime mold is the inspiration.
- “Decaying historical path memory” is the algorithm; termite stigmergy is the inspiration.
- “Dynamic role allocation” is the algorithm; social-animal cooperation is the inspiration.
- “Persistent bounded structural links” is the algorithm; silk is the inspiration.
- “Validated offspring replacement” is the algorithm; genetic inheritance is the inspiration.

This wording prevents the research from depending on biological metaphor alone.

### A.9 Evidence Required Before Any Performance Claim

The project will not use words such as “improves,” “faster,” or “more efficient” unless the claim is supported by:

1. A named baseline version and commit.
2. Identical hardware and build settings.
3. Multiple independent trials.
4. Documented seeds or a documented seed policy.
5. Predefined primary and secondary metrics.
6. Reported variance or uncertainty.
7. Measured computational overhead.
8. Confirmation that validation and recomputation remain correct.

Until these conditions are met, the correct terms are “proposes,” “explores,” “may,” and “hypothesizes.”

### A.10 Revised Research Milestones

The revised milestones are:

**Milestone 1 — Baseline reproduction:** build and run the selected baseline without MBIO changes.

**Milestone 2 — Isolated mechanism:** integrate only adaptive parent selection and measure its cost and behavior.

**Milestone 3 — Repeated evaluation:** repeat the experiment across documented seeds, workloads, and durations.

**Milestone 4 — Second mechanism:** add cumulative memory only if Milestone 2 produces a clear, reproducible reason to continue.

**Milestone 5 — Deferred extensions:** implement silk memory, genetic variation, or selective replacement only as separate experiments with their own tests and cost reports.

**Milestone 6 — Review package:** publish source code, build instructions, logs, benchmark methodology, limitations, and results in readable text files.

This revised plan makes a negative result acceptable. If MBIO adds overhead without improving the declared metric, that result will still identify a useful boundary for future research.
