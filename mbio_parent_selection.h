#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <random>
#include <unordered_map>
#include <vector>

namespace mbio
{

// A small, protocol-neutral view of an AntMiner parent. The selector does not
// change ANN bytes, nonce construction, BPP-9000 scoring, or validation.
struct ParentCandidate
{
    std::uint64_t id = 0;
    std::uint32_t score = std::numeric_limits<std::uint32_t>::max();
    bool resolved = false;
    bool extendable = false;
};

struct SelectionConfig
{
    // Keep the existing AntMiner exploration ratio as the default. The value
    // is deliberately configurable so experiments can compare alternatives.
    double exploration_probability = 1.0 / 8.0;
    double quality_weight = 0.75;
    double trail_weight = 0.25;
    double trail_decay = 7.0 / 8.0;
    double max_trail = 1.0;
};

class AdaptiveParentSelector
{
public:
    explicit AdaptiveParentSelector(SelectionConfig config = {})
        : config_(config)
    {
        if (!(config_.exploration_probability >= 0.0 && config_.exploration_probability <= 1.0))
        {
            config_.exploration_probability = 1.0 / 8.0;
        }
        config_.quality_weight = std::max(0.0, config_.quality_weight);
        config_.trail_weight = std::max(0.0, config_.trail_weight);
        if (config_.quality_weight + config_.trail_weight == 0.0)
        {
            config_.quality_weight = 1.0;
        }
        config_.trail_decay = std::clamp(config_.trail_decay, 0.0, 1.0);
        config_.max_trail = std::max(0.0, config_.max_trail);
    }

    // Returns the index of the selected candidate, or candidates.size() when
    // no resolved and extendable candidate exists. If explore is true, the
    // caller supplies a deterministic uniform-random choice through rng.
    std::size_t select(const std::vector<ParentCandidate>& candidates,
                       bool explore,
                       std::mt19937_64& rng) const
    {
        std::vector<std::size_t> eligible;
        eligible.reserve(candidates.size());
        for (std::size_t i = 0; i < candidates.size(); ++i)
        {
            if (candidates[i].resolved && candidates[i].extendable)
            {
                eligible.push_back(i);
            }
        }
        if (eligible.empty())
        {
            return candidates.size();
        }
        if (explore)
        {
            std::uniform_int_distribution<std::size_t> pick(0, eligible.size() - 1);
            return eligible[pick(rng)];
        }

        std::size_t best = eligible.front();
        double best_weight = weight(candidates[best]);
        for (const std::size_t i : eligible)
        {
            const double current = weight(candidates[i]);
            if (current > best_weight
                || (current == best_weight && candidates[i].score < candidates[best].score))
            {
                best = i;
                best_weight = current;
            }
        }
        return best;
    }

    // Call after a child is validated. improvement must be positive when the
    // child is better than the selected parent; otherwise the trail decays.
    void update(std::uint64_t parent_id, double improvement)
    {
        double& trail = trails_[parent_id];
        trail *= config_.trail_decay;
        if (improvement > 0.0)
        {
            trail += improvement;
        }
        trail = std::clamp(trail, 0.0, config_.max_trail);
    }

    double trail(std::uint64_t parent_id) const
    {
        const auto it = trails_.find(parent_id);
        return it == trails_.end() ? 0.0 : it->second;
    }

    double weight(const ParentCandidate& candidate) const
    {
        const double quality = 1.0 / (1.0 + static_cast<double>(candidate.score));
        const double trail_value = trail(candidate.id);
        const double total = config_.quality_weight + config_.trail_weight;
        return (config_.quality_weight * quality + config_.trail_weight * trail_value) / total;
    }

    const SelectionConfig& config() const { return config_; }

private:
    SelectionConfig config_;
    std::unordered_map<std::uint64_t, double> trails_;
};

} // namespace mbio
