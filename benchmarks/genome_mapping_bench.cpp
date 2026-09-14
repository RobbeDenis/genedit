#include "genedit.hpp"
#include "slime.hpp"

#include <benchmark/benchmark.h>

constexpr size_t n{ 256 };

static void BM_Direct(benchmark::State& state) {
    for (auto _ : state) {
        using TSlime = Slime<genedit::gm::Direct>;
        std::vector<TSlime> slimes{ };
        slimes.reserve(n);
        for (size_t i{ 0 }; i < n; ++i) {
            slimes.emplace_back(TSlime{ .dna{ genedit::random_dna(TSlime::DNA_SIZE) } });
            slimes[i].map_genome();
            benchmark::DoNotOptimize(slimes);
        }
    }
}

static void BM_DirectUnchecked(benchmark::State& state) {
    for (auto _ : state) {
        using TSlime = Slime<genedit::gm::DirectUnchecked, SlimeGenomePadded>;
        std::vector<TSlime> slimes{ };
        slimes.reserve(n);
        for (size_t i{ 0 }; i < n; ++i) {
            slimes.emplace_back(TSlime{ .dna{ genedit::random_dna(TSlime::DNA_SIZE) } });
            slimes[i].map_genome();
            benchmark::DoNotOptimize(slimes);
        }
    }
}

static void BM_DirectManualUnchecked(benchmark::State& state) {
    for (auto _ : state) {
        using TSlime = Slime<genedit::gm::DirectManualUnchecked, SlimeGenomePadded>;
        std::vector<TSlime> slimes{ };
        slimes.reserve(n);
        for (size_t i{ 0 }; i < n; ++i) {
            slimes.emplace_back(TSlime{ .dna{ genedit::random_dna(TSlime::DNA_SIZE) } });
            slimes[i].map_genome();
            benchmark::DoNotOptimize(slimes);
        }
    }
}

BENCHMARK(BM_Direct);
BENCHMARK(BM_DirectUnchecked);
BENCHMARK(BM_DirectManualUnchecked);