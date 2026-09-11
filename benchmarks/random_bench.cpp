#include "genedit.hpp"

#include <benchmark/benchmark.h>

static void BM_RandomDNA(benchmark::State& state) {
    const size_t size{ 32 };

    for (auto _ : state) {
        DNA dna{ .bytes{ random_dna(size) } };
        benchmark::DoNotOptimize(dna);
    }
}

BENCHMARK(BM_RandomDNA);