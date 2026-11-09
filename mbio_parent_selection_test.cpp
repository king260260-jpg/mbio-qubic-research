#include <catch2/catch.hpp>

#include "ant/mbio_parent_selection.h"

#include <random>
#include <vector>

TEST_CASE("adaptive selector matches baseline when trails are empty", "[mbio][parent]")
{
    std::vector<mbio::ParentCandidate> candidates = {
        {10, 4200, true, true},
        {20, 1200, true, true},
        {30, 2500, true, true},
    };
    mbio::AdaptiveParentSelector selector;
    std::mt19937_64 rng(7);

    const std::size_t selected = selector.select(candidates, false, rng);
    REQUIRE(selected == 1);
    REQUIRE(candidates[selected].score == 1200);
}

TEST_CASE("adaptive trail can reward a parent after validated improvement", "[mbio][parent]")
{
    std::vector<mbio::ParentCandidate> candidates = {
        {10, 1000, true, true},
        {20, 1100, true, true},
    };
    mbio::SelectionConfig config;
    config.quality_weight = 0.25;
    config.trail_weight = 0.75;
    mbio::AdaptiveParentSelector selector(config);
    std::mt19937_64 rng(9);

    REQUIRE(selector.select(candidates, false, rng) == 0);
    selector.update(20, 1.0);
    REQUIRE(selector.trail(20) == Approx(1.0));
    REQUIRE(selector.select(candidates, false, rng) == 1);
}

TEST_CASE("adaptive selector excludes unresolved or non-extendable parents", "[mbio][parent]")
{
    std::vector<mbio::ParentCandidate> candidates = {
        {10, 1, false, true},
        {20, 2, true, false},
        {30, 3, true, true},
    };
    mbio::AdaptiveParentSelector selector;
    std::mt19937_64 rng(11);

    REQUIRE(selector.select(candidates, false, rng) == 2);
}

TEST_CASE("adaptive exploration is deterministic with a fixed seed", "[mbio][parent]")
{
    std::vector<mbio::ParentCandidate> candidates = {
        {10, 10, true, true},
        {20, 20, true, true},
        {30, 30, true, true},
        {40, 40, true, true},
    };
    mbio::AdaptiveParentSelector selector;
    std::mt19937_64 rng_a(1234);
    std::mt19937_64 rng_b(1234);

    for (int i = 0; i < 20; ++i)
    {
        REQUIRE(selector.select(candidates, true, rng_a) == selector.select(candidates, true, rng_b));
    }
}

TEST_CASE("trail decay is bounded and reproducible", "[mbio][parent]")
{
    mbio::SelectionConfig config;
    config.trail_decay = 7.0 / 8.0;
    config.max_trail = 1.0;
    mbio::AdaptiveParentSelector selector(config);

    selector.update(99, 10.0);
    REQUIRE(selector.trail(99) == Approx(1.0));
    selector.update(99, 0.0);
    REQUIRE(selector.trail(99) == Approx(7.0 / 8.0));
}
