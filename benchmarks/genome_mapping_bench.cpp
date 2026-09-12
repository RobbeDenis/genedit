#include "genedit.hpp"
#include "slime.hpp"

#include <benchmark/benchmark.h>

constexpr size_t n{ 256 };

static void BM_RawPadded(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<SlimePadded> slimes{ };
        slimes.reserve(n);
        for (size_t i{ 0 }; i < n; ++i) {
            slimes.emplace_back(SlimePadded{ .dna{ random_dna(Slime::DNA_SIZE) } });
            interpret_dna_raw(slimes[i].dna, &slimes[i].genome, Slime::SM);
            benchmark::DoNotOptimize(slimes);
        }
    }
}

static void BM_Checked(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<Slime> slimes{ };
        slimes.reserve(n);
        for (size_t i{ 0 }; i < n; ++i) {
            slimes.emplace_back(Slime{ .dna{ random_dna(Slime::DNA_SIZE) } });
            interpret_dna_checked(slimes[i].dna, &slimes[i].genome, Slime::SM);
            benchmark::DoNotOptimize(slimes);
        }
    }
}

BENCHMARK(BM_RawPadded);
BENCHMARK(BM_Checked);